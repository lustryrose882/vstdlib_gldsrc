//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//



// These are redefined in the project settings to prevent anyone from using them.
// We in this module are of a higher caste and thus are privileged in their use.

#ifndef IS_VSTDLIB
    #define IS_VSTDLIB
#endif

#ifdef strncpy
	#undef strncpy
#endif

#ifdef _snprintf
	#undef _snprintf
#endif

#if defined( sprintf )
	#undef sprintf
#endif

#if defined( vsprintf )
	#undef vsprintf
#endif

#ifdef _vsnprintf
#ifdef _WIN32
	#undef _vsnprintf
#endif
#endif

#ifdef vsnprintf
#ifndef _WIN32
	#undef vsnprintf
#endif
#endif

#if defined( strcat )
	#undef strcat
#endif

#ifdef strncat
	#undef strncat
#endif

// NOTE: I have to include stdio + stdarg first so vsnprintf gets compiled in
#include <stdio.h>
#include <stdarg.h>

#ifdef POSIX
    #include <ctype.h>
    #include <unistd.h>
    #include <stdlib.h>
    #define _getcwd getcwd
#elif _WIN32
    #include <direct.h>
    #if !defined( _XBOX )
        #define WIN32_LEAN_AND_MEAN
        #define NOMINMAX
        #include <windows.h>
    #else
        #include <xtl.h>
    #endif
#endif
    #ifdef _WIN32
        #ifndef CP_UTF8
        #define CP_UTF8 65001
    #endif
#endif

#ifdef _WIN32
    #define CORRECT_PATH_SEPARATOR '\\'
    #define INCORRECT_PATH_SEPARATOR '/'
#elif POSIX
    #define CORRECT_PATH_SEPARATOR '/'
    #define INCORRECT_PATH_SEPARATOR '\\'
#endif


#include "tier0/dbg.h"
#include <string.h>
#include <stdlib.h>
#include "tier0/basetypes.h"
#include "tier1/UtlDict.h"

#include "tier0/memdbgon.h"

#undef Q_memset
#undef Q_memcpy
#undef Q_memmove
#undef Q_memcmp
#undef Q_strcpy
#undef Q_strrchr
#undef Q_strcmp
#undef Q_wcscmp
#undef Q_strlen
#undef Q_stricmp
#undef Q_strstr
#undef Q_strupr
#undef Q_strlower
#undef Q_wcslen
#undef Q_strncmp
#undef Q_strcasecmp
#undef Q_strncasecmp
#undef Q_strnicmp
#undef Q_atoi
#undef Q_atof
#undef Q_stristr
#undef Q_strnistr
#undef Q_strnchr
#undef Q_normalizeFloatString
#undef Q_strncpy
#undef Q_snprintf
#undef Q_wcsncpy
#undef Q_strncat
#undef Q_strnlwr
#undef Q_vsnprintf
#undef Q_pretifymem
#undef Q_pretifynum
#undef Q_UTF8ToUnicode
#undef Q_UnicodeToUTF8
#undef Q_hextobinary
#undef Q_binarytohex
#undef Q_FileBase
#undef Q_StripTrailingSlash
#undef Q_StripExtension
#undef Q_DefaultExtension
#undef Q_SetExtension
#undef Q_StripFilename
#undef Q_StripLastDir
#undef Q_UnqualifiedFileName
#undef Q_ComposeFileName
#undef Q_ExtractFilePath
#undef Q_ExtractFileExtension
#undef Q_GetFileExtension
#undef Q_RemoveDotSlashes
#undef Q_MakeAbsolutePath
#undef Q_AppendSlash
#undef Q_IsAbsolutePath	
#undef Q_StrSubst
#undef Q_SplitString
#undef Q_SplitString2
#undef Q_StrSlice
#undef Q_StrLeft
#undef Q_StrRight
#undef Q_FixSlashes
#undef Q_strtowcs
#undef Q_wcstostr
#undef Q_strcat

DLL_EXPORT void Q_FixSlashes( char *pname, char separator = CORRECT_PATH_SEPARATOR );

static void		Q_memset (void *dest, int fill, int count)			{ memset( dest, fill, count ); }
static void		Q_memcpy (void *dest, const void *src, int count)	{ memcpy( dest, src, count ); }
static void		Q_memmove (void *dest, const void *src, int count)	{ memmove( dest, src, count ); }
static int		Q_memcmp (const void *m1, const void *m2, int count){ return memcmp( m1, m2, count ); } 
static int		Q_strlen (const char *str)							{ return (int) strlen ( str ); }
static void		Q_strcpy (char *dest, const char *src)				{ strcpy( dest, src ); }
static int		Q_wcslen(const wchar_t *pwch)						{ return (int)wcslen(pwch); }
static char*	Q_strrchr (const char *s, char c)					{ return strrchr((char *) s, c ); }
static int		Q_strcmp (const char *s1, const char *s2)			{ return strcmp( s1, s2 ); }
static int		Q_wcscmp (const wchar_t *s1, const wchar_t *s2)		{ return wcscmp( s1, s2 ); }
static int		Q_stricmp( const char *s1, const char *s2 )			{ return stricmp( s1, s2 ); }
static char*	Q_strstr( const char *s1, const char *search )		{ return strstr((char *) s1, search ); }
static char*	Q_strupr (char *start)								{ return strupr( start ); }
static char*	Q_strlower (char *start)							{ return strlwr( start ); }

DLL_EXPORT void _Q_memset (const char* file, int line, void *dest, int fill, int count)
{
	Assert( count >= 0 );
	AssertValidWritePtr( dest, count );

	memset(dest,fill,count);
}

DLL_EXPORT void _Q_memcpy (const char* file, int line, void *dest, const void *src, int count)
{
	Assert( count >= 0 );
	AssertValidReadPtr( src, count );
	AssertValidWritePtr( dest, count );

	memcpy( dest, src, count );
}

DLL_EXPORT void _Q_memmove(const char* file, int line, void *dest, const void *src, int count)
{
	Assert( count >= 0 );
	AssertValidReadPtr( src, count );
	AssertValidWritePtr( dest, count );

	memmove( dest, src, count );
}

DLL_EXPORT int _Q_memcmp (const char* file, int line, const void *m1, const void *m2, int count)
{
	Assert( count >= 0 );
	AssertValidReadPtr( m1, count );
	AssertValidReadPtr( m2, count );

	return memcmp( m1, m2, count );
}

DLL_EXPORT int	_Q_strlen(const char* file, int line, const char *str)
{
	AssertValidStringPtr(str);
	return strlen( str );
}

DLL_EXPORT int _Q_wcslen(const char* file, int line, const wchar_t *pwch)
{
	return wcslen( pwch );
}

DLL_EXPORT char *_Q_strrchr(const char* file, int line, const char *s, char c)
{
	AssertValidStringPtr( s );
    int len = Q_strlen(s);
    s += len;
    while (len--)
	if (*--s == c) return (char *)s;
    return 0;
}

DLL_EXPORT int _Q_strcmp (const char* file, int line, const char *s1, const char *s2)
{
	AssertValidStringPtr( s1 );
	AssertValidStringPtr( s2 );

	return strcmp( s1, s2 );
}

DLL_EXPORT int _Q_wcscmp (const char* file, int line, const wchar_t *s1, const wchar_t *s2)
{
	while (1)
	{
		if (*s1 != *s2)
			return -1;              // strings not equal    
		if (!*s1)
			return 0;               // strings are equal
		s1++;
		s2++;
	}
	
	return -1;
}

DLL_EXPORT int	_Q_stricmp(const char* file, int line,  const char *s1, const char *s2 )
{
	AssertValidStringPtr( s1 );
	AssertValidStringPtr( s2 );

	return stricmp( s1, s2 );
}


DLL_EXPORT char *_Q_strstr(const char* file, int line,  const char *s1, const char *search )
{
	AssertValidStringPtr( s1 );
	AssertValidStringPtr( search );

	// Casting the args to (char*) in order to get the overload of strstr() that returns a (char*) instead of (const char *). This is a changed brought about by VS2005. 
	return strstr( (char*)s1, (char*)search );
}

DLL_EXPORT char *_Q_strupr (const char* file, int line, char *start)
{
	AssertValidStringPtr( start );
	return strupr( start );
}


DLL_EXPORT char *_Q_strlower (const char* file, int line, char *start)
{
	AssertValidStringPtr( start );
	return strlwr(start);
}

DLL_EXPORT int Q_strncmp (const char *s1, const char *s2, int count)
{
	Assert( count >= 0 );
	AssertValidStringPtr( s1, count );
	AssertValidStringPtr( s2, count );

	while ( count-- > 0 )
	{
		if ( *s1 != *s2 )
			return *s1 < *s2 ? -1 : 1; // string different
		if ( *s1 == '\0' )
			return 0; // null terminator hit - strings the same
		s1++;
		s2++;
	}

	return 0; // count characters compared the same
}

//Source 2013 version. - Solokiller
DLL_EXPORT char *Q_strnlwr( char *s, size_t count )
{
	// Assert( count >= 0 ); tautology since size_t is unsigned
	AssertValidStringPtr( s, count );

	char* pRet = s;
	if( !s || !count )
		return s;

	while( --count > 0 )
	{
		if( !*s )
			return pRet; // reached end of string

		*s = tolower( *s );
		++s;
	}

	*s = 0; // null-terminate original string at "count-1"
	return pRet;
}


DLL_EXPORT int Q_strncasecmp (const char *s1, const char *s2, int n)
{
	Assert( n >= 0 );
	AssertValidStringPtr( s1 );
	AssertValidStringPtr( s2 );
	
	while ( n-- > 0 )
	{
		int c1 = *s1++;
		int c2 = *s2++;

		if (c1 != c2)
		{
			if (c1 >= 'a' && c1 <= 'z')
				c1 -= ('a' - 'A');
			if (c2 >= 'a' && c2 <= 'z')
				c2 -= ('a' - 'A');
			if (c1 != c2)
				return c1 < c2 ? -1 : 1;
		}
		if ( c1 == '\0' )
			return 0; // null terminator hit - strings the same
	}
	
	return 0; // n characters compared the same
}

DLL_EXPORT int Q_strcasecmp (const char *s1, const char *s2)
{
	AssertValidStringPtr(s1);
	AssertValidStringPtr(s2);

	return Q_strncasecmp (s1, s2, 99999);
}

DLL_EXPORT int Q_strnicmp (const char *s1, const char *s2, int n)
{
	Assert( n >= 0 );
	AssertValidStringPtr(s1);
	AssertValidStringPtr(s2);

	return Q_strncasecmp( s1, s2, n );
}

DLL_EXPORT int Q_atoi (const char *str)
{
	AssertValidStringPtr( str );

	int             val;
	int             sign;
	int             c;
	
	Assert( str );
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else
		sign = 1;
		
	val = 0;

//
// check for hex
//
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X') )
	{
		str += 2;
		while (1)
		{
			c = *str++;
			if (c >= '0' && c <= '9')
				val = (val<<4) + c - '0';
			else if (c >= 'a' && c <= 'f')
				val = (val<<4) + c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				val = (val<<4) + c - 'A' + 10;
			else
				return val*sign;
		}
	}
	
//
// check for character
//
	if (str[0] == '\'')
	{
		return sign * str[1];
	}
	
//
// assume decimal
//
	while (1)
	{
		c = *str++;
		if (c <'0' || c > '9')
			return val*sign;
		val = val*10 + c - '0';
	}
	
	return 0;
}


float Q_atof (const char *str)
{
	AssertValidStringPtr( str );
	double			val;
	int             sign;
	int             c;
	int             decimal, total;
	
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else
		sign = 1;
		
	val = 0;

//
// check for hex
//
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X') )
	{
		str += 2;
		while (1)
		{
			c = *str++;
			if (c >= '0' && c <= '9')
				val = (val*16) + c - '0';
			else if (c >= 'a' && c <= 'f')
				val = (val*16) + c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				val = (val*16) + c - 'A' + 10;
			else
				return val*sign;
		}
	}
	
//
// check for character
//
	if (str[0] == '\'')
	{
		return sign * str[1];
	}
	
//
// assume decimal
//
	decimal = -1;
	total = 0;
	while (1)
	{
		c = *str++;
		if (c == '.')
		{
			decimal = total;
			continue;
		}
		if (c <'0' || c > '9')
			break;
		val = val*10 + c - '0';
		total++;
	}

	if (decimal == -1)
		return val*sign;
	while (total > decimal)
	{
		val /= 10;
		total--;
	}
	
	return val*sign;
}

//-----------------------------------------------------------------------------
// Finds a string in another string with a case insensitive test
//-----------------------------------------------------------------------------
char const* Q_stristr( char const* pStr, char const* pSearch )
{
	AssertValidStringPtr(pStr);
	AssertValidStringPtr(pSearch);

	if (!pStr || !pSearch) 
		return 0;

	char const* pLetter = pStr;

	// Check the entire string
	while (*pLetter != 0)
	{
		// Skip over non-matches
		if (tolower((unsigned char)*pLetter) == tolower((unsigned char)*pSearch))
		{
			// Check for match
			char const* pMatch = pLetter + 1;
			char const* pTest = pSearch + 1;
			while (*pTest != 0)
			{
				// We've run off the end; don't bother.
				if (*pMatch == 0)
					return 0;

				if (tolower((unsigned char)*pMatch) != tolower((unsigned char)*pTest))
					break;

				++pMatch;
				++pTest;
			}

			// Found a match!
			if (*pTest == 0)
				return pLetter;
		}

		++pLetter;
	}

	return 0;
}

DLL_EXPORT char* Q_stristr( char* pStr, char const* pSearch )
{
	AssertValidStringPtr( pStr );
	AssertValidStringPtr( pSearch );

	return (char*)Q_stristr( (char const*)pStr, pSearch );
}

//-----------------------------------------------------------------------------
// Finds a string in another string with a case insensitive test w/ length validation
//-----------------------------------------------------------------------------
char const* Q_strnistr( char const* pStr, char const* pSearch, int n )
{
	AssertValidStringPtr(pStr);
	AssertValidStringPtr(pSearch);

	if (!pStr || !pSearch) 
		return 0;

	char const* pLetter = pStr;

	// Check the entire string
	while (*pLetter != 0)
	{
		if ( n <= 0 )
			return 0;

		// Skip over non-matches
		if (tolower(*pLetter) == tolower(*pSearch))
		{
			int n1 = n - 1;

			// Check for match
			char const* pMatch = pLetter + 1;
			char const* pTest = pSearch + 1;
			while (*pTest != 0)
			{
				if ( n1 <= 0 )
					return 0;

				// We've run off the end; don't bother.
				if (*pMatch == 0)
					return 0;

				if (tolower(*pMatch) != tolower(*pTest))
					break;

				++pMatch;
				++pTest;
				--n1;
			}

			// Found a match!
			if (*pTest == 0)
				return pLetter;
		}

		++pLetter;
		--n;
	}

	return 0;
}

const char* Q_strnchr( const char* pStr, char c, int n )
{
	char const* pLetter = pStr;
	char const* pLast = pStr + n;

	// Check the entire string
	while ( (pLetter < pLast) && (*pLetter != 0) )
	{
		if (*pLetter == c)
			return pLetter;
		++pLetter;
	}
	return NULL;
}

DLL_EXPORT void Q_strncpy( char *pDest, char const *pSrc, int maxLen )
{
	Assert( maxLen >= 0 );
	AssertValidWritePtr( pDest, maxLen );
	AssertValidStringPtr( pSrc );

	strncpy( pDest, pSrc, maxLen );
	if ( maxLen > 0 )
	{
		pDest[maxLen-1] = 0;
	}
}

DLL_EXPORT void Q_wcsncpy( wchar_t *pDest, wchar_t const *pSrc, int maxLenInBytes )
{
	Assert( maxLenInBytes >= 0 );
	AssertValidWritePtr( pDest, maxLenInBytes );
	AssertValidReadPtr( pSrc );

	int maxLen = maxLenInBytes / sizeof(wchar_t);

	wcsncpy( pDest, pSrc, maxLen );
	if( maxLen )
	{
		pDest[maxLen-1] = 0;
	}
}


DLL_EXPORT int Q_snprintf( char *pDest, int maxLen, char const *pFormat, ... )
{
	Assert( maxLen >= 0 );
	AssertValidWritePtr( pDest, maxLen );
	AssertValidStringPtr( pFormat );

	va_list marker;

	va_start( marker, pFormat );
#ifdef _WIN32
	int len = _vsnprintf( pDest, maxLen, pFormat, marker );
#elif POSIX
	int len = vsnprintf( pDest, maxLen, pFormat, marker );
#else
	#error "define vsnprintf type."
#endif
	va_end( marker );

	// Len < 0 represents an overflow
	if( len < 0 )
	{
		len = maxLen;
		pDest[maxLen-1] = 0;
	}

	return len;
}


DLL_EXPORT int Q_vsnprintf( char *pDest, int maxLen, char const *pFormat, va_list params )
{
	Assert( maxLen > 0 );
	AssertValidWritePtr( pDest, maxLen );
	AssertValidStringPtr( pFormat );

	int len = _vsnprintf( pDest, maxLen, pFormat, params );

	if( len < 0 )
	{
		len = maxLen;
		pDest[maxLen-1] = 0;
	}

	return len;
}



//-----------------------------------------------------------------------------
// Purpose: If COPY_ALL_CHARACTERS == max_chars_to_copy then we try to add the whole pSrc to the end of pDest, otherwise
//  we copy only as many characters as are specified in max_chars_to_copy (or the # of characters in pSrc if thats's less).
// Input  : *pDest - destination buffer
//			*pSrc - string to append
//			destBufferSize - sizeof the buffer pointed to by pDest
//			max_chars_to_copy - COPY_ALL_CHARACTERS in pSrc or max # to copy
// Output : char * the copied buffer
//-----------------------------------------------------------------------------
DLL_EXPORT char *Q_strncat(char *pDest, const char *pSrc, size_t destBufferSize, int max_chars_to_copy )
{
	size_t charstocopy = (size_t)0;

	Assert( destBufferSize >= 0 );
	AssertValidStringPtr( pDest);
	AssertValidStringPtr( pSrc );
	
	size_t len = strlen(pDest);
	size_t srclen = strlen( pSrc );
	if ( max_chars_to_copy <= COPY_ALL_CHARACTERS )
	{
		charstocopy = srclen;
	}
	else
	{
		charstocopy = (size_t)min( max_chars_to_copy, (int)srclen );
	}

	if ( len + charstocopy >= destBufferSize )
	{
		charstocopy = destBufferSize - len - 1;
	}

	if ( !charstocopy )
	{
		return pDest;
	}

	char *pOut = strncat( pDest, pSrc, charstocopy );
	pOut[destBufferSize-1] = 0;
	return pOut;
}

DLL_EXPORT void Q_strcat(char* dest, const char* src, int cchDest)
{
	Q_strncat(dest, src, cchDest, COPY_ALL_CHARACTERS);
}


//-----------------------------------------------------------------------------
// Purpose: Converts value into x.xx MB/ x.xx KB, x.xx bytes format, including commas
// Input  : value - 
//			2 - 
//			false - 
// Output : char
//-----------------------------------------------------------------------------
#define NUM_PRETIFYMEM_BUFFERS 8
DLL_EXPORT char *Q_pretifymem( float value, int digitsafterdecimal /*= 2*/, bool usebinaryonek /*= false*/ )
{
	static char output[ NUM_PRETIFYMEM_BUFFERS ][ 32 ];
	static int  current;

#ifdef _XBOX
	// undo the confusing metric reports
	usebinaryonek = true;
#endif

	float		onekb = usebinaryonek ? 1024.0f : 1000.0f;
	float		onemb = onekb * onekb;

	char *out = output[ current ];
	current = ( current + 1 ) & ( NUM_PRETIFYMEM_BUFFERS -1 );

	char suffix[ 8 ];

	// First figure out which bin to use
	if ( value > onemb )
	{
		value /= onemb;
		Q_snprintf( suffix, sizeof( suffix ), " MB" );
	}
	else if ( value > onekb )
	{
		value /= onekb;
		Q_snprintf( suffix, sizeof( suffix ), " KB" );
	}
	else
	{
		Q_snprintf( suffix, sizeof( suffix ), " bytes" );
	}

	char val[ 32 ];

	// Clamp to >= 0
	digitsafterdecimal = max( digitsafterdecimal, 0 );

	// If it's basically integral, don't do any decimals
	if ( FloatMakePositive( value - (int)value ) < 0.00001 )
	{
		Q_snprintf( val, sizeof( val ), "%i%s", (int)value, suffix );
	}
	else
	{
		char fmt[ 32 ];

		// Otherwise, create a format string for the decimals
		Q_snprintf( fmt, sizeof( fmt ), "%%.%if%s", digitsafterdecimal, suffix );
		Q_snprintf( val, sizeof( val ), fmt, value );
	}

	// Copy from in to out
	char *i = val;
	char *o = out;

	// Search for decimal or if it was integral, find the space after the raw number
	char *dot = strstr( i, "." );
	if ( !dot )
	{
		dot = strstr( i, " " );
	}

	// Compute position of dot
	int pos = dot - i;
	// Don't put a comma if it's <= 3 long
	pos -= 3;

	while ( *i )
	{
		// If pos is still valid then insert a comma every third digit, except if we would be
		//  putting one in the first spot
		if ( pos >= 0 && !( pos % 3 ) )
		{
			// Never in first spot
			if ( o != out )
			{
				*o++ = ',';
			}
		}

		// Count down comma position
		pos--;

		// Copy rest of data as normal
		*o++ = *i++;
	}

	// Terminate
	*o = 0;

	return out;
}

//-----------------------------------------------------------------------------
// Purpose: Returns a string representation of an integer with commas
//			separating the 1000s (ie, 37,426,421)
// Input  : value -		Value to convert
// Output : Pointer to a static buffer containing the output
//-----------------------------------------------------------------------------
#define NUM_PRETIFYNUM_BUFFERS 8
DLL_EXPORT char *Q_pretifynum( int64 value )
{
	static char output[ NUM_PRETIFYMEM_BUFFERS ][ 32 ];
	static int  current;

	char *out = output[ current ];
	current = ( current + 1 ) & ( NUM_PRETIFYMEM_BUFFERS -1 );

	*out = 0;

	// Render the leading -, if necessary
	if ( value < 0 )
	{
		char *pchRender = out + Q_strlen( out );
		Q_snprintf( pchRender, 32, "-" );
		value = -value;
	}

	// Render quadrillions
	if ( value >= 1000000000000 )
	{
		char *pchRender = out + Q_strlen( out );
		Q_snprintf( pchRender, 32, "%d,", value / 1000000000000 );
	}

	// Render trillions
	if ( value >= 1000000000000 )
	{
		char *pchRender = out + Q_strlen( out );
		Q_snprintf( pchRender, 32, "%d,", value / 1000000000000 );
	}

	// Render billions
	if ( value >= 1000000000 )
	{
		char *pchRender = out + Q_strlen( out );
		Q_snprintf( pchRender, 32, "%d,", value / 1000000000 );
	}

	// Render millions
	if ( value >= 1000000 )
	{
		char *pchRender = out + Q_strlen( out );
		if ( value >= 1000000000 )
			Q_snprintf( pchRender, 32, "%03d,", ( value / 1000000 ) % 1000 );
		else
			Q_snprintf( pchRender, 32, "%d,", ( value / 1000000 ) % 1000 );
	}

	// Render thousands
	if ( value >= 1000 )
	{
		char *pchRender = out + Q_strlen( out );
		if ( value >= 1000000 )
			Q_snprintf( pchRender, 32, "%03d,", ( value / 1000 ) % 1000 );
		else
			Q_snprintf( pchRender, 32, "%d,", ( value / 1000 ) % 1000 );
	}

	// Render units
	char *pchRender = out + Q_strlen( out );
	if ( value > 1000 )
		Q_snprintf( pchRender, 32, "%03d", value % 1000 );
	else
		Q_snprintf( pchRender, 32, "%d", value % 1000 );

	return out;
}


//-----------------------------------------------------------------------------
// Purpose: Converts a UTF8 string into a unicode string
//-----------------------------------------------------------------------------
DLL_EXPORT int Q_UTF8ToUnicode( const char *pUTF8, wchar_t *pwchDest, int cubDestSizeInBytes )
{
	AssertValidStringPtr(pUTF8);
	AssertValidWritePtr(pwchDest);

	pwchDest[0] = 0;
#ifdef _WIN32
	int cchResult = MultiByteToWideChar( CP_UTF8, 0, pUTF8, -1, pwchDest, cubDestSizeInBytes / sizeof(wchar_t) );
#elif POSIX
	int cchResult = mbstowcs( pwchDest, pUTF8, cubDestSizeInBytes / sizeof(wchar_t) );
#endif
	pwchDest[(cubDestSizeInBytes / sizeof(wchar_t)) - 1] = 0;
	return cchResult;
}

//-----------------------------------------------------------------------------
// Purpose: Converts a unicode string into a UTF8 (standard) string
//-----------------------------------------------------------------------------
DLL_EXPORT int Q_UnicodeToUTF8( const wchar_t *pUnicode, char *pUTF8, int cubDestSizeInBytes )
{
	AssertValidStringPtr(pUTF8, cubDestSizeInBytes);
	AssertValidReadPtr(pUnicode);

	pUTF8[0] = 0;
#ifdef _WIN32
	int cchResult = WideCharToMultiByte( CP_UTF8, 0, pUnicode, -1, pUTF8, cubDestSizeInBytes, NULL, NULL );
#elif POSIX
	int cchResult = wcstombs( pUTF8, pUnicode, cubDestSizeInBytes );
#endif
	pUTF8[cubDestSizeInBytes - 1] = 0;
	return cchResult;
}

static unsigned char Q_nibble( char c )
{
	if ( ( c >= '0' ) &&
		 ( c <= '9' ) )
	{
		 return (unsigned char)(c - '0');
	}

	if ( ( c >= 'A' ) &&
		 ( c <= 'F' ) )
	{
		 return (unsigned char)(c - 'A' + 0x0a);
	}

	if ( ( c >= 'a' ) &&
		 ( c <= 'f' ) )
	{
		 return (unsigned char)(c - 'a' + 0x0a);
	}

	return '0';
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *in - 
//			numchars - 
//			*out - 
//			maxoutputbytes - 
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_hextobinary( char const *in, int numchars, byte *out, int maxoutputbytes )
{
	int len = Q_strlen( in );
	numchars = min( len, numchars );
	// Make sure it's even
	numchars = ( numchars ) & ~0x1;

	// Must be an even # of input characters (two chars per output byte)
	Assert( numchars >= 2 );

	memset( out, 0x00, maxoutputbytes );

	byte *p;
	int i;

	p = out;
	for ( i = 0; 
		 ( i < numchars ) && ( ( p - out ) < maxoutputbytes ); 
		 i+=2, p++ )
	{
		*p = ( Q_nibble( in[i] ) << 4 ) | Q_nibble( in[i+1] );		
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *in - 
//			inputbytes - 
//			*out - 
//			outsize - 
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_binarytohex( const byte *in, int inputbytes, char *out, int outsize )
{
	Assert( outsize >= 1 );
	char doublet[10];
	int i;

	out[0]=0;

	for ( i = 0; i < inputbytes; i++ )
	{
		unsigned char c = in[i];
		Q_snprintf( doublet, sizeof( doublet ), "%02x", c );
		Q_strncat( out, doublet, outsize, COPY_ALL_CHARACTERS );
	}
}

#if defined( _WIN32 ) || defined( WIN32 )
#define PATHSEPARATOR(c) ((c) == '\\' || (c) == '/')
#else	//_WIN32
#define PATHSEPARATOR(c) ((c) == '/')
#endif	//_WIN32


//-----------------------------------------------------------------------------
// Purpose: Extracts the base name of a file (no path, no extension, assumes '/' or '\' as path separator)
// Input  : *in - 
//			*out - 
//			maxlen - 
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_FileBase( const char *in, char *out, int maxlen )
{
	Assert( maxlen >= 1 );
	Assert( in );
	Assert( out );

	if ( !in || !in[ 0 ] )
	{
		*out = 0;
		return;
	}

	int len, start, end;

	len = Q_strlen( in );
	
	// scan backward for '.'
	end = len - 1;
	while ( end&& in[end] != '.' && !PATHSEPARATOR( in[end] ) )
	{
		end--;
	}
	
	if ( in[end] != '.' )		// no '.', copy to end
	{
		end = len-1;
	}
	else 
	{
		end--;					// Found ',', copy to left of '.'
	}

	// Scan backward for '/'
	start = len-1;
	while ( start >= 0 && !PATHSEPARATOR( in[start] ) )
	{
		start--;
	}

	if ( start < 0 || !PATHSEPARATOR( in[start] ) )
	{
		start = 0;
	}
	else 
	{
		start++;
	}

	// Length of new sting
	len = end - start + 1;

	int maxcopy = min( len + 1, maxlen );

	// Copy partial string
	Q_strncpy( out, &in[start], maxcopy );
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *ppath - 
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_StripTrailingSlash( char *ppath )
{
	Assert( ppath );

	int len = Q_strlen( ppath );
	if ( len > 0 )
	{
		if ( PATHSEPARATOR( ppath[ len - 1 ] ) )
		{
			ppath[ len - 1 ] = 0;
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *in - 
//			*out - 
//			outSize - 
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_StripExtension( const char *in, char *out, int outSize )
{
	// Find the last dot. If it's followed by a dot or a slash, then it's part of a 
	// directory specifier like ../../somedir/./blah.
	const char *pLastExt = in;
	const char *pTest = strrchr( pLastExt, '.' );
	if ( pTest )
	{
		// This handles things like ".\blah" or "c:\my@email.com\abc\def\geh"
		// Which would otherwise wind up with "" and "c:\my@email", respectively.
		if ( strrchr( in, '\\' ) < pTest && strrchr( in, '/' ) < pTest )
		{
			pLastExt = pTest + 1;
		}
	}

	// Copy up to the last dot.
	if ( pLastExt > in )
	{
		int nChars = pLastExt - in - 1;
		nChars = min( nChars, outSize-1 );
		memcpy( out, in, nChars );
		out[nChars] = 0;
	}
	else
	{
		if ( out != in )
		{
			Q_strncpy( out, in, outSize );
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *path - 
//			*extension - 
//			pathStringLength - 
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_DefaultExtension( char *path, const char *extension, int pathStringLength )
{
	Assert( path );
	Assert( pathStringLength >= 1 );
	Assert( extension );
	Assert( extension[0] == '.' );

	char    *src;

	// if path doesn't have a .EXT, append extension
	// (extension should include the .)
	src = path + Q_strlen(path) - 1;

	while ( !PATHSEPARATOR( *src ) && ( src > path ) )
	{
		if (*src == '.')
		{
			// it has an extension
			return;                 
		}
		src--;
	}

	// Concatenate the desired extension
	Q_strncat( path, extension, pathStringLength, COPY_ALL_CHARACTERS );
}

//-----------------------------------------------------------------------------
// Purpose: Force extension...
// Input  : *path - 
//			*extension - 
//			pathStringLength - 
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_SetExtension( char *path, const char *extension, int pathStringLength )
{
	Q_StripExtension( path, path, pathStringLength );
	Q_DefaultExtension( path, extension, pathStringLength );
}

//-----------------------------------------------------------------------------
// Purpose: Remove final filename from string
// Input  : *path - 
// Output : void  Q_StripFilename
//-----------------------------------------------------------------------------
DLL_EXPORT void  Q_StripFilename (char *path)
{
	int             length;

	length = Q_strlen( path )-1;
	if ( length <= 0 )
		return;

	while ( length > 0 && 
		!PATHSEPARATOR( path[length] ) )
	{
		length--;
	}

	path[ length ] = 0;
}

//TODO: already defined in the header - Solokiller
#ifdef _WIN32
#define CORRECT_PATH_SEPARATOR '\\'
#define INCORRECT_PATH_SEPARATOR '/'
#elif POSIX
#define CORRECT_PATH_SEPARATOR '/'
#define INCORRECT_PATH_SEPARATOR '\\'
#endif


//-----------------------------------------------------------------------------
// Purpose: Changes all '/' or '\' characters into separator
// Input  : *pname - 
//			separator - 
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_FixSlashes( char *pname, char separator /* = CORRECT_PATH_SEPARATOR */ )
{
	while ( *pname )
	{
		if ( *pname == INCORRECT_PATH_SEPARATOR || *pname == CORRECT_PATH_SEPARATOR )
		{
			*pname = separator;
		}
		pname++;
	}
}

bool _Q_IsMeanSpaceW( wchar_t wch )
{
	bool bIsMean = false;

	switch( wch )
	{
	case L'\x0082':	  // BREAK PERMITTED HERE
	case L'\x0083':	  // NO BREAK PERMITTED HERE
	case L'\x00A0':	  // NO-BREAK SPACE
	case L'\x034F':   // COMBINING GRAPHEME JOINER
	case L'\x2000':   // EN QUAD
	case L'\x2001':   // EM QUAD
	case L'\x2002':   // EN SPACE
	case L'\x2003':   // EM SPACE
	case L'\x2004':   // THICK SPACE
	case L'\x2005':   // MID SPACE
	case L'\x2006':   // SIX SPACE
	case L'\x2007':   // figure space
	case L'\x2008':   // PUNCTUATION SPACE
	case L'\x2009':   // THIN SPACE
	case L'\x200A':   // HAIR SPACE
	case L'\x200B':   // ZERO-WIDTH SPACE
	case L'\x200C':   // ZERO-WIDTH NON-JOINER
	case L'\x200D':   // ZERO WIDTH JOINER
	case L'\x2028':   // LINE SEPARATOR
	case L'\x2029':   // PARAGRAPH SEPARATOR
	case L'\x202F':   // NARROW NO-BREAK SPACE
	case L'\x2060':   // word joiner
	case L'\xFEFF':   // ZERO-WIDTH NO BREAK SPACE
	case L'\xFFFC':   // OBJECT REPLACEMENT CHARACTER
		bIsMean = true;
		break;
	}

	return bIsMean;
}

//-----------------------------------------------------------------------------
// Purpose: strips trailing whitespace; returns pointer inside string just past
// any leading whitespace.
//
// bAggresive = true causes this function to also check for "mean" spaces,
// which we don't want in persona names or chat strings as they're disruptive
// to the user experience.
//-----------------------------------------------------------------------------
static wchar_t *StripWhitespaceWorker( int cchLength, wchar_t *pwch, bool *pbStrippedWhitespace, bool bAggressive )
{
	// walk backwards from the end of the string, killing any whitespace
	*pbStrippedWhitespace = false;

	wchar_t *pwchEnd = pwch + cchLength;
	while( --pwchEnd >= pwch )
	{
		if( !iswspace( *pwchEnd ) && ( !bAggressive || !_Q_IsMeanSpaceW( *pwchEnd ) ) )
			break;

		*pwchEnd = 0;
		*pbStrippedWhitespace = true;
	}

	// walk forward in the string
	while( pwch < pwchEnd )
	{
		if( !iswspace( *pwch ) )
			break;

		*pbStrippedWhitespace = true;
		pwch++;
	}

	return pwch;
}

static wchar_t* StripUnprintableWorker( wchar_t* pch, bool* pbStrippedAny )
{
	*pbStrippedAny = false;

	wchar_t* pszSource = pch;
	wchar_t* pszDest = pch;

	for( ; *pszSource; ++pszSource )
	{
		if( *pszSource >= L' ' && !_Q_IsMeanSpaceW( *pszSource ) && *pszSource != L'\x2026' )
		{
			*pszDest++ = *pszSource;
		}
	}

	*pszDest = L'\0';

	*pbStrippedAny = pszSource != pszDest;

	return pch;
}

//-----------------------------------------------------------------------------
// Purpose: strips leading and trailing whitespace
//-----------------------------------------------------------------------------
DLL_EXPORT bool Q_StripPrecedingAndTrailingWhitespace( char *pch )
{
	// convert to unicode
	int cch = Q_strlen( pch );
	int cubDest = ( cch + 1 ) * sizeof( wchar_t );
	wchar_t *pwch = ( wchar_t * ) stackalloc( cubDest );
	int cwch = Q_UTF8ToUnicode( pch, pwch, cubDest );

	bool bStrippedWhitespace = false;
	pwch = StripWhitespaceWorker( cwch - 1, pwch, &bStrippedWhitespace, false /* not aggressive */ );

	// copy back, if necessary
	if( bStrippedWhitespace )
	{
		Q_UnicodeToUTF8( pwch, pch, cch );
	}

	return bStrippedWhitespace;
}

//-----------------------------------------------------------------------------
// Purpose: Strip off the last directory from dirName
// Input  : *dirName - 
//			maxlen - 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
DLL_EXPORT bool Q_StripLastDir( char *dirName, int maxlen )
{
	if( dirName[0] == 0 || 
		!Q_stricmp( dirName, "./" ) || 
		!Q_stricmp( dirName, ".\\" ) )
		return false;
	
	int len = Q_strlen( dirName );

	Assert( len < maxlen );

	// skip trailing slash
	if ( PATHSEPARATOR( dirName[len-1] ) )
	{
		len--;
	}

	while ( len > 0 )
	{
		if ( PATHSEPARATOR( dirName[len-1] ) )
		{
			dirName[len] = 0;
			Q_FixSlashes( dirName, CORRECT_PATH_SEPARATOR );
			return true;
		}
		len--;
	}

	// Allow it to return an empty string and true. This can happen if something like "tf2/" is passed in.
	// The correct behavior is to strip off the last directory ("tf2") and return true.
	if( len == 0 )
	{
		Q_snprintf( dirName, maxlen, ".%c", CORRECT_PATH_SEPARATOR );
		return true;
	}

	return true;
}


//-----------------------------------------------------------------------------
// Purpose: Returns a pointer to the beginning of the unqualified file name 
//			(no path information)
// Input:	in - file name (may be unqualified, relative or absolute path)
// Output:	pointer to unqualified file name
//-----------------------------------------------------------------------------
DLL_EXPORT const char * Q_UnqualifiedFileName( const char * in )
{
	// back up until the character after the first path separator we find,
	// or the beginning of the string
	const char * out = in + strlen( in ) - 1;
	while ( ( out > in ) && ( !PATHSEPARATOR( *( out-1 ) ) ) )
		out--;
	return out;
}

DLL_EXPORT void Q_AppendSlash( char *pStr, int strSize )
{
	int len = Q_strlen( pStr );
	if ( len > 0 && !PATHSEPARATOR(pStr[len-1]) )
	{
		if ( len+1 >= strSize )
			Error( "Q_AppendSlash: ran out of space on %s.", pStr );
		
		pStr[len] = CORRECT_PATH_SEPARATOR;
		pStr[len+1] = 0;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Composes a path and filename together, inserting a path separator
//			if need be
// Input:	path - path to use
//			filename - filename to use
//			dest - buffer to compose result in
//			destSize - size of destination buffer
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_ComposeFileName( const char *path, const char *filename, char *dest, int destSize )
{
	Q_strncpy( dest, path, destSize );
	Q_AppendSlash( dest, destSize );
	Q_strncat( dest, filename, destSize, COPY_ALL_CHARACTERS );
	Q_FixSlashes( dest );
}


//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *path - 
//			*dest - 
//			destSize - 
// Output : void Q_ExtractFilePath
//-----------------------------------------------------------------------------
DLL_EXPORT bool Q_ExtractFilePath (const char *path, char *dest, int destSize )
{
	Assert( destSize >= 1 );
	if ( destSize < 1 )
	{
		return false;
	}

	// Last char
	int len = Q_strlen(path);
	const char *src = path + (len ? len-1 : 0);

	// back up until a \ or the start
	while ( src != path && !PATHSEPARATOR( *(src-1) ) )
	{
		src--;
	}

	int copysize = min( src - path, destSize - 1 );
	memcpy( dest, path, copysize );
	dest[copysize] = 0;

	return copysize != 0 ? true : false;
}

//-----------------------------------------------------------------------------
// Purpose: Returns a pointer to the file extension within a file name string
// Input:	in - file name 
// Output:	pointer to beginning of extension (after the "."), or NULL
//				if there is no extension
//-----------------------------------------------------------------------------
DLL_EXPORT const char * Q_GetFileExtension( const char * path )
{
	const char    *src;

	src = path + strlen(path) - 1;

//
// back up until a . or the start
//
	while (src != path && *(src-1) != '.' )
		src--;

	// check to see if the '.' is part of a pathname
	if (src == path || PATHSEPARATOR( *src ) )
	{		
		return NULL;  // no extension
	}

	return src;
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *path - 
//			*dest - 
//			destSize - 
// Output : void Q_ExtractFileExtension
//-----------------------------------------------------------------------------
DLL_EXPORT void Q_ExtractFileExtension( const char *path, char *dest, int destSize )
{
	*dest = '\0';
	const char * extension = Q_GetFileExtension( path );
	if ( NULL != extension )
		Q_strncpy( dest, extension, destSize );
}

DLL_EXPORT bool Q_RemoveDotSlashes( char *pFilename )
{
	// Get rid of "./"'s
	char *pIn = pFilename;
	char *pOut = pFilename;
	while ( *pIn )
	{
		// The logic on the second line is preventing it from screwing up "../"
		if ( pIn[0] == '.' && PATHSEPARATOR( pIn[1] ) &&
			(pIn == pFilename || pIn[-1] != '.') )
		{
			pIn += 2;
		}
		else
		{
			*pOut = *pIn;
			++pIn;
			++pOut;
		}
	}
	*pOut = 0;


	// Get rid of a trailing "/." (needless).
	int len = strlen( pFilename );
	if ( len > 2 && pFilename[len-1] == '.' && PATHSEPARATOR( pFilename[len-2] ) )
	{
		pFilename[len-2] = 0;
	}

	// Each time we encounter a "..", back up until we've read the previous directory name,
	// then get rid of it.
	pIn = pFilename;
	while ( *pIn )
	{
		if ( pIn[0] == '.' && 
			 pIn[1] == '.' && 
			 (pIn == pFilename || PATHSEPARATOR(pIn[-1])) &&	// Preceding character must be a slash.
			 (pIn[2] == 0 || PATHSEPARATOR(pIn[2])) )			// Following character must be a slash or the end of the string.
		{
			char *pEndOfDots = pIn + 2;
			char *pStart = pIn - 2;

			// Ok, now scan back for the path separator that starts the preceding directory.
			while ( 1 )
			{
				if ( pStart < pFilename )
					return false;

				if ( PATHSEPARATOR( *pStart ) )
					break;

				--pStart;
			}

			// Now slide the string down to get rid of the previous directory and the ".."
			memmove( pStart, pEndOfDots, strlen( pEndOfDots ) + 1 );

			// Start over.
			pIn = pFilename;
		}
		else
		{
			++pIn;
		}
	}
	
	Q_FixSlashes( pFilename );	
	return true;
}

// small helper function shared by lots of modules
DLL_EXPORT bool Q_IsAbsolutePath( const char *pStr )
{
	return ( pStr[0] && pStr[1] == ':' ) || pStr[0] == '/' || pStr[0] == '\\';
}

DLL_EXPORT void Q_MakeAbsolutePath( char *pOut, int outLen, const char *pPath, const char *pStartingDir )
{
	if ( Q_IsAbsolutePath( pPath ) )
	{
		// pPath is not relative.. just copy it.
		Q_strncpy( pOut, pPath, outLen );
	}
	else
	{
		// Make sure the starting directory is absolute..
		if ( pStartingDir && Q_IsAbsolutePath( pStartingDir ) )
		{
			Q_strncpy( pOut, pStartingDir, outLen );
		}
		else
		{
#ifndef _XBOX
			if ( !_getcwd( pOut, outLen ) )
				Error( "Q_MakeAbsolutePath: _getcwd failed." );
#else
			Assert( 0 );
			if ( outLen )
				*pOut = 0;
#endif

			if ( pStartingDir )
			{
				Q_AppendSlash( pOut, outLen );
				Q_strncat( pOut, pStartingDir, outLen, COPY_ALL_CHARACTERS );
			}
		}

		// Concatenate the paths.
		Q_AppendSlash( pOut, outLen );
		Q_strncat( pOut, pPath, outLen, COPY_ALL_CHARACTERS );
	}

	if ( !Q_RemoveDotSlashes( pOut ) )
		Error( "Q_MakeAbsolutePath: tried to \"..\" past the root." );

	Q_FixSlashes( pOut );
}



// Copies at most nCharsToCopy bytes from pIn into pOut.
// Returns false if it would have overflowed pOut's buffer.
static bool CopyToMaxChars( char *pOut, int outSize, const char *pIn, int nCharsToCopy )
{
	if ( outSize == 0 )
		return false;

	int iOut = 0;
	while ( *pIn && nCharsToCopy > 0 )
	{
		if ( iOut == (outSize-1) )
		{
			pOut[iOut] = 0;
			return false;
		}
		pOut[iOut] = *pIn;
		++iOut;
		++pIn;
		--nCharsToCopy;
	}
	
	pOut[iOut] = 0;
	return true;
}

// Returns true if it completed successfully.
// If it would overflow pOut, it fills as much as it can and returns false.
DLL_EXPORT bool Q_StrSubst( 
	const char *pIn, 
	const char *pMatch,
	const char *pReplaceWith,
	char *pOut,
	int outLen,
	bool bCaseSensitive
	)
{
	int replaceFromLen = strlen( pMatch );
	int replaceToLen = strlen( pReplaceWith );

	const char *pInStart = pIn;
	char *pOutPos = pOut;
	pOutPos[0] = 0;

	while ( 1 )
	{
		int nRemainingOut = outLen - (pOutPos - pOut);

		const char *pTestPos = ( bCaseSensitive ? strstr( pInStart, pMatch ) : Q_stristr( pInStart, pMatch ) );
		if ( pTestPos )
		{
			// Found an occurence of pMatch. First, copy whatever leads up to the string.
			int copyLen = pTestPos - pInStart;
			if ( !CopyToMaxChars( pOutPos, nRemainingOut, pInStart, copyLen ) )
				return false;
			
			// Did we hit the end of the output string?
			if ( copyLen > nRemainingOut-1 )
				return false;

			pOutPos += strlen( pOutPos );
			nRemainingOut = outLen - (pOutPos - pOut);

			// Now add the replacement string.
			if ( !CopyToMaxChars( pOutPos, nRemainingOut, pReplaceWith, replaceToLen ) )
				return false;

			pInStart += copyLen + replaceFromLen;
			pOutPos += replaceToLen;			
		}
		else
		{
			// We're at the end of pIn. Copy whatever remains and get out.
			int copyLen = strlen( pInStart );
			Q_strncpy( pOutPos, pInStart, nRemainingOut );
			return ( copyLen <= nRemainingOut-1 );
		}
	}
}

DLL_EXPORT bool Q_StrSubstInPlace(char* pchInOut, int cchInOut, const char* pMatch, const char* pReplaceWith, bool bCaseSensitive)
{
	char* pchT = (char*)stackalloc(cchInOut);
	if (Q_StrSubst(pchInOut, pMatch, pReplaceWith, pchT, cchInOut, bCaseSensitive))
	{
		Q_strncpy(pchInOut, pchT, cchInOut);
		return true;
	}
	return false;
}


DLL_EXPORT char* AllocString( const char *pStr, int nMaxChars )
{
	int allocLen;
	if ( nMaxChars == -1 )
		allocLen = strlen( pStr ) + 1;
	else
		allocLen = min( (int)strlen(pStr), nMaxChars ) + 1;

	char *pOut = new char[allocLen];
	Q_strncpy( pOut, pStr, allocLen );
	return pOut;
}


DLL_EXPORT void Q_SplitString2( const char *pString, const char **pSeparators, int nSeparators, CUtlVector<char*> &outStrings )
{
	outStrings.Purge();
	const char *pCurPos = pString;
	while ( 1 )
	{
		int iFirstSeparator = -1;
		const char *pFirstSeparator = 0;
		for ( int i=0; i < nSeparators; i++ )
		{
			const char *pTest = Q_stristr( pCurPos, pSeparators[i] );
			if ( pTest && (!pFirstSeparator || pTest < pFirstSeparator) )
			{
				iFirstSeparator = i;
				pFirstSeparator = pTest;
			}
		}

		if ( pFirstSeparator )
		{
			// Split on this separator and continue on.
			int separatorLen = strlen( pSeparators[iFirstSeparator] );
			if ( pFirstSeparator > pCurPos )
			{
				outStrings.AddToTail( AllocString( pCurPos, pFirstSeparator-pCurPos ) );
			}

			pCurPos = pFirstSeparator + separatorLen;
		}
		else
		{
			// Copy the rest of the string
			if ( strlen( pCurPos ) )
			{
				outStrings.AddToTail( AllocString( pCurPos, -1 ) );
			}
			return;
		}
	}
}


DLL_EXPORT void Q_SplitString( const char *pString, const char *pSeparator, CUtlVector<char*> &outStrings )
{
	Q_SplitString2( pString, &pSeparator, 1, outStrings );
}


// This function takes a slice out of pStr and stores it in pOut.
// It follows the Python slice convention:
// Negative numbers wrap around the string (-1 references the last character).
// Numbers are clamped to the end of the string.
DLL_EXPORT void Q_StrSlice( const char *pStr, int firstChar, int lastCharNonInclusive, char *pOut, int outSize )
{
	if ( outSize == 0 )
		return;
	
	int length = strlen( pStr );

	// Fixup the string indices.
	if ( firstChar < 0 )
	{
		firstChar = length - (-firstChar % length);
	}
	else if ( firstChar >= length )
	{
		pOut[0] = 0;
		return;
	}

	if ( lastCharNonInclusive < 0 )
	{
		lastCharNonInclusive = length - (-lastCharNonInclusive % length);
	}
	else if ( lastCharNonInclusive > length )
	{
		lastCharNonInclusive %= length;
	}

	if ( lastCharNonInclusive <= firstChar )
	{
		pOut[0] = 0;
		return;
	}

	int copyLen = lastCharNonInclusive - firstChar;
	if ( copyLen <= (outSize-1) )
	{
		memcpy( pOut, &pStr[firstChar], copyLen );
		pOut[copyLen] = 0;
	}
	else
	{
		memcpy( pOut, &pStr[firstChar], outSize-1 );
		pOut[outSize-1] = 0;
	}
}


DLL_EXPORT void Q_StrLeft( const char *pStr, int nChars, char *pOut, int outSize )
{
	if ( nChars == 0 )
	{
		if ( outSize != 0 )
			pOut[0] = 0;

		return;
	}

	Q_StrSlice( pStr, 0, nChars, pOut, outSize );
}


DLL_EXPORT void Q_StrRight( const char *pStr, int nChars, char *pOut, int outSize )
{
	int len = strlen( pStr );
	if ( nChars >= len )
	{
		Q_strncpy( pOut, pStr, outSize );
	}
	else
	{
		Q_StrSlice( pStr, -nChars, strlen( pStr ), pOut, outSize );
	}
}

//-----------------------------------------------------------------------------
// Convert multibyte to wchar + back
//-----------------------------------------------------------------------------
#ifndef _XBOX
DLL_EXPORT void Q_strtowcs( const char *pString, int nInSize, wchar_t *pWString, int nOutSize )
{
#ifdef _WIN32
	if ( !MultiByteToWideChar( CP_UTF8, 0, pString, nInSize, pWString, nOutSize ) )
	{
		*pWString = L'\0';
	}
#elif POSIX
	if ( mbstowcs( pWString, pString, nOutSize / sizeof(wchar_t) ) <= 0 )
	{
		*pWString = 0;
	}
#endif
}

DLL_EXPORT void Q_wcstostr( const wchar_t *pWString, int nInSize, char *pString, int nOutSize )
{
#ifdef _WIN32
	if ( !WideCharToMultiByte( CP_UTF8, 0, pWString, nInSize, pString, nOutSize, NULL, NULL ) )
	{
		*pString = '\0';
	}
#elif POSIX
	if ( wcstombs( pString, pWString, nOutSize ) <= 0 )
	{
		*pString = '\0';
	}
#endif
}
#endif

