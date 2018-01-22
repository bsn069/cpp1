#pragma once

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_net.h>


#include <boost/function.hpp>

#include <stdint.h>
#include <memory>
#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class I_SendMail : public std::enable_shared_from_this<I_SendMail> {
public:
	typedef std::shared_ptr<I_SendMail> T_SPI_SendMail;

public:
 

public:
	T_SPI_SendMail GetSPI_SendMail() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_SendMail() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End