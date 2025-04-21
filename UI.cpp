#include "surface.h"
#include "template.h"
#include "game.h"
#include "UI.h"
#include <Windows.h>
#include <SDL.h>

UI::UI(Tmpl8::Surface* screen, std::vector<Rect> buttons)
	:screen(screen), buttons(buttons)
{
	onButton.resize(buttons.size(), true);
}



void UI::draw(bool showHitbox)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		screen->Box(buttons[i].x, buttons[i].y, buttons[i].x + buttons[i].w, buttons[i].y + buttons[i].h, 0x0000ff);
	}
}

bool UI::clicked()
{
	if (pushed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UI::showMouse(bool showMouse, Tmpl8::Surface* screen, int mouseX, int mouseY)
{
	if (showMouse)
	{
		screen->Box(mouseX - 2, mouseY - 2, mouseX + 2, mouseY + 2, 0x00ff00); // Draw the mouse to the screen
	}	
	MouseX = mouseX;
	MouseY = mouseY;
}

void UI::checkButtons()
{
	
	for (int i = 0; i < buttons.size(); i++)
	{
		if (MouseX > buttons[i].x && 
			MouseX < buttons[i].x + buttons[i].w && 
			MouseY > buttons[i].y && 
			MouseY < buttons[i].y + buttons[i].h)
		{
			onButton[i] = true;
			std::cout << onButton[i] << '\n';
		}
		else
		{
			onButton[i] = false;
		}
	}
}

int playButtonx1 = ScreenWidth / 3;
int playButtonx2 = ScreenWidth / 3 * 2;
int playButtony1 = 200;
int playButtony2 = 300;
bool pressed = false;


bool UI::pressedPlay()
{
	
	if (onButton[0] == true && pushed == true)
	{
		pressed = true;
	}
	if (pressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UI::mouseDown(int button)
{
	switch (button)
	{
		case 1
		:pushed = true;
	}
}

void UI::mouseUp(int button)
{
	switch (button)
	{
		case 1
		:pushed = false;
	}
}
