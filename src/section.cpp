#include <iostream>
#include <vector>
#include <memory>
#include "section.hpp"
#include "colors.hpp"


Section::Section(SDL_Renderer* renderer, int x, int y, int width, int height)
    : renderer(renderer), x(x), y(y), width(width), height(height){

        rect = SDL_Rect{(int)x, (int)y, (int)width, (int)height};

        int dragBarHeight = std::max(10, static_cast<int>(rect.h * 0.1));
        dragBar = SDL_Rect{(int)x, (int)y, (int)width, dragBarHeight};

        //TODO:
        // DONE Set rect
        //Set title (x,y)
        //set data (x,y)
        //DONE Add drawSection function code 
        //DONE Add dragable code (hold down on top title bar of the section square)
}
Section::~Section(){}

// SECTION Setters
void Section::setWidth(int newWidth){rect.w = newWidth;}
void Section::setHeight(int newHeight){rect.h = newHeight;}
void Section::setTitle(const char* newTitle){title = newTitle;}
void Section::setDragging(bool newDragging){ dragging = newDragging;}

// SECTION Getters
int Section::getWidth(){return rect.w;}
int Section::getHeight(){return rect.h;}
const char* Section::getTitle(){return title;}
SDL_Rect Section::getRect(){return rect;}
bool Section::getDragging(){return dragging;}

// SECTION Drawers
void Section::drawSection(){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    //Draw border
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &rect);

    //Draw DragBar
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderFillRect(renderer, &dragBar);
}

// SECTION Actions
bool Section::pointInRect(int x, int y){
    if (x >= rect.x && x < rect.x + rect.w &&
            y >= rect.y && y < rect.y + rect.h){
        return true;
    }
    return false;
}

bool Section::pointInDragBar(int x, int y){
    if (x >= dragBar.x && x < dragBar.x + dragBar.w &&
            y >= dragBar.y && y < dragBar.y + dragBar.h){
        return true;
    }
    return false;
}

void Section::update(int mouseX, int mouseY, bool mousePressed){
    if (!mousePressed){
        dragging = false;
        return;
    };

    bool overDragBar = pointInDragBar(mouseX, mouseY);

    if (mousePressed && overDragBar && !dragging){
        mouseXOffSet = mouseX - rect.x;
        mouseYOffSet = mouseY - rect.y;
        dragging = true;
    }

    if (dragging){
        rect.x = mouseX - mouseXOffSet;
        rect.y = mouseY - mouseYOffSet;
        dragBar.x = mouseX - mouseXOffSet;
        dragBar.y = mouseY - mouseYOffSet;
    }

    bool over = pointInRect(mouseX, mouseY);
    if (!over) return;

    //TODO button logic goes here
    //if (!dragging){}
}
