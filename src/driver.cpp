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
<<<<<<< HEAD
// Paused
    // resume button
    this->resumeButton.setSize(Vector2f(500, 180));
    this->resumeButton.setFillColor(Color::White);
    FloatRect bounds = resumeButton.getLocalBounds();
    this->resumeButton.setPosition( (SCREEN_WIDTH - bounds.width)/2, (SCREEN_HEIGHT - bounds.height)/2);

    // return to the main screen
    this->quitPause.setSize(Vector2f(500, 180));
    this->quitPause.setFillColor(Color::White);
    bounds = quitPause.getLocalBounds();
    this->quitPause.setPosition( (SCREEN_WIDTH - bounds.width)/2, (SCREEN_HEIGHT - bounds.height)/2+200);

    // resume text
    this->resumeText.setFont(font);
    this->resumeText.setCharacterSize(69);
    this->resumeText.setFillColor(Color::Black);
    this->resumeText.setString("RESUME");
    bounds = resumeText.getLocalBounds();
    this->resumeText.setPosition((SCREEN_WIDTH - bounds.width)/2, this->resumeButton.getPosition().y+50);

    // quit pause text
    this->quitPauseText.setFont(font);
    this->quitPauseText.setCharacterSize(69);
    this->quitPauseText.setFillColor(Color::Black);
    this->quitPauseText.setString("RESUME");
    bounds = quitPauseText.getLocalBounds();
    this->quitPauseText.setPosition((SCREEN_WIDTH - bounds.width)/2, this->quitPause.getPosition().y+50);
=======
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce

// Titlescreen
    // Main Title
    this->mainTitles.setFont(font);
    this->mainTitles.setCharacterSize(150);
    this->mainTitles.setString("SoLARiS - Beta");
<<<<<<< HEAD
    bounds = mainTitles.getLocalBounds();
    this->mainTitles.setPosition((SCREEN_WIDTH - bounds.width)/2, 400);
    this->mainTitles.setFillColor(Color::White);
 
=======
    FloatRect bounds = mainTitles.getLocalBounds();
    this->mainTitles.setPosition((SCREEN_WIDTH - bounds.width)/2, 400);
    this->mainTitles.setFillColor(Color::White);

>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce
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
<<<<<<< HEAD
    this->backgroundTex.loadFromFile("media/bgimg.jpg");
    this->background.setTexture(backgroundTex);
    this->background.setPosition(Vector2f(0, 0));
    this->shipSpeed = 0.5;

    
    // Moving Camera Section
    SPACE_WIDTH = backgroundTex.getSize().x;
    SPACE_HEIGHT = backgroundTex.getSize().y;
    this->camera.setCenter(Vector2f(SPACE_WIDTH/2, SPACE_HEIGHT/2));
    this->camera.setSize(Vector2f(SCREEN_WIDTH/2.5, SCREEN_HEIGHT/2.5));

    // Loading texture
    this->shipTex.loadFromFile("media/astronaut-Solaris.png");
    this->ship.setTexture(shipTex);
    this->ship.setOrigin(Vector2f(this->shipTex.getSize().x/2, this->shipTex.getSize().y/2 ));
    this->ship.setScale(Vector2f(5.0f, 5.0f));
=======
    this->background.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    this->background.setPosition(Vector2f(0, 0));
    this->background.setFillColor(sf::Color::Red);

    this->ship.setSize(Vector2f(100, 400));
    this->ship.setOrigin(Vector2f(this->ship.getSize().x/2, this->ship.getSize().y/2 ));
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce
    this->ship.setPosition(250, 250);
    this->shipVel = Vector2f(0, 0);
    this->shipAcc = Vector2f(0, 0);

}

void solaris::shipApplyForce(Vector2f force) {
    this->shipAcc += force;
}

void solaris::shipRotateForce(float d) {
    this->shipRotAcc += d;
}
void solaris::initWindow(){
    // Window
	this->videoMode.height = SCREEN_HEIGHT;
    this->videoMode.width = SCREEN_WIDTH;
    this->window = new RenderWindow(this->videoMode, "Solaris - Beta");

    // Frames
    this->window->setFramerateLimit(60);
<<<<<<< HEAD

=======
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce
}


// Accessors
const bool solaris::running() const {
    return this->window->isOpen();
}

<<<<<<< HEAD
void solaris::set_camera() {
    // Centering the camera
    camera.setCenter(ship.getPosition().x,
                     ship.getPosition().y);
    
    // Checking for camera going out of bounds
    if (camera.getCenter().x - camera.getSize().x/2 < 0){
        camera.setCenter(0+camera.getSize().x/2, camera.getCenter().y);
    }

    if (camera.getCenter().x + camera.getSize().x/2 > SPACE_WIDTH){
        camera.setCenter(SPACE_WIDTH - camera.getSize().x/2, camera.getCenter().y);
    }

    if (camera.getCenter().y - camera.getSize().y/2 < 0){
        camera.setCenter(camera.getCenter().x, 0+camera.getSize().y/2 );
    }

    if (camera.getCenter().y + camera.getSize().y/2 > SPACE_HEIGHT){
        camera.setCenter(camera.getCenter().x, SPACE_HEIGHT - camera.getSize().y/2);
    }
}


=======
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce
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
<<<<<<< HEAD
                    if (gameState == TITLESCREEN) this->window->close();
                    else if (gameState == SHIP) nextState = PAUSED;
                    else if (gameState == PAUSED) nextState = SHIP;
=======
                    this->window->close();
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce
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
<<<<<<< HEAD
    if (resumeButton.getGlobalBounds().contains(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y) ){
        if (pressed) {
                nextState = SHIP;
            }
    }
    if (quitPause.getGlobalBounds().contains(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y) ){
        if (pressed){
            nextState = TITLESCREEN;
        }
    }
}

void solaris::paused_render(){
    this->window->clear();
    this->window->draw(resumeButton);
    this->window->draw(resumeText);
    this->window->draw(quitPause);
    this->window->draw(quitPauseText);
    this->window->display();
}

void solaris::paused_update(){
    this->window->setView(this->window->getDefaultView());
=======

}

void solaris::paused_render(){

}

void solaris::paused_update(){

>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce
}

// OVERWORLD Screen-----------------------------------------------------------//

<<<<<<< HEAD
void solaris::overworld_logic() {

}

void solaris::overworld_render() {
=======
void solaris::overworld_logic(){

}

void solaris::overworld_render(){
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce

}

void solaris::overworld_update(){

}

// SHIP Screen----------------------------------------------------------------//
void solaris::ship_logic(){
    // collison for walls
     if (this->ship.getLocalBounds().top < 0 || this->ship.getLocalBounds().top > SCREEN_HEIGHT){
        this->shipVel.x = 0;
        this->shipVel.y = 0; 
     } else {
        // movement for ship
<<<<<<< HEAD
        if (Keyboard::isKeyPressed(Keyboard::Key::W)){
            shipApplyForce(Vector2f(0, -shipSpeed));
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            shipApplyForce(Vector2f(-shipSpeed, 0));
        } 
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            shipApplyForce(Vector2f(shipSpeed, 0));
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
            shipApplyForce(Vector2f(0, shipSpeed));
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
            shipRotateForce(-0.5);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
            shipRotateForce(0.5);
        }
=======
        if (Keyboard::isKeyPressed(Keyboard::Key::Space)){
            this->shipVel.x = dir.x * 10.0f;
            this->shipVel.y = dir.y * 10.0f;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            shipRotateForce(-0.5);
        } if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            shipRotateForce(0.5);
        }

>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce
     }
    
}

void solaris::ship_render(){
    this->window->clear();
    this->window->draw(this->background);
    this->window->draw(this->ship);
    this->window->display();
}

void solaris::ship_update(){
<<<<<<< HEAD
    this->window->setView(camera);
=======
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce
    // getting direction
    dir.y = -std::cos(( this->ship.getRotation() * 3.14) / 180);
    dir.x = std::sin(( this->ship.getRotation() * 3.14) / 180);

<<<<<<< HEAD

    // applying the forces
    if (abs(shipVel.x) < 2 && abs(shipVel.y) < 2){
        this->shipVel += this->shipAcc;
    }
    this->shipRotVel += this->shipRotAcc;
    
    // Sprite Change depending on direction of movement
    if (this->shipVel.x > 0){
        this->shipTex.loadFromFile("media/astronaut-right.png");
        this->ship.setTexture(shipTex);
    } else {
        this->shipTex.loadFromFile("media/astronaut-left.png");
        this->ship.setTexture(shipTex);
    }
    if (this->shipVel == Vector2f(0, 0)){
        this->shipTex.loadFromFile("media/astronaut-Solaris.png");
        this->ship.setTexture(shipTex);
    }
=======
    // applying the forces
    this->shipRotVel += this->shipRotAcc;
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce

    // move/rotate ship
    this->ship.rotate(this->shipRotVel);
    this->ship.move(this->shipVel);

    // dispating forces
    this->shipVel.x *= 0.99;
    this->shipVel.y *= 0.99;
    this->shipRotVel *= 0.8;
<<<<<<< HEAD
    if (abs(this->shipVel.x) < 0.1) this->shipVel.x = 0;
    if (abs(this->shipVel.y) < 0.1) this->shipVel.y = 0;


    // Reset Acceleration so program doesn't bReAk
    this->shipRotAcc = 0;
    this->shipAcc.x = 0;
    this->shipAcc.y = 0;

    // set the camera
    set_camera();
=======
    this->shipRotAcc = 0;
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce
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
<<<<<<< HEAD
        case PAUSED:
            paused_render();
            break;
=======
>>>>>>> b081b8f0b4ce1b89ab5e98ab4574193f21a2f3ce

    }


}
