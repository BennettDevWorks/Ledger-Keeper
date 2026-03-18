#pragma once 

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "colors.hpp"


class Section{
	public:
		Section(SDL_Renderer* renderer, int x, int y, int width, int height);
		~Section();
		
		// SECTION Setter
		void setWidth(int newWidth);
		void setHeight(int newHeight);
		void setTitle(const char* newTitle);
        void setDragging(bool newDragging);

		// SECTION Getter
		int getWidth();
		int getHeight();
		const char* getTitle();
		SDL_Rect getRect();
        bool getDragging();

		// SECTION Drawer
		void drawSection();

        // SECTION Actions
        bool pointInRect(int x, int y);
        bool pointInDragBar(int x, int y);
        void update(int mouseX, int mouseY, bool mousePressed);

	private:
        int x, y, width, height;
		const char* title;
		SDL_Rect rect;
        SDL_Rect dragBar;
        SDL_Renderer* renderer;
		int value;
		Color color = WHITE;
        Color borderColor = DARKGREY;
        bool dragging = false;
        int mouseXOffSet = 0;
        int mouseYOffSet = 0;
};
