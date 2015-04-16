
#include "stdafx.h"
#include "ProjectPaths.h"

namespace {

	void GetRegFiles( std::vector< std::string >* p_filelist )
	{
		// Clear the list
		assert( p_filelist != 0 );
		p_filelist->clear();

		// Get keys for all users
		WinAPI::RegKey users_key( HKEY_USERS );
		std::vector< std::string > users;
		users_key.EnumKeys( &users );

		// Check all users
		for ( size_t i=0; i < users.size(); i++ ) {

			// Open folders key
			const std::string key_name = users[i] + "\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders";
			WinAPI::RegKey folders_key;
			if ( 0 != folders_key.Open( HKEY_USERS, key_name.c_str(), KEY_READ ) )
				continue;

			// Get folder name
			std::string dirname;
			if ( 0 != folders_key.QueryValue( "Local AppData", &dirname ) || dirname.empty() )
				continue;

			// Add fully qualified file name to the list
			p_filelist->push_back( dirname + "\\Microsoft\\VisualStudio\\7.0\\VCComponents.dat" );
		}
	}

	bool LoadFile( WinAPI::File& file, std::string* p_contents )
	{
		assert( p_contents != 0 );
		if ( ! file.IsOpen() )
			return false;
		const int size = file.GetSize();
		p_contents->resize( size );
		return size != 0 && size == file.Read( &(*p_contents)[0], size );
	}

}

void RegisterPath( const std::string& section_name, const std::string& path )
{
	// Make the path valid
	std::string pattern = path;
	if ( ! pattern.empty() && pattern[ pattern.size()-1 ] == '\\' )
		pattern.resize( pattern.size() - 1 );

	// Make the section valid
	std::string section = section_name;
	if ( ! section.empty() && section[ section.size()-1 ] != '=' )
		section += '=';

	// Traverse all config files for all users
	std::vector< std::string > filelist;
	GetRegFiles( &filelist );
	for ( size_t i=0; i < filelist.size(); i++ ) {

		// Load settings file
		WinAPI::File file( filelist[i].c_str() );
		std::string contents;
		if ( ! LoadFile( file, &contents ) )
			continue;

		// Add path to the appropriate section
		const size_t section_begin = contents.find( section );
		if ( section_begin == contents.npos )
			continue;
		size_t section_end = contents.find( "\r", section_begin );
		if ( section_end == contents.npos )
			continue;
		if ( section_end > 0 && contents[ section_end-1 ] != ';' )
			contents.insert( section_end, 1, ';' ),
			section_end++;
		contents.insert( section_end, pattern );

		// Save modified settings
		file.Seek( 0 );
		file.Truncate();
		file.Write( &contents[0], static_cast<int>( contents.size() ) );
	}
}

void DeregisterPath( const std::string& path )
{
	// Make the path valid
	std::string pattern = path;
	if ( ! pattern.empty() && pattern[ pattern.size()-1 ] == '\\' )
		pattern.resize( pattern.size() - 1 );

	// Traverse all config files for all users
	std::vector< std::string > filelist;
	GetRegFiles( &filelist );
	for ( size_t i=0; i < filelist.size(); i++ ) {

		// Load settings file
		WinAPI::File file( filelist[i].c_str() );
		std::string contents;
		if ( ! LoadFile( file, &contents ) )
			continue;

		// Remove all occurences of path
		size_t idx = 0;
		while ( (idx = contents.find( pattern )) != contents.npos ) {
			size_t len_to_del = pattern.size();
			if ( idx > 0 && idx + pattern.size() < contents.size() && contents[idx-1] == ';' && contents[idx+pattern.size()] == ';' )
				len_to_del++;
			contents.erase( idx, len_to_del );
		}

		// Save modified settings
		file.Seek( 0 );
		file.Truncate();
		file.Write( &contents[0], static_cast<int>( contents.size() ) );
	}
}
