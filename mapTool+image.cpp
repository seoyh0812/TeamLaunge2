#include "stdafx.h"
#include "mapTool.h"

void mapTool::imageInit()
{
	//�̹����� ����� ��Ʈ ���� ����
	_saveBt = RectMake(WINSIZEX - 210 + CAMX, 620 + CAMY, 64, 32);
	_saveBt2 = RectMake(WINSIZEX - 140 + CAMX, 620 + CAMY, 64, 32);
	_saveBt3 = RectMake(WINSIZEX - 70 + CAMX, 620 + CAMY, 64, 32);

	_loadBt = RectMake(WINSIZEX - 210 + CAMX, 660 + CAMY, 64, 32);
	_loadBt2 = RectMake(WINSIZEX - 140 + CAMX, 660 + CAMY, 64, 32);
	_loadBt3 = RectMake(WINSIZEX - 70 + CAMX, 660 + CAMY, 64, 32);

	_move = RectMake(WINSIZEX - 210 + CAMX, 580 + CAMY, 64, 32);
	_unMove = RectMake(WINSIZEX - 140 + CAMX, 580 + CAMY, 64, 32);
	_undo = RectMake(WINSIZEX - 70 + CAMX, 580 + CAMY, 64, 32);

	_fill = RectMake(WINSIZEX - 210 + CAMX, 540 + CAMY, 64, 32);
	_open = RectMake(WINSIZEX - 140 + CAMX, 540 + CAMY, 64, 32);
	_close = RectMake(WINSIZEX - 140 + CAMX, 540 + CAMY, 64, 32);

	_small = RectMake(WINSIZEX - 70 + CAMX, 540 + CAMY, 64, 32);
	_medium = RectMake(WINSIZEX - 70 + CAMX, 540 + CAMY, 64, 32);
	_max = RectMake(WINSIZEX - 70 + CAMX, 540 + CAMY, 64, 32);

	_leftBt = RectMake(WINSIZEX - 75 + CAMX, 385 + CAMY, 64, 32);
	_rightBt = RectMake(WINSIZEX - 35 + CAMX, 385 + CAMY, 64, 32);

	_objDel = RectMake(WINSIZEX - 140 + CAMX, 500 + CAMY, 64, 32);
	_menuRc = RectMake(CAMX + WINSIZEX - 522, CAMY, 522, 394);

	_delAll = RectMake(WINSIZEX - 70 + CAMX, 500 + CAMY, 64, 32);

	//���� menuRc�ȿ� �־ ����ó�� �ʿ����
	_tree1 = RectMake(CAMX + WINSIZEX - 512, CAMY, 107, 113);
	_icZergling = RectMake(CAMX + WINSIZEX - 512, CAMY, 80, 90);
}

void mapTool::imageRender()
{
	//���̼�Ÿ��
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ // ȭ�� ���� ���� �׸��� �ʵ��� ��. �� ������. ���ξ����� �̰� ���� �ÿ����� �̰� �ٿ��� �����൵ �ɵ�
		if (_rs == SMALL)
		{
			if (_isoTile[i].nX > 9) continue;
			if (_isoTile[i].nY > 9) continue;
		}
		else if (_rs == MEDIUM)
		{
			if (_isoTile[i].nX > 19) continue;
			if (_isoTile[i].nY > 19) continue;
		}
		else

			if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
				_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;

		if (_isoTile[i].inRect)
		{//����� ����ǥ�ÿ� �Բ� �̹����� ����Ǵ°�
			if (_isoTile[i].name == TREE1)
			{
				IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 150);
				IMAGEMANAGER->findImage("tree")->render(getMemDC(), _isoTile[i].drawX - 32, _isoTile[i].drawY - 90);
			}
			else if (_isoTile[i].name == ZERGLING)
			{
				IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 150);
				IMAGEMANAGER->findImage("���۸��̵�����")->frameRender(getMemDC(), _isoTile[i].drawX + 10, _isoTile[i].drawY - 5, 5, 0);
			}
			else IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 150);
		}//����� ���콺�� Ÿ���� ���� �ʾ�����
		else if (_isoTile[i].name == NONE)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
		}
		else if (_isoTile[i].name == TREE1)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
			IMAGEMANAGER->findImage("tree")->render(getMemDC(), _isoTile[i].drawX - 32, _isoTile[i].drawY - 90);
		}
		else if (_isoTile[i].name == ZERGLING)
		{
			IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
			IMAGEMANAGER->findImage("���۸��̵�����")->frameRender(getMemDC(), _isoTile[i].drawX + 10, _isoTile[i].drawY - 5, 5, 0);
		}
	}

	if (_brushOn)
	{
		//����Ÿ�� �޴�
		IMAGEMANAGER->findImage("tileMenu")->render(getMemDC(), CAMX + WINSIZEX - 522, CAMY);
		IMAGEMANAGER->findImage("leftBt")->render(getMemDC(), _leftBt.left, _leftBt.top);
		IMAGEMANAGER->findImage("rightBt")->render(getMemDC(), _rightBt.left, _rightBt.top);
		//����Ÿ��
		//ù��° �޴�(Ÿ��)
		if (_menuNum == ONE)
		{
			HBRUSH _brush;
			_brush = CreateSolidBrush(RGB(255, 255, 255));
			for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
			{
				if (PtInRect(&_sample[i].rc, _cameraPtMouse)) FillRect(getMemDC(), &_sample[i].rc, _brush);
			}
			IMAGEMANAGER->findImage("mapTiles")->render(getMemDC(), CAMX + WINSIZEX - 512, CAMY);
		}
		else if (_menuNum == TWO)
		{
			HBRUSH _brush;
			_brush = CreateSolidBrush(RGB(255, 255, 255));
			if (PtInRect(&_tree1, _cameraPtMouse)) FillRect(getMemDC(), &_tree1, _brush);
			IMAGEMANAGER->findImage("tree")->render(getMemDC(), _tree1.left, _tree1.top);
		}
		else if (_menuNum == THREE)
		{
			IMAGEMANAGER->findImage("icon_zergling")->render(getMemDC(), _icZergling.left, _icZergling.top);
		}
	}
	//���̺�� �ε�
	IMAGEMANAGER->findImage("save1")->render(getMemDC(), _saveBt.left, _saveBt.top);
	IMAGEMANAGER->findImage("save2")->render(getMemDC(), _saveBt2.left, _saveBt2.top);
	IMAGEMANAGER->findImage("save3")->render(getMemDC(), _saveBt3.left, _saveBt3.top);
	IMAGEMANAGER->findImage("load1")->render(getMemDC(), _loadBt.left, _loadBt.top);
	IMAGEMANAGER->findImage("load2")->render(getMemDC(), _loadBt2.left, _loadBt2.top);
	IMAGEMANAGER->findImage("load3")->render(getMemDC(), _loadBt3.left, _loadBt3.top);
	IMAGEMANAGER->findImage("undo")->render(getMemDC(), _undo.left, _undo.top);
	IMAGEMANAGER->findImage("fill")->render(getMemDC(), _fill.left, _fill.top);
	IMAGEMANAGER->findImage("delAll")->render(getMemDC(), _delAll.left, _delAll.top);

	if (!_objDelOn) IMAGEMANAGER->findImage("objDel")->alphaRender(getMemDC(), _objDel.left, _objDel.top, 80);
	else IMAGEMANAGER->findImage("objDel")->render(getMemDC(), _objDel.left, _objDel.top);

	if (_rs == SMALL) IMAGEMANAGER->findImage("small")->render(getMemDC(), _small.left, _small.top);
	else if (_rs == MEDIUM) IMAGEMANAGER->findImage("medium")->render(getMemDC(), _medium.left, _medium.top);
	else IMAGEMANAGER->findImage("max")->render(getMemDC(), _max.left, _max.top);

	if (!_brushOn) IMAGEMANAGER->findImage("open")->render(getMemDC(), _open.left, _open.top);
	else IMAGEMANAGER->findImage("close")->render(getMemDC(), _close.left, _close.top);
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