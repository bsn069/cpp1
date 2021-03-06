#include <bsn_cpp/plug_base64/src/plug_base64.h>

#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>
#include <bsn_cpp/plug_cmd/include/i_plug_cmd.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>

#include <cryptopp/base64.h>

#include <iostream>  
#include <string>  
#include <sstream>  

using namespace std;  

D_BsnNamespace1(plug_base64)
//////////////////////////////////////////////////////////////////////
C_PlugBase64::C_PlugBase64(void* pData) {
	D_OutInfo();
}

C_PlugBase64::~C_PlugBase64() {
	D_OutInfo();
 
}

bool C_PlugBase64::Decode(std::string const& strInput, std::string& strOut) {  
    CryptoPP::Base64Decoder decoder; 
    decoder.PutMessageEnd((const uint8_t*)strInput.c_str(), strInput.size(), -1, false);  //如果base64中有\n请使用true
    if (!decoder.AnyRetrievable()) {
        return false;
    }
    auto neededLength = decoder.MaxRetrievable();
    strOut.resize(neededLength);
    decoder.Get((uint8_t*)strOut.data(), neededLength); 
    return true;
}  

bool C_PlugBase64::Encode(std::string const& strInput, std::string& strOut) {  
    CryptoPP::Base64Encoder encoder; 
    encoder.PutMessageEnd((const uint8_t*)strInput.c_str(), strInput.size(), -1, true);  //如果base64中有\n请使用true
    if (!encoder.AnyRetrievable()) {
        return false;
    }
    auto neededLength = encoder.MaxRetrievable();
    strOut.resize(neededLength);
    encoder.Get((uint8_t*)strOut.data(), neededLength); 
    return true;
}  

char const * const C_PlugBase64::GetName() const {
	return "base64";
}

bool C_PlugBase64::OnLoad(std::set<std::string>& needPlugNames) {
	D_OutInfo();

	needPlugNames.insert("cmd");

	return true;
}

void C_PlugBase64::ProcCmd(std::string const& strCmd) {
	
}

bool C_PlugBase64::Init(T_SPI_PlugMgr spI_PlugMgr) {
	D_OutInfo();
	m_spI_PlugMgr = spI_PlugMgr;
	return true;
}

bool C_PlugBase64::AllInitAfter() {
	D_OutInfo();

	RegAllCmd();
	
	return true;
}

bool C_PlugBase64::RegAllCmd() {
	D_OutInfo();

	auto spI_PlugCmd = m_spI_PlugMgr->GetPlugPtr<D_N1(plug_cmd)::I_PlugCmd>("cmd");
	if (!spI_PlugCmd) {
		return false;
	}

	spI_PlugCmd->RegPlugCmd(GetName(), "help", boost::bind(&C_PlugBase64::CmdHelp, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "Encode", boost::bind(&C_PlugBase64::CmdEncode, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "Decode", boost::bind(&C_PlugBase64::CmdDecode, this, _1, _2));

	return true;
}

void C_PlugBase64::CmdHelp(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
}

void C_PlugBase64::CmdEncode(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
    std::string strOut;
    Encode(strParam, strOut);
    D_OutInfo2("encode=", strOut);
}

void C_PlugBase64::CmdDecode(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
    std::string strOut;
    Decode(strParam, strOut);
    D_OutInfo2("encode=", strOut);
}

bool C_PlugBase64::Update() {
	// D_OutInfo();
	return true;
}

bool C_PlugBase64::Quit() {
	D_OutInfo();
 
	return true;
}

bool C_PlugBase64::UnInit() {
	D_OutInfo();
	m_spI_PlugMgr = nullptr;
	return true;
}

void C_PlugBase64::OnReloadPre(std::string const& strName) {
	D_OutInfo();
	
}

void C_PlugBase64::OnReloadPost(std::string const& strName) {
	D_OutInfo();
	
	if (strName.compare("cmd") == 0) {
		RegAllCmd();
	}
}

C_PlugBase64::T_SPC_PlugBase64 C_PlugBase64::GetSPC_PlugBase64() {
	D_OutInfo();
	auto spI_Plug = GetSPI_Plug();
	auto spC_PlugBase64 = std::dynamic_pointer_cast<C_PlugBase64>(spI_Plug);
	return spC_PlugBase64;
}

//////////////////////////////////////////////////////////////////////
C_PlugBase64* CreateC_PlugBase64(void* pData) {
	D_OutInfo();
	C_PlugBase64* pC_PlugBase64 = New<C_PlugBase64>(pData);
	return pC_PlugBase64;
}

void ReleaseC_PlugBase64(I_PlugBase64* pI_PlugBase64) {
	D_OutInfo();
	C_PlugBase64* pC_PlugBase64 = static_cast<C_PlugBase64*>(pI_PlugBase64);
	Delete(pC_PlugBase64);
}

C_PlugBase64::T_SPC_PlugBase64 C_PlugBase64::NewC_PlugBase64(void* pData) {
	D_OutInfo();
	auto pC_PlugBase64 = CreateC_PlugBase64(pData);
	auto spC_PlugBase64 = C_PlugBase64::T_SPC_PlugBase64(pC_PlugBase64, ReleaseC_PlugBase64);
	return spC_PlugBase64;
}

C_PlugBase64::T_SPI_PlugBase64 C_PlugBase64::NewI_PlugBase64(void* pData) {
	D_OutInfo();
	auto spC_PlugBase64 = C_PlugBase64::NewC_PlugBase64(pData);
	auto spI_PlugBase64 = spC_PlugBase64->GetSPI_PlugBase64();
	return spI_PlugBase64;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif