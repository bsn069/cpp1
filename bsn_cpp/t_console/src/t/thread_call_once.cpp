#include <bsn/template_console/include/t/t.h>

static int g_count;

static
T_void
init_count(int x)
{
	cout << "init_count" << endl;
	g_count = x;
}


static
T_void
call_func( )
{
	cout << "call_func" << endl;
	static once_flag s_once;
	call_once(s_once, init_count, 1);
}



T_void
thread_call_once()
{
	{
		scoped_thread<> st(call_func);
		scoped_thread<> st1(call_func);
	}
	sleep_for(seconds(1));
	thread_group th;
	th.create_thread(call_func);
	th.create_thread(call_func);
	th.join_all();
	sleep_for(seconds(1));
	{
		scoped_thread<> st(call_func);
		scoped_thread<> st1(call_func);
	}
	sleep_for( seconds(1));
}
