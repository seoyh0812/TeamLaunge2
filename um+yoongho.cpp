#include "stdafx.h"
#include "unitManager.h"

void unitManager::yoonghoUpdate()
{
	for (int i = 0; i < _vUnit.size(); ++i)
	{
		if (_vUnit[i]->getState() == DEAD) continue;
		RECT temp;
		for (int j = 0; j < _vUnit.size(); ++j)
		{// 타겟팅하는 포문(타겟 없는놈 대상)
			if (_vUnit[i]->getTarget() != -1 || _vUnit[j]->getState() == DEAD) continue;
			if (_vUnit[i]->getBelong() == _vUnit[j]->getBelong()) continue; // 적아군구분
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getFocusRect()) &&
				_vUnit[i]->getTarget() == -1)
			{ // 감지렉트에 온 경우 타겟팅이랑 목표를 그쪽으로
				_vUnit[i]->getTarget() = j;
				_vUnit[i]->setDest(_vUnit[j]->getX(), _vUnit[j]->getY());
				break;
			}
		}
	}
}

