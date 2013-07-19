#ifndef VRPrinter_PH_INCLUDED
#define VRPrinter_PH_INCLUDED

#include "vxrexx.h"

#ifdef VRPrinter_Class_Source

VRMESSAGEMAP VRPrinterMessageMap[] =
  {
    { WM_INITCAP, NULL, "vrWM_INITCAP" },
    { WM_NULL, NULL, NULL }
  };

#else

extern VRMESSAGEMAP VRPrinterMessageMap[];

#endif


extern const VRPROPENTRY VRPrinterPropertyList[];
extern const VRMETHENTRY VRPrinterMethodList[];

#ifdef VRPrinter_Class_Source

#include "core.ph"
#include "vxcdata.h"
SOM_Scope bool SOMLINK VRPrinterClass_vrLocalClassInit( M_VRPrinter *class )
  {
    bool ok;
    get_rexx_properties( class ) = (PVRPROPENTRY) VRPrinterPropertyList;
    get_rexx_methods( class ) = (PVRMETHENTRY) VRPrinterMethodList;
    get_parent_class( class ) = _somGetParent( class );
    get_is_virtual( class ) = FALSE;
    get_default_prefix( class ) = "PRT";

    get_is_predefined( class ) = FALSE;
    VRInheritMessageMap( class, 20 );

    ok = VRAddToMessageMap( class, VRPrinterMessageMap );
    if( ok ){
        ok = VRAddStandardMap( class );
    }

    VRPrinterClass_vrLocalWindowClassInit( class );
    return( TRUE );
  }

#endif


#endif
