# ConsoleLogonHook
This project hooks onto and provides a graphical user interface for the console logon screen in Windows 10.<br>
Credits go to [@mishaproductions](https://github.com/mishaproductions) for the [DirectUI library](https://github.com/MishaProductions/dui70), I was too lazy to properly embed it into the CLH repo

> [!NOTE]
> This is not the original repository, CLH is now deprecated and the original owner recommends you to use [AuthUX](https://github.com/world-windows-federation/AuthUX), unless you have a specific use case, please go use that instead!

> [!WARNING]
> **This project is in early development and might be unstable.** You may encounter issues using a Microsoft account, however, this will work perfectly fine on local accounts. Disabling the lockscreen and the <kbd>CTRL</kbd> <kbd>Alt</kbd> <kbd>Del</kbd> logon keybinds is recommended as they're not fully implemented yet.
 
## Installation
> [!WARNING]
> **This will require administrator privileges to be installed.**

1. Copy the 2 DLL files (ConsoleLogonHook.dll and ConsoleLogonUI.dll) from [Releases](https://github.com/n1d3v/ConsoleLogonHook/releases) into %SYSTEMROOT%\System32
2. Open a CMD window as TrustedInstaller via PsExec64 and copy and paste the following commands:

```cmd
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsRuntime\ActivatableClassId\Windows.Internal.UI.Logon.Controller.ConsoleBlockedShutdownResolver /v DllPath /t REG_SZ /d %systemroot%\System32\ConsoleLogonHook.dll /f
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsRuntime\ActivatableClassId\Windows.Internal.UI.Logon.Controller.ConsoleLockScreen /v DllPath /t REG_SZ /d %systemroot%\System32\ConsoleLogonHook.dll /f
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsRuntime\ActivatableClassId\Windows.Internal.UI.Logon.Controller.ConsoleLogonUX /v DllPath /t REG_SZ /d %systemroot%\System32\ConsoleLogonHook.dll /f
reg add HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WindowsRuntime\ActivatableClassId\Windows.Internal.Shell.PlatformExtensions.ConsoleCredUX /v DllPath /t REG_SZ /d %systemroot%\System32\ConsoleLogonHook.dll /f
```
or merge the registry key in the Release ZIP as Trusted Installer.

3. Take ownership of the file `Windows.UI.Logon.dll` and rename it to something else. Example: `Windows.UI.Logon.dll.bak`, this is required as it will force the use of the console logon screen.
