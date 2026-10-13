#include "MainMenu.h"
#include <algorithm>

MainMenu::MainMenu()
{
    // =========================================================
    // FONTS
    // =========================================================

    font.loadFromFile(
        "arial.ttf"
    );

    titleFont.loadFromFile(
        "snapitc.ttf"
    );


    // =========================================================
    // AUDIO
    // =========================================================

    menuMusic.openFromFile(
        "MainmenuSTP2.mp3"
    );

    menuMusic.setLoop(
        true
    );

    menuMusic.setVolume(
        50
    );


    hoverBuffer.loadFromFile(
        "UIhoverSTP2.mp3"
    );

    hoverSound.setBuffer(
        hoverBuffer
    );

    hoverSound.setVolume(
        70
    );


    clickBuffer.loadFromFile(
        "ButtonclickSTP2.mp3"
    );

    clickSound.setBuffer(
        clickBuffer
    );

    clickSound.setVolume(
        80
    );


    hoveredButton =
        -1;

    mouseWasPressed =
        false;

    optionsOpen =
        false;

    menuMusicEnabled =
        true;


    menuMusic.play();


    // =========================================================
    // BACKGROUND
    // =========================================================

    backgroundTexture.loadFromFile(
        "SQUID GAME MM2.jpg"
    );


    background.setTexture(
        backgroundTexture
    );


    sf::Vector2u textureSize =
        backgroundTexture.getSize();


    float scaleX =
        1280.0f /
        static_cast<float>(
            textureSize.x
            );


    float scaleY =
        720.0f /
        static_cast<float>(
            textureSize.y
            );


    // Use the larger scale so the whole screen is covered.
    float backgroundScale =
        std::max(
            scaleX,
            scaleY
        );


    background.setScale(
        backgroundScale,
        backgroundScale
    );


    // Centre the oversized image so cropping happens evenly.
    sf::FloatRect backgroundBounds =
        background.getGlobalBounds();


    background.setPosition(
        (
            1280.0f -
            backgroundBounds.width
            ) /
        2.0f,

        (
            720.0f -
            backgroundBounds.height
            ) /
        2.0f
    );


    // =========================================================
    // TITLE
    // =========================================================

    


    // =========================================================
    // SINGLE PLAYER
    // =========================================================

    singlePlayer.setFont(
        font
    );


    singlePlayer.setString(
        "Single Player"
    );


    singlePlayer.setCharacterSize(
        32
    );


    singlePlayer.setFillColor(
        sf::Color::White
    );


    singlePlayerButton.setSize(
        sf::Vector2f(
            330,
            60
        )
    );


    singlePlayerButton.setPosition(
        475,
        230
    );


    singlePlayerButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    singlePlayerButton.setOutlineColor(
        sf::Color(
            255,
            255,
            255,
            100
        )
    );


    singlePlayerButton.setOutlineThickness(
        2.0f
    );


    singlePlayer.setPosition(
        555,
        243
    );


    // =========================================================
    // MULTIPLAYER
    // =========================================================

    multiplayer.setFont(
        font
    );


    multiplayer.setString(
        "Multiplayer"
    );


    multiplayer.setCharacterSize(
        32
    );


    multiplayer.setFillColor(
        sf::Color::White
    );


    multiplayerButton.setSize(
        sf::Vector2f(
            330,
            60
        )
    );


    multiplayerButton.setPosition(
        475,
        300
    );


    multiplayerButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    multiplayerButton.setOutlineColor(
        sf::Color(
            255,
            255,
            255,
            100
        )
    );


    multiplayerButton.setOutlineThickness(
        2.0f
    );


    multiplayer.setPosition(
        565,
        313
    );


    // =========================================================
    // OPTIONS
    // =========================================================

    options.setFont(
        font
    );


    options.setString(
        "Options"
    );


    options.setCharacterSize(
        32
    );


    options.setFillColor(
        sf::Color::White
    );


    optionsButton.setSize(
        sf::Vector2f(
            330,
            60
        )
    );


    optionsButton.setPosition(
        475,
        370
    );


    optionsButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    optionsButton.setOutlineColor(
        sf::Color(
            255,
            255,
            255,
            100
        )
    );


    optionsButton.setOutlineThickness(
        2.0f
    );


    options.setPosition(
        585,
        383
    );


    // =========================================================
    // EXIT GAME
    // =========================================================

    exitGame.setFont(
        font
    );


    exitGame.setString(
        "Exit Game"
    );


    exitGame.setCharacterSize(
        32
    );


    exitGame.setFillColor(
        sf::Color::White
    );


    exitGameButton.setSize(
        sf::Vector2f(
            330,
            60
        )
    );


    exitGameButton.setPosition(
        475,
        440
    );


    exitGameButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    exitGameButton.setOutlineColor(
        sf::Color(
            255,
            255,
            255,
            100
        )
    );


    exitGameButton.setOutlineThickness(
        2.0f
    );


    exitGame.setPosition(
        570,
        453
    );


    // =========================================================
    // OPTIONS SCREEN TITLE
    // =========================================================

    optionsTitle.setFont(
        titleFont
    );


    optionsTitle.setString(
        "Options"
    );


    optionsTitle.setCharacterSize(
        56
    );


    optionsTitle.setFillColor(
        sf::Color::White
    );


    optionsTitle.setPosition(
        525,
        190
    );


    // =========================================================
    // MUSIC TOGGLE BUTTON
    // =========================================================

    musicToggleButton.setSize(
        sf::Vector2f(
            330,
            60
        )
    );


    musicToggleButton.setPosition(
        475,
        310
    );


    musicToggleButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    musicToggleButton.setOutlineColor(
        sf::Color(
            255,
            255,
            255,
            100
        )
    );


    musicToggleButton.setOutlineThickness(
        2.0f
    );


    musicToggleText.setFont(
        font
    );


    musicToggleText.setString(
        "Menu Music: ON"
    );


    musicToggleText.setCharacterSize(
        28
    );


    musicToggleText.setFillColor(
        sf::Color::White
    );


    musicToggleText.setPosition(
        525,
        323
    );


    // =========================================================
    // BACK BUTTON
    // =========================================================

    backButton.setSize(
        sf::Vector2f(
            330,
            60
        )
    );


    backButton.setPosition(
        475,
        390
    );


    backButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    backButton.setOutlineColor(
        sf::Color(
            255,
            255,
            255,
            100
        )
    );


    backButton.setOutlineThickness(
        2.0f
    );


    backText.setFont(
        font
    );


    backText.setString(
        "Back"
    );


    backText.setCharacterSize(
        30
    );


    backText.setFillColor(
        sf::Color::White
    );


    backText.setPosition(
        605,
        403
    );
}


// =============================================================
// DRAW
// =============================================================

void MainMenu::draw(
    sf::RenderWindow& window
)
{
    window.draw(
        background
    );



    // =========================================================
    // OPTIONS SCREEN
    // =========================================================

    if (
        optionsOpen
        )
    {
        window.draw(
            optionsTitle
        );


        window.draw(
            musicToggleButton
        );


        window.draw(
            backButton
        );


        window.draw(
            musicToggleText
        );


        window.draw(
            backText
        );


        return;
    }


    // =========================================================
    // NORMAL MAIN MENU
    // =========================================================

    window.draw(
        singlePlayerButton
    );


    window.draw(
        multiplayerButton
    );


    window.draw(
        optionsButton
    );


    window.draw(
        exitGameButton
    );


    window.draw(
        singlePlayer
    );


    window.draw(
        multiplayer
    );


    window.draw(
        options
    );


    window.draw(
        exitGame
    );
}


// =============================================================
// INPUT
// =============================================================

GameState MainMenu::handleInput(
    sf::RenderWindow& window
)
{
    sf::Vector2i mousePosition =
        sf::Mouse::getPosition(
            window
        );


    float mouseX =
        static_cast<float>(
            mousePosition.x
            );


    float mouseY =
        static_cast<float>(
            mousePosition.y
            );


    bool mousePressed =
        sf::Mouse::isButtonPressed(
            sf::Mouse::Left
        );


    // =========================================================
    // OPTIONS SCREEN
    // =========================================================

    if (
        optionsOpen
        )
    {
        musicToggleButton.setFillColor(
            sf::Color(
                30,
                30,
                30,
                180
            )
        );


        backButton.setFillColor(
            sf::Color(
                30,
                30,
                30,
                180
            )
        );


        int newHoveredButton =
            -1;


        // -----------------------------------------------------
        // MUSIC TOGGLE HOVER
        // -----------------------------------------------------

        if (
            musicToggleButton
            .getGlobalBounds()
            .contains(
                mouseX,
                mouseY
            )
            )
        {
            newHoveredButton =
                4;


            musicToggleButton.setFillColor(
                sf::Color(
                    255,
                    255,
                    255,
                    80
                )
            );
        }


        // -----------------------------------------------------
        // BACK HOVER
        // -----------------------------------------------------

        else if (
            backButton
            .getGlobalBounds()
            .contains(
                mouseX,
                mouseY
            )
            )
        {
            newHoveredButton =
                5;


            backButton.setFillColor(
                sf::Color(
                    255,
                    255,
                    255,
                    80
                )
            );
        }


        // -----------------------------------------------------
        // HOVER SOUND
        // -----------------------------------------------------

        if (
            newHoveredButton !=
            hoveredButton
            )
        {
            if (
                newHoveredButton !=
                -1
                )
            {
                hoverSound.play();
            }


            hoveredButton =
                newHoveredButton;
        }


        // -----------------------------------------------------
        // CLICK
        //
        // Only fires when mouse FIRST becomes pressed.
        // Prevents ON/OFF from rapidly toggling.
        // -----------------------------------------------------

        if (
            mousePressed &&
            !mouseWasPressed
            )
        {
            // =================================================
            // MUSIC ON / OFF
            // =================================================

            if (
                musicToggleButton
                .getGlobalBounds()
                .contains(
                    mouseX,
                    mouseY
                )
                )
            {
                clickSound.play();


                menuMusicEnabled =
                    !menuMusicEnabled;


                if (
                    menuMusicEnabled
                    )
                {
                    musicToggleText.setString(
                        "Menu Music: ON"
                    );


                    playMusic();
                }

                else
                {
                    musicToggleText.setString(
                        "Menu Music: OFF"
                    );


                    stopMusic();
                }
            }


            // =================================================
            // BACK
            // =================================================

            else if (
                backButton
                .getGlobalBounds()
                .contains(
                    mouseX,
                    mouseY
                )
                )
            {
                clickSound.play();


                optionsOpen =
                    false;


                hoveredButton =
                    -1;
            }
        }


        mouseWasPressed =
            mousePressed;


        return
            GameState::MainMenu;
    }


    // =========================================================
    // NORMAL MAIN MENU
    // =========================================================

    singlePlayerButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    multiplayerButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    optionsButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    exitGameButton.setFillColor(
        sf::Color(
            30,
            30,
            30,
            180
        )
    );


    int newHoveredButton =
        -1;


    // =========================================================
    // HOVER
    // =========================================================

    if (
        singlePlayerButton
        .getGlobalBounds()
        .contains(
            mouseX,
            mouseY
        )
        )
    {
        newHoveredButton =
            0;


        singlePlayerButton.setFillColor(
            sf::Color(
                255,
                255,
                255,
                80
            )
        );
    }


    else if (
        multiplayerButton
        .getGlobalBounds()
        .contains(
            mouseX,
            mouseY
        )
        )
    {
        newHoveredButton =
            1;


        multiplayerButton.setFillColor(
            sf::Color(
                255,
                255,
                255,
                80
            )
        );
    }


    else if (
        optionsButton
        .getGlobalBounds()
        .contains(
            mouseX,
            mouseY
        )
        )
    {
        newHoveredButton =
            2;


        optionsButton.setFillColor(
            sf::Color(
                255,
                255,
                255,
                80
            )
        );
    }


    else if (
        exitGameButton
        .getGlobalBounds()
        .contains(
            mouseX,
            mouseY
        )
        )
    {
        newHoveredButton =
            3;


        exitGameButton.setFillColor(
            sf::Color(
                255,
                255,
                255,
                80
            )
        );
    }


    // =========================================================
    // HOVER SOUND
    // =========================================================

    if (
        newHoveredButton !=
        hoveredButton
        )
    {
        if (
            newHoveredButton !=
            -1
            )
        {
            hoverSound.play();
        }


        hoveredButton =
            newHoveredButton;
    }


    // =========================================================
    // CLICK
    // =========================================================

    if (
        mousePressed &&
        !mouseWasPressed
        )
    {
        // =====================================================
        // SINGLE PLAYER
        // =====================================================

        if (
            singlePlayerButton
            .getGlobalBounds()
            .contains(
                mouseX,
                mouseY
            )
            )
        {
            clickSound.play();


            mouseWasPressed =
                mousePressed;


            return
                GameState::GameSelection;
        }


        // =====================================================
        // MULTIPLAYER
        // =====================================================

        if (
            multiplayerButton
            .getGlobalBounds()
            .contains(
                mouseX,
                mouseY
            )
            )
        {
            clickSound.play();


            mouseWasPressed =
                mousePressed;


            return
                GameState::GameSelection;
        }


        // =====================================================
        // OPTIONS
        // =====================================================

        if (
            optionsButton
            .getGlobalBounds()
            .contains(
                mouseX,
                mouseY
            )
            )
        {
            clickSound.play();


            optionsOpen =
                true;


            hoveredButton =
                -1;
        }


        // =====================================================
        // EXIT
        // =====================================================

        if (
            exitGameButton
            .getGlobalBounds()
            .contains(
                mouseX,
                mouseY
            )
            )
        {
            clickSound.play();

            window.close();
        }
    }


    mouseWasPressed =
        mousePressed;


    return
        GameState::MainMenu;
}


// =============================================================
// STOP MUSIC
// =============================================================

void MainMenu::stopMusic()
{
    menuMusic.stop();
}


// =============================================================
// PLAY MUSIC
// =============================================================

void MainMenu::playMusic()
{
    if (
        menuMusicEnabled &&
        menuMusic.getStatus() !=
        sf::Music::Playing
        )
    {
        menuMusic.play();
    }
}