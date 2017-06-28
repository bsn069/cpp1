#pragma once

namespace N_Bsn
{

template<typename T>
class C_PtrNode
{
public:
	explicit C_PtrNode(T* pData) : m_pNext(nullptr) {
		m_pData = pData;
	}

public:
	C_Node<T>* 	m_pNext;
	T* 			m_pData;
}
 

template<typename TNode>
class C_SWSDList
{
public:
	explicit C_SWSDList(TNode* pNode) : m_pHead(pNode), m_pTail(pNode)
	{
	}

	void PushBack(TNode* pNode)
	{

	}

	TNode* PopFront()
	{
		if (m_pHead == nullptr)
		{
			return nullptr;
		}
	}

public:
	TNode* m_pHead;
	TNode* m_pTail;
}

} // end namespace NBSN
