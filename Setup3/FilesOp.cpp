
#include "stdafx.h"
#include "FilesOp.h"

namespace {

	void RecursiveCopy( const std::string& src_dir, const std::string& dest_dir )
	{
		// Create destination directory
		CreateDirectory( dest_dir.substr( 0, dest_dir.size()-1 ).c_str(), 0 );

		// Copy files to the destination directory
		std::vector< std::string > files;
		WinAPI::FindFile::GetAll( (src_dir+"*.*").c_str(), &files, WinAPI::FindFile::FILES );
		for ( size_t i=0; i < files.size(); i++ )
			CopyFile( (src_dir+files[i]).c_str(), (dest_dir+files[i]).c_str(), FALSE );

		// Copy subdirectories
		std::vector< std::string > dirs;
		WinAPI::FindFile::GetAll( (src_dir+"*.*").c_str(), &dirs, WinAPI::FindFile::DIRECTORIES );
		for ( size_t i=0; i < dirs.size(); i++ )
			if ( dirs[i] != "." && dirs[i] != ".." )
				RecursiveCopy( src_dir+dirs[i]+"\\", dest_dir+dirs[i]+"\\" );
	}

}

void CopyFiles( const std::string& src_dir, const std::string& dest_dir )
{
	// Make directories valid
	std::string source = src_dir;
	if ( ! source.empty() && source[ source.size()-1 ] != '\\' )
		source += '\\';
	std::string destination = dest_dir;
	if ( ! destination.empty() && destination[ destination.size()-1 ] != '\\' )
		destination += '\\';

	// Copy directories
	RecursiveCopy( source, destination );
}

void RemoveTree( const std::string& directory )
{
	// Make directory name valid
	std::string dirname = directory;
	if ( ! dirname.empty() && dirname[ dirname.size()-1 ] != '\\' )
		dirname += '\\';

	// Recurse subdirectories
	std::vector< std::string > dirs;
	WinAPI::FindFile::GetAll( (dirname+"*.*").c_str(), &dirs, WinAPI::FindFile::DIRECTORIES );
	for ( size_t i=0; i < dirs.size(); i++ )
		if ( dirs[i] != "." && dirs[i] != ".." )
			RemoveTree( dirname+dirs[i]+'\\' );

	// Get the MoveFileEx function
	typedef BOOL (WINAPI* MOVEFILEEXA)( LPCSTR lpExistingFileName, LPCSTR lpNewFileName, DWORD dwFlags );
	HMODULE hkernel = GetModuleHandle( "KERNEL32.DLL" );
	MOVEFILEEXA move_method = (MOVEFILEEXA)GetProcAddress( hkernel, "MoveFileExA" );

	// Remove files
	std::vector< std::string > files;
	WinAPI::FindFile::GetAll( (dirname+"*.*").c_str(), &files, WinAPI::FindFile::FILES );
	for ( size_t i=0; i < files.size(); i++ ) {
		const std::string filename = dirname + files[i];
		if ( ! DeleteFile( filename.c_str() ) )
			if ( move_method )
				(*move_method)( filename.c_str(), 0, MOVEFILE_DELAY_UNTIL_REBOOT );
	}

	// Remove directory
	if ( ! dirname.empty() )
		dirname.resize( dirname.size()-1 );
	if ( ! RemoveDirectory( dirname.c_str() ) )
		if ( move_method )
			(*move_method)( dirname.c_str(), 0, MOVEFILE_DELAY_UNTIL_REBOOT );
}
