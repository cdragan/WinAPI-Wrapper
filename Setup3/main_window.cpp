
#include "StdAfx.h"
#include "main_window.h"
#include "HxNamespace.h"
#include "FilesOp.h"
#include "ProjectPaths.h"

using namespace WinAPI;

namespace {
	Application<
		/* window class  */	MainWindow,
		/* accelerators  */	ModelessDialogAccel< MainWindow >
		> app;

	enum {
		ID_FINITO = 123,
		ID_FINITO_U,
		ID_ABORT,
	};

	bool Exists( const char* filename )
	{
		return FindFile( filename ).IsOpen();
	}

	class ChooseFolderDialog: public Dialog {
		Edit folder;
		string install_folder;
	public:
		ChooseFolderDialog( string& oldinstalldir ): Dialog( IDD_CHOOSEFOLDER ), install_folder( oldinstalldir ) { }
		const char* GetInstallFolder() const { return install_folder.c_str(); }
	protected:
		virtual bool OnInitDialog( HWND hwndFocus, LPARAM lParam );
		virtual void OnCommand( int nIdentifier, int nNotifyCode, HWND hwndControl );
	};
}

MainWindow::MainWindow()
{
	INITCOMMONCONTROLSEX icc = { sizeof( INITCOMMONCONTROLSEX ), ICC_WIN95_CLASSES };
	InitCommonControlsEx( &icc );
	ModelessDialog::Create( IDD_SETUP3, 0 );
	Thread::Create();
}

void MainWindow::OnDestroy()
{
	PostQuitMessage( 0 );
}

void MainWindow::OnCommand( int nIdentifier, int nNotifyCode, HWND hwndControl )
{
	switch ( nIdentifier ) {

	case ID_FINITO:
		MessageBox( "WinAPI Wrapper installed successfully", "Setup", MB_OK | MB_ICONASTERISK );
		Destroy();
		break;

	case ID_FINITO_U:
		MessageBox( "WinAPI Wrapper uninstalled", "Setup", MB_OK | MB_ICONASTERISK );
		Destroy();
		break;

	case ID_ABORT:
		MessageBox( "Installation aborted", "Setup", MB_OK | MB_ICONASTERISK );
		Destroy();
		break;

	}
}

void MainWindow::Run()
{
	// Obtain old install dir
	RegKey instkey;
	instkey.OpenMachine( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\WinAPIWrapper" );
	string oldinstalldir;
	if ( instkey.QueryValue( "InstallDir", &oldinstalldir ) != ERROR_SUCCESS ) {
		RegKey key;
		key.OpenMachine( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion" );
		string program_files;
		key.QueryValue( "ProgramFilesDir", &program_files );
		oldinstalldir = program_files + "\\WinAPI Wrapper";
	}

	// Go to the startup directory
	const char* cmdline = GetCommandLine();
	int i = 0;
	while ( (cmdline[i] == ' ' || cmdline[i] == 9) && cmdline[i] != 13 && cmdline[i] != 0 )
		i++;
	const bool b_quote = cmdline[i] == '"';
	const int begin = b_quote ? (++i) : i;
	if ( b_quote )
		while ( cmdline[i] != '"' && cmdline[i] != 13 && cmdline[i] != 0 )
			i++;
	else
		while ( cmdline[i] != ' ' && cmdline[i] != 9 && cmdline[i] != 13 && cmdline[i] != 0 )
			i++;
	while ( i > begin && cmdline[i] != '\\' )
		i--;
	if ( i > begin )
		SetCurrentDirectory( string( cmdline+begin, i-begin ).c_str() );

	// Check if the user wants only to uninstall the old version
	if ( string(cmdline+i+1,strlen(cmdline)-i-1).find( "/uninstall" ) != string::npos ) {

		// Deregister stuff from VS
		DeregisterNamespace( "WinAPIWrapper" );
		DeregisterPath( oldinstalldir );

		// Get VS dir
		string idedir;
		RegKey uninst;
		uninst.OpenMachine( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\WinAPIWrapper" );
		uninst.QueryValue( "IDEDir", &idedir );
		uninst.Close();

		// Remove AppWizard
		if ( ! idedir.empty() ) {
			RemoveTree( idedir + "..\\..\\vc7\\VCWizards\\WinAPIWrapperWiz" );
			vector< string > files;
			const string vcpdir = idedir + "..\\..\\vc7\\vcprojects\\";
			FindFile::GetAll( (vcpdir + "WinAPIWrapperWiz.*").c_str(), &files, FindFile::FILES );
			for ( size_t i=0; i < files.size(); i++ )
				DeleteFile( (vcpdir + files[i]).c_str() );
		}

		// Remove installation files
		RemoveTree( oldinstalldir );

		// Remove registry keys
		uninst.OpenMachine( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall" );
		uninst.Delete( "WinAPIWrapper" );

		// OK
		PostMessage( WM_COMMAND, ID_FINITO_U );
		return;
	}

	string installdir;
	for (;;) {

		// Make the user select the installation folder
		ChooseFolderDialog dlg( oldinstalldir );
		if ( dlg.Go( *this ) != IDOK ) {
			PostMessage( WM_COMMAND, ID_ABORT );
			return;
		}
		installdir = dlg.GetInstallFolder();

		// Create install directory
		if ( ! CreateDirectory( installdir.c_str(), 0 ) && GetLastError() != ERROR_ALREADY_EXISTS )
			MessageBox( "Error: cannot create install folder", "Setup", MB_OK | MB_ICONSTOP );
		else
			break;
	}

	// Copy installation files
	CopyFiles( "WinAPIWrapper", installdir );

	// Get registry keys for installing the AppWizard
	const string mother_key_path( "SOFTWARE\\Microsoft\\VisualStudio" );
	RegKey vs_mother_key;
	vector<string> ver_keys;
	if ( vs_mother_key.OpenMachine( mother_key_path.c_str(), KEY_READ ) == ERROR_SUCCESS )
		vs_mother_key.EnumKeys( &ver_keys );

	// Install the AppWizard
	string idedir;
	for ( vector<string>::const_iterator kit=ver_keys.begin(); kit != ver_keys.end(); kit++ ) {

		// Get Visual Studio install path from the registry
		RegKey key;
		const bool b_visual_ok =
			key.OpenMachine( (mother_key_path+"\\"+*kit).c_str(), KEY_READ ) == ERROR_SUCCESS
			&& key.QueryValue( "InstallDir", &idedir ) == ERROR_SUCCESS;
		const string vcprojects = idedir + "..\\..\\vc7\\vcprojects";
		const string VCWizards = idedir + "..\\..\\vc7\\VCWizards";

		// Copy AppWizard
		if ( b_visual_ok && Exists( vcprojects.c_str() ) && Exists( VCWizards.c_str() ) ) {
			CopyFiles( "AppWizard\\vcprojects", vcprojects );
			CopyFiles( "AppWizard\\VCWizards", VCWizards );
			break;
		}
	}

	// Register help
	DeregisterNamespace( "WinAPIWrapper" );
	RegisterNamespace( installdir + "\\Help", "WinAPIWrapper", "WinAPI Wrapper", "WinAPI Wrapper library help" );

	// Register headers and libs
	DeregisterPath( oldinstalldir );
	RegisterPath( "Include Dirs", installdir );
	RegisterPath( "Library Dirs", installdir );

	// Register uninstaller
	RegKey uninst;
	uninst.CreateMachine( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\WinAPIWrapper" );
	uninst.SetValue( "DisplayName", "WinAPI Wrapper library" );
	uninst.SetValue( "UninstallString", ("\"" + installdir + "\\setup.exe\" /uninstall").c_str() );
	uninst.SetValue( "InstallDir", installdir.c_str() );
	uninst.SetValue( "IDEDir", idedir.c_str() );

	// End the info dialog
	PostMessage( WM_COMMAND, ID_FINITO );
}

bool ChooseFolderDialog::OnInitDialog( HWND hwndFocus, LPARAM lParam )
{
	folder = Edit( GetDlgItem( IDC_FOLDER ) );
	folder.SetText( install_folder.c_str() );
	return true;
}

void ChooseFolderDialog::OnCommand( int nIdentifier, int nNotifyCode, HWND hwndControl )
{
	switch ( nIdentifier ) {

	case IDOK:
		install_folder = folder.GetText();
		EndDialog( IDOK );
		break;

	case IDCANCEL:
		EndDialog( IDCANCEL );
		break;

	case IDC_BROWSE:
		{   GetFolderDialog dlg( *this, "Select installation folder:\n(e.g. C:\\Program Files\\)", BIF_NONEWFOLDERBUTTON | BIF_USENEWUI );
			if ( dlg.Go() )
				folder.SetText( (string( dlg.GetFolderName() ) + "\\WinAPI Wrapper").c_str() );
		}
		break;

	}
}
