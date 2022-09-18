
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <functional>		//for std::function
#include <condition_variable>

typedef std::function<void(void *arg)> cb_t;

class Timer_t
{
public:
	int id;						//Return to user when timer create, receive specific id for deleting the timer
	std::chrono::steady_clock::time_point start;	//The start point of timer.
	std::chrono::nanoseconds to;			//Record the actual timeout. It is useful to output the original timer in timerLoop
	void *arg;					//User arguments. Set during SetTimer; Return to user when such timer timeout.
	void print(std::string prefix, bool isPrintDelta);
};

class Timer
{
public:
	Timer();
	~Timer();

	/**
	 * timeout: microsecond
	 * return timerID
	 * create specific timer for timeout and *arg with current accuracy.
	 * Unit: specified by type or microsecond for int
	 * TODO: suppport timerID.
	 */
	int SetTimer(int timeout, void *arg);
	int SetTimer(std::chrono::nanoseconds timeout, void *arg);
	void DelTimer(int timerId);
	//Set the accuracy, timerLoop will return all the timer with the same Timer_t.until and accuracy.
	//Unit: microsecond
	int Accuracy(int newAccuracy);
	//The callback called by timerLoop. User should inherit the Timer class and implement own OnTimer method
	virtual void OnTimer(void *arg);
	//TODO: it should not a public function!
	void timerLoop(void);
	std::atomic_int newTimer;

private:
	std::chrono::nanoseconds accuracy;
	std::vector<Timer_t> tos;
	std::condition_variable cv;
	std::mutex cv_m;
	//Variable for sync between SetTimer and timeLoop.
	int lastID;
	std::thread timer;
	std::atomic_int stop_requested;
};

