#pragma once
#include "gameNode.h"
#include "zergling.h"
#include "civilian.h"
#include <vector>
#include "stageManager.h"

class unitManager : public gameNode
{
private:
	vector<unit*> _vUnit;
	vector<unit*>::iterator _viUnit;

public:
	unitManager();
	~unitManager();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	vector<unit*> getVUnit() { return _vUnit; }
	vector<unit*>::iterator getViUnit() { return _viUnit; }

	stageManager*	_sm;

	void chanhoUpdate();
	void deokhoUpdate();
	void hyunjeongUpdate();
	void yoonghoUpdate();
	void younghanUpdate();

	// ��0���ϸ� �������θ���� �׾��µ� �����������̻��̸� ����
	void deadErase();

	void createZergling(BELONG belong, float x, float y);
	void createCivilian(BELONG belong, float x, float y);

	void setLinkSm(stageManager* sm) { _sm = sm; }			//�������� �Ŵ����� ��ũ������ �׷��� Ÿ���� �Ӽ��� üũ������
};

