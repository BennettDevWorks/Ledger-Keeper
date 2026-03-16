#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "colors.hpp"
#include "section.hpp"


class Button{
	public:
		Button(SDL_Renderer* renderer, int x, int y, const char* title, int width=100, int height=70);
		~Button();

		//Setters
		void setWidth(int newWidth);
		void setHeight(int newHeight);
		void setTitle(const char* title);
		void setColor(Color newColor);
        void setIsActive(bool newIsActive);

		//Getters
		int getWidth();
		int getHeight();
		bool getIsActive();
		std::string getTitle();
		Color getColor();
		Color getActiveColor();
		Color getStandByeColor();
		const SDL_Rect& getRect() const;

		//Drawers
		void drawButton();

		//Actions
		void action();

	private:
		int textX, textY, textWidth, textHeight;
		int fontSize = 12;
		TTF_Font* font;
		const char* title;
		SDL_Rect rect;
		SDL_Renderer* renderer;
		Color color = WHITE;
		Color standByeColor = WHITE;
		Color activeColor = DARKGREY;
		Color textColor = BLACK;
		bool isActive;
};

class AddSectionButton : public Button{
	public:
		void drawButton();
};
