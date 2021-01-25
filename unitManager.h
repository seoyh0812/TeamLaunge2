#pragma once
#include "gameNode.h"
#include "zergling.h"
#include "civilian.h"
#include <vector>

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

	void chanhoUpdate();
	void deokhoUpdate();
	void hyunjeongUpdate();
	void yoonghoUpdate();
	void younghanUpdate();

	// ��0���ϸ� �������θ���� �׾��µ� �����������̻��̸� ����
	void deadErase();

	void createZergling(BELONG belong, float x, float y);
	void createCivilian(BELONG belong, float x, float y);
};

