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
class I_URL : public std::enable_shared_from_this<I_URL> {
public:
	typedef std::shared_ptr<I_URL> T_SPI_URL;

public:
	virtual void Parse(std::string const& strURL) = 0;

public:
	T_SPI_URL GetSPI_URL() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	virtual ~I_URL() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End