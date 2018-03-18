namespace ZSpire {
	class AudioSource
	{

	private:

		unsigned int mSourceID;
		unsigned int mBufferID;

	public:

		ZSVECTOR3 position;
		bool mLooped;

		bool Open(const char* Filename, bool Looped);
		void Play();
		void Close();
		void setTranslation(ZSVECTOR3 position);
		void Stop();
	};
}