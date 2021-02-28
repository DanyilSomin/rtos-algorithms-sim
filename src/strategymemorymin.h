#ifndef STRATEGY_MEMORY_FIRST_H
#define STRATEGY_MEMORY_FIRST_H

#include <vector>

#include "strategy.h"
#include "settings.h"
#include "process.h"

/*
	Track the last avaible process with minimal index
	to be shure that all processes with smaller index are unavailable.
	Search available process from index of last avaible process
	to cut off first unavailable processes check.

	On update set index of last available process to new
	only if it is smaller then current index.

    O(1) memory
    O(n) comparations
    unstable
*/
class StrategyMemoryMin : public Strategy
{
public:
	StrategyMemoryMin(std::vector<Process>& processes);

	bool add(std::chrono::milliseconds timeAlive) override;

	void drawInLine() const override;

private:
	void finishCallback(int id) override;

	std::vector<Process>& mProcesses;

	int mMinAvaibleIndex = -1;

	size_t mComparations = 0;
};

#endif