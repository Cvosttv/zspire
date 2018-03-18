namespace ZSpire {

	struct ZSWindowDesc {
		unsigned int WIDTH;
		unsigned int HEIGHT;

		char WINDOW_TITLE[256];

		bool isResizable;
		bool isVsyncEnabled;

		ZSWindowDesc() {
			WIDTH = 640;
			HEIGHT = 480;

			isResizable = true;

			isVsyncEnabled = false;
		}

	};

	class ZSpireApp {
	protected:
		ZSWindowDesc desc;

	public:
		void PollEvents();
		void ZSDestroyWindow();
		bool createWindow(ZSWindowDesc desc);
		void MSGBox(const char* title, const char* message);
		void postFrame();

		void gl_clear();
	};
}