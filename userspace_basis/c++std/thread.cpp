
#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <atomic>

int i;
std::condition_variable cv;
std::mutex cv_m;
std::chrono::time_point<std::chrono::high_resolution_clock> start;
std::chrono::time_point<std::chrono::high_resolution_clock> end;
std::chrono::microseconds timer(1000000);
std::atomic_int nt;
const int max = 5;

void sleep()
{
	const int max = 5;
	std::chrono::microseconds timeout;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::duration<long, std::nano> elapsed;

	for (int i = 0; i < max; i++) {
		timeout =  (std::chrono::microseconds)(rand() % 29000 + 1000);
		std::cout << "timeout: " << timeout.count() << " ";
		start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(timeout);
		auto end = std::chrono::high_resolution_clock::now();
		elapsed = end - start;
		std::cout << "Real time elapsed: " << elapsed.count() / 1000 << "us" << " ";
		std::cout << "Delta: " << elapsed.count() / 1000 - timeout.count() << "us" << std::endl;
	}
}

void producer()
{
	timer = (std::chrono::microseconds)(30000);
	std::cout << "producer: timer: " << timer.count() << std::endl;
	start = std::chrono::high_resolution_clock::now();
	std::lock_guard<std::mutex> lk(cv_m);
	nt = 1;
	cv.notify_all();
}

void consumer()
{
	std::unique_lock<std::mutex> lk(cv_m);
	while(true) {
		if(cv.wait_for(lk, timer, []{return nt == 1;})) {
			std::cout << "consumer: get new timer " << timer.count() << std::endl;
			nt = 0;
		} else {
			end = std::chrono::high_resolution_clock::now();
			auto elapsed = end - start;
			std::cout << "Real time elapsed: " << elapsed.count() / 1000 << "us" << " ";
			std::cout << "Delta: " << elapsed.count() / 1000 - timer.count() << "us" << std::endl;
			float delta = ((elapsed.count() / 1000 - timer.count())) / timer.count();
			if (delta > 0.01)
				std::cerr << "##### over 1% delta " << delta << std::endl;
			else
				std::cerr << ".";
			break;
		}
	}
}

class MyThread
{
public:
	~MyThread();
	void startThread();
	void threadTest();
private:
	std::thread t;
};

MyThread::~MyThread()
{
	t.join();
}

void MyThread::startThread()
{
	t = std::thread(&MyThread::threadTest, this);
}

void MyThread::threadTest()
{
	for(int i = 0; i < 5; i++) {
		int sec = rand() % 10;
		std::cout << this << ": " << i << ", second: " << sec << std::endl;
		std::this_thread::sleep_for((std::chrono::microseconds)sec * 100000);
	}
}

int main()
{
	//Test sleep
	//std::thread tSleep(sleep);
	//tSleep.join();

	//Test wait_for
	//std::thread tProducer(producer), tConsumer(consumer);
	//tProducer.join();
	//tConsumer.join();

	//Test create multiple threads from the same class
	MyThread m;
	MyThread n;
	m.startThread();
	n.startThread();
	return 0;
}
