#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "raylib.h"


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

		//Drawer
		void drawSection();

	private:
		int width = 50;
		int height = 50;
		int x = 50;
		int y = 50;
		const char* title;
		int value;
		Color color = WHITE;
};
