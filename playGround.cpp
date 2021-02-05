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

	_x = _y = _seeMinimap = 0;

	_ms = new mainScene;

	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("���ξ�", _ms);
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

	if (SCENEMANAGER->getMinimapScene() && !_seeMinimap)
	{
		_seeMinimap = true;
	}
	else if (!SCENEMANAGER->getMinimapScene() && _seeMinimap)
	{
		_seeMinimap = false;
	}

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
	if (!_seeMinimap && (CAMX != 0 || CAMY != 0))
	{
		CAMERAMANAGER->setCameraX(0);
		CAMERAMANAGER->setCameraY(0);
	}

	yoonghoUpdate();
	SCENEMANAGER->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, CAMX + WINSIZEX, CAMY + WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	SCENEMANAGER->render(); // ��� �� Ȯ�����..
	//================= �Ʒ��� �ǵ��� ���� ==============================
	if (_x == 0) // Ȯ����ϴ°Ÿ� �̷��� �׸�
	{
		if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getMemDC(), CAMX, CAMY);
		uiRender();
		if (SCENEMANAGER->getAlpha() > 0) FINDIMG("��ü����")->alphaRender(getMemDC(), CAMX, CAMY, SCENEMANAGER->getAlpha());
		_backBuffer->render(getHDC(), 0, 0, CAMX, CAMY, WINSIZEX, WINSIZEY);
	}
	else
	{ // Ȯ������ϰ� �׸��� ���̿� �����־ �׸��� �ɵ�
		_backBuffer->resizedRender(getMemDC(), CAMX, CAMY, CAMX + _x, CAMY + _y, WINSIZEX, WINSIZEY, WINSIZEX - 2 * _x, WINSIZEY - 2 * _y);
		if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getMemDC(), CAMX,CAMY);
		uiRender();
		if (SCENEMANAGER->getAlpha() > 0) FINDIMG("��ü����")->alphaRender(getMemDC(), CAMX, CAMY, SCENEMANAGER->getAlpha());
		_backBuffer->render(getHDC(), 0, 0, CAMX, CAMY, WINSIZEX, WINSIZEY);
	}
}