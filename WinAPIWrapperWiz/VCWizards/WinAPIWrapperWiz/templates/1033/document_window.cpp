
#include "StdAfx.h"
#include "document_window.h"

using namespace WinAPI;
[!if PURE_WRAPPER || ON_GENERIC]

int DocumentWindow::HandleMessage( int uMsg, int wParam, int lParam )
{
	switch ( uMsg ) {

[!if !PURE_WRAPPER]
	case WM_USER: // Replace this with your messages

[!endif]
[!if PURE_WRAPPER]
	case WM_CREATE:
		return 0;

[!if ON_COMMAND]
	case WM_COMMAND:
		return 0;

[!endif]
[!if ON_NOTIFY]
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
[!if ON_SIZE]
	case WM_SIZE:
		return MDIChildWindow::HandleMessage( uMsg, wParam, lParam );

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
		return MDIChildWindow::HandleMessage( uMsg, wParam, lParam );

	}
}
[!endif]
[!if !PURE_WRAPPER]
[!if ON_CREATE]

bool DocumentWindow::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	return true;
}
[!endif]
[!if ON_COMMAND]

void DocumentWindow::OnCommand( int nIdentifier, int nNotifyCode, HWND hwndControl )
{
	switch ( nIdentifier ) {

	case 50: // Replace this with your commands

	default:
		break;

	}
}
[!endif]
[!if ON_NOTIFY]

int DocumentWindow::OnNotify( int nIdentifier, LPNMHDR pnmh )
{
	return 0;
}
[!endif]
[!if ON_PAINT]

void DocumentWindow::OnPaint()
{
	PaintDC dc( *this );
	dc.TextOut( WPoint(50,50), "Hello, World!" );
}
[!endif]
[!if ON_SIZE]

void DocumentWindow::OnSize( int sizing, WSize new_size )
{
	// Required for the child window to maximize properly
	MDIChildWindow::OnSize( sizing, new_size );
}
[!endif]
[!if ON_MOUSE_MOVE]

void DocumentWindow::OnMouseMove( WPoint point, int keys )
{
}
[!endif]
[!if ON_MOUSE_DOWN]

void DocumentWindow::OnMouseDown( WPoint point, int keys, int button )
{
}
[!endif]
[!if ON_MOUSE_UP]

void DocumentWindow::OnMouseUp( WPoint point, int keys, int button )
{
}
[!endif]
[!if ON_MOUSE_DBL_CLK]

void DocumentWindow::OnMouseDblClk( WPoint point, int keys, int button )
{
}
[!endif]
[!if !DIALOG_APP]
[!if ON_KEY_UP_DOWN]

void DocumentWindow::OnKeyDown( int key, int keyData )
{
}

void DocumentWindow::OnKeyUp( int key, int keyData )
{
}
[!endif]
[!endif]
[!endif]
