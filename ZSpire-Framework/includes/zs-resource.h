#ifndef ZSRESOURCE
#define ZSRESOURCE
#endif


namespace ZSpire {
	struct ZSResourceDesc {
		char label[128];

		char packFilePath[256];

		unsigned int start_byte;
		unsigned int end_byte;

		bool loaded = false;
	};
}