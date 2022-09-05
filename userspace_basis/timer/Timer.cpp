
#include <iostream>
#include <iomanip>      // std::setprecision
#include "timer.h"

void Timer_t::print(std::string s, bool isPrintDelta = false)
{
	auto start_us = std::chrono::time_point_cast<std::chrono::microseconds>(start);
	auto now_us = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::steady_clock::now());
	//std::cout << s << " " << to.count() / 1000 / 1000 << "ms real delta " << std::fixed << std::setprecision(1) << double((now_us - start_us).count())/1000  << " start from " << start_us.time_since_epoch().count() << ", arg: " << arg << std::endl;
	std::stringstream out;
	out << "(" << this << ") " << s << to.count() / 1000 / 1000 << "ms";
	if(isPrintDelta)
		out << ", delta " << std::fixed << std::setprecision(2) << double((now_us - start_us - to).count()) / 1000 / 1000 << "ms";

	std::cout << out.str() << std::endl;
}

Timer::Timer()
{
	newTimer = 0;
	stop_requested = 0;
	accuracy = std::chrono::nanoseconds(1000 * 1000);
	timer = std::thread(&Timer::timerLoop, this);
}

Timer::~Timer()
{
	stop_requested = 1;
	SetTimer(accuracy, this);
	timer.join();
}

/**
 * < 0: error
 * = 0: ignored.
 * > 0: successful
 */
int Timer::SetTimer(int timeout, void *arg)
{
	return SetTimer((std::chrono::microseconds)timeout, arg);
}

int Timer::SetTimer(std::chrono::nanoseconds timeout, void *arg)
{
	Timer_t t;
	bool verbose = false;

	//Arguments check
	if (timeout > (std::chrono::nanoseconds)1000000000 || timeout < accuracy) {
		std::cout <<  "Do not support timer more than 1 second or below " << accuracy.count() << std::endl;
		return -EINVAL;
	}
	t.start = std::chrono::steady_clock::now();
	t.to = timeout / accuracy * accuracy;

	if (tos.size() > 0) {
		auto last = tos.back();
		auto until_last = std::chrono::time_point_cast<std::chrono::milliseconds>(last.start + last.to);
		auto until_new = std::chrono::time_point_cast<std::chrono::milliseconds>(t.start + t.to);
		if (until_new < until_last) {
			std::cerr << "Could not set the timer (" << t.to.count() / 1000 / 1000 << " ms) early than than existing timer(" << until_new.time_since_epoch().count() << " < " << until_last.time_since_epoch().count() << ") . ignore" << std::endl;
			return 0;
		}
	}
	t.arg = arg;

	//push timer to queue
	tos.push_back(t);
	if (verbose)
		t.print("SetTimer: Timeout after ");

	//send message to timer loop
	std::lock_guard<std::mutex> lk(cv_m);
	newTimer = 1;
	cv.notify_all();

	return 1;
}

void Timer::DelTimer(int timerId) {}

int Timer::Accuracy(int newAccuracy)
{
	accuracy = (std::chrono::nanoseconds)newAccuracy;

	return 0;
}

void Timer::OnTimer(void *arg)
{
	std::cout << "OnTimer: arg: " << arg << ": " << *(int*)arg << std::endl;
	//Cast arg to Object
	//Deal with Object
}

void Timer::timerLoop(void)
{
	std::unique_lock<std::mutex> lk(cv_m);
	std::chrono::steady_clock::time_point next_timer;

	std::cout<<"timer loop started: " << this <<std::endl;
	while(stop_requested == 0) {
		//loop all the timer
		//check if timer timeout
		//True:  Call on timer; output info; remove the timer
		auto t = tos.begin();
		while (t != tos.end()) {
			//verbose: t->print("timerLoop: Timer: ");
			if (t->start + t->to < std::chrono::steady_clock::now()) {
				//TODO: save delta to analysis the response time.
				this->OnTimer(t->arg);
				t->print("timerLoop: remove Timer: ");
				t = tos.erase(t);
			} else {
				t++;
			}
		}
		//Re-enter wait with the next timer timeout
		if (tos.size() == 0)
			next_timer = std::chrono::steady_clock::now() + accuracy * 1000;
		else
			next_timer = tos.begin()->start + tos.begin()->to;

		if (cv.wait_until(lk, next_timer, [this]{return newTimer == 1;})) {
			if (stop_requested == 0) {
				if (tos.size() > 0) {
					tos.back().print("Wake up because of getting new Timer: ");
					newTimer = 0;
				} else {
					std::cerr << "Concurrency issue!" << std::endl;
				}
			}
		} else if (tos.size() > 0) {
			//Raise timer
			OnTimer(tos.begin()->arg);
			tos.begin()->print("Timer timeout: remove Timer: ", true);
			tos.erase(tos.begin());
		} else {
			std::cout << "No timer, continue to waiting for" << std::endl;
		}
	}
}

