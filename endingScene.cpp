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
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	/*_mainSelectRc = RectMakeCenter(�¸�/�й��̹��� ���μ��÷�Ʈ);
	_exitSelectRc = RectMakeCenter(�¸�/�й��̹��� �������ἱ�÷�Ʈ);*/
	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	////====�¸� / �й� �� �����ϱ� ==================================================================================
	//if (_isGameOver /* && �¸� ���� - �� ���� ����ų� ���ü������ �ϰų� �� ����*/)
	//{
	//	_result == VICTORY;
	//}
	//else if (_isGameOver  /* && �й� ���� - �� ���� ����ų� ���ü������ �ϰų� �� ����*/)
	//{
	//	_result == DEFEAT;
	//}



	////====�¸� / �й� �� �����ϱ� ==================================================================================
	//switch (_result)
	//{
	//	// ---- victory ----
	//case VICTORY:
	//	FINDIMG("�÷��̾���")->render(getMemDC(), 500, 300);
	//	FINDIMG("�¸�")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
	//	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
	//	{
	//		if (PtInRect(&_mainSelectRc, _ptMouse))
	//		{
	//			SCENEMANAGER->changeScene("���ξ�");
	//		}
	//		if (PtInRect(&_exitSelectRc, _ptMouse))
	//		{
	//			PostQuitMessage(0);
	//		}
	//	}
	//	break;
	//	// ---- defeated ----
	//case DEFEAT:
	//	FINDIMG("�й�")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
	//	FINDIMG("�÷��̾���")->render(getMemDC(), 500, 300);
	//	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
	//	{
	//		if (PtInRect(&_mainSelectRc, _ptMouse))
	//		{
	//			SCENEMANAGER->changeScene("���ξ�");
	//		}
	//		if (PtInRect(&_exitSelectRc, _ptMouse))
	//		{
	//			PostQuitMessage(0);
	//		}
	//	}
	//	break;
	//}
}

void endingScene::render()
{
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
