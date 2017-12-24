
/***
 *          _               _
 *         | |             | |
 *       __| |_ ____      _| |__  _   _
 *      / _` | '_ \ \ /\ / / '_ \| | | |
 *     | (_| | | | \ V  V /| |_) | |_| |
 *      \__,_|_| |_|\_/\_/ |_.__/ \__,_|
 *
 *     DevelNext Window Blur Util - dnwbu by Rebzzel
 *     For use this you need:
 *         DevelNext
 *         DFFI (https://github.com/HackMemory/dn-dffi-ext)
 *     License: https://github.com/Rebzzel/dnwbu#license
 */


#ifndef __dnwbu_h__
#define __dnwbu_h__

#define DN_DLL_EXPORT extern "C" __declspec (dllexport)

typedef void *PVOID; // from windef.h
typedef unsigned long ULONG; // from windef.h

enum
{
	ACCENT_DISABLED = 0,
	ACCENT_ENABLE_GRADIENT = 1,
	ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
	ACCENT_ENABLE_BLURBEHIND = 3,
	ACCENT_INVALID_STATE = 4,

	WCA_ACCENT_POLICY = 19
};

struct ACCENTPOLICY
{
	int nAccentState;
	int nFlags;
	int nColor;
	int nAnimationId;
};

struct WINCOMPATTRDATA
{
	int nAttribute;
	PVOID pData;
	ULONG ulDataSize;
};

/**
* \brief Blur for win7 windows.
* \param szWindowName Name of the window.
*
* \return 0 If success.
*/
DN_DLL_EXPORT int SetWindowBlur7(const char* szWindowName);

/**
* \brief Blur for win10 windows.
* \param szWindowName Name of the window.
*
* \return 0 If success. 1 If user32.dll can't be loaded. 2 If SetWindowCompositionAttribute function not found in user32.dll.
*/
DN_DLL_EXPORT int SetWindowBlur10(const char* szWindowName);

/**
* \brief Automatically gets the windows version and blurs the window.
* \param szWindowName Name of the window.
*
* \return 0 If success. 4 If Windows version not supported.
*/
DN_DLL_EXPORT int SetWindowBlur(const char* szWindowName);

#endif