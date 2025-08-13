// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <hstring.h>
#include <pplwin.h>
#include "init/init.h"

HMODULE consoleLogon = 0;

HMODULE GetConsoleLogonDLL()
{
    if (consoleLogon)
        return consoleLogon;

    consoleLogon = LoadLibraryW(L"C:\\Windows\\System32\\ConsoleLogon.dll");
    if (!consoleLogon)
        MessageBox(0, L"FAILED TO LOAD", L"FAILED TO LOAD", 0);
    return consoleLogon;
}

extern "C" __declspec(dllexport) HRESULT __stdcall DllCanUnloadNow()
{
    return reinterpret_cast<HRESULT(*)()>(GetProcAddress(GetConsoleLogonDLL(), "DllCanUnloadNow"))();
}

extern "C" __declspec(dllexport) __int64 DllGetActivationFactory(HSTRING string, PVOID Ptr)
{
    return reinterpret_cast<__int64(*)(HSTRING string, PVOID Ptr)>(GetProcAddress(GetConsoleLogonDLL(), "DllGetActivationFactory"))(string, Ptr);
}

extern "C" __declspec(dllexport) HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return reinterpret_cast<HRESULT(*)(REFCLSID rclsid, REFIID riid, LPVOID * ppv)>(GetProcAddress(GetConsoleLogonDLL(), "DllGetClassObject"))(rclsid, riid, ppv);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        init::InitHooks();
        break;

    case DLL_PROCESS_DETACH:
        //FreeLibraryAndExitThread(consoleLogon,0);
        init::Unload();
        break;
    }
    return TRUE;
}

