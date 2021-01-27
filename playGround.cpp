#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	_x = _y = 0;
	_backGround = IMAGEMANAGER->addImage("���", "image/backGround.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("���ξ�", new mainScene);
	SCENEMANAGER->addScene("����", new mapTool);
	SCENEMANAGER->addScene("Ÿ��Ʋ��", new titleScene);
	SCENEMANAGER->addScene("������", new endingScene);

	SCENEMANAGER->changeScene("�ε���");

	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_ADD) && _x < 300)
	{
		_x += 12;
		_y += 7;
	}
	if (KEYMANAGER->isStayKeyDown(VK_SUBTRACT) && _x > 0)
	{
		_x -= 12;
		_y -= 7;
	}

	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, CAMX + WINSIZEX, CAMY + WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	_backGround->render(getMemDC(), CAMX, CAMY);
	SCENEMANAGER->render();
	if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getMemDC(), CAMX, CAMY);
	//================= �Ʒ��� �ǵ��� ���� ==============================
	if (_x == 0) _backBuffer->render(getHDC(), 0, 0, CAMX, CAMY, WINSIZEX, WINSIZEY);
	else _backBuffer->resizedRender(getHDC(), 0, 0, CAMX + _x, CAMY + _y, WINSIZEX, WINSIZEY, WINSIZEX - 2 * _x, WINSIZEY - 2 * _y);
}