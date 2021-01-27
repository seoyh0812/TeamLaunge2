#include "stdafx.h"
#include "mapTool.h"

//��� ���콺�� ������Ʈ�� ���÷�Ʈ�� �浹 + � �޴��� �����ִ��� �˻��ؼ� ������� �ִ°ſ���
void mapTool::ptInObj()
{
	if (PtInRect(&_tree1, _cameraPtMouse) && _menuNum == TWO)	_objName = TREE1;
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
		else if (_objName == ZERGLING && !_objDelOn)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name = ZERGLING;
			InvalidateRect(_hWnd, NULL, false);
		}
	}
}