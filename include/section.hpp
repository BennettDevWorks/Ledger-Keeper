#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "colors.hpp"


class Section{
	public:
		Section();
		~Section();
		
		//Setter
		void setWidth(int newWidth);
		void setHeight(int newHeight);
		void setTitle(const char* newTitle);

		//Getter
		int getWidth();
		int getHeight();
		const char* getTitle();
		SDL_Rect getRect();

		//Drawer
		void drawSection();

	private:
		const char* title;
		SDL_Rect rect;
		int value;
		Color color = WHITE;
};
