#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	POINT cameraLocation;

	bool minimapBaseOnTotalMap;
	// �̴ϸ��� ��ü�ʱ��������ϸ� true, ������â �������� �ϸ� false(minimap�Լ����� ����)

	int vibrationCount;
	int count;

	float rangeX1;	float rangeX2;
	float rangeY1;	float rangeY2;

	float minimapX;	float minimapY;
	float minimapHeight;
	float minimapWidth;

	bool cameraLocked; // ī�޶� �����ƴ���

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();

	// ī�޶� x�� ī�޶� y(������).. CAMX, CAMY�� �������ؼ� ��
	long getCameraX() { return cameraLocation.x; }
	long getCameraY() { return cameraLocation.y; }

	// ī�޶� x�� y�� �ٲ���(������)
	void setCameraX(long x);
	void setCameraY(long y);

	// ī�޶� ���� ������ ���� (����̹����� ���缭) setCameraRange(x��ǥ, y��ǥ)
	// ..�� ��������µ� ��� stdafx.h �����ι����� �Է¹ް� �س���
	// setCameraRange �Լ� ���� �� �����ص� �˴ϴ�. 
	void setCameraRange(int x, int y); // 0,0���� x,y

	// �����ũ�⵵ �̿� �����ְ������ ���ϴ���... (�����Ͽ� �����Ͻ�)

	// ī�޶� ���� ������ ���� (����̹����� ���缭) setCameraRange(x������ǥ, y������ǥ, x����ǥ, y����ǥ)
	void setCameraRange(int x1, int y1, int x2, int y2); // x1,y1���� x2,y2

	// ī�޶� ���� ������ ���� (����̹����� ���缭) setCameraRange(�̹���������)
	void setCameraRange(image * image);

	// focusOnRect(RECT, xȭ���� n����1 �������� �;� ��ũ������, yȭ���� n����1 �������� �;� ��ũ������)
	void focusOnRect(RECT &rc, int x = 2, int y = 2);

	// �̴ϸ� ��ü�� �׸��� �Լ� minimap(hdc, ������ x��ǥ, y��ǥ, ��, ����, ��ü�ʱ������� ���� ���� �ƴϸ� ������â����)
	void minimap(HDC hdc, int x, int y, int width, int height, bool standardMap = false);

	// ������ �̴ϸʿ� ������ ������Ʈ�� �߰� minimapObject(hdc, RECT)
	int minimapObject(HDC hdc, RECT & rc);

	// vibrate(�Ը�) �Ը� ���� ���ص� ��(�⺻��10)
	void vibrate(int magnitude = 10);

	// ī�޶� �� ���� �Լ�
	bool getCameraLock() { return cameraLocked; }
	void cameraLock() { cameraLocked = true; } // ī�޶� ��� �����Դϴ�.
	void cameraLockOff() { cameraLocked = false; }
};

