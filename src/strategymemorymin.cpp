#include "strategymemorymin.h"

#include <iostream>

StrategyMemoryMin::StrategyMemoryMin(std::vector<Process>& processes)
	: mProcesses{ processes }
{ }

bool StrategyMemoryMin::add(std::chrono::milliseconds timeAlive)
{
	std::function<void(int)> callUpdate = [this](int id) { finishCallback(id); };

	for (int i = (mMinAvaibleIndex < 0) ? 0 : mMinAvaibleIndex; i < mProcesses.size(); ++i)
	{
		++mComparations;
		if (!mProcesses[i].isAlive())
		{
			mProcesses[i] = { i, timeAlive, callUpdate };
			
			mMinAvaibleIndex = i;
			
			return true;
		}
	}

	return false;
}

void StrategyMemoryMin::drawInLine() const
{
	std::cout << "Memory min: \t[";
	for (const auto& p : mProcesses)
	{
		if (p.isAlive())
		{
			std::cout << 'O';
		}
		else
		{
			std::cout << '-';
		}
	}
	std::cout << ']'
		<< " Comparations: "
		<< mComparations
		<< '\n';
}

void StrategyMemoryMin::finishCallback(int id)
{
	if (mMinAvaibleIndex < 0 || mMinAvaibleIndex > id)
	{
		mMinAvaibleIndex = id;
	}
}
