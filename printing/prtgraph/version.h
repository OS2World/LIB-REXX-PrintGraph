
#define DLLNAME "VRPRINT"

#define MINIMUM_VXREXX_LEVEL 210
#define LEVEL_ERRORMSG "This object library requires VX-REXX version 2.10 or higher."
#define LEVEL_TITLE "VRPRINT Object Library"

#define VERSION 100
#define VERSION_STRING "1.00"

#define VersionEntry _VRPRINT_VERSION_INFO_

#ifdef MAKELIB
#define SomInit    VRPRINT_SOMInitModule
#define SomUninit  VRPRINT_SOMUninitModule
#else
#define SomInit    SOMInitModule
#define SomUninit  SOMUninitModule
#endif

