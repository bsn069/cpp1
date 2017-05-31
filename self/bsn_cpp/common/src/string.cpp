#include <bsn/common/include/string.h>


#ifdef _WIN32
	#include <Windows.h>
#else
	#error "unknown system"
#endif
D_BsnNamespace2(Common, String)
//////////////////////////////////////////////////////////////////////



D_FunImp  T_int32 D_const ANSI2UnicodeLen(T_char D_const * D_const pc_SrcANSI)
{
	return MultiByteToWideChar(CP_ACP, 0, pc_SrcANSI, -1, NULL, 0);
}


D_FunImp T_int32 D_const Unicode2ANSILen(T_wchar D_const * D_const pwc_SrcUnicode)
{
	return WideCharToMultiByte(CP_ACP, 0, pwc_SrcUnicode, -1, NULL, 0, 0, 0);
}


D_FunImp T_int32 D_const UTF82UnicodeLen(T_char D_const * D_const pc_SrcUTF8)
{
	return MultiByteToWideChar(CP_UTF8, 0, pc_SrcUTF8, -1, NULL, 0);
}


D_FunImp T_int32 D_const Unicode2UTF8Len(T_wchar D_const * D_const pwc_SrcUnicode)
{
	return WideCharToMultiByte(CP_UTF8, 0, pwc_SrcUnicode, -1, NULL, 0, 0, 0);
}


D_FunImp T_int32 D_const ANSI2Unicode(
	T_char D_const * D_const pc_SrcANSI
	, T_wchar* D_const pwc_DesUnicode
	, T_int32 D_const i32_DesUnicodeLen
	)
{
	return MultiByteToWideChar(CP_ACP, 0, pc_SrcANSI, -1, pwc_DesUnicode, i32_DesUnicodeLen);
}


D_FunImp T_int32 D_const Unicode2ANSI(
	T_wchar D_const * D_const pwc_SrcUnicode
	, T_char* D_const pc_DesANSI
	, T_int32 D_const i32_DesANSILen
	)
{
	return WideCharToMultiByte(CP_ACP, 0, pwc_SrcUnicode, -1, pc_DesANSI, i32_DesANSILen, 0, 0);
}


D_FunImp T_int32 D_const UTF82Unicode(
				 T_char D_const * D_const pc_SrcUTF8
				 , T_wchar* D_const pwc_DesUnicode
				 , T_int32 D_const i32_DesUnicodeLen
				 )
{
	return MultiByteToWideChar(CP_UTF8, 0, pc_SrcUTF8, -1, pwc_DesUnicode, i32_DesUnicodeLen);
}


D_FunImp T_int32 D_const Unicode2UTF8(
				 T_wchar D_const * D_const pwc_SrcUnicode
				 , T_char* D_const pc_DesUTF8
				 , T_int32 D_const i32_DesUTF8Len
				 )
{
	return WideCharToMultiByte(CP_UTF8, 0, pwc_SrcUnicode, -1, pc_DesUTF8, i32_DesUTF8Len, 0, 0);
}


D_FunImp T_void ANSI2Unicode(T_char D_const * D_const pc_SrcANSI, wstring& wstr_Out)
{
	T_int32 D_const nSize = ANSI2UnicodeLen( pc_SrcANSI ) - 1;
	wstr_Out.resize( nSize );
	ANSI2Unicode(pc_SrcANSI, &(wstr_Out)[0], nSize); 
}


D_FunImp T_void Unicode2ANSI(T_wchar D_const * D_const pc_SrcUnicode, string& str_Out)
{

	T_int32 D_const nSize = Unicode2ANSILen( pc_SrcUnicode ) - 1;
	str_Out.resize( nSize );
	Unicode2ANSI(pc_SrcUnicode, &(str_Out)[0], nSize); 
}

 
D_FunImp T_void UTF82Unicode(T_char D_const * D_const pc_SrcUTF8, wstring& wstr_Out)
{
	T_int32 D_const nSize = UTF82UnicodeLen( pc_SrcUTF8 ) - 1;
	wstr_Out.resize( nSize );
	UTF82Unicode(pc_SrcUTF8, &(wstr_Out)[0], nSize); 
}


D_FunImp T_void Unicode2UTF8(T_wchar D_const * D_const pc_SrcUnicode, string& str_Out)
{
	T_int32 D_const nSize = Unicode2UTF8Len( pc_SrcUnicode ) - 1;
	str_Out.resize( nSize );
	Unicode2UTF8(pc_SrcUnicode, &(str_Out)[0], nSize); 
}


D_FunImp T_uint32 D_const Copy(T_char D_const * D_const pc_Src, T_char * D_const pc_Dest, T_uint32 D_const u32_DestLen)
{
	T_uint32 D_const u32_Len = (T_uint32)__min(strlen(pc_Src), u32_DestLen - 1);
	memcpy(pc_Dest, pc_Src, u32_Len);
	pc_Dest[ u32_Len ] = '\0';

	return u32_Len + 1;
}


D_FunImp T_uint32 D_const Copy(T_wchar D_const * D_const pwc_Src, T_wchar * D_const pwc_Dest, T_uint32 D_const u32_DestLen)
{
	T_uint32 D_const u32_Len = (T_uint32)__min(wcslen(pwc_Src), u32_DestLen - 1);
	memcpy(pwc_Dest, pwc_Src, sizeof(T_wchar) *u32_Len);
	pwc_Dest[ u32_Len ] = L'\0';

	return u32_Len + 1;
}


D_FunImp T_void ANSI2Unicode(string D_const& str_Src, wstring& wstr_Out)
{
	ANSI2Unicode(str_Src.c_str(), wstr_Out);
}


D_FunImp T_void Unicode2ANSI(wstring D_const& wstr_Src, string& str_Out)
{
	Unicode2ANSI(wstr_Src.c_str(), str_Out);
}

D_FunImp T_void UTF82Unicode(string D_const& str_SrcUTF8, wstring& wstr_Out)
{
	UTF82Unicode(str_SrcUTF8.c_str(), wstr_Out);
}


D_FunImp T_void Unicode2UTF8(wstring D_const& wstr_SrcUnicode, string& str_Out)
{
	Unicode2UTF8(wstr_SrcUnicode.c_str(), str_Out);
}


D_FunImp T_uint32 D_const Copy(string D_const& str_Src, T_char * D_const pc_Dest, T_uint32 D_const u32_DestLen)
{
	return Copy(str_Src.c_str(), pc_Dest, u32_DestLen);
}


D_FunImp T_uint32 D_const Copy(wstring D_const& wstr_Src, T_wchar * D_const pwc_Dest, T_uint32 D_const u32_DestLen)
{
	return Copy(wstr_Src.c_str(), pwc_Dest, u32_DestLen);
}

D_BsnNamespace2End
