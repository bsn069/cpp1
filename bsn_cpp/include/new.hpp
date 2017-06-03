#pragma once
#include "define.h"

namespace N_Bsn
{

template<typename T_Type>
D_inline 
T_Type* const
New( void )
{
	return new T_Type();
}


template<typename T_Type, typename T_Param1>
D_inline
T_Type* const
New(T_Param1 const& V_Param1)
{
	return new T_Type( V_Param1 );
}


template<typename T_Type, typename T_Param1>
D_inline
T_Type* const
New(T_Param1& V_Param1)
{
	return new T_Type(V_Param1);
}

template<typename T_Type, typename T_Param1, typename T_Param2>
D_inline
T_Type* const
New(T_Param1 const& V_Param1, T_Param2 const& V_Param2)
{
	return new T_Type( V_Param1, V_Param2 );
}

template<typename T_Type, typename T_Param1, typename T_Param2>
D_inline
T_Type* const
New(T_Param1& V_Param1, T_Param2& V_Param2)
{
	return new T_Type(V_Param1, V_Param2);
}


template<typename T_Type, typename T_Param1, typename T_Param2, typename T_Param3>
D_inline
T_Type* const
New(T_Param1 const& V_Param1, T_Param2 const& V_Param2, T_Param3 const& V_Param3)
{
	return new T_Type( V_Param1, V_Param2, V_Param3 );
}

} // end namespace N_Bsn
