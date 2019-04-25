#pragma once
#include <memory>
#include "VECTOR2.h"
#include "Obj.h"


class Camera
{
public:
	Camera();
	~Camera();

	VECTOR2 &GetPos(void);
	bool SetPos(VECTOR2 pos);
	bool SetPos(float x, float y);
	bool SetTarget(std::weak_ptr<Obj> target);
	void Update(void);
private:
	VECTOR2 pos;
	std::weak_ptr<Obj> target;
	RECT antiMoveRect;
};
