#pragma once
#include <tchar.h>
#include <windows.h>

bool RegistryGetValue(HKEY hk, const TCHAR * pszKey, const TCHAR * pszValue, DWORD dwType, LPBYTE data, DWORD dwSize);
bool IsCurrentOSTabletMedCenter();
