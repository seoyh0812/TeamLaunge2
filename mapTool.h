#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>

//�ֱ� �̰�
#define ISO_UNMOVE UNMOVE

//########aStar���� ����###########
struct tagMAStarTile
{
	int tileNum;
	int parentNodeTileNum;
	int totalCost;
	int costFromStart;
	int costToGoal;
	bool isOpen;
};
//########aStar���� ����###########

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

	RECT			_goldBt;

	RECT			_menuRc;
	RECT			_objDel;

	RECT			_delAll;
	RECT			_homeBt;

	RECT			_tree1;
	RECT			_tree2;
	RECT			_tree3;
	RECT			_tree4;
	RECT			_tree5;

	RECT			_wall1;
	RECT			_wall2;
	RECT			_wall3;
	RECT			_wall4;

	RECT			_playerFlagRc;
	RECT			_enemyFlagRc;
	int _savePopUp; // 0�̸� ���°Ű� 1�̸� �����ߵƴ� 2�̸� �����޼��� �˾�
	int _popUpCount;

	/////////////////////////////////////
	RECT			_icZergling;
	RECT			_icMarine;
	RECT			_icCivilian;
	RECT			_icTemplar;
	RECT			_icBishop;
	RECT			_icDiablo;
	RECT			_icSkeleton;
	RECT			_icGhost;
	/////////////////////////////////////
	POINT			_pickingPt;

	POINT			_cameraPtMouse; // ����Ƽ���콺���� ī�޶���ġ ������ ��Ƽ���콺

	bool			_moveUnMove;
	bool			_tempSaved;
	bool			_brushOn;
	bool			_objDelOn;
	bool			_menuInPt;

	int _currentStage; // �� �������� �۾������� (���ǻ� 1,2,3)

	renderSize		_rs;
	menuNum			_menuNum;
	objName			_objName;

	//########aStar���� ����###########
	vector<tagMAStarTile*>			_vTotalList;
	vector<tagMAStarTile*>::iterator _viTotalList;
	vector<tagMAStarTile*>			_vOpenList;
	vector<tagMAStarTile*>::iterator _viOpenList;
	vector<tagMAStarTile*>			_vCloseList;
	vector<tagMAStarTile*>::iterator _viCloseList;
	int _startTile;		//����Ÿ���� ��ȣ
	int _endTile;			//����Ÿ��
	int _currentTile;		//����Ÿ��

	bool _stop; // ��ã����
	bool _seePath;

	int _playerTile; // �÷��̾� ����� ��Ÿ�Ͽ� �ִ��� �ε��Ҷ� �ҷ��´�.
	int _enemyTile; // ���ʹ� ����� ��Ÿ�Ͽ� �ִ��� �ε��Ҷ� �ҷ��´�.

	int _modifyingNum; // ���ڸ���°�� ���������� (0=������x, 1õ�ڸ��� 2���ڸ��� 3���ڸ��� 4�����ڸ���)
	int _modifyingCount; // 5��ī��Ʈ
public:
	vector<int> aStarPath(int fromTileNum, int toTileNum);

	//���� �ִ� ���� ã�Ƴ��� ����� �Լ�
	vector<tagMAStarTile*> addOpenList(int currentTile);
	//���� ��� ã�� �Լ�
	void pathFinder(int currentTile);
	//########aStar����###########

public:
	mapTool();
	~mapTool();
	vector<int> _path;

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
	void homeBt();

	void save();
	void load();
	void tempSave();												//�ڷΰ��Ⱑ �Ǿ��� ��Ȳ(?)�� �����ؼ� ����ִ� ���
	void tempLoad();												//�ڷΰ����� ��Ȳ(?)�� �ҷ�����

	void fill(int x, int y);										//��ü Ÿ���� ĥ���ִ� �Լ�
	void objDelAll();												//������Ʈ ��ü�� �����ִ� �Լ�

	void cameraControl();
	void sampleTileMove();

	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ�


	void numberInput();
};

