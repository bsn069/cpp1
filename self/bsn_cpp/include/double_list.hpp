#pragma once

namespace N_Bsn
{

template<typename T_Type>
class C_DoubleList
{
public:
	typename typedef T_Type::value_type T_ValueType;


public:
	// 取得写入的容器
	T_Type&	Flip( );
	// 写入 可以多个线程调用
	T_void	Write(T_ValueType D_const V_Value);
	T_void	WriteRef(T_ValueType D_const& V_Value);


public:
	C_DoubleList( );
	~C_DoubleList( );

	
private:
	T_uint32	m_u32Read;
	T_uint32	m_u32Write;

	mutex	m_Mutex;

	T_Type	m_Value[2];


private:
};


template<typename T_Type>
C_DoubleList<T_Type>::~C_DoubleList()
{

}



template<typename T_Type>
T_void
C_DoubleList<T_Type>::Write(T_ValueType D_const V_Value)
{
	WriteRef(V_Value);
}

template<typename T_Type>
T_void
C_DoubleList<T_Type>::WriteRef(T_ValueType D_const& V_Value)
{
	lock_guard<mutex> lock_obj(m_Mutex);
	m_Value[m_u32Write].push_back(V_Value);
}

template<typename T_Type>
T_Type&
C_DoubleList<T_Type>::Flip(  )
{
	{
		lock_guard<mutex> lock_obj( m_Mutex );
		swap(m_u32Write, m_u32Read);
		m_Value[ m_u32Write ].clear();
	}
	return m_Value[ m_u32Read ];
}


template<typename T_Type>
C_DoubleList<T_Type>::C_DoubleList(  )
: m_u32Read( 0 )
, m_u32Write( 1 )
{
	m_Value[ m_u32Read ].clear();
	m_Value[ m_u32Write ].clear();
}



































 
 
 
//////////////////////////////////////////////////////////////////////
} // end namespace NBSN
 
