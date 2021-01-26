#pragma once
#include "gameNode.h"
#include "tile.h"

//�ֱ� �̰�
#define ISO_UNMOVE UNMOVE

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
	isoTile		_isoTile[TILEX * TILEY];
	tagTilePoint	_tilePoint;
	tagSample		_sample[SAMPLEX * SAMPLEY];
	tagTempTile		_tempTile;

	//��ư ��Ʈ��
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
	/////////////////////////////////////
	POINT			_pickingPt;

	POINT			_cameraPtMouse; // ����Ƽ���콺���� ī�޶���ġ ������ ��Ƽ���콺

	bool			_moveUnMove;
	bool			_tempSaved;
	bool			_brushOn;

	renderSize		_rs;
public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	void createIsoMap(int tileX, int tileY);		//���ʿ� ���̽�Ÿ�� ����ִ� �Լ�
	void createSampleTiles();										//����Ÿ�� ����ִ� �Լ�
	void ptInSample();												//����Ÿ�� �ȿ� ���콺�� ������
	void createTile();												//Ÿ���� ���Ӱ� ������Ʈ ���ִ� �Լ�
	void imageInit();												//�̹��� ����
	void imageRender();												//�̹��� ����
	void moveUnMove();												//�ΰ� ��ư�� �������� �Ͼ�� �������
	void openClose();												//�귯������ ���� ��ġ��
	void renderSize();												//���� ������ ����

	void save();
	void load();
	void tempSave();												//�ڷΰ��Ⱑ �Ǿ��� ��Ȳ(?)�� �����ؼ� ����ִ� ���
	void tempLoad();												//�ڷΰ����� ��Ȳ(?)�� �ҷ�����

	void fill(int x, int y);										//��ü Ÿ���� ĥ���ִ� �Լ�

	void cameraControl();
	void sampleTileMove();

	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ�
};

