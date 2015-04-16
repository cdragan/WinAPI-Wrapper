
#include "StdAfx.h"
#include "main_window.h"
[!if MDI_APP]
#include "document_window.h"
[!endif]

using namespace WinAPI;

namespace {
[!if !ACCELERATORS && SDI_APP]
	Application< MainWindow > app;
[!endif]
[!if ACCELERATORS && SDI_APP]
	Application<
		/* window class  */	MainWindow,
		/* accelerators  */	AccelFromResource< MainWindow, IDR_[!output UPPER_CASE_PROJECT_NAME] >
		> app;
[!endif]
[!if DIALOG_APP]
	Application<
		/* window class  */	MainWindow,
		/* accelerators  */	ModelessDialogAccel< MainWindow >
		> app;
[!endif]
[!if !ACCELERATORS && MDI_APP]
	Application<
		/* window class  */	MainWindow,
		/* accelerators  */	MDIAccel< MainWindow >
		> app;
[!endif]
[!if ACCELERATORS && MDI_APP]
	Application<
		/* window class  */	MainWindow,
		/* accelerators  */	MDIAccelFromResource< MainWindow, IDR_[!output UPPER_CASE_PROJECT_NAME] >
		> app;
[!endif]
[!if CUSTOM_WINDOW_CLASS]

	WindowClass main_wc(
		/* hIcon		*/	LoadIcon( __MODULE_HANDLE, MAKEINTRESOURCE(IDI_[!output UPPER_CASE_PROJECT_NAME]) ),
[!if MDI_APP]
		/* hbrBackground*/	0
[!else]
		/* hbrBackground*/	reinterpret_cast<HBRUSH>( COLOR_WINDOW+1 )
[!endif]
		);
[!endif]
}

MainWindow::MainWindow()
{
	INITCOMMONCONTROLSEX icc = { sizeof( INITCOMMONCONTROLSEX ), ICC_WIN95_CLASSES | ICC_COOL_CLASSES };
	InitCommonControlsEx( &icc );
[!if SDI_APP && !CUSTOM_WINDOW_CLASS && !MENU]
	Create( "[!output PROJECT_NAME]" );
[!endif]
[!if MDI_APP && !CUSTOM_WINDOW_CLASS && !MENU]
	Create( "[!output PROJECT_NAME]", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN );
[!endif]
[!if SDI_APP && CUSTOM_WINDOW_CLASS && !MENU]
	Create( "[!output PROJECT_NAME]", main_wc );
[!endif]
[!if MDI_APP && CUSTOM_WINDOW_CLASS && !MENU]
	Create( "[!output PROJECT_NAME]", main_wc, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN );
[!endif]
[!if !DIALOG_APP && MENU]
	Create(
		/* lpszWindowName	*/	"[!output PROJECT_NAME]",
[!if CUSTOM_WINDOW_CLASS]
		/* wndClass			*/	main_wc,
[!endif]
[!if SDI_APP]
		/* dwStyle			*/	WS_OVERLAPPEDWINDOW,
[!else]
		/* dwStyle			*/	WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
[!endif]
		/* rc				*/	WRect( WPoint( CW_USEDEFAULT, 0 ), CW_USEDEFAULT, 0 ),
		/* hwndParent		*/	0,
		/* hMenu			*/	LoadMenu( __MODULE_HANDLE, MAKEINTRESOURCE(IDR_MAINMENU) ),
		/* dwExStyle		*/	0,
		/* lParam			*/	0
		);
[!endif]
[!if DIALOG_APP]
	Create( IDD_[!output UPPER_CASE_PROJECT_NAME], 0 );
[!endif]
}
[!if !PURE_WRAPPER && ON_GENERIC && !MDI_APP]

int MainWindow::HandleMessage( int uMsg, int wParam, int lParam )
{
	switch ( uMsg ) {

	case WM_USER: // Replace this with your messages

	default:
[!if SDI_APP]
		return Window::HandleMessage( uMsg, wParam, lParam );
[!endif]
[!if DIALOG_APP]
		return ModelessDialog::HandleMessage( uMsg, wParam, lParam );
[!endif]

	}
}
[!endif]
[!if PURE_WRAPPER]

int MainWindow::HandleMessage( int uMsg, int wParam, int lParam )
{
	switch ( uMsg ) {

[!if !DIALOG_APP]
	case WM_CREATE:
[!else]
	case WM_INITDIALOG:
		SetIcon( LoadIcon( __MODULE_HANDLE, MAKEINTRESOURCE(IDI_[!output UPPER_CASE_PROJECT_NAME]) ) );
[!endif]
[!if MDI_APP]
		CreateClient( GetClientRect(), GetMenu().GetSubMenu( 1 ) );
		CreateDocumentWindow();
[!endif]
[!if STATUSBAR]
		statusbar.Create( *this );
[!endif]
[!if TOOLBAR]
[!if REBAR]
		rebar.Create( *this );

		toolbar.Create( *this, -1, TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_WRAPABLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_NODIVIDER );
[!else]
		toolbar.Create( *this, -1, TBSTYLE_TOOLTIPS );

[!endif]
		toolbar.AddBitmap( 3, IDB_TOOLBAR );
		toolbar.AddButton( 0, ID_FILE_NEW );
		toolbar.AddButton( 1, ID_FILE_OPEN );
		toolbar.AddButton( 2, ID_FILE_SAVE );
[!endif]
[!if REBAR]
		rebar.InsertBand( toolbar, toolbar.GetMaxSize(), "Toolbar" );

		combo.Create( WRect(0,0,200,0), *this, -1 );
		combo.SetFont( StockObject( DEFAULT_GUI_FONT ) );
		combo.AddString( "aaa" );
		combo.AddString( "bbb" );
		rebar.InsertBand( combo, "ComboBox" );

[!endif]
[!if DIALOG_APP]
		return 1;
[!else]
		return 0;
[!endif]

	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;

[!if !MDI_APP || MENU || TOOLBAR]
[!if ON_COMMAND || MENU || TOOLBAR]
	case WM_COMMAND:
[!endif]
[!if DIALOG_APP || MENU || TOOLBAR]
		switch ( LOWORD(wParam) ) {

[!endif]
[!if DIALOG_APP]
		case IDOK:
		case IDCANCEL:
			Destroy();
			break;

[!endif]
[!if MENU || TOOLBAR]
		case ID_FILE_NEW:
[!if MDI_APP]
			CreateDocumentWindow();
[!endif]
			break;

		case ID_FILE_OPEN:
			{	GetFileNameDialog dlg( *this );
				if ( dlg.GoOpen() )
					MessageBox( dlg.GetPathName(), "Opening file..." );
			}
			break;

		case ID_FILE_SAVE:
			{	GetFileNameDialog dlg( *this );
				if ( dlg.GoSave() )
					MessageBox( dlg.GetPathName(), "Saving file..." );
			}
			break;

[!endif]
[!if MENU]
		case ID_FILE_SAVEAS:
			{	GetFileNameDialog dlg( *this );
				if ( dlg.GoSave() )
					MessageBox( dlg.GetPathName(), "Saving file..." );
			}
			break;

		case ID_FILE_EXIT:
			SendMessage( WM_CLOSE );
			break;
[!if MDI_APP]

		case ID_WINDOW_TILE:
			MDITile();
			break;

		case ID_WINDOW_CASCADE:
			MDICascade();
			break;
[!endif]

		case ID_HELP_ABOUT:
			MessageBox( "This is an AppWizard-generated application skeleton\nApplication name: [!output PROJECT_NAME]", "About", MB_ICONASTERISK );
			break;

[!endif]
[!if DIALOG_APP || MENU || TOOLBAR]
		}
[!endif]
[!if ON_COMMAND || MENU || TOOLBAR]
[!if MDI_APP]
		return MDIFrameWindow::HandleMessage( uMsg, wParam, lParam );

[!else]
		return 0;

[!endif]
[!endif]
[!endif]
[!if TOOLBAR]
	case WM_NOTIFY:
		{	LPTOOLTIPTEXT pttt = windows_cast<LPTOOLTIPTEXT>( lParam );
			switch ( pttt->hdr.code ) {

			case TTN_GETDISPINFO:
				switch ( pttt->hdr.idFrom ) {

				case ID_FILE_NEW:
					strcpy( pttt->szText, "New File" );
					break;

				case ID_FILE_OPEN:
					strcpy( pttt->szText, "Open File" );
					break;

				case ID_FILE_SAVE:
					strcpy( pttt->szText, "Save File" );
					break;

				default:
					break;

				}
				break;
[!if REBAR]

			case RBN_HEIGHTCHANGE:
[!if MDI_APP]
				{	WRect rc = GetClientRect();
					rc.top += rebar.GetBarHeight();
					rc.bottom -= statusbar.GetClientRect().Height();
					GetClientWindow().Move( rc );
				}
[!endif]
				break;
[!endif]

			default:
				break;

			}
		}
		return 0;

[!endif]
[!if TOOLBAR || STATUSBAR]
	case WM_SIZE:
[!if TOOLBAR]
[!if REBAR]
		rebar.SendMessage( WM_SIZE, wParam, lParam );
[!else]
		toolbar.AutoSize();
[!endif]
[!endif]
[!if STATUSBAR]
		statusbar.SendMessage( WM_SIZE, wParam, lParam );
[!endif]
[!if MDI_APP]
		{	WRect rc = GetClientRect();
[!if TOOLBAR]
[!if REBAR]
			rc.top += rebar.GetBarHeight();
[!else]
			rc.top += toolbar.GetClientRect().Height();
[!endif]
[!endif]
[!if STATUSBAR]
			rc.bottom -= statusbar.GetClientRect().Height();
[!endif]
			GetClientWindow().Move( rc );
		}
[!endif]
		return 0;

[!endif]
[!if !MDI_APP]
[!if ON_NOTIFY && !TOOLBAR]
	case WM_NOTIFY:
		return 0;

[!endif]
[!if ON_PAINT]
	case WM_PAINT:
		{   PaintDC dc( *this );
			dc.TextOut( WPoint(50,50), "Hello, World!" );
		}
		return 0;

[!endif]
[!if ON_SIZE && !TOOLBAR && !STATUSBAR]
	case WM_SIZE:
		return 0;

[!endif]
[!if ON_MOUSE_MOVE]
	case WM_MOUSEMOVE:
		return 0;

[!endif]
[!if ON_KEY_UP_DOWN]
	case WM_KEYDOWN:
		return 0;

	case WM_KEYUP:
		return 0;

[!endif]
[!endif]
	default:
[!if SDI_APP]
		return Window::HandleMessage( uMsg, wParam, lParam );
[!endif]
[!if MDI_APP]
		return MDIFrameWindow::HandleMessage( uMsg, wParam, lParam );
[!endif]
[!if DIALOG_APP]
		return ModelessDialog::HandleMessage( uMsg, wParam, lParam );
[!endif]

	}
}
[!endif]
[!if !PURE_WRAPPER]
[!if DIALOG_APP && ON_CREATE]

bool MainWindow::OnInitDialog( HWND hwndFocus, LPARAM lParam )
{
	SetIcon( LoadIcon( __MODULE_HANDLE, MAKEINTRESOURCE(IDI_[!output UPPER_CASE_PROJECT_NAME]) ) );
	return true;
}
[!endif]
[!if !DIALOG_APP]
[!if ON_CREATE || MDI_APP || TOOLBAR || STATUSBAR]

bool MainWindow::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
[!if MDI_APP]
	CreateClient( GetClientRect(), GetMenu().GetSubMenu( 1 ) );
	CreateDocumentWindow();
[!endif]
[!if STATUSBAR]
	statusbar.Create( *this );
[!endif]
[!if TOOLBAR]
[!if REBAR]
	rebar.Create( *this );

	toolbar.Create( *this, -1, TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_WRAPABLE | CCS_NORESIZE | CCS_NOPARENTALIGN | CCS_NODIVIDER );
[!else]
	toolbar.Create( *this, -1, TBSTYLE_TOOLTIPS );

[!endif]
	toolbar.AddBitmap( 3, IDB_TOOLBAR );
	toolbar.AddButton( 0, ID_FILE_NEW );
	toolbar.AddButton( 1, ID_FILE_OPEN );
	toolbar.AddButton( 2, ID_FILE_SAVE );
[!endif]
[!if REBAR]
	rebar.InsertBand( toolbar, toolbar.GetMaxSize(), "Toolbar" );

	combo.Create( WRect(0,0,200,0), *this, -1 );
	combo.SetFont( StockObject( DEFAULT_GUI_FONT ) );
	combo.AddString( "aaa" );
	combo.AddString( "bbb" );
	rebar.InsertBand( combo, "ComboBox" );

[!endif]
	return true;
}
[!endif]
[!endif]

void MainWindow::OnDestroy()
{
	PostQuitMessage( 0 );
}
[!if !MDI_APP || MENU || TOOLBAR]
[!if ON_COMMAND || MENU || TOOLBAR]

void MainWindow::OnCommand( int nIdentifier, int nNotifyCode, HWND hwndControl )
{
	switch ( nIdentifier ) {
[!if DIALOG_APP]

	case IDOK:
	case IDCANCEL:
		Destroy();
		break;
[!endif]
[!if MENU || TOOLBAR]

	case ID_FILE_NEW:
[!if MDI_APP]
		CreateDocumentWindow();
[!endif]
		break;

	case ID_FILE_OPEN:
		{	GetFileNameDialog dlg( *this );
			if ( dlg.GoOpen() )
				MessageBox( dlg.GetPathName(), "Opening file..." );
		}
		break;

	case ID_FILE_SAVE:
		{	GetFileNameDialog dlg( *this );
			if ( dlg.GoSave() )
				MessageBox( dlg.GetPathName(), "Saving file..." );
		}
		break;
[!endif]
[!if MENU]

	case ID_FILE_SAVEAS:
		{	GetFileNameDialog dlg( *this );
			if ( dlg.GoSave() )
				MessageBox( dlg.GetPathName(), "Saving file..." );
		}
		break;

	case ID_FILE_EXIT:
		SendMessage( WM_CLOSE );
		break;
[!if MDI_APP]

	case ID_WINDOW_TILE:
		MDITile();
		break;

	case ID_WINDOW_CASCADE:
		MDICascade();
		break;
[!endif]

	case ID_HELP_ABOUT:
		MessageBox( "This is an AppWizard-generated application skeleton\nApplication name: [!output PROJECT_NAME]", "About", MB_ICONASTERISK );
		break;
[!endif]
[!if !MENU && !DIALOG_APP && !TOOLBAR]

	case 30: // Replace this with your commands
[!endif]

	default:
[!if MDI_APP]
		MDIFrameWindow::OnCommand( nIdentifier, nNotifyCode, hwndControl );
[!endif]
		break;

	}
}
[!endif]
[!endif]
[!if TOOLBAR]

int MainWindow::OnNotify( int nIdentifier, LPNMHDR pnmh )
{
	switch ( pnmh->code ) {

	case TTN_GETDISPINFO:
		{	LPTOOLTIPTEXT pttt = reinterpret_cast<LPTOOLTIPTEXT>( pnmh );
			switch ( pnmh->idFrom ) {

			case ID_FILE_NEW:
				strcpy( pttt->szText, "New File" );
				break;

			case ID_FILE_OPEN:
				strcpy( pttt->szText, "Open File" );
				break;

			case ID_FILE_SAVE:
				strcpy( pttt->szText, "Save File" );
				break;

			default:
				break;

			}
		}
		break;
[!if REBAR]

	case RBN_HEIGHTCHANGE:
[!if MDI_APP]
		{	WRect rc = GetClientRect();
			rc.top += rebar.GetBarHeight();
			rc.bottom -= statusbar.GetClientRect().Height();
			GetClientWindow().Move( rc );
		}
[!endif]
		break;
[!endif]

	default:
		break;

	}
	return 0;
}
[!endif]
[!if TOOLBAR || STATUSBAR]

void MainWindow::OnSize( int sizing, WSize new_size )
{
[!if TOOLBAR]
[!if REBAR]
	rebar.SendMessage( WM_SIZE, sizing, MAKELPARAM(new_size.cx,new_size.cy) );
[!else]
	toolbar.AutoSize();
[!endif]
[!endif]
[!if STATUSBAR]
	statusbar.SendMessage( WM_SIZE, sizing, MAKELPARAM(new_size.cx,new_size.cy) );
[!endif]
[!if MDI_APP]
	WRect rc = GetClientRect();
[!if TOOLBAR]
[!if REBAR]
	rc.top += rebar.GetBarHeight();
[!else]
	rc.top += toolbar.GetClientRect().Height();
[!endif]
[!endif]
[!if STATUSBAR]
	rc.bottom -= statusbar.GetClientRect().Height();
[!endif]
	GetClientWindow().Move( rc );
[!endif]
}
[!endif]
[!endif]
[!if !PURE_WRAPPER && !MDI_APP]
[!if ON_NOTIFY && !TOOLBAR]

int MainWindow::OnNotify( int nIdentifier, LPNMHDR pnmh )
{
	return 0;
}
[!endif]
[!if ON_PAINT]

void MainWindow::OnPaint()
{
	PaintDC dc( *this );
	dc.TextOut( WPoint(50,50), "Hello, World!" );
}
[!endif]
[!if ON_SIZE && !TOOLBAR && !STATUSBAR]

void MainWindow::OnSize( int sizing, WSize new_size )
{
}
[!endif]
[!if ON_MOUSE_MOVE]

void MainWindow::OnMouseMove( WPoint point, int keys )
{
}
[!endif]
[!if ON_MOUSE_DOWN]

void MainWindow::OnMouseDown( WPoint point, int keys, int button )
{
}
[!endif]
[!if ON_MOUSE_UP]

void MainWindow::OnMouseUp( WPoint point, int keys, int button )
{
}
[!endif]
[!if ON_MOUSE_DBL_CLK]

void MainWindow::OnMouseDblClk( WPoint point, int keys, int button )
{
}
[!endif]
[!if ON_KEY_UP_DOWN]

void MainWindow::OnKeyDown( int key, int keyData )
{
}

void MainWindow::OnKeyUp( int key, int keyData )
{
}
[!endif]
[!endif]
[!if MDI_APP]

bool MainWindow::CreateDocumentWindow()
{
	DocumentWindow* pDocWnd = new DocumentWindow( GetClientWindow() );
	if ( ! pDocWnd->IsCreated() ) {
		Window::Delete( pDocWnd );
		return false;
	}
	pDocWnd->Show();
	return true;
}
[!endif]
