#pragma once
#include "gameNode.h"
#include "tile.h"
#include "unitManager.h"

struct tagAStarTile
{
	int tileNum;
	int parentNodeTileNum;
	int totalCost;
	int costFromStart;
	int costToGoal;
	bool isOpen;
};

enum STAGE
{
	STAGE1,
	STAGE2,
	STAGE3
};

enum STAGEMOVE
{
	S_MOVE, S_UNMOVE
};

enum pickUnit
{
	P_NONE, P_ZERGLING, P_MARINE, P_CIVILIAN, P_TEMPLAR, P_BISHOP, P_GHOST
};

class stageManager : public gameNode
{
private:
	isoTile _isoTile[TILEX*TILEY];
	STAGE _stage;
	int _gold; // ���� �������� �𸣰����� ���� ���������Ŵ������� �����ϱ�� ����
	POINT _pickingPt;
	POINT _cameraPtMouse; // ����Ƽ���콺���� ī�޶���ġ ������ ��Ƽ���콺

	RECT	_homeBt;
	RECT	_onBt;
	RECT	_offBt;
	RECT	_startBt;
	RECT	_retryBt;
	RECT	_clearBt;

	//���� ���� ��Ʈ
	RECT	_zerglingBt;
	RECT	_marineBt;
	RECT	_civilianBt;
	RECT	_templarBt;
	RECT	_bishopBt;
	RECT	_ghostBt;

	unitManager* _um;
	bool	_battlePhase; // �̰� false�� ��ġ������ true�� ����������
	bool	_menuInPt;			//���콺�� �޴��ȿ� ������ ���ʿ��� �ൿ���� �����ϱ� ���� ����
	bool	_onOff;				//���ֱ��� �޴� �¿���(���ӽ��۴������� �ڵ����� ������ ����Ǿ���)
	pickUnit	_pickUnit;
	int _tempGold; //��� �������� �Ǹ� �̰� �ٽ� �ҷ���
	int _playerTile;
	int _enemyTile;
	int _alpha;
	

	vector<tagAStarTile*>			_vTotalList;
	vector<tagAStarTile*>::iterator _viTotalList;
	vector<tagAStarTile*>			_vOpenList;
	vector<tagAStarTile*>::iterator _viOpenList;
	vector<tagAStarTile*>			_vCloseList;
	vector<tagAStarTile*>::iterator _viCloseList;
	vector<int> _path;

	int _startTile;		//����Ÿ���� ��ȣ
	int _endTile;			//����Ÿ��
	int _currentTile;		//����Ÿ��

	bool _stop; // ��ã����

	bool _isVictory;
	bool _isDefeat;

public:
	stageManager();
	~stageManager();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	void objectRender();    //������Ʈ �׸��°� ���� �M. �ֳĸ� ���� ������ �׷�����ϹǷ�
	void uiRender();		//UI���� (�ֻ�� ������ ���� ���μ���)
	void uiRect();			//UI��ġ�� ��Ʈ�� ��Ƽ� ����� �ο����ֱ�����
	void homeBt();			//Ȩ��ư ���
	void onOffBt();			//�޴� ON/OFF ��ư ���
	void startBt();			//��ŸƮ ��ư ���
	void retryBt();			//��Ʈ���� ��ư ���
	void ptInIso();			//���̼�Ÿ�Ͼȿ� ���콺�� ���Դ��� �Ǵ�����
	void ptInCreateMenu();	//���콺�� ���� �޴��ȿ� ������
	void ptInMenu();		//�޴��ȿ� ���콺�� ������ üũ���ִ� ���
	void createUnit();		//���� �����ϴ� �ڵ�
	void clearBt();			//Ŭ�����ư ���

	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ� 

	void setStage(STAGE stage);
	isoTile* getIsoTile() { return _isoTile; }		//Ÿ���� ���� ������Ʈ �Ӽ� ����


	vector<int> aStarPath(int fromTileNum, int toTileNum);

	//���� �ִ� ���� ã�Ƴ��� ����� �Լ�
	vector<tagAStarTile*> addOpenList(int currentTile);
	//���� ��� ã�� �Լ�
	void pathFinder(int currentTile);

	void umLink(unitManager * um) { _um = um; }

	void stageChange();
};

