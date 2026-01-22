#include <iostream>
#include <vector>
#include <memory>
#include "section.hpp"
#include "colors.hpp"


Section::Section(){}
Section::~Section(){}

//Setters
void Section::setWidth(int newWidth){rect.w = newWidth;}
void Section::setHeight(int newHeight){rect.h = newHeight;}
void Section::setTitle(const char* newTitle){title = newTitle;}

//Getters
int Section::getWidth(){return rect.w;}
int Section::getHeight(){return rect.h;}
const char* Section::getTitle(){return title;}
SDL_Rect Section::getRect(){return rect;}

//Drawers
void Section::drawSection(){
	std::cout << "Draw SectioN" << std::endl;
}
