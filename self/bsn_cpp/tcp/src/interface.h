#pragma once

#include "./main.h"
#include "./../include/i_interface.h"
#include <asio.hpp>
D_BsnNamespace1(TCP)


class C_Interface : public I_Interface
{
public:
	asio::io_service		m_IOService;
	asio::io_service::work*	m_pWork;
	boost::thread_group		m_ThreadGroup;

public:
	C_Interface();
	virtual ~C_Interface() {};


public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

	virtual T_int32 D_const CreateServer(I_Server*& pServer) override;
	virtual T_int32 D_const ReleaseServer(I_Server*& pServer) override;

	virtual T_int32 D_const CreateClient(I_Client*& pClient) override;
	virtual T_int32 D_const ReleaseClient(I_Client*& pClient) override;

	virtual T_int32 D_const Start() override;

	T_bool D_const IsStart() D_const {return (T_nullptr != m_pWork);};
	T_int32 D_const Stop();
};


D_BsnNamespace1End
