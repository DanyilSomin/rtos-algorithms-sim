#include "process.h"

Process::Process(int id, std::chrono::milliseconds timeAlive,
	std::function<void(int)>& onExecuteFinish)
	: mOnExecuteFinish{ onExecuteFinish },
	mCreationTime{ std::chrono::system_clock::now() },
	mTimeAlive{ timeAlive },
	mIsAlive{ true },
	mId{ id }
{  }

Process::Process() {}

void Process::update()
{
	if (!mIsAlive) return;

	if (std::chrono::system_clock::now() > mCreationTime + mTimeAlive)
	{
		mIsAlive = false;
		mOnExecuteFinish(mId);
	}
}

bool Process::isAlive() const
{ 
	return mIsAlive; 
}