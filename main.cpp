#include <windows.h>
#include <vector>
#include <map>

// Global map to store finger positions.
// Key: Finger ID (DWORD), Value: Position (POINT)
std::map<DWORD, POINT> g_touchPoints;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"TouchSampleWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"Win32 Trackpad Touch Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    // Register the window for touch input
    if (!RegisterTouchWindow(hwnd, 0)) {
        MessageBox(hwnd, L"Error: Could not register for touch input.", L"Error", MB_OK | MB_ICONERROR);
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void ProcessTouchInput(HWND hwnd, UINT numInputs, HTOUCHINPUT hTouchInput) {
    TOUCHINPUT* pInputs = new TOUCHINPUT[numInputs];
    if (pInputs == NULL) {
        return;
    }

    if (GetTouchInputInfo(hTouchInput, numInputs, pInputs, sizeof(TOUCHINPUT))) {
        for (UINT i = 0; i < numInputs; i++) {
            TOUCHINPUT ti = pInputs[i];

            POINT pt;
            pt.x = TOUCH_COORD_TO_PIXEL(ti.x);
            pt.y = TOUCH_COORD_TO_PIXEL(ti.y);
            ScreenToClient(hwnd, &pt);

            if (ti.dwFlags & TOUCHEVENTF_DOWN) {
                // Finger went down, add it to our map
                g_touchPoints[ti.dwID] = pt;
            }
            else if (ti.dwFlags & TOUCHEVENTF_MOVE) {
                // Finger is moving, update its position
                g_touchPoints[ti.dwID] = pt;
            }
            else if (ti.dwFlags & TOUCHEVENTF_UP) {
                // Finger went up, remove it from our map
                g_touchPoints.erase(ti.dwID);
            }
        }
    }

    // CRITICAL: Must close the handle to prevent resource leaks
    CloseTouchInputHandle(hTouchInput);
    delete[] pInputs;

    // Force the window to be redrawn
    InvalidateRect(hwnd, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // White background
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // Create a brush to draw the circles
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 200)); // Blue
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        // Draw a circle for each currently tracked finger
        for (auto const& [id, pt] : g_touchPoints) {
            // Draw a circle of radius 20 around the touch point
            Ellipse(hdc, pt.x - 20, pt.y - 20, pt.x + 20, pt.y + 20);
        }

        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);

        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_TOUCH:
    {
        UINT numInputs = LOWORD(wParam);
        HTOUCHINPUT hTouchInput = (HTOUCHINPUT)lParam;
        ProcessTouchInput(hwnd, numInputs, hTouchInput);
        return 0;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        // Unregister is good practice, though not strictly required as
        // window destruction cleans up registrations.
        UnregisterTouchWindow(hwnd);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}