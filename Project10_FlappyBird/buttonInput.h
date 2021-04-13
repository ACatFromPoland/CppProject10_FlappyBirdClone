#pragma once
#include <SFML/Graphics.hpp>

class newPressMouse {
public:
	bool toggleclick = false;
	sf::Mouse::Button givenbutton;
	newPressMouse(sf::Mouse::Button gb) {
		givenbutton = gb;
	}

	bool isPressed() {
		if (sf::Mouse::isButtonPressed(givenbutton)) {
			if (!toggleclick) {
				toggleclick = true;
				return true;
			}
		}
		else
		{
			toggleclick = false;
		}
		return false;
	}
};

class newPressKey {
public:
	bool togglekey = false;
	sf::Keyboard::Key givenkey;
	newPressKey(sf::Keyboard::Key gk) {
		givenkey = gk;
	}

	bool isPressed() {
		if (sf::Keyboard::isKeyPressed(givenkey)) {
			if (!togglekey) {
				togglekey = true;
				return true;
			}
		}
		else if (!sf::Keyboard::isKeyPressed(givenkey)) {
			togglekey = false;
		}
		return false;
	}
};

class newToggleKey {
public:

	sf::Keyboard::Key givenkey;
	newToggleKey(sf::Keyboard::Key gk) {
		givenkey = gk;
	}

	bool pressedkey = false;
	bool togglekey = false;

	bool isToggled() {
		if (sf::Keyboard::isKeyPressed(givenkey)) {
			if (!pressedkey)
				if (!togglekey)
					togglekey = true;

				else if (togglekey)
					togglekey = false;
			pressedkey = true;
		}
		if (!sf::Keyboard::isKeyPressed(givenkey)) {
			pressedkey = false;
		}

		return togglekey;
	}
};

class newHoldKey {
public:

};