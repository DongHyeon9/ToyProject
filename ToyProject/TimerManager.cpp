#include "TimerManager.h"

bool TimerManager::Init()
{
	prev = std::chrono::steady_clock::now();

	LOG("타이머 매니저 초기화 성공");
	return true;
}

double TimerManager::Update()
{
	prev = cur;
	cur = std::chrono::steady_clock::now();
	return std::chrono::duration<double>(cur - prev).count();
}

void TimerManager::Terminate()
{

}