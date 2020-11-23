#include "../include/UI.h"
#include "../include/driver.h"
//#include "driver.cpp"


void HealthBar::display(RenderWindow *win, solaris *game) {
    if (gameState == OUTERSPACE){
        // positioning the health bar
        displaySprite.setPosition(game->astro.getPosition().x + SCREEN_WIDTH/2, 
                                  game->astro.getPosition().y + SCREEN_HEIGHT/2);

        // display the sprite
        win->draw(displaySprite);

    }
}

void HealthBar::logic() {
    
}