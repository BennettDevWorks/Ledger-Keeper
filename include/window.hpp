#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "raylib.h"


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

	private:
		int width, height;
		const char* title;
		std::vector<std::unique_ptr<Button>> buttons;
		std::vector<std::unique_ptr<Section>> sections;
};

class Button{
	public:
		Button();
		~Button();

		//Setters
		void setWidth(int newWidth);
		void setHeight(int newHeight);
		void setTitle(const char* title);

		//Getters
		int getWidth();
		int getHeight();
		std::string getTitle();

		//Drawers
		void drawButton();

		//Actions
		void action();

	private:
		int x, y;
		int width = 100;
		int height = 70;
		const char* title;
};

class AddSectionButton : public Button{
	public:
		void drawButton();
}
