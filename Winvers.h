#if !defined (_WinVers_H_)
#define _WinVers_H_

#include <windows.h>
#include <winreg.h>

//////////////////////////////////////////////////////////////////////////////
//
// This class is used to obtain version information for the currently running
// operating system.  Simply instantiate an object of this class and call its
// methods to obtain the various version attributes.
//
class CWindowsVersion
{
// Construction
public:
	CWindowsVersion();      // default constructor
	~CWindowsVersion() {};  // destructor

// Operations
public:
	int   GetPlatform();    // returns Platform id
	float GetVersion();     // returns Version #
	int   GetMajor();       // returns major Version #
	int   GetMinor();       // returns minor Version #
	int   GetServicePackMajor();  // returns major Version #
	int   GetServicePackMinor();  // returns minor Version #
	int   GetBuild();       // returns Build #
	bool  IsServer();       // returns true if Server version
	LPCSTR GetPlatformFmt();// returns the formatted platform
	LPCSTR GetVersionFmt(); // returns Version # formatted in a string
	LPCSTR GetMiscInfo();   // returns misc vers info
	LPCSTR GetProcessorArchitecture();  // returns the processor architecture (x86 vs x64)

// Implementation
private:
	void GetDetails10();
	void GetDetails8();
	void GetDetails7();
	void GetDetailsVista();
	void GetDetails2003();
	void GetDetails2000();
	void GetDetailsXP();
	void DetectProductInfo();

// Attributes (Implementation)
private:
	OSVERSIONINFOEX m_osV;
	int m_nPlatform;        // Platform type
	float m_fVersion;       // actual version number
	int m_nMajorVers;       // major version number
	int m_nMinorVers;       // minor version number
	int m_nSpMajor;			// service pack major number
	int m_nSpMinor;			// service pack minor number
	char m_szVersionFmt[_MAX_PATH]; // formatted full version string
	char m_szPlatform[1024]; // worksation or server type
	int m_nBuild;           // build number
	bool m_bIsServer;       // true if Server edition
	char m_szMiscInfo[_MAX_PATH];   // CSDVersion misc info data
	char m_szSemiAnnual[_MAX_PATH]; // semi-annual version
};

#endif
