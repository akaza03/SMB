#pragma once
#include <memory>
#include "BaseScene.h"

#define lpGameTask GameTask::GetInstance()
//	20 * 20
constexpr int SCREEN_SIZE_X = 640;
constexpr int SCREEN_SIZE_Y = 640;

class GameTask
{
public:

	static GameTask &GetInstance()
	{
		return *s_Instance;
	}
	void Run();

	char keyData[256];
	char keyDataOld[256];

private:
	//	ŠÖ”µÌŞ¼Şª¸Ä
	struct GameTaskDeleter
	{
		void operator()(GameTask* gameTask) const
		{
			delete gameTask;
		}
	};
	static std::unique_ptr<GameTask, GameTaskDeleter> s_Instance;

	GameTask();
	~GameTask();
	int SysInit();

	std::unique_ptr<BaseScene> activeScene;
};