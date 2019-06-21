#include <windows.h>
#include "registrykeys.h"
#include "support.h"

void GetNetFx4xRelease(char* szRelease)
{
	DWORD dwRelValue = 0;
	lstrcpy(szRelease, "");
	RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xRegKeyName, g_szNetfx4xReleaseRegValueName, NULL, (LPBYTE)&dwRelValue, sizeof(DWORD));

	if (dwRelValue >= 528040)
		lstrcpy(szRelease, "4.8");
	else if (dwRelValue >= 461808)
		lstrcpy(szRelease, "4.7.2");
	else if (dwRelValue >= 461308)
		lstrcpy(szRelease, "4.7.1");
	else if (dwRelValue >= 460798)
		lstrcpy(szRelease, "4.7");
	else if (dwRelValue >= 394802)
		lstrcpy(szRelease, "4.6.2");
	else if (dwRelValue >= 394254)
		lstrcpy(szRelease, "4.6.1");
	else if (dwRelValue >= 393295)
		lstrcpy(szRelease, "4.6");
	else if (dwRelValue >= 379893)
		lstrcpy(szRelease, "4.5.2");
	else if (dwRelValue >= 378675)
		lstrcpy(szRelease, "4.5.1");
	else if (dwRelValue >= 378389)
		lstrcpy(szRelease, "4.5");
}

bool IsNetfx4xInstalled()
{
	DWORD dwRegValue = 0;
	DWORD dwRelValue = 0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xRegKeyName, g_szNetfx4xRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue != 1)
			return false;

		if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xRegKeyName, g_szNetfx4xReleaseRegValueName, NULL, (LPBYTE)&dwRelValue, sizeof(DWORD)))
		{
			if (dwRelValue != 0)
				return true;
		}
	}

	return false;
}

bool IsNetfx40FullInstalled()
{
	DWORD dwRegValue = 0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xRegKeyName, g_szNetfx4xRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

bool IsNetfx40ClientInstalled()
{
	DWORD dwRegValue = 0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xClientRegKeyName, g_szNetfx4xRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

bool IsNetfx35Installed()
{
	DWORD dwRegValue = 0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx35RegKeyName, g_szNetfx35RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

bool IsNetfx30Installed()
{
	DWORD dwRegValue = 0;

	// look for original Net 3.0 install
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx30OrigRegKeyName, g_szNetfx30OrigRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	// no original 3.0 install so look for 3.0sp1 install
	// MS keeps changing registry keys!
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx30RegKeyName, g_szNetfx30RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

bool IsNetfx20Installed()
{
	DWORD dwRegValue = 0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx20RegKeyName, g_szNetfx20RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

/******************************************************************
Uses the detection method recommended at
http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnnetdep/html/redistdeploy1_1.asp
to determine whether the .NET Framework 1.1 is installed on the machine
******************************************************************/
bool IsNetfx11Installed()
{
	DWORD dwRegValue = 0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx11RegKeyName, g_szNetfx11RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

/******************************************************************
Uses the detection method recommended at
http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnnetdep/html/dotnetfxref.asp
to determine whether the .NET Framework 1.0 is installed on the machine
******************************************************************/
bool IsNetfx10Installed()
{
	TCHAR szRegValue[MAX_PATH];
	return (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx10RegKeyName, g_szNetfx10RegKeyValue, NULL, (LPBYTE)szRegValue, MAX_PATH));
}
