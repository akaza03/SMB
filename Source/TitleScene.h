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
	int MushroomPosY;				//	�ɺ���ق�PosY
	int blinkCnt;					//	�_�ł̊Ԋu
};

