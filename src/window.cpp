#include <iostream>
#include <vector>
#include <memory>
#include <string>
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
	InitWindow(width, height, title);
	SetTargetFPS(60);

	buttons.push_back(std::make_unique<Button>(10, 10, "Add Section"));
}
Window::~Window(){}

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
	while (!WindowShouldClose()){
		BeginDrawing();
			ClearBackground(bgColor);
			update();
			drawButtons();
		EndDrawing();
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


