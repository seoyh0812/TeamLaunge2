#pragma once
#include "gameNode.h"
#include "stageManager.h"
#include "unitManager.h"
#include "skillNEffectManager.h"
#include <vector>

struct tagAStarTile
{
	int tileNum;
	int parentNodeTileNum;
	int totalCost;
	int costFromStart;
	int costToGoal;
	bool isOpen;
};

class interaction :	public gameNode
{
private:
	stageManager*			_sm;
	unitManager*			_um;
	skillNEffectManager*	_se;

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
	
public:
	interaction();
	~interaction();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void chanhoInit();		void chanhoUpdate();	void chanhoRender();
	void deokhoInit();		void deokhoUpdate();	void deokhoRender();
	void hyunjeongInit();	void hyunjeongUpdate();	void hyunjeongRender();
	void yoonghoInit();		void yoonghoUpdate();	void yoonghoRender();
	void younghanInit();	void younghanUpdate();	void younghanRender();
	
	void smLink(stageManager* sm) { _sm = sm; }
	void umLink(unitManager* um) { _um = um; }
	void seLink(skillNEffectManager* se) { _se = se; }

	inline POINT picking(long x, long y);

	vector<int> aStarPath(int fromTileNum, int toTileNum);

	//���� �ִ� ���� ã�Ƴ��� ����� �Լ�
	vector<tagAStarTile*> addOpenList(int currentTile);
	//���� ��� ã�� �Լ�
	void pathFinder(int currentTile);
};

