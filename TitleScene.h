#pragma once
#include "BaseScene.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	scene_ptr Update(scene_ptr scn);

private:
	int MushroomPosY;				//	·Éº¶°¿Ù‚ÌPosY
	int blinkCnt;					//	“_–Å‚ÌŠÔŠu
};

