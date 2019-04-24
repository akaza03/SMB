#include <DxLib.h>
#include "ImageMng.h"
#include "MapCtl.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameTask.h"

//	ここにてnew
std::unique_ptr<GameTask, GameTask::GameTaskDeleter> GameTask::s_Instance(new GameTask);

GameTask::GameTask()
{
	SysInit();
}

GameTask::~GameTask()
{
	DxLib_End();
}

void GameTask::Run()
{
	activeScene = std::make_unique<TitleScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		memcpy(keyDataOld, keyData, sizeof(keyDataOld));			//	コピー
		GetHitKeyStateAll(keyData);									//	取得
		//	ｼｰﾝの更新
		activeScene = activeScene->Update(std::move(activeScene));
	}
}

int GameTask::SysInit()
{
	//	ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("1701301_赤崎里駆");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}