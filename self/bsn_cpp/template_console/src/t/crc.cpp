#include <bsn/template_console/include/t/t.h>


T_void
crc_()
{
	using namespace boost;
	{
		crc_32_type crc32;
		cout << std::hex;
		cout << crc32.checksum() << endl;

		crc32.reset();
		crc32.process_byte(1);
		cout << crc32.checksum() << endl;
		
		crc32.reset();
		crc32.process_bytes("1234567890", 10);
		cout << crc32.checksum() << endl;

		char a[] = "1234567890";
		crc32.reset();
		crc32.process_block(a, a + 10);
		cout << crc32.checksum() << endl;

		string str = "1234567890";
		crc32.reset();
		crc32 = std::for_each(str.begin(), str.end(), crc32);
		cout << crc32() << endl;
	}
}
