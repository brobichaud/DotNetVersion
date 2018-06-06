#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "winvers.h"
#include "registrykeys.h"
#include "framework.h"
#include "servicepack.h"
#include "support.h"


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	TCHAR szMessage[4096];
	TCHAR szVersion[_MAX_PATH];
	TCHAR szTemp[_MAX_PATH];

	CWindowsVersion winver;
	memset(szMessage, 0, sizeof(szMessage));
	lstrcpy(szMessage, "Operating System:\n");
	lstrcat(szMessage, winver.GetVersionFmt());
	lstrcat(szMessage, "\n\n");
	lstrcat(szMessage, "DotNet Framework Runtimes:\n");

	// If Framework 4.x is installed, get the service pack level
	if (IsNetfx4xInstalled())
	{
		memset(szVersion, 0, sizeof(szVersion));
		GetNetfx4xSpLevel(szVersion);

		TCHAR szRelease[_MAX_PATH];
		GetNetFx4xRelease(szRelease);

		_stprintf_s(szTemp, _T("Version 4.x: v%s (%s)"), szVersion , szRelease);
	}

	// If Framework 4.0 Full is installed, get the service pack level
	else if (IsNetfx40FullInstalled())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx40SpLevel = GetNetfx40FullSpLevel(szVersion);

		if (iNetfx40SpLevel > 0)
			_stprintf_s(szTemp, _T("Version 4.x: v%s (sp%i)"), szVersion, iNetfx40SpLevel);
		else
			_stprintf_s(szTemp, _T("Version 4.x: v%s"), szVersion);
	}
	
	// If Framework 4.0 Client is installed, get the service pack level
	else if (IsNetfx40ClientInstalled())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx40SpLevel = GetNetfx40ClientSpLevel(szVersion);

		if (iNetfx40SpLevel > 0)
			_stprintf_s(szTemp, _T("Version 4.x: v%s (sp%i) Client Profile"), szVersion, iNetfx40SpLevel);
		else
			_stprintf_s(szTemp, _T("Version 4.x: v%s Client Profile"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 4.x: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	// If Framework 3.5 is installed, get the service pack level
	if (IsNetfx35Installed())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx35SpLevel = GetNetfx35SpLevel(szVersion);

		if (iNetfx35SpLevel > 0)
			_stprintf_s(szTemp, _T("Version 3.5: v%s (sp%i)"), szVersion, iNetfx35SpLevel);
		else
			_stprintf_s(szTemp, _T("Version 3.5: v%s"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 3.5: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	// If Framework 3.0 is installed, get the service pack level
	if (IsNetfx30Installed())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx30SpLevel = GetNetfx30SpLevel(szVersion);

		if (iNetfx30SpLevel > 0)
			_stprintf_s(szTemp, _T("Version 3.0: v%s (sp%i)"), szVersion, iNetfx30SpLevel);
		else
			_stprintf_s(szTemp, _T("Version 3.0: v%s"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 3.0: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	// If Framework 2.0 is installed, get the service pack level
	if (IsNetfx20Installed())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx20SpLevel = GetNetfx20SpLevel(szVersion);

		if (iNetfx20SpLevel > 0)
			_stprintf_s(szTemp, _T("Version 2.0: v%s (sp%i)"), szVersion, iNetfx20SpLevel);
		else
			_stprintf_s(szTemp, _T("Version 2.0: v%s"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 2.0: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	// If Framework 1.1 is installed, get the service pack level
	if (IsNetfx11Installed())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx11SpLevel = GetNetfx11SpLevel(szVersion);

		if (iNetfx11SpLevel > 0)
			_stprintf_s(szTemp, _T("Version 1.1: v%s (sp%i)"), szVersion, iNetfx11SpLevel);
		else
			_stprintf_s(szTemp, _T("Version 1.1: v%s"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 1.1: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	// If Framework 1.0 is installed, get the service pack level
	if (IsNetfx10Installed())
	{
		int iNetfx10SpLevel = GetNetfx10SpLevel();

		if (iNetfx10SpLevel > 0)
			_stprintf_s(szTemp, _T("Version 1.0: Installed (sp%i)"), iNetfx10SpLevel);
		else
			_stprintf_s(szTemp, _T("Version 1.0: Installed"));
	}
	else
		_stprintf_s(szTemp, _T("Version 1.0: Not Installed"));

	lstrcat(szMessage, szTemp);

	MessageBox(NULL, szMessage, _T("DotNet Version Information v4.7"), MB_OK | MB_ICONINFORMATION);

	return 0;
}
