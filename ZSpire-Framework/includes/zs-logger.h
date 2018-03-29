#define TYPE_ERROR 1
#define TYPE_OPENGL 9
#define TYPE_LOG 4
#define TYPE_ENGINE 11
#define TYPE_SCRIPTERROR 15

typedef unsigned int uint;


namespace ZSpire {

	void close_outputFile();
	void open_outputFile(const char* fpath);
	void Log(uint TYPE, const char *format, ...);
}