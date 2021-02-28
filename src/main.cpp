#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <memory>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "settings.h"
#include "process.h"
#include "strategysimple.h"
#include "strategymemorymin.h"
#include "strategyloop.h"
#include "strategystack.h"

using StrategyVector = std::vector<std::unique_ptr<Strategy>>;
using Clock = std::chrono::system_clock;

void draw(const StrategyVector& strategies);
void sleepMs(int sleepMs);

#ifdef WIN32
void gotoStart();
#endif

int main()
{
	// randomise using current system time
	srand(time(nullptr));

	// initialize vectors with processes for each algorythm
	std::vector<Process> processesSimple{ processAmount };
	std::vector<Process> processesFirst{ processAmount };
	std::vector<Process> processesLoop{ processAmount };
	std::vector<Process> processesStack{ processAmount };

	// initialize vectors with strategies for each algorythm
	StrategyVector strategies;
	strategies.emplace_back(new StrategySimple{ processesSimple });
	strategies.emplace_back(new StrategyMemoryMin{ processesFirst });
	strategies.emplace_back(new StrategyLoop{ processesLoop });
	strategies.emplace_back(new StrategyStack{ processesStack });

	// force addition of a first process
	auto timeToAdd = Clock::now();

	// game loop
	while (true)
	{
		// update all procesess so they can track time
		// and callback on execution finish
		for (auto& p : processesSimple) { p.update(); }
		for (auto& p : processesFirst) { p.update(); }
		for (auto& p : processesLoop) { p.update(); }
		for (auto& p : processesStack) { p.update(); }

		// add new process if it is time to do it
		if (Clock::now() > timeToAdd)
		{
			std::chrono::milliseconds timeAlive{ processTimeAliveMin +
				  rand() % (processTimeAliveMax - processTimeAliveMin) };
			for (auto& s : strategies)
			{
				s->add(timeAlive);
			}

			// calculate time when next process should be added
			timeToAdd = Clock::now() +
				std::chrono::milliseconds{ processCreationTimeMin +
				rand() % (processCreationTimeMax - processCreationTimeMin) };
		}

		// update information to console
		draw(strategies);

		sleepMs(updatePeriod);
	}

	return 1;
}

void draw(const StrategyVector& strategies)
{
#ifdef WIN32
	gotoStart();
#else
	for (int i = 0; i < strategies.size(); ++i)
	{
		std::cout << "\x1b[A"; // line up
	}
#endif

	for (const auto& s : strategies)
	{
		s->drawInLine();
	}
}

void sleepMs(int sleepMs)
{
#ifdef WIN32
	Sleep(sleepMs);
#else
	usleep(sleepMs * 1000);
#endif
}

#ifdef WIN32
void gotoStart()
{
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	static COORD CursorPosition;
	CursorPosition.X = 0;
	CursorPosition.Y = 0;
	SetConsoleCursorPosition(console, CursorPosition);
}
#endif