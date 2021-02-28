#include "strategymemorymin.h"

#include <iostream>

StrategyMemoryMin::StrategyMemoryMin(std::vector<Process>& processes)
	: mProcesses{ processes }
{ }

bool StrategyMemoryMin::add(std::chrono::milliseconds timeAlive)
{
	auto callUpdate = [this](int id) { finishCallback(id); };

	for (int i = (mMinAvaibleIndex < 0) ? 0 : mMinAvaibleIndex; i < mProcesses.size(); ++i)
	{
		++mComparations;
		if (!mProcesses[i].isAlive())
		{
			std::function<void(int)> f{ callUpdate };
			mProcesses[i] = { i, timeAlive, f };
			
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

void StrategyMemoryMin::finishCallback(int id)
{
	if (mMinAvaibleIndex < 0 || mMinAvaibleIndex > id)
	{
		mMinAvaibleIndex = id;
	}
}
