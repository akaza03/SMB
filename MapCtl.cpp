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

	chipGP[0] = GP_BG;			//	��
	chipGP[1] = GP_BG;			//	�n�ʗp��ۯ�
	chipGP[2] = GP_BG;			//	�ݶ���ۯ�(�j��\)
	chipGP[3] = GP_BG;			//	�j��ł��Ȃ���ۯ�(�����ۯ��̐���̉ʂ�)
	chipGP[4] = GP_BG;			//	�����ۯ�
	chipGP[5] = GP_ITEM;		//	���߰�ɺ
	chipGP[6] = GP_ITEM;		//	̧����ܰ
	chipGP[7] = GP_ITEM;		//	���
	chipGP[8] = GP_CHAR;		//	��ڲ԰
	chipGP[9] = GP_CHAR;		//	�G
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

	//	ϯ���ް��̓ǂݍ���
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

	//	m_map�̗v�f���̎擾
	int mapY = sizeof(m_map) / sizeof(m_map[0]);
	int mapX = sizeof(m_map[0]) / sizeof(m_map[0][0]);

	mapID.resize(mapY);
	for (int IDy = 0; IDy < mapY; IDy++)
	{
		mapID[IDy].resize(mapX);
	}

	//	ϯ���ް��̏�������
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
						//	�ްђ��͕`�悵�Ȃ�
					case	TYPE_BLANK:				//	��
					case	TYPE_PLAYER:			//	��ڲ԰
					case	TYPE_ENEMY:				//	�G
						break;
						//	���ʂɕ`��
					case	TYPE_GL:				//	�n�ʗp��ۯ�
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[1], true);
						break;
					case	TYPE_BBL:				//	�ݶ���ۯ�(�j��\)
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[2], true);
						break;
					case	TYPE_BL:				//	�j��ł��Ȃ���ۯ�(�����ۯ��̐���̉ʂ�)
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[4], true);
						break;
					case	TYPE_PIPE_LU:			//	�y�ǂ̍���
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[273], true);
						break;
					case	TYPE_PIPE_LD:			//	�y�ǂ̍���
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[307], true);
						break;
					case	TYPE_PIPE_RU:			//	�y�ǂ̉E��
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[274], true);
						break;
					case	TYPE_PIPE_RD:			//	�y�ǂ̉E��
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[308], true);
						break;
					case	TYPE_GOLD:				//	���
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0, 0))[59], true);
						break;
						//	����`��
					case	TYPE_QBL:				//	�����ۯ�
						//if (){
						DrawGraph(x * CHIP_SIZE + drawOffset.x, y * CHIP_SIZE/* + drawOffset.y + AreaOffset.y*/, ImageMng::GetInstance().GetID("image/Tile.png", VECTOR2(32, 32), VECTOR2(34, 28), VECTOR2(0,0))[25], true);
						break;
						//}
						//else
						//{
						//	//	�j��ł��Ȃ���ۯ�(�����ۯ��̐���̉ʂ�)
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
