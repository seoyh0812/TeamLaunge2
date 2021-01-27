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

	RECT			_leftBt;
	RECT			_rightBt;

	RECT			_menuRc;
	RECT			_objDel;

	RECT			_delAll;

	RECT			_tree1;
	RECT			_tree2;
	RECT			_tree3;
	RECT			_tree4;
	RECT			_tree5;

	RECT			_icZergling;
	/////////////////////////////////////
	POINT			_pickingPt;

	POINT			_cameraPtMouse; // ����Ƽ���콺���� ī�޶���ġ ������ ��Ƽ���콺

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

	void createIsoMap(int tileX, int tileY);		//���ʿ� ���̽�Ÿ�� ����ִ� �Լ�
	void createSampleTiles();										//����Ÿ�� ����ִ� �Լ�
	void ptInIso();												//����Ÿ�� �ȿ� ���콺�� ������
	void createTile();												//Ÿ���� ���Ӱ� ������Ʈ ���ִ� �Լ�
	void imageInit();												//�̹��� ����
	void imageRender();												//�̹��� ����
	void moveUnMove();												//�ΰ� ��ư�� �������� �Ͼ�� �������
	void openClose();												//�귯������ ���� ��ġ��
	void renderSize();												//���� ������ ����
	void leftRightBt();												//�귯������ �޴� �ѱ��
	void ptInObj();													//������Ʈ���� �����̸��� �־��⶧���� ������Ʈ Ŭ���� ȿ���� �ٸ����ٷ�����
	void createObj();												//Ÿ�Ͽ� ������Ʈ �Ӽ��� �־��ִ� ��
	void objDel();													//������Ʈ ���찳
	void menuInPt();												//�޴� �ȿ� ���콺�� ������ Ÿ�� �������� ����
	void sampleInTemp();											//���� Ÿ���� ���� ������ ����ִ� �Լ�

	void save();
	void load();
	void tempSave();												//�ڷΰ��Ⱑ �Ǿ��� ��Ȳ(?)�� �����ؼ� ����ִ� ���
	void tempLoad();												//�ڷΰ����� ��Ȳ(?)�� �ҷ�����

	void fill(int x, int y);										//��ü Ÿ���� ĥ���ִ� �Լ�
	void objDelAll();												//������Ʈ ��ü�� �����ִ� �Լ�

	void cameraControl();
	void sampleTileMove();

	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ�
};

