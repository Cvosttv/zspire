namespace ZSpire {
	class GameObject {
	protected:

		Transform transform;
		Mesh* mesh;
		Texture* diffuse_texture;

		char label[128];

		bool hasTextureDiffuse = false;
		bool hasMesh = false;

	public:
		

		void setPosition(ZSVECTOR3 pos);
		void setScale(ZSVECTOR3 scale);
		void setRotation(ZSVECTOR3 rotation);

		void setMesh(Mesh* mesh);
		void setDiffuseTexture(Texture* texture);

		void Draw();

		Transform* getTransform();
		
		char* getLabel();
		void setLabel(const char* label);
	};
}
