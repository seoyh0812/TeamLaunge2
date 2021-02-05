#include "stdafx.h"
#include "endingScene.h"

endingScene::endingScene()
{
}

endingScene::~endingScene()
{
}

HRESULT endingScene::init()
{
	_score = CAMX;
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	//_mainSelectRc = RectMakeCenter(�¸�/�й��̹��� ���μ��÷�Ʈ);
	//_exitSelectRc = RectMakeCenter(�¸�/�й��̹��� �������ἱ�÷�Ʈ);
	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		PostQuitMessage(0);
	}
	//====�¸� / �й� �� �����ϱ� ==================================================================================
	/*if (_isGameOver)  && �¸� ���� - �� ���� ����ų� ���ü������ �ϰų� �� ����
	{
		_result == VICTORY;
	}
	else if (_isGameOver)/* && �й� ���� - �� ���� ����ų� ���ü������ �ϰų� �� ����
	{
		_result == DEFEAT;
	}



	//====�¸� / �й� �� �����ϱ� ==================================================================================
	switch (_result)
	{
		// ---- victory ----
	case VICTORY:
		FINDIMG("�¸�")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
		if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
		{
			if (PtInRect(&_mainSelectRc, _ptMouse))
			{
				SCENEMANAGER->changeScene("���ξ�");
			}
			if (PtInRect(&_exitSelectRc, _ptMouse))
			{
				PostQuitMessage(0);
			}
		}
		break;
		// ---- defeated ----
	case DEFEAT:
		FINDIMG("�й�")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
		if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
		{
			if (PtInRect(&_mainSelectRc, _ptMouse))
			{
				SCENEMANAGER->changeScene("���ξ�");
			}
			if (PtInRect(&_exitSelectRc, _ptMouse))
			{
				PostQuitMessage(0);
			}
		}
		break;
	}*/
}

void endingScene::render()
{
	FINDIMG("�ѽ¸�")->render(getMemDC());

	// �������ھ� �����ִ°�
	if (_score > 9999) FINDIMG("����")->frameRender(getMemDC(), 600 - 30, WINSIZEY/2, _score / 10000 % 10, 0);
	if (_score > 999) FINDIMG("����")->frameRender(getMemDC(), 600 - 15, WINSIZEY / 2, _score / 1000 % 10, 0);
	if (_score > 99) FINDIMG("����")->frameRender(getMemDC(), 600, WINSIZEY / 2, _score / 100 % 10, 0);
	if (_score > 9) FINDIMG("����")->frameRender(getMemDC(), 600 + 15, WINSIZEY / 2, _score / 10 % 10, 0);
	FINDIMG("����")->frameRender(getMemDC(), 600 + 30, WINSIZEY / 2, _score % 10, 0);
	//switch (_result)
	//{
	//	// ---- victory ----
	//case VICTORY:
	//	break;
	//	// ---- defeated ----
	//case DEFEAT:
	//	break;
	//}
}
