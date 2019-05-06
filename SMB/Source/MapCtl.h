#pragma once
#include <vector>
#include <memory>
#include "VECTOR2.h"

#define BLANK(Y,X) MapCtl::GetInstance().Blank(Y,X)
#define GET_MAP_ID2(X,Y,Z) MapCtl::GetInstance().GetMapData(X,Y,Z)
#define GET_MAP_SIZE MapCtl::GetInstance().GetChipSize()
#define lpMapCtl MapCtl::GetInstance()

constexpr int DATA_BIT_LEN(8);

constexpr int VIEW_AREA_CNT_X = 20;							//	ï\é¶¥ÿ±
constexpr int VIEW_AREA_CNT_Y = 20;							//	ï\é¶¥ÿ±
constexpr int GAME_AREA_CNT_X = 100;						//	πﬁ∞—ëSëÃÇÃ¥ÿ±
constexpr int GAME_AREA_CNT_Y = VIEW_AREA_CNT_Y;			//	πﬁ∞—ëSëÃÇÃ¥ÿ±
constexpr int CHIP_SIZE = 32;								//	1œΩÇÃª≤Ωﬁ

const VECTOR2 VIEW_AREA = VECTOR2(VIEW_AREA_CNT_X, VIEW_AREA_CNT_Y);
const VECTOR2 GAME_AREA = VECTOR2(GAME_AREA_CNT_X, GAME_AREA_CNT_Y);


//	¡ØÃﬂÇÃ∏ﬁŸ∞Ãﬂï™ÇØ
enum CHIP_GP {
	GP_BG,				//	îwåi
	GP_ITEM,			//	±≤√—
	GP_CHAR,			//	∑¨◊∏¿∞
	GP_MAX
};

//	¡ØÃﬂÇÃéÌóﬁ
enum CHIP_TYPE {
	TYPE_BLANK	 = 0,			//	ãÛîí
	TYPE_GL		 = 1,			//	ínñ ópÃﬁ€Ø∏
	TYPE_BBL	 = 2,			//	⁄›∂ﬁÃﬁ€Ø∏(îjâÛâ¬î\)
	TYPE_BL		 = 6,			//	îjâÛÇ≈Ç´Ç»Ç¢Ãﬁ€Ø∏( √≈Ãﬁ€Ø∏ÇÃê¨ÇÍÇÃâ Çƒ)
	TYPE_QBL	 = 3,			//	 √≈Ãﬁ€Ø∏
	TYPE_PIPE_LU = 19,			//	ìyä«ÇÃç∂è„
	TYPE_PIPE_LD = 28,			//	ìyä«ÇÃç∂â∫
	TYPE_PIPE_RU = 20,			//	ìyä«ÇÃâEè„
	TYPE_PIPE_RD = 29,			//	ìyä«ÇÃâEâ∫
	TYPE_MR,					//	Ω∞ ﬂ∞∑…∫
	TYPE_FLOUR,					//	Ãß≤±Ã◊‹∞
	TYPE_GOLD	 = 12,			//	∫≤›
	TYPE_PLAYER	 = 64,			//	Ãﬂ⁄≤‘∞
	TYPE_ENEMY	 = 37,			//	ìG	
	TYPE_MAX
};


using VEC_CHIP = std::vector<unsigned int>;
using VEC_CHIP2 = std::vector<VEC_CHIP>;


class MapCtl
{
public:
	static MapCtl &GetInstance()
	{
		return *s_Instance;
	}

	CHIP_TYPE GetMapData(VECTOR2 pos, CHIP_GP gpID) const;
	CHIP_TYPE GetMapData(float x, float y, CHIP_GP gpID) const;
	void MapDraw();
	bool LoadMap(std::string filename);
	const VECTOR2 GetDrawOffset();
	void SetCameraPos(VECTOR2 pos);
	void SetMap(CHIP_TYPE type, VECTOR2 pos);

private:
	struct MapCtlDeleter
	{
		void operator()(MapCtl *mapCtl)const
		{
			delete mapCtl;
		}
	};

	static std::unique_ptr<MapCtl, MapCtlDeleter> s_Instance;
	MapCtl();
	~MapCtl();

	VEC_CHIP2 mapID;
	CHIP_GP chipGP[TYPE_MAX];

	VECTOR2 cameraPos;
};

