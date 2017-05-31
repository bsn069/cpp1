#pragma once

namespace N_Bsn
{
//////////////////////////////////////////////////////////////////////

// ×´Ì¬»ùÀà
template <class C_Entity>
class C_FSMState
{
public:
	typedef C_Entity T_Entity;


public: 
	virtual void Enter(T_Entity*)=0; 
	virtual void Exit(T_Entity*)=0;

	virtual void Update(T_Entity*)=0;
 

public:
	virtual ~C_FSMState(){}
};


// ×´Ì¬»ú
template <class C_Entity>
class C_FSMMachine
{
public:
	typedef C_Entity T_Entity;


public:
	T_void SetCurrentState(C_FSMState<T_Entity>* oState){ m_pCurrentState = oState; }
	T_void SetGlobalState(C_FSMState<T_Entity>* oState) { m_pGlobalState = oState; }
	T_void SetPreviousState(C_FSMState<T_Entity>* oState){ m_pPreviousState = oState; }

	C_FSMState<T_Entity>*  CurrentState()  D_const { return m_pCurrentState; }
	C_FSMState<T_Entity>*  GlobalState()   D_const { return m_pGlobalState; }
	C_FSMState<T_Entity>*  PreviousState() D_const { return m_pPreviousState; }

	T_void  Update() D_const
	{
		if (T_nullptr != m_pGlobalState)	m_pGlobalState->Update( m_pOwner );
		if (T_nullptr != m_pCurrentState)	m_pCurrentState->Update( m_pOwner );
	}

	T_void  ChangeState(C_FSMState<T_Entity>* pNewState)
	{
		assert(pNewState && "<C_FSMMachine::ChangeState>: trying to change to a null state");
		m_pPreviousState = m_pCurrentState;
		m_pCurrentState->Exit( m_pOwner );
		m_pCurrentState = pNewState;
		m_pCurrentState->Enter( m_pOwner );
	}

	T_void  RevertToPreviousState()
	{
		ChangeState( m_pPreviousState );
	}

	T_bool  IsInState(const C_FSMState<T_Entity>& oState) D_const
	{
		return typeid(*m_pCurrentState) == typeid(oState);
	}


public:
  C_FSMMachine(T_Entity* pOwner)
	: m_pOwner( pOwner )
	, m_pCurrentState( T_nullptr )
	, m_pPreviousState( T_nullptr )
	, m_pGlobalState( T_nullptr )
  {
  }


private:
	T_Entity*			m_pOwner;
 
	C_FSMState<T_Entity>*	m_pCurrentState;
	C_FSMState<T_Entity>*	m_pPreviousState;
	C_FSMState<T_Entity>*	m_pGlobalState;
};


//////////////////////////////////////////////////////////////////////
} // end namespace N_Bsn
