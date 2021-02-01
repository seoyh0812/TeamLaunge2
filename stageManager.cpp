#include "stdafx.h"
#include "stageManager.h"

stageManager::stageManager()
{
}

stageManager::~stageManager()
{
}

HRESULT stageManager::init()
{
	_stage = STAGE1;
	_battlePhase = false;
	_menuInPt = false;
	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
	_cameraPtMouse.x = _ptMouse.x + CAMX;
	_cameraPtMouse.y = _ptMouse.y + CAMY;
	_pickingPt = picking(_cameraPtMouse.x, _cameraPtMouse.y);
	uiRect();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		homeBt();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_stage = STAGE1;
		setStage(_stage);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_stage = STAGE2;
		setStage(_stage);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_stage = STAGE3;
		setStage(_stage);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RETURN))
	{ // ������ ����Ű���س����� ���߿� ��ġ������ ������ ��ư(���ӽ���)�� ���� ���� �ٲܰ���
		_battlePhase = true;
		_um->setActive();
	}
}

void stageManager::render()
{
	//���̼�Ÿ��
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ 
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
	}
}

void stageManager::objectRender()
{
	//������Ʈ��! �׷��ش�
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		else if (_isoTile[i].name == TREE1)
		{
			IMAGEMANAGER->findImage("tree")->render(getMemDC(), _isoTile[i].drawX - 32, _isoTile[i].drawY - 90);
		}
		else if (_isoTile[i].name == TREE2)
		{
			IMAGEMANAGER->findImage("tree2")->render(getMemDC(), _isoTile[i].drawX - 10, _isoTile[i].drawY - 90);
		}
		else if (_isoTile[i].name == TREE3)
		{
			IMAGEMANAGER->findImage("tree3")->render(getMemDC(), _isoTile[i].drawX - 12, _isoTile[i].drawY - 118);
		}
		else if (_isoTile[i].name == TREE4)
		{
			IMAGEMANAGER->findImage("tree4")->render(getMemDC(), _isoTile[i].drawX - 15, _isoTile[i].drawY - 105);
		}
		else if (_isoTile[i].name == TREE5)
		{
			IMAGEMANAGER->findImage("tree5")->render(getMemDC(), _isoTile[i].drawX - 3, _isoTile[i].drawY - 58);
		}
	}
}

void stageManager::uiRender()
{
	IMAGEMANAGER->findImage("ui_clear")->render(getMemDC(), CAMX + WINSIZEX - 128, CAMY);
	IMAGEMANAGER->findImage("ui_start")->render(getMemDC(), CAMX + WINSIZEX - 64, CAMY);
	IMAGEMANAGER->findImage("ui_home")->render(getMemDC(), CAMX, CAMY + 500);
	IMAGEMANAGER->findImage("ui_retry")->render(getMemDC(), CAMX, CAMY + 532);

	//���� ���� �޴�
	IMAGEMANAGER->findImage("ui_menu")->render(getMemDC(), CAMX + WINSIZEX - 930, CAMY + WINSIZEY - 132);
	IMAGEMANAGER->findImage("icon_zergling")->render(getMemDC(), CAMX + 280, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_marine")->render(getMemDC(), CAMX + 360, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_civilian")->render(getMemDC(), CAMX + 440, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_templar")->render(getMemDC(), CAMX + 520, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_bishop")->render(getMemDC(), CAMX + 600, CAMY + WINSIZEY - 95);
	IMAGEMANAGER->findImage("icon_ghost")->render(getMemDC(), CAMX + 680, CAMY + WINSIZEY - 95);
}

void stageManager::uiRect()
{
	_homeBt = RectMake(CAMX, CAMY + 500, 64, 32);
}

void stageManager::homeBt()
{
	if (PtInRect(&_homeBt, _cameraPtMouse))
	{
		_menuInPt = true;
		if (_menuInPt) SCENEMANAGER->changeScene("Ÿ��Ʋ��");
	}
	else _menuInPt = false;
}

inline POINT stageManager::picking(long x, long y)
{ // �̰� ��ŷ
	int xx; int yy;
	if (2 * y < (x - 960))	return { -1,0 }; // y=1/2x���� �����ִ��� (�ʹ� ���)
	if (2 * y < -(x - 960))	return { -1,0 }; // y=-1/2x���� �����ִ��� (�ʹ� ���)
	//-1�̸� ����ó����(Ű�Ŵ��� L��ư ����)

	// �� y=1/2x�� �ƴ϶� 2y=x�� ��ĸ� ������������ �����⶧���� �̷��� ������.
	// 320�� TILEWIDTH * TILEX / 2 (=����ü ����ũ���� ���ݰ�)�� ������ ���ϸ� ���̱� ���� ����ϰ� ��������

	 // 64�� Ÿ�� ����(TILEHEIGHT)�� �纯 2���Ѱ��̸� �̸�ŭ�� �̰ݵ�(�����ΰ�) �����̶� ���� ��
	xx = (2 * y + (x - 960)) / 64; // y������ �̿��� ������� �ٲپ���
	// xx = ((y + 1/2*(x - 960)) / 32
	// (x��ǥ) = ((y + 1/2 *(x - ��x����)) / Ÿ�ϳ���
	//           �ѤѤѤѤѤѤѤѤѤѤѤѤ�
	//           ��>�� �κ��� y����(h)
	if (xx > 29) return { -1,0 }; // �ʹ� ����Ÿ� ����ó��

	yy = (2 * y - (x - 960)) / 64; // ���⸸ ������ ������ ��
	// yy = ((y - 1/2*(x - 960)) / 32
	// (y��ǥ) = ((y - 1/2 *(x - ��x����)) / Ÿ�ϳ���
	//           �ѤѤѤѤѤѤѤѤѤѤѤѤ�
	//           ��>�� �κ��� y����(h)
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}

void stageManager::setStage(STAGE stage)
{ // �� ���� ������ ��⼭�ϱ�� ��
	HANDLE file;
	DWORD read;

	switch (stage)
	{
	case STAGE1:
		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);

		_gold = _isoTile[0].gold;
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].name == ZERGLING)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == MARINE)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == CIVILIAN)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == TEMPLAR)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == BISHOP)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			//if (_isoTile[i].name == DIABLO)
			//{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
			//	_um->createDiablo(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			//if (_isoTile[i].name == SKELETON)
			//{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
			//	_um->createSkeleton(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			if (_isoTile[i].name == GHOST)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
		}

		break;
	case STAGE2:
		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);

		_gold = _isoTile[0].gold;
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].name == ZERGLING)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == MARINE)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == CIVILIAN)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == TEMPLAR)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == BISHOP)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			//if (_isoTile[i].name == DIABLO)
			//{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
			//	_um->createDiablo(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			//if (_isoTile[i].name == SKELETON)
			//{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
			//	_um->createSkeleton(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			if (_isoTile[i].name == GHOST)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
		}

		break;
	case STAGE3:
		file = CreateFile("stage3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);

		_gold = _isoTile[0].gold;
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].name == ZERGLING)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createZergling(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == MARINE)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createMarine(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == CIVILIAN)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createCivilian(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == TEMPLAR)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createTemplar(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			if (_isoTile[i].name == BISHOP)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createBishop(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
			//if (_isoTile[i].name == DIABLO)
			//{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
			//	_um->createDiablo(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			//if (_isoTile[i].name == SKELETON)
			//{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
			//	_um->createSkeleton(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			//}
			if (_isoTile[i].name == GHOST)
			{ // ���ʹ� ������ ���⼭�ϰ� ������Ʈ�� �츮�� �׷��ָ��(���ֺ��� ���߿� �׷��ٰ���. ��������)
				_um->createGhost(ENEMY, _isoTile[i].centerX, _isoTile[i].centerY);
			}
		}
		break;
	}
}
