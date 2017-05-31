#include "./main.h"
#ifdef D_USE_2
D_BsnNamespace1(UDP)
//////////////////////////////////////////////////////////////////////




class C_Imp : public I_Interface
{

public:
	virtual T_wchar D_const * D_const Name() D_const;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const;


public:
	C_Imp();
	virtual ~C_Imp();

private:

};


D_FunImp D_BSN_udp_DLL I_Interface* Create()
{
	return new C_Imp;
}

C_Imp::C_Imp()
{
	wcout << L"C_Imp::C_Imp()" << endl;
}

C_Imp::~C_Imp()
{
	wcout << L"C_Imp::~C_Imp()" << endl;
}


T_wchar D_const * D_const  C_Imp::Name() D_const
{
	return L"C_Imp";
}


T_wchar D_const * D_const C_Imp::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch ( i32ErrorCode )
	{
	case 1: return L"had init";
	case 2: return L"not init";
	default: return L"Unknown";
	}
}







D_BsnNamespace1End
#endif