//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//

#include "vstdlib/cvar.h"
#include <ctype.h>
#include "tier0/icommandline.h"
#include "tier1/utlrbtree.h"
#include "tier1/strtools.h"
#include "tier1/KeyValues.h"
#include "tier1/convar.h"
#include "tier0/vprof.h"
#include "tier1/tier1.h"
#include "tier1/utlbuffer.h"

#ifdef _X360
#include "xbox/xbox_console.h"
#endif

#ifdef _LINUX
#include <wctype.h>
#include <wchar.h>
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Factor for CVars 
//-----------------------------------------------------------------------------

class CDefaultCvar : public ICvar
{
public:
	virtual bool Connect(CreateInterfaceFn factory);
	virtual void Disconnect();
	virtual void* QueryInterface(const char* pInterfaceName);
	virtual InitReturnVal_t Init();
	virtual void Shutdown();

	virtual void RegisterConCommandBase(ConCommandBase* pVar);
	virtual const char* GetCommandLineValue(const char* pVarName);
	virtual ConVar* FindVar(const char* var_name);
	virtual const ConVar* FindVar(const char* var_name) const;
	virtual ConCommandBase* GetCommands(void);
	virtual void UnlinkVariables(int flag);

	virtual void InstallGlobalChangeCallback(FnChangeCallback callback);
	virtual void CallGlobalChangeCallback(ConVar* var, const char* pOldString);
private:
	CUtlVector<FnChangeCallback> m_GlobalChangeCallbacks;
	ConCommandBase* m_pConCommandList;
};

static CDefaultCvar s_Cvar;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CDefaultCvar, ICvar, CVAR_QUERY_INTERFACE_VERSION, s_Cvar);

// WHAT THE FUC?
static ICvar* g_pCustomICvarIF;
static ICvar* pCV;

DLL_EXPORT ICvar *GetCVarIF()
{
	return g_pCustomICvarIF;
}

DLL_EXPORT void SetCVarIF(ICvar *pCVarIF)
{
	if ( pCVarIF )
		g_pCustomICvarIF = pCVarIF;
	else
		g_pCustomICvarIF = pCV;
}

//-----------------------------------------------------------------------------
// Returns a CVar dictionary for tool usage
//-----------------------------------------------------------------------------
CreateInterfaceFn VStdLib_GetICVarFactory()
{
	return Sys_GetFactoryThis();
}

void CDefaultCvar::RegisterConCommandBase(ConCommandBase* pVar)
{
	//TODO 
}

//-----------------------------------------------------------------------------
// Methods of IAppSystem
//-----------------------------------------------------------------------------
bool CDefaultCvar::Connect( CreateInterfaceFn factory )
{
	return 1;
}

void CDefaultCvar::Disconnect()
{
}

void CDefaultCvar::Shutdown()
{
}

void *CDefaultCvar::QueryInterface( const char *pInterfaceName )
{
	if ( !Q_stricmp( pInterfaceName, CVAR_QUERY_INTERFACE_VERSION ) )
		return (ICvar*)this;
	
	return nullptr;
}

InitReturnVal_t CDefaultCvar::Init()
{
	return INIT_OK;
}


//-----------------------------------------------------------------------------
// Purpose Finds ConVars
//-----------------------------------------------------------------------------
const ConVar *CDefaultCvar::FindVar( const char *var_name ) const
{
	const ConCommandBase *var = ConCommandBase::FindCommand( var_name );
	if ( !var || var->IsCommand() )
		return NULL;
	
	return static_cast<const ConVar*>(var);
}

ConVar *CDefaultCvar::FindVar( const char *var_name )
{
	ConCommandBase *var = (ConCommandBase*)ConCommandBase::FindCommand( var_name );
	if ( !var || var->IsCommand() )
		return NULL;
	
	return static_cast<ConVar*>( var );
}


const char* CDefaultCvar::GetCommandLineValue( const char *pVariableName )
{
	int nLen = Q_strlen(pVariableName);
	char *pSearch = (char*)stackalloc( nLen + 2 );
	pSearch[0] = '+';
	memcpy( &pSearch[1], pVariableName, nLen + 1 );
	return CommandLine()->ParmValue( pSearch );
}

ConCommandBase* CDefaultCvar::GetCommands( void )
{
	return m_pConCommandList;
}

void CDefaultCvar::UnlinkVariables(int flag)
{
}


void CDefaultCvar::InstallGlobalChangeCallback( FnChangeCallback callback )
{
	Assert( callback && m_GlobalChangeCallbacks.Find( callback ) < 0 );
	m_GlobalChangeCallbacks.AddToTail( callback );
}

void CDefaultCvar::CallGlobalChangeCallback(ConVar* var, const char* pOldString)
{
	int nCallbackCount = m_GlobalChangeCallbacks.Count();
	for (int i = 0; i < nCallbackCount; ++i)
	{
		(*m_GlobalChangeCallbacks[i])(var, pOldString);
	}
}