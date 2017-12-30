#include "plug_data.h"

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/define.h>

#include <boost/function.hpp>
#include <boost/format.hpp>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugData::C_PlugData(std::string strName) 
	: m_strName(strName) 
{
	D_OutInfo1(m_strName);
}

C_PlugData::~C_PlugData() {
	D_OutInfo1(m_strName);
 
	UnLoadPlug();
	UnLoadLib();
}

bool C_PlugData::LoadLib() {
	D_OutInfo1(m_strName);
	
	if (m_lib.is_loaded()) {
		D_OutInfo1("had loaded");
		return false;
	}

	auto strLibName = boost::str(boost::format("bsn_dlib_plug_%1%_d") % m_strName);
	D_OutInfo2("strLibName=", strLibName);

	boost::system::error_code ec;
	m_lib.load(strLibName, ec, boost::dll::load_mode::append_decorations);
	if (ec) {
		D_OutInfo3("ec=", ec, ec.message());
		return false;
	}

	if (!m_lib.has("CreatePlug")) {
		D_OutInfo1("not found symbol CreatePlug");
		UnLoadLib();
		return false;
	}

	return true;
}

bool C_PlugData::UnLoadLib() {
	D_OutInfo1(m_strName);
	
	if (!m_lib.is_loaded()) {
		D_OutInfo1("not loaded");
		return false;
	}

	if (m_spI_Plug) {
		UnLoadPlug();
	}

	m_lib.unload();

	return true;
}

bool C_PlugData::LoadPlug() {
	D_OutInfo1(m_strName);

	if (m_spI_Plug) {
		D_OutInfo1("had load plug");
		return false;
	}

	if (!m_lib.is_loaded()) {
		D_OutInfo1("not loaded lib");
		return false;
	}

	typedef I_Plug::T_SPI_Plug	(T_CreatePlug)();
	auto pFunc = m_lib.get<T_CreatePlug>("CreatePlug");
	D_OutInfo2("pFunc=", pFunc);
	m_spI_Plug = pFunc();
	D_OutInfo2("m_spI_Plug=", m_spI_Plug.get());

	return true;
}

bool C_PlugData::UnLoadPlug() {
	D_OutInfo1(m_strName);

	if (!m_spI_Plug) {
		D_OutInfo1("not load plug");
		return false;
	}

	if (!m_lib.is_loaded()) {
		D_OutInfo1("not loaded lib");
		return false;
	}

	D_OutInfo3("m_spI_Plug=", m_spI_Plug.get(), m_spI_Plug.use_count());
	if (m_spI_Plug.use_count() != 1) {
		D_OutInfo1("had use by other");
		return false;
	}

	m_spI_Plug = nullptr;
	return true;
}

std::string const& C_PlugData::GetName() {
	return m_strName;
}

I_Plug::T_SPI_Plug C_PlugData::GetPlug() {
	return m_spI_Plug;
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif