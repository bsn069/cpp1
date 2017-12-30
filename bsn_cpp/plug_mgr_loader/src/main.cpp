#include <bsn_cpp/plug_mgr/include/port.h>
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/d_out.h>

int main(int argc, char* argv[]) {
	D_OutInfo();
	D_N1(plug_mgr)::I_PlugMgr::T_SPI_PlugMgr 
		spI_PlugMgr = D_N1(plug_mgr)::NewPlugMgr();
	D_OutInfo();
	spI_PlugMgr->Run();
	D_OutInfo();
	spI_PlugMgr = nullptr;
	D_OutInfo();
}
