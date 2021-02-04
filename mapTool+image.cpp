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
	_homeBt = RectMake(CAMX, CAMY + 500, 64, 32);
	_goldBt = RectMake(CAMX, CAMY + 548, 200, 32);

	//���� menuRc�ȿ� �־ ����ó�� �ʿ����
	_tree1 = RectMake(CAMX + WINSIZEX - 512, CAMY, 107, 113);
	_tree2 = RectMake(CAMX + WINSIZEX - 402, CAMY, 89, 115);
	_tree3 = RectMake(CAMX + WINSIZEX - 312, CAMY, 84, 139);
	_tree4 = RectMake(CAMX + WINSIZEX - 222, CAMY, 94, 128);
	_tree5 = RectMake(CAMX + WINSIZEX - 122, CAMY, 76, 83);
	_wall1 = RectMake(CAMX + WINSIZEX - 512, CAMY + 113, 32, 45);
	_wall2 = RectMake(CAMX + WINSIZEX - 480, CAMY + 113, 32, 45);
	_wall3 = RectMake(CAMX + WINSIZEX - 448, CAMY + 113, 32, 45);
	_wall4 = RectMake(CAMX + WINSIZEX - 416, CAMY + 113, 32, 45);
	_lava_obj1 = RectMake(CAMX + WINSIZEX - 122, CAMY + 83, 54, 97);
	_lava_obj3 = RectMake(CAMX + WINSIZEX - 122, CAMY + 180, 70, 52);
	_lava_obj2_l = RectMake(CAMX + WINSIZEX - 512, CAMY + 158, 54, 86);
	_lava_obj2_r = RectMake(CAMX + WINSIZEX - 458, CAMY + 158, 54, 86);

	_playerFlagRc = RectMake(CAMX + WINSIZEX - 512, CAMY+266, 64, 118);
	_enemyFlagRc = RectMake(CAMX + WINSIZEX - 448, CAMY+266, 64, 118);

	_icZergling = RectMake(CAMX + WINSIZEX - 512, CAMY, 80, 90);
	_icMarine = RectMake(CAMX + WINSIZEX - 432, CAMY, 80, 90);
	_icCivilian = RectMake(CAMX + WINSIZEX - 352, CAMY, 80, 90);
	_icTemplar = RectMake(CAMX + WINSIZEX - 272, CAMY, 80, 90);
	_icBishop = RectMake(CAMX + WINSIZEX - 192, CAMY, 80, 90);
	_icDiablo = RectMake(CAMX + WINSIZEX - 112, CAMY, 80, 90);
	_icSkeleton = RectMake(CAMX + WINSIZEX - 512, CAMY + 90, 80, 90);
	_icGhost = RectMake(CAMX + WINSIZEX - 432, CAMY + 90, 80, 90);
}

void mapTool::imageRender()
{
	//���̼�Ÿ��
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ // ȭ�� ���� ���� �׸��� �ʵ��� ��. �� ������. ���ξ����� �̰� ���� �ÿ����� �̰� �ٿ��� �����൵ �ɵ�
		if (_rs == SMALL)
		{
			if (_isoTile[i].nX < 9 || _isoTile[i].nX > 19) continue;
			if (_isoTile[i].nY < 9 || _isoTile[i].nY > 19) continue;
		}
		else if (_rs == MEDIUM)
		{
			if (_isoTile[i].nX < 4 || _isoTile[i].nX > 24) continue;
			if (_isoTile[i].nY < 4 || _isoTile[i].nY > 24) continue;
		}
		else

		if (_isoTile[i].centerX < CAMX - 32 || _isoTile[i].centerX > CAMX + WINSIZEX + 32 ||
			_isoTile[i].centerY < CAMY - 16 || _isoTile[i].centerY > CAMY + WINSIZEY + 16) continue;
		
		//���̼� Ÿ�� �׷���
		if (_isoTile[i].inRect)	IMAGEMANAGER->findImage("mapTiles")->alphaFrameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY, 100);
		else IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);


		//����� Ÿ�� ���� ������Ʈ�� �׷��ִ� �κ�
		if (_isoTile[i].name == TREE1)	IMAGEMANAGER->findImage("tree")->render(getMemDC(), _isoTile[i].drawX - 32, _isoTile[i].drawY - 90);
		else if (_isoTile[i].name == TREE2)	IMAGEMANAGER->findImage("tree2")->render(getMemDC(), _isoTile[i].drawX - 10, _isoTile[i].drawY - 90);
		else if (_isoTile[i].name == TREE3)	IMAGEMANAGER->findImage("tree3")->render(getMemDC(), _isoTile[i].drawX - 12, _isoTile[i].drawY - 118);
		else if (_isoTile[i].name == TREE4)	IMAGEMANAGER->findImage("tree4")->render(getMemDC(), _isoTile[i].drawX - 15, _isoTile[i].drawY - 105);
		else if (_isoTile[i].name == TREE5)	IMAGEMANAGER->findImage("tree5")->render(getMemDC(), _isoTile[i].drawX - 3, _isoTile[i].drawY - 58);
		else if (_isoTile[i].name == WALL1)	IMAGEMANAGER->findImage("wall1")->render(getMemDC(), _isoTile[i].drawX + 8, _isoTile[i].drawY - 18);
		else if (_isoTile[i].name == WALL2)	IMAGEMANAGER->findImage("wall2")->render(getMemDC(), _isoTile[i].drawX + 24, _isoTile[i].drawY - 18);
		else if (_isoTile[i].name == WALL3)	IMAGEMANAGER->findImage("wall1")->render(getMemDC(), _isoTile[i].drawX + 32, _isoTile[i].drawY - 28);
		else if (_isoTile[i].name == WALL4)	IMAGEMANAGER->findImage("wall2")->render(getMemDC(), _isoTile[i].drawX + 4, _isoTile[i].drawY - 28);
		else if (_isoTile[i].name == LAVA_OBJ1)	IMAGEMANAGER->findImage("lava_obj1")->render(getMemDC(), _isoTile[i].drawX + 4, _isoTile[i].drawY - 72);
		else if (_isoTile[i].name == LAVA_OBJ3)	IMAGEMANAGER->findImage("lava_obj3")->render(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY - 25);
		else if (_isoTile[i].name == LAVA_OBJ2_L)	IMAGEMANAGER->findImage("lava_obj2_l")->render(getMemDC(), _isoTile[i].drawX + 4, _isoTile[i].drawY - 60);
		else if (_isoTile[i].name == LAVA_OBJ2_R)	IMAGEMANAGER->findImage("lava_obj2_r")->render(getMemDC(), _isoTile[i].drawX , _isoTile[i].drawY - 60);
		else if (_isoTile[i].name == PLAYERFLAG)	IMAGEMANAGER->findImage("�÷��̾���")->render(getMemDC(), _isoTile[i].centerX - 32, _isoTile[i].centerY - 118);
		else if (_isoTile[i].name == ENEMYFLAG)	IMAGEMANAGER->findImage("���ʹ̱��")->render(getMemDC(), _isoTile[i].centerX - 32, _isoTile[i].centerY - 118);
		else if (_isoTile[i].name == ZERGLING)	IMAGEMANAGER->findImage("���۸��̵�����")->frameRender(getMemDC(), _isoTile[i].drawX + 11, _isoTile[i].drawY - 5, 4, 0);
		else if (_isoTile[i].name == MARINE)	IMAGEMANAGER->findImage("�����⺻����")->frameRender(getMemDC(), _isoTile[i].drawX + 15, _isoTile[i].drawY - 5, 0, 4);
		else if (_isoTile[i].name == CIVILIAN)	IMAGEMANAGER->findImage("�ù�����")->frameRender(getMemDC(), _isoTile[i].drawX + 23, _isoTile[i].drawY - 5, 4, 7);
		else if (_isoTile[i].name == TEMPLAR)	IMAGEMANAGER->findImage("���÷��������")->frameRender(getMemDC(), _isoTile[i].drawX + 18, _isoTile[i].drawY - 10, 4, 7);
		else if (_isoTile[i].name == BISHOP)	IMAGEMANAGER->findImage("��������")->frameRender(getMemDC(), _isoTile[i].drawX + 25, _isoTile[i].drawY - 2, 4, 0);
		else if (_isoTile[i].name == DIABLO) IMAGEMANAGER->findImage("��ƺ�� ����")->frameRender(getMemDC(), _isoTile[i].drawX - 70, _isoTile[i].drawY - 145, 4, 2);
		else if (_isoTile[i].name == SKELETON) IMAGEMANAGER->findImage("�ذ񺴻� ����")->frameRender(getMemDC(), _isoTile[i].drawX - 2, _isoTile[i].drawY - 14, 4, 2);
		else if (_isoTile[i].name == GHOST)	IMAGEMANAGER->findImage("ghost_move_red")->frameRender(getMemDC(), _isoTile[i].drawX + 7, _isoTile[i].drawY - 10, 4, 0);

		//�𹫺� Ÿ�� ǥ��
		if (_isoTile[i].MUM == UNMOVE) IMAGEMANAGER->findImage("un")->render(getMemDC(), _isoTile[i].drawX + 23, _isoTile[i].drawY + 7);
	}

	for (int i = 0; i < _path.size(); ++i)
	{
		if (!_seePath) break;
		FINDIMG("���̵�Ÿ��")->alphaRender(getMemDC(), _isoTile[_path[i]].drawX, _isoTile[_path[i]].drawY,150);
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
			_brush = CreateSolidBrush(RGB(100, 100, 100));
			for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
			{
				if (PtInRect(&_sample[i].rc, _cameraPtMouse)) FillRect(getMemDC(), &_sample[i].rc, _brush);
			}
			IMAGEMANAGER->findImage("mapTiles")->render(getMemDC(), CAMX + WINSIZEX - 512, CAMY);
		}
		else if (_menuNum == TWO)
		{
			HBRUSH _brush;
			_brush = CreateSolidBrush(RGB(100, 100, 100));
			if (PtInRect(&_tree1, _cameraPtMouse)) FillRect(getMemDC(), &_tree1, _brush);
			IMAGEMANAGER->findImage("tree")->render(getMemDC(), _tree1.left, _tree1.top);

			if (PtInRect(&_tree2, _cameraPtMouse)) FillRect(getMemDC(), &_tree2, _brush);
			IMAGEMANAGER->findImage("tree2")->render(getMemDC(), _tree2.left, _tree2.top);

			if (PtInRect(&_tree3, _cameraPtMouse)) FillRect(getMemDC(), &_tree3, _brush);
			IMAGEMANAGER->findImage("tree3")->render(getMemDC(), _tree3.left, _tree3.top);

			if (PtInRect(&_tree4, _cameraPtMouse)) FillRect(getMemDC(), &_tree4, _brush);
			IMAGEMANAGER->findImage("tree4")->render(getMemDC(), _tree4.left, _tree4.top);

			if (PtInRect(&_tree5, _cameraPtMouse)) FillRect(getMemDC(), &_tree5, _brush);
			IMAGEMANAGER->findImage("tree5")->render(getMemDC(), _tree5.left, _tree5.top);

			if (PtInRect(&_playerFlagRc , _cameraPtMouse)) FillRect(getMemDC(), &_playerFlagRc, _brush);
			IMAGEMANAGER->findImage("�÷��̾���")->render(getMemDC(), _playerFlagRc.left, _playerFlagRc.top);

			if (PtInRect(&_enemyFlagRc, _cameraPtMouse)) FillRect(getMemDC(), &_enemyFlagRc, _brush);
			IMAGEMANAGER->findImage("���ʹ̱��")->render(getMemDC(), _enemyFlagRc.left, _enemyFlagRc.top);

			if (PtInRect(&_wall1, _cameraPtMouse)) FillRect(getMemDC(), &_wall1, _brush);
			IMAGEMANAGER->findImage("wall1")->render(getMemDC(), _wall1.left, _wall1.top);

			if (PtInRect(&_wall2, _cameraPtMouse)) FillRect(getMemDC(), &_wall2, _brush);
			IMAGEMANAGER->findImage("wall2")->render(getMemDC(), _wall2.left, _wall2.top);

			if (PtInRect(&_wall3, _cameraPtMouse)) FillRect(getMemDC(), &_wall3, _brush);
			IMAGEMANAGER->findImage("wall1")->render(getMemDC(), _wall3.left, _wall3.top);

			if (PtInRect(&_wall4, _cameraPtMouse)) FillRect(getMemDC(), &_wall4, _brush);
			IMAGEMANAGER->findImage("wall2")->render(getMemDC(), _wall4.left, _wall4.top);

			if (PtInRect(&_lava_obj1, _cameraPtMouse)) FillRect(getMemDC(), &_lava_obj1, _brush);
			IMAGEMANAGER->findImage("lava_obj1")->render(getMemDC(), _lava_obj1.left, _lava_obj1.top);

			if (PtInRect(&_lava_obj3, _cameraPtMouse)) FillRect(getMemDC(), &_lava_obj3, _brush);
			IMAGEMANAGER->findImage("lava_obj3")->render(getMemDC(), _lava_obj3.left, _lava_obj3.top);

			if (PtInRect(&_lava_obj2_l, _cameraPtMouse)) FillRect(getMemDC(), &_lava_obj2_l, _brush);
			IMAGEMANAGER->findImage("lava_obj2_l")->render(getMemDC(), _lava_obj2_l.left, _lava_obj2_l.top);

			if (PtInRect(&_lava_obj2_r, _cameraPtMouse)) FillRect(getMemDC(), &_lava_obj2_r, _brush);
			IMAGEMANAGER->findImage("lava_obj2_r")->render(getMemDC(), _lava_obj2_r.left, _lava_obj2_r.top);
		}
		else if (_menuNum == THREE)
		{
			IMAGEMANAGER->findImage("icon_zergling")->render(getMemDC(), _icZergling.left, _icZergling.top);
			IMAGEMANAGER->findImage("icon_marine")->render(getMemDC(), _icMarine.left, _icMarine.top);
			IMAGEMANAGER->findImage("icon_civilian")->render(getMemDC(), _icCivilian.left, _icCivilian.top);
			IMAGEMANAGER->findImage("icon_templar")->render(getMemDC(), _icTemplar.left, _icTemplar.top);
			IMAGEMANAGER->findImage("icon_bishop")->render(getMemDC(), _icBishop.left, _icBishop.top);
			IMAGEMANAGER->findImage("icon_diablo")->render(getMemDC(), _icDiablo.left, _icDiablo.top);
			IMAGEMANAGER->findImage("icon_skeleton")->render(getMemDC(), _icSkeleton.left, _icSkeleton.top);
			IMAGEMANAGER->findImage("icon_ghost")->render(getMemDC(), _icGhost.left, _icGhost.top);
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
	IMAGEMANAGER->findImage("ui_home")->render(getMemDC(), _homeBt.left, _homeBt.top);
	if (_currentStage == 1)
	{
		FINDIMG("���罺������")->alphaRender(getMemDC(), _loadBt.left + 2, _loadBt.top + 2, 100);
	}
	if (_currentStage == 2)
	{
		FINDIMG("���罺������")->alphaRender(getMemDC(), _loadBt2.left + 2, _loadBt2.top + 2, 100);
	}
	if (_currentStage == 3)
	{
		FINDIMG("���罺������")->alphaRender(getMemDC(), _loadBt3.left + 2, _loadBt3.top + 2, 100);
	}
	FINDIMG("���ް��")->render(getMemDC(), _goldBt.left, _goldBt.top);
	FINDIMG("�޷�")->render(getMemDC(), CAMX + 102, CAMY + 552);
	if (_modifyingNum != 1 || _modifyingCount % 12 > 6) FINDIMG("����")->frameRender(getMemDC(), CAMX + 132, CAMY + 555, _isoTile[0].gold / 1000 % 10, 0);
	if (_modifyingNum != 2 || _modifyingCount % 12 > 6) FINDIMG("����")->frameRender(getMemDC(), CAMX + 147, CAMY + 555, _isoTile[0].gold / 100 % 10, 0);
	if (_modifyingNum != 3 || _modifyingCount % 12 > 6) FINDIMG("����")->frameRender(getMemDC(), CAMX + 162, CAMY + 555, _isoTile[0].gold / 10 % 10, 0);
	if (_modifyingNum != 4 || _modifyingCount % 12 > 6) FINDIMG("����")->frameRender(getMemDC(), CAMX + 177, CAMY + 555, _isoTile[0].gold % 10, 0);



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

	if (_savePopUp == 1) FINDIMG("�����˾�")->alphaFrameRender(getMemDC(), CAMX + 425, CAMY + 300, 0, 0, 15+ 2*_popUpCount);
	else if (_savePopUp == 2) FINDIMG("�����˾�")->alphaFrameRender(getMemDC(), CAMX + 425, CAMY + 300, 0, 1, 15+ 2 * _popUpCount);
}