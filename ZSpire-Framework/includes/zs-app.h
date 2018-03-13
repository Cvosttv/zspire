namespace ZSpire {

	struct ZSWindowDesc {
		unsigned int WIDTH;
		unsigned int HEIGHT;

		char WINDOW_TITLE[256];

		bool isResizable;

		ZSWindowDesc() {
			WIDTH = 640;
			HEIGHT = 480;

			isResizable = true;
		}

	};

	class ZSpireApp {
	protected:
		ZSWindowDesc desc;

	public:
		void ZSDestroyWindow();
		bool createWindow(ZSWindowDesc desc);
		void MSGBox();
		void postFrame();

		void gl_clear();
	};
}