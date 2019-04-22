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

//	��Ұ��݊֘A
enum ANIM_TBL {
	ANIM_TBL_START,				//	���߂̽��Ĉʒu
	ANIM_TBL_FRAME,				//	�ϐ�
	ANIM_TBL_INV,				//	�Ԋu
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
	VECTOR2 divSize;		//	�`�����߻���
	VECTOR2 divCnt;			//	�`�����߂̐�(�c��)
	VECTOR2 chipOffset;		//	�`�����߂̲Ұ��ID��2�����z��
	std::map<std::string, int[ANIM_TBL_MAX]> animTable;
	std::string animName;				//	��Ұ��ݖ�
	virtual bool initAnim();
protected:
	const char(&keyData)[256];
	const char(&keyDataOld)[256];
	VECTOR2 pos;			//	�`��ʒu
	int speed;				//	�ړ���
	unsigned int animCnt;
	DIR_LR dirLR;
	bool AddAnim(std::string animName, int id_x, int id_y, int frame, int inv);
	bool death;
};

