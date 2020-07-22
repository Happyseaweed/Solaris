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

    this->font.loadFromFile("media/zero_hour.ttf");

// Titlescreen
    // Main Title
    this->mainTitles.setFont(font);
    this->mainTitles.setCharacterSize(150);
    this->mainTitles.setString("SoLARiS - Beta");
    FloatRect bounds = mainTitles.getLocalBounds();
    this->mainTitles.setPosition((SCREEN_WIDTH - bounds.width)/2, 400);
    this->mainTitles.setFillColor(Color::White);

    // PLay Button
    this->playButton.setSize(Vector2f(500, 180));
    this->playButton.setFillColor(Color::White);
    this->pressed = false;
    bounds = playButton.getLocalBounds();
    this->playButton.setPosition( (SCREEN_WIDTH - bounds.width)/2, (SCREEN_HEIGHT - bounds.height)/2);
    
    // Play Button Text
    this->playText.setFont(font);
    this->playText.setCharacterSize(69);
    this->playText.setFillColor(Color::Black);
    this->playText.setString("PLAY");
    bounds = playText.getLocalBounds();
    this->playText.setPosition((SCREEN_WIDTH - bounds.width)/2, this->playButton.getPosition().y+50);

    // Quit Button
    this->quitButton.setSize(Vector2f(500, 180));
    this->quitButton.setFillColor(Color::White);
    this->pressed = false;
    bounds = quitButton.getLocalBounds();
    this->quitButton.setPosition( (SCREEN_WIDTH - bounds.width)/2, (SCREEN_HEIGHT - bounds.height)/2+200);

    // Quit Text
    this->quitText.setFont(font);
    this->quitText.setCharacterSize(69);
    this->quitText.setFillColor(Color::Black);
    this->quitText.setString("QUIT");
    bounds = quitText.getLocalBounds();
    this->quitText.setPosition((SCREEN_WIDTH - bounds.width)/2, this->quitButton.getPosition().y+50);

// Ship
    this->background.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    this->background.setPosition(Vector2f(0, 0));
    this->background.setFillColor(sf::Color::Red);

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
        //titlescreen_update();
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

// Title Screen ---------------------------------------------------------------------------------------//

void solaris::titlescreen_logic(){
    // Mouse clicks the button
    if (playButton.getGlobalBounds().contains(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y) ){

        if (pressed) {
            cout << "ahmed has small pp" << endl;
            nextState = SHIP;
        }
    }
    if (quitButton.getGlobalBounds().contains(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y) ){
        if (pressed){
            this->window->close();
        }
    }

}

void solaris::titlescreen_render(){
    this->window->clear();
    this->window->draw(mainTitles);
    this->window->draw(playButton);
    this->window->draw(playText);
    this->window->draw(quitButton);
    this->window->draw(quitText);
    this->window->display();

}

void solaris::titlescreen_update(){
    switch(event.type){
        case sf::Event::MouseButtonPressed:
            pressed = true;
            break;
        case sf::Event::MouseButtonReleased:
            pressed = false;
            break;
    }

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
    this->window->clear();
    this->window->draw(this->background);
    this->window->display();
}

void solaris::ship_update(){

}


//  Main Update Function
void solaris::update(){
    this->pollEvents();
    switch (gameState) {
        case TITLESCREEN:
            titlescreen_update();
            break;
        case SHIP:
            ship_update();
            break;
    }
}
// Main Logic Function
void solaris::logic(){
    switch (gameState) {
        case TITLESCREEN:
            titlescreen_logic();
            break;
        case SHIP:
            ship_logic();
            break;
    }
}
// Render functions
void solaris::render(){
    switch (gameState) {
        case TITLESCREEN:
            titlescreen_render();
            break;
        case SHIP:
            ship_render();
            break;

    }


}
