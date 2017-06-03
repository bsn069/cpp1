#include "./../interface.h"

D_BsnNamespace1(t_share)
//////////////////////////////////////////////////////////////////////

char const* const C_Interface::Error(int32_t const i32ErrorCode) const
{
	switch (i32ErrorCode)
	{
		case 1: return "1";
		default: return "Unknown";
	}
}


char const* const C_Interface::Name() const
{
	return "t_share";
}


C_Interface::C_Interface()
{
 	std::cout << this->Name() << " C_Interface::C_Interface()" << std::endl;
}


C_Interface::~C_Interface()
{
 	std::cout << this->Name() << " C_Interface::~C_Interface()" << std::endl;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
