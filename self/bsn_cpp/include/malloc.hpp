#pragma once 

namespace N_Bsn
{

template<typename T_Type>
D_inline 
T_Type*
Malloc(T_uint32 u32Size)
{
	return (T_Type*)malloc( u32Size );
}


} // end namespace N_Bsn
