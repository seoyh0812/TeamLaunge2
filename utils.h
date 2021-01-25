#pragma once

#define PI 3.14159f
#define PI2 PI * 2

#define PI4 float(PI / 4.0f)
#define PI8 float(PI / 8.0f)
#define PI16 float(PI / 16.0f)
#define PI32 float(PI / 32.0f)
#define PI64 float(PI / 64.0f)
#define PI128 float(PI / 128.0f)

#define FLOAT_EPSILON 0.001f //�Ǽ��� ���� ���� ������� �ϴ� �׸��� �ε� �Ǽ��񱳸� ���ؼ� ��
#define FLOAT_TO_INT(f1) static_cast<int>(f1 + FLOAT_EPSILON)
#define FLOAT_EQUAL(f1, f2) (fabs(f1, f2) <= FLOAT_EPSILON)

namespace TFIVE_UTIL
{
	float getDistance(float x1, float y1, float x2, float y2);

	float getAngle(float x1, float y1, float x2, float y2);


}