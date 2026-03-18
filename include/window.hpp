#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "colors.hpp"
#include "section.hpp"
#include "button.hpp"


class Window{
	public:
		Window(int width, int height, const char* title);
		~Window();

		// SECTION Setters
		void setWidth(int newWidth);
		void setHeight(int newHeight);
		void setTitle(const char* newTitle);

		// SECTION Getters
		int getWidth();
		int getHeight();
		std::string getTitle();

		//Draw
		void drawWindow();
		void drawButtons();
        void drawSections();

		// SECTION Update
		void update();

        // SECTION Callbacks
        void addSection();

	private:
		std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{nullptr, SDL_DestroyWindow};
		std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{nullptr, SDL_DestroyRenderer};
		bool running;
		int width, height;
		const char* title;
		int textX, textY, textWidth, textHeight;
		int fontSize = 18;
		TTF_Font* font;
		std::vector<std::unique_ptr<Button>> buttons;
		std::vector<std::unique_ptr<Section>> sections;
        Section* draggingSection = nullptr;
		Color bgColor = DARKBLUE;
};
