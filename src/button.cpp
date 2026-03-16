#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.hpp"
#include "button.hpp"
#include "colors.hpp"


struct _TTF_Font;
using TTF_Font = _TTF_Font;

//------------------Button---------------------
Button::Button(SDL_Renderer* renderer, TTF_Font* newFont, int x, int y, const char* title, int width, int height)
: renderer(renderer), title(title), font(newFont) {
	rect = SDL_Rect{x, y, width, height};
	TTF_SizeText(font, title, &textWidth, &textHeight);

	textX = rect.x + (rect.w - textWidth) / 2;
	textY = rect.y + (rect.h - textHeight) / 2;
}

Button::~Button(){}

//Setters
void Button::setWidth(int newWidth){
	rect.w = newWidth;
	textX = rect.x + (rect.w - textWidth / 2);
}
void Button::setHeight(int newHeight){
	rect.h= newHeight;
	textY = rect.h + (rect.h - fontSize) / 2;
}
void Button::setTitle(const char* newTitle){
	title = newTitle;
	textX = rect.x + (rect.w - textWidth / 2);
	textY = rect.h + (rect.h - fontSize) / 2;
}
void Button::setColor(Color newColor){color = newColor;}
void Button::setIsActive(bool newIsActive){isActive = newIsActive;}

//Getters
int Button::getWidth(){return rect.w;}
int Button::getHeight(){return rect.h;}
bool Button::getIsActive(){return isActive;}
Color Button::getColor(){return color;}
Color Button::getActiveColor(){return activeColor;}
Color Button::getStandByeColor(){return standbyeColor;}
const SDL_Rect& Button::getRect() const {return rect;} 

//Drawers
void Button::drawButton(){
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);

    //Draw Border
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &rect);

    //Draw Text
    SDL_Color  sdlTextColor = {textColor.r, textColor.g, textColor.b, textColor.a};
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, title, sdlTextColor);

    if (!textSurface){
        //std::cout << "Text render error" << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    textWidth = textSurface->w;
    textHeight = textSurface->h;

    //Center text in button
    textX = rect.x + (rect.w - textWidth) / 2;
    textY= rect.y + (rect.h - textHeight) / 2;

    SDL_Rect textRect = {textX, textY, textWidth, textHeight};
    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}

//Actions
