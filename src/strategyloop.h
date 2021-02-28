#ifndef STRATEGY_LOOP_H
#define STRATEGY_LOOP_H

#include <vector>

#include "strategy.h"
#include "settings.h"
#include "process.h"

/*
	Complicated but practically faster version of 'memory first'.
	
	Seek free process from last available process index
	and loop 'i' variable to '0' in case of 'i > length'.
	
	On finishCallback change last available index only if it cut
	the distance to next available process.

	O(1) memory
	O(n) comparations
	unstable
*/
class StrategyLoop : public Strategy
{
public:
	StrategyLoop(std::vector<Process>& processes);

	bool add(std::chrono::milliseconds timeAlive) override;

	void drawInLine() const override;

private:
	void finishCallback(int id);

	std::vector<Process>& mProcesses;

	int mLastAvaible = 0;

	size_t mComparations = 0;
};

#endif
