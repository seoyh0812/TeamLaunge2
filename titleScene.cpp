#include "stdafx.h"
#include "titleScene.h"

titleScene::titleScene()
{
}

titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	return S_OK;
}

void titleScene::release()
{
}

void titleScene::update()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		SCENEMANAGER->changeScene("���ξ�");
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		SCENEMANAGER->changeScene("����");
	}
}

void titleScene::render()
{
	TextOut(getMemDC(), WINSIZEX / 3, WINSIZEY / 2,
		"A��ŸƮ     S����     D�ɼ�(����X)",
		strlen("A��ŸƮ     S����     D�ɼ�(����X)"));
}
