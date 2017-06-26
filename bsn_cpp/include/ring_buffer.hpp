#pragma once

#include "i_ring_buffer.hpp"
#include <algorithm>
#include <atomic>
/*
http://blog.csdn.net/chen19870707/article/details/39994303
*/
namespace N_Bsn
{

template<uint32_t uCapcityPowOf2> // uCapcityPowOf2必须是2^x
class C_RingBuffer : public I_RingBuffer
{
public:
	
public:
	// 总容量
	uint32_t Capcity() const;
	// 已用容量
	uint32_t Size() const;
	// 剩余容量
	uint32_t Space() const;
	bool 	Empty() const;
	// 希望读取的数据长度为len，函数返回实际长度
	uint32_t Read(uint8_t* pData, uint32_t uLen);
	// 希望写入的数据长度为len，函数返回实际长度
	uint32_t Write(uint8_t* pData, uint32_t uLen);

	// 返回下次可写的指针pData 及连续长度uLen
	void GetNextWriteData(uint8_t*& pData, uint32_t& uLen);
	// 增加已写入长度
	void IncWriteDataLength(uint32_t uLen);

public:
	C_RingBuffer();
	virtual ~C_RingBuffer() = default;

private:
	volatile uint32_t 	m_uReadPos;
	volatile uint32_t 	m_uWritePos;
	uint8_t		m_data[uCapcityPowOf2];
};

template<uint32_t uCapcity>
C_RingBuffer<uCapcity>::C_RingBuffer()
: m_uReadPos(0)
, m_uWritePos(0)
{

}

template<uint32_t uCapcity>
void C_RingBuffer<uCapcity>::IncWriteDataLength(uint32_t uLen)
{
	m_uWritePos += uLen;
}

template<uint32_t uCapcity>
void C_RingBuffer<uCapcity>::GetNextWriteData(uint8_t*& pData, uint32_t& uLen)
{
	auto uSize =  m_uWritePos - m_uReadPos;
	auto uSpace = uCapcity - uSize;
	if (uSpace == 0)
	{
		return;
	}

	auto uWriteIndex = (m_uWritePos & (uCapcity - 1));
	pData = &m_data[uWriteIndex];
	auto uRightSize = uCapcity - uWriteIndex;
	uLen = std::min(uSpace, uRightSize);
}


template<uint32_t uCapcity>
uint32_t C_RingBuffer<uCapcity>::Write(uint8_t* pData, uint32_t uLen)
{
	auto uReadPos = m_uReadPos;
	std::atomic_thread_fence(std::memory_order_acquire);

	auto uSize =  (m_uWritePos - uReadPos);
	auto uSpace = uCapcity - uSize;
	uLen = std::min(uSpace, uLen);

	/*
	first put the data starting from m_uWritePos to buffer end
	m_uWritePos % Capcity() 当Capcity()=powOf2时等价于 (m_uWritePos & (Capcity() - 1)
	*/
	auto uWirteIndex = (m_uWritePos & (uCapcity - 1));
	auto uRightSize = uCapcity - uWirteIndex;
	auto uCopySize = std::min(uLen, uRightSize);
	memcpy(&m_data[uWirteIndex], pData, uCopySize); 
	/* then put the rest (if any) at the beginning of the buffer */
	memcpy(m_data, pData + uCopySize, uLen - uCopySize);

	/*
	* Ensure that we add the bytes to the kfifo	
	* we update the m_uWritePos index
	加写内存屏障，保证in 加之前，memcpy的字节已经全部写入buffer，如果不加内存屏障，可能数据还没写完，另一个CPU就来读数据，读到的缓冲区内的数据不完全，因为读数据是通过 in – out 来判断的。
	*/
	std::atomic_thread_fence(std::memory_order_release);
	/*
	这里 只是用了 m_uWritePos += uLen而未取模，用到了unsigned int的溢出性质，当m_uWritePos持续增加到溢出时又会被置为0，这样就节省了每次m_uWritePos向前增加都要取模的性能
	*/
	m_uWritePos += uLen;
	return uLen;
}


template<uint32_t uCapcity>
uint32_t C_RingBuffer<uCapcity>::Read(uint8_t* pData, uint32_t uLen)
{
	auto uWritePos = m_uWritePos;
	std::atomic_thread_fence(std::memory_order_acquire);

	auto uSize =  (uWritePos - m_uReadPos);
	uLen = std::min(uSize, uLen);

	auto uReadIndex = (m_uReadPos & (uCapcity - 1));
	auto uRightSize = uCapcity - uReadIndex;
	auto uCopySize = std::min(uLen, uRightSize);
	memcpy(pData, &m_data[uReadIndex], uCopySize); 
	memcpy(pData + uCopySize, m_data, uLen - uCopySize);

	std::atomic_thread_fence(std::memory_order_release);
	m_uReadPos += uLen;
	return uLen;
}

template<uint32_t uCapcity>
uint32_t C_RingBuffer<uCapcity>::Capcity() const
{
	return uCapcity;
}

template<uint32_t uCapcity>
uint32_t C_RingBuffer<uCapcity>::Size() const
{
	return (m_uWritePos - m_uReadPos);
}

template<uint32_t uCapcity>
uint32_t C_RingBuffer<uCapcity>::Space() const
{
	return Capcity() - Size();
}

template<uint32_t uCapcity>
bool C_RingBuffer<uCapcity>::Empty() const
{
	return m_uReadPos == m_uWritePos;
}
} // end namespace NBSN

 