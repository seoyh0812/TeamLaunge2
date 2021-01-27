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
	else if (PtInRect(&_icZergling, _cameraPtMouse) && _menuNum == THREE)	_objName = ZERGLING;
}

//��� ���õ� ������Ʈ�� ����� �Ǵ��ؼ� ������ Ÿ�Ͽ� �� ������Ʈ ���� �ο����ִ°̴ϴ�
void mapTool::createObj()
{
	//���⼭ ���� ��Ƶ� ������Ʈ �̸��� �ο��ؼ� Ÿ������ �����߰��Ҳ���
	if (!_menuInPt)
	{
		if (_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = NONE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE1 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE1;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE2 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE2;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE3 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE3;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE4 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE4;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == TREE5 && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = TREE5;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_objName == ZERGLING && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = ZERGLING;
			InvalidateRect(_hWnd, NULL, false);
		}
	}
}