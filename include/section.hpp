#pragma once 

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "editSection.hpp"
#include "colors.hpp"
#include "button.hpp"


class Button;
class Section;
class EditSection;

class Section{
	public:
		Section(int newID, SDL_Renderer* renderer, TTF_Font* newFont, int x, int y, int width, int height);
		~Section();
		
		// SECTION Setter
		void setWidth(int newWidth);
		void setHeight(int newHeight);
		void setTitle(const char* newTitle);
        void setDragging(bool newDragging);

		// SECTION Getter
		int getWidth();
		int getHeight();
		const char* getTitle();
		SDL_Rect getRect();
        bool getDragging();
        int getID();

		// SECTION Drawer
		void drawSection();
        void drawSectionTitle();
        void drawEditButton();
        void drawDeleteButton();
        void drawValue();

        // SECTION Actions
        bool pointInRect(int x, int y);
        bool pointInDragBar(int x, int y);
        void update(int mouseX, int mouseY, bool mousePressed);

        // SECTION Callbacks
        void editSection();
        void deleteSection(int id);
        std::function<void()> setDelete;

	private:
        int x, y, width, height, id;
		const char* title = "New Section";
        SDL_Texture* titleTexture;
        SDL_Rect titleRect;
        TTF_Font* font;
		SDL_Rect rect;
        SDL_Rect dragBar;
        SDL_Renderer* renderer;
		int value;
		Color color = WHITE;
        Color borderColor = DARKGREY;
        Color textColor = BLACK;
        bool dragging = false;
        int mouseXOffSet = 0;
        int mouseYOffSet = 0;
        std::unique_ptr<Button> editButton;
        std::unique_ptr<Button> deleteButton;
        std::unique_ptr<EditSection> editWindow;
};
