#include "stdafx.h"
#include "mapTool.h"

//���� �𹫺� ��ư
void mapTool::moveUnMove()
{
	if (PtInRect(&_move, _cameraPtMouse))
	{
		_moveUnMove = false;
	}

	if (PtInRect(&_unMove, _cameraPtMouse))
	{
		_moveUnMove = true;
	}
}
//���� ��ġ�� ��ư
void mapTool::openClose()
{
	if (PtInRect(&_open, _cameraPtMouse) && !_brushOn)
	{
		_brushOn = true;
	}
	else if (PtInRect(&_close, _cameraPtMouse) && _brushOn)
	{
		_brushOn = false;
	}
}
//���������� ��ư
void mapTool::renderSize()
{
	if (PtInRect(&_small, _cameraPtMouse) && _rs == SMALL)
	{
		_rs = MEDIUM;
	}
	else if (PtInRect(&_medium, _cameraPtMouse) && _rs == MEDIUM)
	{
		_rs = MAX;
	}
	else if (PtInRect(&_max, _cameraPtMouse) && _rs == MAX)
	{
		_rs = SMALL;
	}
}
//��� �޴� �ȿ� ���콺�� ���ִµ��ȿ��� Ÿ���� �׸�������� ��ȣ�� ���ִ� �ſ���
void mapTool::menuInPt()
{
	if (PtInRect(&_menuRc, _cameraPtMouse) && _brushOn) _menuInPt = true;
	else if (PtInRect(&_saveBt, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_saveBt2, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_saveBt3, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_loadBt, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_loadBt2, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_loadBt3, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_move, _cameraPtMouse))    _menuInPt = true;
	else if (PtInRect(&_unMove, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_undo, _cameraPtMouse))    _menuInPt = true;
	else if (PtInRect(&_fill, _cameraPtMouse))    _menuInPt = true;
	else if (PtInRect(&_open, _cameraPtMouse))    _menuInPt = true;
	else if (PtInRect(&_close, _cameraPtMouse))   _menuInPt = true;
	else if (PtInRect(&_small, _cameraPtMouse))   _menuInPt = true;
	else if (PtInRect(&_medium, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_max, _cameraPtMouse))     _menuInPt = true;
	else if (PtInRect(&_leftBt, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_rightBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_objDel, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_delAll, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_homeBt, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_goldBt, _cameraPtMouse))  _menuInPt = true;	
	else _menuInPt = false;
}

//��� left right ȭ��ǥ ��ư�ε� ���� � �޴��� �����ִ��� + ��ư�� ���콺�� �������� �˻��ؼ�
//��Ȳ�� ���� �´� �ൿ�� ���ִ°ſ���
void mapTool::leftRightBt()
{
	if (PtInRect(&_rightBt, _cameraPtMouse) && _menuNum == ONE)
	{
		_menuNum = TWO;
		_objName = NONE;
	}
	else if (PtInRect(&_rightBt, _cameraPtMouse) && _menuNum == TWO)
	{
		_menuNum = THREE;
		_objName = NONE;
	}
	else if (PtInRect(&_rightBt, _cameraPtMouse) && _menuNum == THREE)
	{
		_menuNum = THREE;
		_objName = NONE;
	}
	else if (PtInRect(&_leftBt, _cameraPtMouse) && _menuNum == TWO)
	{
		_menuNum = ONE;
		_objName = NONE;
	}
	else if (PtInRect(&_leftBt, _cameraPtMouse) && _menuNum == THREE)
	{
		_menuNum = TWO;
		_objName = NONE;
	}
}

//��� ������Ʈ ����⸦ ���� ����
void mapTool::objDel()
{
	if (!_objDelOn) _objDelOn = true;
	else if (_objDelOn) _objDelOn = false;
}

//�̰� ������ Ÿ�Ϸ� �� ��ü�� ���� ä���ִ� ���
void mapTool::fill(int x, int y)
{
	for (int i = 0; i < TILEX* TILEY; ++i)
	{
		if (!_moveUnMove) _isoTile[i].MUM = MOVE;
		else  _isoTile[i].MUM = UNMOVE;
		_isoTile[i].fX = x;
		_isoTile[i].fY = y;
	}
}

//��� ��� ������Ʈ�� NONE���� ������ ��ġ �����Ȱ�ó�� �����ִ� ģ������
void mapTool::objDelAll()
{
	for (int i = 0; i < TILEX* TILEY; ++i)
	{
		_isoTile[i].name = NONE;
	}
	_playerTile = -1;
	_enemyTile = -1;
}

void mapTool::homeBt()
{
	SCENEMANAGER->changeScene("Ÿ��Ʋ��");
}