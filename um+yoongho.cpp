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
		{
			if (_vUnit[i]->getState() != WALK || _vUnit[j]->getState() == DEAD || i==j) continue;
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getRect()))
			{ // �׳� ��Ʈ�� �浹
				if (_vUnit[i]->getBelong() != _vUnit[j]->getBelong())
				{ // �ҼӴٸ��� ��������ϸ� ���� �ο������.
					_vUnit[i]->getTarget() = j;
					_vUnit[j]->getTarget() = i;
				}
				int width = (temp.right - temp.left);
				int height = (temp.bottom - temp.top);
				if (width > height)
				{ // ���Ʒ��� �ε��� �����
					if (_vUnit[i]->getY() < _vUnit[j]->getY())
					{
						_vUnit[i]->getY() -= height;
					}
					else if(_vUnit[i]->getY() > _vUnit[j]->getY())
					{
						_vUnit[i]->getY() += height;
					}
				}
				else if (width < height)
				{
					if (_vUnit[i]->getX() < _vUnit[j]->getX())
					{
						_vUnit[i]->getX() -= width;
					}
					else if(_vUnit[i]->getX() > _vUnit[j]->getX())
					{
						_vUnit[i]->getX() += width;
					}
				}
				_vUnit[i]->RMC();
				if (_vUnit[i]->getBelong() == _vUnit[j]->getBelong())
				{ // �������� �и� ���� ����������� �� �и��� �غ���
					_vUnit[j]->getStuck() += 1;
				}
			}
		}
	}
}

