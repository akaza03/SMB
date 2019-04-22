#pragma once
#include <memory>
#include <array>
#include "ImageMng.h"

class BaseScene;
using scene_ptr = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	virtual ~BaseScene();
	virtual scene_ptr Update(scene_ptr scn) = 0;
};

