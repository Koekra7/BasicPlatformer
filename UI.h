#pragma once
#include "SpriteSheet.h"
#include <memory>
#include "game.h"

class UI
{
public:
	UI() = default; // Constructor.
	~UI() = default; // Destructor.

	void showMouse(bool showMouse, Tmpl8::Surface* screen, int mouseX, int mouseY);
	bool pressedPlay(Tmpl8::Surface* screen, bool showborder);

private:
	int MouseX = 0;
	int MouseY = 0;
};