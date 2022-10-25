
#include "Timer.h"
#include <iostream>

class MyTimer_t {
public:
	int foo;
	std::string bar;
};

class MyTimer: public Timer
{
public:
	void OnTimer(void *arg);
};

void MyTimer::OnTimer(void *arg)
{
	class MyTimer_t *t = (class MyTimer_t*)arg;
	std::cout << "MyTimer: " << t->foo << " " << t->bar << std::endl;
}

int main(int argc, char *argv[])
{
	int arg1 = argc;
	Timer t;
	int start;
	int end;
	int step;

//	start = atoi(argv[1]);
//	end = atoi(argv[2]);
//	step = atoi(argv[3]);
	std::cout << "Test accuracy for 1-30ms" << std::endl;
	start = 1000;
	end = 30000;
	step = 5000;
	for(int i = start; i < end; i += step) {
		std::cout << "User set timer " << i / 1000 << " ms" << std::endl;
		t.SetTimer(i, &arg1);
		std::this_thread::sleep_for((std::chrono::microseconds)(i + step));
	}
	std::cout << std::endl;

	std::cout << "Test overlaped timer" << std::endl;
	std::cout << "User set timer " << 5000 / 1000 << " ms" << std::endl;
	t.SetTimer(5000, &arg1);
	std::cout << "User set timer " << 20000 / 1000 << " ms" << std::endl;
	t.SetTimer(20000, &arg1);
	std::this_thread::sleep_for((std::chrono::microseconds)(15000));
	std::cout << "User set timer " << 4000 / 1000 << " ms" << std::endl;
	t.SetTimer(4000, &arg1); //This timer is smaller then previous one which will timeout after 5000 us. So, this timer will be rejected.
	std::cout << "User set timer " << 5000 / 1000 << " ms" << std::endl;
	t.SetTimer(5000, &arg1);
	std::this_thread::sleep_for((std::chrono::microseconds)(10000));
	std::cout << "User set timer " << 400000 / 1000 << " ms" << std::endl;
	t.SetTimer(400000, &arg1);
	std::cout << "User set timer " << 500000 / 1000 << " ms" << std::endl;
	t.SetTimer(500000, &arg1);
	std::this_thread::sleep_for((std::chrono::microseconds)(600000));
	std::cout << std::endl;

	std::cout << "Test inheritance" << std::endl;
	MyTimer m;
	MyTimer_t ma;
	MyTimer_t mb;
	MyTimer_t mc;
	ma.foo = 1;
	ma.bar = "abc";
	mb.foo = 2;
	mc.bar = "abc345";
	mc.foo = 3;
	mb.bar = "abc123";
	m.SetTimer(5000, (void*)&ma);
	m.SetTimer(6000, (void*)&mb);
	m.SetTimer(10000, (void*)&mc);
	std::this_thread::sleep_for((std::chrono::microseconds)(20000));
	std::cout << std::endl;

	std::cout << "Test two instances. Should be individual timerLoop" << std::endl;
	MyTimer n;
	MyTimer_t na;
	MyTimer_t nb;
	MyTimer_t nc;
	na.foo = 4;
	na.bar = "xyz";
	nb.foo = 5;
	nc.bar = "xyz345";
	nc.foo = 6;
	nb.bar = "xyz123";
	m.SetTimer(5000, (void*)&ma);
	n.SetTimer(5000, (void*)&na);
	m.SetTimer(6000, (void*)&mb);
	n.SetTimer(6000, (void*)&nb);
	m.SetTimer(10000, (void*)&mc);
	n.SetTimer(10000, (void*)&nc);
	std::this_thread::sleep_for((std::chrono::microseconds)(20000));

	return 0;
}
