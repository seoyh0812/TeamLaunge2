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

		// ���ְ����� ��Ʈ�浹
		if (_vUnit[i]->getID() == 1 || _vUnit[i]->getID() == 3) continue; // �ϴ� �������ְ� �浹�� ���Ƶ�
		for (int j = 0; j < _vUnit.size(); ++j)
		{// Ÿ�����ϴ� ����(Ÿ�� ���³� ���)
			if (_vUnit[j]->getState() == DEAD) continue;
			if (IntersectRect(&temp, &_vUnit[j]->getRect(), &_vUnit[i]->getRect()))
			{ // �׳� ��Ʈ�� �浹
				if (_vUnit[i]->getBelong() != _vUnit[j]->getBelong())
				{ // �ҼӴٸ��� ��������ϸ� ���� �ο������.
					_vUnit[i]->getTarget() = j;
					_vUnit[j]->getTarget() = i;
				}
				int widthHalf = (temp.right - temp.left)/2;
				int heightHalf = (temp.bottom - temp.top)/2;
				if (widthHalf > heightHalf)
				{ // ���Ʒ��� �ε��� �����
					if (_vUnit[i]->getY() < _vUnit[j]->getY())
					{
						_vUnit[i]->getY() -= heightHalf;
						_vUnit[j]->getY() += heightHalf;
					} // ���� �ݾ� �̴°ɷ� �غ�
					else if(_vUnit[i]->getY() > _vUnit[j]->getY())
					{
						_vUnit[i]->getY() += heightHalf;
						_vUnit[j]->getY() -= heightHalf;
					}
				}
				else if (widthHalf < heightHalf)
				{
					if (_vUnit[i]->getX() < _vUnit[j]->getX())
					{
						_vUnit[i]->getX() -= widthHalf;
						_vUnit[j]->getX() += widthHalf;
					}
					else if(_vUnit[i]->getX() > _vUnit[j]->getX())
					{
						_vUnit[i]->getX() += widthHalf;
						_vUnit[j]->getX() -= widthHalf;
					}
				}
				_vUnit[i]->RMC();
				_vUnit[j]->RMC();
			}
		}
	}
}

