#pragma once
#include "gameNode.h"
#include <vector>
#include "flague.h"
#include "psionic.h"
#include "heal.h"

class skillNEffectManager :	public gameNode
{
private:
	vector<skillNEffect*> _vSne;
	vector<skillNEffect*>::iterator _viSne;

public:
	skillNEffectManager();
	~skillNEffectManager();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void createPsionic(S_BELONG belong, float x, float y);
	void createPlague(S_BELONG belong, float x, float y);
	void createHeal(S_BELONG belong, float x, float y);

	vector<skillNEffect*> getVSne() { return _vSne; }
	vector<skillNEffect*>::iterator getViSne() { return _viSne; }
};

