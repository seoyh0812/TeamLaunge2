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

	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, CAMX+WINSIZEX, CAMY + WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	SCENEMANAGER->render();
	if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getMemDC(), CAMX, CAMY);
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC(), 0, 0, CAMX, CAMY, WINSIZEX, WINSIZEY);
}