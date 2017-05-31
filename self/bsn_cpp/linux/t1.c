#include <stdio.h>

/*
root@debian:/home/bsn_cpp/liunx_study# gcc -o t1 t1.c
root@debian:/home/bsn_cpp/liunx_study# ./t1
*/



/*
root@debian:/home/bsn_cpp/liunx_study# size t1
   text    data     bss     dec     hex filename
    979     276      20    1275     4fb t1

int const			gc_iTest1 = 1;
int					giTest2 = 2;
static int const	gsc_iTest3 = 3;
static int			gs_iTest4 = 4;

int					giTest6;
static int			gs_iTest7;

int main(int argc, char* argv[])
{
	printf("hello world\n");

	int const			c_iTest = 1;
	int					iTest2 = 2;
	static int const	sc_iTest3 = 3;
	static int			s_iTest4 = 4;

	int			iTest6;
	static int	s_iTest7;
	printf("-----------------\n");
}
*/


/*
root@debian:/home/bsn_cpp/liunx_study# size t1
   text    data     bss     dec     hex filename
    991     276      20    1287     507 t1

int const			gc_iTest1 = 1;
int					giTest2 = 2;
static int const	gsc_iTest3 = 3;
static int			gs_iTest4 = 4;

int					giTest6;
static int			gs_iTest7;

// ���� ��̬���� ��text��
int const			gc2_iTest1 = 1;
static int const	gsc2_iTest3 = 3;
int main(int argc, char* argv[])
{
	printf("hello world\n");

	int const			c_iTest = 1;
	int					iTest2 = 2;
	static int const	sc_iTest3 = 3;
	static int			s_iTest4 = 4;

	int			iTest6;
	static int	s_iTest7;

	// �����ﾲ̬���� ��text��
	static int const	sc2_iTest3 = 3;
	printf("-----------------\n");
}
*/



/*
root@debian:/home/bsn_cpp/liunx_study# size t1
  text    data     bss     dec     hex filename
   991     288      20    1299     513 t1

int const			gc_iTest1 = 1;
int					giTest2 = 2;
static int const	gsc_iTest3 = 3;
static int			gs_iTest4 = 4;

int					giTest6;
static int			gs_iTest7;

// ���� ��̬���� ��text��
int const			gc2_iTest1 = 1;
static int const	gsc2_iTest3 = 3;
// ȫ�ֳ�ʼ������ ��data��
int					g3iTest2 = 2;
static int			gs3_iTest4 = 4;
int main(int argc, char* argv[])
{
	printf("hello world\n");

	int const			c_iTest = 1;
	int					iTest2 = 2;
	static int const	sc_iTest3 = 3;
	static int			s_iTest4 = 4;

	int			iTest6;
	static int	s_iTest7;

	// �����ﾲ̬���� ��text��
	static int const	sc2_iTest3 = 3;
	// ��̬��ʼ������ ��data��
	static int			s3_iTest4 = 4;
	printf("-----------------\n");
}
*/


/*
root@debian:/home/bsn_cpp/liunx_study# size t1
   text    data     bss     dec     hex filename
    991     288      32    1311     51f t1

int const			gc_iTest1 = 1;
int					giTest2 = 2;
static int const	gsc_iTest3 = 3;
static int			gs_iTest4 = 4;

int					giTest6;
static int			gs_iTest7;

// ȫ�ֳ��� ��̬���� ��text��
int const			gc2_iTest1 = 1;
static int const	gsc2_iTest3 = 3;
// ȫ�ֳ�ʼ������ ��data��
int					g3iTest2 = 2;
static int			gs3_iTest4 = 4;
// ȫ��δʼ������ ��bss��
int					g4iTest6;
static int			gs4_iTest7;
int main(int argc, char* argv[])
{
	printf("hello world\n");

	int const			c_iTest = 1;
	int					iTest2 = 2;
	static int const	sc_iTest3 = 3;
	static int			s_iTest4 = 4;

	int			iTest6;
	static int	s_iTest7;

	// ������ ��̬���� ��text��
	static int const	sc2_iTest3 = 3;
	// ������ ��̬��ʼ������ ��data��
	static int			s3_iTest4 = 4;
	// ������ ��̬δʼ������ ��bss��
	static int	s4_iTest7;
	printf("-----------------\n");
}
*/


/*
root@debian:/home/bsn_cpp/liunx_study# size t1
  text    data     bss     dec     hex filename
  1011     312      32    1355     54b t1
 
int const			gc_iTest1 = 1;
int					giTest2 = 2;
static int const	gsc_iTest3 = 3;
static int			gs_iTest4 = 4;

int					giTest6;
static int			gs_iTest7;

// ȫ�ֳ��� ��̬���� ��text��
int const			gc2_iTest1 = 1;
static int const	gsc2_iTest3 = 3;
// ȫ�ֳ�ʼ������ ��data��
int					g3iTest2 = 2;
static int			gs3_iTest4 = 4;
// ȫ��δʼ������ ��bss��
int					g4iTest6;
static int			gs4_iTest7;
// g_pcTest1��g_pcTest2��data "01234"��text 
char*  g_pcTest1 = "01234";
char*  g_pcTest2 = "01234";
char*  g_pcTest3 = "0123";
char*  g_pcTest4 = "1234";
char*  g_pcTest5 = "123";
char  g_cTest1 = 'a';;
int main(int argc, char* argv[])
{
	printf("hello world\n");

	int const			c_iTest = 1;
	int					iTest2 = 2;
	static int const	sc_iTest3 = 3;
	static int			s_iTest4 = 4;

	int			iTest6;
	static int	s_iTest7;

	// ������ ��̬���� ��text��
	static int const	sc2_iTest3 = 3;
	// ������ ��̬��ʼ������ ��data��
	static int			s3_iTest4 = 4;
	// ������ ��̬δʼ������ ��bss��
	static int	s4_iTest7;

	char* pcTest1 = "01234";
	printf("-----------------\n");
}
*/


/*
root@debian:/home/bsn_cpp/liunx_study# size t1
   text    data     bss     dec     hex filename
   1416     316      32    1764     6e4 t1
root@debian:/home/bsn_cpp/liunx_study# ./t1
hello world
-----------------
g_pcTest1[0x080485e0]=01234
g_pcTest2[0x080485e0]=01234
g_pcTest3[0x080485e6]=0123
g_pcTest4[0x080485eb]=1234
g_pcTest5[0x080485f0]=123
  pcTest1[0x080485e0]=01234
-----------------


int const			gc_iTest1 = 1;
int					giTest2 = 2;
static int const	gsc_iTest3 = 3;
static int			gs_iTest4 = 4;

int					giTest6;
static int			gs_iTest7;

// ȫ�ֳ��� ��̬���� ��text��
int const			gc2_iTest1 = 1;
static int const	gsc2_iTest3 = 3;
// ȫ�ֳ�ʼ������ ��data��
int					g3iTest2 = 2;
static int			gs3_iTest4 = 4;
// ȫ��δʼ������ ��bss��
int					g4iTest6;
static int			gs4_iTest7;
// g_pcTest1��g_pcTest2��data "01234"��text 
char*  g_pcTest1 = "01234";
char*  g_pcTest2 = "01234";
char*  g_pcTest3 = "0123";
char*  g_pcTest4 = "1234";
char*  g_pcTest5 = "123";
char  g_cTest1 = 'a';;
int main(int argc, char* argv[])
{
	printf("hello world\n");

	int const			c_iTest = 1;
	int					iTest2 = 2;
	static int const	sc_iTest3 = 3;
	static int			s_iTest4 = 4;

	int			iTest6;
	static int	s_iTest7;

	// ������ ��̬���� ��text��
	static int const	sc2_iTest3 = 3;
	// ������ ��̬��ʼ������ ��data��
	static int			s3_iTest4 = 4;
	// ������ ��̬δʼ������ ��bss��
	static int	s4_iTest7;

	char* pcTest1 = "01234";
	printf("-----------------\n");
	printf("g_pcTest1[0x%08x]=%s\n",(unsigned int)g_pcTest1, g_pcTest1);
	printf("g_pcTest2[0x%08x]=%s\n",(unsigned int)g_pcTest2, g_pcTest2);
	printf("g_pcTest3[0x%08x]=%s\n",(unsigned int)g_pcTest3, g_pcTest3);
	printf("g_pcTest4[0x%08x]=%s\n",(unsigned int)g_pcTest4, g_pcTest4);
	printf("g_pcTest5[0x%08x]=%s\n",(unsigned int)g_pcTest5, g_pcTest5);
	printf("pcTest1[0x%08x]=%s\n",(unsigned int)pcTest1, pcTest1);
	printf("-----------------\n");
}
*/



/*
-----------------
g_pcTest1[0x080487d0]=01234
g_pcTest2[0x080487d0]=01234
g_pcTest3[0x080487d6]=0123
g_pcTest4[0x080487db]=1234
g_pcTest5[0x080487e0]=123
g_cTest2[0x08049ac0]=91234
pcTest1[0x080487d0]=01234
cTest1[0xbf9beb5a]=91234
-----------------
[0x08048464]main
[0x080487c8]gc2_iTest1
[0x080487cc]gsc2_iTest3
[0x08049aa4]g3iTest2
[0x08049aa8]gs3_iTest4
[0x08049aec]g4iTest6
[0x08049adc]gs4_iTest7
[0x0804a008]pMalloc1
[0x0804a018]pMalloc2
[0xbf9beb54]&pMalloc1
[0xbf9beb50]&pMalloc2
*/

#include <stdlib.h>

int const			gc_iTest1 = 1;
int					giTest2 = 2;
static int const	gsc_iTest3 = 3;
static int			gs_iTest4 = 4;

int					giTest6;
static int			gs_iTest7;

// ȫ�ֳ��� ��̬���� ��text��
int const			gc2_iTest1 = 1;
static int const	gsc2_iTest3 = 3;
// ȫ�ֳ�ʼ������ ��data��
int					g3iTest2 = 2;
static int			gs3_iTest4 = 4;
// ȫ��δʼ������ ��bss��
int					g4iTest6;
static int			gs4_iTest7;
// g_pcTest1��g_pcTest2��data "01234"��text 
char*  g_pcTest1 = "01234";
char*  g_pcTest2 = "01234";
char*  g_pcTest3 = "0123";
char*  g_pcTest4 = "1234";
char*  g_pcTest5 = "123";
// ��data 
char g_cTest2[] = "01234";
char  g_cTest1 = 'a';;
int main(int argc, char* argv[])
{
	printf("hello world\n");

	int const			c_iTest = 1;
	int					iTest2 = 2;
	static int const	sc_iTest3 = 3;
	static int			s_iTest4 = 4;

	int			iTest6;
	static int	s_iTest7;

	// ������ ��̬���� ��text��
	static int const	sc2_iTest3 = 3;
	// ������ ��̬��ʼ������ ��data��
	static int			s3_iTest4 = 4;
	// ������ ��̬δʼ������ ��bss��
	static int	s4_iTest7;

	char* pcTest1 = "01234";
	// �����޸���text�ε����� ��������ʱsegfault error 
	//pcTest1[0] = '1';
	// ��ջ�Ϸ����˿ռ� �����޸�
	char cTest1[] = "01234";
	cTest1[0] = '9';

	g_cTest2[0] = '9';

	int* pMalloc1 = (int*) malloc(4);
	int* pMalloc2 = (int*) malloc(4);
	free(pMalloc1);
	free(pMalloc2);

	printf("-----------------\n");
	printf("g_pcTest1[0x%08x]=%s\n",(unsigned int)g_pcTest1, g_pcTest1);
	printf("g_pcTest2[0x%08x]=%s\n",(unsigned int)g_pcTest2, g_pcTest2);
	printf("g_pcTest3[0x%08x]=%s\n",(unsigned int)g_pcTest3, g_pcTest3);
	printf("g_pcTest4[0x%08x]=%s\n",(unsigned int)g_pcTest4, g_pcTest4);
	printf("g_pcTest5[0x%08x]=%s\n",(unsigned int)g_pcTest5, g_pcTest5);
	printf("g_cTest2[0x%08x]=%s\n",(unsigned int)g_cTest2, g_cTest2);
	printf("pcTest1[0x%08x]=%s\n",(unsigned int)pcTest1, pcTest1);
	printf("cTest1[0x%08x]=%s\n",(unsigned int)cTest1, cTest1);
	printf("-----------------\n");
	printf("[0x%08x]main\n",(unsigned int)&main);
	printf("[0x%08x]gc2_iTest1\n",(unsigned int)&gc2_iTest1);
	printf("[0x%08x]gsc2_iTest3\n",(unsigned int)&gsc2_iTest3);
	printf("[0x%08x]g3iTest2\n",(unsigned int)&g3iTest2);
	printf("[0x%08x]gs3_iTest4\n",(unsigned int)&gs3_iTest4);
	printf("[0x%08x]g4iTest6\n",(unsigned int)&g4iTest6);
	printf("[0x%08x]gs4_iTest7\n",(unsigned int)&gs4_iTest7);
	printf("[0x%08x]pMalloc1\n",(unsigned int)pMalloc1);
	printf("[0x%08x]pMalloc2\n",(unsigned int)pMalloc2);
	printf("[0x%08x]&pMalloc1\n",(unsigned int)&pMalloc1);
	printf("[0x%08x]&pMalloc2\n",(unsigned int)&pMalloc2);
	
	printf("-----------------\n");
}




/*
�ε�������4�ֽڵı���
�����ַ��������text�Σ��������޸���ֵ�������������������segfault error 
ָ����ͬ�ַ���������ָ�룬��ָ��ֵ����ͬ��
����char cTest1[] = "01234";���ַ����ǿ����޸ĵ�
���ݷ��ôӵ͵�ַ��ʼ text data bss �� ����ջ����͵�ַ���ӵģ�ջ�еı��������������ڸߵ�ַ��
��ջ�ĵ�ַ���Կ���������ֻ�д�Լ3G���ڴ�ռ�

*/