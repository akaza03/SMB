#include <DxLib.h>
#include "ImageMng.h"
#include "MapCtl.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameTask.h"

//	�����ɂ�new
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
		memcpy(keyDataOld, keyData, sizeof(keyDataOld));			//	�R�s�[
		GetHitKeyStateAll(keyData);									//	�擾
		//	��݂̍X�V
		activeScene = activeScene->Update(std::move(activeScene));
	}
}

int GameTask::SysInit()
{
	//	���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("1701301_�ԍ藢��");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}