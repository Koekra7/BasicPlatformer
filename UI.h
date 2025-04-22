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

	void draw(bool showHitbox);
	bool clicked();
	void checkButtons();
	int clickedButton();
	void makeUsable(Player& player, Coin& coin);
	void showMouse(bool showMouse, Tmpl8::Surface* screen, int mouseX, int mouseY);
	bool pressedPlay();
	void resetPlay();
	void mouseDown(int button);
	void mouseUp(int button);

private:
	int MouseX = 0;
	int MouseY = 0;
	std::vector<Rect> buttons;
	Tmpl8::Surface* screen;
	bool pushed = false;
	int onButton = -1;
	bool wasPushed = false;
	
};