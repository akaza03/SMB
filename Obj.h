#pragma once
#include <string>
#include <map>
#include <vector>
#include "VECTOR2.h"

enum DIR_LR {
	DIR_L,
	DIR_R,
	DIR_MAX
};

//	±ÆÒ°¼®İŠÖ˜A
enum ANIM_TBL {
	ANIM_TBL_START,				//	Á¯Ìß‚Ì½À°ÄˆÊ’u
	ANIM_TBL_FRAME,				//	ºÏ”
	ANIM_TBL_INV,				//	ŠÔŠu
	ANIM_TBL_MAX
};

class Obj
{
public:
	Obj(const char(&_keyData)[256], const char(&_keyDataOld)[256],VECTOR2(chipOffset));
	~Obj();
	void init(std::string filename, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, int speed);
	virtual bool Update();
	virtual void Draw();
	void Draw(int id);
	void SetPos(const VECTOR2& pos);
	bool GetDeath();
	const VECTOR2 & GetPos();
	bool SetAnim(std::string animName);
private:
	std::string imageName;
	VECTOR2 divSize;		//	•`‰æÁ¯Ìß»²½Ş
	VECTOR2 divCnt;			//	•`‰æÁ¯Ìß‚Ì”(c‰¡)
	VECTOR2 chipOffset;		//	•`‰æÁ¯Ìß‚Ì²Ò°¼ŞID‚Ì2ŸŒ³”z—ñ
	std::map<std::string, int[ANIM_TBL_MAX]> animTable;
	std::string animName;				//	±ÆÒ°¼®İ–¼
	virtual bool initAnim();
protected:
	const char(&keyData)[256];
	const char(&keyDataOld)[256];
	VECTOR2 pos;			//	•`‰æˆÊ’u
	int speed;				//	ˆÚ“®—Ê
	unsigned int animCnt;
	DIR_LR dirLR;
	bool AddAnim(std::string animName, int id_x, int id_y, int frame, int inv);
	bool death;
};

