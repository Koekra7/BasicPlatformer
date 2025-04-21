#include "surface.h"
#include "template.h"
#include "game.h"
#include "UI.h"
#include <Windows.h>

UI::UI(Tmpl8::Surface* screen, std::vector<Rect> buttons)
	:screen(screen), buttons(buttons)
{
	
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

int playButtonx1 = ScreenWidth / 3;
int playButtonx2 = ScreenWidth / 3 * 2;
int playButtony1 = 200;
int playButtony2 = 300;
bool pressed = false;


bool UI::pressedPlay(Tmpl8::Surface* screen, bool showborder)
{
	if (showborder && pressed != true) 
	{
		screen->Box(playButtonx1, playButtony1, playButtonx2, playButtony2, 0xffffff);
	}

	if (MouseX > playButtonx1 && MouseX < playButtonx2 && MouseY > playButtony1 && MouseY < playButtony2 && (GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		std::printf("Play button pressed\n");
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
