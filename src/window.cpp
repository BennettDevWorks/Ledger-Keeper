#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include "raylib.h"
#include "window.hpp"


//------------------Button---------------------
Button::Button(int x, int y, const char* title, int width, int height)
: x(x), y(y), width(width), height(height), title(title) {
	textX = x + (width - MeasureText(title, fontSize)) / 2;
	textY = y + (height - fontSize) / 2;
}

Button::~Button(){}

//Setters
void Button::setWidth(int newWidth){width = newWidth;}
void Button::setHeight(int newHeight){height = newHeight;}
void Button::setTitle(const char* newTitle){title = newTitle;}
void Button::setColor(Color newColor){color = newColor;}

//Getters
int Button::getWidth(){return width;}
int Button::getHeight(){return height;}
bool Button::getIsActive(){return isActive;}
Color Button::getColor(){return color;}
Color Button::getActiveColor(){return activeColor;}
Color Button::getStandByeColor(){return standByeColor;}
Rectangle Button::getRec(){return Rectangle{(float)x, (float)y, (float)width, (float)height};}


//Drawers
void Button::drawButton(){
	DrawRectangle(x, y, width, height, color);
	DrawText(title, textX, textY, fontSize, textColor);
}

//Actions

//------------------Window--------------------
Window::Window(int width, int height, const char* title) 
: width(width), height(height), title(title) {
	running = true;

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		running = false;
		return;
	}

	window = SDL_CreateWindow(title,
						SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED,
						widh, height,
						SDL_WINDOW_SHOWN);

	if (!window){
		SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
		running = false;
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer){
		SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		running = false;
		SDL_Quit();
		return;
	}

	buttons.push_back(std::make_unique<Button>(10, 10, "Add Section"));
}

Window::~Window(){
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_Quit();
}

//Setters
void Window::setWidth(int newWidth){
	width = newWidth;
}
void Window::setHeight(int newHeight){
	height = newHeight;
}
void Window::setTitle(const char* newTitle){
	title = newTitle;
}

//Getters
int Window::getWidth(){return width;}
int Window::getHeight(){return height;}
std::string Window::getTitle(){return title;}

//Drawers
void Window::drawWindow(){
	while (running){
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				running = false;
			}
		}

		SetDrawColor(renderer, bgColor);
		SDL_RenderClear(renderer);

		update();

		drawButtons();

		SDL_RenderPresent(renderer);
	}
}

void Window::drawButtons(){
	for (auto& button : buttons){
		button->drawButton();
	}
}

//Update
void Window::update(){
	//std::cout << "Updating window" << std::endl;
	Vector2 mousePos = GetMousePosition();

	for (auto& button : buttons){
		if (button->getIsActive()){
			button->setColor(button->getStandByeColor());
		}
		if (CheckCollisionPointRec(mousePos, button->getRec())){
			button->setColor(button->getActiveColor());
		}
	}
}


