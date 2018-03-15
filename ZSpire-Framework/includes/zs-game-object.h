namespace ZSpire {
	class GameObject {
	protected:
		Transform transform;
		Mesh* mesh;
		Texture* diffuse_texture;
	public:

		void setPosition(ZSVECTOR3 pos);
		void setScale(ZSVECTOR3 scale);
		void setRotation(ZSVECTOR3 rotation);

		void setMesh(Mesh* mesh);
		void Draw();

		Transform* getTransform();
	};
}
