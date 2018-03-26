struct PackFileState {
	char path[128];
	unsigned int written_bytes = 0;
//	bool IsFirstTime = false;
};

bool IsSceneLoaded();

void LoadScene(const char* path);

void saveScene();

void createNewScene(const char* name);