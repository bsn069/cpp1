#pragma once

namespace N_Bsn
{

// ������������
template<typename T_Type>
D_inline
T_void
Destory(T_Type* p)
{
	if (T_nullptr != p)
	{
		p->~T_Type();
	}
}

} // end namespace N_Bsn
