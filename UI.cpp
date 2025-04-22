#include "surface.h"
#include "template.h"
#include "game.h"
#include "UI.h"
#include <Windows.h>
#include <SDL.h>

UI::UI(Tmpl8::Surface* screen, std::vector<Rect> buttons)
	:screen(screen), buttons(buttons)
{
	
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
       if (pushed && !wasPushed)
       {  
		   wasPushed = true;
		   return true; 
       }
		return false;
	}


void UI::showMouse(bool showMouse, Tmpl8::Surface* screen, int mouseX, int mouseY)
{
	if (showMouse)
	{
		screen->Box(mouseX - 2, mouseY - 2, mouseX + 2, mouseY + 2, 0x0000ff); // Draw the mouse to the screen
	}	
	MouseX = mouseX;
	MouseY = mouseY;
}

void UI::checkButtons()
{
	
	for (int i = 0; i <= 3; i++)
	{
		if (MouseX > buttons[i].x && 
			MouseX < buttons[i].x + buttons[i].w && 
			MouseY > buttons[i].y && 
			MouseY < buttons[i].y + buttons[i].h)
		{
			onButton = i;
			break;
		}
		else
		{
			onButton = -1;
		}
	}
}

int UI::clickedButton()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (onButton >= 0 && clicked() == true)
		{
			return onButton;
			std::cout << "clicked on button " << i << '\n'; // Debug output

		}
	}
	return -1;
}

float speedmod = 1;
float jumpmod = 1;

void UI::makeUsable(Player& player, Coin& coin)
{
	//std::cout << onButton << '\n';
	switch (clickedButton())
	{
	case -1:
		

		break;
	case 0: //start button

		std::cout << "case0" << '\n';
		break;
	case 1: //reset button

		std::cout << "case1" << '\n';
		break;
	case 2: //upgrade speed

		std::cout << "case2" << '\n';
		
		if (coin.getCoins() >= 3)
		{
			speedmod += 0.5;
			std::cout << "speedmod" << "=" << speedmod << '\n';
			coin.setCoins(coin.getCoins() - 3);
		}
		else
		{
			std::cout << "cant do that yet" << '\n';
		}
		
		break;
	case 3: //upgrade jump

		std::cout << "case3" << '\n';

		if (coin.getCoins() >= 3)
		{
			jumpmod += 0.5;
			std::cout << "jumpmod" << "=" << speedmod << '\n';
			coin.setCoins(coin.getCoins() - 3);
		}
		else
		{
			std::cout << "cant do that yet" << '\n';
		}

		break;
	}
	player.SetSpeed(speedmod, jumpmod);
}

bool pressed = false;


bool UI::pressedPlay()
{
	
	if (onButton == 0 && clicked() == true)
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

void UI::resetPlay()
{
	pressed = false;
	pushed = false;
}

void UI::mouseDown(int button)
{
	switch (button)
	{
		case 1:
			pushed = true;
			break;
	}
}

void UI::mouseUp(int button)
{
	switch (button)
	{
		case 1:
			pushed = false;
			wasPushed = false;
			break;
	}
}
