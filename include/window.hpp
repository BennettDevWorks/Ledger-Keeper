#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
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

		//Getters
		int getWidth();
		int getHeight();
		bool getIsActive();
		std::string getTitle();
		Color getColor();
		Color getActiveColor();
		Color getStandByeColor();
		SDL_Rect getRect();

		//Drawers
		void drawButton();

		//Actions
		void action();

	private:
		int textX, textY;
		int fontSize = 12;
		const char* title;
		SDL_Rect rect;
		SDL_Renderer* renderer;
		Color color = WHITE;
		Color standByeColor = WHITE;
		Color activeColor = DARKGRAY;
		Color textColor = BLACK;
		bool isActive;
};

class AddSectionButton : public Button{
	public:
		void drawButton();
};

class Window{
	public:
		Window(int width, int height, const char* title);
		~Window();

		//Setters
		void setWidth(int newWidth);
		void setHeight(int newHeight);
		void setTitle(const char* newTitle);

		//Getters
		int getWidth();
		int getHeight();
		std::string getTitle();

		//Draw
		void drawWindow();
		void drawButtons();

		//Update
		void update();

	private:
		bool running;
		int width, height;
		const char* title;
		std::vector<std::unique_ptr<Button>> buttons;
		std::vector<std::unique_ptr<Section>> sections;
		Color bgColor = DARKBLUE;
};

