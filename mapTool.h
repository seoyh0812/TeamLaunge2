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
	bool _tempSaved; // Ű�ڸ��� ������Ҵ����µ� ������ �ҷ����°� �����Ϸ���
	int _selectTileX; int _selectTileY;
	int _currentStage;
	tagSampleTile _sampleTile;



private:

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void save(); // map���Ͽ� ����
	void load(); // map���Ϸκ��� �ҷ�����
	void tempSave();
	void tempLoad();	
	void fill(int x, int y);


	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ�
};

