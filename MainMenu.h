#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameState.h"


class MainMenu
{
private:

    sf::Font font;
    sf::Font titleFont;


    // =========================================================
    // BACKGROUND
    // =========================================================

    sf::Texture backgroundTexture;
    sf::Sprite background;


    // =========================================================
    // MAIN MENU TEXT
    // =========================================================

    sf::Text singlePlayer;
    sf::Text multiplayer;
    sf::Text options;
    sf::Text exitGame;


    // =========================================================
    // MAIN MENU BUTTONS
    // =========================================================

    sf::RectangleShape singlePlayerButton;
    sf::RectangleShape multiplayerButton;
    sf::RectangleShape optionsButton;
    sf::RectangleShape exitGameButton;


    // =========================================================
    // OPTIONS SCREEN
    // =========================================================

    sf::Text optionsTitle;

    sf::Text musicToggleText;
    sf::Text backText;

    sf::RectangleShape musicToggleButton;
    sf::RectangleShape backButton;

    bool optionsOpen;
    bool menuMusicEnabled;


    // =========================================================
    // AUDIO
    // =========================================================

    sf::Music menuMusic;

    sf::SoundBuffer hoverBuffer;
    sf::SoundBuffer clickBuffer;

    sf::Sound hoverSound;
    sf::Sound clickSound;


    // =========================================================
    // INPUT / HOVER
    // =========================================================

    int hoveredButton;

    bool mouseWasPressed;


public:

    MainMenu();


    GameState handleInput(
        sf::RenderWindow& window
    );


    void draw(
        sf::RenderWindow& window
    );


    void stopMusic();

    void playMusic();
};