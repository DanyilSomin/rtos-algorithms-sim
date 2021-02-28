#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include "process.h"

class Strategy
{
public:
	virtual bool add(std::chrono::milliseconds timeAlive) = 0;

	virtual void drawInLine() const = 0;

	virtual ~Strategy() = default;

private:
	virtual void finishCallback(int) = 0;
};

#endif