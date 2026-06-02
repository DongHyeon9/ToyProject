#pragma once
#include "EngineCore.h"

class TimerManager : public ISingleton<TimerManager>
{
public:
	bool Init();
	double Update();
	void Terminate();
	double GetDeltaTime() const { return std::chrono::duration<double>(cur - prev).count(); }

private:
	std::chrono::time_point<std::chrono::steady_clock> cur{};
	std::chrono::time_point<std::chrono::steady_clock> prev{};
};

