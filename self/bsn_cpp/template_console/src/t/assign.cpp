#include <bsn/template_console/include/t/t.h>

 



T_void
assign_()
{
	srand(time(0));
	typedef map<int, string> T_Map;
	typedef tuple<string, int> T_Tuple;

	list<int> l = list_of(1)(2)(3).repeat(2,3)(2);
	forward_list<int> fl = (list_of(1)(2)(3).repeat(2, 3), 4, 5);
	vector<int> v = list_of(1)(2).repeat_fun(2, rand)(3);
	set<int> s = list_of(11).range(v.begin(),v.end())(12)(13);
	deque<int> d = list_of(1)(2)(3);
	T_Map m = map_list_of(1, "a")(2, "b")(3, "abc");
	vector<T_Tuple> t = tuple_list_of("a", 1)("b", 2)("abc", 3);
	stack<int> stk = (list_of(1)(2)).to_adapter();
	queue<int> q = (list_of(1)(2)(3)).repeat(2,3).to_adapter();

	auto funClear = [&](){
		l.clear();
		fl.clear();
		v.clear();
		s.clear();
		d.clear();
		m.clear();
		t.clear();
	};
	auto funPrint = [&](string strWhat){
		cout << endl << strWhat << endl;
		if (!stk.empty())
		{
			cout << "stack stk=";
			while ( !stk.empty() )
			{
				cout << stk.top() << " ";
				stk.pop();
			}
			cout << endl;
		}
		if (!q.empty())
		{
			cout << "queue q=";
			while (!q.empty())
			{
				cout << q.front() << " ";
				q.pop();
			}
			cout << endl;
		}
		if (!l.empty())
		{
			cout << "list l=";
			for_each(l.begin(), l.end(), [](int i){cout << i << " "; });
			cout << endl;
		}
		if (!fl.empty())
		{
			cout << "forward_list fl=";
			for_each(fl.begin(), fl.end(), [](int i){cout << i << " "; });
			cout << endl;
		}
		if (!v.empty())
		{
			cout << "vector v=";
			for_each(v.begin(), v.end(), [](int i){cout << i << " "; });
			cout << endl;
		}
		if (!s.empty())
		{
			cout << "set s=";
			for_each(s.begin(), s.end(), [](int i){cout << i << " "; });
			cout << endl;
		}
		if (!d.empty())
		{
			cout << "deque d=";
			for_each(d.begin(), d.end(), [](int i){cout << i << " "; });
			cout << endl;
		}
		if (!m.empty())
		{
			cout << "map m=";
			for_each(m.begin(), m.end(), [](T_Map::value_type& i){cout << i.first << "-" << i.second << " "; });
			cout << endl;
		}
		if (!t.empty())
		{
			cout << "vector<T_Tuple> t=";
			for_each(t.begin(), t.end(), [](T_Tuple& i){cout << i.get<0>() << "-" << i.get<1>() << " "; });
			cout << endl;
		}
	};

	{
		funPrint("list_of");
	}

	{
		funClear();
		push(q)(3)(2).repeat(2, 1);
		push(stk)(3)(2).repeat(2, 1);
		funPrint("push");
	}

	{
		funClear();
		insert(s)(1)(2)(3);
		insert(m)(1, "a")(2, "b")(3, "abc");
		funPrint("insert");
	}

	{
		funClear();
		push_front(l)(1)(2)(3);
		push_front(fl)(1)(2)(3);
		push_front(d)(1)(2)(3);
		funPrint("push_front");
	}

	{
		funClear();
		push_back(l)(1)(2)(3);
		push_back(v)(1)(2)(3);
		push_back(d)(1)(2)(3);
		push_back(t)("a", 1)("b", 2)("abc", 3);
		funPrint("push_back");
	}

	{
		funClear();
		stk += 1, 2, 3, 4, 5, 6;
		l += 1, 2, 3;
		v += 1, 2, 3, 4;
		s += 1, 2, 3, 4, 5;
		d += 1, 2, 3, 4, 5, 6;
		m += make_pair(1, "a"), make_pair(2, "b"), make_pair(3, "abc");
		funPrint("+=");
	}

}
