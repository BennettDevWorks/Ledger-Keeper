#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include "section.hpp"
#include "colors.hpp"
#include "editSection.hpp"


Section::Section(int newID, SDL_Renderer* renderer, TTF_Font* newFont, int x, int y, int width, int height)
    : id(newID), renderer(renderer), font(newFont), x(x), y(y), width(width), height(height){

        rect = SDL_Rect{(int)x, (int)y, (int)width, (int)height};

        TTF_SizeText(font, title, &titleRect.w, &titleRect.h);


        titleRect.x = rect.x + (rect.w - titleRect.w) / 2;
        titleRect.y = rect.y + (rect.h - titleRect.h) / 6;

        SDL_Surface*  textSurface = TTF_RenderText_Blended(font, title, textColor.toSDL());
        if (!textSurface){
            std::cerr << "Error with section: " << newID << std::endl;
            throw std::runtime_error("Text Render Error Section");
        }

        titleTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        int dragBarHeight = std::max(10, static_cast<int>(rect.h * 0.1));
        dragBar = SDL_Rect{(int)x, (int)y, (int)width, dragBarHeight};


        int buttonX = x;
        int buttonY = y + dragBarHeight + titleRect.h + std::max(static_cast<int>(height * 0.05), 10);
        int buttonWidth = (width >> 2);
        int buttonHeight = static_cast<int>(height *0.15);
        editButton = std::make_unique<Button>(renderer, font, buttonX, buttonY, 
                                                "Edit",
                                                buttonWidth, buttonHeight);
        editButton->setRX(buttonX - x);
        editButton->setRY(buttonY - y);
        editButton->onClick = [this]() {
            this->editSection();
        };

        int dButtonWidth = static_cast<int>(width * 0.25);
        int dButtonHeight = static_cast<int>(height * 0.15);
        int dButtonX = x + width - dButtonWidth;
        int dButtonY = y + dragBarHeight + titleRect.h + std::max(static_cast<int>(height * 0.05), 10);
        deleteButton = std::make_unique<Button>(renderer, font, dButtonX, dButtonY, 
                                                "Delete", 
                                                dButtonWidth,
                                                dButtonHeight);
        deleteButton->setRX(dButtonX - x);
        deleteButton->setRY(dButtonY - y);
        deleteButton->onClick = [this](){
            this->deleteSection(id);
        };


        editWindow = std::make_unique<EditSection>(renderer, font, x, y, width, height);
        editWindow->setTitle("Edit Section");

        editWindow->addEditInputField("Type");
        editWindow->addEditInputField("Value");


        //TODO:
        // DONE Set rect
        // DONE Set title (x,y)
        // Add edit section button that makes a pop up
        // set data (x,y)
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
    if (editWindow->getIsActive()){
        editWindow->drawSection();
        return;
    }


    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    //Draw border
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &rect);

    //Draw DragBar
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderFillRect(renderer, &dragBar);

    //Draw Title
    drawSectionTitle();

    drawEditButton();

    drawDeleteButton();
}

void Section::drawSectionTitle(){
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
}

void Section::drawEditButton(){
    editButton->drawButton();
}

void Section::drawDeleteButton(){
    deleteButton->drawButton();
}

void Section::drawValue(){
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
    editButton->update(mouseX, mouseY, mousePressed);
    deleteButton->update(mouseX, mouseY, mousePressed);

    if (editWindow->getIsActive()){
        editWindow->update(mouseX, mouseY, mousePressed);
        return;
    }

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
        titleRect.x = rect.x + (rect.w - titleRect.w) / 2;
        titleRect.y = rect.y + (rect.h - titleRect.h) / 6;
        dragBar.x = mouseX - mouseXOffSet;
        dragBar.y = mouseY - mouseYOffSet;
        editButton->setX(rect.x + editButton->getRX());
        editButton->setY(rect.y + editButton->getRY());
        deleteButton->setX(rect.x + deleteButton->getRX());
        deleteButton->setY(rect.y + deleteButton->getRY());
    }

    bool over = pointInRect(mouseX, mouseY);
    if (!over) return;
}

// SECTION Callbacks
void Section::editSection(){
    editWindow->setActive();
    editWindow->updatePos(rect.x, rect.y);
}

void Section::deleteSection(int id){
    if (setDelete){
        std::cout << "Delete Section at section level" << std::endl;
        setDelete();
    }
}
