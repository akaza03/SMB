#include "DxLib.h"
#include "ImageMng.h"

std::unique_ptr<ImageMng, ImageMng::ImageMngDeleter> ImageMng::s_Instance(new ImageMng());


const VEC_INT & ImageMng::GetID(std::string f_name)
{
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(1);
		imgMap[f_name][0] = LoadGraph(f_name.c_str());
	}
	return imgMap[f_name];
	// TODO: return ステートメントをここに挿入します
}

const VEC_INT & ImageMng::GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset)
{
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(divCnt.x * divCnt.y);
		imgMap[f_name][0] = LoadDivGraph(f_name.c_str(),divCnt.x * divCnt.y,divCnt.x,divCnt.y,divSize.x,divSize.y,&imgMap[f_name][0],true);
	}
	return imgMap[f_name];
	// TODO: return ステートメントをここに挿入します
}

ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}

