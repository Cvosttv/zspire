namespace ZSpire{

	bool InitOpenAL_Device();

	void setListenerPosition(ZSVECTOR3 position);
	void setListenerOrientation(ZSVECTOR3 target, ZSVECTOR3 up);

	void DestroyAL();
}