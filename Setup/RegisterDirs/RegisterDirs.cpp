
#include <winapi.h>
#include <locale>

using namespace WinAPI;
using namespace std;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	// Decompose command line into separate strings
	const string cmdline( GetCommandLine() );
	vector<string> argv;
	for ( size_t i=0; i < cmdline.size(); i++ ) {
		while ( i < cmdline.size() && isspace( cmdline[i] ) ) i++;
		if ( i >= cmdline.size() ) continue;
		if ( cmdline[i] == '"' ) {
			i++;
			size_t j = i;
			while ( i < cmdline.size() && cmdline[i] != '"' ) i++;
			argv.push_back( cmdline.substr( j, i-j ) );
			if ( i < cmdline.size() ) i++;
		} else {
			size_t j = i;
			while ( i < cmdline.size() && ! isspace( cmdline[i] ) ) i++;
			argv.push_back( cmdline.substr( j, i-j ) );
		}
	}
	if ( argv.size() < 3 )
		return 0;
	if ( argv[1] != "register" && argv[1] != "deregister" )
		return 0;

	// Process config files for subsequent users
	RegKey users_key( HKEY_USERS );
	vector<string> users;
	users_key.EnumKeys( &users );
	for ( size_t i=0; i < users.size(); i++ ) {

		// Open appropriate registry key (Shell Folders)
		const string key_name = users[i] + "\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders";
		RegKey folders_key;
		if ( 0 != folders_key.Open( HKEY_USERS, key_name.c_str(), KEY_READ ) )
			continue;

		// Get name of the directory with settings
		string dirname;
		if ( 0 != folders_key.QueryValue( "Local AppData", &dirname ) || dirname.empty() )
			continue;

		// Open the settings file
		const string filename = dirname + "\\Microsoft\\VisualStudio\\7.0\\VCComponents.dat";
		File file( filename.c_str() );
		if ( ! file.IsOpen() )
			continue;

		// Load the settings file
		const int size = file.GetSize();
		string contents( size, '\0' );
		if ( file.Read( &contents[0], size ) != size )
			continue;

		// Perform an action depending on the command line
		string pattern = argv[2];
		if ( pattern[pattern.size()-1] == '\\' ) pattern.resize( pattern.size()-1 );
		pattern += ';';
		if ( argv[1] == "register" ) {
			const size_t includes_idx = contents.find( "Include Dirs=" );
			size_t includes_end_idx = contents.find( "\r", includes_idx );
			if ( includes_end_idx > 0 && contents[includes_end_idx-1] != ';' )
				contents.insert( includes_end_idx, 1, ';' ), includes_end_idx++;
			contents.insert( includes_end_idx, pattern );
			const size_t libraries_idx = contents.find( "Library Dirs=" );
			size_t libraries_end_idx = contents.find( "\r", libraries_idx );
			if ( libraries_end_idx > 0 && contents[libraries_end_idx-1] != ';' )
				contents.insert( libraries_end_idx, 1, ';' ), libraries_end_idx++;
			contents.insert( libraries_end_idx, pattern );
		} else {
			size_t idx = 0;
			while ( (idx=contents.find( pattern )) != contents.npos )
				contents.erase( idx, pattern.length() );
		}

		// Save the modified settings
		file.Seek( 0 );
		file.Truncate();
		file.Write( &contents[0], static_cast<int>(contents.size()) );
	}
	return 0;
}
