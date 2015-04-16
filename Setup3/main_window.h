
#pragma once

#include "resource.h"

class MainWindow: public WinAPI::ModelessDialog, public WinAPI::Thread {
public:
	MainWindow();
protected:
	virtual void OnDestroy();
	virtual void OnCommand( int nIdentifier, int nNotifyCode, HWND hwndControl );
	virtual void Run();
};
