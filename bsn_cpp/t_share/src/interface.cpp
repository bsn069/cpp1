#include "./interface.h"
D_BsnNamespace1(NameSpace)
//////////////////////////////////////////////////////////////////////

T_wchar D_const * D_const C_Interface::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch (i32ErrorCode)
	{
		case 1: return L"1";
		default: return L"Unknown";
	}
}


T_wchar D_const * D_const  C_Interface::Name() D_const
{
	return L"C_Imp";
}


C_Interface::C_Interface()
{

}


C_Interface::~C_Interface()
{

}





//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
