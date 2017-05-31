#include <bsn/template_console/include/t/t.h>

T_void 
integer_traits_()
{
	
	wcout << L"integer_traits<int>::const_min= " << integer_traits<int>::const_min << endl;
	wcout << L"integer_traits<int>::const_max= " << integer_traits<int>::const_max << endl;
	wcout << L"" << endl;
	wcout << L"integer_traits<T_int8>::const_min= " << integer_traits<T_int8>::const_min << endl;
	wcout << L"integer_traits<T_int16>::const_min= " << integer_traits<T_int16>::const_min << endl;
	wcout << L"integer_traits<T_int32>::const_min= " << integer_traits<T_int32>::const_min << endl;
	wcout << L"integer_traits<T_int64>::const_min= " << integer_traits<T_int64>::const_min << endl;
	wcout << L"integer_traits<T_int8>::const_max= " << integer_traits<T_int8>::const_max << endl;
	wcout << L"integer_traits<T_int16>::const_max= " << integer_traits<T_int16>::const_max << endl;
	wcout << L"integer_traits<T_int32>::const_max= " << integer_traits<T_int32>::const_max << endl;
	wcout << L"integer_traits<T_int64>::const_max= " << integer_traits<T_int64>::const_max << endl;
	wcout << L"" << endl;
	
	wcout << L"integer_traits<unsigned int>::const_min= " << integer_traits<unsigned int>::const_min << endl;
	wcout << L"integer_traits<unsigned int>::const_max= " << integer_traits<unsigned int>::const_max << endl;
	wcout << L"" << endl;
	wcout << L"integer_traits<T_uint8>::const_min= " << integer_traits<T_uint8>::const_min << endl;
	wcout << L"integer_traits<T_uint16>::const_min= " << integer_traits<T_uint16>::const_min << endl;
	wcout << L"integer_traits<T_uint32>::const_min= " << integer_traits<T_uint32>::const_min << endl;
	wcout << L"integer_traits<T_uint64>::const_min= " << integer_traits<T_uint64>::const_min << endl;
	wcout << L"integer_traits<T_uint8>::const_max= " <<  integer_traits<T_uint8>::const_max << endl;
	wcout << L"integer_traits<T_uint16>::const_max= " << integer_traits<T_uint16>::const_max << endl;
	wcout << L"integer_traits<T_uint32>::const_max= " << integer_traits<T_uint32>::const_max << endl;
	wcout << L"integer_traits<T_uint64>::const_max= " << integer_traits<T_uint64>::const_max << endl;
	wcout << L"" << endl;

	wcout << L"integer_traits<float>::min()= " << integer_traits<float>::min() << endl;
	wcout << L"integer_traits<float>::max()= " << integer_traits<float>::max() << endl;
	wcout << L"" << endl;

	wcout << L"integer_traits<double>::min()= " << integer_traits<double>::min() << endl;
	wcout << L"integer_traits<double>::max()= " << integer_traits<double>::max() << endl;
}

