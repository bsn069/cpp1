#pragma once

#include <bsn/include/port.h>
#include <bsn/common/include/lib_def.h>

D_BsnNamespace2(Common, String)
//////////////////////////////////////////////////////////////////////

// pcSrcANSI NULL��β��ANSI�ַ���
// wstrOut(û�н�β��0) 
D_FunDef D_BSN_common_DLL T_void ANSI2Unicode(T_char D_const * D_const pc_SrcANSI, wstring& wstr_Out);
D_FunDef D_BSN_common_DLL T_void ANSI2Unicode(string D_const& str_Src, wstring& wstr_Out);
// pwcSrcUnicode NULL��β��Unicode�ַ���
// strOut(û�н�β��0) 
D_FunDef D_BSN_common_DLL T_void Unicode2ANSI(T_wchar D_const * D_const pwc_SrcUnicode, string& str_Out);
D_FunDef D_BSN_common_DLL T_void Unicode2ANSI(wstring D_const& wstr_Src, string& str_Out);

// pcSrcUTF8 NULL��β��ANSI�ַ���
// wstrOut(û�н�β��0) 
D_FunDef D_BSN_common_DLL T_void UTF82Unicode(T_char D_const * D_const pc_SrcUTF8, wstring& wstr_Out);
D_FunDef D_BSN_common_DLL T_void UTF82Unicode(string D_const& str_SrcUTF8, wstring& wstr_Out);
// pwcSrcUnicode NULL��β��Unicode�ַ���
// strOut(û�н�β��0) 
D_FunDef D_BSN_common_DLL T_void Unicode2UTF8(T_wchar D_const * D_const pwc_SrcUnicode, string& str_Out);
D_FunDef D_BSN_common_DLL T_void Unicode2UTF8(wstring D_const& wstr_SrcUnicode, string& str_Out);

// pSrc 0��β���ַ���
// pDest(���ٰ�����β0)���ɷ�dwDestLen-1���ַ�
// ����ʵ�ʸ��Ƶ�pDest���ַ��������� ��β0(�� ��С����ֵ1)
D_FunDef D_BSN_common_DLL T_uint32 D_const Copy(T_char D_const * D_const pc_Src, T_char * D_const pc_Dest, T_uint32 D_const u32_DestLen);
D_FunDef D_BSN_common_DLL T_uint32 D_const Copy(string D_const& str_Src, T_char * D_const pc_Dest, T_uint32 D_const u32_DestLen);
// pSrc 0��β���ַ���
// pDest(���ٰ�����β0)���ɷ�dwDestLen-1���ַ�
// ����ʵ�ʸ��Ƶ�pDest���ַ��������� ��β0(�� ��С����ֵ1)
D_FunDef D_BSN_common_DLL T_uint32 D_const Copy(T_wchar D_const * D_const pwc_Src, T_wchar * D_const pwc_Dest, T_uint32 D_const u32_DestLen);
D_FunDef D_BSN_common_DLL T_uint32 D_const Copy(wstring D_const& wstr_Src, T_wchar * D_const pwc_Dest, T_uint32 D_const u32_DestLen);


// ����ַ���
template<typename T_StrType>
D_FunTemplate D_inline T_void Split(T_StrType D_const& strIn, T_StrType D_const& Sep, vector<T_StrType>& vec_OutStr)
{
	typedef char_separator< T_StrType::value_type > T_SepType; 
	typedef tokenizer<T_SepType, T_StrType::const_iterator, T_StrType> T_Tokenizer;
	
	T_SepType	SepStr( Sep.c_str() );
	T_Tokenizer Tokens(strIn, SepStr);

	T_Tokenizer::iterator it = Tokens.begin( );
	for ( ;it != Tokens.end(); ++it)
	{
		vec_OutStr.push_back( *it );
	}
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace2End

