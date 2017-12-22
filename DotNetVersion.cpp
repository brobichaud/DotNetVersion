#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "WinVers.h"

// Constants that represent registry key names and value names
// to use for detection
const TCHAR *g_szNetfx10RegKeyName = _T("Software\\Microsoft\\.NETFramework\\Policy\\v1.0");
const TCHAR *g_szNetfx10RegKeyValue = _T("3705");
const TCHAR *g_szNetfx10SPxMSIRegKeyName = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{78705f0d-e8db-4b2d-8193-982bdda15ecd}");
const TCHAR *g_szNetfx10SPxOCMRegKeyName = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{FDC11A6F-17D1-48f9-9EA3-9051954BAA24}");
const TCHAR *g_szNetfx10SPxRegValueName = _T("Version");

const TCHAR *g_szNetfx11RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322");
const TCHAR *g_szNetfx11RegValueName = _T("Install");
const TCHAR *g_szNetfx11SPxRegValueName = _T("SP");

const TCHAR *g_szNetfx20RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727");
const TCHAR *g_szNetfx20RegValueName = _T("Install");
const TCHAR *g_szNetfx20SPxRegValueName = _T("SP");
const TCHAR *g_szNetfx20VersRegValueName = _T("Version");

const TCHAR *g_szNetfx30OrigRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.0\\Setup");
const TCHAR *g_szNetfx30OrigRegValueName = _T("InstallSuccess");
const TCHAR *g_szNetfx30RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.0");
const TCHAR *g_szNetfx30RegValueName = _T("Install");
const TCHAR *g_szNetfx30SPxRegValueName = _T("SP");
const TCHAR *g_szNetfx30VersRegValueName = _T("Version");

const TCHAR *g_szNetfx35RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.5");
const TCHAR *g_szNetfx35RegValueName = _T("Install");
const TCHAR *g_szNetfx35SPxRegValueName = _T("SP");
const TCHAR *g_szNetfx35VersRegValueName = _T("Version");

const TCHAR *g_szNetfx40FullRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full");
const TCHAR *g_szNetfx40ClientRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Client");
const TCHAR *g_szNetfx40RegValueName = _T("Install");
const TCHAR *g_szNetfx40SPxRegValueName = _T("SP");
const TCHAR *g_szNetfx40VersRegValueName = _T("Version");

const TCHAR *g_szNetfx45FullRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full");
const TCHAR *g_szNetfx45ClientRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Client");
const TCHAR *g_szNetfx45RegValueName = _T("Install");
const TCHAR *g_szNetfx45SPxRegValueName = _T("SP");
const TCHAR *g_szNetfx45VersRegValueName = _T("Version");
const TCHAR *g_szNetfx45ReleaseRegValueName = _T("Release");

/******************************************************************
Function Name:	RegistryGetValue
Description:	Get the value of a reg key
Inputs:			HKEY hk - The hk of the key to retrieve
TCHAR *pszKey - Name of the key to retrieve
TCHAR *pszValue - The value that will be retrieved
DWORD dwType - The type of the value that will be retrieved
LPBYTE data - A buffer to save the retrieved data
DWORD dwSize - The size of the data retrieved
Results:		true if successful, false otherwise
******************************************************************/
bool RegistryGetValue(HKEY hk, const TCHAR * pszKey, const TCHAR * pszValue, DWORD dwType, LPBYTE data, DWORD dwSize)
{
	HKEY hkOpened;

	// Try to open the key
	if (RegOpenKeyEx(hk, pszKey, 0, KEY_READ, &hkOpened) != ERROR_SUCCESS)
	{
		return false;
	}

	// If the key was opened, try to retrieve the value
	if (RegQueryValueEx(hkOpened, pszValue, 0, &dwType, (LPBYTE)data, &dwSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hkOpened);
		return false;
	}

	// Clean up
	RegCloseKey(hkOpened);

	return true;
}

bool IsCurrentOSTabletMedCenter()
{
	// Use GetSystemMetrics to detect if we are on a Tablet PC or Media Center OS  
	return ( (GetSystemMetrics(SM_TABLETPC) != 0) || (GetSystemMetrics(SM_MEDIACENTER) != 0) );
}

/******************************************************************
Function Name:	IsNetfx10Installed
Uses the detection method recommended at
http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnnetdep/html/dotnetfxref.asp
to determine whether the .NET Framework 1.0 is installed on the machine
******************************************************************/
bool IsNetfx10Installed()
{
	TCHAR szRegValue[MAX_PATH];
	return (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx10RegKeyName, g_szNetfx10RegKeyValue, NULL, (LPBYTE)szRegValue, MAX_PATH));
}

/******************************************************************
Function Name:	IsNetfx11Installed
Uses the detection method recommended at
http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnnetdep/html/redistdeploy1_1.asp
to determine whether the .NET Framework 1.1 is installed on the machine
******************************************************************/
bool IsNetfx11Installed()
{
	DWORD dwRegValue=0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx11RegKeyName, g_szNetfx11RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

/******************************************************************
Function Name:	IsNetfx20Installed
******************************************************************/
bool IsNetfx20Installed()
{
	DWORD dwRegValue=0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx20RegKeyName, g_szNetfx20RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

/******************************************************************
Function Name:	IsNetfx30Installed
******************************************************************/
bool IsNetfx30Installed()
{
	DWORD dwRegValue=0;

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

/******************************************************************
Function Name:	IsNetfx35Installed
******************************************************************/
bool IsNetfx35Installed()
{
	DWORD dwRegValue=0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx35RegKeyName, g_szNetfx35RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

/******************************************************************
Function Name:	IsNetfx40FullInstalled
******************************************************************/
bool IsNetfx40FullInstalled()
{
	DWORD dwRegValue=0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx40FullRegKeyName, g_szNetfx40RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

/******************************************************************
Function Name:	IsNetfx40ClientInstalled
******************************************************************/
bool IsNetfx40ClientInstalled()
{
	DWORD dwRegValue=0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx40ClientRegKeyName, g_szNetfx40RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

/******************************************************************
Function Name:	IsNetfx45Installed
******************************************************************/
bool IsNetfx45Installed()
{
	DWORD dwRegValue = 0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45FullRegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue == 1)
			return true;
	}

	return false;
}

/******************************************************************
Function Name:	GetNetfx10SPLevel
Uses the detection method recommended at
http://blogs.msdn.com/astebner/archive/2004/09/14/229802.aspx
to determine what service pack for the .NET Framework 1.0 is installed on the machine
******************************************************************/
int GetNetfx10SPLevel()
{
	TCHAR szRegValue[MAX_PATH];
	TCHAR *pszSPLevel = NULL;
	int iRetValue = 0;
	bool bRegistryRetVal = false;

	if (IsCurrentOSTabletMedCenter())
		bRegistryRetVal = RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx10SPxOCMRegKeyName, g_szNetfx10SPxRegValueName, NULL, (LPBYTE)szRegValue, MAX_PATH);
	else
		bRegistryRetVal = RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx10SPxMSIRegKeyName, g_szNetfx10SPxRegValueName, NULL, (LPBYTE)szRegValue, MAX_PATH);

	if (bRegistryRetVal)
	{
		// This registry value should be of the format
		// #,#,#####,# where the last # is the SP level
		// Try to parse off the last # here
		pszSPLevel = _tcsrchr(szRegValue, _T(','));
		if (NULL != pszSPLevel)
		{
			// Increment the pointer to skip the comma
			pszSPLevel++;

			// Convert the remaining value to an integer
			iRetValue = _tstoi(pszSPLevel);
		}
	}

	return iRetValue;
}

/******************************************************************
Function Name:	GetNetfx11SPLevel
Uses the detection method recommended at
http://blogs.msdn.com/astebner/archive/2004/09/14/229574.aspx
to determine what service pack for the .NET Framework 1.1 is installed on the machine
******************************************************************/
int GetNetfx11SPLevel(char* szVersion)
{
	DWORD dwRegValue=0;

	// default version, we have no way of obtaining anything else
	lstrcpy(szVersion, "1.1.4322");

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx11RegKeyName, g_szNetfx11SPxRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx20SPLevel
******************************************************************/
int GetNetfx20SPLevel(char* szVersion)
{
	DWORD dwRegValue=0;

	// default version
	lstrcpy(szVersion, "2.0.50727");

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx20RegKeyName, g_szNetfx20SPxRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue > 0)
			RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx20RegKeyName, g_szNetfx20VersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);

		return (int)dwRegValue;
	}

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx30SPLevel
******************************************************************/
int GetNetfx30SPLevel(char* szVersion)
{
	DWORD dwRegValue=0;

	// default version
	lstrcpy(szVersion, "");

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx30RegKeyName, g_szNetfx30SPxRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue > 0)
			RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx30RegKeyName, g_szNetfx30VersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);

		return (int)dwRegValue;
	}
	else
		RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx30OrigRegKeyName, g_szNetfx30VersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);


	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx35SPLevel
******************************************************************/
int GetNetfx35SPLevel(char* szVersion)
{
	DWORD dwRegValue=0;

	// default version
	lstrcpy(szVersion, "");

	RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx35RegKeyName, g_szNetfx35VersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx35RegKeyName, g_szNetfx35SPxRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx40FullSPLevel
******************************************************************/
int GetNetfx40FullSPLevel(char* szVersion)
{
	DWORD dwRegValue=0;

	// default version
	lstrcpy(szVersion, "");

	RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx40FullRegKeyName, g_szNetfx40VersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx40FullRegKeyName, g_szNetfx40SPxRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx40ClientSPLevel
******************************************************************/
int GetNetfx40ClientSPLevel(char* szVersion)
{
	DWORD dwRegValue=0;

	// default version
	lstrcpy(szVersion, "");

	RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx40ClientRegKeyName, g_szNetfx40VersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx40ClientRegKeyName, g_szNetfx40SPxRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx45SPLevel
******************************************************************/
int GetNetfx45SPLevel(char* szVersion)
{
	DWORD dwRegValue = 0;

	// default version
	lstrcpy(szVersion, "");

	RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45FullRegKeyName, g_szNetfx45VersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45FullRegKeyName, g_szNetfx45SPxRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

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

	// If .NET Framework 1.0 is installed, get the service pack level
	if (IsNetfx10Installed())
	{
		int iNetfx10SPLevel = GetNetfx10SPLevel();

		if (iNetfx10SPLevel > 0)
			_stprintf_s(szTemp, _T("Version 1.0: Installed (sp%i)"), iNetfx10SPLevel);
		else
			_stprintf_s(szTemp, _T("Version 1.0: Installed"));
	}
	else
		_stprintf_s(szTemp, _T("Version 1.0: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	// If .NET Framework 1.1 is installed, get the service pack level
	if (IsNetfx11Installed())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx11SPLevel = GetNetfx11SPLevel(szVersion);

		if (iNetfx11SPLevel > 0)
			_stprintf_s(szTemp, _T("Version 1.1: v%s (sp%i)"), szVersion, iNetfx11SPLevel);
		else
			_stprintf_s(szTemp, _T("Version 1.1: v%s"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 1.1: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	// If .NET Framework 2.0 is installed, get the service pack level
	if (IsNetfx20Installed())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx20SPLevel = GetNetfx20SPLevel(szVersion);

		if (iNetfx20SPLevel > 0)
			_stprintf_s(szTemp, _T("Version 2.0: v%s (sp%i)"), szVersion, iNetfx20SPLevel);
		else
			_stprintf_s(szTemp, _T("Version 2.0: v%s"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 2.0: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	// If .NET Framework 3.0 is installed, get the service pack level
	if (IsNetfx30Installed())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx30SPLevel = GetNetfx30SPLevel(szVersion);

		if (iNetfx30SPLevel > 0)
			_stprintf_s(szTemp, _T("Version 3.0: v%s (sp%i)"), szVersion, iNetfx30SPLevel);
		else
			_stprintf_s(szTemp, _T("Version 3.0: v%s"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 3.0: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	// If .NET Framework 3.5 is installed, get the service pack level
	if (IsNetfx35Installed())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx35SPLevel = GetNetfx35SPLevel(szVersion);

		if (iNetfx35SPLevel > 0)
			_stprintf_s(szTemp, _T("Version 3.5: v%s (sp%i)"), szVersion, iNetfx35SPLevel);
		else
			_stprintf_s(szTemp, _T("Version 3.5: v%s"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 3.5: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	
	// If .NET Framework 4.5 or 4.6 is installed, get the service pack level
	if (IsNetfx45Installed())
	{
		memset(szVersion, 0, sizeof(szVersion));
		DWORD dwRelValue = 0;
		GetNetfx40FullSPLevel(szVersion);

		RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45FullRegKeyName, g_szNetfx45ReleaseRegValueName, NULL, (LPBYTE)&dwRelValue, sizeof(DWORD));
		_stprintf_s(szTemp, _T("Version 4.x: v%s"), szVersion);
	}
	else if (IsNetfx40FullInstalled()) // If .NET Framework 4.0 is installed, get the service pack level
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx40SPLevel = GetNetfx40FullSPLevel(szVersion);

		if (iNetfx40SPLevel > 0)
			_stprintf_s(szTemp, _T("Version 4.x: v%s (sp%i)"), szVersion, iNetfx40SPLevel);
		else
			_stprintf_s(szTemp, _T("Version 4.x: v%s"), szVersion);
	}
	else if (IsNetfx40ClientInstalled())
	{
		memset(szVersion, 0, sizeof(szVersion));
		int iNetfx40SPLevel = GetNetfx40ClientSPLevel(szVersion);

		if (iNetfx40SPLevel > 0)
			_stprintf_s(szTemp, _T("Version 4.x: v%s (sp%i) Client Profile"), szVersion, iNetfx40SPLevel);
		else
			_stprintf_s(szTemp, _T("Version 4.x: v%s Client Profile"), szVersion);
	}
	else
		_stprintf_s(szTemp, _T("Version 4.x: Not Installed"));

	lstrcat(szMessage, szTemp);
	lstrcat(szMessage, "\n");

	MessageBox(NULL, szMessage, _T("DotNet Version Information v4.6"), MB_OK | MB_ICONINFORMATION);

	return 0;
}
