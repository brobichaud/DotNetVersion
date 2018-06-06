#include "WinVers.h"

#ifndef VER_SUITE_WH_SERVER
#define VER_SUITE_WH_SERVER 0x00008000 // for Windows Home Server
#endif

typedef BOOL (WINAPI *PGetProductInfo)(DWORD, DWORD, DWORD, DWORD, PDWORD);

//////////////////////////////////////////////////////////////////////////////
//
// Retrieves the version info data and fills in class members
//
CWindowsVersion::CWindowsVersion()
{
	// initialize members
	m_nPlatform = 0;
	m_fVersion = (float)0;
	m_nMajorVers = 0;
	m_nMinorVers = 0;
	m_nBuild = 0;
	m_bIsServer = false;
	ZeroMemory(&m_szVersionFmt, sizeof(m_szVersionFmt));
	ZeroMemory(&m_szMiscInfo, sizeof(m_szMiscInfo));
	ZeroMemory(&m_szPlatform, sizeof(m_szPlatform));

	ZeroMemory(&m_osV, sizeof(OSVERSIONINFOEX));
	m_osV.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (!GetVersionEx((OSVERSIONINFO *)&m_osV))
		return;

	// fill in member variables
	m_nPlatform = m_osV.dwPlatformId;
	m_fVersion = m_osV.dwMajorVersion + ((float)m_osV.dwMinorVersion / 100);
	m_nMajorVers = m_osV.dwMajorVersion;
	m_nMinorVers = m_osV.dwMinorVersion;
	m_nSpMajor = m_osV.wServicePackMajor;
	m_nSpMinor = m_osV.wServicePackMinor;
	m_nBuild = (int) LOWORD(m_osV.dwBuildNumber);
	lstrcpy(m_szMiscInfo, m_osV.szCSDVersion);

	// get more details on the platform version
	// as long as we are running a 32bit OS, earlier versions not supported.
	if (m_osV.dwPlatformId != VER_PLATFORM_WIN32_NT)
		return;

	// determine the platform
	if (GetMajor() == 10 && GetMinor() == 0)  // Windows 10
		GetDetails10();
	if (GetMajor() == 6 && GetMinor() == 2)  // Windows 8 & Server 2012
		GetDetails8();
	else if (GetMajor() == 6 && GetMinor() == 1)  // Windows 7 & Server 2008 R2
		GetDetails7();
	else if (GetMajor() == 6 && GetMinor() == 0)  // Windows Vista & Server 2008
		GetDetailsVista();
	else if (GetMajor() == 5 && GetMinor() == 2)  // Windows Home Server & Server 2003
		GetDetails2003();
	else if (GetMajor() == 5 && GetMinor() == 0)  // Windows 2000
		GetDetails2000();
	else if (GetMajor() == 5)  // Windows XP
		GetDetailsXP();
}

//////////////////////////////////////////////////////////////////////////////
//
// Gets the version details for Windows 10
//
void CWindowsVersion::GetDetails10()
{
	if (m_osV.wProductType == VER_NT_WORKSTATION)
	{
		lstrcpy(m_szPlatform, "Windows 10");
	}
	else
	{
		m_bIsServer = true;
		lstrcpy(m_szPlatform, "Windows Server 2016");
	}

	DetectProductInfo();

	// append the processor architecture
	lstrcat(m_szPlatform, " ");
	lstrcat(m_szPlatform, GetProcessorArchitecture());
}

//////////////////////////////////////////////////////////////////////////////
//
// Gets the version details for Windows 8 and Server 2012
//
void CWindowsVersion::GetDetails8()
{
	if (m_osV.wProductType == VER_NT_WORKSTATION)
	{
		if (m_nBuild >= 9200)
			lstrcpy(m_szPlatform, "Windows 8.1");
		else
			lstrcpy(m_szPlatform, "Windows 8");
	}
	else
	{
		m_bIsServer = true;
		if (m_nBuild >= 9200)
			lstrcpy(m_szPlatform, "Windows Server 2012 R2");
		else
			lstrcpy(m_szPlatform, "Windows Server 2012");
	}

	DetectProductInfo();

	// append the processor architecture
	lstrcat(m_szPlatform, " ");
	lstrcat(m_szPlatform, GetProcessorArchitecture());
}

//////////////////////////////////////////////////////////////////////////////
//
// Gets the version details for Windows 7 and Server 2008 R2
//
void CWindowsVersion::GetDetails7()
{
	if (m_osV.wProductType == VER_NT_WORKSTATION)
	{
		lstrcpy(m_szPlatform, "Windows 7");
	}
	else
	{
		m_bIsServer = true;
		lstrcpy(m_szPlatform, "Windows Server 2008 R2");
	}

	DetectProductInfo();

	// append the processor architecture
	lstrcat(m_szPlatform, " ");
	lstrcat(m_szPlatform, GetProcessorArchitecture());
}

//////////////////////////////////////////////////////////////////////////////
//
// Gets the version details for Windows Vista and Server 2008
//
void CWindowsVersion::GetDetailsVista()
{
	if (m_osV.wProductType == VER_NT_WORKSTATION)
	{
		lstrcpy(m_szPlatform, "Windows Vista");
	}
	else
	{
		m_bIsServer = true;
		lstrcpy(m_szPlatform, "Windows Server 2008");
	}

	DetectProductInfo();

	// append the processor architecture
	lstrcat(m_szPlatform, " ");
	lstrcat(m_szPlatform, GetProcessorArchitecture());
}

//////////////////////////////////////////////////////////////////////////////
//
// Gets the version details for Server 2003
//
void CWindowsVersion::GetDetails2003()
{
	m_bIsServer = true;

	if (m_osV.wSuiteMask & VER_SUITE_WH_SERVER)
		lstrcpy(m_szPlatform, "Windows Home Server");
	else
	{
		if (GetSystemMetrics(SM_SERVERR2) != 0)
			lstrcpy(m_szPlatform, "Windows Server 2003 R2");
		else
			lstrcpy(m_szPlatform, "Windows Server 2003");

		if (m_osV.wSuiteMask & VER_SUITE_DATACENTER)
			lstrcat(m_szPlatform, " Datacenter");
		else if (m_osV.wSuiteMask & VER_SUITE_ENTERPRISE)
			lstrcat(m_szPlatform, " Enterprise");
		else if (m_osV.wSuiteMask & VER_SUITE_BLADE)
			lstrcat(m_szPlatform, " Web");
		else if (m_osV.wSuiteMask & VER_SUITE_COMPUTE_SERVER)
			lstrcat(m_szPlatform, " Compute Cluster");
		else if (m_osV.wSuiteMask & VER_SUITE_STORAGE_SERVER)
			lstrcat(m_szPlatform, " Storage Server");
		else
			lstrcat(m_szPlatform, " Standard");
	}

	// append the processor architecture
	lstrcat(m_szPlatform, " ");
	lstrcat(m_szPlatform, GetProcessorArchitecture());
}

//////////////////////////////////////////////////////////////////////////////
//
// Gets the version details for Windows 2000
//
void CWindowsVersion::GetDetails2000()
{
	lstrcpy(m_szPlatform, "Windows 2000");

	if (m_osV.wProductType == VER_NT_WORKSTATION)
		lstrcat(m_szPlatform, " Professional");
	else
	{
		m_bIsServer = true;
		if (m_osV.wSuiteMask & VER_SUITE_DATACENTER)
			lstrcat(m_szPlatform, " Datacenter Server");
		else if (m_osV.wSuiteMask & VER_SUITE_ENTERPRISE)
			lstrcat(m_szPlatform, " Advanced Server");
		else
			lstrcat(m_szPlatform, " Server");
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// Gets the version details for Windows XP
//
void CWindowsVersion::GetDetailsXP()
{
	lstrcpy(m_szPlatform, "Windows XP");

	if (GetSystemMetrics(SM_MEDIACENTER) != 0)
		lstrcat(m_szPlatform, " Media Center Edition");
	else if (GetSystemMetrics(SM_STARTER) != 0)
		lstrcat(m_szPlatform, " Starter Edition");
	else if (GetSystemMetrics(SM_TABLETPC) != 0)
		lstrcat(m_szPlatform, " Tablet PC Edition");
	else
	{
		if (m_osV.wSuiteMask & VER_SUITE_PERSONAL)
			lstrcat(m_szPlatform, " Home");
		else
			lstrcat(m_szPlatform, " Professional");
	}

	if (GetMinor() == 2)
		lstrcat(m_szPlatform, " x64");
	else
		lstrcat(m_szPlatform, " x86");
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the processor architecture string
//
LPCSTR CWindowsVersion::GetProcessorArchitecture()
{
	// append processor architecture
	SYSTEM_INFO sysInfo;
	GetNativeSystemInfo(&sysInfo);
	if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
		return "x86";
	else
		return "x64";
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the platform number
//
int CWindowsVersion::GetPlatform()
{
	return m_nPlatform;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the version number in float format
//
float CWindowsVersion::GetVersion()
{
	return m_fVersion;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the major version number
//
int CWindowsVersion::GetMajor()
{
	return m_nMajorVers;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the minor version number
//
int CWindowsVersion::GetMinor()
{
	return m_nMinorVers;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the ServicePack major version number
//
int CWindowsVersion::GetServicePackMajor()
{
	return m_nSpMajor;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the ServicePack minor version number
//
int CWindowsVersion::GetServicePackMinor()
{
	return m_nSpMinor;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the formatted platform
//
LPCSTR CWindowsVersion::GetPlatformFmt()
{
	return m_szPlatform;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the version number formatted in a string
//
LPCSTR CWindowsVersion::GetVersionFmt()
{
	if ((GetServicePackMajor() > 0) && (GetServicePackMinor() > 0))
		wsprintf(m_szVersionFmt, "%s SP%d.%d\nVersion %d.%d Build %d", m_szPlatform, m_nSpMajor, m_nSpMinor, m_nMajorVers, m_nMinorVers, m_nBuild);
	else if (GetServicePackMajor() > 0)
		wsprintf(m_szVersionFmt, "%s SP%d\nVersion %d.%d Build %d", m_szPlatform, m_nSpMajor, m_nMajorVers, m_nMinorVers, m_nBuild);
	else
		wsprintf(m_szVersionFmt, "%s\nVersion %d.%d Build %d", m_szPlatform, m_nMajorVers, m_nMinorVers, m_nBuild);
	return m_szVersionFmt;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns the build number
//
int CWindowsVersion::GetBuild()
{
	return m_nBuild;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns true if this is a Server, else false
//
bool CWindowsVersion::IsServer()
{
	return m_bIsServer;
}

//////////////////////////////////////////////////////////////////////////////
//
// Returns misc version info.  For NT this typically is the service pack
// number.
//
LPCSTR CWindowsVersion::GetMiscInfo()
{
	return m_szMiscInfo;
}

//////////////////////////////////////////////////////////////////////////////
//
// Fills in the product type if available
//
void CWindowsVersion::DetectProductInfo()
{
	PGetProductInfo lpProducInfo = (PGetProductInfo)GetProcAddress(GetModuleHandle("kernel32.dll"), "GetProductInfo");
	if (lpProducInfo != NULL)
	{
		DWORD prodType = 0;
		if (lpProducInfo(m_osV.dwMajorVersion, m_osV.dwMinorVersion, m_osV.wServicePackMajor, m_osV.wServicePackMinor, &prodType))
		{
			//// debugging, show actual product type number
			//char num[32];
			//wsprintf(num, " (%d)", prodType);
			//lstrcat(m_szPlatform, num);

			switch (prodType)
			{
				case PRODUCT_PROFESSIONAL_WMC:
					lstrcat(m_szPlatform, " Pro with Media Center");
					break;
				case PRODUCT_PROFESSIONAL:
					lstrcat(m_szPlatform, " Professional");
					break;
				case PRODUCT_BUSINESS:
				case PRODUCT_BUSINESS_N:
					lstrcat(m_szPlatform, " Business");
					break;
				case PRODUCT_CLUSTER_SERVER:
					lstrcat(m_szPlatform, " Cluster");
					break;
				case PRODUCT_DATACENTER_SERVER:
				case PRODUCT_DATACENTER_SERVER_V:
					lstrcat(m_szPlatform, " Datacenter");
					break;
				case PRODUCT_DATACENTER_SERVER_CORE:
				case PRODUCT_DATACENTER_SERVER_CORE_V:
					lstrcat(m_szPlatform, " Datacenter Core");
					break;
				case PRODUCT_ENTERPRISE:
				case PRODUCT_ENTERPRISE_SERVER:
				case PRODUCT_ENTERPRISE_SERVER_V:
				case PRODUCT_ENTERPRISE_SERVER_IA64:
					lstrcat(m_szPlatform, " Enterprise");
					break;
				case PRODUCT_ENTERPRISE_SERVER_CORE:
				case PRODUCT_ENTERPRISE_SERVER_CORE_V:
					lstrcat(m_szPlatform, " Enterprise Core");
					break;
				case PRODUCT_HOME_BASIC:
				case PRODUCT_HOME_BASIC_N:
					lstrcat(m_szPlatform, " Home Basic");
					break;
				case PRODUCT_HOME_PREMIUM:
				case PRODUCT_HOME_PREMIUM_N:
					lstrcat(m_szPlatform, " Home Premium");
					break;
				case PRODUCT_HYPERV:
					lstrcat(m_szPlatform, " HyperV");
					break;
				case PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT:
				case PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING:
				case PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY:
					lstrcat(m_szPlatform, " Medium Business");
					break;
				case PRODUCT_SMALLBUSINESS_SERVER:
				case PRODUCT_SERVER_FOR_SMALLBUSINESS:
				case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
					lstrcat(m_szPlatform, " Small Business");
					break;
				case PRODUCT_SERVER_FOUNDATION:
					lstrcat(m_szPlatform, " Foundation");
					break;
				case PRODUCT_STANDARD_SERVER:
				case PRODUCT_STANDARD_SERVER_V:
					lstrcat(m_szPlatform, " Standard");
					break;
				case PRODUCT_STANDARD_SERVER_CORE:
				case PRODUCT_STANDARD_SERVER_CORE_V:
					lstrcat(m_szPlatform, " Standard Core");
					break;
				case PRODUCT_STARTER:
					lstrcat(m_szPlatform, " Starter");
					break;
				case PRODUCT_STORAGE_EXPRESS_SERVER:
				case PRODUCT_STORAGE_STANDARD_SERVER:
				case PRODUCT_STORAGE_WORKGROUP_SERVER:
				case PRODUCT_STORAGE_ENTERPRISE_SERVER:
					lstrcat(m_szPlatform, " Storage");
					break;
				case PRODUCT_ULTIMATE:
				case PRODUCT_ULTIMATE_N:
					lstrcat(m_szPlatform, " Ultimate");
					break;
				case PRODUCT_WEB_SERVER:
					lstrcat(m_szPlatform, " Web");
					break;
				case PRODUCT_WEB_SERVER_CORE:
					lstrcat(m_szPlatform, " Web Core");
					break;
				case PRODUCT_UNLICENSED:
					lstrcat(m_szPlatform, " Unlicensed");
					break;
			}
		}
	}
}
