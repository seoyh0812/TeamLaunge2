#pragma once
#include "unit.h"

enum ATTACK_PHASE
{
	SUMMON,
	EARTHQUAKE,
	FIREBALL
};

class diablo :
	public unit
{

private:

	ATTACK_PHASE _attackPhase;
	RECT _summonRc; // ��ȯ���� ��Ʈ
	//bool _isAttack; // ��ȯ �ߴ��� ���ߴ��� 
	//int _isAttackCount; // ���ݽ��� ī��Ʈ �Դϴ�.

public:
	diablo();
	~diablo();

	virtual HRESULT init(BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	virtual void reRender();

	virtual void setState(STATE state);
//	virtual void getAttackPhase(ATTACK_PHASE _attckPhase, STATE state);
};
