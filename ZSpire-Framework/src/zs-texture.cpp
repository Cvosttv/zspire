#define _CRT_SECURE_NO_WARNINGS
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

//including GLEW
#ifdef _WIN32
#include <glew.h>
#endif

#ifdef __linux__
#include <GL/glew.h>
#endif

#include "stdio.h"
#include "stdlib.h"
#include <sys/stat.h>

#include "../includes/zs-resource.h"

#include "../includes/zs-texture.h"

#ifdef __linux__
#define _fileno fileno
#endif

#include "../includes/zs-logger.h"

void ZSpire::Texture::InitializeTexture() {
	glGenTextures(1, &this->TEXTURE_ID);
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE_ID);
}

bool ZSpire::Texture::LoadDDSFromBuffer(unsigned char* buffer) {
	InitializeTexture();

	this->properties.HEIGHT = *(unsigned int*)&(buffer[12]);
	this->properties.WIDTH = *(unsigned int*)&(buffer[16]);
	unsigned int linearSize = *(unsigned int*)&(buffer[20]);
	unsigned int mipMapCount = *(unsigned int*)&(buffer[28]);
	unsigned int fourCC = *(unsigned int*)&(buffer[84]);


	unsigned char * bufferT;
	unsigned int bufsize;
	/* вычисляем размер буфера */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	bufferT = (unsigned char*)malloc(bufsize * sizeof(unsigned char));

	for (unsigned int i = 0; i < bufsize; i++) {
		bufferT[i] = buffer[i + 128];

	}

	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	int nwidth = (int)this->properties.WIDTH;
	int nheight = (int)this->properties.HEIGHT;

	//Mipmaps
	for (unsigned int level = 0; level < mipMapCount && (nwidth || nheight); ++level)
	{
		unsigned int size = ((nwidth + 3) / 4)*((nheight + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, nwidth, nheight,
			0, size, bufferT + offset);

		offset += size;
		nwidth /= 2;
		nheight /= 2;
	}
	free(bufferT);
	return true;
}

bool ZSpire::Texture::LoadDDSFromFile(const char* file_path) {
	FILE * file = fopen(file_path, "rb");
	if (file == NULL) {
		ZSpire::Log(TYPE_ERROR, "%s %s", "Can't load DDS file ", file_path);
		return false;
	}
	unsigned char header[128];
	fread(header, 1, 128, file);

	if (header[0] != 'D' && header[1] != 'D' && header[2] != 'S') {
		ZSpire::Log(TYPE_ERROR, "%s %s %s", "Perhaps, file ", file_path, " is'nt DDS image file.");
		return false;
	}
	fseek(file, 0, SEEK_SET);

	struct stat buff;


	fstat(_fileno(file), &buff);

	unsigned char * data = (unsigned char*)malloc(sizeof(unsigned char*) * buff.st_size);
	fread(data, 1, buff.st_size, file);
	LoadDDSFromBuffer(data);

	free(data);
	fclose(file);

	return true;
}

void ZSpire::Texture::Use(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE_ID);
}

void ZSpire::Texture::Release() {
	glDeleteTextures(1, &this->TEXTURE_ID);
}

unsigned int ZSpire::Texture::getTextureGL_ID() {
	return this->TEXTURE_ID;
}

void ZSpire::Texture::setAnisotropyValue(float aniso) {
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE_ID);
	glTexParameterf(GL_TEXTURE_2D, GL_ARB_texture_filter_anisotropic, aniso);
}

bool ZSpire::Texture::loadFromResourceDesk(){
	FILE* file = fopen(resource_desc.packFilePath, "rb");

	fseek(file, resource_desc.start_byte, SEEK_SET);

	unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char*) * (resource_desc.end_byte - resource_desc.start_byte));


	fread(buffer, 1, resource_desc.end_byte - resource_desc.start_byte, file);

	return LoadDDSFromBuffer(buffer);


}