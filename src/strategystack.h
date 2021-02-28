#ifndef STRATEGY_STACK_H
#define STRATEGY_STACK_H

#include <vector>

#include "strategy.h"
#include "settings.h"
#include "process.h"

/*
	Save all available processes ids on the stack.
	Pop id from the stack on process creation.

	On finishCallback id of finished process is now available
	so push back it to the stack.

	O(n) memory
	No comparations
	stable
*/

class StrategyStack : public Strategy
{
public:
	StrategyStack(std::vector<Process>& processes);

	bool add(std::chrono::milliseconds timeAlive) override;

	void drawInLine() const override;

private:
	void finishCallback(int id);

	std::vector<Process> &mProcesses;

	class StaticStack
	{
	public:
		StaticStack(size_t capacity);

		void push(int val);
		int pop();

		size_t size() const;
		bool full() const;

	private:
		std::vector<int> mNumbers;
		size_t mSize = 0;
	} mIds;

	int mLastAvaible = 0;

	size_t mComparations = 0;
};

#endif