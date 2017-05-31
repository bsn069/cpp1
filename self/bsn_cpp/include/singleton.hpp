#pragma once


namespace N_Bsn
{
//////////////////////////////////////////////////////////////////////


template <class T>
class C_Singleton
{
public:
	typedef C_Singleton<T> T_Base;

	C_Singleton()
	{
		D_Assert(T_nullptr == ms_pInstance);
		ms_pInstance = static_cast<T*>(this);
	}

	virtual ~C_Singleton()
	{
		D_Assert(T_nullptr != ms_pInstance);
		ms_pInstance = T_nullptr;
	}

	static T& Ref()
	{
		return (*Ptr());
	}

	static T* Ptr()
	{
		return ms_pInstance;
	}


private:
	static T* ms_pInstance;
};

/*
class C_SingletonTest
	: public C_Singleton<C_SingletonTest>
{
};

template <> C_SingletonTest* C_Singleton<C_SingletonTest>::ms_pInstance = T_nullptr;
new C_SingletonTest();
delete C_SingletonTest();
*/


//////////////////////////////////////////////////////////////////////
} // end namespace NBSN
