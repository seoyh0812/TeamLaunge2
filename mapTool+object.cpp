#include "stdafx.h"
#include "mapTool.h"

//��� ���콺�� ������Ʈ�� ���÷�Ʈ�� �浹 + � �޴��� �����ִ��� �˻��ؼ� ������� �ִ°ſ���
void mapTool::ptInObj()
{
	if (PtInRect(&_tree1, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE1;
	else if (PtInRect(&_tree2, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE2;
	else if (PtInRect(&_tree3, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE3;
	else if (PtInRect(&_tree4, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE4;
	else if (PtInRect(&_tree5, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE5;
	else if (PtInRect(&_playerFlagRc, _cameraPtMouse) && _menuNum == TWO)	_objName = PLAYERFLAG;
	else if (PtInRect(&_enemyFlagRc, _cameraPtMouse) && _menuNum == TWO)	_objName = ENEMYFLAG;
	else if (PtInRect(&_icZergling, _cameraPtMouse) && _menuNum == THREE)	_objName = ZERGLING;
	else if (PtInRect(&_icMarine, _cameraPtMouse) && _menuNum == THREE)		_objName = MARINE;
	else if (PtInRect(&_icCivilian, _cameraPtMouse) && _menuNum == THREE)	_objName = CIVILIAN;
	else if (PtInRect(&_icTemplar, _cameraPtMouse) && _menuNum == THREE)	_objName = TEMPLAR;
	else if (PtInRect(&_icBishop, _cameraPtMouse) && _menuNum == THREE)		_objName = BISHOP;
	else if (PtInRect(&_icDiablo, _cameraPtMouse) && _menuNum == THREE)		_objName = DIABLO;
	else if (PtInRect(&_icSkeleton, _cameraPtMouse) && _menuNum == THREE)	_objName = SKELETON;
	else if (PtInRect(&_icGhost, _cameraPtMouse) && _menuNum == THREE)		_objName = GHOST;
}

//��� ���õ� ������Ʈ�� ����� �Ǵ��ؼ� ������ Ÿ�Ͽ� �� ������Ʈ ���� �ο����ִ°̴ϴ�
void mapTool::createObj()
{
	//���⼭ ���� ��Ƶ� ������Ʈ �̸��� �ο��ؼ� Ÿ������ �����߰��Ҳ���
	if (!_menuInPt)
	{
		if (_objDelOn)
		{
			if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == PLAYERFLAG) _playerTile = -1;
			if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == ENEMYFLAG) _enemyTile = -1;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = NONE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE1 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE1;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE2 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE2;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE3 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE3;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE4 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE4;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE5 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE5;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == PLAYERFLAG && !_objDelOn)
		{
			_isoTile[_playerTile].name = NONE;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = PLAYERFLAG;
			_playerTile = _pickingPt.y * TILEX + _pickingPt.x;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == ENEMYFLAG && !_objDelOn)
		{
			_isoTile[_enemyTile].name = NONE;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = ENEMYFLAG;
			_enemyTile = _pickingPt.y * TILEX + _pickingPt.x;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == ZERGLING && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = ZERGLING;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == MARINE && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = MARINE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == CIVILIAN && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = CIVILIAN;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TEMPLAR && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TEMPLAR;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == BISHOP && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = BISHOP;
			InvalidateRect(_hWnd, NULL, false);
		}
		//�̹��������� ����
		//else if (_objName == DIABLO && !_objDelOn)
		//{
		//	_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = DIABLO;
		//	InvalidateRect(_hWnd, NULL, false);
		//}
		//else if (_objName == SKELETON && !_objDelOn)
		//{
		//	_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = SKELETON;
		//	InvalidateRect(_hWnd, NULL, false);
		//}
		else if (_objName == GHOST && !_objDelOn && _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM != UNMOVE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = GHOST;
			InvalidateRect(_hWnd, NULL, false);
		}
	}
}