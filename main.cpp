#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <hidsdi.h> // Required for HID functions like HidD_GetFeature
#include <hidpi.h>
#include <setupapi.h> // For device enumeration
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

//raw input gathered struct
#pragma pack (push, r1, 1)
extern "C" struct TouchpadInputReport_Touchpoint {
    uint8_t pressedStatus;
    uint8_t trackedTouchpointID;
    uint16_t xPos;
    uint16_t yPos;
};
extern "C" struct TouchpadInputReport {
    char unknown1;
    TouchpadInputReport_Touchpoint touchpoints[5];
    uint16_t touchpointsPressed;
    uint16_t tenthmsCount;
};
#pragma pack(pop, r1, 8)

// Global variables to store the output strings
static uint16_t g_lastTimerVal = 0;
static std::wstring g_parsedInputOutput = L"Nothing here";
static std::wstring g_rawInputOutput = L"Move your finger or click on the touchpad...";

// Forward declaration of the Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

    const wchar_t CLASS_NAME[] = L"Raw Touchpad Input Window Class";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"Raw Precision Touchpad Input", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    {

        RAWINPUTDEVICE rid;
        rid.usUsagePage = 0x0D; // Digitizer
        rid.usUsage = 0x05;     // Touch Pad
        rid.dwFlags = RIDEV_INPUTSINK;
        rid.hwndTarget = hwnd;

        if (!RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE))) {
            MessageBox(hwnd, L"Failed to register for raw touchpad input.", L"Error", MB_ICONERROR);
        }
        return 0;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }

    case WM_INPUT:
    {
        UINT dataSize;
        GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));
        std::vector<BYTE> buffer(dataSize);

        if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer.data(), &dataSize, sizeof(RAWINPUTHEADER)) != dataSize) {
            g_rawInputOutput = L"Error getting raw input data.";
        }
        else {
            RAWINPUT* raw = (RAWINPUT*)buffer.data();
            if (raw->header.dwType == RIM_TYPEHID) {
               /* std::wstringstream parsedSS;
                TouchpadInputReport* tir = reinterpret_cast<TouchpadInputReport*>(&raw->data.hid.bRawData);
                parsedSS << L"Unknown: " << tir->unknown1 << L"\n";
                for (int i = 0; i < tir->touchpointsPressed; i++) {
                    parsedSS << L"Touchpoint[" << i << 
                        L"]: PressedStatus: " << tir->touchpoints[i].pressedStatus << 
                        L" TrackedTouchpointID: " << tir->touchpoints[i].trackedTouchpointID <<
                        L" xpos: " << tir->touchpoints[i].xPos <<
                        L" ypos: " << tir->touchpoints[i].yPos <<
                        L"\n";
                }

                parsedSS << L"Touchpoints pressed: " << tir->touchpointsPressed << L"\n";
                parsedSS << L"Timer: " << tir->tenthmsCount << L"\n";
                parsedSS << L"Timer delta from last update: " << tir->tenthmsCount - g_lastTimerVal << L"\n";
                g_lastTimerVal = tir->tenthmsCount;*/

                std::wstringstream ss;
                ss << L"------------------------------------\n";
                ss << L"Real-time HID Input Report:\n";
                ss << std::hex << std::uppercase << std::setfill(L'0');

                for (DWORD i = 0; i < raw->data.hid.dwSizeHid * raw->data.hid.dwCount; ++i) {
                    ss << std::setw(2) << static_cast<int>(raw->data.hid.bRawData[i]) << L" ";
                    if ((i + 1) % 16 == 0) ss << L"\n";
                }
                //g_parsedInputOutput = parsedSS.str();
                g_rawInputOutput = ss.str();
            }
        }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        HFONT hFont = CreateFontW(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, L"Consolas");
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // Define two regions for drawing text
        RECT topRect = ps.rcPaint;
        topRect.bottom = topRect.bottom / 2; // Use top half for capabilities

        RECT bottomRect = ps.rcPaint;
        bottomRect.top = topRect.bottom; // Use bottom half for raw input

        // Draw static capabilities
        DrawTextW(hdc, g_parsedInputOutput.c_str(), -1, &topRect, DT_LEFT | DT_TOP | DT_WORDBREAK);

        // Draw real-time input
        DrawTextW(hdc, g_rawInputOutput.c_str(), -1, &bottomRect, DT_LEFT | DT_TOP | DT_WORDBREAK);

        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);

        EndPaint(hwnd, &ps);
        return 0;
    }

    } // end switch

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}