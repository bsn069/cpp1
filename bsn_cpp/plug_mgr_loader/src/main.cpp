#include <bsn_cpp/plug_mgr/include/port.h>
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/d_out.h>

int main(int argc, char* argv[]) {
	D_OutInfo();

	if (argc != 2) {
		D_OutInfo1("not config file");
		return -1;
	}
	
	D_N1(plug_mgr)::I_PlugMgr::T_SPI_PlugMgr 
		spI_PlugMgr = D_N1(plug_mgr)::NewPlugMgr();
	D_OutInfo();
	spI_PlugMgr->Run(argv[1]);
	D_OutInfo();
	spI_PlugMgr = nullptr;
	D_OutInfo();
}
