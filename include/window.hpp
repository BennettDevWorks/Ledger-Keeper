#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "section.hpp"
#include "raylib.h"


class Button{
	public:
		Button(int x, int y, const char* title, int width=100, int height=70);
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
		Rectangle getRec();

		//Drawers
		void drawButton();

		//Actions
		void action();

	private:
		int x, y, textX, textY;
		int fontSize = 12;
		int width = 100;
		int height = 70;
		const char* title;
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
		int width, height;
		const char* title;
		std::vector<std::unique_ptr<Button>> buttons;
		std::vector<std::unique_ptr<Section>> sections;
		Color bgColor = DARKBLUE;
};

