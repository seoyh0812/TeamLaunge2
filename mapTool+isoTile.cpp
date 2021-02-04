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
			if(_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE) _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = MOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_moveUnMove && _tempTile.fX >= 0 && _tempTile.fY >= 0 && _menuNum == ONE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fX = _tempTile.fX;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fY = _tempTile.fY;
			if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE) _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
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

//�巡���Ҷ� ���� ���� ���� �����ص�
void mapTool::tempDrag()
{
	_dragX = _cameraPtMouse.x;
	_dragY = _cameraPtMouse.y;
}

//�巡�� ������ ����Ʈ ĥ���ִ±��
void mapTool::dragPaint()
{
	_dragRc = RectMake(_dragX, _dragY, _cameraPtMouse.x - _dragX, _cameraPtMouse.y - _dragY);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (PtInRect(&_dragRc, _isoTile[i].pt))
		{
			if (!_moveUnMove && _tempTile.fX >= 0 && _tempTile.fY >= 0 && _menuNum == ONE)
			{//�𹫺� Ÿ�� off�� ����Ÿ�Ϸ� �����
				_isoTile[i].fX = _tempTile.fX;
				_isoTile[i].fY = _tempTile.fY;
				_isoTile[i].MUM = MOVE;
				InvalidateRect(_hWnd, NULL, false);
			}
			else if (_moveUnMove && _tempTile.fX >= 0 && _tempTile.fY >= 0 && _menuNum == ONE)
			{//�𹫺� Ÿ�� on�̸� �𹫺�Ÿ�Ϸ� �����
				_isoTile[i].fX = _tempTile.fX;
				_isoTile[i].fY = _tempTile.fY;
				_isoTile[i].MUM = UNMOVE;
				InvalidateRect(_hWnd, NULL, false);
			}
			else if (_tempTile.fX >= 0 && _tempTile.fY >= 0 && !_objDelOn && _menuNum == TWO && _objName != PLAYERFLAG && _objName != ENEMYFLAG)
			{//obj del ������ ���¿��� ������Ʈ�� �巡�׷� �׸��� ����
				if (_isoTile[i].name != PLAYERFLAG && _isoTile[i].name != ENEMYFLAG) _isoTile[i].name = _objName; //����� ����, ���� ����ó�� ����
				_isoTile[i].MUM = UNMOVE;
				InvalidateRect(_hWnd, NULL, false);
			}
			else if (_tempTile.fX >= 0 && _tempTile.fY >= 0 && !_objDelOn && _menuNum == THREE && _objName != PLAYERFLAG && _objName != ENEMYFLAG)
			{//obj del ������ ���¿��� �� ������ �巡�׷� �׸��� ����
				if (_isoTile[i].name != PLAYERFLAG && _isoTile[i].name != ENEMYFLAG) _isoTile[i].name = _objName; //����� ����, ���� ����ó�� ����
				_isoTile[i].MUM = MOVE;
				InvalidateRect(_hWnd, NULL, false);
			}
			else if (_tempTile.fX >= 0 && _tempTile.fY >= 0 && _objDelOn)
			{//obj del ���������� Ÿ���� �Ȱǵ�� ������Ʈ �ʱ�ȭ �� ����Ÿ�Ϸ� �ʱ�ȭ
				_isoTile[i].MUM = MOVE;
				_isoTile[i].name = NONE;
				InvalidateRect(_hWnd, NULL, false);
			}
		}
	}
}