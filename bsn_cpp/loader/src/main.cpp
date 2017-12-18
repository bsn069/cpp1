#include <bsn_cpp/global/include/port.h>
#include <bsn_cpp/include/name_space.h>

int main(int argc, char* argv[]) {
	D_N1(global)::I_Global::T_SPI_Global spI_Global 
		= D_N1(global)::NewGlobal();
	spI_Global->Run();
	spI_Global = nullptr;
}
