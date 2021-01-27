#include "stdafx.h"
#include "mapTool.h"

//�̰ɷ� isoTile ���� ���ÿ��� �Է¹ް� ���ʿ� �׸��°ſ���
void mapTool::createTile()
{
	if (!_menuInPt && !_objDelOn)
	{
		if (!_moveUnMove && _tempTile.fX >= 0 && _tempTile.fY >= 0 && _menuNum == ONE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fX = _tempTile.fX;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fY = _tempTile.fY;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = MOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_moveUnMove && _tempTile.fX >= 0 && _tempTile.fY >= 0 && _menuNum == ONE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fX = _tempTile.fX;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fY = _tempTile.fY;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
	}
}

void mapTool::sampleInTemp()
{
	//�̺κ����� �޴� �ѱ�ڿ� Ÿ�ϱ׷����°� ������
	if (_brushOn && _menuNum == ONE)
	{
		//���ο� Ÿ���� �������!!
		for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
		{
			if (PtInRect(&_sample[i].rc, _cameraPtMouse))
			{
				_tempTile.fX = _sample[i].fX;
				_tempTile.fY = _sample[i].fY;
				return;
			}
		}
	}
	//else
	//{
	//	_tempTile.fX = -1;
	//	_tempTile.fY = -1;
	//	return;
	//}
}

//�̰� ���콺�� ���̼�Ÿ�Ͼȿ� ������ Ȯ�����ִ°� �׷��� ���� ���콺�� ���Ÿ�Ͽ��ִ� ����ٶ� ������ ����
void mapTool::ptInIso()
{
	//���콺����Ʈ�� ���̼�Ÿ�Ͼȿ� ���Դ��� Ȯ������
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (i == _pickingPt.y * TILEX + _pickingPt.x)
		{
			_isoTile[i].inRect = true;
		}
		else _isoTile[i].inRect = false;
	}
}

//�̰� ������ isoTile ������ ������ִ� ����̿��� (init)
void mapTool::createSampleTiles()
{
	for (int i = 0; i < SAMPLEY; ++i)
	{
		for (int j = 0; j < SAMPLEX; ++j)
		{
			//�̰� ������ ��ġ�� �����صδ°� �׷��� ���° Ÿ������ �˰� ������ ��������
			_sample[i * SAMPLEX + j].fX = j;
			_sample[i * SAMPLEX + j].fY = i;

			_sample[i * SAMPLEX + j].rc = RectMake((WINSIZEX - 512) + (j*TILESIZEX), 0 + (i*TILESIZEY), TILESIZEX, TILESIZEY);
		}
	}
}