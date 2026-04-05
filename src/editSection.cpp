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
           std::cerr << "Text Render error section" << std::endl;
           return;
       }

       titleTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

       titleX = rect.x + (rect.w - titleWidth) / 2;
       titleY = rect.y + (rect.h - titleHeight) / 6;
       titleRect = {titleX, titleY, titleWidth, titleHeight};

       nextInputFieldX = x + static_cast<int>(width * 0.2);
       nextInputFieldY = titleY + titleHeight + 20;
       inputFieldWidth = static_cast<int>(width * 0.6);
       inputFieldHeight = static_cast<int>(height * 0.15);
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
    drawEditInputFields();

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

void EditSection::drawEditInputFields(){
    for (auto& field : inputFields){
        //std::cout << "Input Field Type: " << field.label << std::endl;
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_RenderDrawRect(renderer, &field.rect);
    }
}

// SECTION Action
bool EditSection::pointInRect(int x, int y, SDL_Rect* rect){
    return (x >= rect->x && x < rect->x + rect->w &&
            y >= rect->y && y < rect->y + rect->h);
}

void EditSection::addEditInputField(const char* newLabel){
    InputField newField;

    newField.rect = SDL_Rect{nextInputFieldX, nextInputFieldY, inputFieldWidth, inputFieldHeight};
    newField.label = newLabel;
    newField.text[0] = '\0';
    newField.isActive = false;

    inputFields.push_back(newField);

    nextInputFieldY = nextInputFieldY + inputFieldHeight*1.2;

    std::cout << "Input Field added: " << newField.label << std::endl;
}

void EditSection::updatePos(int newX, int newY){
    rect.x = newX;
    rect.y = newY;

    titleRect.x = rect.x + (rect.w - titleWidth) / 2;
    titleRect.y = rect.y + (rect.h - titleHeight) / 8;

    //Make new button position 
    int buttonHeight = static_cast<int>(height * 0.15);
    int buttonWidth = (width >> 2);
    int buttonX = rect.x + (width >> 1) - (buttonWidth >> 1);
    int buttonY = rect.y + height - buttonHeight;
    confirmButton->setX(buttonX);
    confirmButton->setY(buttonY);

    //Update input field positions 
    updateEditInputFields();
}

void EditSection::updateEditInputFields(){
    nextInputFieldY = titleRect.y + titleHeight + 20;

    for (int i=0; i < inputFields.size() ;i++){
        inputFields[i].rect.y = nextInputFieldY;
        inputFields[i].rect.x = rect.x + static_cast<int>(width * 0.3);

        nextInputFieldY = nextInputFieldY + inputFieldHeight*1.2;
    }
}

void EditSection::update(int mouseX, int mouseY, bool mousePressed){
    confirmButton->update(mouseX, mouseY, mousePressed);
}

// SECTION Callbacks
void EditSection::stopEditing(){
    active = false;
}
