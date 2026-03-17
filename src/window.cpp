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

// SECTION ------------------Window--------------------
Window::Window(int width, int height, const char* title) 
: width(width), height(height), title(title) {
	running = true;

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		running = false;
		return;
	}

    if (TTF_Init() != 0){
        SDL_Log("TTF_Init Error: %s", TTF_GetError());
        running = false;
        return;
    }

	font = TTF_OpenFont("Assets/Fonts/Smooch_Sans/SmoochSans-VariableFont_wght.ttf", fontSize);
    if (!font) {
        SDL_Log("Font load error: %s", TTF_GetError());
    }

	window.reset(SDL_CreateWindow(title,
						SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED,
						width, height,
						SDL_WINDOW_RESIZABLE));

	if (!window){
		SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
		running = false;
		SDL_Quit();
		return;
	}

	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	if (!renderer){
		SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
		running = false;
		SDL_Quit();
		return;
	}

	buttons.push_back(std::make_unique<Button>(renderer.get(), font, 10, 10, "Add Section"));
    buttons[0]->onClick = [this]() {
        this->addSection();
    };
}

Window::~Window(){
	//if (renderer.get()) SDL_DestroyRenderer(renderer.get());
	//if (window.get()) SDL_DestroyWindow(window.get());
    renderer.reset();
    window.reset();
	SDL_Quit();
}

// SECTION Drawers
void Window::drawWindow(){
    SDL_Event event;


	while (running){
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				running = false;
			}
		}

		SDL_SetRenderDrawColor(renderer.get(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		SDL_RenderClear(renderer.get());

		update();

		drawButtons();
        drawSections();

		SDL_RenderPresent(renderer.get());
	}
}

void Window::drawButtons(){
	for (auto& button : buttons){
		button->drawButton();
	}
}

void Window::drawSections(){
    for (auto& section : sections){
        section->drawSection();
    }
}

// SECTION Update
void Window::update(){
	//std::cout << "Updating window" << std::endl;
	int mouseX, mouseY;
	bool isMousePressed = SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT);
	SDL_Point mousePos = {mouseX, mouseY};

	for (auto& button : buttons){
		//Highlight button
        button->update(mouseX, mouseY, isMousePressed);
	}
}

// SECTION Setters
void Window::setWidth(int newWidth){
	width = newWidth;
}
void Window::setHeight(int newHeight){
	height = newHeight;
}
void Window::setTitle(const char* newTitle){
	title = newTitle;
}

// SECTION Getters
int Window::getWidth(){return width;}
int Window::getHeight(){return height;}
std::string Window::getTitle(){return title;}

//Callbacks 
void Window::addSection(){
    float size = 150;
    float x = (width - size) / 2;
    float y = (height - size) /2;

    sections.push_back(std::make_unique<Section>(renderer.get(), x, y, size, size));
    std::cout << "Added section to middle of window" << std::endl;
    std::cout << "X: " << x << std::endl;
    std::cout << "Y: " << y << std::endl;
}
