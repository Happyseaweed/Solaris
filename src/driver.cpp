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
            case OUTERSPACE:
                gameState = OUTERSPACE;
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
    this->habTexture.loadFromFile("media/hab.png");
    this->habitat.setTexture(habTexture);
    this->habitat.setScale(Vector2f(5.0f, 5.0f));
    this->habitat.setPosition(Vector2f(600, 300));


    this->backgroundTex.loadFromFile("media/astronaut/bgimg.png");
    this->spaceBackground.setTexture(backgroundTex);
    this->spaceBackground.setScale(Vector2f(6, 6));
    this->spaceBackground.setPosition(Vector2f(0, 0));
    this->astroSpeed = 0.5;

    
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
    cout << "Texture Loaded." << endl;

    // Collision block test;
    this->bloc.loadFromFile("media/collision-block.png");
    this->block.setTexture(bloc);
    this->block.setOrigin(Vector2f(this->bloc.getSize().x/2, this->bloc.getSize().y/2));
    this->block.setScale(Vector2f(10.0f, 10.0f));
    this->block.setPosition(500, 500);
    this->blockVel = Vector2f(0, 0);
    this->blockAcc = Vector2f(0, 0);

    // OxygenTank
    cout << "Loading UI . . ." << endl;
    this->oTank.loadFromFile("media/oxygenTank100.png");
    this->oxygenTank100.setTexture(oTank);
    this->oxygenTank100.setOrigin(Vector2f(this->oTank.getSize().x/2, this->oTank.getSize().y/2));
    this->oxygenTank100.setScale(Vector2f(5.0f, 5.0f));
    cout << camera.x << endl;
    Vector2f oxygenPos = this->window->mapPixelToCoords(Vector2i(100, 100), camera);

    this->oxygenTank100.setPosition(100, 500);
    cout << "UI Loaded." << endl;
    
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
                    else if (gameState == PAUSED) nextState = SHIP;
                }
            break;
        }
    }


}

// Title Screen ---------------------------------------------------------------------------------------//

void solaris::titlescreen_logic(){
    // Mouse clicks the button
    // Play button
    if (playButton.getGlobalBounds().contains(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y) ){

        if (pressed) { // Clicks Play
            cout << "ahmed has small pp" << endl;
            pressed = false;
            nextState = OUTERSPACE;
        }
    }
    // Quit button
    if (quitButton.getGlobalBounds().contains(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y) ){
        if (pressed){ // Clicks the quit button
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
    // Resume button, when clicked, returns to previous state
    if (resumeButton.getGlobalBounds().contains(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y) ){
        if (pressed) {
            pressed = false;
            nextState = OUTERSPACE;
        }
    }
    // Quit button, when clicked, quits the program
    if (quitPause.getGlobalBounds().contains(Mouse::getPosition(*this->window).x, Mouse::getPosition(*this->window).y) ){
        if (pressed){
            pressed = false;
            this->window->close();
        }
    }
}

void solaris::paused_render(){
    this->window->setView(this->window->getDefaultView());
    this->window->clear();
    this->window->draw(resumeButton);
    this->window->draw(resumeText);
    this->window->draw(quitPause);
    this->window->draw(quitPauseText);
    this->window->display();
}

void solaris::paused_update(){

    switch(event.type){
        case sf::Event::MouseButtonPressed:
            pressed = true;
            break;
        case sf::Event::MouseButtonReleased:
            pressed = false;
            break;
    }
}

// OVERWORLD Screen-----------------------------------------------------------//

void solaris::overworld_logic() {

}

void solaris::overworld_render() {

}

void solaris::overworld_update(){

}

// outerspace Screen----------------------------------------------------------------//
void solaris::outerspace_logic(){
    // collison fpr walls
    if (this->astro.getGlobalBounds().top < 0 || this->astro.getGlobalBounds().top+this->astro.getGlobalBounds().height > SPACE_HEIGHT){
        this->astroVel.y *= -2; 
    } 
    else if (this->astro.getGlobalBounds().left < 0 || this->astro.getGlobalBounds().left+this->astro.getGlobalBounds().width > SPACE_WIDTH){
        this->astroVel.x *= -2;
    } else {
        // movement for ship
        if (Keyboard::isKeyPressed(Keyboard::Key::W)){
            astroApplyForce(Vector2f(0, -astroSpeed));
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            astroApplyForce(Vector2f(-astroSpeed, 0));
        } 
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            astroApplyForce(Vector2f(astroSpeed, 0));
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
            astroApplyForce(Vector2f(0, astroSpeed));
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
            astroRotateForce(-0.5);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
            astroRotateForce(0.5);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Space)){
            //teleport(Vector2f(this->pt.getPosition().x, this->pt.getPosition().y));
            astroVel.x += 1;
            astroVel.y += 1;
        }
    }
    // Block collision with Boundary
    if (this->block.getGlobalBounds().top < 0 || this->block.getGlobalBounds().top+this->block.getGlobalBounds().height > SPACE_HEIGHT){
        this->blockVel.y *= -2; 
    } 
    else if (this->block.getGlobalBounds().left < 0 || this->block.getGlobalBounds().left+this->block.getGlobalBounds().width > SPACE_WIDTH){
        this->blockVel.x *= -2;
    }

    // Block Collision with Player
    if (this->astro.getGlobalBounds().intersects(this->block.getGlobalBounds())){
        // get angle of collision with respect to block (as origin);
        
        // Centers of player and block
        Vector2f playerCenter = Vector2f(this->astro.getPosition().x/2, this->astro.getPosition().y/2);
        Vector2f blockCenter = Vector2f(this->block.getPosition().x/2, this->block.getPosition().y/2);
        // Differences 
        float xdif = playerCenter.x - blockCenter.x;
        float ydif = playerCenter.y - blockCenter.y;
        
        // angles + length
        float theta = (atan(ydif/xdif)*3.14159)/180; // angle relative to block
        float diff = sqrt(xdif*xdif + ydif*ydif); // length of collision vector, kinda useless at the moment

        // velocities of player
        float X = astroVel.x; 
        float Y = astroVel.y;

        float alpha = (atan(X/Y)*3.14159)/180;
        int colQuad = 0;

        if (xdif > 0 && ydif > 0) colQuad = 3;
        else if (xdif < 0 && ydif < 0) colQuad = 1;
        else if (xdif < 0 && ydif > 0) colQuad = 4;
        else if (xdif > 0 && ydif < 0) colQuad = 2;

        float phi = 0;

        if (colQuad == 1 || colQuad == 3){
            phi = min(alpha+theta, (90-alpha)+(90-theta) );
        }   
        else if (colQuad == 2 || colQuad == 4){
            phi = min(alpha + (90-theta), (90-alpha)+theta );
        }
        
        // rotation
        //blocRotAcc += sqrt(X*X + Y*Y) * cos(phi);

        // Get velocity
        blockVel.x = astroVel.x*2;
        blockVel.y = astroVel.y*2;
        astroVel.x *= -0.2;
        astroVel.y *= -0.2;

    }
    
}

void solaris::outerspace_render(){
    // set the camera
    set_camera();
    this->window->setView(camera);

    
    this->pt.setRadius(10);
    this->pt.setOrigin(pt.getRadius(), pt.getRadius() );
    this->pt.setPosition(ray1.cast(block.getGlobalBounds()));
  

    // drawing scene
    this->window->clear();
    this->window->draw(this->spaceBackground);
    this->window->draw(this->block);
    this->window->draw(this->astro);
    this->window->draw(this->habitat);
    this->window->draw(pt);
    this->window->draw(this->oxygenTank100);
    this->window->draw(this->ray1.line, 20, Lines);
    this->window->display();
}

void solaris::outerspace_update(){
    
    // getting direction
    dir.y = -std::cos(( this->astro.getRotation() * 3.14) / 180);
    dir.x = std::sin(( this->astro.getRotation() * 3.14) / 180);


    // apply astro forces
    if (abs(astroVel.x) < 2 && abs(astroVel.y) < 2){
        this->astroVel += this->astroAcc;
    }
    this->astroRotVel += this->astroRotAcc;
    this->blocRotVel += this->blocRotAcc;
    // Sprite astroge depending on direction of movement
    // Decided to store sprites seperately, instead of loading them everytime, to prevent glitches
    if (this->astroVel.x > 0){
        this->astro.setTexture(astroRightTex);
    } else {
        this->astro.setTexture(astroLeftTex);
    }
    if (this->astroVel == Vector2f(0, 0)){
        this->astro.setTexture(astroTex);
    }

    // moves/trotate ship
    this->astro.rotate(this->astroRotVel);
    this->astro.move(this->astroVel);
    this->block.move(this->blockVel);
    this->block.rotate(this->blocRotVel);
    //this->block.rotate(0.02);

    // disapating forces
    this->astroVel.x *= 0.99;
    this->astroVel.y *= 0.99;
    this->blockVel.x *= 0.5;
    this->blockVel.y *= 0.5;
    this->blocRotVel *= 0.8;
    this->astroRotVel *= 0.8;
    if (abs(this->astroVel.x) < 0.1) this->astroVel.x = 0;
    if (abs(this->astroVel.y) < 0.1) this->astroVel.y = 0;
    if (abs(this->blockVel.x) < 0.2) this->blockVel.x = 0;
    if (abs(this->blockVel.y) < 0.2) this->blockVel.y = 0;
    if (abs(this->astroRotVel) < 0.2) this->astroRotVel = 0;
    if (abs(this->blocRotVel) < 0.2) this->blocRotVel = 0;

    // Resastrocceleration so program doesn't bReAk

    this->astroRotAcc = 0;
    this->blocRotAcc = 0;
    this->astroAcc.x = 0;
    this->astroAcc.y = 0;

    // RAY TESTING
    ray1.setPos(astro.getPosition());
    ray1.lookAt(Vector2f(this->window->mapPixelToCoords(Mouse::getPosition(*this->window)) ));
}

// Ship screens
void solaris::ship_logic(){

}
void solaris::ship_render(){
    
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
