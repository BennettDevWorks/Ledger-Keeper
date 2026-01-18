#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "raylib.h"
#include "window.hpp"


Window::Window(int width, int height, const char* title) 
: width(width), height(height), title(title) {
	InitWindow(width, height, title);
	SetTargetFPS(60);
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
			ClearBackground(DARKBLUE);
			drawButtons();
		EndDrawing();
	}
}

void Window::drawButtons(){
	for auto& button : buttons{
		button->draw();
	}
}

//-------------------------------Buttons----------------------



