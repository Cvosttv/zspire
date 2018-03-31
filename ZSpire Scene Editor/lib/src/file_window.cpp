#define _CRT_SECURE_NO_WARNINGS
typedef unsigned int uint;

#include "imgui.h"
#include <SDL.h>
#include <vector>
#include "string.h"
#include <string>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

#include "../includes/file_window.h"

std::vector <ZSWindows::FileEntry> files;
std::string path = "D:\\";

void ZSWindows::UpdateFileList() {
	files.resize(0);
	
	std::string search_path = path + "/*.*";
#ifdef _WIN32
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
				FileEntry fe;
				strcpy(fe.name, fd.cFileName);
				fe.type = ZS_FILE_TYPE_DIR;
				files.push_back(fe);
			}
			
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				FileEntry fe;
				strcpy(fe.name, fd.cFileName);
				files.push_back(fe);
			}
			

		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
#endif
}

void ZSWindows::DrawFilesWindow(SDL_Window * window){
	ImGui::Begin("Files");

	UpdateFileList();

	for (unsigned int i = 0; i < files.size(); i++) {

		char namebuf[256];
		if (files[i].type == ZS_FILE_TYPE_DIR) {
			strcpy(namebuf, "(DIR) ");
			strcat(namebuf, files[i].name);

		} else {
	strcpy(namebuf, files[i].name);
				}

		if (ImGui::Button(namebuf) == true) {
			if(files[i].type == ZS_FILE_TYPE_DIR){
				path = path + "\\" + std::string(files[i].name);
			
			}
		}
	}

	ImGui::End();
}
