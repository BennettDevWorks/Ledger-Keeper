#include <iostream>
#include <vector>
#include <memory>
#include "section.hpp"
#include "raylib.h"


Section::Section(){}
Section::~Section(){}

//Setters
void Section::setWidth(int newWidth){width = newWidth;}
void Section::setHeight(int newHeight){height = newHeight;}
void Section::setTitle(const char* newTitle){title = newTitle;}

//Getters
int Section::getWidth(){return width;}
int Section::getHeight(){return height;}
const char* Section::getTitle(){return title;}

//Drawers
void Section::drawSection(){
	DrawRectangle(x, y, width, height, color);
}
