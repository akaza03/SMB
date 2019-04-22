#pragma once
#include <mutex>
#include <map>
#include <vector>
#include "VECTOR2.h"

using VEC_INT = std::vector<int>;
#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

class ImageMng
{
public:
	static ImageMng &GetInstance()
	{
		return *s_Instance;
	}
	const VEC_INT& GetID(std::string f_name);
	const VEC_INT& GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset);
private:
	struct ImageMngDeleter
	{
		void operator()(ImageMng* imageMng) const
		{
			delete imageMng;
		}
	};
	static std::unique_ptr<ImageMng, ImageMngDeleter> s_Instance;
	ImageMng();
	~ImageMng();
	std::map<std::string, VEC_INT>imgMap;
};

