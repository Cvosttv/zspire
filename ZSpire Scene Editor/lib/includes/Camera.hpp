class Camera{
public:
	float fov = 45;
	float nearPlane = 0.1f;
	float farPlane = 1000.0f;

	bool cullFace = true;
	bool drawDepth = true;


};