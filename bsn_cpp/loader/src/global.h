#include <bsn_cpp/common/include/port.h>
#include <bsn_cpp/load_lib/include/port.h>
#include <bsn_cpp/log/include/port.h>
#include <bsn_cpp/net/include/port.h>

#include <boost/asio.hpp>

class C_Global {
public:
	uint32_t 									m_u32FrameMS;
	boost::asio::io_service 					m_ioService;
	boost::asio::deadline_timer 				m_updateTimer;
	D_N1(common)::I_Common::T_SPI_Common 		m_spI_Common;
	D_N1(common)::I_Alloc::T_SPI_Alloc 			m_spI_AllocRaw;
	D_N1(load_lib)::I_LoadLib::T_SPI_LoadLib	m_spI_LoadLib;
	D_N1(log)::I_Log::T_SPI_Log 				m_spI_Log;
	D_N1(net)::I_Net::T_SPI_Net 				m_spI_Net;

public:
	void Run();
	
public:
	C_Global();
	~C_Global();

private:
	void Init();
	void UnInit();
	void WaitUpdate();
	void Update();
}
