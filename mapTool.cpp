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
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	createSampleTiles();

	createIsoMap(TILEX, TILEY);
	_tempTile.fX = 0;
	_tempTile.fY = 0;
	_pickingPt = { 0,0 };
	_moveUnMove = false;
	_brushOn = false;
	_rs = MAX;
	_menuNum = ONE;
	_objName = NONE;
	_objDelOn = false;
	_menuInPt = false;
	return S_OK;
}

void mapTool::release()
{
}

//�׷��� ���� x, �׷��� ���� y, TILEX �ֱ�, TILEY �ֱ�
void mapTool::createIsoMap(int tileX, int tileY)
{

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
			_isoTile[i * tileX + j].name = NONE;

			_isoTile[i * tileX + j].centerX = TILESIZEX * (TILEX + (j - i))/2;
			_isoTile[i * tileX + j].centerY = TILESIZEY * (i + j + 1) / 2;

			_isoTile[i * tileX + j].drawX = _isoTile[i * tileX + j].centerX - TILESIZEX / 2;
			_isoTile[i * tileX + j].drawY = _isoTile[i * tileX + j].centerY - TILESIZEY / 2;
		}
	}
}


void mapTool::update()
{
	_pickingPt = picking(_cameraPtMouse.x, _cameraPtMouse.y);
	cameraControl();
	imageInit();
	menuInPt();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_undo, _cameraPtMouse)) tempLoad();
		tempSave();
		if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createTile();
		sampleInTemp();
		save();
		load();
		moveUnMove();
		if (PtInRect(&_fill, _cameraPtMouse) && _tempTile.fX >= 0 && _tempTile.fY >= 0) fill(_tempTile.fX, _tempTile.fY);
		openClose();
		renderSize();
		if (_brushOn) leftRightBt();
		ptInObj();
		if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createObj();
		if (PtInRect(&_objDel, _cameraPtMouse)) objDel();
		if (PtInRect(&_delAll, _cameraPtMouse)) objDelAll();
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createTile();
		ptInObj();
		if (_pickingPt.x >= 0 && _pickingPt.y >= 0) createObj();
	}
	ptInIso();
	if (KEYMANAGER->isOnceKeyDown(VK_F4)) SCENEMANAGER->changeScene("���ξ�");
}

void mapTool::render()
{
	imageRender();

	//�Ʒ��� ���ǻ� ���� ���ں��̰��ϴ°�
	char str[256];
	sprintf_s(str, "TempTile X : %d , Y : %d", _tempTile.fX, _tempTile.fY);
	TextOut(getMemDC(), CAMX, CAMY+70, str, strlen(str));

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		sprintf_s(str, "%d, %d", _isoTile[i].nX, _isoTile[i].nY);
		if (KEYMANAGER->isToggleKey(VK_F1)) TextOut(getMemDC(), CAMX+ _isoTile[i].drawX + TILEX, CAMY+_isoTile[i].drawY + (TILEY / 2), str, strlen(str));
	}

	sprintf_s(str, "ptMouse X : %d , Y : %d", CAMX + _cameraPtMouse.x, CAMY + _cameraPtMouse.y);
	TextOut(getMemDC(), CAMX+ 150, CAMY+ 70, str, strlen(str));
}

inline POINT mapTool::picking(long x, long y)
{ // �̰� ��ŷ
	int xx; int yy;
	if (2 * y < (x - 960))	return { -1,0 }; // y=1/2x���� �����ִ��� (�ʹ� ���)
	if (2 * y < -(x - 960))	return { -1,0 }; // y=-1/2x���� �����ִ��� (�ʹ� ���)
	//-1�̸� ����ó����(Ű�Ŵ��� L��ư ����)

	// �� y=1/2x�� �ƴ϶� 2y=x�� ��ĸ� ������������ �����⶧���� �̷��� ������.
	// 320�� TILEWIDTH * TILEX / 2 (=����ü ����ũ���� ���ݰ�)�� ������ ���ϸ� ���̱� ���� ����ϰ� ��������

	 // 64�� Ÿ�� ����(TILEHEIGHT)�� �纯 2���Ѱ��̸� �̸�ŭ�� �̰ݵ�(�����ΰ�) �����̶� ���� ��
	xx = (2 * y + (x - 960)) / 64; // y������ �̿��� ������� �ٲپ���
	if (xx > 29) return { -1,0 }; // �ʹ� ����Ÿ� ����ó��

	yy = (2 * y - (x - 960)) / 64; // ���⸸ ������ ������ ��
	if (yy > 29) return { -1,0 };

	return { xx , yy };
}