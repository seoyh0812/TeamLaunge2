#pragma once

//타일 사이즈
#define TILESIZEX 64
#define TILESIZEY 32

//타일 갯수
#define TILEX 30
#define TILEY 30

//맵 사이즈
#define MAPSIZEX TILESIZEX * TILEX
#define MAPSIZEY TILESIZEY * TILEY

//타일셋(샘플타일) 범위
#define SAMPLEX 4
#define SAMPLEY 5

enum moveUnMove
{
	MOVE, UNMOVE
};

//그려지는 iso타일
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
