#include "Win32MessageMap.h"
#include <cstdio> // For sprintf_s

// Initialize the static map member.
// This calls CreateMessageMap() once during program startup.
std::map<UINT, const wchar_t*> Win32MessageMap::s_messageMap = Win32MessageMap::CreateMessageMap();

// Implementation of the map creation helper function.
// This is where all the WM_ messages are mapped to their strings.
std::map<UINT, const wchar_t*> Win32MessageMap::CreateMessageMap() {
    std::map<UINT, const wchar_t*> map;

    // --- START GENERATED FROM PROVIDED WINUSER.H SNIPPET ---
    // Window Messages
    map[WM_NULL] = L"WM_NULL";
    map[WM_CREATE] = L"WM_CREATE";
    map[WM_DESTROY] = L"WM_DESTROY";
    map[WM_MOVE] = L"WM_MOVE";
    map[WM_SIZE] = L"WM_SIZE";

    map[WM_ACTIVATE] = L"WM_ACTIVATE";
    map[WM_SETFOCUS] = L"WM_SETFOCUS";
    map[WM_KILLFOCUS] = L"WM_KILLFOCUS";
    map[WM_ENABLE] = L"WM_ENABLE";
    map[WM_SETREDRAW] = L"WM_SETREDRAW";
    map[WM_SETTEXT] = L"WM_SETTEXT";
    map[WM_GETTEXT] = L"WM_GETTEXT";
    map[WM_GETTEXTLENGTH] = L"WM_GETTEXTLENGTH";
    map[WM_PAINT] = L"WM_PAINT";
    map[WM_CLOSE] = L"WM_CLOSE";
    map[WM_QUERYENDSESSION] = L"WM_QUERYENDSESSION"; // Conditional in original, but resolved by compiler
    map[WM_QUERYOPEN] = L"WM_QUERYOPEN";             // Conditional in original, but resolved by compiler
    map[WM_ENDSESSION] = L"WM_ENDSESSION";           // Conditional in original, but resolved by compiler
    map[WM_QUIT] = L"WM_QUIT";
    map[WM_ERASEBKGND] = L"WM_ERASEBKGND";
    map[WM_SYSCOLORCHANGE] = L"WM_SYSCOLORCHANGE";
    map[WM_SHOWWINDOW] = L"WM_SHOWWINDOW";
    map[WM_WININICHANGE] = L"WM_WININICHANGE";
    map[WM_SETTINGCHANGE] = L"WM_SETTINGCHANGE";     // Defined as WM_WININICHANGE

    map[WM_DEVMODECHANGE] = L"WM_DEVMODECHANGE";
    map[WM_ACTIVATEAPP] = L"WM_ACTIVATEAPP";
    map[WM_FONTCHANGE] = L"WM_FONTCHANGE";
    map[WM_TIMECHANGE] = L"WM_TIMECHANGE";
    map[WM_CANCELMODE] = L"WM_CANCELMODE";
    map[WM_SETCURSOR] = L"WM_SETCURSOR";
    map[WM_MOUSEACTIVATE] = L"WM_MOUSEACTIVATE";
    map[WM_CHILDACTIVATE] = L"WM_CHILDACTIVATE";
    map[WM_QUEUESYNC] = L"WM_QUEUESYNC";

    map[WM_GETMINMAXINFO] = L"WM_GETMINMAXINFO";

    map[WM_PAINTICON] = L"WM_PAINTICON";
    map[WM_ICONERASEBKGND] = L"WM_ICONERASEBKGND";
    map[WM_NEXTDLGCTL] = L"WM_NEXTDLGCTL";
    map[WM_SPOOLERSTATUS] = L"WM_SPOOLERSTATUS";
    map[WM_DRAWITEM] = L"WM_DRAWITEM";
    map[WM_MEASUREITEM] = L"WM_MEASUREITEM";
    map[WM_DELETEITEM] = L"WM_DELETEITEM";
    map[WM_VKEYTOITEM] = L"WM_VKEYTOITEM";
    map[WM_CHARTOITEM] = L"WM_CHARTOITEM";
    map[WM_SETFONT] = L"WM_SETFONT";
    map[WM_GETFONT] = L"WM_GETFONT";
    map[WM_SETHOTKEY] = L"WM_SETHOTKEY";
    map[WM_GETHOTKEY] = L"WM_GETHOTKEY";
    map[WM_QUERYDRAGICON] = L"WM_QUERYDRAGICON";
    map[WM_COMPAREITEM] = L"WM_COMPAREITEM";
    map[WM_GETOBJECT] = L"WM_GETOBJECT";             // Conditional in original, but resolved by compiler
    map[WM_COMPACTING] = L"WM_COMPACTING";
    map[WM_COMMNOTIFY] = L"WM_COMMNOTIFY";
    map[WM_WINDOWPOSCHANGING] = L"WM_WINDOWPOSCHANGING";
    map[WM_WINDOWPOSCHANGED] = L"WM_WINDOWPOSCHANGED";

    map[WM_POWER] = L"WM_POWER";
    map[WM_COPYDATA] = L"WM_COPYDATA";
    map[WM_CANCELJOURNAL] = L"WM_CANCELJOURNAL";

    map[WM_NOTIFY] = L"WM_NOTIFY";                   // Conditional in original, but resolved by compiler
    map[WM_INPUTLANGCHANGEREQUEST] = L"WM_INPUTLANGCHANGEREQUEST";
    map[WM_INPUTLANGCHANGE] = L"WM_INPUTLANGCHANGE";
    map[WM_TCARD] = L"WM_TCARD";
    map[WM_HELP] = L"WM_HELP";
    map[WM_USERCHANGED] = L"WM_USERCHANGED";
    map[WM_NOTIFYFORMAT] = L"WM_NOTIFYFORMAT";

    map[WM_CONTEXTMENU] = L"WM_CONTEXTMENU";
    map[WM_STYLECHANGING] = L"WM_STYLECHANGING";
    map[WM_STYLECHANGED] = L"WM_STYLECHANGED";
    map[WM_DISPLAYCHANGE] = L"WM_DISPLAYCHANGE";
    map[WM_GETICON] = L"WM_GETICON";
    map[WM_SETICON] = L"WM_SETICON";

    map[WM_NCCREATE] = L"WM_NCCREATE";
    map[WM_NCDESTROY] = L"WM_NCDESTROY";
    map[WM_NCCALCSIZE] = L"WM_NCCALCSIZE";
    map[WM_NCHITTEST] = L"WM_NCHITTEST";
    map[WM_NCPAINT] = L"WM_NCPAINT";
    map[WM_NCACTIVATE] = L"WM_NCACTIVATE";
    map[WM_GETDLGCODE] = L"WM_GETDLGCODE";
    map[WM_SYNCPAINT] = L"WM_SYNCPAINT";             // Conditional in original, but resolved by compiler
    map[WM_NCMOUSEMOVE] = L"WM_NCMOUSEMOVE";
    map[WM_NCLBUTTONDOWN] = L"WM_NCLBUTTONDOWN";
    map[WM_NCLBUTTONUP] = L"WM_NCLBUTTONUP";
    map[WM_NCLBUTTONDBLCLK] = L"WM_NCLBUTTONDBLCLK";
    map[WM_NCRBUTTONDOWN] = L"WM_NCRBUTTONDOWN";
    map[WM_NCRBUTTONUP] = L"WM_NCRBUTTONUP";
    map[WM_NCRBUTTONDBLCLK] = L"WM_NCRBUTTONDBLCLK";
    map[WM_NCMBUTTONDOWN] = L"WM_NCMBUTTONDOWN";
    map[WM_NCMBUTTONUP] = L"WM_NCMBUTTONUP";
    map[WM_NCMBUTTONDBLCLK] = L"WM_NCMBUTTONDBLCLK";

    map[WM_NCXBUTTONDOWN] = L"WM_NCXBUTTONDOWN";     // Conditional in original, but resolved by compiler
    map[WM_NCXBUTTONUP] = L"WM_NCXBUTTONUP";         // Conditional in original, but resolved by compiler
    map[WM_NCXBUTTONDBLCLK] = L"WM_NCXBUTTONDBLCLK"; // Conditional in original, but resolved by compiler

    map[WM_INPUT_DEVICE_CHANGE] = L"WM_INPUT_DEVICE_CHANGE"; // Conditional in original, but resolved by compiler
    map[WM_INPUT] = L"WM_INPUT";                     // Conditional in original, but resolved by compiler

    map[WM_KEYFIRST] = L"WM_KEYFIRST";
    map[WM_KEYDOWN] = L"WM_KEYDOWN";
    map[WM_KEYUP] = L"WM_KEYUP";
    map[WM_CHAR] = L"WM_CHAR";
    map[WM_DEADCHAR] = L"WM_DEADCHAR";
    map[WM_SYSKEYDOWN] = L"WM_SYSKEYDOWN";
    map[WM_SYSKEYUP] = L"WM_SYSKEYUP";
    map[WM_SYSCHAR] = L"WM_SYSCHAR";
    map[WM_SYSDEADCHAR] = L"WM_SYSDEADCHAR";
    map[WM_UNICHAR] = L"WM_UNICHAR";                 // Conditional in original, but resolved by compiler
    map[WM_KEYLAST] = L"WM_KEYLAST";                 // Conditional in original, but resolved by compiler

    map[WM_IME_STARTCOMPOSITION] = L"WM_IME_STARTCOMPOSITION"; // Conditional in original, but resolved by compiler
    map[WM_IME_ENDCOMPOSITION] = L"WM_IME_ENDCOMPOSITION";     // Conditional in original, but resolved by compiler
    map[WM_IME_COMPOSITION] = L"WM_IME_COMPOSITION";           // Conditional in original, but resolved by compiler
    map[WM_IME_KEYLAST] = L"WM_IME_KEYLAST";                   // Conditional in original, but resolved by compiler

    map[WM_INITDIALOG] = L"WM_INITDIALOG";
    map[WM_COMMAND] = L"WM_COMMAND";
    map[WM_SYSCOMMAND] = L"WM_SYSCOMMAND";
    map[WM_TIMER] = L"WM_TIMER";
    map[WM_HSCROLL] = L"WM_HSCROLL";
    map[WM_VSCROLL] = L"WM_VSCROLL";
    map[WM_INITMENU] = L"WM_INITMENU";
    map[WM_INITMENUPOPUP] = L"WM_INITMENUPOPUP";
    map[WM_GESTURE] = L"WM_GESTURE";                 // Conditional in original, but resolved by compiler
    map[WM_GESTURENOTIFY] = L"WM_GESTURENOTIFY";     // Conditional in original, but resolved by compiler
    map[WM_MENUSELECT] = L"WM_MENUSELECT";
    map[WM_MENUCHAR] = L"WM_MENUCHAR";
    map[WM_ENTERIDLE] = L"WM_ENTERIDLE";
    map[WM_MENURBUTTONUP] = L"WM_MENURBUTTONUP";     // Conditional in original, but resolved by compiler
    map[WM_MENUDRAG] = L"WM_MENUDRAG";               // Conditional in original, but resolved by compiler
    map[WM_MENUGETOBJECT] = L"WM_MENUGETOBJECT";     // Conditional in original, but resolved by compiler
    map[WM_UNINITMENUPOPUP] = L"WM_UNINITMENUPOPUP"; // Conditional in original, but resolved by compiler
    map[WM_MENUCOMMAND] = L"WM_MENUCOMMAND";         // Conditional in original, but resolved by compiler

    map[WM_CHANGEUISTATE] = L"WM_CHANGEUISTATE";     // Conditional in original, but resolved by compiler
    map[WM_UPDATEUISTATE] = L"WM_UPDATEUISTATE";     // Conditional in original, but resolved by compiler
    map[WM_QUERYUISTATE] = L"WM_QUERYUISTATE";       // Conditional in original, but resolved by compiler

    map[WM_CTLCOLORMSGBOX] = L"WM_CTLCOLORMSGBOX";
    map[WM_CTLCOLOREDIT] = L"WM_CTLCOLOREDIT";
    map[WM_CTLCOLORLISTBOX] = L"WM_CTLCOLORLISTBOX";
    map[WM_CTLCOLORBTN] = L"WM_CTLCOLORBTN";
    map[WM_CTLCOLORDLG] = L"WM_CTLCOLORDLG";
    map[WM_CTLCOLORSCROLLBAR] = L"WM_CTLCOLORSCROLLBAR";
    map[WM_CTLCOLORSTATIC] = L"WM_CTLCOLORSTATIC";
    map[MN_GETHMENU] = L"MN_GETHMENU"; // This is not a WM_ message, but included in the snippet. Keeping it for completeness based on your provided list.

    map[WM_MOUSEFIRST] = L"WM_MOUSEFIRST";
    map[WM_MOUSEMOVE] = L"WM_MOUSEMOVE";
    map[WM_LBUTTONDOWN] = L"WM_LBUTTONDOWN";
    map[WM_LBUTTONUP] = L"WM_LBUTTONUP";
    map[WM_LBUTTONDBLCLK] = L"WM_LBUTTONDBLCLK";
    map[WM_RBUTTONDOWN] = L"WM_RBUTTONDOWN";
    map[WM_RBUTTONUP] = L"WM_RBUTTONUP";
    map[WM_RBUTTONDBLCLK] = L"WM_RBUTTONDBLCLK";
    map[WM_MBUTTONDOWN] = L"WM_MBUTTONDOWN";
    map[WM_MBUTTONUP] = L"WM_MBUTTONUP";
    map[WM_MBUTTONDBLCLK] = L"WM_MBUTTONDBLCLK";
    map[WM_MOUSEWHEEL] = L"WM_MOUSEWHEEL";           // Conditional in original, but resolved by compiler
    map[WM_XBUTTONDOWN] = L"WM_XBUTTONDOWN";         // Conditional in original, but resolved by compiler
    map[WM_XBUTTONUP] = L"WM_XBUTTONUP";             // Conditional in original, but resolved by compiler
    map[WM_XBUTTONDBLCLK] = L"WM_XBUTTONDBLCLK";     // Conditional in original, but resolved by compiler
    map[WM_MOUSEHWHEEL] = L"WM_MOUSEHWHEEL";         // Conditional in original, but resolved by compiler

    map[WM_MOUSELAST] = L"WM_MOUSELAST";             // Conditional in original, but resolved by compiler

    map[WM_PARENTNOTIFY] = L"WM_PARENTNOTIFY";
    map[WM_ENTERMENULOOP] = L"WM_ENTERMENULOOP";
    map[WM_EXITMENULOOP] = L"WM_EXITMENULOOP";

    map[WM_NEXTMENU] = L"WM_NEXTMENU";               // Conditional in original, but resolved by compiler
    map[WM_SIZING] = L"WM_SIZING";                   // Conditional in original, but resolved by compiler
    map[WM_CAPTURECHANGED] = L"WM_CAPTURECHANGED";   // Conditional in original, but resolved by compiler
    map[WM_MOVING] = L"WM_MOVING";                   // Conditional in original, but resolved by compiler

    map[WM_POWERBROADCAST] = L"WM_POWERBROADCAST";   // Conditional in original, but resolved by compiler

    map[WM_DEVICECHANGE] = L"WM_DEVICECHANGE";       // Conditional in original, but resolved by compiler

    map[WM_MDICREATE] = L"WM_MDICREATE";
    map[WM_MDIDESTROY] = L"WM_MDIDESTROY";
    map[WM_MDIACTIVATE] = L"WM_MDIACTIVATE";
    map[WM_MDIRESTORE] = L"WM_MDIRESTORE";
    map[WM_MDINEXT] = L"WM_MDINEXT";
    map[WM_MDIMAXIMIZE] = L"WM_MDIMAXIMIZE";
    map[WM_MDITILE] = L"WM_MDITILE";
    map[WM_MDICASCADE] = L"WM_MDICASCADE";
    map[WM_MDIICONARRANGE] = L"WM_MDIICONARRANGE";
    map[WM_MDIGETACTIVE] = L"WM_MDIGETACTIVE";

    map[WM_MDISETMENU] = L"WM_MDISETMENU";
    map[WM_ENTERSIZEMOVE] = L"WM_ENTERSIZEMOVE";
    map[WM_EXITSIZEMOVE] = L"WM_EXITSIZEMOVE";
    map[WM_DROPFILES] = L"WM_DROPFILES";
    map[WM_MDIREFRESHMENU] = L"WM_MDIREFRESHMENU";

    map[WM_POINTERDEVICECHANGE] = L"WM_POINTERDEVICECHANGE"; // Conditional in original, but resolved by compiler
    map[WM_POINTERDEVICEINRANGE] = L"WM_POINTERDEVICEINRANGE"; // Conditional in original, but resolved by compiler
    map[WM_POINTERDEVICEOUTOFRANGE] = L"WM_POINTERDEVICEOUTOFRANGE"; // Conditional in original, but resolved by compiler

    map[WM_TOUCH] = L"WM_TOUCH";                     // Conditional in original, but resolved by compiler

    map[WM_NCPOINTERUPDATE] = L"WM_NCPOINTERUPDATE"; // Conditional in original, but resolved by compiler
    map[WM_NCPOINTERDOWN] = L"WM_NCPOINTERDOWN";     // Conditional in original, but resolved by compiler
    map[WM_NCPOINTERUP] = L"WM_NCPOINTERUP";         // Conditional in original, but resolved by compiler
    map[WM_POINTERUPDATE] = L"WM_POINTERUPDATE";     // Conditional in original, but resolved by compiler
    map[WM_POINTERDOWN] = L"WM_POINTERDOWN";         // Conditional in original, but resolved by compiler
    map[WM_POINTERUP] = L"WM_POINTERUP";             // Conditional in original, but resolved by compiler
    map[WM_POINTERENTER] = L"WM_POINTERENTER";       // Conditional in original, but resolved by compiler
    map[WM_POINTERLEAVE] = L"WM_POINTERLEAVE";       // Conditional in original, but resolved by compiler
    map[WM_POINTERACTIVATE] = L"WM_POINTERACTIVATE"; // Conditional in original, but resolved by compiler
    map[WM_POINTERCAPTURECHANGED] = L"WM_POINTERCAPTURECHANGED"; // Conditional in original, but resolved by compiler
    map[WM_TOUCHHITTESTING] = L"WM_TOUCHHITTESTING"; // Conditional in original, but resolved by compiler
    map[WM_POINTERWHEEL] = L"WM_POINTERWHEEL";       // Conditional in original, but resolved by compiler
    map[WM_POINTERHWHEEL] = L"WM_POINTERHWHEEL";     // Conditional in original, but resolved by compiler
    map[DM_POINTERHITTEST] = L"DM_POINTERHITTEST"; // Not WM_ but in message range. Keeping per snippet.
    map[WM_POINTERROUTEDTO] = L"WM_POINTERROUTEDTO"; // Conditional in original, but resolved by compiler
    map[WM_POINTERROUTEDAWAY] = L"WM_POINTERROUTEDAWAY"; // Conditional in original, but resolved by compiler
    map[WM_POINTERROUTEDRELEASED] = L"WM_POINTERROUTEDRELEASED"; // Conditional in original, but resolved by compiler

    map[WM_IME_SETCONTEXT] = L"WM_IME_SETCONTEXT";   // Conditional in original, but resolved by compiler
    map[WM_IME_NOTIFY] = L"WM_IME_NOTIFY";           // Conditional in original, but resolved by compiler
    map[WM_IME_CONTROL] = L"WM_IME_CONTROL";         // Conditional in original, but resolved by compiler
    map[WM_IME_COMPOSITIONFULL] = L"WM_IME_COMPOSITIONFULL"; // Conditional in original, but resolved by compiler
    map[WM_IME_SELECT] = L"WM_IME_SELECT";           // Conditional in original, but resolved by compiler
    map[WM_IME_CHAR] = L"WM_IME_CHAR";               // Conditional in original, but resolved by compiler
    map[WM_IME_REQUEST] = L"WM_IME_REQUEST";         // Conditional in original, but resolved by compiler
    map[WM_IME_KEYDOWN] = L"WM_IME_KEYDOWN";         // Conditional in original, but resolved by compiler
    map[WM_IME_KEYUP] = L"WM_IME_KEYUP";             // Conditional in original, but resolved by compiler

    map[WM_MOUSEHOVER] = L"WM_MOUSEHOVER";           // Conditional in original, but resolved by compiler
    map[WM_MOUSELEAVE] = L"WM_MOUSELEAVE";           // Conditional in original, but resolved by compiler
    map[WM_NCMOUSEHOVER] = L"WM_NCMOUSEHOVER";       // Conditional in original, but resolved by compiler
    map[WM_NCMOUSELEAVE] = L"WM_NCMOUSELEAVE";       // Conditional in original, but resolved by compiler

    map[WM_WTSSESSION_CHANGE] = L"WM_WTSSESSION_CHANGE"; // Conditional in original, but resolved by compiler

    map[WM_TABLET_FIRST] = L"WM_TABLET_FIRST";       // Conditional in original, but resolved by compiler
    map[WM_TABLET_LAST] = L"WM_TABLET_LAST";         // Conditional in original, but resolved by compiler

    map[WM_DPICHANGED] = L"WM_DPICHANGED";           // Conditional in original, but resolved by compiler
    map[WM_DPICHANGED_BEFOREPARENT] = L"WM_DPICHANGED_BEFOREPARENT"; // Conditional in original, but resolved by compiler
    map[WM_DPICHANGED_AFTERPARENT] = L"WM_DPICHANGED_AFTERPARENT"; // Conditional in original, but resolved by compiler
    map[WM_GETDPISCALEDSIZE] = L"WM_GETDPISCALEDSIZE"; // Conditional in original, but resolved by compiler

    map[WM_CUT] = L"WM_CUT";
    map[WM_COPY] = L"WM_COPY";
    map[WM_PASTE] = L"WM_PASTE";
    map[WM_CLEAR] = L"WM_CLEAR";
    map[WM_UNDO] = L"WM_UNDO";
    map[WM_RENDERFORMAT] = L"WM_RENDERFORMAT";
    map[WM_RENDERALLFORMATS] = L"WM_RENDERALLFORMATS";
    map[WM_DESTROYCLIPBOARD] = L"WM_DESTROYCLIPBOARD";
    map[WM_DRAWCLIPBOARD] = L"WM_DRAWCLIPBOARD";
    map[WM_PAINTCLIPBOARD] = L"WM_PAINTCLIPBOARD";
    map[WM_VSCROLLCLIPBOARD] = L"WM_VSCROLLCLIPBOARD";
    map[WM_SIZECLIPBOARD] = L"WM_SIZECLIPBOARD";
    map[WM_ASKCBFORMATNAME] = L"WM_ASKCBFORMATNAME";
    map[WM_CHANGECBCHAIN] = L"WM_CHANGECBCHAIN";
    map[WM_HSCROLLCLIPBOARD] = L"WM_HSCROLLCLIPBOARD";
    map[WM_QUERYNEWPALETTE] = L"WM_QUERYNEWPALETTE";
    map[WM_PALETTEISCHANGING] = L"WM_PALETTEISCHANGING";
    map[WM_PALETTECHANGED] = L"WM_PALETTECHANGED";
    map[WM_HOTKEY] = L"WM_HOTKEY";

    map[WM_PRINT] = L"WM_PRINT";                     // Conditional in original, but resolved by compiler
    map[WM_PRINTCLIENT] = L"WM_PRINTCLIENT";         // Conditional in original, but resolved by compiler

    map[WM_APPCOMMAND] = L"WM_APPCOMMAND";           // Conditional in original, but resolved by compiler

    map[WM_THEMECHANGED] = L"WM_THEMECHANGED";       // Conditional in original, but resolved by compiler

    map[WM_CLIPBOARDUPDATE] = L"WM_CLIPBOARDUPDATE"; // Conditional in original, but resolved by compiler

    map[WM_DWMCOMPOSITIONCHANGED] = L"WM_DWMCOMPOSITIONCHANGED"; // Conditional in original, but resolved by compiler
    map[WM_DWMNCRENDERINGCHANGED] = L"WM_DWMNCRENDERINGCHANGED"; // Conditional in original, but resolved by compiler
    map[WM_DWMCOLORIZATIONCOLORCHANGED] = L"WM_DWMCOLORIZATIONCOLORCHANGED"; // Conditional in original, but resolved by compiler
    map[WM_DWMWINDOWMAXIMIZEDCHANGE] = L"WM_DWMWINDOWMAXIMIZEDCHANGE"; // Conditional in original, but resolved by compiler

    map[WM_DWMSENDICONICTHUMBNAIL] = L"WM_DWMSENDICONICTHUMBNAIL"; // Conditional in original, but resolved by compiler
    map[WM_DWMSENDICONICLIVEPREVIEWBITMAP] = L"WM_DWMSENDICONICLIVEPREVIEWBITMAP"; // Conditional in original, but resolved by compiler

    map[WM_GETTITLEBARINFOEX] = L"WM_GETTITLEBARINFOEX"; // Conditional in original, but resolved by compiler

    map[WM_HANDHELDFIRST] = L"WM_HANDHELDFIRST";     // Conditional in original, but resolved by compiler
    map[WM_HANDHELDLAST] = L"WM_HANDHELDLAST";       // Conditional in original, but resolved by compiler

    map[WM_AFXFIRST] = L"WM_AFXFIRST";               // Conditional in original, but resolved by compiler
    map[WM_AFXLAST] = L"WM_AFXLAST";                 // Conditional in original, but resolved by compiler

    map[WM_PENWINFIRST] = L"WM_PENWINFIRST";
    map[WM_PENWINLAST] = L"WM_PENWINLAST";

    map[WM_APP] = L"WM_APP";                         // Conditional in original, but resolved by compiler

    // Private Window Messages Start Here:
    map[WM_USER] = L"WM_USER";

    // --- END GENERATED FROM PROVIDED WINUSER.H SNIPPET ---

    return map;
}

const wchar_t* Win32MessageMap::GetMessageName(UINT message) {
    auto it = s_messageMap.find(message);
    if (it != s_messageMap.end()) {
        return it->second;
    }

    // Handle WM_USER and above (application-defined messages)
    if (message >= WM_USER) {
        // WARNING: Using a static buffer here makes the function NOT thread-safe.
        // If multiple threads call this concurrently, the buffer contents
        // might be overwritten before previous callers can use them.
        static wchar_t customMsgBuffer[64];
        wsprintfW(customMsgBuffer, L"WM_USER + %u", message - WM_USER);
        return customMsgBuffer;
    }

    // Handle unknown messages (e.g., those from RegisterWindowMessage() or system internal)
    // WARNING: Same thread-safety considerations as above.
    static wchar_t unknownMsgBuffer[64];
    wsprintfW(unknownMsgBuffer, L"Unknown (0x%04X)", message);
    return unknownMsgBuffer;
}