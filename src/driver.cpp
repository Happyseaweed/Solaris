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
#include <math.h>

#define ll long long

#include "../include/driver.h"
#include "../include/UI.h"

using namespace std;
using namespace sf;

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
                break;
            case OUTERSPACE:
                gameState = OUTERSPACE;
                nextState = STATE_NULL;
                break;
            case SHIP:
                gameState = SHIP;
                nextState = STATE_NULL;
                break;
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
    this->quitPauseText.setString("QUIT");
    bounds = quitPauseText.getLocalBounds();
    this->quitPauseText.setPosition((SCREEN_WIDTH - bounds.width)/2, this->quitPause.getPosition().y+50);

// Titlescreen
    // Main Title
    this->mainTitles.setFont(font);
    this->mainTitles.setCharacterSize(150);
    this->mainTitles.setString("SoLARiS - Beta");
    bounds = mainTitles.getLocalBounds();
    this->mainTitles.setPosition((SCREEN_WIDTH - bounds.width)/2, 400);
    this->mainTitles.setFillColor(Color::White);
 
    // Play Button
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
    this->habTexture.loadFromFile("media/hab.png");
    this->habitat.setTexture(habTexture);
    this->habitat.setScale(Vector2f(5.0f, 5.0f));
    this->habitat.setPosition(Vector2f(600, 300));

    this->backgroundTex.loadFromFile("media/astronaut/bgimg.png");
    this->spaceBackground.setTexture(backgroundTex);
    this->spaceBackground.setScale(Vector2f(6, 6));
    this->spaceBackground.setPosition(Vector2f(0, 0));
    this->astroSpeed = 1;
    
    // Moving Camera Section
    cout << "Loading Camera Section . . ." << endl;
    SPACE_WIDTH = spaceBackground.getTextureRect().width * spaceBackground.getScale().x;
    SPACE_HEIGHT = spaceBackground.getTextureRect().height * spaceBackground.getScale().y;
    this->camera.setCenter(Vector2f(SPACE_WIDTH/2, SPACE_HEIGHT/2));
    this->camera.setSize(Vector2f(SCREEN_WIDTH/2.5, SCREEN_HEIGHT/2.5));
    cout << "Camera Section Loaded." << endl;

    // Loading texture
    cout << "Loading Textures . . ." << endl;
    this->astroTex.loadFromFile("media/astronaut/astro-center.png");
    this->astroRightTex.loadFromFile("media/astronaut/astro-right.png");
    this->astroLeftTex.loadFromFile("media/astronaut/astro-left.png");
    this->astro.setTexture(astroTex);
    this->astro.setOrigin(Vector2f(this->astroTex.getSize().x/2, this->astroTex.getSize().y/2 ));
    this->astro.setScale(Vector2f(5.0f, 5.0f));
    this->astro.setPosition(250, 250);
    this->astroVel = Vector2f(0, 0);
    this->astroAcc = Vector2f(0, 0);
    this->astroRotAcc = 0;
    this->astroRotVel = 0;
    cout << "Texture Loaded." << endl;

    // Collision block test;
    // this->bloc.loadFromFile("media/collision-block.png");
    // this->block.setTexture(bloc);
    this->block.setOrigin(Vector2f(this->bloc.getSize().x/2, this->bloc.getSize().y/2));
    this->block.setScale(Vector2f(10.0f, 10.0f));
    this->block.setPosition(500, 500);
    this->blockVel = Vector2f(0, 0);
    this->blockAcc = Vector2f(0, 0);

    // OxygenTank
    
    cout << "Loading UI . . ." << endl;

    this->healthB.loadFromFile("media/lineHealthBar.png");
    this->healthBar.setTexture(healthB);
    //this->healthBar.setOrigin(Vector2f(this->healthB.getSize().x/2, this->healthB.getSize().y/2));
    this->healthBar.setScale(Vector2f(5.0f, 5.0f));
    this->healthBar.setPosition(0+50, 0+25);

    this->oxygenB.loadFromFile("media/lineOxygenTank.png");
    this->oxygenBar.setTexture(oxygenB);
    this->oxygenBar.setScale(Vector2f(5.0f, 5.0f));
    this->oxygenBar.setPosition(0+50, 0+200);

    cout << "UI Loaded." << endl;

    // Minimap
    cout << "Loading Minimap" << endl;
    this->miniTex.loadFromFile("media/minimap.png");
    this->miniPlayerTex.loadFromFile("media/astronaut/minipointer.png");
    this->miniSprite.setTexture(miniTex);
    this->miniPlayer.setTexture(miniPlayerTex);
    this->miniPlayer.setScale(sf::Vector2f(8,8));
    showMap = 1;

    // keyDown
    keyDown=true;
    // this->miniSprite.setOrigin(Vector2f(this->miniTex.getSize().x/2, this->miniTex.getSize().y/2));
    // this->miniSprite.setScale(Vector2f(0.5f, 0.5f));
    // this->miniSprite.setPosition(1000, 300);
    
    this->intButton.loadFromFile("media/interactionButton.png");
    this->interactionButton.setTexture(intButton);
    this->interactionButton.setOrigin(Vector2f(this->intButton.getSize().x/2, this->intButton.getSize().y/2));
    this->interactionButton.setScale(Vector2f(.75f, .75f));
    this->interactionButton.setPosition(1600, 700);
    this->intRange = false;

    // Shaders
    // shader.loadFromFile("include/blur.frag", Shader::Fragment);
    // shader.setParameter("texture", sf::Shader::CurrentTexture);
    // shader.setParameter("blur_radius", 201);
    
    // RAY CaSting
    ray1.setPos(astro.getPosition());
}

void solaris::astroApplyForce(Vector2f force) {
    this->astroAcc += force;
}

void solaris::astroRotateForce(float d) {
    this->astroRotAcc += d;
}

void solaris::teleport(Vector2f position){
    float x = position.x;
    float y = position.y;
    this->astro.setPosition(x, y);
}

void solaris::initWindow(){
    // Window
	this->videoMode.height = SCREEN_HEIGHT;
    this->videoMode.width = SCREEN_WIDTH;
    this->window = new RenderWindow(this->videoMode, "Solaris - Beta");

    // Frames
    this->window->setFramerateLimit(60);

    // Making GUI Views
    this->guiView = this->window->getDefaultView();
    //this->guiView.setViewport(sf::FloatRect(1, 1, 1, 1));
    this->miniView = this->window->getDefaultView();

    float padding = 0.005;
    this->miniView.setViewport(sf::FloatRect(0.75f-padding, 0.f+padding, 0.25f, 0.25f));
    this->miniSprite.setScale(sf::Vector2f(this->miniView.getSize().x/miniSprite.getTextureRect().width, this->miniView.getSize().y/miniSprite.getTextureRect().height));
}

// Accessors
const bool solaris::running() const {
    return this->window->isOpen();
}

void solaris::set_camera() {
    // Centering the camera
    camera.setCenter(astro.getPosition().x,
                     astro.getPosition().y);
    
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
                    if (gameState == TITLESCREEN) this->window->close();
                    else if (gameState == OUTERSPACE) nextState = PAUSED;
                    else if (gameState == PAUSED) nextState = OUTERSPACE;
                }
            break;
        }
    }
}


float solaris::interactionCurve(float t){
    return sin(1/(0.3+t));
}

//  Main Update Function
void solaris::update(){

    this->pollEvents();
    switch (gameState) {
        case TITLESCREEN:
            titlescreen_update();
            break;
        case OUTERSPACE:
            outerspace_update();
            break;
        case SHIP:
            ship_update();
            break;
        case PAUSED:
            paused_update();
            break;
    }
}

// Main Logic Function
void solaris::logic(){
    switch (gameState) {
        case TITLESCREEN:
            titlescreen_logic();
            break;
        case OUTERSPACE:
            outerspace_logic();
            break;
        case SHIP:
            ship_logic();
            break;
        case PAUSED:
            paused_logic();
            break;
    }
}

// Render functions
void solaris::render(){
    switch (gameState) {
        case TITLESCREEN:
            titlescreen_render();
            break;
        case OUTERSPACE:
            outerspace_render();
            break;
        case SHIP: // here
            ship_render();
            break;
        case PAUSED:
            paused_render();
            break;
    }
}