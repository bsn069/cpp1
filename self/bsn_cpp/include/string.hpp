#pragma once

D_BsnNamespace1(String)
//////////////////////////////////////////////////////////////////////
// ²ð·Ö×Ö·û´®
template<typename T_StrType>
D_FunTemplate 
D_inline 
T_void 
Split(
	T_StrType D_const&		strIn
	, T_StrType D_const&	Sep
	, vector<T_StrType>&	vec_OutStr
	)
{
	typedef char_separator< T_StrType::value_type > T_SepType;
	typedef tokenizer<T_SepType, T_StrType::const_iterator, T_StrType> T_Tokenizer;

	T_SepType	SepStr(Sep.c_str());
	T_Tokenizer Tokens(strIn, SepStr);

	T_Tokenizer::iterator it = Tokens.begin();
	for (; it != Tokens.end(); ++it)
	{
		vec_OutStr.push_back(*it);
	}
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 
