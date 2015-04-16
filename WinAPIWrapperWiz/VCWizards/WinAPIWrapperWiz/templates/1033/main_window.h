
#pragma once

#include "resource.h"

[!if SDI_APP]
class MainWindow: public WinAPI::Window {
[!endif]
[!if MDI_APP]
class MainWindow: public WinAPI::MDIFrameWindow {
[!endif]
[!if DIALOG_APP]
class MainWindow: public WinAPI::ModelessDialog {
[!endif]
public:
	MainWindow();
[!if MDI_APP]
	bool CreateDocumentWindow();
[!endif]
protected:
[!if PURE_WRAPPER || ON_GENERIC]
[!if PURE_WRAPPER || !MDI_APP]
	virtual int HandleMessage( int uMsg, int wParam, int lParam );
[!endif]
[!endif]
[!if !PURE_WRAPPER && !MDI_APP]
	virtual void OnDestroy();
[!if ON_CREATE && DIALOG_APP]
	virtual bool OnInitDialog( HWND hwndFocus, LPARAM lParam );
[!endif]
[!if !DIALOG_APP]
[!if ON_CREATE || TOOLBAR || STATUSBAR]
	virtual bool OnCreate( LPCREATESTRUCT lpCreateStruct = 0 );
[!endif]
[!endif]
[!if ON_COMMAND || DIALOG_APP || MENU || TOOLBAR]
	virtual void OnCommand( int nIdentifier, int nNotifyCode, HWND hwndControl );
[!endif]
[!if ON_NOTIFY && !TOOLBAR]
	virtual int OnNotify( int nIdentifier, LPNMHDR pnmh );
[!endif]
[!if ON_PAINT]
	virtual void OnPaint();
[!endif]
[!if ON_SIZE && !TOOLBAR && !STATUSBAR]
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
[!if !PURE_WRAPPER && MDI_APP]
	virtual bool OnCreate( LPCREATESTRUCT lpCreateStruct = 0 );
	virtual void OnDestroy();
[!if MENU || TOOLBAR || STATUSBAR]
	virtual void OnCommand( int nIdentifier, int nNotifyCode, HWND hwndControl );
[!endif]
[!endif]
[!if TOOLBAR && !PURE_WRAPPER]
	virtual int OnNotify( int nIdentifier, LPNMHDR pnmh );
[!endif]
[!if !PURE_WRAPPER]
[!if TOOLBAR || STATUSBAR]
	virtual void OnSize( int sizing, WinAPI::WSize new_size );
[!endif]
[!endif]
[!if TOOLBAR || STATUSBAR]
private:
[!endif]
[!if REBAR]
	WinAPI::Rebar rebar;
	WinAPI::ComboBox combo;
[!endif]
[!if TOOLBAR]
	WinAPI::Toolbar toolbar;
[!endif]
[!if STATUSBAR]
	WinAPI::StatusBar statusbar;
[!endif]
};
