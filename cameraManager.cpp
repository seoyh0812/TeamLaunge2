#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	cameraLocation.x = cameraLocation.y = minimapHeight = minimapWidth = rangeX1 = rangeY1 = 0;
	rangeX2 = MAPSIZEX;	rangeY2 = MAPSIZEY;
	cameraLocked = false;

	return S_OK;
}

void cameraManager::release()
{
}


// (�ʿ�� �� ��) ī�޶� x�� �ٲ���(������)
void cameraManager::setCameraX(long x)
{
	if (cameraLocked) return;
	cameraLocation.x = x; 
}
// (�ʿ�� �� ��) ī�޶� y�� �ٲ���(������)
void cameraManager::setCameraY(long y)
{
	if (cameraLocked) return;
	cameraLocation.y = y; 
}

// ī�޶� ���� ������ ���� (����̹����� ���缭) setCameraRange(x��ǥ, y��ǥ)
// ..�� ��������µ� ��� stdafx.h �����ι����� �Է¹ް� �س���
// setCameraRange �Լ� ���� �� �����ص� �˴ϴ�. 
void cameraManager::setCameraRange(int x, int y)
{
	rangeX1 = 0; rangeX2 = x; rangeY1 = 0;  rangeY2 = y;
	//gameNode::setBackBuffer(x, y);
}

// ī�޶� ���� ������ ���� (����̹����� ���缭) setCameraRange(x������ǥ, y������ǥ, x����ǥ, y����ǥ)
void cameraManager::setCameraRange(int x1, int y1, int x2, int y2)
{
	rangeX1 = x1; rangeX2 = x2; rangeY1 = y1;  rangeY2 = y2;
}

// ī�޶� ���� ������ ���� (����̹����� ���缭) setCameraRange(�̹���������)
void cameraManager::setCameraRange(image * image)
{
	rangeX1 = 0; rangeX2 = image->getWidth(); rangeY1 = 0;  rangeY2 = image->getHeight();
}

// focusOnRect(RECT, xȭ���� n����1 �������� �;� ��ũ������, yȭ���� n����1 �������� �;� ��ũ������)
void cameraManager::focusOnRect(RECT & rc, int x, int y)
{
	if (cameraLocked) return; // ������� �������� �ʽ��ϴ�.
	if (x < 2) x = 2; // �������� ���� �� �־����� �˾Ƽ� 2�� �ٲ���
	if (y < 2) y = 2; // �������� ���� �� �־����� �˾Ƽ� 2�� �ٲ���
	// rc�� x������ ī�޶�+��������/x���� ������� �������� ī�޶� �̵�
	if ((rc.left + rc.right) / 2 <= cameraLocation.x + WINSIZEX / x)
	{ // ��ġ 10�� ������ �����ص� �˴ϴ�.
		cameraLocation.x -= 10;
		if (cameraLocation.x < (rc.left + rc.right) / 2 - WINSIZEX / x)
		{
			cameraLocation.x = (rc.left + rc.right) / 2 - WINSIZEX / x;
		}
	}
	// rc�� x������ ī�޶�+(x-1)*��������/x���� ū��� ���������� ī�޶� �̵�
	if ((rc.left + rc.right) / 2 >= cameraLocation.x + WINSIZEX - WINSIZEX / x)
	{
		cameraLocation.x += 10;
		if (cameraLocation.x > (rc.left + rc.right) / 2 - WINSIZEX + WINSIZEX / x)
		{
			cameraLocation.x = (rc.left + rc.right) / 2 - WINSIZEX + WINSIZEX / x;
		}
	}
	// rc�� y������ ī�޶�+��������/y���� ������� �������� ī�޶� �̵�
	if ((rc.top + rc.bottom) / 2 <= cameraLocation.y + WINSIZEY / y)
	{
		cameraLocation.y -= 10;
		if (cameraLocation.y < (rc.top + rc.bottom) / 2 - WINSIZEY / y)
		{
			cameraLocation.y = (rc.top + rc.bottom) / 2 - WINSIZEY / y;
		}
	}
	// rc�� y������ ī�޶�+(y-1)*��������/y���� ū��� �Ʒ������� ī�޶� �̵�
	if ((rc.top + rc.bottom) / 2 >= cameraLocation.y + WINSIZEY - WINSIZEY / y)
	{
		cameraLocation.y += 10;
		if (cameraLocation.y > (rc.top + rc.bottom) / 2 - WINSIZEY + WINSIZEY / y)
		{
			cameraLocation.y = (rc.top + rc.bottom) / 2 - WINSIZEY + WINSIZEY / y;
		}
	}

	if (cameraLocation.x < rangeX1) cameraLocation.x = rangeX1;
	if (cameraLocation.y < rangeY1) cameraLocation.y = rangeY1;
	if (cameraLocation.x > rangeX2 - WINSIZEX) cameraLocation.x = rangeX2 - WINSIZEX;
	if (cameraLocation.y > rangeY2 - WINSIZEY) cameraLocation.y = rangeY2 - WINSIZEY; // ����ó��
}


// �̴ϸ� Ʋ�� �׸��� �Լ� minimap(hdc, ������ x��ǥ, y��ǥ, ��, ����)
void cameraManager::minimap(HDC hdc, int x, int y, int width, int height, bool standardMap)
{
	minimapX = cameraLocation.x + x;
	minimapY = cameraLocation.y + y;
	minimapWidth = width;
	minimapHeight = height;
	Rectangle(hdc, minimapX, minimapY, minimapX + minimapWidth, minimapY + minimapHeight);
	minimapBaseOnTotalMap = standardMap;
}

// ������ �̴ϸʿ� ������Ʈ�� �߰� minimapObject(hdc, RECT)
int cameraManager::minimapObject(HDC hdc, RECT & rc)
{
	if (minimapHeight == 0 || minimapWidth == 0) return 0; // Ʋ�� �� ��������ٸ� �������
	if (minimapBaseOnTotalMap)// �̴ϸ��� ��ü �� �����̸�
	{
		if (rc.left < -5 || rc.right > MAPSIZEX + 5 ||
			rc.top < -5 || rc.bottom > MAPSIZEY + 5) return 0; // �ʹ� ����� �� �׷���
		//���̴� �� ���̹Ƿ� ���� ����
		Rectangle(hdc, minimapX + rc.left*minimapWidth / MAPSIZEX,
			minimapY + rc.top*minimapHeight / MAPSIZEY,
			minimapX + rc.right*minimapWidth / MAPSIZEX,
			minimapY + rc.bottom*minimapHeight / MAPSIZEY);
	}
	else  // �̴ϸ��� ������â �����̸�
	{
		if (rc.left < cameraLocation.x - 5 || rc.right > cameraLocation.x + WINSIZEX + 5 ||
			rc.top < cameraLocation.y - 5 || rc.bottom > cameraLocation.y + WINSIZEY + 5) return 0; // �ʹ� ����� �� �׷���
		//���̴� �� ���̹Ƿ� ���� ����
		Rectangle(hdc, minimapX + (rc.left - cameraLocation.x)*minimapWidth / WINSIZEX,
			minimapY + (rc.top - cameraLocation.y)*minimapHeight / WINSIZEY,
			minimapX + (rc.right - cameraLocation.x)*minimapWidth / WINSIZEX,
			minimapY + (rc.bottom - cameraLocation.y)*minimapHeight / WINSIZEY);
	}
}

// vibrate(�Ը�)
void cameraManager::vibrate(int magnitude)
{
	cameraLocation.x += rand() % (2 * magnitude + 1) - magnitude; // -mag~+mag����
	cameraLocation.y += rand() % (2 * magnitude + 1) - magnitude; // �����ϰ� �̵�
	if (cameraLocation.x < 0) cameraLocation.x = 0;
	if (cameraLocation.x > rangeX2 - WINSIZEX) cameraLocation.x = rangeX2 - WINSIZEX;
	if (cameraLocation.y < 0) cameraLocation.y = 0;
	if (cameraLocation.y > rangeY2 - WINSIZEY) cameraLocation.y = rangeY2 - WINSIZEY; // ����ó��
}
