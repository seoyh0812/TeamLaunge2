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
	//_mainSelectRc = RectMakeCenter(승리/패배이미지 메인선택렉트);
	//_exitSelectRc = RectMakeCenter(승리/패배이미지 게임종료선택렉트);
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
	//====승리 / 패배 시 선택하기 ==================================================================================
	/*if (_isGameOver)  && 승리 조건 - 이 뭔지 물어보거나 깃발체력으로 하거나 할 예정
	{
		_result == VICTORY;
	}
	else if (_isGameOver)/* && 패배 조건 - 이 뭔지 물어보거나 깃발체력으로 하거나 할 예정
	{
		_result == DEFEAT;
	}



	//====승리 / 패배 시 선택하기 ==================================================================================
	switch (_result)
	{
		// ---- victory ----
	case VICTORY:
		FINDIMG("승리")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
		if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
		{
			if (PtInRect(&_mainSelectRc, _ptMouse))
			{
				SCENEMANAGER->changeScene("메인씬");
			}
			if (PtInRect(&_exitSelectRc, _ptMouse))
			{
				PostQuitMessage(0);
			}
		}
		break;
		// ---- defeated ----
	case DEFEAT:
		FINDIMG("패배")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);
		if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
		{
			if (PtInRect(&_mainSelectRc, _ptMouse))
			{
				SCENEMANAGER->changeScene("메인씬");
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
	FINDIMG("롤승리")->render(getMemDC());
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
