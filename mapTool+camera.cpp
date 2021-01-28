#include "stdafx.h"
#include "mapTool.h"

//�̰� ī�޶� �������ִ� �κ� -> ���� : ī�޶�� �÷��̱׶��忡 ����ī�޶� �̿��ϱ������
void mapTool::cameraControl()
{
	_cameraPtMouse.x = _ptMouse.x + CAMX;
	_cameraPtMouse.y = _ptMouse.y + CAMY;
	sampleTileMove();
}

//�̰� ȭ���� �����ӿ����� ���� ���������ϴ� ����Ÿ���� ������
void mapTool::sampleTileMove()
{
	for (int i = 0; i < SAMPLEY; ++i)
	{
		for (int j = 0; j < SAMPLEX; ++j)
		{
			_sample[i * SAMPLEX + j].rc = RectMake((WINSIZEX + CAMX - 512) + (j*TILESIZEX), CAMY + (i*TILESIZEY), TILESIZEX, TILESIZEY);
		}
	}
}