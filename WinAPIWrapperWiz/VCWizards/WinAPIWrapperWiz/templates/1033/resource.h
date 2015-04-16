//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by [!output PROJECT_NAME].rc
//

#define IDI_[!output UPPER_CASE_PROJECT_NAME]           101
[!if DIALOG_APP]
#define IDD_[!output UPPER_CASE_PROJECT_NAME]	    102
[!endif]
[!if ACCELERATORS]
#define IDR_[!output UPPER_CASE_PROJECT_NAME]		103
[!endif]
[!if MENU]
#define IDR_MAINMENU			104
[!endif]
[!if MENU || TOOLBAR]
#define ID_FILE_NEW				105
#define ID_FILE_OPEN            106
#define ID_FILE_SAVE            107
[!endif]
[!if MENU]
#define ID_FILE_SAVEAS          108
#define ID_FILE_EXIT            109
#define ID_HELP_ABOUT           110
#define ID_WINDOW_TILE			111
#define ID_WINDOW_CASCADE		112
[!endif]
[!if TOOLBAR]
#define IDB_TOOLBAR				113
[!endif]
#define IDC_STATIC				-1
// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	114
#define _APS_NEXT_COMMAND_VALUE		40001
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		101
#endif
#endif
