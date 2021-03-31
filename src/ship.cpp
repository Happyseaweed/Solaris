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

// Ship screens
void solaris::ship_logic(){
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
            astroRotateForce(-0.75);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
            astroRotateForce(0.75);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Space)){
            teleport(Vector2f(this->pt.getPosition().x, this->pt.getPosition().y));
            //astroVel.x += 1;
            //astroVel.y += 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::F) && intRange){
            nextState = SHIP;
        }
    }
}
void solaris::ship_render(){
    // set the camera
    set_camera();
    this->window->setView(camera);

    this->pt.setRadius(10);
    this->pt.setOrigin(pt.getRadius(), pt.getRadius() );
    this->pt.setPosition(ray1.cast(block.getGlobalBounds()));

    // drawing scene
    this->window->clear();
    // this->window->draw(this->spaceBackground);
    this->window->draw(this->astro);
    this->window->draw(this->habitat);
    this->window->draw(pt);
    this->window->draw(this->ray1.line, 20, Lines);
    if (intRange) this->window->draw(this->interactionButton);

    // Drawing GUI
    this->window->setView(guiView);
    this->window->draw(this->circleHealth);
    this->window->draw(this->oxygenTank100);
    this->window->draw(this->healthBar);
    this->window->draw(this->oxygenBar);

    this->window->setView(miniView);
    // std::cout << "miniPlayer X: " << miniPlayer.getPosition().x << "| miniPlayer Y: " << miniPlayer.getPosition().y << std::endl;
    // std::cout << "astro X: " << astro.getPosition().x << "| astro Y: " << astro.getPosition().y << std::endl;
    this->window->draw(this->miniSprite);
    this->window->draw(this->miniPlayer);
    this->window->display();
}
void solaris::ship_update(){
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

    // Reset astrocceleration so program doesn't bReAk
    this->astroRotAcc = 0;
    this->astroAcc.x = 0;
    this->astroAcc.y = 0;

    // RAY TESTING
    ray1.setPos(astro.getPosition());
    ray1.lookAt(Vector2f(this->window->mapPixelToCoords(Mouse::getPosition(*this->window)) ));

    // MINIMAP
    sf::Vector2f viewSize = miniView.getSize();
    sf::Vector2f bigSize = sf::Vector2f (SPACE_WIDTH, SPACE_HEIGHT);
    sf::Vector2f astroPos = astro.getPosition();
    sf::Vector2f convertPos = sf::Vector2f(viewSize.x / (bigSize.x / astroPos.x), viewSize.y / (bigSize.y / astroPos.y));
    miniPlayer.setPosition(convertPos);
    miniPlayer.setColor(sf::Color(255, 255, 255, showMap*255));
    miniSprite.setColor(sf::Color(255, 255, 255, showMap*255));
}