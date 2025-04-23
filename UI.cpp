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



void UI::draw(bool showHitbox) // Draw the UI buttons
{
	for (int i = 0; i < buttons.size(); i++)
	{
		screen->Box(buttons[i].x, buttons[i].y, buttons[i].x + buttons[i].w, buttons[i].y + buttons[i].h, 0x0000ff);
	}
}


bool UI::clicked() // Check if the mouse is clicked
	{
	if (pushed && !wasPushed) // make shure the clicked only triggers once and not multiple times
       {  
		   wasPushed = true;
		   return true; 
       }
		return false;
	}


void UI::showMouse(bool showMouse, Tmpl8::Surface* screen, int mouseX, int mouseY) // Show the mouse on the screen
{
	if (showMouse)
	{
		screen->Box(mouseX - 2, mouseY - 2, mouseX + 2, mouseY + 2, 0x0000ff); // Draw the mouse to the screen
	}	
	MouseX = mouseX; 
	MouseY = mouseY;
}

void UI::checkButtons() // Check which button is hovered over
{
	
	for (int i = 0; i < buttons.size(); i++) // check for all the buttons
	{
		if (MouseX > buttons[i].x && 
			MouseX < buttons[i].x + buttons[i].w && 
			MouseY > buttons[i].y && 
			MouseY < buttons[i].y + buttons[i].h)
		{
			onButton = i; // onbutton is set to the button that is hovered over
			break;
		}
		else
		{
			onButton = -1;
		}
	}
}

int UI::clickedButton() // Check which button is clicked
{
	for (int i = 0; i < buttons.size(); i++) // check for all the buttons
	{
		if (onButton >= 0 && clicked() == true) // if the the mouse is clicked and the mouse is hovering over a button
		{
			return onButton;
			std::cout << "clicked on button " << i << '\n'; // Debug output

		}
	}
	return -1;
}

float speedmod = 1;
float jumpmod = 1;

void UI::makeUsable(Player& player, Coin& coin) // Check which button is clicked and do something
{
	//std::cout << onButton << '\n';
	switch (clickedButton()) // Check which button is clicked
	{
	case -1:
		

		break;
	case 0: //start button

		std::cout << "case0" << '\n';
		break;
	case 1: //reset button

		std::cout << "case1" << '\n';
		exit(0);
		break;
	case 2: //upgrade speed

		std::cout << "case2" << '\n';
		
		if (coin.getCoins() >= 5) // if the player has enough coins/eggs
		{
			speedmod += 0.1; // adding speed
			std::cout << "speedmod" << "=" << speedmod << '\n';
			coin.setCoins(coin.getCoins() - 5); // reducing the coins/eggs
		}
		else
		{
			std::cout << "cant do that yet" << '\n';
		}
		
		break;
	case 3: //upgrade jump

		std::cout << "case3" << '\n';

		if (coin.getCoins() >= 5) // if the player has enough coins / eggs
		{
			jumpmod += 0.1; // adding jump
			std::cout << "jumpmod" << "=" << jumpmod << '\n';
			coin.setCoins(coin.getCoins() - 5); // reducing the coins/eggs
		}
		else
		{
			std::cout << "cant do that yet" << '\n';
		}

		break;
	}
	
	
	player.SetSpeed(speedmod, jumpmod); // setting the speed and jump boost
}

bool pressed = false;


bool UI::pressedPlay() // Check if the play button is pressed
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

void UI::resetPlay() // Reset the play button
{
	pressed = false;
	pushed = false;
}

void UI::mouseDown(int button) // Check if the mouse is clicked
{
	switch (button)
	{
		case 1:
			pushed = true;
			break;
	}
}

void UI::mouseUp(int button) // Check if the mouse is released
{
	switch (button)
	{
		case 1:
			pushed = false;
			wasPushed = false;
			break;
	}
}
