#pragma once
#include "SpriteSheet.h"
#include <memory>
#include "game.h"

class UI
{
public:
	UI() = default; // Constructor.
	UI(Tmpl8::Surface* screen, std::vector<Rect> buttons);
	~UI() = default; // Destructor.

	void draw(bool showHitbox); // Draw the UI buttons
	bool clicked(); // Check if the mouse is clicked
	void checkButtons(); // Check which button is hovered over
	int clickedButton(); // Check which button is clicked
	void makeUsable(Player& player, Coin& coin); // Check which button is clicked and do something
	void showMouse(bool showMouse, Tmpl8::Surface* screen, int mouseX, int mouseY); // Show the mouse on the screen
	bool pressedPlay(); // Check if the play button is pressed
	void resetPlay(); // Reset the play button
	void mouseDown(int button); // Check if the mouse is clicked
	void mouseUp(int button); // Check if the mouse is released

private:
	int MouseX = 0;
	int MouseY = 0;
	std::vector<Rect> buttons;
	Tmpl8::Surface* screen;
	bool pushed = false;
	int onButton = -1;
	bool wasPushed = false;
	
};