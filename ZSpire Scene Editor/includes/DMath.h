///#pragma once
/*
    Pershades 2017
    DMath.h file

*/

#define PI 3.1415926
#define PI_OVER_360 3.1415926 / 360

#define REAL_NUM_EQ(x, y) (fabs((x) - (y)) < 0.000001)

float FastInvSqrt(float x);

double radians(float angle);

struct DRECT {

	float x;
	float y;
	float width;
	float height;

	DRECT(float x, float y, float width, float height){
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};
bool isRectFullscreen(DRECT rect);

struct DSDKVector3 {
	float x = 0;
	float y = 0;
	float z = 0;




	DSDKVector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

};

struct Vector3{

float x = 0;
float y = 0;
float z = 0;


Vector3(float x, float y, float z){
this->x = x;
this->y = y;
this->z = z;
}
Vector3() {
}
};



Vector3 vCross(Vector3 v1, Vector3 v2);
Vector3 vNormalize(Vector3 v);
void vNormalize(Vector3* v);

struct Vector2{
    
    float x = 0;
    float y = 0;
    
    
    Vector2(){
    }
    
    Vector2(float x, float y){
    this->x = x;
    this->y = y;
    }
    
    };

struct Vertex{

	Vector3 pos;

	Vector2 uv;

	Vector3 normal;

	Vector3 tangent;

	Vector3 bitangent;

    uint boneID[12];
    float weight[12];
    
	Vertex(){}
    Vertex(Vector3 pos, Vector2 uv){
        this->pos.x = pos.x;
        this->pos.y = pos.y;
        this->pos.z = pos.z;

        this->uv.x= uv.x;
       this->uv.y = uv.y;

    }
    Vertex(Vector3 pos, Vector2 uv, Vector3 norm){
		this->pos.x = pos.x;
		this->pos.y = pos.y;
		this->pos.z = pos.z;

        this->uv.x = uv.x;
       this->uv.y = uv.y;

       this->normal.x = norm.x;
       this->normal.y = norm.y;
       this->normal.z = norm.z;

    }

  Vertex(Vector3 pos, Vector2 uv, Vector3 norm, Vector3 tangent, Vector3 bitangent){
	  this->pos.x = pos.x;
	  this->pos.y = pos.y;
	  this->pos.z = pos.z;

        this->uv.x = uv.x;
       this->uv.y = uv.y;

       this->normal.x = norm.x;
       this->normal.y = norm.y;
       this->normal.z = norm.z;

        this->tangent.x = tangent.x;
        this->tangent.y = tangent.y;
        this->tangent.z = tangent.z;

        this->bitangent.x = bitangent.x;
        this->bitangent.y = bitangent.y;
        this->bitangent.z= bitangent.z;
    }
};
struct Vector4{
    
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;
    
    Vector4(){
    }
    
    Vector4(float x, float y, float z, float w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    }
    
    };
    
struct AnimVec3 {

	float x;
	float y;
	float z;
	float time;

};
struct AnimQuaternion {
	float x;
	float y;
	float z;
	float w;
	float time;
	AnimQuaternion(float x, float y, float z,float w, float time) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		this->time = time;
	}
	AnimQuaternion() {}
};


struct Mat4x4{
    float m[4][4];

    Mat4x4 (Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4){
        m[0][0] = v1.x; m[0][1] = v1.y; m[0][2] = v1.z; m[0][3] = v1.w;
        m[1][0] = v2.x; m[1][1] = v2.y; m[1][2] = v2.z; m[1][3] = v2.w;
        m[2][0] = v3.x; m[2][1] = v3.y; m[2][2] = v3.z; m[2][3] = v3.w;
        m[3][0] = v4.x; m[3][1] = v4.y; m[3][2] = v4.z; m[3][3] = v4.w;


    }
    Mat4x4(){
        for (uint i = 0; i < 4; i ++){
            for(uint j = 0; j < 4; j++){
                m[i][j] = 0;
            }
        }

    }
};

Mat4x4 getIdentity();

Mat4x4 matrixMM(Mat4x4 l, Mat4x4 r);

inline Mat4x4 operator+(const Mat4x4& l, const Mat4x4& r);

inline Mat4x4 operator-(const Mat4x4& l, const Mat4x4& r);
inline Mat4x4 operator*(const Mat4x4& l, const Mat4x4& r)
{
	return matrixMM(l, r);

}
inline Vector3 operator-(const Vector3& l, const Vector3& r)
{
	Vector3 Ret(l.x - r.x, l.y - r.y, l.z - r.z);

	return Ret;
}

inline Vector3 operator+(const Vector3& l, const Vector3& r)
{
	Vector3 Ret(l.x + r.x, l.y + r.y, l.z + r.z);

	return Ret;
}

inline Vector3 operator*(const Vector3& l, float r)
{
	Vector3 Ret(l.x * r, l.y * r, l.z *r);

	return Ret;
}

float vDot(Vector3 v1, Vector3 v2);

float getDistance(Vector3 v1, Vector3 v2);

Mat4x4 transpose(Mat4x4 original);

Mat4x4 getFrustum(float fovy, float aspect, float zNear, float zFar);
Mat4x4 matrixOrthogonal(float left, float right, float bottom, float top);
Mat4x4 matrixOrthogonalZ(float left, float right, float bottom, float top, float zNear, float zFar);


Mat4x4 getScale(float scaleX, float scaleY, float scaleZ);
Mat4x4 getTranslation(float trX, float trY, float trZ);
Mat4x4 getRotationX(float thetaN);
Mat4x4 getRotationY(float thetaN);
    
Mat4x4 getRotationZ(float thetaN);


Mat4x4 matrixLookAt(Vector3 eye, Vector3 center, Vector3 up);

Mat4x4 removeRotation(Mat4x4 transform, Mat4x4 view);

uint getCountsOfDigits(int number);

struct Transform{
    Vector3 pos = Vector3(0,0,0);
    Vector3 scale = Vector3(1,1,1);
    Vector3 rotation = Vector3(0,0,0);

};

void QuaternionToMatrix(Mat4x4* result, const AnimQuaternion quat);

void QuatNormalize(AnimQuaternion in, AnimQuaternion* out);

void QuatInterpolate(AnimQuaternion* pOut, const AnimQuaternion pStart, const AnimQuaternion pEnd, float pFactor);
Vector3 getFrontLook(float pitch, float yaw);


Vector3 getDirection(float pitch, float yaw,float roll);

Mat4x4 removeTranslationFromViewMat(Mat4x4 viewMat);