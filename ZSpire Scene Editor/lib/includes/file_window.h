#define ZS_FILE_TYPE_DIR 1

namespace ZSWindows {

	struct FileEntry {
		char name[128];
		int type;
	};

	void UpdateFileList();
	void DrawFilesWindow(SDL_Window * window);
}