#pragma once

namespace N_Bsn
{

template<typename T_Type>
D_inline
T_Type* D_const
NewArray(T_uint32 u32Count)
{
	return new T_Type[ u32Count ];
}

} // end namespace N_Bsn
