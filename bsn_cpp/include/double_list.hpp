#pragma once


#include <boost/thread.hpp>
// #include <vector>

namespace N_Bsn {

template<typename T_Type>
class C_DoubleList {
public:
	typedef typename T_Type::value_type T_ValueType;


public:
	// 取得写入的容器
	T_Type&	Flip( );
	// 写入 可以多个线程调用
	void	Write(T_ValueType const V_Value);
	void	WriteRef(T_ValueType const& V_Value);


public:
	C_DoubleList( );
	~C_DoubleList( );

	
private:
	uint32_t	m_u32Read;
	uint32_t	m_u32Write;

	boost::mutex	m_Mutex;

	T_Type	m_Value[2];


private:
};


template<typename T_Type>
C_DoubleList<T_Type>::~C_DoubleList()
{

}



template<typename T_Type>
void
C_DoubleList<T_Type>::Write(T_ValueType const V_Value)
{
	WriteRef(V_Value);
}

template<typename T_Type>
void
C_DoubleList<T_Type>::WriteRef(T_ValueType const& V_Value)
{
	boost::lock_guard<boost::mutex> lock_obj(m_Mutex);
	m_Value[m_u32Write].push_back(V_Value);
}

template<typename T_Type>
T_Type&
C_DoubleList<T_Type>::Flip(  )
{
	{
		boost::lock_guard<boost::mutex> lock_obj( m_Mutex );
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
 
