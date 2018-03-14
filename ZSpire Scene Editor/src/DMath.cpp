//#include "../stdafx.h"
typedef unsigned int uint;

#include "math.h"
#include "../includes/DMath.h"



float FastInvSqrt(float x) {
	float xhalf = 0.5f * x;
	int i = *(int*)&x;  
	i = 0x5f3759df - (i >> 1);  // What the fvck this ?
	x = *(float*)&i;
	x = x * (1.5f - (xhalf*x*x));
	return x;
}

double radians(float angle) {
	return angle * PI / 180;

}


bool isRectFullscreen(DRECT rect) {

	if (rect.x == 0 && rect.y == 0 && rect.width == 1 && rect.height == 1.0f) return true;
	return false;
}


Vector3 vCross(Vector3 v1, Vector3 v2)
{
	Vector3 out = Vector3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
	return out;
}

float getDistance(Vector3 v1, Vector3 v2) {
	return (float)(sqrt(fabs(v1.x - v2.x) * fabs(v1.x - v2.x) + fabs(v1.y - v2.y) * fabs(v1.y - v2.y) + fabs(v1.z - v2.z) * fabs(v1.z - v2.z)));
}

void vNormalize(Vector3* v)
{
	float sqr = v->x * v->x + v->y * v->y + v->z * v->z;
	if (REAL_NUM_EQ(sqr, 1) || REAL_NUM_EQ(sqr, 0))
		return;

	float invrt = 1.0f / (float)sqrt(sqr);

	v->x *= invrt;
	v->y *= invrt;
	v->z *= invrt;
}
Vector3 vNormalize(Vector3 v)
{
	Vector3 result;

	float sqr = v.x * v.x + v.y * v.y + v.z * v.z;
	if (REAL_NUM_EQ(sqr, 1) || REAL_NUM_EQ(sqr, 0))
		return v;

	float invrt = (float)(1.0f / sqrt(sqr));
	result.x *= invrt;
	result.y *= invrt;
	result.z *= invrt;
	return result;
}

Mat4x4 getIdentity() {
	Mat4x4 Ret;

	Ret.m[0][0] = 1; Ret.m[0][1] = 0; Ret.m[0][2] = 0; Ret.m[0][3] = 0;
	Ret.m[1][0] = 0; Ret.m[1][1] = 1; Ret.m[1][2] = 0; Ret.m[1][3] = 0;
	Ret.m[2][0] = 0; Ret.m[2][1] = 0; Ret.m[2][2] = 1; Ret.m[2][3] = 0;
	Ret.m[3][0] = 0; Ret.m[3][1] = 0; Ret.m[3][2] = 0; Ret.m[3][3] = 1;

	return Ret;
}

Mat4x4 matrixMM(Mat4x4 l, Mat4x4 r) {
	Mat4x4 Ret;
	for (uint i = 0; i < 4; i++) {
		for (uint b = 0; b < 4; b++) {
			Ret.m[i][b] = l.m[i][0] * r.m[0][b] +
				l.m[i][1] * r.m[1][b] +
				l.m[i][2] * r.m[2][b] +
				l.m[i][3] * r.m[3][b];

		}

	}
	return Ret;
}

inline Mat4x4 operator+(const Mat4x4& l, const Mat4x4& r)
{
	Mat4x4 Ret;
	Ret.m[0][0] = l.m[0][0] + r.m[0][0];  Ret.m[0][1] = l.m[0][1] + r.m[0][1];   Ret.m[0][2] = l.m[0][2] + r.m[0][2];  Ret.m[0][3] = l.m[0][3] + r.m[0][3];
	Ret.m[1][0] = l.m[1][0] + r.m[1][0];  Ret.m[1][1] = l.m[1][1] + r.m[1][1];   Ret.m[1][2] = l.m[1][2] + r.m[1][2];  Ret.m[1][3] = l.m[1][3] + r.m[1][3];
	Ret.m[2][0] = l.m[2][0] + r.m[2][0];  Ret.m[2][1] = l.m[2][1] + r.m[2][1];   Ret.m[2][2] = l.m[2][2] + r.m[2][2];  Ret.m[2][3] = l.m[2][3] + r.m[2][3];
	Ret.m[3][0] = l.m[3][0] + r.m[3][0];  Ret.m[3][1] = l.m[3][1] + r.m[3][1];   Ret.m[3][2] = l.m[3][2] + r.m[3][2];  Ret.m[3][3] = l.m[3][3] + r.m[3][3];

	return Ret;
}

inline Mat4x4 operator-(const Mat4x4& l, const Mat4x4& r)
{
	Mat4x4 Ret;
	Ret.m[0][0] = l.m[0][0] - r.m[0][0];  Ret.m[0][1] = l.m[0][1] - r.m[0][1];   Ret.m[0][2] = l.m[0][2] - r.m[0][2];  Ret.m[0][3] = l.m[0][3] - r.m[0][3];
	Ret.m[1][0] = l.m[1][0] - r.m[1][0];  Ret.m[1][1] = l.m[1][1] - r.m[1][1];   Ret.m[1][2] = l.m[1][2] - r.m[1][2];  Ret.m[1][3] = l.m[1][3] - r.m[1][3];
	Ret.m[2][0] = l.m[2][0] - r.m[2][0];  Ret.m[2][1] = l.m[2][1] - r.m[2][1];   Ret.m[2][2] = l.m[2][2] - r.m[2][2];  Ret.m[2][3] = l.m[2][3] - r.m[2][3];
	Ret.m[3][0] = l.m[3][0] - r.m[3][0];  Ret.m[3][1] = l.m[3][1] - r.m[3][1];   Ret.m[3][2] = l.m[3][2] - r.m[3][2];  Ret.m[3][3] = l.m[3][3] - r.m[3][3];

	return Ret;
}

float vDot(Vector3 v1, Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


Mat4x4 transpose(Mat4x4 original) {
	Mat4x4 result;
	result.m[0][0] = result.m[0][0];
	result.m[1][0] = result.m[0][1];
	result.m[2][0] = result.m[0][2];
	result.m[3][0] = result.m[0][3];

	result.m[0][1] = result.m[1][0];
	result.m[1][1] = result.m[1][1];
	result.m[2][1] = result.m[1][2];
	result.m[3][1] = result.m[1][3];

	result.m[0][2] = result.m[2][0];
	result.m[1][2] = result.m[2][1];
	result.m[2][2] = result.m[2][2];
	result.m[3][2] = result.m[2][3];

	result.m[3][0] = result.m[0][3];
	result.m[3][1] = result.m[1][3];
	result.m[3][2] = result.m[2][3];
	result.m[3][3] = result.m[3][3];
	return result;

}

Mat4x4 getFrustum(float fovy, float aspect, float zNear, float zFar) {
	Mat4x4 result;
	double range = tan(PI * (fovy / (2.0f * 180.f))) * zNear;
	double left = -range * aspect;
	double right = range * aspect;
	double bottom = -range;
	double top = range;

	result.m[0][0] = (2.0f * zNear) / (float)(right - left);
	result.m[1][1] = (2.0f * zNear) / (float)(top - bottom);
	result.m[2][2] = -(zFar + zNear) / (zFar - zNear);
	result.m[2][3] = -1.0f;
	result.m[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);


	return result;
}
Mat4x4 matrixOrthogonal(float left, float right, float bottom, float top)
{
	Mat4x4 out = getIdentity();
	out.m[0][0] = 2.0f / (right - left);
	out.m[1][1] = 2.0f / (top - bottom);
	out.m[2][2] = -1.0f;
	out.m[3][0] = -(right + left) / (right - left);
	out.m[3][1] = -(top + bottom) / (top - bottom);


	return out;
}
Mat4x4 matrixOrthogonalZ(float left, float right, float bottom, float top, float zNear, float zFar) {
	Mat4x4 out = getIdentity();
	out.m[0][0] = 2.0f / (right - left);
	out.m[1][1] = 2.0f / (top - bottom);
	
	out.m[2][2] = -1.0f / (zFar - zNear);
	out.m[3][2] = -zNear / (zFar - zNear);

	out.m[3][0] = -(right + left) / (right - left);
	out.m[3][1] = -(top + bottom) / (top - bottom);


	return out;
}

Mat4x4 getScale(float scaleX, float scaleY, float scaleZ) {

	Mat4x4 mat;

	mat.m[0][0] = scaleX; mat.m[0][1] = 0; mat.m[0][2] = 0; mat.m[0][3] = 0;
	mat.m[1][0] = 0; mat.m[1][1] = scaleY; mat.m[1][2] = 0; mat.m[1][3] = 0;
	mat.m[2][0] = 0; mat.m[2][1] = 0; mat.m[2][2] = scaleZ; mat.m[2][3] = 0;
	mat.m[3][0] = 0; mat.m[3][1] = 0; mat.m[3][2] = 0; mat.m[3][3] = 1;

	return mat;
}

Mat4x4 getTranslation(float trX, float trY, float trZ) {

	Mat4x4 mat;

	mat.m[0][0] = 1; mat.m[0][1] = 0; mat.m[0][2] = 0; mat.m[0][3] = 0;
	mat.m[1][0] = 0; mat.m[1][1] = 1; mat.m[1][2] = 0; mat.m[1][3] = 0;
	mat.m[2][0] = 0; mat.m[2][1] = 0; mat.m[2][2] = 1; mat.m[2][3] = 0;
	mat.m[3][0] = trX; mat.m[3][1] = trY; mat.m[3][2] = trZ; mat.m[3][3] = 1;

	return mat
		;
}
Mat4x4 getRotationX(float thetaN) {
	double theta = radians(thetaN);
	Mat4x4 mat;

	mat.m[0][0] = 1; mat.m[0][1] = 0;               mat.m[0][2] = 0;                mat.m[0][3] = 0;
	mat.m[1][0] = 0; mat.m[1][1] = (float)cos(theta);      mat.m[1][2] = (float)sin(theta) * -1;  mat.m[1][3] = 0;
	mat.m[2][0] = 0; mat.m[2][1] = (float)sin(theta);      mat.m[2][2] = (float)cos(theta);       mat.m[2][3] = 0;
	mat.m[3][0] = 0; mat.m[3][1] = 0;               mat.m[3][2] = 0;                mat.m[3][3] = 1;

	return mat;
}
Mat4x4 getRotationY(float thetaN) {
	double theta = radians(thetaN);
	Mat4x4 mat;

	mat.m[0][0] = (float)cos(theta);       mat.m[0][1] = 0;            mat.m[0][2] = (float)sin(theta);   mat.m[0][3] = 0;
	mat.m[1][0] = 0;                mat.m[1][1] = 1;            mat.m[1][2] = 0;            mat.m[1][3] = 0;
	mat.m[2][0] = (float)sin(theta) * -1;  mat.m[2][1] = 0;            mat.m[2][2] = (float)cos(theta);   mat.m[2][3] = 0;
	mat.m[3][0] = 0;                mat.m[3][1] = 0;            mat.m[3][2] = 0;            mat.m[3][3] = 1;

	return mat;
}

Mat4x4 getRotationZ(float thetaN) {
	double theta = radians(thetaN);
	Mat4x4 mat;

	mat.m[0][0] = (float)cos(theta);       mat.m[0][1] = (float)sin(theta) * -1;  mat.m[0][2] = 0;   mat.m[0][3] = 0;
	mat.m[1][0] = (float)sin(theta);       mat.m[1][1] = (float)cos(theta);       mat.m[1][2] = 0;   mat.m[1][3] = 0;
	mat.m[2][0] = 0;                mat.m[2][1] = 0;                mat.m[2][2] = 1;   mat.m[2][3] = 0;
	mat.m[3][0] = 0;                mat.m[3][1] = 0;                mat.m[3][2] = 0;   mat.m[3][3] = 1;

	return mat;
}


Mat4x4 matrixLookAt(Vector3 eye, Vector3 center, Vector3 up)
{
	Vector3 f = Vector3(center.x - eye.x, center.y - eye.y, center.z - eye.z);
	vNormalize(&f);

	Vector3 u;

	Vector3 s = vCross(f, up);
	vNormalize(&s);
	u = vCross(s, f);


	Mat4x4 out;
	out = getIdentity();
	out.m[0][0] = s.x;
	out.m[1][0] = s.y;
	out.m[2][0] = s.z;

	out.m[0][1] = u.x;
	out.m[1][1] = u.y;
	out.m[2][1] = u.z;

	out.m[0][2] = -f.x;
	out.m[1][2] = -f.y;
	out.m[2][2] = -f.z;

	out.m[3][0] = -vDot(s, eye);
	out.m[3][1] = -vDot(u, eye);
	out.m[3][2] = vDot(f, eye);

	return out;
}



uint getCountsOfDigits(int number) {
	int count = (number == 0) ? 1 : 0;
	while (number != 0) {
		count++;
		number /= 10;
	}
	return count;
}



void QuaternionToMatrix(Mat4x4* result, const AnimQuaternion quat)
{
	result->m[0][0] = 1.0f - 2.0f * (quat.y * quat.y + quat.z * quat.z);
	result->m[0][1] = 2.0f * (quat.x * quat.y - quat.z * quat.w);
	result->m[0][2] = 2.0f * (quat.x * quat.z + quat.y * quat.w);

	result->m[1][0] = 2.0f * (quat.x * quat.y + quat.z * quat.w);
	result->m[1][1] = 1.0f - 2.0f * (quat.x * quat.x + quat.z * quat.z);
	result->m[1][2] = 2.0f * (quat.y * quat.z - quat.x * quat.w);

	result->m[2][0] = 2.0f * (quat.x * quat.z - quat.y * quat.w);
	result->m[2][1] = 2.0f * (quat.y * quat.z + quat.x * quat.w);
	result->m[2][2] = 1.0f - 2.0f * (quat.x * quat.x + quat.y * quat.y);
}

void QuatNormalize(AnimQuaternion in, AnimQuaternion* out) {
	const float mag = in.x * in.x + in.y * in.y + in.z * in.z + in.w * in.w;
	if (mag)
	{
		out->x /= mag;
		out->y /= mag;
		out->z /= mag;
		out->w /= mag;
		out->time = in.time;
	}
}

void QuatInterpolate(AnimQuaternion* pOut, const AnimQuaternion pStart, const AnimQuaternion pEnd, float pFactor)
{
	// calc cosine theta
	float cosom = pStart.x * pEnd.x + pStart.y * pEnd.y + pStart.z * pEnd.z + pStart.w * pEnd.w;

	// adjust signs (if necessary)
	AnimQuaternion end = pEnd;
	if (cosom < 0.0f)
	{
		cosom = -cosom;
		end.x = -end.x;   // Reverse all signs
		end.y = -end.y;
		end.z = -end.z;
		end.w = -end.w;
	}

	// Calculate coefficients
	float sclp, sclq;
	if ((1.0f - cosom) > 0.0001f) // 0.0001 -> some epsillon
	{
		// Standard case (slerp)
		float omega, sinom;
		omega = (float)acos(cosom); // extract theta from dot product's cos theta
		sinom = (float)sin(omega);
		sclp = (float)sin((1.0f - pFactor) * omega) / sinom;
		sclq = (float)sin(pFactor * omega) / sinom;
	}
	else
	{
		// Very close, do linear interp (because it's faster)
		sclp = 1.0f - pFactor;
		sclq = pFactor;
	}

	pOut->x = sclp * pStart.x + sclq * end.x;
	pOut->y = sclp * pStart.y + sclq * end.y;
	pOut->z = sclp * pStart.z + sclq * end.z;
	pOut->w = sclp * pStart.w + sclq * end.w;
}

Vector3 getFrontLook(float pitch, float yaw) {
	Vector3 result;

	result.x = (float)(cos(radians(yaw)) * cos(radians(pitch)));
	result.y = (float)sin(radians(pitch));
	result.z = (float)(sin(radians(yaw)) * cos(radians(pitch)));
	return result;
}

Vector3 getDirection(float pitch, float yaw,float roll) {
	Vector3 q;
	
	double cy = cos(radians(yaw * 0.5f));
	double sy = sin(radians(yaw * 0.5f));
	double cr = cos(radians(roll * 0.5f));
	double sr = sin(radians(roll * 0.5f));
	double cp = cos(radians(pitch * 0.5f));
	double sp = sin(radians(pitch * 0.5f));


	q.z = (float)(cy * sr * cp - sy * cr * sp);
	q.x = (float)(cy * cr * sp + sy * sr * cp);
	q.y = (float)(sy * cr * cp - cy * sr * sp);


	return q;
}

Mat4x4 removeTranslationFromViewMat(Mat4x4 viewMat) {

	Mat4x4 result = viewMat;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;

	return result;
}

Mat4x4 removeRotation(Mat4x4 transform, Mat4x4 view) {
	Mat4x4 result = transform;

	result.m[0][0] = view.m[0][0];
	result.m[0][1] = view.m[1][0];
	result.m[0][2] = view.m[2][0];

	result.m[1][0] = view.m[0][1];
	result.m[1][1] = view.m[1][1];
	result.m[1][2] = view.m[2][1];

	result.m[2][0] = view.m[0][2];
	result.m[2][1] = view.m[1][2];
	result.m[2][2] = view.m[2][2];

	return result;
}