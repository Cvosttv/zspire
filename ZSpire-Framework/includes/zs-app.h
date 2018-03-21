#define DEFAULT_WIDTH 0
#define DEFAULT_HEIGHT 0

namespace ZSpire {

	struct ZSWindowDesc {
		unsigned int WIDTH;
		unsigned int HEIGHT;

		char WINDOW_TITLE[256];

		bool isResizable;
		bool isVsyncEnabled;
		bool isFullscreen;

		ZSWindowDesc() {
			WIDTH = DEFAULT_WIDTH;
			HEIGHT = DEFAULT_HEIGHT;

			isResizable = true;
			isFullscreen = false;
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
		void setWindowProperties(ZSWindowDesc desc);
		void MSGBox(const char* title, const char* message);
		void postFrame();

		void gl_clear();
	};
}