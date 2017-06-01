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
#define D_inline

template <typename T, uint32_t N>
uint8_t (*ArraySize(T (&)[N] ))[N];
#define D_ArrayCount(A) (sizeof(*ArraySize(A)))
#define D_ArrayByte(A) (sizeof( A ))


// 声明函数已被遗弃 不建议使用
#define D_Deprecate __declspec(deprecated)


#if (defined _MSC_VER)
	#define D_DllImport __declspec(dllimport)
	#define D_DllExport __declspec(dllexport)
#else
	#define D_DllImport 
	#define D_DllExport 
#endif

#define D_DllCImport extern "C" D_DllImport
#define D_DllCExport extern "C" D_DllExport






} // end namespace NBSN

 