
#include "winapi.h"

#ifndef MINGW
#include <crtdbg.h>
#endif

using namespace WinAPI;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
#ifndef MINGW
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	ApplicationBase* p_application = ApplicationBase::p_application;
	if ( p_application != 0 )
		p_application->Run();
	return 0;
}
