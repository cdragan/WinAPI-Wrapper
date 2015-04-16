
// Resign from STL
#define SKIP_STL
// Resign from additional virtual methods in Window
#define PURE_WRAPPER
// Include main WinAPI Wrapper header
#include <winapi.h>

// Include the WinAPI Wrapper namespace
using namespace WinAPI;

// Define main window class based on a regular window class
class MainWindow: public Window {
public:
	// Constructor creates the actual window (through CreateWindowEx)
	MainWindow() {
		Create( "Sample App" );
	}
	// Handle all messages
	virtual int HandleMessage( int uMsg, int wParam, int lParam ) {
		switch ( uMsg ) {
			// Acknowledge window creation
			case WM_CREATE: return 1;
			// During window destruction the message queue is stopped
			case WM_DESTROY: PostQuitMessage( 0 ); return 0;
			// Call OnPaint() to serve WM_PAINT
			case WM_PAINT: OnPaint(); return 0;
			// Default message processing
			default: return Window::HandleMessage( uMsg, wParam, lParam );
		}
	}
	// Paint "Hello, World!" during WM_PAINT
	void OnPaint() {
		PaintDC( *this ).TextOut( WPoint(50,50), "Hello, World!", 13 );
	}
};

// The application object using the main window class
namespace {
	Application< MainWindow > app;
}
