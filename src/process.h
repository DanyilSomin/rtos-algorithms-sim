#ifndef PROCESS_H
#define PROCESS_H

#include <functional>
#include <ctime>
#include <chrono>
#include <iostream>

class Process
{
public:
	Process(int id, std::chrono::milliseconds timeAlive,
		std::function<void(int)>& onExecuteFinish);

	Process();

	void update();

	bool isAlive() const;

private:
	std::function<void(int)> mOnExecuteFinish = 0;

	std::chrono::system_clock::time_point mCreationTime;
	std::chrono::milliseconds mTimeAlive{ 0 };

	int mId = 0;

	bool mIsAlive = false;
};

#endif