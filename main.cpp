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
    uint8_t touchpointsPressed, padButtonPressed;
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

struct MemberLocation {
    USAGE Page, ID;
};

// for finger members
static const MemberLocation ContactID = { 0x0D, 0x51 };
static const MemberLocation X = { 0x01, 0x30 };
static const MemberLocation Y = { 0x01, 0x31 };

// for whole touchpad
static const MemberLocation ContactCount = { 0x0D, 0x54 };
static const MemberLocation ScanTime = { 0x0D, 0x56 };

template <typename _Type>
inline bool arrayHas(const _Type* arr, size_t arrlen, const _Type& val) {
    for (size_t i = 0; i < arrlen; i++) {
        if (arr[i] == val) return true;
    }
    return false;
}

TouchpadInputReport getTir(PRAWINPUT rawInp, PHIDP_PREPARSED_DATA ppData) {
    TouchpadInputReport tir = {};
    
    ULONG output = 0;

    NTSTATUS hidpstat1 = HIDP_STATUS_SUCCESS;
    NTSTATUS hidpstat2 = HIDP_STATUS_INVALID_REPORT_LENGTH;
    NTSTATUS hidpstat3 = HIDP_STATUS_INVALID_REPORT_TYPE;
    NTSTATUS hidpstat4 = HIDP_STATUS_INCOMPATIBLE_REPORT_ID;
    NTSTATUS hidpstat5 = HIDP_STATUS_INVALID_PREPARSED_DATA;
    NTSTATUS hidpstat6 = HIDP_STATUS_USAGE_NOT_FOUND;

    const ULONG len = 8;
    ULONG usageArrLen = len;
    USAGE usageArr[len];

    for (int i = 0; i < 5; i++) {
        // Contact ID
        HidP_GetUsageValue(
            HidP_Input,
            ContactID.Page,
            i + 1,
            ContactID.ID,
            &output,
            ppData,
            (PCHAR)rawInp->data.hid.bRawData,
            rawInp->data.hid.dwSizeHid
        );
        tir.touchpoints[i].trackedTouchpointID = output;

        // X
        HidP_GetUsageValue(
            HidP_Input,
            X.Page,
            i + 1,
            X.ID,
            &output,
            ppData,
            (PCHAR)rawInp->data.hid.bRawData,
            rawInp->data.hid.dwSizeHid
        );
        tir.touchpoints[i].xPos = output;

        // Y
        HidP_GetUsageValue(
            HidP_Input,
            Y.Page,
            i + 1,
            Y.ID,
            &output,
            ppData,
            (PCHAR)rawInp->data.hid.bRawData,
            rawInp->data.hid.dwSizeHid
        );
        tir.touchpoints[i].yPos = output;

        // Tip and Confidence
        HidP_GetUsages(
            HidP_Input,
            0x0D,
            i + 1,
            usageArr,
            &usageArrLen,
            ppData,
            (PCHAR)rawInp->data.hid.bRawData,
            rawInp->data.hid.dwSizeHid
        );
        arrayHas<USAGE>(usageArr, usageArrLen, 0x42) ? tir.touchpoints[i].pressedStatus += 1 : (NULL);
        !arrayHas<USAGE>(usageArr, usageArrLen, 0x47) ? tir.touchpoints[i].pressedStatus += 2 : (NULL);
    }

    HidP_GetUsages(
        HidP_Input,
        0x09,
        0,
        usageArr,
        &usageArrLen,
        ppData,
        (PCHAR)rawInp->data.hid.bRawData,
        rawInp->data.hid.dwSizeHid
    );
    arrayHas<USAGE>(usageArr, usageArrLen, 0x01) ? tir.padButtonPressed += 1 : (NULL);
    arrayHas<USAGE>(usageArr, usageArrLen, 0x02) ? tir.padButtonPressed += 2 : (NULL);
    arrayHas<USAGE>(usageArr, usageArrLen, 0x03) ? tir.padButtonPressed += 4 : (NULL);

    // Contact Count
    NTSTATUS status = HidP_GetUsageValue(
        HidP_Input,
        ContactCount.Page,
        0,
        ContactCount.ID,
        &output,
        ppData,
        (PCHAR)rawInp->data.hid.bRawData,
        rawInp->data.hid.dwSizeHid
    );
    tir.touchpointsPressed = output;

    // Scan Time
    status = HidP_GetUsageValue(
        HidP_Input,
        ScanTime.Page,
        0,
        ScanTime.ID,
        &output,
        ppData,
        (PCHAR)rawInp->data.hid.bRawData,
        rawInp->data.hid.dwSizeHid
    );
    tir.tenthmsCount = output;


    return tir;
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
            //caps loading
            static bool capsLoaded = false;
            static PHIDP_PREPARSED_DATA preparsedData = nullptr;
            if (!capsLoaded) {
                PRAWINPUT rawInputData = ((PRAWINPUT)buffer.data());

                UINT ppDataSize;
                GetRawInputDeviceInfoW(
                    rawInputData->header.hDevice,
                    RIDI_PREPARSEDDATA,
                    NULL,
                    &ppDataSize
                );

                preparsedData = (PHIDP_PREPARSED_DATA)HeapAlloc(GetProcessHeap(), 0, ppDataSize);
                GetRawInputDeviceInfoW(
                    ((PRAWINPUT)buffer.data())->header.hDevice,
                    RIDI_PREPARSEDDATA,
                    preparsedData,
                    &ppDataSize
                );
                HIDP_CAPS hidpCaps = {};
                HidP_GetCaps(preparsedData, &hidpCaps);
                USHORT capsLength = hidpCaps.NumberInputValueCaps;
                PHIDP_VALUE_CAPS valueCaps = (PHIDP_VALUE_CAPS)HeapAlloc(GetProcessHeap(), 0, capsLength * sizeof(HIDP_VALUE_CAPS));
                HidP_GetValueCaps(HidP_Input, valueCaps, &capsLength, preparsedData);
                
                for (int i = 0; i < capsLength; i++) {
                    HIDP_VALUE_CAPS oneValueCaps = valueCaps[i];
                    short a = oneValueCaps.UsagePage;
                }

                USHORT buttonsLength = hidpCaps.NumberInputButtonCaps;
                PHIDP_BUTTON_CAPS buttonCaps = (PHIDP_BUTTON_CAPS)HeapAlloc(GetProcessHeap(), 0, buttonsLength * sizeof(HIDP_BUTTON_CAPS));
                HidP_GetButtonCaps(HidP_Input, buttonCaps, &buttonsLength, preparsedData);

                for (int i = 0; i < buttonsLength; i++) {
                    HIDP_BUTTON_CAPS oneButtonCaps = buttonCaps[i];
                    short a = oneButtonCaps.LinkCollection;
                }
                

                USAGE usagePage = 0x01;
                USAGE usage = 0x30;
                USHORT linkCollection = 1;

                ULONG output = 0;

                HidP_GetUsageValue(
                    HidP_Input, 
                    usagePage, 
                    linkCollection,
                    usage, 
                    &output, 
                    preparsedData, 
                    (PCHAR)rawInputData->data.hid.bRawData,
                    rawInputData->data.hid.dwSizeHid
                );
                
                

                capsLoaded = true;
                //HeapFree(GetProcessHeap(), 0, preparsedData);
                HeapFree(GetProcessHeap(), 0, valueCaps);
            }
            
            //other raw stuff
            RAWINPUT* raw = (RAWINPUT*)buffer.data();
            if (raw->header.dwType == RIM_TYPEHID) {
               std::wstringstream parsedSS;
                TouchpadInputReport tir = getTir(raw, preparsedData);
                parsedSS << L"Unknown: " << std::to_wstring(tir.unknown1) << L"\n";
                for (int i = 0; i < tir.touchpointsPressed; i++) {
                    parsedSS << L"Touchpoint[" << i << 
                        L"]: PressedStatus: " << tir.touchpoints[i].pressedStatus << 
                        L" TrackedTouchpointID: " << tir.touchpoints[i].trackedTouchpointID <<
                        L" xpos: " << tir.touchpoints[i].xPos <<
                        L" ypos: " << tir.touchpoints[i].yPos <<
                        L"\n";
                }

                parsedSS << L"Touchpoints pressed: " << tir.touchpointsPressed << L"\n";
                parsedSS << L"Pad pressed: " << tir.padButtonPressed << L"\n";
                parsedSS << L"Timer: " << tir.tenthmsCount << L"\n";
                parsedSS << L"Timer delta from last update: " << tir.tenthmsCount - g_lastTimerVal << L"\n";
                g_lastTimerVal = tir.tenthmsCount;

                std::wstringstream ss;
                ss << L"------------------------------------\n";
                ss << L"Real-time HID Input Report:\n";
                ss << std::hex << std::uppercase << std::setfill(L'0');

                for (DWORD i = 0; i < raw->data.hid.dwSizeHid * raw->data.hid.dwCount; ++i) {
                    ss << std::setw(2) << static_cast<int>(raw->data.hid.bRawData[i]) << L" ";
                    if ((i + 1) % 16 == 0) ss << L"\n";
                }
                g_parsedInputOutput = parsedSS.str();
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