#pragma once

//Ÿ�� ������
#define TILESIZEX 64
#define TILESIZEY 32

//Ÿ�� ����
#define TILEX 30
#define TILEY 30

//�� ������
#define MAPSIZEX TILESIZEX * TILEX
#define MAPSIZEY TILESIZEY * TILEY

//Ÿ�ϼ�(����Ÿ��) ����
#define SAMPLEX 4
#define SAMPLEY 5

enum moveUnMove
{
	MOVE, UNMOVE
};

//�׷����� isoŸ��
class isoTile
{
public:
	float drawX;
	float drawY;
	float centerX;
	float centerY;
	int nX;
	int nY;
	int fX;
	int fY;
	bool inRect;
	moveUnMove MUM;
};
