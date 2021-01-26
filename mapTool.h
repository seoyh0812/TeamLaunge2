#pragma once
#include "gameNode.h"
#include "tile.h"

//멀까 이건
#define ISO_UNMOVE UNMOVE

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
	int fX;
	int fY;
};

class mapTool : public gameNode
{
private:
	isoTile		_isoTile[TILEX * TILEY];
	tagTilePoint	_tilePoint;
	tagSample		_sample[SAMPLEX * SAMPLEY];
	tagTempTile		_tempTile;

	//버튼 렉트들
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

	RECT			_open;
	RECT			_close;

	RECT			_small;
	RECT			_medium;
	RECT			_max;

	RECT			_leftBt;
	RECT			_rightBt;

	RECT			_menuRc;
	RECT			_objDel;

	RECT			_tree1;
	RECT			_icZergling;
	/////////////////////////////////////
	POINT			_pickingPt;

	POINT			_cameraPtMouse; // 걍피티마우스말고 카메라위치 보정한 피티마우스

	bool			_moveUnMove;
	bool			_tempSaved;
	bool			_brushOn;
	bool			_objDelOn;
	bool			_menuInPt;

	renderSize		_rs;
	menuNum			_menuNum;
	objName			_objName;
public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	void createIsoMap(int tileX, int tileY);		//왼쪽에 베이스타일 깔아주는 함수
	void createSampleTiles();										//샘플타일 깔아주는 함수
	void ptInIso();												//샘플타일 안에 마우스가 들어갔을때
	void createTile();												//타일을 새롭게 업데이트 해주는 함수
	void imageInit();												//이미지 인잇
	void imageRender();												//이미지 렌더
	void moveUnMove();												//두개 버튼을 눌렀을때 일어나는 기능정의
	void openClose();												//브러쉬도구 접기 펼치기
	void renderSize();												//렌더 사이즈 조절
	void leftRightBt();												//브러쉬도구 메뉴 넘기기
	void ptInObj();													//오브젝트마다 고유이름을 주었기때문에 오브젝트 클릭시 효과를 다르게줄려고만듬
	void createObj();												//타일에 오브젝트 속성을 넣어주는 것
	void objDel();													//오브젝트 지우개
	void menuInPt();												//메뉴 안에 마우스가 들어갔을때 타일 안찍히게 막음

	void save();
	void load();
	void tempSave();												//뒤로가기가 되어줄 상황(?)을 저장해서 담아주는 기능
	void tempLoad();												//뒤로가기의 상황(?)을 불러와줌

	void fill(int x, int y);										//전체 타일을 칠해주는 함수

	void cameraControl();
	void sampleTileMove();

	inline POINT picking(long x, long y); // 피킹하는 함수
};

