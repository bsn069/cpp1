#include <bsn/template_console/include/t/t.h>


class C_Buffer
{
public:
	mutex	m_Mutex;

	condition_variable_any m_Put;
	condition_variable_any m_Get;

	stack<int> m_Stk;
	int m_iCapacity;

	T_void Put(int x)
	{
		{
			auto lock = make_unique_lock(m_Mutex);
			while (m_Stk.size() == m_iCapacity)
			{
				cout << "full waiting ..." << endl;
				m_Put.wait(lock);
			}
			cout << "put " << x << endl;
			m_Stk.push(x);
		}
		m_Get.notify_one();
	}

	T_void Get(int& x)
	{
		{
			auto lock = make_unique_lock(m_Mutex);
			while ( m_Stk.empty() )
			{
				cout << "empty waiting ..." << endl;
				m_Get.wait(lock);
			}
			x = m_Stk.top();
			m_Stk.pop();
			cout << "get " << x << endl;
		}
		m_Put.notify_one();
	}


public:
	C_Buffer();
	~C_Buffer();

private:

};

C_Buffer::C_Buffer()
{
	m_iCapacity = 3;
}

C_Buffer::~C_Buffer()
{
}

static C_Buffer vBuffer;


T_void 
Put(int x)
{
	for (auto i = 0; i < x; ++i)
	{
		vBuffer.Put(i);
	}
}

T_void
Get(int x)
{
	int j;
	for (auto i = 0; i < x; ++i)
	{
		vBuffer.Get(j);
		sleep_for( milliseconds(1));
	}
}

T_void
condition_variable_any_()
{
	 
	thread_group th;
	th.create_thread(bind(Get, 10));
	th.create_thread(bind(Put, 10));
	th.join_all();
 
}
