#include "DxLib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "ImageMng.h"
#include "MapCtl.h"

std::unique_ptr<MapCtl, MapCtl::MapCtlDeleter> MapCtl::s_Instance(new MapCtl);


MapCtl::MapCtl()
{
	//mapID.resize(GAME_AREA_CNT_Y);
	//for (int y = 0; y < GAME_AREA_CNT_Y; y++)
	//{
	//	mapID[y].resize(GAME_AREA_CNT_X);
	//}

	chipGP[0] = GP_BG;			//	‹ó”’
	chipGP[1] = GP_BG;			//	’n–Ê—pÌÞÛ¯¸
	chipGP[2] = GP_BG;			//	ÚÝ¶ÞÌÞÛ¯¸(”j‰ó‰Â”\)
	chipGP[3] = GP_BG;			//	”j‰ó‚Å‚«‚È‚¢ÌÞÛ¯¸(ÊÃÅÌÞÛ¯¸‚Ì¬‚ê‚Ì‰Ê‚Ä)
	chipGP[4] = GP_BG;			//	ÊÃÅÌÞÛ¯¸
	chipGP[5] = GP_ITEM;		//	½°Êß°·Éº
	chipGP[6] = GP_ITEM;		//	Ì§²±Ì×Ü°
	chipGP[7] = GP_ITEM;		//	º²Ý
	chipGP[8] = GP_CHAR;		//	ÌßÚ²Ô°
	chipGP[9] = GP_CHAR;		//	“G
}


MapCtl::~MapCtl()
{
}

bool MapCtl::LoadMap(std::string filename)
{
	using namespace std;
	ifstream ifs(filename);
	string str;
	int x = 0;
	int y = 0;

	int m_map[20][100];

	//	Ï¯ÌßÃÞ°À‚Ì“Ç‚Ýž‚Ý
	while (getline(ifs, str))
	{
		string token;
		istringstream stream(str);
		while (getline(stream, token, ','))
		{
			m_map[y][x] = stoi(token.c_str());
			x++;
		}
	}

	//	m_map‚Ì—v‘f”‚ÌŽæ“¾
	int mapY = sizeof(m_map) / sizeof(m_map[0]);
	int mapX = sizeof(m_map[0]) / sizeof(m_map[0][0]);

	mapID.resize(mapY);
	for (int IDy = 0; IDy < mapY; IDy++)
	{
		mapID[IDy].resize(mapX);
	}

	//	Ï¯ÌßÃÞ°À‚Ì‘‚«ž‚Ý
	for (int Posy = 0; Posy < 20; Posy++)
	{
		for (int Posx = 0; Posx < 100; Posx++)
		{
			mapID[Posy][Posx] = m_map[Posy][Posx];
		}
	}

	return true;
}

CHIP_TYPE MapCtl::GetMapData(VECTOR2 pos, CHIP_GP gpID) const
{
	VECTOR2 tmpPos(pos / CHIP_SIZE);
	if (tmpPos.y >= (float)mapID.size())
	{
		return TYPE_BLANK;
	}
	if (tmpPos.x >= (float)mapID[tmpPos.y].size())
	{
		return TYPE_BLANK;
	}
	return (CHIP_TYPE)((mapID[tmpPos.y][tmpPos.x] >> (gpID * DATA_BIT_LEN)) & 0xff);
}

CHIP_TYPE MapCtl::GetMapData(float x, float y, CHIP_GP gpID) const
{
	if (x < 0 || y < 0)
	{
		return TYPE_BLANK;
	}
	if (y >= (float)mapID.size())
	{
		return TYPE_BLANK;
	}
	if (x >= (float)mapID[y].size())
	{
		return TYPE_BLANK;
	}
	return (CHIP_TYPE)((mapID[y][x] >> (gpID * DATA_BIT_LEN)) & 0xff);
}

void MapCtl::MapDraw()
{
	VECTOR2 drawOffset = GetDrawOffset();
	int drawStartX = -(drawOffset.x / CHIP_SIZE);

	ClsDrawScreen();
	for (CHIP_GP gp = GP_BG; gp < TYPE_MAX; gp = (CHIP_GP)(gp + 1))
	{
		for (int y = 0; y < GAME_AREA_CNT_Y; y++)
		{
			for (int x = drawStartX; x < drawStartX + 1 + VIEW_AREA_CNT_X; x++)
			{
				if (GET_MAP_ID2(x, y, gp) != TYPE_BLANK)
				{
					CHIP_TYPE tmp = GET_MAP_ID2(x, y, gp);
					switch (tmp)
					{
						//	¹Þ°Ñ’†‚Í•`‰æ‚µ‚È‚¢
					case	TYPE_BLANK:				//	‹ó”’
					case	TYPE_PLAYER:			//	ÌßÚ²Ô°
					case	TYPE_ENEMY:				//	“G
						break;
						//	•’Ê‚É•`‰æ
					case	TYPE_GL:				//	’n–Ê—pÌÞÛ¯¸
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[1], true);
						break;
					case	TYPE_BBL:				//	ÚÝ¶ÞÌÞÛ¯¸(”j‰ó‰Â”\)
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[2], true);
						break;
					case	TYPE_BL:				//	”j‰ó‚Å‚«‚È‚¢ÌÞÛ¯¸(ÊÃÅÌÞÛ¯¸‚Ì¬‚ê‚Ì‰Ê‚Ä)
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[4], true);
						break;
					case	TYPE_PIPE_LU:			//	“yŠÇ‚Ì¶ã
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[273], true);
						break;
					case	TYPE_PIPE_LD:			//	“yŠÇ‚Ì¶‰º
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[307], true);
						break;
					case	TYPE_PIPE_RU:			//	“yŠÇ‚Ì‰Eã
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[274], true);
						break;
					case	TYPE_PIPE_RD:			//	“yŠÇ‚Ì‰E‰º
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[308], true);
						break;
					case	TYPE_GOLD:				//	º²Ý
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[59], true);
						break;
						//	“ÁŽê•`‰æ
					case	TYPE_QBL:				//	ÊÃÅÌÞÛ¯¸
						//if (){
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0,0))[25], true);
						break;
						//}
						//else
						//{
						//	//	”j‰ó‚Å‚«‚È‚¢ÌÞÛ¯¸(ÊÃÅÌÞÛ¯¸‚Ì¬‚ê‚Ì‰Ê‚Ä)
						//	DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[4], true);
						//}
					default:
						break;
					}
				}
			}
		}
	}
}

const VECTOR2 MapCtl::GetDrawOffset()
{
	return -(cameraPos - (VIEW_AREA / 2) * CHIP_SIZE);
}


void MapCtl::SetCameraPos(VECTOR2 pos)
{
	cameraPos = pos;
}
