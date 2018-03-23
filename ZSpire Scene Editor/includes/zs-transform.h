namespace ZSpire {
	class Transform {
	protected:

		ZSVECTOR3 position;
		ZSVECTOR3 scale;
		ZSVECTOR3 rotation;

		
	public:

		Transform() {
			position = ZSVECTOR3(0,0,0);
			scale = ZSVECTOR3(1,1,1);
			rotation = ZSVECTOR3(0,0,0);
		}

		ZSMATRIX4x4 translation_matrix;

		void setPosition(ZSVECTOR3 pos);
		void setScale(ZSVECTOR3 scale);
		void setRotation(ZSVECTOR3 rotation);
		void updateMatrix();

		ZSVECTOR3 _getPosition();
		ZSVECTOR3 _getScale();
		ZSVECTOR3 _getRotation();

	};
}