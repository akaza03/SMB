#include <DxLib.h>
#include "MapCtl.h"
#include "ImageMng.h"
#include "Camera.h"



Camera::Camera()
{
	pos = { 0, 0 };
}


Camera::~Camera()
{
}

VECTOR2 &Camera::GetPos(void)
{
	return pos;
}

bool Camera::SetPos(VECTOR2 pos)
{
	this->pos = pos;
	return true;
}

bool Camera::SetPos(float x, float y)
{
	pos = { x,y };
	return true;
}

bool Camera::SetTarget(std::weak_ptr<Obj> target)
{
	this->target = target;
	//	一画面の半分(左端)
	VECTOR2 tmpPos = (VIEW_AREA / 2) * CHIP_SIZE;
	antiMoveRect.left = tmpPos.x;			//	画面左上のx座標
	antiMoveRect.top = tmpPos.y;			//	画面左上のy座標

	//	全体から一画面の半分を引いた分(右端)
	VECTOR2 tmpPos2 = (GAME_AREA - (VIEW_AREA / 2)) * CHIP_SIZE;
	antiMoveRect.right = tmpPos2.x;			//	画面右下のx座標
	antiMoveRect.bottom = tmpPos2.y;		//	画面右下のy座標

	if (antiMoveRect.top > antiMoveRect.bottom)
	{
		antiMoveRect.top = (VIEW_AREA_CNT_Y / 2) * CHIP_SIZE;
		antiMoveRect.bottom = antiMoveRect.top;
	}
	if (antiMoveRect.left > antiMoveRect.right)
	{
		antiMoveRect.left = (VIEW_AREA_CNT_X / 2)* CHIP_SIZE;
		antiMoveRect.right = antiMoveRect.left;
	}

	pos.x = target.lock()->GetPos().x;
	//	ﾌﾟﾚｲﾔｰの初期位置によっては画面外が表示されるので補正
	if (pos.x < 320)
	{
		pos.x = 320;
	}

	pos.y = antiMoveRect.top;
	return true;
}

void Camera::Update(void)
{
	if (target.expired())
	{
		return;
	}
	VECTOR2 tmpPos = target.lock()->GetPos();
	if (tmpPos.x >= antiMoveRect.left && tmpPos.x < antiMoveRect.right)
	{
		pos.x = tmpPos.x;
	}
	if (tmpPos.y >= antiMoveRect.top && tmpPos.y < antiMoveRect.bottom)
	{
		pos.y = tmpPos.y;
	}
}
