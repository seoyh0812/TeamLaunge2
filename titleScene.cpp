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
	_image = IMAGEMANAGER->addImage("Ÿ��Ʋ�޴�", "image/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_gameStart = RectMakeCenter(WINSIZEX / 2, 350, 200, 60);
	_mapTool = RectMakeCenter(WINSIZEX / 2, 430, 200, 60);
	_option = RectMakeCenter(WINSIZEX / 2, 510, 200, 60);
	_exit = RectMakeCenter(WINSIZEX / 2, 592, 200, 60);
	return S_OK;
}

void titleScene::release()
{
}


void titleScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON))
	{
		if (PtInRect(&_gameStart, _ptMouse) == true && PtInRect(&_gameStart, _ptMouse) == true)
		{
			SCENEMANAGER->changeScene("���ξ�");
		}

		else if (PtInRect(&_mapTool, _ptMouse) == true && PtInRect(&_mapTool, _ptMouse) == true)
		{
			SCENEMANAGER->changeScene("����");
		}

		if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON) && PtInRect(&_option, _ptMouse) == true)
		{
			// �������� Ű�Է� �� �����Դϴ�.
			SCENEMANAGER->changeScene("�ɼ�");
		}
		if (KEYMANAGER->isOnceKeyDown(MK_LBUTTON) && PtInRect(&_exit, _ptMouse) == true)
		{
			// ������ �Լ� ã�Ƽ� ��������
		}
	}

}

void titleScene::render()
{

	_image->render(getMemDC());


}
