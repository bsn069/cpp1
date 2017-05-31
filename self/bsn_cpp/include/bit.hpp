#pragma once

namespace N_Bsn
{

// 获取类型占用的位数
template<typename T_Type>
T_uint32 D_const
GetBitCount( T_void )
{
	return (sizeof(T_Type) * 8);
}

// 获取类型占用的位数
template<typename T_Type>
T_uint32 D_const
GetBitCount( T_Type )
{
	return GetBitCount< T_Type >();
}

// 从左边开始有几个连续的1
// 数值的2进制 左边有多少个连续的1
template<typename T_Type>
T_uint32 D_const
GetLeft1Count(T_Type V_Value)
{
	T_uint32	D_const dwBitCount	= GetBitCount( V_Value );
	// 将最左边位置1
	T_Type D_const vMask = 1 << (dwBitCount - 1);

	for (T_uint32 i = 0; i <= dwBitCount; ++i)
	{
		if (0 == (V_Value & vMask))
		{
			return i;
		}

		V_Value <<= 1;
	}

	return dwBitCount;
}

} // end namespace NBSN

 