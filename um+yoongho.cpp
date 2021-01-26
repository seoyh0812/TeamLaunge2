#include "stdafx.h"
#include "unitManager.h"

void unitManager::yoonghoUpdate()
{
	for (int i = 0; i < _vUnit.size(); ++i)
	{
		if (_vUnit[i]->getState() == DEAD) continue;
		RECT temp;
		for (int j = 0; j < _vUnit.size(); ++j)
		{// Ÿ�����ϴ� ����(Ÿ�� ���³� ���)
			if (_vUnit[i]->getTarget() != -1 || _vUnit[j]->getState() == DEAD) continue;
			if (_vUnit[i]->getBelong() == _vUnit[j]->getBelong()) continue; // ���Ʊ�����
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getFocusRect()) &&
				_vUnit[i]->getTarget() == -1)
			{ // ������Ʈ�� �� ��� Ÿ�����̶� ��ǥ�� ��������
				_vUnit[i]->getTarget() = j;
				_vUnit[i]->setDest(_vUnit[j]->getX(), _vUnit[j]->getY());
				break;
			}
		}
	}
}

