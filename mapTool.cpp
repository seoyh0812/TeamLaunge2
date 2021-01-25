#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	imageInit();
	createSampleTiles();

	createIsoMap(650, 0, TILEX, TILEY);
	_tempTile.fX = 0;
	_tempTile.fY = 0;
	_moveUnMove = false;
	return S_OK;
}

void mapTool::imageInit()
{
	//�̹��� ����
	IMAGEMANAGER->addFrameImage("mapTiles", "image/maptool/iso256X160.bmp", 0, 0, 256, 160, 4, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save1", "image/maptool/save1.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save2", "image/maptool/save2.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save3", "image/maptool/save3.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load1", "image/maptool/load1.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load2", "image/maptool/load2.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load3", "image/maptool/load3.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("move", "image/maptool/move.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("unmove", "image/maptool/unmove.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("undo", "image/maptool/undo.bmp", 64, 32, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fill", "image/maptool/fill.bmp", 64, 32, false, RGB(255, 0, 255));

	//�̹����� ����� ��Ʈ ���� ����
	_saveBt = RectMake(WINSIZEX-210, 720, 64, 32);
	_saveBt2 = RectMake(WINSIZEX-140, 720, 64, 32);
	_saveBt3 = RectMake(WINSIZEX-70, 720, 64, 32);

	_loadBt = RectMake(WINSIZEX-210, 760, 64, 32);
	_loadBt2 = RectMake(WINSIZEX-140, 760, 64, 32);
	_loadBt3 = RectMake(WINSIZEX-70, 760, 64, 32);

	_move = RectMake(WINSIZEX-210, 680, 64, 32);
	_unMove = RectMake(WINSIZEX-140, 680, 64, 32);

	_fill = RectMake(WINSIZEX-210, 640, 64, 32);

	_undo = RectMake(WINSIZEX-70, 680, 64, 32);
}

void mapTool::imageRender()
{
	//������ ����Ÿ��
	IMAGEMANAGER->findImage("mapTiles")->render(getMemDC(), WINSIZEX-256, 0);

	//���̺�� �ε�
	IMAGEMANAGER->findImage("save1")->render(getMemDC(), _saveBt.left, _saveBt.top);
	IMAGEMANAGER->findImage("save2")->render(getMemDC(), _saveBt2.left, _saveBt2.top);
	IMAGEMANAGER->findImage("save3")->render(getMemDC(), _saveBt3.left, _saveBt3.top);
	IMAGEMANAGER->findImage("load1")->render(getMemDC(), _loadBt.left, _loadBt.top);
	IMAGEMANAGER->findImage("load2")->render(getMemDC(), _loadBt2.left, _loadBt2.top);
	IMAGEMANAGER->findImage("load3")->render(getMemDC(), _loadBt3.left, _loadBt3.top);
	IMAGEMANAGER->findImage("undo")->render(getMemDC(), _undo.left, _undo.top);
	IMAGEMANAGER->findImage("fill")->render(getMemDC(), _fill.left, _fill.top);

	//����� �𹫵�
	if (!_moveUnMove)
	{
		IMAGEMANAGER->findImage("move")->render(getMemDC(), _move.left, _move.top);
		IMAGEMANAGER->findImage("unmove")->alphaRender(getMemDC(), _unMove.left, _unMove.top, 80);
	}
	else
	{
		IMAGEMANAGER->findImage("move")->alphaRender(getMemDC(), _move.left, _move.top, 80);
		IMAGEMANAGER->findImage("unmove")->render(getMemDC(), _unMove.left, _unMove.top);
	}
}

void mapTool::moveUnMove()
{
	if (PtInRect(&_move, _ptMouse))
	{
		_moveUnMove = false;
	}

	if (PtInRect(&_unMove, _ptMouse))
	{
		_moveUnMove = true;
	}
}

void mapTool::release()
{
}

//�׷��� ���� x, �׷��� ���� y, TILEX �ֱ�, TILEY �ֱ�
void mapTool::createIsoMap(float x, float y, int tileX, int tileY)
{
	_tilePoint.x = x;
	_tilePoint.y = y;

	for (int i = 0; i < tileY; ++i)
	{
		for (int j = 0; j < tileX; ++j)
		{
			_isoTile[i * tileX + j].fX = 0;
			_isoTile[i * tileX + j].fY = 0;
			_isoTile[i * tileX + j].nX = j;
			_isoTile[i * tileX + j].nY = i;

			_isoTile[i * tileX + j].inRect = false;
			_isoTile[i * tileX + j].MUM = MOVE;

			_isoTile[i * tileX + j].drawX = _tilePoint.x + ((j * TILESIZEX) / 2) - (i*(TILESIZEX / 2));
			_isoTile[i * tileX + j].drawY = _tilePoint.y + ((j * TILESIZEY) / 2) + (i*(TILESIZEY / 2));
			_isoTile[i * tileX + j].centerX = _isoTile[i * tileX + j].drawX + (TILEX / 2) + (TILEY / 2);
			_isoTile[i * tileX + j].centerY = _isoTile[i * tileX + j].drawY + (TILEX / 2) + (TILEY / 2);
		}
	}
}

void mapTool::createSampleTiles()
{
	for (int i = 0; i < SAMPLEY; ++i)
	{
		for (int j = 0; j < SAMPLEX; ++j)
		{
			//�̰� ������ ��ġ�� �����صδ°� �׷��� ���° Ÿ������ �˰� ������ ��������
			_sample[i * SAMPLEX + j].fX = j;
			_sample[i * SAMPLEX + j].fY = i;

			_sample[i * SAMPLEX + j].rc = RectMake((WINSIZEX - 256) + (j*TILESIZEX), 0 + (i*TILESIZEY), TILESIZEX, TILESIZEY);
			_sample[i * SAMPLEX + j].inRect = false;
		}
	}
}

void mapTool::ptInSample()
{
	//����Ÿ�Ͼȿ� ���콺�� ������ ǥ���ض�
	for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
	{
		if (PtInRect(&_sample[i].rc, _ptMouse))
		{
			_sample[i].inRect = true;
		}
		else _sample[i].inRect = false;
	}

	//�̰� ���̼� Ÿ�� �ȿ� ���콺�� ������ ǥ�� 
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//���콺����Ʈ�� ���̼�Ÿ�Ͼȿ� ���Դ��� Ȯ������
		if (_ptMouse.x <= _isoTile[i].centerX + (TILESIZEX / 3) && _ptMouse.x >= _isoTile[i].centerX - (TILESIZEX / 3)
			&& _ptMouse.y <= _isoTile[i].centerY + (TILESIZEY / 3) && _ptMouse.y >= _isoTile[i].centerY - (TILESIZEY / 3))
		{
			_isoTile[i].inRect = true;
		}
		else _isoTile[i].inRect = false;
	}
}

void mapTool::createTile()
{
	//���ο� Ÿ���� �������!!
	for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
	{
		if (PtInRect(&_sample[i].rc, _ptMouse))
		{
			_tempTile.fX = _sample[i].fX;
			_tempTile.fY = _sample[i].fY;
			break;
		}
	}

	_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fX = _tempTile.fX;
	_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fY = _tempTile.fY;
	InvalidateRect(_hWnd, NULL, false);

	//for (int i = 0; i < TILEX * TILEY; ++i)
	//{
	//	//���콺����Ʈ�� ���̼�Ÿ�Ͼȿ� ���Դ��� Ȯ������
	//	//���� ���·� �׷����� Ÿ�Ͼ��� MUM�� ���� ����
	//	if (_ptMouse.x <= _isoTile[i].centerX + (TILESIZEX / 3) && _ptMouse.x >= _isoTile[i].centerX - (TILESIZEX / 3)
	//		&& _ptMouse.y <= _isoTile[i].centerY + (TILESIZEY / 3) && _ptMouse.y >= _isoTile[i].centerY - (TILESIZEY / 3) && !_moveUnMove)
	//	{
	//		_isoTile[i].fX = _tempTile.fX;
	//		_isoTile[i].fY = _tempTile.fY;
	//		_isoTile[i].MUM = MOVE;
	//		//ȭ�� �������ִ� �Լ�
	//		InvalidateRect(_hWnd, NULL, false);
	//		break;
	//	}
	//	//�𹫺� ���·� �׷����� Ÿ�Ͼ��� MUM�� ���� �𹫺�
	//	else if (_ptMouse.x <= _isoTile[i].centerX + (TILESIZEX / 3) && _ptMouse.x >= _isoTile[i].centerX - (TILESIZEX / 3)
	//		&& _ptMouse.y <= _isoTile[i].centerY + (TILESIZEY / 3) && _ptMouse.y >= _isoTile[i].centerY - (TILESIZEY / 3) && _moveUnMove)
	//	{
	//		_isoTile[i].fX = _tempTile.fX;
	//		_isoTile[i].fY = _tempTile.fY;
	//		_isoTile[i].MUM = UNMOVE;
	//		//ȭ�� �������ִ� �Լ�
	//		InvalidateRect(_hWnd, NULL, false);
	//		break;
	//	}
	//}
}

void mapTool::save()
{
	if (PtInRect(&_saveBt, _ptMouse))
	{
		HANDLE file;
		DWORD write;

		file = CreateFile("saveMap1.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_saveBt2, _ptMouse))
	{
		HANDLE file;
		DWORD write;

		file = CreateFile("saveMap2.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_saveBt3, _ptMouse))
	{
		HANDLE file;
		DWORD write;

		file = CreateFile("saveMap3.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
	}
}

void mapTool::load()
{
	if (PtInRect(&_loadBt, _ptMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("saveMap1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_loadBt2, _ptMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("saveMap2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
	}

	if (PtInRect(&_loadBt3, _ptMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("saveMap3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(tagIsoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
	}
}

void mapTool::tempSave()
{// ���콺 �� �������� Ÿ���� �׷������� �ߵ���. temp�� ����
	_tempSaved = true;
	HANDLE file;
	DWORD write;

	file = CreateFile("temp.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _isoTile, sizeof(tagIsoTile) * TILEX*TILEY, &write, NULL);

	CloseHandle(file);
}

void mapTool::tempLoad()
{// temp�� �ҷ���
		if (!_tempSaved) return;
		HANDLE file;
		DWORD read;

		file = CreateFile("temp.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(tagIsoTile) * TILEX*TILEY, &read, NULL);

		CloseHandle(file);
}

void mapTool::fill(int x, int y)
{
	for (int i = 0; i < TILEX* TILEY; ++i)
	{
		_isoTile[i].fX = x;
		_isoTile[i].fY = y;
	}
}

void mapTool::update()
{
	_pickingPt = picking(_ptMouse.x, _ptMouse.y);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_undo, _ptMouse)) tempLoad();
		tempSave();
		createTile();
		save();
		load();
		moveUnMove();
		if (PtInRect(&_fill, _ptMouse)) fill(_tempTile.fX, _tempTile.fY);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		createTile();
	}
	ptInSample();
}

void mapTool::render()
{
	//���̼�Ÿ��
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_isoTile[i].inRect) IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 150);
		else IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
	}

	//����Ÿ��
	for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
	{
		HBRUSH _brush;
		_brush = CreateSolidBrush(RGB(100, 100, 100));

		if (_sample[i].inRect) FillRect(getMemDC(), &_sample[i].rc, _brush);

		if (KEYMANAGER->isToggleKey(VK_F2)) Rectangle(getMemDC(), _sample[i].rc);
	}
	imageRender();
	//�̰� ���콺 ���� ���� �� Ÿ�� ����ε� �����
	//IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _ptMouse.x - TILESIZEX / 2, _ptMouse.y - TILESIZEY / 2, _tempTile.fX, _tempTile.fY, 200);

	//�Ʒ��� ���ǻ� ���� ���ں��̰��ϴ°�
	char str[256];
	sprintf_s(str, "TempTile X : %d , Y : %d", _tempTile.fX, _tempTile.fY);
	TextOut(getMemDC(), 0, 70, str, strlen(str));

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		sprintf_s(str, "%d, %d", _isoTile[i].nX, _isoTile[i].nY);
		if (KEYMANAGER->isToggleKey(VK_F1)) TextOut(getMemDC(), _isoTile[i].drawX + (TILEX + 5), _isoTile[i].drawY + (TILEY / 2), str, strlen(str));
	}

	sprintf_s(str, "ptMouse X : %d , Y : %d", _pickingPt.x, _pickingPt.y);
	TextOut(getMemDC(), 150, 70, str, strlen(str));
}

inline POINT mapTool::picking(long x, long y)
{ // �̰� ��ŷ
	int xx; int yy;
	//if (2 * y < (x - 320))	return { -1,0 }; // y=1/2x���� �����ִ��� (�ʹ� ���)
	//if (2 * y < -(x - 320))	return { -1,0 }; // y=-1/2x���� �����ִ��� (�ʹ� ���)
	//-1�̸� ����ó����(Ű�Ŵ��� L��ư ����)

	// �� y=1/2x�� �ƴ϶� 2y=x�� ��ĸ� ������������ �����⶧���� �̷��� ������.
	// 320�� TILEWIDTH * TILENUMX / 2 (=����ü ����ũ���� ���ݰ�)�� ������ ���ϸ� ���̱� ���� ����ϰ� ��������

	 // 64�� Ÿ�� ����(TILEHEIGHT)�� �纯 2���Ѱ��̸� �̸�ŭ�� �̰ݵ�(�����ΰ�) �����̶� ���� ��
	xx = (2 * y + (x - 682)) / 64; // y������ �̿��� ������� �ٲپ���
	if (xx > 19) return { -1,0 }; // �ʹ� ����Ÿ� ����ó��

	yy = (2 * y - (x - 682)) / 64; // ���⸸ ������ ������ ��
	if (yy > 19) return { -1,0 };

	return { xx , yy };
}
