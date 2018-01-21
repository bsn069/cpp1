#include <bsn_cpp/plug_net/src/plug_net.h>
#include <bsn_cpp/plug_net/src/dns.h>
#include <bsn_cpp/plug_net/src/http_client.h>
#include <bsn_cpp/plug_net/src/https_client.h>
#include <bsn_cpp/plug_net/src/http_server.h>
#include <bsn_cpp/plug_net/src/address.h>
#include <bsn_cpp/plug_net/src/url.h>

#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>
#include <bsn_cpp/plug_cmd/include/i_plug_cmd.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_PlugNet::C_PlugNet(void* pData) {
	D_OutInfo();
	m_pData = reinterpret_cast<T_PlugData*>(pData);
}

C_PlugNet::~C_PlugNet() {
	D_OutInfo();
 
}

char const * const C_PlugNet::GetName() const {
	return "net";
}

bool C_PlugNet::Awake() {
	D_OutInfo();

	return true;
}

bool C_PlugNet::Init(T_SPI_PlugMgr spI_PlugMgr) {
	D_OutInfo();
	m_spI_PlugMgr = spI_PlugMgr;
	return true;
}

bool C_PlugNet::AllInitAfter() {
	D_OutInfo();

	RegAllCmd();

	return true;
}

bool C_PlugNet::RegAllCmd() {
	D_OutInfo();

	auto spI_PlugCmd = m_spI_PlugMgr->GetPlugPtr<D_N1(plug_cmd)::I_PlugCmd>("cmd");
	if (!spI_PlugCmd) {
		return false;
	}

	spI_PlugCmd->RegPlugCmd(GetName(), "help", boost::bind(&C_PlugNet::CmdHelp, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "ShowIP", boost::bind(&C_PlugNet::CmdShowIP, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "ShowIPAsync", boost::bind(&C_PlugNet::CmdShowIPAsync, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "HttpGet", boost::bind(&C_PlugNet::CmdHttpGet, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "HttpGetCoro", boost::bind(&C_PlugNet::CmdHttpGetCoro, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "HttpsGet", boost::bind(&C_PlugNet::CmdHttpsGet, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "HttpServer", boost::bind(&C_PlugNet::CmdHttpServer, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "HttpGetAsync", boost::bind(&C_PlugNet::CmdHttpGetAsync, this, _1, _2));
	spI_PlugCmd->RegPlugCmd(GetName(), "URL", boost::bind(&C_PlugNet::CmdURL, this, _1, _2));

	return true;
}

void C_PlugNet::CmdHelp(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
}

void C_PlugNet::CmdShowIPAsync(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
	auto spC_Dns = C_Dns::NewC_Dns(GetSPC_PlugNet());
	spC_Dns->Domain2IPs_async(strParam, [](D_N1(plug_mgr)::C_PlugDataNet::T_IPs vecIPs){
		for (auto strIP : vecIPs) {
			D_OutInfo1(strIP);
		}
	});
}

void C_PlugNet::CmdShowIP(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
	auto spC_Dns = C_Dns::NewC_Dns(GetSPC_PlugNet());
	auto vecIPs = spC_Dns->Domain2IPs(strParam);
	for (auto strIP : vecIPs) {
		D_OutInfo1(strIP);
	}
}

void C_PlugNet::CmdHttpGet(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
	auto spC_HttpClient = C_HttpClient::NewC_HttpClient(GetSPC_PlugNet());
	auto strRet = spC_HttpClient->Get(strParam);
	D_OutInfo1(strRet);
}

void C_PlugNet::CmdHttpsGet(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
	auto spC_HttpsClient = C_HttpsClient::NewC_HttpsClient(GetSPC_PlugNet());
	auto strRet = spC_HttpsClient->Get(strParam);
	D_OutInfo1(strRet);
}

void C_PlugNet::CmdHttpGetAsync(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
	auto spC_HttpClient = C_HttpClient::NewC_HttpClient(GetSPC_PlugNet());
	spC_HttpClient->Get_async(strParam, [](){});
}

void C_PlugNet::CmdHttpGetCoro(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
	auto spC_HttpClient = C_HttpClient::NewC_HttpClient(GetSPC_PlugNet());
	spC_HttpClient->GetCoroutine(strParam);
}

void C_PlugNet::CmdHttpServer(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
 	auto spC_Address = C_Address::NewC_Address();
	spC_Address->SetAddr("0.0.0.0");
	spC_Address->SetPort(80);

	auto spC_HttpServer = C_HttpServer::NewC_HttpServer(GetSPC_PlugNet());
	spC_HttpServer->SetAddress(spC_Address);
	spC_HttpServer->Start();
}

void C_PlugNet::CmdURL(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);
 
	auto spC_URL = C_URL::NewC_URL(GetSPC_PlugNet());
	spC_URL->Parse(strParam);
}

bool C_PlugNet::Update() {
	// D_OutInfo();
	return true;
}

bool C_PlugNet::Quit() {
	D_OutInfo();
 
	return true;
}

bool C_PlugNet::UnInit() {
	D_OutInfo();
	m_spI_PlugMgr = nullptr;
	return true;
}

void C_PlugNet::OnReloadPre(std::string const& strName) {
	D_OutInfo();
	
}

void C_PlugNet::OnReloadPost(std::string const& strName) {
	D_OutInfo();
	
	if (strName.compare("cmd") == 0) {
		RegAllCmd();
	}
}

I_Dns::T_SPI_Dns C_PlugNet::NewI_Dns() {
	return C_Dns::NewI_Dns(GetSPC_PlugNet());
}


C_PlugNet::T_SPC_PlugNet C_PlugNet::GetSPC_PlugNet() {
	D_OutInfo();
	auto spI_Plug = GetSPI_Plug();
	auto spC_PlugNet = std::dynamic_pointer_cast<C_PlugNet>(spI_Plug);
	return spC_PlugNet;
}

boost::asio::io_service& C_PlugNet::GetIOService() {
	return m_pData->m_ioService;
}

//////////////////////////////////////////////////////////////////////
C_PlugNet* CreateC_PlugNet(void* pData) {
	D_OutInfo();
	C_PlugNet* pC_PlugNet = New<C_PlugNet>(pData);
	return pC_PlugNet;
}

void ReleaseC_PlugNet(I_PlugNet* pI_PlugNet) {
	D_OutInfo();
	C_PlugNet* pC_PlugNet = static_cast<C_PlugNet*>(pI_PlugNet);
	Delete(pC_PlugNet);
}

C_PlugNet::T_SPC_PlugNet C_PlugNet::NewC_PlugNet(void* pData) {
	D_OutInfo();
	auto pC_PlugNet = CreateC_PlugNet(pData);
	auto spC_PlugNet = C_PlugNet::T_SPC_PlugNet(pC_PlugNet, ReleaseC_PlugNet);
	return spC_PlugNet;
}

C_PlugNet::T_SPI_PlugNet C_PlugNet::NewI_PlugNet(void* pData) {
	D_OutInfo();
	auto spC_PlugNet = C_PlugNet::NewC_PlugNet(pData);
	auto spI_PlugNet = spC_PlugNet->GetSPI_PlugNet();
	return spI_PlugNet;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif