#include "strategysimple.h"

#include <iostream>

StrategySimple::StrategySimple(std::vector<Process>& processes)
	: mProcesses{ processes }
{ }

bool StrategySimple::add(std::chrono::milliseconds timeAlive)
{
	for (int i = 0; i < mProcesses.size(); ++i)
	{
		++mComparations;
		if (!mProcesses[i].isAlive())
		{
			std::function<void(int)> callUpdate = [this](int id) { };
			mProcesses[i] = { i, timeAlive, callUpdate };
			
			return true;
		}
	}

	return false;
}

void StrategySimple::drawInLine() const
{
	std::cout << "Simple: \t[";
	for (const auto &p : mProcesses)
	{
		if (p.isAlive())
		{
			std::cout << char(178);
		}
		else
		{
			std::cout << char(176);
		}
	}
	std::cout << ']' 
		<< " Comparations: " 
		<< mComparations 
		<< '\n';
}
