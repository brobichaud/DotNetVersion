#include "registrykeys.h"
#include "support.h"

/******************************************************************
Function Name:	GetNetfx4xSpLevel
******************************************************************/
int GetNetfx4xSpLevel(char* szVersion)
{
	DWORD dwRegValue = 0;

	lstrcpy(szVersion, "");

	RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xRegKeyName, g_szNetfx4xVersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xRegKeyName, g_szNetfx4xSpRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx40FullSpLevel
******************************************************************/
int GetNetfx40FullSpLevel(char* szVersion)
{
	DWORD dwRegValue = 0;

	lstrcpy(szVersion, "");

	RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xRegKeyName, g_szNetfx4xVersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xRegKeyName, g_szNetfx4xSpRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx40ClientSpLevel
******************************************************************/
int GetNetfx40ClientSpLevel(char* szVersion)
{
	DWORD dwRegValue = 0;

	lstrcpy(szVersion, "");

	RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xClientRegKeyName, g_szNetfx4xVersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx4xClientRegKeyName, g_szNetfx4xSpRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx35SpLevel
******************************************************************/
int GetNetfx35SpLevel(char* szVersion)
{
	DWORD dwRegValue = 0;

	lstrcpy(szVersion, "");

	RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx35RegKeyName, g_szNetfx35VersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);
	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx35RegKeyName, g_szNetfx35SpRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx30SpLevel
******************************************************************/
int GetNetfx30SpLevel(char* szVersion)
{
	DWORD dwRegValue = 0;

	lstrcpy(szVersion, "");

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx30RegKeyName, g_szNetfx30SpRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
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
Function Name:	GetNetfx20SpLevel
******************************************************************/
int GetNetfx20SpLevel(char* szVersion)
{
	DWORD dwRegValue = 0;

	// default version
	lstrcpy(szVersion, "2.0.50727");

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx20RegKeyName, g_szNetfx20SpRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (dwRegValue > 0)
			RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx20RegKeyName, g_szNetfx20VersRegValueName, NULL, (LPBYTE)szVersion, MAX_PATH);

		return (int)dwRegValue;
	}

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx11SpLevel
Uses the detection method recommended at
http://blogs.msdn.com/astebner/archive/2004/09/14/229574.aspx
to determine what service pack for the .NET Framework 1.1 is installed on the machine
******************************************************************/
int GetNetfx11SpLevel(char* szVersion)
{
	DWORD dwRegValue = 0;

	// default version, we have no way of obtaining anything else
	lstrcpy(szVersion, "1.1.4322");

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx11RegKeyName, g_szNetfx11SpRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
		return (int)dwRegValue;

	// could not find registry value, default to 0
	return 0;
}

/******************************************************************
Function Name:	GetNetfx10SpLevel
Uses the detection method recommended at
http://blogs.msdn.com/astebner/archive/2004/09/14/229802.aspx
to determine what service pack for the .NET Framework 1.0 is installed on the machine
******************************************************************/
int GetNetfx10SpLevel()
{
	TCHAR szRegValue[MAX_PATH];
	TCHAR *pszSpLevel = NULL;
	int iRetValue = 0;
	bool bRegistryRetVal = false;

	if (IsCurrentOSTabletMedCenter())
		bRegistryRetVal = RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx10SpOCMRegKeyName, g_szNetfx10SpRegValueName, NULL, (LPBYTE)szRegValue, MAX_PATH);
	else
		bRegistryRetVal = RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx10SpMSIRegKeyName, g_szNetfx10SpRegValueName, NULL, (LPBYTE)szRegValue, MAX_PATH);

	if (bRegistryRetVal)
	{
		// This registry value should be of the format
		// #,#,#####,# where the last # is the SP level
		// Try to parse off the last # here
		pszSpLevel = _tcsrchr(szRegValue, _T(','));
		if (NULL != pszSpLevel)
		{
			// Increment the pointer to skip the comma
			pszSpLevel++;

			// Convert the remaining value to an integer
			iRetValue = _tstoi(pszSpLevel);
		}
	}

	return iRetValue;
}
