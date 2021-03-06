#include <DxLib.h>
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

	chipGP[0] = GP_BG;			//	空白
	chipGP[1] = GP_BG;			//	地面用ﾌﾞﾛｯｸ
	chipGP[2] = GP_BG;			//	ﾚﾝｶﾞﾌﾞﾛｯｸ(破壊可能)
	chipGP[3] = GP_BG;			//	破壊できないﾌﾞﾛｯｸ(ﾊﾃﾅﾌﾞﾛｯｸの成れの果て)
	chipGP[4] = GP_BG;			//	ﾊﾃﾅﾌﾞﾛｯｸ
	chipGP[5] = GP_ITEM;		//	ｽｰﾊﾟｰｷﾉｺ
	chipGP[6] = GP_ITEM;		//	ﾌｧｲｱﾌﾗﾜｰ
	chipGP[7] = GP_ITEM;		//	ｺｲﾝ
	chipGP[8] = GP_CHAR;		//	ﾌﾟﾚｲﾔｰ
	chipGP[9] = GP_CHAR;		//	敵
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

	//	ﾏｯﾌﾟﾃﾞｰﾀの読み込み
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

	//	m_mapの要素数の取得
	int mapY = sizeof(m_map) / sizeof(m_map[0]);
	int mapX = sizeof(m_map[0]) / sizeof(m_map[0][0]);

	mapID.resize(mapY);
	for (int IDy = 0; IDy < mapY; IDy++)
	{
		mapID[IDy].resize(mapX);
	}

	//	ﾏｯﾌﾟﾃﾞｰﾀの書き込み
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
						//	ｹﾞｰﾑ中は描画しない
					case	TYPE_BLANK:				//	空白
					case	TYPE_PLAYER:			//	ﾌﾟﾚｲﾔｰ
					case	TYPE_ENEMY:				//	敵
						break;
						//	普通に描画
					case	TYPE_GL:				//	地面用ﾌﾞﾛｯｸ
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[1], true);
						break;
					case	TYPE_BBL:				//	ﾚﾝｶﾞﾌﾞﾛｯｸ(破壊可能)
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[2], true);
						break;
					case	TYPE_BL:				//	破壊できないﾌﾞﾛｯｸ(ﾊﾃﾅﾌﾞﾛｯｸの成れの果て)
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[4], true);
						break;
					case	TYPE_PIPE_LU:			//	土管の左上
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[273], true);
						break;
					case	TYPE_PIPE_LD:			//	土管の左下
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[307], true);
						break;
					case	TYPE_PIPE_RU:			//	土管の右上
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[274], true);
						break;
					case	TYPE_PIPE_RD:			//	土管の右下
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[308], true);
						break;
					case	TYPE_GOLD:				//	ｺｲﾝ
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[59], true);
						break;
						//	特殊描画
					case	TYPE_QBL:				//	ﾊﾃﾅﾌﾞﾛｯｸ
						//if (){
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0,0))[25], true);
						break;
						//}
						//else
						//{
						//	//	破壊できないﾌﾞﾛｯｸ(ﾊﾃﾅﾌﾞﾛｯｸの成れの果て)
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

void MapCtl::SetMap(CHIP_TYPE type, VECTOR2 pos)
{
	VECTOR2 SetPos = pos / CHIP_SIZE;
	mapID[SetPos.y][SetPos.x] = type;
}
