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
				_um->getVUnit()[j]->getHP() -= 0.1f;
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
				_um->getVUnit()[tg]->getTarget() = i;
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

	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{
		if (_um->getVUnit()[i]->getState() != WALK) continue;
		POINT tempPtLT = picking(_um->getVUnit()[i]->getRect().left, _um->getVUnit()[i]->getRect().top);
		if (_sm->getIsoTile()[tempPtLT.x + tempPtLT.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() += _um->getVUnit()[i]->getSpeed();
			continue;
		}
		POINT tempPtRT = picking(_um->getVUnit()[i]->getRect().right, _um->getVUnit()[i]->getRect().top);
		if (_sm->getIsoTile()[tempPtRT.x + tempPtRT.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() -= _um->getVUnit()[i]->getSpeed();
			continue;
		}
		POINT tempPtLB = picking(_um->getVUnit()[i]->getRect().left, _um->getVUnit()[i]->getRect().bottom);
		if (_sm->getIsoTile()[tempPtLB.x + tempPtLB.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() += _um->getVUnit()[i]->getSpeed();
			continue;
		}
		POINT tempPtRB = picking(_um->getVUnit()[i]->getRect().right, _um->getVUnit()[i]->getRect().bottom);
		if (_sm->getIsoTile()[tempPtRB.x + tempPtRB.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() -= _um->getVUnit()[i]->getSpeed();
			continue;
		}
	}

	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{
		if (_um->getVUnit()[i]->getState() != WALK || _um->getVUnit()[i]->getTarget() != -1
			|| !_um->getVUnit()[i]->getReturn()) continue;
		_um->getVUnit()[i]->setDest(_sm->getIsoTile()[_um->getVUnit()[i]->getTileNum()].centerX,
			_sm->getIsoTile()[_um->getVUnit()[i]->getTileNum()].centerY);
		_um->getVUnit()[i]->getReturn() = false;
	}


	for (int i = 0; i < _um->getVUnit().size();++i)
	{ // ���޽� �������� �Ѱ��ִ� �Լ�
		if (_um->getVUnit()[i]->getState() != WALK || _um->getVUnit()[i]->getTarget() != -1) continue;
		int tempTileNum = _um->getVUnit()[i]->getTileNum();
		RECT tempRc;
		RECT temp1 = RectMakeCenter(_um->getVUnit()[i]->getX(),
			_um->getVUnit()[i]->getY(), 4, 4);
		RECT temp2 = RectMakeCenter(_sm->getIsoTile()[tempTileNum].centerX,
			_sm->getIsoTile()[tempTileNum].centerY, 4, 4);
		if (IntersectRect(&tempRc, &temp1, &temp2))
		{	// �޹�ȣ���� �ϴ°� �˻� ����		
			for (int j = _um->getVUnit()[i]->getVPath().size()-1; j>=0; --j)
			{	//�����¿� �����˻���
				if (_um->getVUnit()[i]->getVPath()[j] == tempTileNum + 1
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 1
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum + 30
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 30)
				{
					tempTileNum = _um->getVUnit()[i]->getVPath()[j];
					_um->getVUnit()[i]->getTileNum() = tempTileNum;
					_um->getVUnit()[i]->setDest(_sm->getIsoTile()[tempTileNum].centerX, _sm->getIsoTile()[tempTileNum].centerY);
					_um->getVUnit()[i]->eraseVPath(j);
					break;
				}//�밢�� �˻���
				else if (_um->getVUnit()[i]->getVPath()[j] == tempTileNum + 29
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum + 31
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 29
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 31)
				{
					tempTileNum = _um->getVUnit()[i]->getVPath()[j];
					_um->getVUnit()[i]->getTileNum() = tempTileNum;
					_um->getVUnit()[i]->setDest(_sm->getIsoTile()[tempTileNum].centerX, _sm->getIsoTile()[tempTileNum].centerY);
					_um->getVUnit()[i]->eraseVPath(j);
					break;
				}
			}
		}
	}

}

void interaction::yoonghoRender()
{
}



inline POINT interaction::picking(long x, long y)
{
	int xx; int yy;
	if (2 * y < (x - 960))	return { -1,0 }; // y=1/2x���� �����ִ��� (�ʹ� ���)
	if (2 * y < -(x - 960))	return { -1,0 }; // y=-1/2x���� �����ִ��� (�ʹ� ���)
	xx = (2 * y + (x - 960)) / 64;
	if (xx > 29) return { -1,0 }; // �ʹ� ����Ÿ� ����ó��

	yy = (2 * y - (x - 960)) / 64;
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}
