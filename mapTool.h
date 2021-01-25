#pragma once
#include "gameNode.h"

//Ÿ�� ������
#define TILESIZEX 64
#define TILESIZEY 32

//Ÿ�� ����
#define TILEX 20
#define TILEY 20

//�� ������
#define MAPSIZEX TILESIZEX * TILEX
#define MAPSIZEY TILESIZEY * TILEY

//Ÿ�ϼ�(����Ÿ��) ����
#define SAMPLEX 4
#define SAMPLEY 5

//�ֱ� �̰�
#define ISO_UNMOVE UNMOVE

enum moveUnMove
{
	MOVE, UNMOVE
};

//�׷����� isoŸ��
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

//���� Ŭ���� ���� Ÿ���� ������ ����ü
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

	void createIsoMap(float x, float y, int tileX, int tileY);		//���ʿ� ���̽�Ÿ�� ����ִ� �Լ�
	void createSampleTiles();										//����Ÿ�� ����ִ� �Լ�
	void ptInSample();												//����Ÿ�� �ȿ� ���콺�� ������
	void createTile();												//Ÿ���� ���Ӱ� ������Ʈ ���ִ� �Լ�
	void imageInit();												//�̹��� ����
	void imageRender();												//�̹��� ����
	void moveUnMove();												//�ΰ� ��ư�� �������� �Ͼ�� �������

	void save();
	void load();
	void tempSave();												//�ڷΰ��Ⱑ �Ǿ��� ��Ȳ(?)�� �����ؼ� ����ִ� ���
	void tempLoad();												//�ڷΰ����� ��Ȳ(?)�� �ҷ�����

	void fill(int x, int y);										//��ü Ÿ���� ĥ���ִ� �Լ�

	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ�
};

