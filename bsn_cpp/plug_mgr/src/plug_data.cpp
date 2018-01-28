#include <bsn_cpp/plug_mgr/src/plug_data.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/function.hpp>
#include <boost/format.hpp>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugData::T_Name2FuncCreatePlugData C_PlugData::m_Name2FuncCreatePlugData;

C_PlugData::C_PlugData(std::string strName, I_PlugMgr::T_SPI_PlugMgr spI_PlugMgr) 
	: m_strName(strName) 
	, m_pData(nullptr)
{
	D_OutInfo1(m_strName);

	auto pCreatePlugDataFunc = m_Name2FuncCreatePlugData[strName];
	if (pCreatePlugDataFunc == nullptr) {

	} else {
		m_pData = pCreatePlugDataFunc(spI_PlugMgr);
	}
}

C_PlugData::~C_PlugData() {
	D_OutInfo1(m_strName);
	
	UnLoadPlug();
	UnLoadLib();

	Delete(m_pData);
}

bool C_PlugData::Awake() {
	D_OutInfo1(m_strName);
	if (m_spI_Plug == nullptr) {
		D_OutInfo1("m_spI_Plug == nullptr");
		return false;
	}

	return m_spI_Plug->Awake();
}

bool C_PlugData::Init(I_PlugMgr::T_SPI_PlugMgr spI_PlugMgr) {
	D_OutInfo1(m_strName);
	if (m_spI_Plug == nullptr) {
		D_OutInfo1("m_spI_Plug == nullptr");
		return false;
	}

	return m_spI_Plug->Init(spI_PlugMgr);
}

bool C_PlugData::AllInitAfter() {
	D_OutInfo1(m_strName);
	if (m_spI_Plug == nullptr) {
		D_OutInfo1("m_spI_Plug == nullptr");
		return false;
	}

	return m_spI_Plug->AllInitAfter();
}

bool C_PlugData::Update() {
	D_OutInfo1(m_strName);
	if (m_spI_Plug == nullptr) {
		D_OutInfo1("m_spI_Plug == nullptr");
		return false;
	}

	return m_spI_Plug->Update();
}

bool C_PlugData::Quit() {
	D_OutInfo1(m_strName);
	if (m_spI_Plug == nullptr) {
		D_OutInfo1("m_spI_Plug == nullptr");
		return false;
	}

	return m_spI_Plug->Quit();
}

bool C_PlugData::UnInit() {
	D_OutInfo1(m_strName);
	if (m_spI_Plug == nullptr) {
		D_OutInfo1("m_spI_Plug == nullptr");
		return false;
	}

	return m_spI_Plug->UnInit();
}

void C_PlugData::OnReloadPre(std::string const& strName) {
	D_OutInfo1(m_strName);
	if (m_spI_Plug == nullptr) {
		D_OutInfo1("m_spI_Plug == nullptr");
		return;
	}

	m_spI_Plug->OnReloadPre(strName);
}

void C_PlugData::OnReloadPost(std::string const& strName) {
	D_OutInfo1(m_strName);
	if (m_spI_Plug == nullptr) {
		D_OutInfo1("m_spI_Plug == nullptr");
		return;
	}

	m_spI_Plug->OnReloadPost(strName);
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
		D_OutInfo1("plug had loaded");
		return false;
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

	if (m_pData == nullptr) {
		D_OutInfo1("m_pData == nullptr");
		// return false;
	}

	typedef I_Plug::T_SPI_Plug	(T_CreatePlug)(void*);
	auto pFunc = m_lib.get<T_CreatePlug>("CreatePlug");
	D_OutInfo2("pFunc=", pFunc);
	m_spI_Plug = pFunc(m_pData);
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