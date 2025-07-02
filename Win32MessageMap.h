#pragma once

#include <string>
#include <map>
#include <Windows.h> // Required for UINT and WM_ defines

// A static utility class to get string names for Win32 WM_ messages.
class Win32MessageMap {
public:
    // Gets the string name for a given Windows Message (UINT).
    //
    // If the message is a standard WM_ message, its predefined name is returned.
    // If the message is WM_USER or above, it's formatted as "WM_USER + <offset>".
    // If the message is not found and is below WM_USER, it's formatted as "Unknown (0x<hex_value>)".
    //
    // Note: The returned const char* points to an internal static buffer for unknown/WM_USER messages,
    // which is NOT thread-safe. For thread-safe use, you might return std::string or pass in a buffer.
    static const wchar_t* GetMessageName(UINT message);

private:
    // The static map that stores message IDs and their string names.
    // Initialized only once when the program starts.
    static std::map<UINT, const wchar_t*> s_messageMap;

    // Helper function to create and populate the map.
    // This function is called once during static initialization.
    static std::map<UINT, const wchar_t*> CreateMessageMap();

    // Prevent instantiation
    Win32MessageMap() = delete;
    Win32MessageMap(const Win32MessageMap&) = delete;
    Win32MessageMap& operator=(const Win32MessageMap&) = delete;
};