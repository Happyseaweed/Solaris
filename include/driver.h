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
#define SCREEN_WIDTH VideoMode::getDesktopMode().width
#define SCREEN_HEIGHT VideoMode::getDesktopMode().height

//Namespaces
using namespace std;
using namespace sf;

#pragma once;

// if you see this, ahmed is gay & has small pp

// Solaris class
class solaris {
	private:
		// Windows & Events
		RenderWindow* window;
		Event event;
		VideoMode videoMode;

		// Private Functions;
		void initVariables();
		void initWindow();

		// Private variables;
		Font font;
		Clock clock;
		float dt;


		// Titlescreen Variables
		RectangleShape playButton;
		RectangleShape quitButton;
		
		Text mainTitles;
		Text playText;
		Text quitText;
		
		bool pressed;
		

		// Ship
		Texture backgroundTex;
		Sprite background;
		Sprite ship; // Technically the player sprite
		Texture shipTex;
		Vector2f shipVel;

		Vector2f shipAcc;
		float shipRotVel;
		float shipRotAcc;
		Vector2f dir;
		void shipApplyForce(Vector2f force);
		void shipRotateForce(float d);
		
		void set_camera();
		View camera;
		float SPACE_WIDTH;
		float SPACE_HEIGHT;
		float shipSpeed;


		// Paused variable
		RectangleShape pausedBackground;

		RectangleShape resumeButton, quitPause;
		Text resumeText, quitPauseText;
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
