#pragma once

namespace N_Bsn
{

// 调用构造函数
template<typename T_Type>
D_inline
T_void 
Construct(T_Type* p)
{
	new(p) T_Type();
}


template<typename T_Type, typename T_Param1>
D_inline
T_void 
Construct(T_Type* p, T_Param1 D_const& V_Param1)
{
	new(p) T_Type( V_Param1 );
}


template<typename T_Type, typename T_Param1, typename T_Param2>
D_inline
T_void 
Construct(T_Type* p, T_Param1 D_const& V_Param1, T_Param2 D_const& V_Param2)
{
	new(p) T_Type( V_Param1, V_Param2 );
}


template<typename T_Type, typename T_Param1, typename T_Param2, typename T_Param3>
D_inline
T_void 
Construct(T_Type* p, T_Param1 D_const& V_Param1, T_Param2 D_const& V_Param2, T_Param3 D_const& V_Param3)
{
	new(p) T_Type( V_Param1, V_Param2, V_Param3 );
}

} // end namespace N_Bsn
