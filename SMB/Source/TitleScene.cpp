#include <DxLib.h>
#include "GameScene.h"
#include "GameTask.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
	StopSoundFile();
	blinkCnt = 0;
	MushroomPosY = 380;
}


TitleScene::~TitleScene()
{
}

scene_ptr TitleScene::Update(scene_ptr scn)
{
	//memcpy(keyDataOld, keyData, sizeof(keyDataOld));
	//GetHitKeyStateAll(keyData);

	if (lpGameTask.keyData[KEY_INPUT_SPACE])
	{
		return scene_ptr(std::make_unique<GameScene>());
	}

	ClsDrawScreen();

	DrawGraph(0, 0, IMAGE_ID("image/Title.png")[0], true);

	//	·Éº¶°¿Ù‚ÌˆÚ“®
	if (MushroomPosY != 380 && lpGameTask.keyData[KEY_INPUT_UP] && !lpGameTask.keyDataOld[KEY_INPUT_UP])
	{
		MushroomPosY -= 45;
	}
	if (MushroomPosY != 425 && lpGameTask.keyData[KEY_INPUT_DOWN] && !lpGameTask.keyDataOld[KEY_INPUT_DOWN])
	{
		MushroomPosY += 45;
	}

	blinkCnt++;
	if (((blinkCnt / 20) % 2) == 0)				//	“_–Å‚ÌŠÔŠu
	{
		DrawGraph(170, MushroomPosY, IMAGE_ID("image/TitleMushroom.png")[0], true);
	}

	ScreenFlip();
	return scn;
}
