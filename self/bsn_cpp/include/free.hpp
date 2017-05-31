#pragma once

namespace N_Bsn
{

template<typename T_Type>
D_inline 
T_void
Free(T_Type*& p)
{
	if (T_nullptr != p)
	{
		free( p );
		p = T_nullptr;
	}
}


} // end namespace N_Bsn
