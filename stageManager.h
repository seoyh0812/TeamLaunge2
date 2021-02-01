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

enum tileObj
{
	S_NONE, S_TREE1, S_TREE2, S_TREE3, S_TREE4, S_TREE5, S_ZERGLING = 11
};

class stageManager : public gameNode
{
private:
	isoTile _isoTile[TILEX*TILEY];
	STAGE _stage;
	int _gold; // ���� �������� �𸣰����� ���� ���������Ŵ������� �����ϱ�� ����
	POINT _pickingPt;
	POINT _cameraPtMouse; // ����Ƽ���콺���� ī�޶���ġ ������ ��Ƽ���콺

	RECT _homeBt;


	unitManager* _um;
	bool _battlePhase; // �̰� false�� ��ġ������ true�� ����������
	bool _menuInPt;			//���콺�� �޴��ȿ� ������ ���ʿ��� �ൿ���� �����ϱ� ���� ����
	
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
	inline POINT picking(long x, long y); // ��ŷ�ϴ� �Լ� 

	void setStage(STAGE stage);
	isoTile* getIsoTile() { return _isoTile; }		//Ÿ���� ���� ������Ʈ �Ӽ� ����
	void umLink(unitManager * um) { _um = um; }
};

