/* 
 * File:   main.cpp
 * Author: romanius
 *
 * Created on 1 Апрель 2013 г., 14:34
 */

#include "SDK/plugin.h"
#include "main.h"

typedef void (*logprintf_t)(char* format, ...);
extern logprintf_t logprintf;

logprintf_t logprintf;
void **ppPluginData;
extern void *pAMXFunctions;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
	return SUPPORTS_VERSION;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load( void **ppData ) 
{
	pAMXFunctions = ppData[ PLUGIN_DATA_AMX_EXPORTS ];
	logprintf = (logprintf_t)ppData[ PLUGIN_DATA_LOGPRINTF ];
    
    //CCache *cc = new CCache();
    
    //cc->Add(0xABCD, 0xAABBCCDD);
    
    CMemory *cm = new CMemory();
    cm->PrintInfo();
    
    
	logprintf("-> RussianNicks loaded.\n");
    
    
    
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload( )
{
    //sampgdk_finalize();
    
	logprintf("-> RussianNicks unloaded.\n");
}

