#include <windows.h>
#include <vector>
#include <map>

#include "Win32MessageMap.h"

// Global map to store finger positions.
// Key: Pointer ID (UINT32), Value: Position (POINT)
std::map<UINT32, POINT> g_touchPoints;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"PointerSampleWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Win32 Pointer (Multi-Touch) Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    //register
    //RegisterPointerInputTarget(hwnd, PT_TOUCHPAD);
    EnableMouseInPointer(TRUE);
    RegisterTouchWindow(hwnd, TWF_FINETOUCH | TWF_WANTPALM);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // Extract the pointer ID from a pointer message
    UINT32 pointerId = GET_POINTERID_WPARAM(wParam);
    POINTER_INFO pointerInfo = {};

    wchar_t buf[64];
    wsprintfW(buf, L"Messaged Received: %s\n", Win32MessageMap::GetMessageName(message));
    OutputDebugStringW(buf);

    switch (message) {
    case WM_POINTERDOWN:
    {
        // Get the full information for this pointer
        if (GetPointerInfo(pointerId, &pointerInfo)) {
            // We are only interested in touch inputs
            if (pointerInfo.pointerType == PT_TOUCH) {
                POINT pt = pointerInfo.ptPixelLocation;
                ScreenToClient(hwnd, &pt);
                // Add the new finger to our map
                g_touchPoints[pointerId] = pt;
                InvalidateRect(hwnd, NULL, TRUE);
            }
        }
        return 0; // Mark message as handled
    }

    case WM_POINTERUPDATE:
    {
        if (GetPointerInfo(pointerId, &pointerInfo)) {
            POINT pt = pointerInfo.ptPixelLocation;
            ScreenToClient(hwnd, &pt);
            // Update the finger's position in our map
            g_touchPoints[pointerId] = pt;
            InvalidateRect(hwnd, NULL, TRUE);
            if (pointerInfo.pointerType == PT_TOUCH) {
                
            }
        }
        return 0; // Mark message as handled
    }

    case WM_POINTERUP:
    {
        // This pointer is now 'up', so remove it from our map
        g_touchPoints.erase(pointerId);
        InvalidateRect(hwnd, NULL, TRUE);
        return 0; // Mark message as handled
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        HBRUSH hBrush = CreateSolidBrush(RGB(200, 0, 0)); // Red
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        // Draw a circle for each currently tracked finger
        for (auto const& [id, pt] : g_touchPoints) {
            Ellipse(hdc, pt.x - 20, pt.y - 20, pt.x + 20, pt.y + 20);
        }

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}