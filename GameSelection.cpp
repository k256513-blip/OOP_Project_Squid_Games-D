#include "GameSelection.h"
#include <algorithm>
GameSelection::GameSelection()
{
    font.loadFromFile("snapitc.ttf");

    // Load background image
    backgroundTexture.loadFromFile("MENU2.jpg");

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


    float backgroundScale =
        std::max(
            scaleX,
            scaleY
        );


    background.setScale(
        backgroundScale,
        backgroundScale
    );


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
    // SELECTION STATES
    // =========================================================

    redLightSelected = false;
    dalgonaSelected = false;
    tugOfWarSelected = false;
    glassBridgeSelected = false;
    squidGameSelected = false;


    // =========================================================
 // TITLE
 // =========================================================

    title.setFont(font);

    title.setString(
        "Choose the games you want to play in this session"
    );

    title.setCharacterSize(32);

    title.setFillColor(
        sf::Color::Black
    );

    title.setPosition(
        250,
        80
    );
    // =========================================================
    // RED LIGHT, GREEN LIGHT
    // =========================================================

    redLightGreenLight.setFont(font);
    redLightGreenLight.setString(
        "Red Light, Green Light"
    );
    redLightGreenLight.setCharacterSize(28);
    redLightGreenLight.setPosition(450, 183);


    redLightButton.setSize(
        sf::Vector2f(400, 50)
    );

    redLightButton.setPosition(
        430, 170
    );

    redLightButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    redLightButton.setOutlineColor(
        sf::Color(255, 255, 255, 100)
    );

    redLightButton.setOutlineThickness(
        2.0f
    );


    // =========================================================
    // DALGONA
    // =========================================================

    dalgona.setFont(font);
    dalgona.setString("Dalgona");
    dalgona.setCharacterSize(28);
    dalgona.setPosition(450, 243);


    dalgonaButton.setSize(
        sf::Vector2f(400, 50)
    );

    dalgonaButton.setPosition(
        430, 230
    );

    dalgonaButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    dalgonaButton.setOutlineColor(
        sf::Color(255, 255, 255, 100)
    );

    dalgonaButton.setOutlineThickness(
        2.0f
    );


    // =========================================================
    // TUG OF WAR
    // =========================================================

    tugOfWar.setFont(font);
    tugOfWar.setString("Tug of War");
    tugOfWar.setCharacterSize(28);
    tugOfWar.setPosition(450, 303);


    tugOfWarButton.setSize(
        sf::Vector2f(400, 50)
    );

    tugOfWarButton.setPosition(
        430, 290
    );

    tugOfWarButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    tugOfWarButton.setOutlineColor(
        sf::Color(255, 255, 255, 100)
    );

    tugOfWarButton.setOutlineThickness(
        2.0f
    );


    // =========================================================
    // GLASS STEPPING STONES
    // =========================================================

    glassBridge.setFont(font);
    glassBridge.setString(
        "Glass Stepping Stones"
    );
    glassBridge.setCharacterSize(28);
    glassBridge.setPosition(450, 363);


    glassBridgeButton.setSize(
        sf::Vector2f(400, 50)
    );

    glassBridgeButton.setPosition(
        430, 350
    );

    glassBridgeButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    glassBridgeButton.setOutlineColor(
        sf::Color(255, 255, 255, 100)
    );

    glassBridgeButton.setOutlineThickness(
        2.0f
    );


    // =========================================================
    // SQUID GAME
    // =========================================================

    squidGame.setFont(font);
    squidGame.setString(
        "Squid Game"
    );
    squidGame.setCharacterSize(28);
    squidGame.setPosition(450, 423);


    squidGameButton.setSize(
        sf::Vector2f(400, 50)
    );

    squidGameButton.setPosition(
        430, 410
    );

    squidGameButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    squidGameButton.setOutlineColor(
        sf::Color(255, 255, 255, 100)
    );

    squidGameButton.setOutlineThickness(
        2.0f
    );


    // =========================================================
    // CONTINUE BUTTON
    // =========================================================

    continueButton.setFont(font);
    continueButton.setString("Continue");
    continueButton.setCharacterSize(32);
    continueButton.setPosition(500, 523);


    continueButtonBox.setSize(
        sf::Vector2f(300, 55)
    );

    continueButtonBox.setPosition(
        470, 510
    );

    continueButtonBox.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    continueButtonBox.setOutlineColor(
        sf::Color(255, 255, 255, 100)
    );

    continueButtonBox.setOutlineThickness(
        2.0f
    );
}


// =============================================================
// DRAW
// =============================================================

void GameSelection::draw(
    sf::RenderWindow& window
)
{
    // Background
    window.draw(background);

    // Title
    window.draw(title);


    // Game buttons
    window.draw(redLightButton);
    window.draw(dalgonaButton);
    window.draw(tugOfWarButton);
    window.draw(glassBridgeButton);
    window.draw(squidGameButton);


    // Game text
    window.draw(redLightGreenLight);
    window.draw(dalgona);
    window.draw(tugOfWar);
    window.draw(glassBridge);
    window.draw(squidGame);


    // Continue button
    window.draw(continueButtonBox);
    window.draw(continueButton);
}


// =============================================================
// INPUT
// =============================================================

GameState GameSelection::handleInput(
    sf::Event& event
)
{
    float mouseX = 0.0f;
    float mouseY = 0.0f;


    // Get mouse position
    if (event.type == sf::Event::MouseMoved)
    {
        mouseX =
            static_cast<float>(
                event.mouseMove.x
                );

        mouseY =
            static_cast<float>(
                event.mouseMove.y
                );
    }
    else if (
        event.type == sf::Event::MouseButtonPressed
        )
    {
        mouseX =
            static_cast<float>(
                event.mouseButton.x
                );

        mouseY =
            static_cast<float>(
                event.mouseButton.y
                );
    }
    else
    {
        sf::Vector2i mousePosition =
            sf::Mouse::getPosition();

        mouseX =
            static_cast<float>(
                mousePosition.x
                );

        mouseY =
            static_cast<float>(
                mousePosition.y
                );
    }


    // =========================================================
    // DEFAULT BUTTON APPEARANCE
    // =========================================================

    redLightButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    dalgonaButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    tugOfWarButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    glassBridgeButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    squidGameButton.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    continueButtonBox.setFillColor(
        sf::Color(30, 30, 30, 180)
    );


    // =========================================================
    // HOVER EFFECT
    // =========================================================

    if (
        redLightButton
        .getGlobalBounds()
        .contains(mouseX, mouseY)
        )
    {
        redLightButton.setFillColor(
            sf::Color(255, 255, 255, 80)
        );
    }
    else if (
        dalgonaButton
        .getGlobalBounds()
        .contains(mouseX, mouseY)
        )
    {
        dalgonaButton.setFillColor(
            sf::Color(255, 255, 255, 80)
        );
    }
    else if (
        tugOfWarButton
        .getGlobalBounds()
        .contains(mouseX, mouseY)
        )
    {
        tugOfWarButton.setFillColor(
            sf::Color(255, 255, 255, 80)
        );
    }
    else if (
        glassBridgeButton
        .getGlobalBounds()
        .contains(mouseX, mouseY)
        )
    {
        glassBridgeButton.setFillColor(
            sf::Color(255, 255, 255, 80)
        );
    }
    else if (
        squidGameButton
        .getGlobalBounds()
        .contains(mouseX, mouseY)
        )
    {
        squidGameButton.setFillColor(
            sf::Color(255, 255, 255, 80)
        );
    }
    else if (
        continueButtonBox
        .getGlobalBounds()
        .contains(mouseX, mouseY)
        )
    {
        continueButtonBox.setFillColor(
            sf::Color(255, 255, 255, 80)
        );
    }


    // =========================================================
    // HANDLE CLICKS
    // =========================================================

    if (
        event.type == sf::Event::MouseButtonPressed
        &&
        event.mouseButton.button == sf::Mouse::Left
        )
    {
        // Red Light, Green Light
        if (
            redLightButton
            .getGlobalBounds()
            .contains(mouseX, mouseY)
            )
        {
            redLightSelected =
                !redLightSelected;
        }


        // Dalgona
        if (
            dalgonaButton
            .getGlobalBounds()
            .contains(mouseX, mouseY)
            )
        {
            dalgonaSelected =
                !dalgonaSelected;
        }


        // Tug of War
        if (
            tugOfWarButton
            .getGlobalBounds()
            .contains(mouseX, mouseY)
            )
        {
            tugOfWarSelected =
                !tugOfWarSelected;
        }


        // Glass Stepping Stones
        if (
            glassBridgeButton
            .getGlobalBounds()
            .contains(mouseX, mouseY)
            )
        {
            glassBridgeSelected =
                !glassBridgeSelected;
        }


        // Squid Game
        if (
            squidGameButton
            .getGlobalBounds()
            .contains(mouseX, mouseY)
            )
        {
            squidGameSelected =
                !squidGameSelected;
        }


        // Continue
        if (
            continueButtonBox
            .getGlobalBounds()
            .contains(mouseX, mouseY)
            )
        {
            if (
                redLightSelected ||
                dalgonaSelected ||
                tugOfWarSelected ||
                glassBridgeSelected ||
                squidGameSelected
                )
            {
                return GameState::Playing;
            }
        }
    }


    // =========================================================
    // SELECTED TEXT COLORS
    // =========================================================

    if (redLightSelected)
        redLightGreenLight.setFillColor(
            sf::Color::Green
        );
    else
        redLightGreenLight.setFillColor(
            sf::Color::White
        );


    if (dalgonaSelected)
        dalgona.setFillColor(
            sf::Color::Green
        );
    else
        dalgona.setFillColor(
            sf::Color::White
        );


    if (tugOfWarSelected)
        tugOfWar.setFillColor(
            sf::Color::Green
        );
    else
        tugOfWar.setFillColor(
            sf::Color::White
        );


    if (glassBridgeSelected)
        glassBridge.setFillColor(
            sf::Color::Green
        );
    else
        glassBridge.setFillColor(
            sf::Color::White
        );


    if (squidGameSelected)
        squidGame.setFillColor(
            sf::Color::Green
        );
    else
        squidGame.setFillColor(
            sf::Color::White
        );


    return GameState::GameSelection;
}


// =============================================================
// SELECTION GETTERS
// =============================================================

bool GameSelection::isRedLightSelected()
{
    return redLightSelected;
}


bool GameSelection::isDalgonaSelected()
{
    return dalgonaSelected;
}


bool GameSelection::isTugOfWarSelected()
{
    return tugOfWarSelected;
}


bool GameSelection::isGlassBridgeSelected()
{
    return glassBridgeSelected;
}


bool GameSelection::isSquidGameSelected()
{
    return squidGameSelected;
}