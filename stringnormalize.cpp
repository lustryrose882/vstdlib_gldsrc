//===== Copyright � 1996-2005, BWGS Corporation, All rights reserved. ======//
//
// Purpose: nothing
//
//===========================================================================//

#include "public/tier0/validator.h"
#include "public/tier1/tier1.h"

class IStringNormalization
{
public:
	virtual void Initialize() = 0;
	virtual char const* GetCommandLineValue(char const* pVariableName) = 0;
	virtual int Normalize(bool bAggressive, const wchar_t* pwchSrc, wchar_t* pwchDest, int cchDest) = 0;
	virtual int Normalize(bool bAggressive, const char* pchSrc, char* pchDest, int cchDest) = 0;
	virtual void ValidateStatics(CValidator* const validator, char* pchName) = 0;
	virtual int Test_BValidateStructures() = 0;

};

class CStringNormalization : IStringNormalization 
{
	virtual void Initialize();
	virtual int Normalize(bool bAggressive, const wchar_t* pwchSrc, wchar_t* pwchDest, int cchDest);
	virtual int Normalize(bool bAggressive, const char* pchSrc, char* pchDest, int cchDest);
	virtual void ValidateStatics(CValidator* const validator, char* pchName);
	virtual int Test_BValidateStructures();
};

void CStringNormalization::Initialize()
{
}

void CStringNormalization::ValidateStatics(CValidator* const validator, char* pchName)
{
}

int CStringNormalization::Normalize(bool bAggressive, const wchar_t* pwchSrc, wchar_t* pwchDest, int cchDest)
{
	return 0;
}

int CStringNormalization::Normalize(bool bAggressive, const char* pchSrc, char* pchDest, int cchDest)
{
	return 0;
}

int CStringNormalization::Test_BValidateStructures()
{
	return 0;
}
