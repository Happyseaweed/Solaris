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
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

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

		// Private variables;
		// ahmed has a small pp


	public:
		solaris();
		virtual ~solaris();

		// Window running boolean
		const bool running() const;

		// Public Functions
		void update();
		void render();
		void pollEvents();

};

































