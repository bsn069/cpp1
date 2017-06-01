#include "./interface.h"
D_BsnNamespace1(NameSpace)
//////////////////////////////////////////////////////////////////////

wchar_t const* const C_Interface::Error(int32_t const i32ErrorCode) const
{
	switch (i32ErrorCode)
	{
		case 1: return L"1";
		default: return L"Unknown";
	}
}


wchar_t const* const C_Interface::Name() const
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
