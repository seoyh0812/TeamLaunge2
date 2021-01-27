#include "stdafx.h"
#include "interaction.h"

void interaction::yoonghoInit()
{
}

void interaction::yoonghoUpdate()
{
	for (int i = 0; i < _se->getVSne().size(); ++i)
	{ // ���̿��н���
		if (_se->getVSne()[i]->getID() != 1) continue;
		for (int j = 0; j < _um->getVUnit().size(); ++j)
		{
			if (_um->getVUnit()[j]->getState() == DEAD) continue;
			if (_um->getVUnit()[j]->getBelong() == _se->getVSne()[i]->getBelong()) continue;
			RECT temp; // �Ǿƽĺ��� �ϴ� ���̿��н�������.. �̳ѹ��� �ٸ����� 0,1�� ���ϹǷ� �񱳰����ϴ�
			if (IntersectRect(&temp, &_um->getVUnit()[j]->getRect(), &_se->getVSne()[i]->getRect()))
			{
				_um->getVUnit()[j]->getHP() -= 0.2f;
			}
		}
	}



	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{ // Ÿ���ִ³�
		int tg = _um->getVUnit()[i]->getTarget();
		if (tg == -1) continue; // Ÿ�پ��³��� ��Ƽ��
		RECT temp;
		if (_um->getVUnit()[tg]->getState() == DEAD)
		{
			_um->getVUnit()[i]->getTarget() = -1; // Ÿ���� �������̸� Ǯ����
			continue;
		}
		if (_um->getVUnit()[i]->getAttackReady())
		{ // Ÿ���� �ִ� ���¿��� �����غ�Ǹ�
			if (_um->getVUnit()[i]->getID() == 3)
			{ // �ù��̸� ��׷β�(Ÿ���� ��������)
				for (int j = 0; j < _um->getVUnit().size(); ++j)
				{
					if (IntersectRect(&temp, &_um->getVUnit()[i]->getFocusRect(), &_um->getVUnit()[j]->getRect())
						&& _um->getVUnit()[j]->getState() != DEAD 
						&& _um->getVUnit()[i]->getBelong() != _um->getVUnit()[j]->getBelong())
					{
						_um->getVUnit()[j]->getTarget() = i;
					}
				}
			}
			else if (_um->getVUnit()[i]->getID() == 4)
			{ // ���÷��� ������ ������
				if (_um->getVUnit()[i]->getBelong() == PLAYER)
				{
					_se->createPsionic(S_PLAYER, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
				}
				if (_um->getVUnit()[i]->getBelong() == ENEMY)
				{
					_se->createPsionic(S_ENEMY, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
				}
			}
			_um->getVUnit()[i]->getAttackReady() = false;
			_um->getVUnit()[tg]->getHP() -= _um->getVUnit()[i]->getDamage();
		}
		else if (IntersectRect(&temp, &_um->getVUnit()[tg]->getRect(), &_um->getVUnit()[i]->getRangeRect())
			&& _um->getVUnit()[i]->getState() != ATTACK)
		{
			_um->getVUnit()[i]->setState(ATTACKWAIT);
		}
		else if (!IntersectRect(&temp, &_um->getVUnit()[tg]->getRect(), &_um->getVUnit()[i]->getRangeRect())
			&& _um->getVUnit()[i]->getState() == ATTACKWAIT) // ���ݴ���߿��� Ÿ���� ��Ÿ� ����� ����
		{
			_um->getVUnit()[i]->setState(WALK);
		}
		if (_um->getVUnit()[i]->getState() == WALK)
		{ // Ÿ�������� ��ũ�� ��븦 ��ǥ�� �Ѵ�
			_um->getVUnit()[i]->setDest(_um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
		}
	}

}

void interaction::yoonghoRender()
{
}