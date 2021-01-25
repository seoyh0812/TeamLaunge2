#pragma once
#include "gameNode.h"

//타일 사이즈
#define TILESIZEX 64
#define TILESIZEY 32

//타일 갯수
#define TILEX 20
#define TILEY 20

//맵 사이즈
#define MAPSIZEX TILESIZEX * TILEX
#define MAPSIZEY TILESIZEY * TILEY

//타일셋(샘플타일) 범위
#define SAMPLEX 4
#define SAMPLEY 5

//멀까 이건
#define ISO_UNMOVE UNMOVE

enum moveUnMove
{
	MOVE, UNMOVE
};

//그려지는 iso타일
struct tagIsoTile
{
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

struct tagTilePoint
{
	float x;
	float y;
};

//내가 클릭한 현재 타일을 저장할 구조체
struct tagTempTile
{
	int fX;
	int fY;
};

struct tagSample
{
	RECT rc;
	bool inRect;
	int fX;
	int fY;
};

class mapTool : public gameNode
{
private:
	tagIsoTile		_isoTile[TILEX * TILEY];
	tagTilePoint	_tilePoint;
	tagSample		_sample[SAMPLEX * SAMPLEY];
	tagTempTile		_tempTile;

	RECT			_saveBt;
	RECT			_saveBt2;
	RECT			_saveBt3;

	RECT			_loadBt;
	RECT			_loadBt2;
	RECT			_loadBt3;

	RECT			_move;
	RECT			_unMove;

	RECT			_undo;
	RECT			_fill;

	POINT			_pickingPt;

	bool			_moveUnMove;
	bool			_tempSaved;

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	void createIsoMap(float x, float y, int tileX, int tileY);		//왼쪽에 베이스타일 깔아주는 함수
	void createSampleTiles();										//샘플타일 깔아주는 함수
	void ptInSample();												//샘플타일 안에 마우스가 들어갔을때
	void createTile();												//타일을 새롭게 업데이트 해주는 함수
	void imageInit();												//이미지 인잇
	void imageRender();												//이미지 렌더
	void moveUnMove();												//두개 버튼을 눌렀을때 일어나는 기능정의

	void save();
	void load();
	void tempSave();												//뒤로가기가 되어줄 상황(?)을 저장해서 담아주는 기능
	void tempLoad();												//뒤로가기의 상황(?)을 불러와줌

	void fill(int x, int y);										//전체 타일을 칠해주는 함수

	inline POINT picking(long x, long y); // 피킹하는 함수
};

