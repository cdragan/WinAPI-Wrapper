
#include <windows.h>

void* operator new( size_t size )
{
	return GlobalAlloc( GMEM_FIXED, size );
}

void operator delete( void* ptr )
{
	GlobalFree( ptr );
}

int _purecall()
{
	return 0;
}

int atexit( void (__cdecl *func)() )
{
	return 0;
}

extern "C" {
	typedef int (__cdecl *PROCPTR)();

	extern PROCPTR __xi_a;
	extern PROCPTR __xi_z;

	extern PROCPTR __xc_a;
	extern PROCPTR __xc_z;

	extern PROCPTR __xp_a;
	extern PROCPTR __xp_z;

	extern PROCPTR __xt_a;
	extern PROCPTR __xt_z;
}

inline void doexit()
{
}

void CallPROCPTRChain( PROCPTR* a, PROCPTR* b )
{
	for ( ; a < b; a++ )
		if ( *a != 0 && (*a)() != 0 )
			doexit();
}

int WINAPI WinMainCRTStartup()
{
	CallPROCPTRChain( &__xi_a, &__xi_z );
	CallPROCPTRChain( &__xc_a, &__xc_z );
	const int retval = WinMain( 0, 0, 0, 0 );
	CallPROCPTRChain( &__xp_a, &__xp_z );
	CallPROCPTRChain( &__xt_a, &__xt_z );
	return retval;
}
