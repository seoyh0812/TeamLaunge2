#include "stdafx.h"
#include "unitManager.h"

void unitManager::yoonghoUpdate()
{
	for (int i = 0; i < _vUnit.size(); ++i)
	{
		if (_vUnit[i]->getState() == DEAD) continue;
		RECT temp;
		for (int j = 0; j < _vUnit.size(); ++j)
		{// Ÿ�����ϴ°�
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

	for (int i = 0; i < _vUnit.size(); ++i)
	{ // Ÿ���ִ³�
		int tg = _vUnit[i]->getTarget();
		if (tg == -1) continue;
		RECT temp;
		if (_vUnit[tg]->getState() == DEAD)
		{
			_vUnit[i]->getTarget() = -1;
			continue;
		}
		if (_vUnit[i]->getAttackReady())
		{
			if (_vUnit[i]->getID() == 3)
			{ // �ù��̸� ��׷β�
				for (int j = 0; j < _vUnit.size(); ++j)
				{
					if (IntersectRect(&temp, &_vUnit[i]->getFocusRect(), &_vUnit[j]->getRect())
						&& _vUnit[j]->getState() != DEAD && _vUnit[i]->getBelong() != _vUnit[j]->getBelong())
					{
						_vUnit[j]->getTarget() = i;
					}
				}
			}
			_vUnit[i]->getAttackReady() = false;
			_vUnit[tg]->getHP() -= _vUnit[i]->getDamage();
		}
		else if (IntersectRect(&temp, &_vUnit[tg]->getRect(), &_vUnit[i]->getRangeRect())
			&& _vUnit[i]->getState() != ATTACK)
		{
			_vUnit[i]->setState(ATTACKWAIT);
		}
		else if (!IntersectRect(&temp, &_vUnit[tg]->getRect(), &_vUnit[i]->getRangeRect())
			&& _vUnit[i]->getState() == ATTACKWAIT)
		{
			_vUnit[i]->setState(WALK);
		}
		if (_vUnit[i]->getState() == WALK)
		{
			_vUnit[i]->setDest(_vUnit[tg]->getX(), _vUnit[tg]->getY());
		}
	}
}

