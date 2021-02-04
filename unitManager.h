#pragma once
#include "gameNode.h"
#include "zergling.h"
#include "civilian.h"
#include "marine.h"
#include "templar.h"
#include "bishop.h"
#include "ghost.h"
#include "diablo.h"
#include "skeleton.h"
#include "flagUnit.h"
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

	vector<unit*> &getVUnit() { return _vUnit; }
	vector<unit*>::iterator &getViUnit() { return _viUnit; }

	void reRender();

	void chanhoUpdate();
	void deokhoUpdate();
	void hyunjeongUpdate();
	void yoonghoUpdate();
	void younghanUpdate();

	// ��0���ϸ� �������θ���� �׾��µ� �����������̻��̸� ����
	void deadErase();
	void progressBarRender();

	void setActive();

	void createZergling(BELONG belong, float x, float y);
	void createCivilian(BELONG belong, float x, float y);
	void createMarine(BELONG belong, float x, float y);
	void createTemplar(BELONG belong, float x, float y);
	void createBishop(BELONG belong, float x, float y);
	void createGhost(BELONG belong, float x, float y);
	void createDiablo(BELONG belong, float x, float y);
	void createskeleton(BELONG belong, float x, float y);
	void createSkeleton(BELONG belong, float x, float y);
	void createFlag(BELONG belong, float x, float y);
};

