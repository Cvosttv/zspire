#define NON_SHOWING -1

namespace ZSWindows {

	void DrawInspectorWindow(SDL_Window * window);
	
	namespace Inspector {
		void selectObject(unsigned int obj_to_select);
		void selectLight(unsigned int light_to_select);

		void selectTexture(unsigned int texture_to_select);
		void selectMesh(unsigned int mesh_to_select);
	}
}