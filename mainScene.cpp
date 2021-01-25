#include "stdafx.h"
#include "mainScene.h"

mainScene::mainScene()
{
}

mainScene::~mainScene()
{
}

HRESULT mainScene::init()
{
	_sm = new stageManager;
	_sm->init();
	_um = new unitManager;
	_um->init();
	_se = new skillNEffectManager;
	_se->init();
	_ia = new interaction;
	_ia->init();

	_ia->umLink(_um);
	_ia->smLink(_sm);
	_ia->seLink(_se);

	_um->createZergling(ENEMY, 300, 300);
	_se->createPsionic(S_PLAYER, 200, 200);
	SOUNDMANAGER->play("사운드추가예시");

	_indexX = _indexY = _count = 0;
	_destX = _destY = _x = _y = 200.f;
	_zerling = RectMakeCenter(_x, _y, 39, 40);
	_destRc = RectMakeCenter(_destX, _destY, 2, 2);
	return S_OK;
}

void mainScene::release()
{
	_sm->release();
	_um->release();
	_se->release();
	_ia->release();
}

void mainScene::update()
{
	_sm->update();
	_um->update();
	_se->update();
	_ia->update();

	if (_count < 6) ++_count;
	else
	{
		_count = 0;
		++_indexY;
		if (_indexY > 6) _indexY = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < _um->getVUnit().size(); ++i)
		{
			_um->getVUnit()[i]->setState(DEAD);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		_destX = _ptMouse.x;
		_destY = _ptMouse.y;
		_angle = getAngle(_x, _y, _destX, _destY);
		if (_angle < 0) _angle += PI2;
		_indexX = (int)((_angle + PI8) / PI4);
		_indexX = 2 -_indexX;
		if (_indexX < 0) _indexX += 8;
		_destRc = RectMakeCenter(_destX, _destY, 5, 5);
	}
	RECT temp;
	if (!IntersectRect(&temp, &_destRc, &_zerling))
	{
		_x += 3 * cosf(_angle);
		_y -= 3 * sinf(_angle);
	}
	_zerling = RectMakeCenter(_x, _y, 39, 40);
}

void mainScene::render()
{
	_sm->render();
	_ia->render();
	_um->render();
	_se->render();

	
	FINDIMG("저글링이동블루")->frameRender(getMemDC(), _zerling.left, _zerling.top, _indexX, _indexY);

	uiRender();
}

