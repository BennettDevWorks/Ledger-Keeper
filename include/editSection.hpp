#pragma once 

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "colors.hpp"
#include "button.hpp"

struct InputField{
    SDL_Rect rect;
    const char* label;
    char text[256];
    bool isActive;
};


class EditSection{
    public: 
        EditSection(SDL_Renderer* renderer, TTF_Font* newFont, int x, int y, int width, int height); 
        ~EditSection();

        // SECTION Setter 
        void setX(int);
        void setY(int);
        void setWidth(int);
        void setHeight(int);
        void setTitle(const char*);
        void setActive();

        // SECTION Getter
        int getWidth();
        int getHeight();
        bool getIsActive();
        const char* getTitle();
        SDL_Rect getRect();

        // SECTION Drawer
        void drawSection();
        void drawSectionTitle();
        void drawConfirmButton();
        void drawEditInputFields();

        // SECTION Action
        bool pointInRect(int, int, SDL_Rect*);
        void addEditInputField(const char* newLabel);
        void update(int mouseX, int mouseY, bool mousePressed);
        void updatePos(int newX, int newY);
        void updateEditInputFields();
        void stopEditing();

    private:
        int x, y, width, height;
        const char* title = "Edit Section";
        SDL_Texture* titleTexture;
        SDL_Rect titleRect;
        int titleX, titleY, titleWidth, titleHeight;
        TTF_Font* font;
        SDL_Rect rect;
        SDL_Renderer* renderer;
        Color color = WHITE;
        Color borderColor = DARKGREY;
        Color textColor = BLACK;
        std::unique_ptr<Button> confirmButton;
        std::vector<InputField> inputFields;
        bool dragging = false;
        bool active = false;
        int nextInputFieldX, nextInputFieldY;
        int inputFieldWidth, inputFieldHeight;
};
