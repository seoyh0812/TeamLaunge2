#pragma once

//Ÿ�� ������
#define TILESIZEX 64
#define TILESIZEY 32

//Ÿ�� ����
#define TILEX 30
#define TILEY 30

//Ÿ�ϼ�(����Ÿ��) ����
#define SAMPLEX 8
#define SAMPLEY 12

enum moveUnMove
{
	MOVE, UNMOVE
};

enum renderSize
{
	SMALL, MEDIUM, MAX
};

enum menuNum
{
	ONE = 1, TWO, THREE
};

enum objName
{
	//������Ʈ 0 ~ 10
	NONE, TREE1, TREE2, TREE3, TREE4, TREE5, PLAYERFLAG, ENEMYFLAG, WALL1, WALL2, WALL3, WALL4,
	PLAYEROCCUPIED, LAVA_OBJ1, LAVA_OBJ2_L, LAVA_OBJ2_R, LAVA_OBJ3,
	//�� 21 ~
	ZERGLING = 21, MARINE, CIVILIAN, TEMPLAR, BISHOP, DIABLO, SKELETON, GHOST
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
	int gold; // ���� 0��Ÿ�Ͽ��� �����. �������� ���ް��
	moveUnMove MUM;
	objName    name;
	POINT	pt;
};
