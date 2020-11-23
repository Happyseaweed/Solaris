#include "../include/UI.h"
#include "../include/driver.h"
//#include "driver.cpp"

HealthBar::HealthBar(){
    tex1.loadFromFile("astro.png");
    tex2.loadFromFile("astro.png");
    tex3.loadFromFile("astro.png");
    tex4.loadFromFile("astro.png");
    tex5.loadFromFile("astro.png");

    displayStates.push_back(tex1);
    displayStates.push_back(tex2);
    displayStates.push_back(tex3);
    displayStates.push_back(tex4);
    displayStates.push_back(tex5);
}
void HealthBar::display(RenderWindow *win, solaris *game) {
    if (gameState == OUTERSPACE){
        // positioning the health bar
        displaySprite.setPosition(game->astro.getPosition().x + SCREEN_WIDTH/2, 
                                  game->astro.getPosition().y + SCREEN_HEIGHT/2);

        // display the sprite
        win->draw(displaySprite);
    }
}

void HealthBar::logic(int health) {

   if (health > 80) {
       displaySprite.setTexture(tex1);
   } else if (health > 60) {
       displaySprite.setTexture(tex2);
   } else if (health > 40) {
       displaySprite.setTexture(tex3);
   } else if (health > 20) {
       displaySprite.setTexture(tex4);
   } else {
       displaySprite.setTexture(tex5);
   }
}