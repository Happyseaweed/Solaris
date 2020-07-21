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

#define ll long long

#include "../include/driver.h"

using namespace std;
using namespace sf;

// Game state shiz
enum States {
    TITLESCREEN,
    PAUSED,
    OVERWORLD,
    SHIP,
    STATE_NULL
};

// variables for gamestates
int gameState = TITLESCREEN;
int nextState = STATE_NULL;

// handles changing states if necessary
void change_state() {
    if (gameState != STATE_NULL) {
        switch (nextState) {
            case TITLESCREEN:
                gameState = TITLESCREEN;
                nextState = STATE_NULL;
                break;
            case PAUSED:
                gameState = PAUSED;
                nextState = STATE_NULL;
                break;
            case OVERWORLD:
                gameState = OVERWORLD;
                nextState = STATE_NULL;
            case SHIP:
                gameState = SHIP;
                nextState = STATE_NULL;
        }
    }
}

// Constructors:
solaris::solaris(){
    this->initVariables();
    this->initWindow();
}

solaris::~solaris(){
    delete this->window;
}
// Initialization functions
void solaris::initVariables(){
    this->window = nullptr;

    this->font.loadFromFile("zero_hour.ttf");

    // Titlescreen
    this->playButton.setSize(Vector2f(500, 250));
    this->playButton.setPosition(690, 690);
    this->playButton.setFillColor(Color::White);

}

void solaris::initWindow(){
    // Window
	this->videoMode.height = SCREEN_HEIGHT;
    this->videoMode.width = SCREEN_WIDTH;
    this->window = new RenderWindow(this->videoMode, "Solaris - Beta");

    // Frames
    this->window->setFramerateLimit(60);
}


// Accessors
const bool solaris::running() const {
    return this->window->isOpen();
}

// Event functions ----------------------------------------------------------- //
void solaris::pollEvents(){
    // Event polling;

    while(this->window->pollEvent(this->event)){
        switch(event.type){
            case Event::Closed:
                this->window->close();
            case Event::KeyPressed:
                if (this->event.key.code == Keyboard::Escape){
                    this->window->close();
                }
            break;
        }
    }
}

// Title Screen --------------------------------------------------------------//

void solaris::titlescreen_logic(){
    // Mouse clicks the button
    if (playButton.getGlobalBounds().contains(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y) ){

        cout << "ahmed has small pp" << endl;
        nextState = SHIP;
    }

}

void solaris::titlescreen_render(){
    this->window->clear();
    this->window->draw(playButton);
    this->window->display();

}

void solaris::titlescreen_update(){

}

// Pause Screen --------------------------------------------------------------//

void solaris::paused_logic(){

}

void solaris::paused_render(){

}

void solaris::paused_update(){

}

// OVERWORLD Screen-----------------------------------------------------------//

void solaris::overworld_logic(){

}

void solaris::overworld_render(){

}

void solaris::overworld_update(){

}

// SHIP Screen----------------------------------------------------------------//
void solaris::ship_logic(){

}

void solaris::ship_render(){

}

void solaris::ship_update(){

}


//  Main Update Function
void solaris::update(){
    this->pollEvents();
}
// Main Logic Function
void solaris::logic(){
    switch (gameState) {
        case TITLESCREEN:
            titlescreen_logic();
    }
}
// Render functions
void solaris::render(){


    switch (gameState) {
        case TITLESCREEN:
            titlescreen_render();
    }


}
