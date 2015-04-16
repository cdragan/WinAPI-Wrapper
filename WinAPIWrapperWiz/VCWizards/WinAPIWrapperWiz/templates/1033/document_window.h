
#pragma once

class DocumentWindow: public WinAPI::MDIChildWindow {
public:
	DocumentWindow( HWND hwndClient ) {
		Create( "Document Window", hwndClient );
	}
protected:
[!if PURE_WRAPPER || ON_GENERIC]
	virtual int HandleMessage( int uMsg, int wParam, int lParam );
[!endif]
[!if !PURE_WRAPPER]
[!if ON_CREATE]
	virtual bool OnCreate( LPCREATESTRUCT lpCreateStruct = 0 );
[!endif]
[!if ON_COMMAND]
	virtual void OnCommand( int nIdentifier, int nNotifyCode, HWND hwndControl );
[!endif]
[!if ON_NOTIFY]
	virtual int OnNotify( int nIdentifier, LPNMHDR pnmh );
[!endif]
[!if ON_PAINT]
	virtual void OnPaint();
[!endif]
[!if ON_SIZE]
	virtual void OnSize( int sizing, WinAPI::WSize new_size );
[!endif]
[!if ON_MOUSE_MOVE]
	virtual void OnMouseMove( WinAPI::WPoint point, int keys );
[!endif]
[!if ON_MOUSE_DOWN]
	virtual void OnMouseDown( WinAPI::WPoint point, int keys, int button );
[!endif]
[!if ON_MOUSE_UP]
	virtual void OnMouseUp( WinAPI::WPoint point, int keys, int button );
[!endif]
[!if ON_MOUSE_DBL_CLK]
	virtual void OnMouseDblClk( WinAPI::WPoint point, int keys, int button );
[!endif]
[!if ON_KEY_UP_DOWN]
	virtual void OnKeyDown( int key, int keyData );
	virtual void OnKeyUp( int key, int keyData );
[!endif]
[!endif]
};
