#pragma once

namespace N_Bsn
{

// ��ȡ����ռ�õ�λ��
template<typename T_Type>
T_uint32 D_const
GetBitCount( T_void )
{
	return (sizeof(T_Type) * 8);
}

// ��ȡ����ռ�õ�λ��
template<typename T_Type>
T_uint32 D_const
GetBitCount( T_Type )
{
	return GetBitCount< T_Type >();
}

// ����߿�ʼ�м���������1
// ��ֵ��2���� ����ж��ٸ�������1
template<typename T_Type>
T_uint32 D_const
GetLeft1Count(T_Type V_Value)
{
	T_uint32	D_const dwBitCount	= GetBitCount( V_Value );
	// �������λ��1
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

 