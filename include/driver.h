#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <stack>
#include <fstream>
#include <stdio.h>
#include <map>

// SFML Stuff:
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Personal Preference stuff:
#define ll long long
#define SCREEN_WIDTH 3200
#define SCREEN_HEIGHT 2400

//Namespaces
using namespace std;
using namespace sf;

#pragma once;

class solaris {
	private:
		// Windows & Events
		RenderWindow* window;
		Event event;
		VideoMode videoMode;

		// Private Functions;
		void initVariables();
		void initWindow();
		void initAhmedSmallPP();

		// Private variables;
		Font font;

		// Titlescreen
		RectangleShape playButton;
		bool playPressed;

		// Ship
		RectangleShape background;




	public:
		solaris();
		virtual ~solaris();

		// Window running boolean
		const bool running() const;

		// Gamestate function declaration
		// Title screen
		void titlescreen_logic();
		void titlescreen_render();
		void titlescreen_update();

		// Paused
		void paused_logic();
		void paused_render();
		void paused_update();

		// Overworld
		void overworld_logic();
		void overworld_render();
		void overworld_update();

		// Ship
		void ship_logic();
		void ship_render();
		void ship_update();

		// Public Functions
		void logic();
		void render();
		void update();
		void pollEvents();
};

void change_state();
