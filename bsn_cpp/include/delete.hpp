#pragma once

namespace N_Bsn
{

template<typename T_Type>
D_inline
void
Delete(T_Type*& p)
{
	if (nullptr != p)
	{
		delete p;
		p = nullptr;
	}
}

} // end namespace N_Bsn
