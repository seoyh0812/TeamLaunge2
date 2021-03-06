#include "stdafx.h"
#include "interaction.h"

void interaction::yoonghoInit()
{
}

void interaction::yoonghoUpdate()
{
	for (int i = 0; i < _se->getVSne().size(); ++i)
	{ // 사이오닉스톰
		if (_se->getVSne()[i]->getID() == 1)
		{
			for (int j = 0; j < _um->getVUnit().size(); ++j)
			{
				if (_um->getVUnit()[j]->getState() == DEAD) continue;
				if (_um->getVUnit()[j]->getBelong() == _se->getVSne()[i]->getBelong()) continue;
				RECT temp; // 피아식별을 하는 사이오닉스톰으로.. 이넘문은 다르지만 0,1로 비교하므로 비교가능하다
				if (IntersectRect(&temp, &_um->getVUnit()[j]->getRect(), &_se->getVSne()[i]->getRect()))
				{
					_um->getVUnit()[j]->getHP() -= 0.1f;
				}
			}
		}		
		else if (_se->getVSne()[i]->getID() == 2)
		{

			for (int j = 0; j < _um->getVUnit().size(); ++j)
			{ // 힐
				if (_um->getVUnit()[j]->getState() == DEAD) continue;
				if (_um->getVUnit()[j]->getBelong() == _se->getVSne()[i]->getBelong()) continue;
				RECT temp;
				if (IntersectRect(&temp, &_um->getVUnit()[j]->getRect(), &_se->getVSne()[i]->getRect()))
				{
					_um->getVUnit()[j]->getHP() += 0.065f;					
				}
			}
		}
		else if (_se->getVSne()[i]->getID() == 3)
		{ // 번개 닿으면 데미지
			for (int j = 0; j < _um->getVUnit().size(); ++j)
			{
				if (_um->getVUnit()[j]->getState() == DEAD) continue;
				if (_um->getVUnit()[j]->getBelong() == _se->getVSne()[i]->getBelong()) continue;
				RECT temp; // 피아식별을 하는 사이오닉스톰으로.. 이넘문은 다르지만 0,1로 비교하므로 비교가능하다
				if (IntersectRect(&temp, &_um->getVUnit()[j]->getRect(), &_se->getVSne()[i]->getRect()))
				{
					_um->getVUnit()[j]->getHP() -= 0.75f;
				}
			}
		}
		else if (_se->getVSne()[i]->getID() == 4)
		{ // 불 닿으면 데미지
			for (int j = 0; j < _um->getVUnit().size(); ++j)
			{
				if (_um->getVUnit()[j]->getState() == DEAD) continue;
				if (_um->getVUnit()[j]->getBelong() == _se->getVSne()[i]->getBelong()) continue;
				RECT temp;
				if (IntersectRect(&temp, &_um->getVUnit()[j]->getRect(), &_se->getVSne()[i]->getRect()))
				{
					_um->getVUnit()[j]->getHP() -= 0.125f;
				}
			}
		}
		else if (_se->getVSne()[i]->getID() == 5)
        { // 나선환 닿으면 데미지
            for (int j = 0; j < _um->getVUnit().size(); ++j)
            {
                if (_um->getVUnit()[j]->getState() == DEAD) continue;
                if (_um->getVUnit()[j]->getBelong() == _se->getVSne()[i]->getBelong()) continue;
                RECT temp;
                if (IntersectRect(&temp, &_um->getVUnit()[j]->getRect(), &_se->getVSne()[i]->getRect()))
                {
                    _um->getVUnit()[j]->getHP() -= 0.25f;
                }
            }
        }
	}

	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{ // 타겟있는놈만
		int tg = _um->getVUnit()[i]->getTarget();
		if (tg == -1 || _um->getVUnit()[i]->getStuck() < 0) continue; // 타겟없는놈은 컨티뉴
		RECT temp;
		if (_um->getVUnit()[tg]->getState() == DEAD)
		{
			_um->getVUnit()[i]->getTarget() = -1; // 타겟이 죽은놈이면 풀어줌
			continue;
		}
		if (_um->getVUnit()[i]->getAttackReady())
		{ // 타겟이 있는 상태에서 공격준비되면
			if (_um->getVUnit()[i]->getID() == 3)
			{ // 시민이면 어그로끔(타겟을 내쪽으로)
				_um->getVUnit()[tg]->getTarget() = i;
			}
			else if (_um->getVUnit()[i]->getID() == 4)
			{ // 템플러면 스톰을 생성함
				if (_um->getVUnit()[i]->getBelong() == PLAYER)
				{
					_se->createPsionic(S_PLAYER, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
				}
				if (_um->getVUnit()[i]->getBelong() == ENEMY)
				{
					_se->createPsionic(S_ENEMY, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
				}
			}
			else if (_um->getVUnit()[i]->getID() == 5)
			{ // 비숍이면 힐장판 생성
				if (_um->getVUnit()[i]->getBelong() == PLAYER)
				{ 
					_se->createHeal(S_ENEMY, _um->getVUnit()[i]->getX(), _um->getVUnit()[i]->getY());
				}
				if (_um->getVUnit()[i]->getBelong() == ENEMY)
				{
					_se->createHeal(S_PLAYER, _um->getVUnit()[i]->getX(), _um->getVUnit()[i]->getY());
				}
			}
			else if (_um->getVUnit()[i]->getID() == 6)
			{ // 디아블로면 해골생성 
				if (_um->getVUnit()[i]->getBelong() == ENEMY)
				{
					_um->createSkeleton(ENEMY,
						_um->getVUnit()[i]->getX() + 200 * cosf(_um->getVUnit()[i]->getAngle1()),
						_um->getVUnit()[i]->getY() - 200 * sinf(_um->getVUnit()[i]->getAngle1()));
					_um->getVUnit()[_um->getVUnit().size() - 1]->getActive() = true;
					_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = _sm->getPlayerTile();
					_um->createSkeleton(ENEMY,
						_um->getVUnit()[i]->getX() - 100 + 200 * cosf(_um->getVUnit()[i]->getAngle1()),
						_um->getVUnit()[i]->getY() - 200 * sinf(_um->getVUnit()[i]->getAngle1()));
					_um->getVUnit()[_um->getVUnit().size() - 1]->getActive() = true;
					_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() = _sm->getPlayerTile();
					_um->createSkeleton(ENEMY,
						_um->getVUnit()[i]->getX() + 100 + 200 * cosf(_um->getVUnit()[i]->getAngle1()),
						_um->getVUnit()[i]->getY() - 200 * sinf(_um->getVUnit()[i]->getAngle1()));
					_um->getVUnit()[_um->getVUnit().size() - 1]->getActive() = true;
					_um->getVUnit()[_um->getVUnit().size() - 1]->getTileNum() =_sm->getPlayerTile();
					_um->getVUnit()[i]->getID() = 21; // 디아블로 페이즈2
				}
			}
			else if (_um->getVUnit()[i]->getID() == 21)
			{ // 디아블로페이즈2면 번개생성
				if (_um->getVUnit()[i]->getBelong() == ENEMY)
				{
					PLAYSND("번개");
					_um->getVUnit()[i]->getID() = 6; // 해골소환페이즈로
					_se->createThunder(S_ENEMY, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY() - 100);
					_se->createThunder(S_ENEMY, _um->getVUnit()[tg]->getX() + rand() % 200 , _um->getVUnit()[tg]->getY() + rand() % 200 - 100);
					_se->createThunder(S_ENEMY, _um->getVUnit()[tg]->getX() + rand() % 200, _um->getVUnit()[tg]->getY() - rand() % 200 - 100);
					_se->createThunder(S_ENEMY, _um->getVUnit()[tg]->getX() - rand() % 200, _um->getVUnit()[tg]->getY() - rand() % 200 - 100);
					_se->createThunder(S_ENEMY, _um->getVUnit()[tg]->getX() - rand() % 200, _um->getVUnit()[tg]->getY() + rand() % 200 - 100);
				}
			}
			else if (_um->getVUnit()[i]->getID() == 8)
			{ // 고스트 펑
				_se->createGhostffect(S_PLAYER, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
			}
            else if (_um->getVUnit()[i]->getID() == 9)
            {   // 브레스
                if (_um->getVUnit()[i]->getBelong() == PLAYER)
                {
                    _se->createfire(S_PLAYER, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
                }
                if (_um->getVUnit()[i]->getBelong() == ENEMY)
                {
                    _se->createfire(S_ENEMY, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
                }
            }
            else if (_um->getVUnit()[i]->getID() == 10)
            {   // 나선환
                if (_um->getVUnit()[i]->getBelong() == PLAYER)
                {
                    _se->createNEffect(S_PLAYER, _um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
                }
            }

			_um->getVUnit()[i]->getAttackReady() = false;
			if (_um->getVUnit()[i]->getID() != 5) // 힐장판이 아니면 데미지
			{
				_um->getVUnit()[tg]->getHP() -= _um->getVUnit()[i]->getDamage();
			}
			else if (_um->getVUnit()[i]->getID() == 5) // 힐장판이면 HP 회복하는 것으로 변경
			{
				_um->getVUnit()[i]->getHP() += _um->getVUnit()[i]->getDamage();
			}
			
		}
		else if (IntersectRect(&temp, &_um->getVUnit()[tg]->getRect(), &_um->getVUnit()[i]->getRangeRect())
			&& _um->getVUnit()[i]->getState() != ATTACK)
		{
			_um->getVUnit()[i]->setState(ATTACKWAIT);
		}
		else if (!IntersectRect(&temp, &_um->getVUnit()[tg]->getRect(), &_um->getVUnit()[i]->getRangeRect())
			&& _um->getVUnit()[i]->getState() == ATTACKWAIT && _um->getVUnit()[i]->getStuck() >= 0) // 공격대기중에서 타겟이 사거리 벗어나면 추적
		{
			_um->getVUnit()[i]->setState(WALK);
		}
		if (_um->getVUnit()[i]->getState() == WALK && _um->getVUnit()[i]->getStuck() >= 0)
		{ // 타겟있을떄 워크는 상대를 목표로 한다
			_um->getVUnit()[i]->setDest(_um->getVUnit()[tg]->getX(), _um->getVUnit()[tg]->getY());
		}
	}

	
	// 유닛이 맵충돌
	for (int i = 0; i < _um->getVUnit().size(); ++i)
	{
		if (_um->getVUnit()[i]->getState() != WALK || _um->getVUnit()[i]->getID() == 6 || _um->getVUnit()[i]->getID() == 21
			|| _um->getVUnit()[i]->getStuck() < 0) continue;
		POINT tempPtL = picking(_um->getVUnit()[i]->getRect().left, _um->getVUnit()[i]->getY());
		if (_sm->getIsoTile()[tempPtL.x + tempPtL.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() += _um->getVUnit()[i]->getSpeed();
			_um->getVUnit()[i]->RMC();
			_um->getVUnit()[i]->getStuck() += 1;
			continue;
		}
		POINT tempPtR = picking(_um->getVUnit()[i]->getRect().right, _um->getVUnit()[i]->getY());
		if (_sm->getIsoTile()[tempPtR.x + tempPtR.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getX() -= _um->getVUnit()[i]->getSpeed();
			_um->getVUnit()[i]->RMC();
			_um->getVUnit()[i]->getStuck() += 1;
			continue;
		}
		POINT tempPtB = picking(_um->getVUnit()[i]->getX(), _um->getVUnit()[i]->getRect().bottom);
		if (_sm->getIsoTile()[tempPtB.x + tempPtB.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getY() -= _um->getVUnit()[i]->getSpeed();
			_um->getVUnit()[i]->RMC();
			_um->getVUnit()[i]->getStuck() += 1;
			continue;
		}
		POINT tempPtT = picking(_um->getVUnit()[i]->getX(), _um->getVUnit()[i]->getRect().top);
		if (_sm->getIsoTile()[tempPtT.x + tempPtT.y * 30].MUM == UNMOVE)
		{
			_um->getVUnit()[i]->moveCancel();
			_um->getVUnit()[i]->getY() += _um->getVUnit()[i]->getSpeed();
			_um->getVUnit()[i]->RMC();
			_um->getVUnit()[i]->getStuck() += 1;
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
	{ // 도달시 다음으로 넘겨주는 함수
		if (_um->getVUnit()[i]->getState() != WALK || _um->getVUnit()[i]->getTarget() != -1) continue;
		int tempTileNum = _um->getVUnit()[i]->getTileNum();
		_um->getVUnit()[i]->setDest(_sm->getIsoTile()[tempTileNum].centerX, _sm->getIsoTile()[tempTileNum].centerY);
		RECT tempRc;
		RECT temp1 = RectMakeCenter(_um->getVUnit()[i]->getX(),
			_um->getVUnit()[i]->getY(), 4, 4);
		RECT temp2 = RectMakeCenter(_sm->getIsoTile()[tempTileNum].centerX,
			_sm->getIsoTile()[tempTileNum].centerY, 4, 4);
		if (IntersectRect(&tempRc, &temp1, &temp2))
		{	// 뒷번호부터 하는게 검사 덜함		
			for (int j = _um->getVUnit()[i]->getVPath().size()-1; j>=0; --j)
			{	//상하좌우 먼저검사함
				if (_um->getVUnit()[i]->getVPath()[j] == tempTileNum + 1
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 1
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum + 30
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 30)
				{
					tempTileNum = _um->getVUnit()[i]->getVPath()[j];
					_um->getVUnit()[i]->getTileNum() = tempTileNum;
					_um->getVUnit()[i]->eraseVPath(j);
					break;
				}//대각선 검사함
				else if (_um->getVUnit()[i]->getVPath()[j] == tempTileNum + 29
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum + 31
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 29
					|| _um->getVUnit()[i]->getVPath()[j] == tempTileNum - 31)
				{
					tempTileNum = _um->getVUnit()[i]->getVPath()[j];
					_um->getVUnit()[i]->getTileNum() = tempTileNum;
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
	if (2 * y < (x - 960))	return { -1,0 }; // y=1/2x보다 위에있는지 (맵밖 벗어남)
	if (2 * y < -(x - 960))	return { -1,0 }; // y=-1/2x보다 위에있는지 (맵밖 벗어남)
	xx = (2 * y + (x - 960)) / 64;
	if (xx > 29) return { -1,0 }; // 맵밖 벗어난거면 예외처리

	yy = (2 * y - (x - 960)) / 64;
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}
