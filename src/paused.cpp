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