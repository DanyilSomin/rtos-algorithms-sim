#ifndef STRATEGY_SIMPLE_H
#define STRATEGY_SIMPLE_H

#include <vector>

#include "strategy.h"
#include "settings.h"
#include "process.h"

/*
	Search avaible process from the start of array.

	On update do nothing.
	
	No extra memory
	O(n) comparations
	unstable
*/

class StrategySimple : public Strategy
{
public:
	StrategySimple(std::vector<Process> &processes);

	bool add(std::chrono::milliseconds timeAlive);

	void drawInLine() const;

private:
	void finishCallback(int id) override;

	std::vector<Process>& mProcesses;

	size_t mComparations = 0;
};

#endif