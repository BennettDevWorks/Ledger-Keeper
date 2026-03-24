#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "editSection.hpp"
#include "colors.hpp"
#include "button.hpp"

EditSection::EditSection(SDL_Renderer* renderer, TTF_Font* newFont, int x, int y, int width, int height)
    : renderer(renderer), font(newFont), x(x), y(y), width(width), height(height){
        rect = {x, y, width, height};
        
        TTF_SizeText(font, title, &titleWidth, &titleHeight);

        //int buttonWidth = static_cast<int>(width * 0.25);
        int buttonWidth = (width >> 2);
        int buttonHeight = static_cast<int>(height * 0.15);
        int buttonX = x + (width >> 1) - (buttonWidth >> 1);
        int buttonY = y + height - buttonHeight;
        confirmButton = std::make_unique<Button>(renderer, font, 
                                                    buttonX, buttonY,
                                                    "Confirm", 
                                                    buttonWidth, buttonHeight);

        confirmButton->setRX(buttonX - x);
        confirmButton->setRY(buttonY - y);
        confirmButton->onClick = [this]() {
            this->stopEditing();
        };



       SDL_Surface* textSurface = TTF_RenderText_Blended(font, title, textColor.toSDL()); 
       if (!textSurface){
           std::cout << "Text Render error section" << std::endl;
           return;
       }

       titleTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

       titleX = rect.x + (rect.w - titleWidth) / 2;
       titleY = rect.y + (rect.h - titleHeight) / 4;
       titleRect = {titleX, titleY, titleWidth, titleHeight};

}
EditSection::~EditSection(){}


// SECTION Setter
void EditSection::setX(int newX){ rect.x = newX;}
void EditSection::setY(int newY){ rect.y = newY;}
void EditSection::setWidth(int newWidth){ width = newWidth;}
void EditSection::setHeight(int newHeight){ height = newHeight;}
void EditSection::setTitle(const char* newTitle){ title = newTitle;}
void EditSection::setActive(){ active = true;}

// SECTION Getter
int EditSection::getWidth(){ return width;}
int EditSection::getHeight(){ return height;}
bool EditSection::getIsActive(){ return active;}
const char* EditSection::getTitle(){ return title;}
SDL_Rect EditSection::getRect(){ return rect;}

// SECTION Drawer
void EditSection::drawSection(){
    if (!active) return;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    //Draw Border
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &rect);

    //Draw text fields
    //TODO edit fields 

    if (dragging){
        titleRect.x = rect.x + (rect.w - titleWidth) / 2;
        titleRect.y = rect.y + (rect.h - titleHeight) / 6;
    }

    drawSectionTitle();
    drawConfirmButton();
}

void EditSection::drawSectionTitle(){
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
}

void EditSection::drawConfirmButton(){
    confirmButton->drawButton();
}

// SECTION Action
void EditSection::updatePos(int newX, int newY){
    rect.x = newX;
    rect.y = newY;

    titleRect.x = rect.x + (rect.w - titleWidth) / 2;
    titleRect.y = rect.y + (rect.h - titleHeight) / 4;

    //Make new button position 
    int buttonHeight = static_cast<int>(height * 0.15);
    int buttonWidth = (width >> 2);
    int buttonX = rect.x + (width >> 1) - (buttonWidth >> 1);
    int buttonY = rect.y + height - buttonHeight;
    confirmButton->setX(buttonX);
    confirmButton->setY(buttonY);
}

void EditSection::update(int mouseX, int mouseY, bool mousePressed){
    confirmButton->update(mouseX, mouseY, mousePressed);
}

// SECTION Callbacks
void EditSection::stopEditing(){
    active = false;
}
