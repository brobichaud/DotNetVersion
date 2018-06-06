#include "registrykeys.h"

// Constants that represent registry key names and value names to use for detection
const TCHAR *g_szNetfx4xRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full");
const TCHAR *g_szNetfx4xClientRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Client");
const TCHAR *g_szNetfx4xRegValueName = _T("Install");
const TCHAR *g_szNetfx4xSpRegValueName = _T("SP");
const TCHAR *g_szNetfx4xVersRegValueName = _T("Version");
const TCHAR *g_szNetfx4xReleaseRegValueName = _T("Release");

const TCHAR *g_szNetfx35RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.5");
const TCHAR *g_szNetfx35RegValueName = _T("Install");
const TCHAR *g_szNetfx35SpRegValueName = _T("SP");
const TCHAR *g_szNetfx35VersRegValueName = _T("Version");

const TCHAR *g_szNetfx30OrigRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.0\\Setup");
const TCHAR *g_szNetfx30OrigRegValueName = _T("InstallSuccess");
const TCHAR *g_szNetfx30RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.0");
const TCHAR *g_szNetfx30RegValueName = _T("Install");
const TCHAR *g_szNetfx30SpRegValueName = _T("SP");
const TCHAR *g_szNetfx30VersRegValueName = _T("Version");

const TCHAR *g_szNetfx20RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727");
const TCHAR *g_szNetfx20RegValueName = _T("Install");
const TCHAR *g_szNetfx20SpRegValueName = _T("SP");
const TCHAR *g_szNetfx20VersRegValueName = _T("Version");

const TCHAR *g_szNetfx11RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322");
const TCHAR *g_szNetfx11RegValueName = _T("Install");
const TCHAR *g_szNetfx11SpRegValueName = _T("SP");

const TCHAR *g_szNetfx10RegKeyName = _T("Software\\Microsoft\\.NETFramework\\Policy\\v1.0");
const TCHAR *g_szNetfx10RegKeyValue = _T("3705");
const TCHAR *g_szNetfx10SpMSIRegKeyName = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{78705f0d-e8db-4b2d-8193-982bdda15ecd}");
const TCHAR *g_szNetfx10SpOCMRegKeyName = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{FDC11A6F-17D1-48f9-9EA3-9051954BAA24}");
const TCHAR *g_szNetfx10SpRegValueName = _T("Version");

