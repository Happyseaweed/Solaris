#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#pragma once
// Forward delcaration
extern class solaris;

// Class for UI
class UI {
public: 
    // function to display elements
    virtual void display(RenderWindow*, solaris*) = 0;

    // function to process data
    virtual void logic() = 0;
};


class HealthBar : public UI {
private:
    // images of states to display
    vector<Texture> displayStates;

    // current state
    int currState;
    Sprite displaySprite;

    // textures
    sf::Texture tex1, tex2, tex3, tex4, tex5;

    // constructor
    HealthBar();

public:
    void display(RenderWindow*, solaris*);
    void logic(int health);
};

