#pragma once

#include <algorithm>
#include <atomic>
/*
http://blog.csdn.net/chen19870707/article/details/39994303
*/
namespace N_Bsn
{

template<uint32_t uCapcityPowOf2> // uCapcityPowOf2必须是2^x
class C_RingBuffer : I_RingBuffer
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
	// 希望写入的数据长度为len，函数返回写入的实际长度
	uint32_t Write(uint8_t* pData, uint32_t uLen);


public:
	C_RingBuffer() {};
	virtual ~C_RingBuffer() = default;

private:
	uint32_t 	m_uReadPos;
	uint32_t 	m_uWritePos;
	uint8_t		m_data[uCapcityPowOf2];
};

template<uint32_t uCapcity>
C_RingBuffer::C_RingBuffer()
: m_uReadPos(0)
, m_uWritePos(0)
{

}


template<uint32_t uCapcity>
uint32_t C_RingBuffer::Write(uint8_t* pData, uint32_t uLen)
{
	auto uReadPos = m_uReadPos;
	std::atomic_thread_fence(std::memory_order_acquire);

	auto uSize =  (m_uWritePos - uReadPos);
	auto uSpace = uCapcity - uSize;
	uLen = std::min(uSpace, uLen);

	/*
	* Ensure that we sample the uReadPos index -before- we
	* start putting bytes into the buffer
	加内存屏障，保证在开始放入数据之前 uReadPos 取到正确的值（另一个CPU可能正在改写uReadPos值）
	*/
	// smp_mb();
	// __sync_synchronize();

	/*
	first put the data starting from m_uWritePos to buffer end
	m_uWritePos % Capcity() 当Capcity()=powOf2时等价于 (m_uWritePos & (Capcity() - 1)
	*/
	auto uRightPos = (uWritePos & (uCapcity - 1));
	auto uRightCanWriteSize = uCapcity - uRightPos;
	auto uCopySize = std::min(uLen, uRightCanWriteSize);
	// std::atomic_thread_fence(std::memory_order_acquire);
	memcpy(&m_data[uRightPos]), pData, uCopySize); 
	/* then put the rest (if any) at the beginning of the buffer */
	memcpy(m_data, pData + uCopySize, uLen - uCopySize);

	/*
	* Ensure that we add the bytes to the kfifo	
	* we update the m_uWritePos index
	加写内存屏障，保证in 加之前，memcpy的字节已经全部写入buffer，如果不加内存屏障，可能数据还没写完，另一个CPU就来读数据，读到的缓冲区内的数据不完全，因为读数据是通过 in – out 来判断的。
	*/
	// smp_wmb();
	// __sync_synchronize();
	// std::atomic_thread_fence(std::memory_order_acquire);
	std::atomic_thread_fence(std::memory_order_release);
	/*
	这里 只是用了 m_uWritePos += uLen而未取模，用到了unsigned int的溢出性质，当m_uWritePos持续增加到溢出时又会被置为0，这样就节省了每次m_uWritePos向前增加都要取模的性能
	*/
	m_uWritePos += uLen;
	return uLen;
}



template<uint32_t uCapcity>
uint32_t C_RingBuffer::Read(uint8_t* pData, uint32_t uLen)
{
	// max can read Size()
	uLen = std::min(Size(), uLen);

	/*
	* Ensure that we sample the m_uWritePos index -before- we
	* start putting bytes into the buffer
	加读内存屏障，保证在开始取数据之前 m_uWritePos 取到正确的值（另一个CPU可能正在改写 m_uWritePos 值）
	*/
	// smp_rmb();
	// __sync_synchronize();

	/*
	first get the data from m_uReadPos until the end of the buffer 
	m_uReadPos % Capcity() 当Capcity()=powOf2时等价于 (m_uReadPos & (Capcity() - 1)
	*/
	auto uPos = (m_uReadPos & (Capcity() - 1));
	auto uRightSize = Capcity() - uPos;
	auto uCopySize = std::min(uLen, uRightSize);
	memcpy(pData, &m_data[uPos]), uCopySize); 
	/* then get the rest (if any) from the beginning of the buffer */
	memcpy(pData + uCopySize, m_data, uLen - uCopySize);
 

	/*
	* Ensure that we remove the bytes from the kfifo -before-
	* we update the m_uReadPos index.
	加内存屏障，保证在修改m_uReadPos前，已经从buffer中取走了数据，如果不加屏障，可能先执行了增加m_uReadPos的操作，数据还没取完，令一个CPU可能已经往buffer写数据，将数据破坏
	*/
	// smp_mb();
	// __sync_synchronize();
	std::atomic_thread_fence(std::memory_order_release);

	/*
	这里 只是用了 m_uReadPos += uLen而未取模，用到了unsigned int的溢出性质，当m_uReadPos持续增加到溢出时又会被置为0，这样就节省了每次m_uReadPos向前增加都要取模的性能
	*/
	m_uReadPos += uLen;
	return uLen;
}


template<uint32_t uCapcity>
uint32_t C_RingBuffer::Capcity() const
{
	return uCapcity;
}

template<uint32_t uCapcity>
uint32_t C_RingBuffer::Size() const
{
	return (m_uWritePos - m_uReadPos);
}

template<uint32_t uCapcity>
uint32_t C_RingBuffer::Space() const
{
	return Capcity() - Size();
}

template<uint32_t uCapcity>
bool C_RingBuffer::Empty() const
{
	return m_uReadPos == m_uWritePos;
}
} // end namespace NBSN

 