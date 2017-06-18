#include "./../interface.h"

D_BsnNamespace1(global)
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
	return "global";
}


C_Interface::C_Interface()
: m_lib(nullptr)
{
	D_LogInfoFmt("Name()=%s", this->Name());
}


C_Interface::~C_Interface()
{
	D_LogInfoFmt("Name()=%s", this->Name());
	SetLib(nullptr);
}

void C_Interface::SetLib(T_SharePtrLib lib) {
	m_lib = lib;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
