#include <Windows.h>
#include <dwmapi.h>
#include <VersionHelpers.h>

#include "dnwbu.h"

#pragma comment(lib, "dwmapi.lib")

typedef BOOL(__stdcall *tSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);
tSetWindowCompositionAttribute SetWindowCompositionAttribute = nullptr;

DN_DLL_EXPORT int SetWindowBlur7(const char* szWindowName)
{
	DWM_BLURBEHIND dwmbb;
	{
		dwmbb.dwFlags = DWM_BB_ENABLE;
		dwmbb.fEnable = TRUE;
		dwmbb.hRgnBlur = NULL;
	}

	auto hr = DwmEnableBlurBehindWindow(FindWindow(0, szWindowName), &dwmbb);

	if (FAILED(hr))
	{
		return hr;
	}

	return 0;
}

DN_DLL_EXPORT int SetWindowBlur10(const char* szWindowName)
{
	auto hUser32 = LoadLibrary("user32.dll");

	if (hUser32 == nullptr)
	{
		return 1;
	}

	SetWindowCompositionAttribute = reinterpret_cast<tSetWindowCompositionAttribute>(GetProcAddress(hUser32, "SetWindowCompositionAttribute"));

	if (SetWindowCompositionAttribute == nullptr)
	{
		FreeLibrary(hUser32);
		return 2;
	}

	ACCENTPOLICY accentPolicy = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
	WINCOMPATTRDATA data = { WCA_ACCENT_POLICY, &accentPolicy, sizeof(ACCENTPOLICY) };

	SetWindowCompositionAttribute(FindWindow(0, szWindowName), &data);
	FreeLibrary(hUser32);

	return 0;
}

DN_DLL_EXPORT int SetWindowBlur(const char* szWindowName)
{
	if (IsWindows10OrGreater())
	{
		return SetWindowBlur10(szWindowName);
	} else if (IsWindows7OrGreater) {
		return SetWindowBlur7(szWindowName);
	} else {
		return 4;
	}
}