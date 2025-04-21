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

	void showMouse(bool showMouse, Tmpl8::Surface* screen, int mouseX, int mouseY);
	bool pressedPlay(Tmpl8::Surface* screen, bool showborder);

private:
	int MouseX = 0;
	int MouseY = 0;
	std::vector<Rect> buttons;
	Tmpl8::Surface* screen;
	
};