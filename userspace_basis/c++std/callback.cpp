
#include <iostream>
#include <functional>
#include <vector>

class Bar
{
public:
	uint32_t start;
	uint32_t end;
private:
};

typedef std::function<void(Bar *b)> cb_t;

struct cb_arg_t {
	std::function<void(Bar *b)> cb;
	Bar *arg;
};

class CallBack
{
public:
	CallBack();
	~CallBack();

	void register_cb(const cb_t &cb, Bar *b);
	void callback(void);
private:
	std::vector<struct cb_arg_t> cbs;
};

CallBack::CallBack()
{
}

CallBack::~CallBack()
{
}

void CallBack::register_cb(const cb_t &cb, Bar *b)
{
	struct cb_arg_t c;

	c.cb = cb;
	c.arg = b;
	cbs.push_back(c);
	std::cout << "register " << &cb << " with args: " << b << std::endl;
}

void CallBack::callback()
{
	for(const auto& cb: cbs)
		cb.cb(cb.arg);

}

extern "C"
{
	static void cb_foo(Bar *arg)
	{
		std::cout << "arg: " << arg->start << " " << arg->end << std::endl;
	}

	static void cb_f2(Bar *arg)
	{
		std::cout << "arg: " << arg << ": " << arg->start << " " << arg->end << std::endl;
	}
}

int main(int argc, char *argv[])
{
	Bar b1;
	Bar b2;

	CallBack c;

	if (argc < 3)
		return -1;

	b1.start = atoi(argv[1]);
	b1.end = b1.start + atoi(argv[2]);
	b2.start = b1.end;
	b2.end = b2.start + atoi(argv[2]);

	c.register_cb(&cb_foo, &b1);
	c.callback();
	c.register_cb(&cb_f2, &b2);
	c.callback();

	return 0;
}
