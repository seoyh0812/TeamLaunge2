#pragma once
#include "gameNode.h"
#include <vector>
#include <string>
#include "tile.h"

#define TILEWIDTH 64
#define TILEHEIGHT 32

#define TILENUMX 10
#define TILENUMY 10

#define SAMPLETILEX 7
#define SAMPLETILEY 1

struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

class mapTool :	public gameNode
{

	tile _tiles[TILENUMX*TILENUMY];
	bool _tempSaved; // 키자마자 실행취소눌렀는데 템프가 불러오는걸 방지하려고
	int _selectTileX; int _selectTileY;
	int _currentStage;
	tagSampleTile _sampleTile;



private:

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void save(); // map파일에 저장
	void load(); // map파일로부터 불러오기
	void tempSave();
	void tempLoad();	
	void fill(int x, int y);


	inline POINT picking(long x, long y); // 피킹하는 함수
};

