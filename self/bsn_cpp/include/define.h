#pragma once

namespace N_Bsn
{

#define	D_Assert(exp) assert((exp) && #exp)

#define D_AssertRet(exp, retCode) \
{\
	auto ret = (exp);\
	assert(ret && #exp);\
	if (!ret)\
	{\
		return retCode;\
	}\
}\

#define	D_FunIn
#define	D_FunImp
#define	D_FunDef
#define	D_FunTemplate
#define D_inline inline
#define D_const const

	 


template <typename T, size_t N>
T_uint8 (*ArraySize(T (&)[N] ))[N];
#define D_ArrayCount(A) (sizeof(*ArraySize(A)))
#define D_ArrayByte(A) (sizeof( A ))


// 声明函数已被遗弃 不建议使用
#define D_Deprecate __declspec(deprecated)


#define D_DllImport __declspec(dllimport)
#define D_DllExport __declspec(dllexport)

#define D_DllCImport extern "C" D_DllImport
#define D_DllCExport extern "C" D_DllExport






} // end namespace NBSN

 