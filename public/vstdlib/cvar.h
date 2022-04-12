//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//

#if !defined( CVAR_H )
#define CVAR_H
#ifdef _WIN32
#pragma once
#endif

#include "vstdlib/vstdlib.h"
#include "icvar.h"


//-----------------------------------------------------------------------------
// Returns a CVar dictionary for tool usage
//-----------------------------------------------------------------------------
VSTDLIB_INTERFACE CreateInterfaceFn VStdLib_GetICVarFactory();

#define CVAR_QUERY_INTERFACE_VERSION "VEngineCvar002"

#endif // CVAR_H
