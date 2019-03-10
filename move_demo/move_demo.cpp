#include<iostream>

using namespace std;

struct MyClass
{
	int* p = nullptr;
	MyClass()
	{
		cout << "MyClass()" << endl;
	}
	explicit MyClass(int val)
	: p(new int(val))
	{
		cout << "MyClass(int)" << endl;
	}

	MyClass(const MyClass& mc)
	{
		cout << "MyClass(const MyClass&)" << endl;

		if (mc.p)
		{
			p = new int(*(mc.p));
		}
		else
		{
			p = nullptr;
		}
	}

	MyClass(MyClass&& mc)
	: p(mc.p)
	{
		cout << "MyClass(MyClass&&)" << endl;
		mc.p = nullptr;
	}

	MyClass& operator=(const MyClass& mc)
	{
		cout << "operator=(const MyClass&)" << endl;

		if(p != nullptr && mc.p != nullptr)
		{
			*p = *(mc.p);
		}
		else if (p == nullptr && mc.p != nullptr)
		{
			p = new int(*(mc.p));
		}
		else if (p != nullptr && mc.p == nullptr)
		{
			delete p;
			p = nullptr;
		}
		// else (p == nullptr && mc.p == nullptr)
		// {

		// }

		return *this;
	}
	MyClass& operator=(MyClass&& mc)
	{
		cout << "operator=(MyClass&&)" << endl;
		if (p != nullptr)
		{
			delete p;
		}
	
		p = mc.p;
		mc.p = nullptr;
		return *this;
	}

	~MyClass()
	{
		cout << "~MyClass()" << endl;
		if (p != nullptr)
		{
			delete p;
		}
	}
};


MyClass MyFunc()
{
	MyClass mc(777);
	return mc;
}

void MyFunc(MyClass& mc)
{
	if(mc.p)
	{
		*(mc.p) = 777;
	}
	else
	{
		mc.p = new int(777);
	}
}

MyClass operator+(const MyClass& mc1, const MyClass& mc2)
{
	cout << "MyClass operator+(const MyClass& mc1, const MyClass& mc2)" << endl;

	MyClass result((mc1.p ? *(mc1.p) : 0) + (mc2.p ? *(mc2.p) : 0));

	return result;
}

void PrintMyClass(const MyClass& mc)
{
	if (mc.p)
	{
		cout << *(mc.p) << endl;
	}
	else
	{
		cout << "NULL" << endl;
	}
}
int main()
{
	// MyClass ms = MyFunc();

	// MyClass ms;
	// MyFunc(ms);

	// PrintMyClass(ms);

	MyClass mc1, mc2;
	MyClass testVal;

	// testVal = mc1 + mc2;
	testVal = MyFunc();

	// MyClass leftVal(666);
	// // testVal = leftVal;
	// testVal = move(leftVal);

	// PrintMyClass(leftVal);
	// PrintMyClass(testVal);

	return 0;
}