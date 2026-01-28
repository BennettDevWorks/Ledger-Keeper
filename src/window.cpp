#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.hpp"
#include "colors.hpp"


struct _TTF_Font;
using TTF_Font = _TTF_Font;

//------------------Button---------------------
Button::Button(SDL_Renderer* renderer, int x, int y, const char* title, int width, int height)
: renderer(renderer), title(title) {
	rect = SDL_Rect{x, y, width, height};
	TTF_SizeText(font, title, &textWidth, &textHeight);
	textX = rect.x + (rect.w - textWidth / 2);
	textY = rect.h + (rect.h - fontSize) / 2;
}

Button::~Button(){}

//Setters
void Button::setWidth(int newWidth){
	rect.w = newWidth;
	textX = rect.x + (rect.w - textWidth / 2);
}
void Button::setHeight(int newHeight){
	rect.h= newHeight;
	textY = rect.h + (rect.h - fontSize) / 2;
}
void Button::setTitle(const char* newTitle){
	title = newTitle;
	textX = rect.x + (rect.w - textWidth / 2);
	textY = rect.h + (rect.h - fontSize) / 2;
}
void Button::setColor(Color newColor){color = newColor;}

//Getters
int Button::getWidth(){return rect.w;}
int Button::getHeight(){return rect.h;}
bool Button::getIsActive(){return isActive;}
Color Button::getColor(){return color;}
Color Button::getActiveColor(){return activeColor;}
Color Button::getStandByeColor(){return standByeColor;}
SDL_Rect Button::getRect(){return rect;} 

//Drawers
void Button::drawButton(){
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
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

	font = TTF_OpenFont("../Assets/Fonts/Smooch_Sans/SmoochSans-VariableFont_wght.ttf", fontSize);

	window.reset(SDL_CreateWindow(title,
						SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED,
						width, height,
						SDL_WINDOW_SHOWN));

	if (!window){
		SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
		running = false;
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer){
		SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_DestroyWindow(window.get());
		running = false;
		SDL_Quit();
		return;
	}

	buttons.push_back(std::make_unique<Button>(10, 10, "Add Section"));
}

Window::~Window(){
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window.get()) SDL_DestroyWindow(window.get());
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
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	SDL_Point mousePos = {mouseX, mouseY};

	for (auto& button : buttons){
		//Un-highlight button
		if (button->getIsActive()){
			button->setColor(button->getStandByeColor());
		}
		//Highlight button
		if (SDL_PointInRect(&mousePos, &button->getRect())){
			button->setColor(button->getActiveColor());
		}
	}
}


