#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "colors.hpp"
#include "section.hpp"


class Button{
	public:
		Button(SDL_Renderer* renderer, TTF_Font* newFont, int x, int y, const char* title, int width=100, int height=70);
		~Button();

		// SECTION Setters
		void setWidth(int newWidth);
		void setHeight(int newHeight);
		void setTitle(const char* title);
		void setColor(Color newColor);
        void setIsActive(bool newIsActive);
        void setX(int newX);
        void setY(int newY);
        void setRX(int newRX);
        void setRY(int newRY);

		// SECTION Getters
        int getRX();
        int getRY();
		int getWidth();
		int getHeight();
		bool getIsActive();
		std::string getTitle();
		Color getColor();
		Color getActiveColor();
		Color getStandByeColor();
		const SDL_Rect& getRect() const;

		// SECTION Drawers
		void drawButton();

		// SECTION Actions
        bool pointInRect(int x, int y);
        void highlight();
        void standbye();
        std::function<void()> onClick;//call back function 
		void click();
        void update(int mouseX, int mouseY, bool mousePressed);

	private:
		int textX, textY, textWidth, textHeight;
		int fontSize = 12;
		TTF_Font* font;
		const char* title;
		SDL_Rect rect;
		SDL_Renderer* renderer;
		Color color = WHITE;
		Color standbyeColor = WHITE;
		Color activeColor = DARKGREY;
		Color textColor = BLACK;
        Color borderColor = BLACK;
		bool isActive;
        bool wasPressed = false;
        int reletiveX;
        int reletiveY;
};

class AddSectionButton : public Button{
	public:
		void drawButton();
};
