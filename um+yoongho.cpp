#include "stdafx.h"
#include "unitManager.h"

void unitManager::yoonghoUpdate()
{
	for (int i = 0; i < _vUnit.size(); ++i)
	{
		if (_vUnit[i]->getState() == DEAD) continue;
		RECT temp;

		// �������� ���߽߰� Ÿ����
		for (int j = 0; j < _vUnit.size(); ++j)
		{
			if (_vUnit[i]->getTarget() != -1 || _vUnit[j]->getState() == DEAD ||
				_vUnit[i]->getStuck() < 0) continue;
			if (_vUnit[i]->getBelong() == _vUnit[j]->getBelong()) continue; // ���Ʊ�����
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getFocusRect()) && _vUnit[i]->getStuck() >= 0
				&& _vUnit[i]->getTarget() == -1)
			{ // ������Ʈ�� �� ��� Ÿ�����̶� ��ǥ�� ��������
				_vUnit[i]->getTarget() = j;
				_vUnit[i]->setDest(_vUnit[j]->getX(), _vUnit[j]->getY());
				break;
			}
		}

		// ���ְ����� ��Ʈ�浹
		for (int j = 0; j < _vUnit.size(); ++j)
		{ // �����ִ¾ִ� ����ġ ã�������� �浹���� ������ ��Ƽ���س���
			if (_vUnit[i]->getState() != WALK || _vUnit[j]->getState() == DEAD || i==j
				|| _vUnit[i]->getStuck() < 0 || _vUnit[j]->getStuck() < 0) continue;
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getRect()))
			{ // �׳� ��Ʈ�� �浹
				if (_vUnit[i]->getBelong() != _vUnit[j]->getBelong())
				{ // �ҼӴٸ��� ��������ϸ� ���� �ο������.
					_vUnit[i]->getTarget() = j;
					_vUnit[j]->getTarget() = i;
				}				
				_vUnit[i]->moveCancel();
				_vUnit[i]->RMC();
				if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getRect()))
				{ // �̵�����ص� ������ ���ͼ�Ʈ�Ѵٸ� (j�� ����ؾ���)
					_vUnit[i]->getX() += _vUnit[i]->getSpeed() * cosf(_vUnit[i]->getAngle1());
					_vUnit[i]->getY() -= _vUnit[i]->getSpeed() * sinf(_vUnit[i]->getAngle1());
					_vUnit[i]->RMC();
					_vUnit[j]->moveCancel();
					_vUnit[j]->RMC();
				}
				if (_vUnit[i]->getBelong() == _vUnit[j]->getBelong())
				{ // �������� �и� ���� ����������� �� �и��� �غ���
					_vUnit[j]->getStuck() += 1;
				}
				break;
			}
		}
	}
}

