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
			Process p{ i, timeAlive, std::function<void(int)>{ [](int) {} } };

			mProcesses[i] = p;
			
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

void StrategySimple::finishCallback(int id)
{

}