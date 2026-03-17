#pragma once 

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "colors.hpp"


class Section{
	public:
		Section(SDL_Renderer* renderer, double x, double y, double width, double height);
		~Section();
		
		// SECTION Setter
		void setWidth(double newWidth);
		void setHeight(double newHeight);
		void setTitle(const char* newTitle);

		// SECTION Getter
		double getWidth();
		double getHeight();
		const char* getTitle();
		SDL_Rect getRect();

		// SECTION Drawer
		void drawSection();

	private:
        double x, y, width, height;
		const char* title;
		SDL_Rect rect;
        SDL_Renderer* renderer;
		int value;
		Color color = WHITE;
        Color borderColor = DARKGREY;
};
