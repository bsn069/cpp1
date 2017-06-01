#include <bsn/template_console/include/t/t.h>

class C_B1
{
public:
	C_B1(){ cout << "C_B1()" << endl; }
	~C_B1(){ cout << "~C_B1()" << endl; }

	T_void B1(){ cout << "C_B1 virtual T_void B1()" << endl; }
	T_void B11(){ cout << "C_B1 virtual T_void B11()" << endl; }
};

class C_B2
{
public:
	T_int32	m_i32B2;

	C_B2(){ cout << "C_B2()" << endl; }
	~C_B2(){ cout << "~C_B2()" << endl; }

	T_void B2(){ cout << "C_B2 virtual T_void B2()" << endl; }
	T_void B21(){ cout << "C_B2 virtual T_void B21()" << endl; }
};

class C_B3 : public C_B1
{
public:
	T_int32	m_i32B3;

	C_B3(){ cout << "C_B3()" << endl; }
	~C_B3(){ cout << "~C_B3()" << endl; }

	T_void B3(){ cout << "C_B3 virtual T_void B3()" << endl; }
	T_void B31(){ cout << "C_B3 virtual T_void B31()" << endl; }
};

class C_B4 : public C_B1
{
public:
	C_B4(){ cout << "C_B4()" << endl; }
	~C_B4(){ cout << "~C_B4()" << endl; }

	T_void B4(){ cout << "C_B4 virtual T_void B4()" << endl; }
	T_void B41(){ cout << "C_B4 virtual T_void B41()" << endl; }
};

class C_B5 : public C_B2
{
public:
	C_B5(){ cout << "C_B5()" << endl; }
	~C_B5(){ cout << "~C_B5()" << endl; }

	T_void B5(){ cout << "C_B5 virtual T_void B5()" << endl; }
	T_void B51(){ cout << "C_B5 virtual T_void B51()" << endl; }
};

class C_B6 : public C_B2
{
public:
	T_int32 m_i32B6;

	C_B6(){ cout << "C_B6()" << endl; }
	~C_B6(){ cout << "~C_B6()" << endl; }

	T_void B6(){ cout << "C_B6 virtual T_void B6()" << endl; }
	T_void B61(){ cout << "C_B6 virtual T_void B61()" << endl; }
};


class C_C1 
{
public:
	C_C1(){ cout << "C_C1()" << endl; }
	virtual ~C_C1(){ cout << "~C_C1()" << endl; }

	virtual T_void C1(){ cout << "C_C1 virtual T_void C1()" << endl; }
	virtual T_void C11(){ cout << "C_C1 virtual T_void C11()" << endl; }
};

class C_C2
{
public:
	C_C2(){ cout << "C_C2()" << endl; }
	virtual ~C_C2(){ cout << "~C_C2()" << endl; }

	virtual T_void C2(){ cout << "C_C2 virtual T_void C2()" << endl; }
	virtual T_void C21(){ cout << "C_C2 virtual T_void C21()" << endl; }
};

class C_C0
{
public:
	T_int32 m_i32C0;

	C_C0(){ cout << "C_C0()" << endl; }
	virtual ~C_C0(){ cout << "~C_C0()" << endl; }

	virtual T_void C0(){ cout << "C_C0 virtual T_void C0()" << endl; }
	virtual T_void C01(){ cout << "C_C0 virtual T_void C01()" << endl; }
};

class C_CX
{
public:
	T_int32 m_i32CX;

	C_CX(){ cout << "C_CX()" << endl; }
	virtual ~C_CX(){ cout << "~C_CX()" << endl; }

	virtual T_void CX(){ cout << "C_CX virtual T_void CX()" << endl; }
	virtual T_void CX1(){ cout << "C_CX virtual T_void CX1()" << endl; }
};

class C_C3 : public C_C1, public C_C2, public C_C0, public C_CX
{
public:
	C_C3(){ cout << "C_C3()" << endl; }
	virtual ~C_C3(){ cout << "~C_C3()" << endl; }

	virtual T_void C3(){ cout << "C_C3 virtual T_void C3()" << endl; }
	virtual T_void C31(){ cout << "C_C3 virtual T_void C31()" << endl; }
};


class C_D1 : public C_B2, public C_CX, public C_C0
{
public:
	T_int32 m_i32D1;

	C_D1(){ cout << "C_D1()" << endl; }
	~C_D1(){ cout << "~C_D1()" << endl; }

	virtual T_void CD1(){ cout << "C_D1 virtual T_void CD1()" << endl; }
};

class C_D2 : public C_B2
{
public:
	T_int32 m_i32D2;

	C_D2(){ cout << "C_D2()" << endl; }
	~C_D2(){ cout << "~C_D2()" << endl; }

	virtual T_void CD2(){ cout << "C_D2 virtual T_void CD2()" << endl; }
};

T_void
virtual_()
{
	std::ostream::fmtflags old = cout.flags();
	cout << std::hex << std::setiosflags(std::ios::uppercase) << std::setfill('0');
	{
		cout << endl;
		C_B1 b1;
		C_B2 b2;
		C_B3 b3;
		C_B4 b4;
		C_B5 b5;
		C_B6 b6;
		C_CX cx;
		C_C0 c0;
		C_C1 c1;
		C_C2 c2;
		C_C3 c3;
		C_D1 d1;
		d1.m_i32B2 = 1;
		d1.m_i32CX = 2;
		d1.m_i32C0 = 3;
		d1.m_i32D1 = 4;
		C_D2 d2;
		d2.m_i32B2 = 1;
		d2.m_i32D2 = 2;
		{
			cout << "���麯����̳����麯���� �ڴ�(�麯��ָ�� �����Ա �Լ��ĳ�Ա)" << endl;
			T_int32* vt = (T_int32*)&d2;
			cout << "d1" << endl;
			for (auto x = 0; x < 3; ++x)
			{
				cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
			}
		}
		{
			cout << "�̳���(�������麯��) ���麯���Ļ������ȷŵ�ǰ�� �ڴ�(���麯������ ���麯����)" << endl;
			BOOST_STATIC_ASSERT(sizeof(C_D1) == sizeof(C_B2) + sizeof(C_CX) + sizeof(C_C0) + sizeof(d1.m_i32D1));
			T_int32* vt = (T_int32*)&d1;
			cout << "d1" << endl;
			for (auto x = 0; x < 6; ++x)
			{
				cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
			}
		}
		{
			cout << "���麯������ ����������������һ��vptrָ������ʵ���Ŀ�ʼλ�� sizeof=ptrdiff_t" << endl;
			cout << "���麯������ ��Ȼ���������" << endl;
			BOOST_STATIC_ASSERT_MSG(sizeof(C_C1) == sizeof(ptrdiff_t), "���麯���Ŀ��� sizeof=ptrdiff_t");
			BOOST_STATIC_ASSERT_MSG(sizeof(C_C0) == sizeof(c0.m_i32C0) + sizeof(ptrdiff_t), "���麯���ķǿ��� sizeof=ptrdiff_t + ��Ա����ռ�õĿռ�");
		}
		{
			cout << "��ļ̳й�ϵ�ж��ǿ��� sizeof=1" << endl;
			cout << "��ļ̳й�ϵ���зǿ��� sizeof=�������Ա����ռ�õĿռ�" << endl;
			BOOST_STATIC_ASSERT_MSG(sizeof(C_B1) == 1, "���� sizeof=1");
			BOOST_STATIC_ASSERT_MSG(sizeof(C_B2) == sizeof(b2.m_i32B2), "�ǿ��� sizeof=��Ա����ռ�õĿռ�");
			BOOST_STATIC_ASSERT_MSG(sizeof(C_B3) == sizeof(b3.m_i32B3), "�ǿ���̳п��� sizeof=�������Ա����ռ�õĿռ�");
			BOOST_STATIC_ASSERT_MSG(sizeof(C_B4) == 1, "����̳п��� sizeof=1");
			BOOST_STATIC_ASSERT_MSG(sizeof(C_B5) == sizeof(b5.m_i32B2), "����̳зǿ��� sizeof=�������Ա����ռ�õĿռ�");
			BOOST_STATIC_ASSERT_MSG(sizeof(C_B6) == sizeof(b6.m_i32B2) + sizeof(b6.m_i32B6), "�ǿ���̳зǿ��� sizeof=�������Ա����ռ�õĿռ�");
		}

		c3.m_i32C0 = 3;
		c3.m_i32CX = 4;

		printf("&c1 =0X%08X\n", &c1);
		T_int32* vt = (T_int32*)&c1;
		for (auto x = 0; x < 1; ++x)
		{
			cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
		}

		printf("&c2 =0X%08X\n", &c2);
		vt = (T_int32*)&c2;
		for (auto x = 0; x < 1; ++x)
		{
			cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
		}

		printf("&c3 =0X%08X\n", &c3);
		vt = (T_int32*)&c3;
		for (auto x = 0; x < 6; ++x)
		{
			cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
		}
		cout << "��Ա������ַ ���麯������ĵ�ַ�ǲ�һ���� ����ָ��һ��e9��ת ������ʵ�ֵ�" << endl;
		printf("&C_C1::C1  =0X%08X\n", &C_C1::C1 );
		printf("&C_C1::C11 =0X%08X\n", &C_C1::C11);
		{
			typedef T_void(C_C3::*T_F)(T_void);
			T_F fun;
			{
				cout << "��Ա����ָ������ 2��ָ�볤�� Ӧ������this���" << endl;
				BOOST_STATIC_ASSERT(sizeof(T_F) == 2 * sizeof(ptrdiff_t));
				T_F* pTest = 0;
				BOOST_ASSERT(sizeof(T_F) == (size_t)(pTest + 1));
			}
			cout << "���̳�˳�� �Ѷ�������� ÿ��������麯����ָ���ڶ���ʼ��" << endl;
			{
				cout << "pvtb_c1=" << endl;
				T_int32* pvtb = (T_int32*)(*((T_int32*)&c3 + 0));
				for (auto x = 0; x < 3; ++x)
				{
					fun = *(T_F*)&pvtb[x];
					printf("c1.vptr[%u] =0X%08X\n", x, fun);
					if (0 != x)
					{// ���������ڵ�һ��λ����
						(c3.*fun)();
					}
				}
				cout << "�Լ����麯������ ��һ�������麯���ĺ���" << endl;
				for (auto x = 3; x < (3 + 2); ++x)
				{
					fun = *(T_F*)&pvtb[x];
					printf("c3.vptr[%u] =0X%08X\n", x, fun);
					{// ���������ڵ�һ��λ����
						(c3.*fun)();
					}
				}
			}
			{
				cout << "pvtb_c2=" << endl;
				T_int32* pvtb = (T_int32*)(*((T_int32*)&c3 + 1));
				for (auto x = 0; x < 3; ++x)
				{
					fun = *(T_F*)&pvtb[x];
					printf("c2.vptr[%u] =0X%08X\n", x, fun);
					if (0 != x)
					{// ���������ڵ�һ��λ����
						(c3.*fun)();
					}
				}
			}
			{
				cout << "pvtb_c0=" << endl;
				T_int32* pvtb = (T_int32*)(*((T_int32*)&c3 + 2));
				for (auto x = 0; x < 3; ++x)
				{
					fun = *(T_F*)&pvtb[x];
					printf("c0.vptr[%u] =0X%08X\n", x, fun);
					if (0 != x)
					{// ���������ڵ�һ��λ����
						(c3.*fun)();
					}
				}
			}
			{
				cout << "pvtb_cx=" << endl;
				T_int32* pvtb = (T_int32*)(*((T_int32*)&c3 + 4));
				for (auto x = 0; x < 3; ++x)
				{
					fun = *(T_F*)&pvtb[x];
					printf("cx.vptr[%u] =0X%08X\n", x, fun);
					if (0 != x)
					{// ���������ڵ�һ��λ����
						(c3.*fun)();
					}
				}
			}
		}
	}

	/*
	{
		cout << endl;
		C_B i,j;
		i.m_i32b = 1;
		j.m_i32b = 2;
		typedef T_void(C_B::*T_F)(T_void);
		T_F f1 = &C_B::V1;
		printf("&C_B::V1 =0X%08X\n", (T_F)&C_B::V1);
		printf("&C_B::V2 =0X%08X\n", &C_B::V2);
		printf("&C_B::V3 =0X%08X\n", &C_B::V3);

		printf("&i =0X%08X\n", &i);
		T_int32* vt = (T_int32*)&i;
		for (auto x = 0; x < 2; ++x)
		{
			cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
		}

		printf("&j =0X%08X\n", &j);
		vt = (T_int32*)&j;
		for (auto x = 0; x < 2; ++x)
		{
			cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
		}

		cout << "D_ArrayByte(C_B)=" << D_ArrayByte(C_B) << endl;
		cout << "D_ArrayByte(i)=" << D_ArrayByte(i) << endl;

		T_F* pf = (T_F*)(*(T_int32*)&j);
		for (auto x = 0; x < 3; ++x)
		{
			printf("&i =0X%08X\n", pf[x]);
			(i.*pf[x])();
		}

	}
	{
		cout << endl;
		C_B1 i, j;
		i.m_i32b = 1;
		j.m_i32b = 2;
		typedef T_void(C_B1::*T_F)(T_void);
		T_F f1 = &C_B1::V1;
		C_B* pi = &i;
		pi->V1();
		pi->V2();
		pi->V3();
		printf("&C_B1::V1 =0X%08X\n", &C_B1::V1);
		printf("&C_B1::V2 =0X%08X\n", &C_B1::V2);
		printf("&C_B1::V3 =0X%08X\n", &C_B1::V3);
		printf("&C_B1::V4 =0X%08X\n", &C_B1::V4);

		printf("&i =0X%08X\n", &i);
		T_int32* vt = (T_int32*)&i;
		for (auto x = 0; x < 2; ++x)
		{
			cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
		}

		printf("&j =0X%08X\n", &j);
		vt = (T_int32*)&j;
		for (auto x = 0; x < 2; ++x)
		{
			cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
		}

		cout << "D_ArrayByte(C_B)=" << D_ArrayByte(C_B) << endl;
		cout << "D_ArrayByte(i)=" << D_ArrayByte(i) << endl;

		T_F* pf = (T_F*)(*(T_int32*)&i);
		for (auto x = 0; x < 3; ++x)
		{
			printf("&i =0X%08X\n", pf[x]);
			(i.*pf[x])();
		}
		// 3 �ǻ�������һ���麯�� ������ ���õĻ��ᱨ���
		printf("&i =0X%08X\n", pf[4]);
		(i.*pf[4])();
	}
	{
		cout << endl;
		C_B2 i, j;
		i.m_i32b = 1;
		j.m_i32b = 2;
		typedef T_void(C_B2::*T_F)(T_void);
		T_F f1 = &C_B2::V1;
		C_B* pi = &i;
		pi->V1();
		pi->V2();
		pi->V3();
		i.V4();
		i.VA1();

		printf("&C_B2::V1 =0X%08X\n", &C_B2::V1);
		printf("&C_B2::V2 =0X%08X\n", &C_B2::V2);
		printf("&C_B2::V3 =0X%08X\n", &C_B2::V3);
		printf("&C_B2::V4 =0X%08X\n", &C_B2::V4);

		printf("&i =0X%08X\n", &i);
		T_int32* vt = (T_int32*)&i;
		for (auto x = 0; x < 3; ++x)
		{
			cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
		}

		printf("&j =0X%08X\n", &j);
		vt = (T_int32*)&j;
		for (auto x = 0; x < 3; ++x)
		{
			cout << x << " = 0X" << std::setw(8) << vt[x] << endl;
		}

		cout << "D_ArrayByte(C_B2)=" << D_ArrayByte(C_B2) << endl;
		cout << "D_ArrayByte(i)=" << D_ArrayByte(i) << endl;

		T_F* pf = (T_F*)(*((T_int32*)&i + 0));
		for (auto x = 0; x < 3; ++x)
		{
			printf("&i =0X%08X\n", pf[x]);
			if (!pf[x])
			{
				break;
			}
			(i.*pf[x])();
		}
		for (auto x = 4; x < 10; ++x)
		{
			printf("&i =0X%08X\n", pf[x]);
			if (!pf[x])
			{
				break;
			}
			(i.*pf[x])();
		}

		pf = (T_F*)(*((T_int32*)&i + 2));
		for (auto x = 0; x < 3; ++x)
		{
			printf("&i =0X%08X\n", pf[x]);
			if (!pf[x])
			{
				break;
			}
			(i.*pf[x])();
		}
	}
	{
		cout << endl;
		cout << "��������1byte" << endl;
		C_A a;
		cout << "D_ArrayByte(C_A)=" << D_ArrayByte(C_A) << endl;
		cout << "D_ArrayByte(a)=" << D_ArrayByte(a) << endl;
		cout << "(T_uint32)&a=0X" << std::setw(8) << (T_uint32)&a << endl;
	}
	{
		cout << endl;
		cout << "���С�ǳ�Ա������С" << endl;
		C_A1 a;
		cout << "D_ArrayByte(C_A1)=" << D_ArrayByte(C_A1) << endl;
		cout << "D_ArrayByte(a)=" << D_ArrayByte(a) << endl;
		cout << "(T_uint32)&a=0X" << std::setw(8) << (T_uint32)&a << endl;
	}
	{
		cout << endl;
		cout << "���С�ǳ�Ա����������С " << endl;
		C_A2 a;
		cout << "D_ArrayByte(C_A2)=" << D_ArrayByte(C_A2) << endl;
		cout << "D_ArrayByte(a)=" << D_ArrayByte(a) << endl;
		cout << "(T_uint32)&a=0X" << std::setw(8) << (T_uint32)&a << endl;
	}
	{
		cout << endl;
		cout << "���麯���ᵼ�������麯��ָ���С" << endl;
		C_A3 a;
		cout << "D_ArrayByte(C_A3)=" << D_ArrayByte(C_A3) << endl;
		cout << "D_ArrayByte(a)=" << D_ArrayByte(a) << endl;
		cout << "(T_uint32)&a=0X" << std::setw(8) << (T_uint32)&a << endl;
	}
	*/
	cout.flags(old);
} 
