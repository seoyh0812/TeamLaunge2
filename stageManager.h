#pragma once
#include "gameNode.h"
#include "tile.h"
#include "unitManager.h"

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
	void createAlly();		//���� ���۽� �Ʊ� �������ִ� �Լ�

	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ� 

	void setStage(STAGE stage);
	isoTile* getIsoTile() { return _isoTile; }		//Ÿ���� ���� ������Ʈ �Ӽ� ����
	void umLink(unitManager * um) { _um = um; }
};

