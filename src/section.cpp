#include <iostream>
#include <vector>
#include <memory>
#include "section.hpp"
#include "colors.hpp"


Section::Section(SDL_Renderer* renderer, double x, double y, double width, double height)
    : renderer(renderer), x(x), y(y), width(width), height(height){

        rect = SDL_Rect{(int)x, (int)y, (int)width, (int)height};

        //TODO:
        // DONE Set rect
        //Set title (x,y)
        //set data (x,y)
        //DONE Add drawSection function code 
        //Add dragable code (hold down on top title bar of the section square)
}
Section::~Section(){}

// SECTION Setters
void Section::setWidth(double newWidth){rect.w = newWidth;}
void Section::setHeight(double newHeight){rect.h = newHeight;}
void Section::setTitle(const char* newTitle){title = newTitle;}

// SECTION Getters
double Section::getWidth(){return rect.w;}
double Section::getHeight(){return rect.h;}
const char* Section::getTitle(){return title;}
SDL_Rect Section::getRect(){return rect;}

// SECTION Drawers
void Section::drawSection(){
	//std::cout << "Draw SectioN" << std::endl;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    //Draw border
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &rect);
}

