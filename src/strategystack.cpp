#include "strategystack.h"

#include <iostream>
#include <algorithm>

StrategyStack::StrategyStack(std::vector<Process>& processes)
	: mProcesses{ processes }, mIds{ processes.size() }
{
	for (int i = 0; i < mProcesses.size(); ++i)
	{
		mIds.push(i);
	}
}

#include <cassert>

bool StrategyStack::add(std::chrono::milliseconds timeAlive)
{
	if (mIds.size() == 0) return false;

	const int id{ mIds.pop() };
	
	std::function<void(int)> callUpdate = [this](int id) { finishCallback(id); };
	mProcesses[id] = { id, timeAlive, callUpdate };

	return true;
}

void StrategyStack::drawInLine() const
{
	std::cout << "Stack: \t\t[";
	for (const auto& p : mProcesses)
	{
		if (p.isAlive())
		{
			std::cout << '|';
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

void StrategyStack::finishCallback(int id)
{
	if (!mIds.full())
	{
		mIds.push(id);
	}
}

StrategyStack::StaticStack::StaticStack(size_t capacity)
{
	mNumbers.resize(capacity);
}

void StrategyStack::StaticStack::push(int val)
{
	mNumbers[mSize] = val;
	++mSize;
}

int StrategyStack::StaticStack::pop()
{
	--mSize;
	return mNumbers[mSize];
}

size_t StrategyStack::StaticStack::size() const
{
	return mSize;
}

bool StrategyStack::StaticStack::full() const
{
	return mSize == mNumbers.size();
}
