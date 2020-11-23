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

//Forward delcaration
class HealthBar;

#pragma once;

// Game state shiz
enum States {
    TITLESCREEN,
    PAUSED,
    OVERWORLD,
    SHIP,
    OUTERSPACE,
    STATE_NULL
};

// if you see this, ahmed is gay & has small pp
extern int gameState;
extern int nextState;


// Raycasting for player
class Ray {
private:
	// Position of ray
	Vector2f pos;
	// direction of ray
	Vector2f dir;

public:
	// points for line
	Vertex line[2];

	void lookAt(Vector2f p){
		// the direction is point - position
		dir.x = p.x - pos.x;
		dir.y = p.y - pos.y;

		// normalize the vector
		dir = normalize(dir);

		// change the line
		line[0] = pos;
		Vector2f newPos = Vector2f(pos.x+dir.x*10, pos.y+dir.y*10);
		line[1] = newPos;
	}

	// set the position
	void setPos(Vector2f newPos) {
		pos = newPos;
	}

	// normalize the vector
	Vector2f normalize(const Vector2f vec){
		// get the magnitude of vector
		float mag = (float) sqrt( (vec.x*vec.x) + (vec.y*vec.y) );

		// divide by magnitude if not 0
		if (mag != 0){
			return Vector2f(vec.x/mag, vec.y/mag);
		}
		return vec;
	}

	Vector2f cast(FloatRect a){
		float x1, y1, x2, y2;
		float distance = 999999999999;
		Vector2f pt;
		for (int i = 0; i < 4; i++){
			// Left side
			if (i == 0){
				x1 = a.left;
				y1 = a.top;

				x2 = a.left;
				y2 = a.top+a.height;

			// Top side
			} else if (i == 1) {
				x1 = a.left;
				y1 = a.top;
				x2 = a.left+a.width;
				y2 = a.top;

			// Right side
			} else if (i == 2) {
				x1 = a.left+a.width;
				y1 = a.top;
				x2 = a.left+a.width;
				y2 = a.top+a.height;

			// Bottom side
			} else if (i == 3) {
				x1 = a.left+a.width;
				y1 = a.top+a.height;
				x2 = a.left;
				y2 = a.top+a.height;
			}

			// Ray 
			float x3 = pos.x;
			float y3 = pos.y;
			float x4 = pos.x + dir.x;
			float y4 = pos.y + dir.y;


			// deninmator
			float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
			if (den == 0){
				continue;
			}

			float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
			float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

			// if it intersects
			if (t > 0 && t < 1) {
				Vector2f tempPt = Vector2f (x1+t*(x2 - x1), y1+t*(y2-y1));
				
				if (sqrt( pow(pos.x - tempPt.x, 2) + pow(pos.y - tempPt.y, 2) ) < distance){
					distance = sqrt( pow(pos.x - tempPt.x, 2) + pow(pos.y - tempPt.y, 2) );
					pt = tempPt;
				}
			} else {
				continue;
			}
		}
		if (distance == 999999999999){
			return pos;
		}
		return pt;
	}
};


// Solaris class
class solaris {
	friend class HealthBar;
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
		

		// Outerspace
		Texture backgroundTex;
		Sprite spaceBackground;
		Sprite astro; // Technically the player sprite
		Texture astroTex;
		Texture astroLeftTex;
		Texture astroRightTex;
		Vector2f astroVel;
		Shader shader;

		// Ray testing
		Ray ray1;
		CircleShape pt;

		// COLLISION BLOCK TEST
		Sprite block;
		Texture bloc;
		Vector2f blockVel;
		Vector2f blockAcc;
		float blocRotVel;
		float blocRotAcc;

		// Habitat
		Sprite habitat;
		Texture habTexture;
		

		Vector2f astroAcc;
		float astroRotVel;
		float astroRotAcc;
		Vector2f dir;
		void astroApplyForce(Vector2f force);
		void astroRotateForce(float d);
		void teleport(Vector2f position);
		
		void set_camera();
		View camera;
		float SPACE_WIDTH;
		float SPACE_HEIGHT;
		float astroSpeed;



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

		// space
		void outerspace_logic();
		void outerspace_render();
		void outerspace_update();

		// Public Functions
		void logic();
		void render();
		void update();
		void pollEvents();
};


// No one knows why tf this is here
void change_state();
