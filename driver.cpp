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

#include "driver.h"

using namespace std;
using namespace sf;

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
}

void solaris::initWindow(){
    // Window
	this->videoMode.height = SCREEN_HEIGHT;
    this->videoMode.width = SCREEN_WIDTH;
    this->window = new RenderWindow(this->videoMode, "onnichan~");

    // Frames
    this->window->setFramerateLimit(60);
}


// Accessors
const bool solaris::running() const {
    return this->window->isOpen();
}

// Event functions
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

// Update Functions
void solaris::update(){
    this->pollEvents();
}

// Render functions
void solaris::render(){
    // Clear old frame
    this->window->clear();
    // Load new frames and stuff:

    // Render new stuff: 
    this->window->display();

}