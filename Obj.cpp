#include "DxLib.h"
#include "ImageMng.h"
#include "MapCtl.h"
#include "Obj.h"




Obj::Obj(const char(&_keyData)[256], const char(&_keyDataOld)[256],VECTOR2(chipOffset))
	:keyData(_keyData), keyDataOld(_keyDataOld)
{
	pos = { 0,0 };
	divSize = { 0,0 };
	divCnt = { 0,0 };
	death = false;
}

Obj::~Obj()
{
}

void Obj::init(std::string filename, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, int speed)
{
	ImageMng::GetInstance().GetID(filename, divSize, divCnt, chipOffset);
	imageName = filename;
	this->divSize = divSize;
	this->divCnt = divCnt;
	this->chipOffset = chipOffset;
	this->speed = speed;
	initAnim();
}

bool Obj::Update()
{
	return false;
}

void Obj::Draw()
{
	if (imageName.length() == 0)
	{
		return;
	}
	VECTOR2 drawOffset = lpMapCtl.GetDrawOffset();

	int id = 0;
	if (animTable.find(animName) != animTable.end())
	{
		id = animTable[animName][ANIM_TBL_START] + (animCnt / animTable[animName][ANIM_TBL_INV]) % animTable[animName][ANIM_TBL_FRAME];
	}

	if (dirLR == DIR_R)
	{
		DrawGraph(pos.x + drawOffset.x, pos.y + drawOffset.y, IMAGE_ID(imageName)[id], true);
		//DrawGraph(pos.x, pos.y, IMAGE_ID(imageName)[chipOffset.x + chipOffset.y * divCnt.x], true);
	}
	if (dirLR == DIR_L)
	{
		DrawTurnGraph(pos.x + drawOffset.x, pos.y + drawOffset.y, IMAGE_ID(imageName)[id], true);
	}
}

void Obj::Draw(int id)
{
	if (imageName.length() == 0)
	{
		return;
	}
	if ((int)IMAGE_ID(imageName).size() <= id)
	{
		return;
	}
	VECTOR2 drawOffset = lpMapCtl.GetDrawOffset();
	DrawGraph(pos.x + drawOffset.x, pos.y + drawOffset.y, IMAGE_ID(imageName)[id], true);

}

void Obj::SetPos(const VECTOR2 & pos)
{
	this->pos = pos;
}

bool Obj::GetDeath()
{
	return death;
}

const VECTOR2 & Obj::GetPos()
{
	return pos;
}

bool Obj::SetAnim(std::string animName)
{
	Obj::animName = animName;
	if (animTable.find(animName) == animTable.end())
	{
		return false;
	}
	if (Obj::animName == animName)
	{
		//animCnt = 0;
		Obj::animName = animName;
	}
	return false;
}

bool Obj::initAnim()
{
	return true;
}

bool Obj::AddAnim(std::string animName, int id_x, int id_y, int frame, int inv)
{
	animTable[animName][ANIM_TBL_START] = id_x + id_y * divCnt.x;
	animTable[animName][ANIM_TBL_FRAME] = frame;
	animTable[animName][ANIM_TBL_INV] = inv;
	return true;
}
