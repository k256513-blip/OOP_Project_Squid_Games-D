#include "SquidGame.h"
#include <cmath>
#include <string>
#include <algorithm>
#include <cstdlib>

// =============================================================
// CONSTRUCTOR
// =============================================================

SquidGame::SquidGame()
{
    humanPlayer = nullptr;
    opponent = nullptr;


    gameStarted = false;
    gameFinished = false;
    fightResult =
        FightResult::None;
    resultButtonClicked =
        false;

    playerSpeed = 220.0f;
    opponentSpeed = 150.0f;

    opponentStopDistance = 120.0f;

    opponentState =
        OpponentState::Approach;

    opponentDecisionInterval =
        0.30f;

    

    // =========================================================
// BACKGROUND
// =========================================================

    if (
        backgroundTexture.loadFromFile(
            "SquidArena.png"
        )
        )
    {
        backgroundSprite.setTexture(
            backgroundTexture
        );


        sf::Vector2u backgroundSize =
            backgroundTexture.getSize();


        backgroundSprite.setScale(
            1280.0f /
            static_cast<float>(
                backgroundSize.x
                ),

            720.0f /
            static_cast<float>(
                backgroundSize.y
                )
        );


        backgroundSprite.setPosition(
            0.0f,
            0.0f
        );
    }



    // =========================================================
    // ARENA
    // =========================================================

    arenaLeft = 180.0f;
    arenaRight = 1100.0f;

    arenaTop = 120.0f;
    arenaBottom = 650.0f;


    arena.setPosition(
        arenaLeft,
        arenaTop
    );

    arena.setSize(
        sf::Vector2f(
            arenaRight - arenaLeft,
            arenaBottom - arenaTop
        )
    );

    arena.setFillColor(
        sf::Color::Transparent
    );

    arena.setOutlineColor(
        sf::Color::Transparent
    );

    arena.setOutlineThickness(
        0.0f
    );


    // =========================================================
    // FONT
    // =========================================================

    font.loadFromFile(
        "arial.ttf"
    );


    // =========================================================
// FINALIST SPRITES
// =========================================================

    std::string humanSpriteFiles[5] =
    {
        "PlayersSetA1.png",
        "PlayersSetA2.png",
        "PlayersSetA3.png",
        "PlayersSetA4.png",
        "PlayersSetA5.png"
    };


    std::string opponentSpriteFiles[5] =
    {
        "PlayersSetB1.png",
        "PlayersSetB2.png",
        "PlayersSetB3.png",
        "PlayersSetB4.png",
        "PlayersSetB5.png"
    };


    // ---------------------------------------------------------
    // HUMAN
    // ---------------------------------------------------------

    humanIdleTexture.loadFromFile(
        humanSpriteFiles[0]
    );

    humanIdleTexture.setSmooth(
        false
    );


    for (
        int i = 0;
        i < 5;
        i++
        )
    {
        humanWalkTextures[i]
            .loadFromFile(
                humanSpriteFiles[i]
            );

        humanWalkTextures[i]
            .setSmooth(
                false
            );
    }


    // ---------------------------------------------------------
    // OPPONENT
    // ---------------------------------------------------------

    opponentIdleTexture.loadFromFile(
        opponentSpriteFiles[0]
    );

    opponentIdleTexture.setSmooth(
        false
    );


    for (
        int i = 0;
        i < 5;
        i++
        )
    {
        opponentWalkTextures[i]
            .loadFromFile(
                opponentSpriteFiles[i]
            );

        opponentWalkTextures[i]
            .setSmooth(
                false
            );
    }


    // =========================================================
    // HUMAN SPRITE SETUP
    // =========================================================

    humanSprite.setTexture(
        humanIdleTexture
    );

    humanSprite.setTextureRect(
        sf::IntRect(
            64,
            32,
            16,
            32
        )
    );

    humanSprite.setOrigin(
        8.0f,
        16.0f
    );

    humanSprite.setScale(
        2.0f,
        2.0f
    );


    // =========================================================
    // OPPONENT SPRITE SETUP
    // =========================================================

    opponentSprite.setTexture(
        opponentIdleTexture
    );

    opponentSprite.setTextureRect(
        sf::IntRect(
            64,
            32,
            16,
            32
        )
    );

    opponentSprite.setOrigin(
        8.0f,
        16.0f
    );

    opponentSprite.setScale(
        -2.0f,
        2.0f
    );


    // =========================================================
    // ANIMATION VALUES
    // =========================================================

    humanWalkFrame =
        0;

    opponentWalkFrame =
        0;


    humanVisualDirection =
        sf::Vector2f(
            1.0f,
            0.0f
        );

    opponentVisualDirection =
        sf::Vector2f(
            -1.0f,
            0.0f
        );


    humanAnimationClock.restart();
    opponentAnimationClock.restart();


    // =========================================================
    // P1 MARKER
    // =========================================================

    playerOneLabel.setFont(
        font
    );

    playerOneLabel.setString(
        "P1"
    );

    playerOneLabel.setCharacterSize(
        14
    );

    playerOneLabel.setFillColor(
        sf::Color::Yellow
    );

    playerOneLabel.setOutlineColor(
        sf::Color::Black
    );

    playerOneLabel.setOutlineThickness(
        2.0f
    );


    // =========================================================
// RESULT UI
// =========================================================

    resultBox.setSize(
        sf::Vector2f(
            500.0f,
            250.0f
        )
    );

    resultBox.setPosition(
        390.0f,
        250.0f
    );

    resultBox.setFillColor(
        sf::Color(
            20,
            20,
            20,
            235
        )
    );

    resultBox.setOutlineColor(
        sf::Color::White
    );

    resultBox.setOutlineThickness(
        4.0f
    );


    resultText.setFont(
        font
    );

    resultText.setCharacterSize(
        42
    );

    resultText.setFillColor(
        sf::Color::White
    );


    resultButton.setSize(
        sf::Vector2f(
            220.0f,
            60.0f
        )
    );

    resultButton.setPosition(
        530.0f,
        390.0f
    );

    resultButton.setFillColor(
        sf::Color(
            70,
            70,
            70
        )
    );

    resultButton.setOutlineColor(
        sf::Color::White
    );

    resultButton.setOutlineThickness(
        2.0f
    );


    resultButtonText.setFont(
        font
    );

    resultButtonText.setCharacterSize(
        24
    );

    resultButtonText.setFillColor(
        sf::Color::White
    );
    // =========================================================
    // TITLE
    // =========================================================

    title.setFont(
        font
    );

    title.setString(
        "SQUID GAME"
    );

    title.setCharacterSize(
        38
    );

    title.setFillColor(
        sf::Color::White
    );

    title.setPosition(
        520.0f,
        35.0f
    );


    // =========================================================
    // INSTRUCTIONS
    // =========================================================

    instructionText.setFont(
        font
    );

    instructionText.setString(
        "WASD = Move"
    );

    instructionText.setCharacterSize(
        20
    );

    instructionText.setFillColor(
        sf::Color::White
    );

    instructionText.setPosition(
        30.0f,
        700.0f
    );


    // =========================================================
    // FINALIST TEXT
    // =========================================================

    finalistText.setFont(
        font
    );

    finalistText.setCharacterSize(
        20
    );

    finalistText.setFillColor(
        sf::Color::White
    );

    finalistText.setPosition(
        500.0f,
        90.0f
    );

    // =========================================================
// HEALTH / STAMINA VALUES
// =========================================================

    humanHealth = maxHealth;
    opponentHealth = maxHealth;
    healthRegenRate = 2.0f;
    healthRegenDelay = 3.0f;

    humanStamina = maxStamina;
    opponentStamina = maxStamina;
    dashCost = 30.0f;

    staminaRegenRate = 18.0f;
    staminaRegenDelay = 0.6f;

    humanDashing = false;
    dashDuration = 0.18f;
    dashMultiplier = 2.5f;

    // =========================================================
    // HUMAN HEALTH BAR
    // =========================================================

    humanHealthBack.setSize(
        sf::Vector2f(260.0f, 20.0f)
    );

    humanHealthBack.setPosition(
        170.0f,
        80.0f
    );

    humanHealthBack.setFillColor(
        sf::Color(70, 70, 70)
    );


    humanHealthBar.setSize(
        sf::Vector2f(260.0f, 20.0f)
    );

    humanHealthBar.setPosition(
        170.0f,
        80.0f
    );

    humanHealthBar.setFillColor(
        sf::Color::Green
    );


    // =========================================================
    // HUMAN STAMINA BAR
    // =========================================================

    humanStaminaBack.setSize(
        sf::Vector2f(260.0f, 12.0f)
    );

    humanStaminaBack.setPosition(
        170.0f,
        106.0f
    );

    humanStaminaBack.setFillColor(
        sf::Color(70, 70, 70)
    );


    humanStaminaBar.setSize(
        sf::Vector2f(260.0f, 12.0f)
    );

    humanStaminaBar.setPosition(
        170.0f,
        106.0f
    );

    humanStaminaBar.setFillColor(
        sf::Color::Cyan
    );


    // =========================================================
    // OPPONENT HEALTH BAR
    // =========================================================

    opponentHealthBack.setSize(
        sf::Vector2f(260.0f, 20.0f)
    );

    opponentHealthBack.setPosition(
        850.0f,
        80.0f
    );

    opponentHealthBack.setFillColor(
        sf::Color(70, 70, 70)
    );


    opponentHealthBar.setSize(
        sf::Vector2f(260.0f, 20.0f)
    );

    opponentHealthBar.setPosition(
        850.0f,
        80.0f
    );

    opponentHealthBar.setFillColor(
        sf::Color::Green
    );


    // =========================================================
    // OPPONENT STAMINA BAR
    // =========================================================

    opponentStaminaBack.setSize(
        sf::Vector2f(260.0f, 12.0f)
    );

    opponentStaminaBack.setPosition(
        850.0f,
        106.0f
    );

    opponentStaminaBack.setFillColor(
        sf::Color(70, 70, 70)
    );


    opponentStaminaBar.setSize(
        sf::Vector2f(260.0f, 12.0f)
    );

    opponentStaminaBar.setPosition(
        850.0f,
        106.0f
    );

    opponentStaminaBar.setFillColor(
        sf::Color::Cyan
    );


    // =========================================================
    // LABELS
    // =========================================================

    humanHealthText.setFont(font);
    humanHealthText.setCharacterSize(16);
    humanHealthText.setFillColor(sf::Color::White);
    humanHealthText.setPosition(170.0f, 55.0f);
    humanHealthText.setString("PLAYER HEALTH");


    humanStaminaText.setFont(font);
    humanStaminaText.setCharacterSize(14);
    humanStaminaText.setFillColor(sf::Color::White);
    humanStaminaText.setPosition(90.0f, 101.0f);
    humanStaminaText.setString("STAMINA");


    opponentHealthText.setFont(font);
    opponentHealthText.setCharacterSize(16);
    opponentHealthText.setFillColor(sf::Color::White);
    opponentHealthText.setPosition(850.0f, 55.0f);
    opponentHealthText.setString("CPU HEALTH");


    opponentStaminaText.setFont(font);
    opponentStaminaText.setCharacterSize(14);
    opponentStaminaText.setFillColor(sf::Color::White);
    opponentStaminaText.setPosition(770.0f, 101.0f);
    opponentStaminaText.setString("STAMINA");

    humanAimDirection =
        sf::Vector2f(
            1.0f,
            0.0f
        );


    aimIndicator.setRadius(
        5.0f
    );

    aimIndicator.setOrigin(
        5.0f,
        5.0f
    );

    aimIndicator.setFillColor(
        sf::Color::Yellow
    );

    rockSpeed = 550.0f;

    rockDamage = 8.0f;

    rockCooldown = 0.8f;

    meleeDamage = 5.0f;

    meleeRange = 65.0f;

    meleeKnockback = 35.0f;

    meleeStaminaCost = 10.0f;

    meleeCooldown = 0.55f;

    opponentMeleeCooldown = 0.7f;

    opponentDodging =
        false;

    opponentDodgeDirection =
        sf::Vector2f(
            0.0f,
            0.0f
        );

    opponentDodgeDuration =
        0.35f;

    opponentDashing =
        false;

    opponentDashDuration =
        0.18f;

    opponentDashMultiplier =
        2.5f;

    opponentDashCooldown =
        1.25f;

}





// =============================================================
// SET PARTICIPANTS
// =============================================================

void SquidGame::setParticipants(
    const std::vector<Participant*>& survivors
)
{
    finalists = survivors;


    findHumanAndOpponent();


    if (humanPlayer != nullptr)
    {
        humanPlayer->resetForNextGame();

        humanPlayer->setPosition(
            300.0f,
            380.0f
        );
    }


    if (opponent != nullptr)
    {
        opponent->resetForNextGame();

        opponent->setPosition(
            950.0f,
            380.0f
        );
    }

    // =========================================================
// RESET VISUAL POSITIONS
// =========================================================

    if (
        humanPlayer != nullptr
        )
    {
        previousHumanVisualPosition =
            humanPlayer->getPosition();
    }


    if (
        opponent != nullptr
        )
    {
        previousOpponentVisualPosition =
            opponent->getPosition();
    }


    humanWalkFrame =
        0;

    opponentWalkFrame =
        0;


    humanVisualDirection =
        sf::Vector2f(
            1.0f,
            0.0f
        );

    opponentVisualDirection =
        sf::Vector2f(
            -1.0f,
            0.0f
        );


    humanAnimationClock.restart();
    opponentAnimationClock.restart();

}


// =============================================================
// FIND HUMAN / OPPONENT
// =============================================================

void SquidGame::findHumanAndOpponent()
{
    humanPlayer = nullptr;
    opponent = nullptr;


    for (
        Participant* participant :
        finalists
        )
    {
        if (participant == nullptr)
            continue;


        if (!participant->isCPU())
        {
            humanPlayer =
                participant;
        }

        else if (opponent == nullptr)
        {
            opponent =
                participant;
        }
    }


    // ---------------------------------------------------------
    // SAFETY:
    // If both finalists are CPUs, just assign them normally.
    // ---------------------------------------------------------

    if (
        humanPlayer == nullptr &&
        finalists.size() >= 2
        )
    {
        humanPlayer =
            finalists[0];

        opponent =
            finalists[1];
    }
}


// =============================================================
// START GAME
// =============================================================

void SquidGame::startGame()
{
    gameStarted = true;
    gameFinished = false;

    movementClock.restart();
}


// =============================================================
// RESET
// =============================================================

void SquidGame::reset()
{
    finalists.clear();

    humanPlayer = nullptr;
    opponent = nullptr;

    gameStarted = false;
    gameFinished = false;


    // =========================================================
    // RESET HEALTH
    // =========================================================

    humanHealth =
        maxHealth;

    opponentHealth =
        maxHealth;


    // =========================================================
    // RESET STAMINA
    // =========================================================

    humanStamina =
        maxStamina;

    opponentStamina =
        maxStamina;


    // =========================================================
    // RESET COMBAT STATE
    // =========================================================

    humanDashing =
        false;

    rocks.clear();


    // =========================================================
    // RESET AI
    // =========================================================
    opponentDashing =
        false;

    opponentDashClock.restart();
    opponentDashCooldownClock.restart();
    opponentState =
        OpponentState::Approach;
    opponentStaminaRegenClock.restart();

    // =========================================================
    // RESET CLOCKS
    // =========================================================

    movementClock.restart();

    humanHealthRegenClock.restart();
    opponentHealthRegenClock.restart();

    humanStaminaRegenClock.restart();

    opponentDecisionClock.restart();

    humanRockClock.restart();
    opponentRockClock.restart();
    humanMeleeClock.restart();
    dashClock.restart();


    updateBars();
    
    opponentDodging =
        false;

    opponentDodgeDirection =
        sf::Vector2f(
            0.0f,
            0.0f
        );

    opponentDodgeClock.restart();
    fightResult =
        FightResult::None;
    resultButtonClicked =
        false;


    // =========================================================
// RESET SPRITE ANIMATION
// =========================================================

    humanWalkFrame =
        0;

    opponentWalkFrame =
        0;


    humanVisualDirection =
        sf::Vector2f(
            1.0f,
            0.0f
        );

    opponentVisualDirection =
        sf::Vector2f(
            -1.0f,
            0.0f
        );


    humanSprite.setTexture(
        humanIdleTexture
    );

    humanSprite.setTextureRect(
        sf::IntRect(
            64,
            32,
            16,
            32
        )
    );


    opponentSprite.setTexture(
        opponentIdleTexture
    );

    opponentSprite.setTextureRect(
        sf::IntRect(
            64,
            32,
            16,
            32
        )
    );


    humanAnimationClock.restart();
    opponentAnimationClock.restart();


}


// =============================================================
// UPDATE
// =============================================================

void SquidGame::update()
{
    if (!gameStarted)
        return;

    if (gameFinished)
        return;


    float deltaTime =
        movementClock.restart()
        .asSeconds();


    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }


    updateHumanMovement(
        deltaTime
    );

    updateOpponentState();

    updateOpponentMovement(
        deltaTime
    );

    tryOpponentMelee();

    tryOpponentRock();

    updateStamina(
        deltaTime
    );

    updateRocks(
        deltaTime
    );

    updateHealthRegen(
        deltaTime
    );

    updateBars();

    checkFightResult();
}


// =============================================================
// HUMAN MOVEMENT
// =============================================================

void SquidGame::updateHumanMovement(
    float deltaTime
)

{
    updateBars();
    if (humanPlayer == nullptr)
        return;


    // ---------------------------------------------------------
    // If the "human" finalist is actually a CPU,
    // don't allow keyboard control.
    // ---------------------------------------------------------

    if (humanPlayer->isCPU())
        return;

    float currentSpeed =
        playerSpeed;


    if (humanDashing)
    {
        if (
            dashClock
            .getElapsedTime()
            .asSeconds() <
            dashDuration
            )
        {
            currentSpeed *=
                dashMultiplier;
        }

        else
        {
            humanDashing =
                false;
        }
    }


    sf::Vector2f movement(
        0.0f,
        0.0f
    );


    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::W
        )
        )
    {
        movement.y -=
            currentSpeed *
            deltaTime;

    }


    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::S
        )
        )
    {
        movement.y +=
            currentSpeed *
            deltaTime;

        
    }


    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::A
        )
        )
    {
        movement.x -=
            currentSpeed *
            deltaTime;

    }


    if (
        sf::Keyboard::isKeyPressed(
            sf::Keyboard::D
        )
        )
    {
        movement.x +=
            currentSpeed *
            deltaTime;
            
    }


    sf::Vector2f currentPosition =
        humanPlayer->getPosition();


    float newX =
        currentPosition.x +
        movement.x;

    float newY =
        currentPosition.y +
        movement.y;


    // =========================================================
    // BOUNDARY COLLISION
    //
    // Leave a small margin because the Participant has size.
    // =========================================================

    const float margin =
        20.0f;



    // =========================================================
    // LEFT BOUNDARY
    // =========================================================
    if (
        newX <
        arenaLeft - margin
        )
    {
        newX =
            arenaLeft - margin;
    }

    // =========================================================
    // RIGHT BOUNDARY
    // =========================================================

    if (
        newX >
        arenaRight - margin
        )
    {
        newX =
            arenaRight - margin;
    }


    // =========================================================
    // TOP BOUNDARY
    // =========================================================

    if (
        newY <
        arenaTop - margin
        )
    {
        newY =
            arenaTop - margin;
    }


    // =========================================================
    // BOTTOM BOUNDARY
    // =========================================================

    if (
        newY >
        arenaBottom - margin
        )
    {
        newY =
            arenaBottom - margin;
    }


    // =========================================================
// PLAYER VS OPPONENT COLLISION
// =========================================================

    bool blockedByOpponent =
        false;


    if (
        opponent != nullptr
        )
    {
        sf::Vector2f opponentPosition =
            opponent->getPosition();


        const float playerSize =
            40.0f;


        bool overlapX =
            newX <
            opponentPosition.x +
            playerSize
            &&
            newX +
            playerSize >
            opponentPosition.x;


        bool overlapY =
            newY <
            opponentPosition.y +
            playerSize
            &&
            newY +
            playerSize >
            opponentPosition.y;


        if (
            overlapX &&
            overlapY
            )
        {
            blockedByOpponent =
                true;
        }
    }


    // =========================================================
    // APPLY MOVEMENT ONLY IF NOT BLOCKED
    // =========================================================

    if (!blockedByOpponent)
    {
        humanPlayer->setPosition(
            newX,
            newY
        );
    }
}


void SquidGame::tryHumanDash()
{
    if (humanPlayer == nullptr)
        return;


    if (humanStamina < dashCost)
        return;


    // ---------------------------------------------------------
    // DON'T WASTE A DASH IF PLAYER ISN'T MOVING
    // ---------------------------------------------------------

    bool moving =
        sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D);


    if (!moving)
        return;


    humanStamina -=
        dashCost;


    if (humanStamina < 0.0f)
    {
        humanStamina =
            0.0f;
    }


    humanDashing =
        true;


    dashClock.restart();

    humanStaminaRegenClock.restart();
}


void SquidGame::updateBars()
{
    float humanHealthPercent =
        humanHealth / maxHealth;

    float opponentHealthPercent =
        opponentHealth / maxHealth;

    float humanStaminaPercent =
        humanStamina / maxStamina;

    float opponentStaminaPercent =
        opponentStamina / maxStamina;


    humanHealthBar.setSize(
        sf::Vector2f(
            260.0f * humanHealthPercent,
            20.0f
        )
    );

    opponentHealthBar.setSize(
        sf::Vector2f(
            260.0f * opponentHealthPercent,
            20.0f
        )
    );

    humanStaminaBar.setSize(
        sf::Vector2f(
            260.0f * humanStaminaPercent,
            12.0f
        )
    );

    opponentStaminaBar.setSize(
        sf::Vector2f(
            260.0f * opponentStaminaPercent,
            12.0f
        )
    );
}

void SquidGame::updateStamina(
    float deltaTime
)
{
    if (
        humanStaminaRegenClock
        .getElapsedTime()
        .asSeconds() >= staminaRegenDelay
        )
    {
        humanStamina +=
            staminaRegenRate *
            deltaTime;


        if (humanStamina > maxStamina)
        {
            humanStamina =
                maxStamina;
        }
    }

    if (
        opponentStaminaRegenClock
        .getElapsedTime()
        .asSeconds() >=
        staminaRegenDelay
        )
    {
        opponentStamina +=
            staminaRegenRate *
            deltaTime;


        if (
            opponentStamina >
            maxStamina
            )
        {
            opponentStamina =
                maxStamina;
        }
    }
}


// =============================================================
// HANDLE INPUT
// =============================================================

GameState SquidGame::handleInput(
    sf::Event& event
)
{
    if (gameFinished)
    {
        if (
            event.type ==
            sf::Event::MouseButtonPressed &&
            event.mouseButton.button ==
            sf::Mouse::Left
            )
        {
            sf::Vector2f mousePosition(
                static_cast<float>(
                    event.mouseButton.x
                    ),

                static_cast<float>(
                    event.mouseButton.y
                    )
            );


            if (
                resultButton
                .getGlobalBounds()
                .contains(
                    mousePosition
                )
                )
            {
                resultButtonClicked =
                    true;
            }
        }


        return GameState::SquidGame;
    }


    if (
        event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::E
        )
    {
        tryHumanMelee();
    }

    if (
        event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left
        )
    {
        throwHumanRock();
    }

    // Nothing special yet.
    //
    // Movement currently uses real-time keyboard input
    // inside update().
    if (
        event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Right
        )
    {
        tryHumanDash();
    }

    return GameState::SquidGame;
}




// =============================================================
// DRAW
// =============================================================

void SquidGame::draw(
    sf::RenderWindow& window
)
{

    // =========================================================
// BACKGROUND
// =========================================================

    window.draw(
        backgroundSprite
    );
    

    updateHumanAim(
        window
    );

    window.draw(
        arena
    );

    

    window.draw(
        title
    );


    window.draw(
        instructionText
    );


    // =========================================================
    // FINALIST NAMES
    // =========================================================

    if (
        humanPlayer != nullptr &&
        opponent != nullptr
        )
    {
        finalistText.setString(
            humanPlayer->getName() +
            "  VS  " +
            opponent->getName()
        );

        window.draw(
            finalistText
        );
    }


    window.draw(humanHealthText);
    window.draw(humanHealthBack);
    window.draw(humanHealthBar);

    window.draw(humanStaminaText);
    window.draw(humanStaminaBack);
    window.draw(humanStaminaBar);


    window.draw(opponentHealthText);
    window.draw(opponentHealthBack);
    window.draw(opponentHealthBar);

    window.draw(opponentStaminaText);
    window.draw(opponentStaminaBack);
    window.draw(opponentStaminaBar);

    for (Rock& rock : rocks)
    {
        if (rock.active)
        {
            window.draw(
                rock.shape
            );
        }
    }

    // =========================================================
   // HUMAN SPRITE
   // =========================================================

    if (
        humanPlayer != nullptr &&
        humanPlayer->isAlive()
        )
    {
        sf::Vector2f humanPosition =
            humanPlayer->getPosition();


        sf::Vector2f humanMovement(
            humanPosition.x -
            previousHumanVisualPosition.x,

            humanPosition.y -
            previousHumanVisualPosition.y
        );


        float humanMovementLength =
            std::sqrt(
                humanMovement.x *
                humanMovement.x +

                humanMovement.y *
                humanMovement.y
            );


        bool humanMoving =
            humanMovementLength >
            0.05f;


        if (
            humanMoving
            )
        {
            humanVisualDirection.x =
                humanMovement.x /
                humanMovementLength;

            humanVisualDirection.y =
                humanMovement.y /
                humanMovementLength;


            if (
                humanAnimationClock
                .getElapsedTime()
                .asSeconds() >=
                0.08f
                )
            {
                humanAnimationClock.restart();

                humanWalkFrame++;

                if (
                    humanWalkFrame >=
                    5
                    )
                {
                    humanWalkFrame =
                        0;
                }
            }


            humanSprite.setTexture(
                humanWalkTextures[
                    humanWalkFrame
                ]
            );


            humanSprite.setTextureRect(
                sf::IntRect(
                    64,
                    96,
                    16,
                    32
                )
            );
        }

        else
        {
            humanSprite.setTexture(
                humanIdleTexture
            );


            humanSprite.setTextureRect(
                sf::IntRect(
                    64,
                    32,
                    16,
                    32
                )
            );


            humanWalkFrame =
                0;
        }


        // -----------------------------------------------------
        // FACE LEFT / RIGHT
        // -----------------------------------------------------

        if (
            humanVisualDirection.x <
            -0.05f
            )
        {
            humanSprite.setScale(
                -2.0f,
                2.0f
            );
        }

        else if (
            humanVisualDirection.x >
            0.05f
            )
        {
            humanSprite.setScale(
                2.0f,
                2.0f
            );
        }


        // -----------------------------------------------------
        // CENTRE SPRITE OVER ORIGINAL 40x40 PARTICIPANT
        // -----------------------------------------------------

        humanSprite.setPosition(
            humanPosition.x +
            20.0f,

            humanPosition.y +
            20.0f
        );


        // =====================================================
        // HUMAN DASH SLASH
        // =====================================================

        if (
            humanDashing
            )
        {
            drawDashSlash(
                window,
                humanSprite.getPosition(),
                humanVisualDirection
            );
        }


        window.draw(
            humanSprite
        );


        // =====================================================
        // P1 MARKER
        // =====================================================

        sf::FloatRect humanBounds =
            humanSprite.getGlobalBounds();


        playerOneLabel.setPosition(
            humanBounds.left +
            humanBounds.width /
            2.0f -
            9.0f,

            humanBounds.top -
            20.0f
        );


        window.draw(
            playerOneLabel
        );


        previousHumanVisualPosition =
            humanPosition;
    }


    // =========================================================
    // AIM INDICATOR
    // =========================================================

    if (
        humanPlayer != nullptr &&
        humanPlayer->isAlive()
        )
    {
        window.draw(
            aimIndicator
        );
    }


    // =========================================================
    // OPPONENT SPRITE
    // =========================================================

    if (
        opponent != nullptr &&
        opponent->isAlive()
        )
    {
        sf::Vector2f opponentPosition =
            opponent->getPosition();


        sf::Vector2f opponentMovement(
            opponentPosition.x -
            previousOpponentVisualPosition.x,

            opponentPosition.y -
            previousOpponentVisualPosition.y
        );


        float opponentMovementLength =
            std::sqrt(
                opponentMovement.x *
                opponentMovement.x +

                opponentMovement.y *
                opponentMovement.y
            );


        bool opponentMoving =
            opponentMovementLength >
            0.05f;


        if (
            opponentMoving
            )
        {
            opponentVisualDirection.x =
                opponentMovement.x /
                opponentMovementLength;

            opponentVisualDirection.y =
                opponentMovement.y /
                opponentMovementLength;


            if (
                opponentAnimationClock
                .getElapsedTime()
                .asSeconds() >=
                0.08f
                )
            {
                opponentAnimationClock.restart();

                opponentWalkFrame++;

                if (
                    opponentWalkFrame >=
                    5
                    )
                {
                    opponentWalkFrame =
                        0;
                }
            }


            opponentSprite.setTexture(
                opponentWalkTextures[
                    opponentWalkFrame
                ]
            );


            opponentSprite.setTextureRect(
                sf::IntRect(
                    64,
                    96,
                    16,
                    32
                )
            );
        }

        else
        {
            opponentSprite.setTexture(
                opponentIdleTexture
            );


            opponentSprite.setTextureRect(
                sf::IntRect(
                    64,
                    32,
                    16,
                    32
                )
            );


            opponentWalkFrame =
                0;
        }


        // -----------------------------------------------------
        // FACE LEFT / RIGHT
        // -----------------------------------------------------

        if (
            opponentVisualDirection.x <
            -0.05f
            )
        {
            opponentSprite.setScale(
                -2.0f,
                2.0f
            );
        }

        else if (
            opponentVisualDirection.x >
            0.05f
            )
        {
            opponentSprite.setScale(
                2.0f,
                2.0f
            );
        }


        opponentSprite.setPosition(
            opponentPosition.x +
            20.0f,

            opponentPosition.y +
            20.0f
        );


        // =====================================================
        // CPU DASH SLASH
        // =====================================================

        if (
            opponentDashing
            )
        {
            drawDashSlash(
                window,
                opponentSprite.getPosition(),
                opponentVisualDirection
            );
        }


        window.draw(
            opponentSprite
        );


        previousOpponentVisualPosition =
            opponentPosition;
    }

    if (gameFinished)
    {
        window.draw(
            resultBox
        );

        window.draw(
            resultText
        );

        window.draw(
            resultButton
        );

        window.draw(
            resultButtonText
        );
    }
}

void SquidGame::updateHumanAim(
    const sf::RenderWindow& window
)
{
    if (humanPlayer == nullptr)
        return;


    sf::Vector2i mousePixelPosition =
        sf::Mouse::getPosition(
            window
        );


    sf::Vector2f mousePosition =
        window.mapPixelToCoords(
            mousePixelPosition
        );


    sf::Vector2f playerPosition =
        humanPlayer->getPosition();


    // Participant cube is approximately 40 x 40.
    sf::Vector2f playerCenter(
        playerPosition.x + 20.0f,
        playerPosition.y + 20.0f
    );


    sf::Vector2f direction(
        mousePosition.x -
        playerCenter.x,

        mousePosition.y -
        playerCenter.y
    );


    float length =
        std::sqrt(
            direction.x * direction.x +
            direction.y * direction.y
        );


    // Prevent division by zero if cursor is exactly
    // on the player's centre.
    if (length > 0.001f)
    {
        humanAimDirection.x =
            direction.x / length;

        humanAimDirection.y =
            direction.y / length;
    }


    // Position marker slightly in front of Player 1.
    const float indicatorDistance =
        32.0f;


    aimIndicator.setPosition(
        playerCenter.x +
        (
            humanAimDirection.x *
            indicatorDistance
            ),

        playerCenter.y +
        (
            humanAimDirection.y *
            indicatorDistance
            )
    );


}
void SquidGame::throwHumanRock()
{
    if (humanPlayer == nullptr)
        return;


    // ---------------------------------------------------------
    // COOLDOWN
    // ---------------------------------------------------------

    if (
        humanRockClock
        .getElapsedTime()
        .asSeconds() <
        rockCooldown
        )
    {
        return;
    }


    humanRockClock.restart();


    // ---------------------------------------------------------
    // CREATE ROCK
    // ---------------------------------------------------------

    Rock rock;


    rock.shape.setRadius(
        6.0f
    );

    rock.shape.setOrigin(
        6.0f,
        6.0f
    );

    rock.shape.setFillColor(
        sf::Color(
            160,
            160,
            160
        )
    );


    // ---------------------------------------------------------
    // START AT PLAYER CENTRE
    // ---------------------------------------------------------

    sf::Vector2f playerPosition =
        humanPlayer->getPosition();


    sf::Vector2f playerCenter(
        playerPosition.x + 20.0f,
        playerPosition.y + 20.0f
    );


    const float spawnDistance =
        32.0f;


    rock.shape.setPosition(
        playerCenter.x +
        humanAimDirection.x *
        spawnDistance,

        playerCenter.y +
        humanAimDirection.y *
        spawnDistance
    );


    // ---------------------------------------------------------
    // VELOCITY = AIM DIRECTION × SPEED
    // ---------------------------------------------------------

    rock.velocity =
        sf::Vector2f(
            humanAimDirection.x *
            rockSpeed,

            humanAimDirection.y *
            rockSpeed
        );


    rock.active = true;
    rock.thrownByHuman =
        true;

    rocks.push_back(
        rock
    );
}

void SquidGame::updateRocks(
    float deltaTime
)
{
    for (Rock& rock : rocks)
    {
        if (!rock.active)
            continue;


        rock.shape.move(
            rock.velocity.x *
            deltaTime,

            rock.velocity.y *
            deltaTime
        );


        sf::Vector2f rockPosition =
            rock.shape.getPosition();


        // =====================================================
        // REMOVE ROCK WHEN IT LEAVES ARENA
        // =====================================================

        if (
            rockPosition.x < arenaLeft ||
            rockPosition.x > arenaRight ||
            rockPosition.y < arenaTop ||
            rockPosition.y > arenaBottom
            )
        {
            rock.active = false;

            continue;
        }


        // =====================================================
// HUMAN ROCK HITS CPU
// =====================================================

        if (
            rock.thrownByHuman &&
            opponent != nullptr
            )
        {
            sf::Vector2f opponentPosition =
                opponent->getPosition();


            sf::FloatRect opponentBounds(
                opponentPosition.x,
                opponentPosition.y,
                40.0f,
                40.0f
            );


            if (
                opponentBounds.intersects(
                    rock.shape.getGlobalBounds()
                )
                )
            {
                opponentHealth -=
                    rockDamage;


                opponentHealthRegenClock.restart();


                if (
                    opponentHealth <
                    0.0f
                    )
                {
                    opponentHealth =
                        0.0f;
                }


                rock.active =
                    false;


                continue;
            }
        }


        // =====================================================
        // CPU ROCK HITS HUMAN
        // =====================================================

        else if (
            !rock.thrownByHuman &&
            humanPlayer != nullptr
            )
        {
            sf::Vector2f humanPosition =
                humanPlayer->getPosition();


            sf::FloatRect humanBounds(
                humanPosition.x,
                humanPosition.y,
                40.0f,
                40.0f
            );


            if (
                humanBounds.intersects(
                    rock.shape.getGlobalBounds()
                )
                )
            {
                humanHealth -=
                    rockDamage;


                humanHealthRegenClock.restart();


                if (
                    humanHealth <
                    0.0f
                    )
                {
                    humanHealth =
                        0.0f;
                }


                rock.active =
                    false;


                continue;
            }
        }
    }


    // ---------------------------------------------------------
    // CLEAN UP DEAD ROCKS
    // ---------------------------------------------------------

    rocks.erase(
        std::remove_if(
            rocks.begin(),
            rocks.end(),

            [](const Rock& rock)
            {
                return !rock.active;
            }
        ),

        rocks.end()
    );
}

void SquidGame::updateHealthRegen(
    float deltaTime
)
{
    // =========================================================
    // HUMAN HEALTH REGEN
    // =========================================================

    if (
        humanHealth < maxHealth &&
        humanHealthRegenClock
        .getElapsedTime()
        .asSeconds() >= healthRegenDelay
        )
    {
        humanHealth +=
            healthRegenRate *
            deltaTime;


        if (humanHealth > maxHealth)
        {
            humanHealth =
                maxHealth;
        }
    }


    // =========================================================
    // OPPONENT HEALTH REGEN
    // =========================================================

    if (
        opponentHealth < maxHealth &&
        opponentHealthRegenClock
        .getElapsedTime()
        .asSeconds() >= healthRegenDelay
        )
    {
        opponentHealth +=
            healthRegenRate *
            deltaTime;


        if (opponentHealth > maxHealth)
        {
            opponentHealth =
                maxHealth;
        }
    }
}
void SquidGame::tryHumanMelee()
{
    if (
        humanPlayer == nullptr ||
        opponent == nullptr
        )
    {
        return;
    }


    if (
        humanMeleeClock
        .getElapsedTime()
        .asSeconds() <
        meleeCooldown
        )
    {
        return;
    }


    if (
        humanStamina <
        meleeStaminaCost
        )
    {
        return;
    }


    sf::Vector2f humanPosition =
        humanPlayer->getPosition();

    sf::Vector2f opponentPosition =
        opponent->getPosition();


    sf::Vector2f humanCenter(
        humanPosition.x + 20.0f,
        humanPosition.y + 20.0f
    );

    sf::Vector2f opponentCenter(
        opponentPosition.x + 20.0f,
        opponentPosition.y + 20.0f
    );


    float deltaX =
        opponentCenter.x -
        humanCenter.x;

    float deltaY =
        opponentCenter.y -
        humanCenter.y;


    float distance =
        std::sqrt(
            deltaX * deltaX +
            deltaY * deltaY
        );


    if (
        distance >
        meleeRange
        )
    {
        return;
    }


    if (
        distance <
        0.001f
        )
    {
        return;
    }


    humanMeleeClock.restart();

    humanStamina -=
        meleeStaminaCost;

    humanStaminaRegenClock.restart();


    opponentHealth -=
        meleeDamage;

    opponentHealthRegenClock.restart();


    if (
        opponentHealth <
        0.0f
        )
    {
        opponentHealth =
            0.0f;
    }


    // =========================================================
    // KNOCKBACK DIRECTION
    // =========================================================

    float directionX =
        deltaX /
        distance;

    float directionY =
        deltaY /
        distance;


    float newOpponentX =
        opponentPosition.x +
        directionX *
        meleeKnockback;

    float newOpponentY =
        opponentPosition.y +
        directionY *
        meleeKnockback;


    // =========================================================
    // KEEP OPPONENT INSIDE ARENA
    // =========================================================

    const float margin =
        20.0f;


    if (
        newOpponentX <
        arenaLeft - margin
        )
    {
        newOpponentX =
            arenaLeft - margin;
    }


    if (
        newOpponentX >
        arenaRight - margin
        )
    {
        newOpponentX =
            arenaRight - margin;
    }


    if (
        newOpponentY <
        arenaTop - margin
        )
    {
        newOpponentY =
            arenaTop - margin;
    }


    if (
        newOpponentY >
        arenaBottom - margin
        )
    {
        newOpponentY =
            arenaBottom - margin;
    }


    opponent->setPosition(
        newOpponentX,
        newOpponentY
    );
}

bool SquidGame::getOpponentDodgeDirection(
    sf::Vector2f& dodgeDirection
)
{
    if (opponent == nullptr)
    {
        return false;
    }


    sf::Vector2f opponentPosition =
        opponent->getPosition();


    sf::Vector2f opponentCenter(
        opponentPosition.x + 20.0f,
        opponentPosition.y + 20.0f
    );


    for (Rock& rock : rocks)
    {
        if (!rock.active)
        {
            continue;
        }


        sf::Vector2f rockPosition =
            rock.shape.getPosition();


        float velocityLength =
            std::sqrt(
                rock.velocity.x * rock.velocity.x +
                rock.velocity.y * rock.velocity.y
            );


        if (
            velocityLength <
            0.001f
            )
        {
            continue;
        }


        // =====================================================
        // ROCK TRAVEL DIRECTION
        // =====================================================

        sf::Vector2f rockDirection(
            rock.velocity.x /
            velocityLength,

            rock.velocity.y /
            velocityLength
        );


        // Vector from rock to CPU.
        sf::Vector2f toOpponent(
            opponentCenter.x -
            rockPosition.x,

            opponentCenter.y -
            rockPosition.y
        );


        // =====================================================
        // IS THE ROCK ACTUALLY IN FRONT OF IT?
        // =====================================================

        float forwardDistance =
            toOpponent.x *
            rockDirection.x +
            toOpponent.y *
            rockDirection.y;


        // Behind the rock or too far away.
        // =====================================================
// TIME UNTIL ROCK REACHES CPU
// =====================================================

        float timeToImpact =
            forwardDistance /
            velocityLength;


        // Ignore rocks travelling away from us.
        if (
            forwardDistance <= 0.0f
            )
        {
            continue;
        }


        // CPU reacts to dangerous rocks up to about
        // 1.25 seconds before impact.
        if (
            timeToImpact >
            1.25f
            )
        {
            continue;
        }


        // =====================================================
        // DISTANCE FROM ROCK'S FLIGHT LINE
        // =====================================================

        float sidewaysDistance =
            std::abs(
                toOpponent.x *
                rockDirection.y -
                toOpponent.y *
                rockDirection.x
            );


        // Rock isn't going close enough to hit us.
        if (
            sidewaysDistance >
            45.0f
            )
        {
            continue;
        }


        // =====================================================
        // TWO POSSIBLE SIDESTEP DIRECTIONS
        // =====================================================

        sf::Vector2f optionOne(
            -rockDirection.y,
            rockDirection.x
        );


        sf::Vector2f optionTwo(
            rockDirection.y,
            -rockDirection.x
        );


        const float testDistance =
            80.0f;


        sf::Vector2f testOne(
            opponentPosition.x +
            optionOne.x *
            testDistance,

            opponentPosition.y +
            optionOne.y *
            testDistance
        );


        sf::Vector2f testTwo(
            opponentPosition.x +
            optionTwo.x *
            testDistance,

            opponentPosition.y +
            optionTwo.y *
            testDistance
        );


        const float margin =
            20.0f;


        bool optionOneSafe =
            testOne.x >= arenaLeft - margin &&
            testOne.x <= arenaRight - margin &&
            testOne.y >= arenaTop - margin &&
            testOne.y <= arenaBottom - margin;


        bool optionTwoSafe =
            testTwo.x >= arenaLeft - margin &&
            testTwo.x <= arenaRight - margin &&
            testTwo.y >= arenaTop - margin &&
            testTwo.y <= arenaBottom - margin;


        // =====================================================
        // CHOOSE A SIDE
        // =====================================================

        if (
            optionOneSafe &&
            !optionTwoSafe
            )
        {
            dodgeDirection =
                optionOne;
        }


        else if (
            optionTwoSafe &&
            !optionOneSafe
            )
        {
            dodgeDirection =
                optionTwo;
        }


        else
        {
            // Both are available.
            // Pick whichever points more toward arena centre.

            sf::Vector2f arenaCenter(
                (
                    arenaLeft +
                    arenaRight
                    ) / 2.0f,

                (
                    arenaTop +
                    arenaBottom
                    ) / 2.0f
            );


            sf::Vector2f towardCenter(
                arenaCenter.x -
                opponentCenter.x,

                arenaCenter.y -
                opponentCenter.y
            );


            float optionOneScore =
                optionOne.x *
                towardCenter.x +
                optionOne.y *
                towardCenter.y;


            float optionTwoScore =
                optionTwo.x *
                towardCenter.x +
                optionTwo.y *
                towardCenter.y;


            if (
                optionOneScore >
                optionTwoScore
                )
            {
                dodgeDirection =
                    optionOne;
            }

            else
            {
                dodgeDirection =
                    optionTwo;
            }
        }


        return true;
    }


    return false;
}


void SquidGame::updateOpponentMovement(
    float deltaTime
)
{
    if (
        opponent == nullptr ||
        humanPlayer == nullptr
        )
    {
        return;
    }


    if (!opponent->isCPU())
    {
        return;
    }


    sf::Vector2f opponentPosition =
        opponent->getPosition();

    sf::Vector2f humanPosition =
        humanPlayer->getPosition();


    sf::Vector2f opponentCenter(
        opponentPosition.x + 20.0f,
        opponentPosition.y + 20.0f
    );

    sf::Vector2f humanCenter(
        humanPosition.x + 20.0f,
        humanPosition.y + 20.0f
    );


    float deltaX =
        humanCenter.x -
        opponentCenter.x;

    float deltaY =
        humanCenter.y -
        opponentCenter.y;


    float distance =
        std::sqrt(
            deltaX * deltaX +
            deltaY * deltaY
        );


    if (
        distance <
        0.001f
        )
    {
        return;

    }

    tryOpponentDash(
        distance
    );


    // =========================================================
// WALL AWARENESS
// =========================================================

const float wallDangerDistance =
    55.0f;


bool nearLeftWall =
    opponentPosition.x <
    arenaLeft +
    wallDangerDistance;

bool nearRightWall =
    opponentPosition.x >
    arenaRight -
    wallDangerDistance;

bool nearTopWall =
    opponentPosition.y <
    arenaTop +
    wallDangerDistance;

bool nearBottomWall =
    opponentPosition.y >
    arenaBottom -
    wallDangerDistance;


bool nearHorizontalWall =
    nearLeftWall ||
    nearRightWall;

bool nearVerticalWall =
    nearTopWall ||
    nearBottomWall;


bool nearAnyWall =
    nearHorizontalWall ||
    nearVerticalWall;

    // =========================================================
// INCOMING ROCK EVASION
// =========================================================

   // =========================================================
// PERSISTENT ROCK EVASION
// =========================================================

    sf::Vector2f detectedDodgeDirection(
        0.0f,
        0.0f
    );


    bool rockThreatDetected =
        getOpponentDodgeDirection(
            detectedDodgeDirection
        );


    // ---------------------------------------------------------
    // NEW THREAT
    // ---------------------------------------------------------

    if (
        rockThreatDetected &&
        !opponentDodging
        )
    {
        opponentDodging =
            true;

        opponentDodgeDirection =
            detectedDodgeDirection;

        opponentDodgeClock.restart();
    }


    // ---------------------------------------------------------
    // CURRENT DODGE FINISHED
    // ---------------------------------------------------------

    if (
        opponentDodging &&
        opponentDodgeClock
        .getElapsedTime()
        .asSeconds() >=
        opponentDodgeDuration
        )
    {
        opponentDodging =
            false;
    }


    // ---------------------------------------------------------
    // ACTIVE DODGE
    // ---------------------------------------------------------

    bool dodgingRock =
        opponentDodging;

    // =========================================================
    // STATE MOVEMENT SETTINGS
    // =========================================================

    float desiredDistance =
        opponentStopDistance;

    bool moveAway =
        false;


    if (
        opponentState ==
        OpponentState::Pressure
        )
    {
        desiredDistance =
            50.0f;
    }


    else if (
        opponentState ==
        OpponentState::Evade
        )
    {
        desiredDistance =
            240.0f;

        moveAway =
            true;
    }


    else if (
        opponentState ==
        OpponentState::Recover
        )
    {
        desiredDistance =
            320.0f;

        moveAway =
            true;
    }


    // =========================================================
    // ALREADY AT DESIRED DISTANCE
    // =========================================================

   // =========================================================
// DESIRED DISTANCE CHECK
// =========================================================

    if (!dodgingRock)
    {
        // ---------------------------------------------------------
        // APPROACH / PRESSURE
        // ---------------------------------------------------------

        if (!moveAway)
        {
            if (
                distance <=
                desiredDistance
                )
            {
                return;
            }
        }


        // ---------------------------------------------------------
        // EVADE / RECOVER
        // ---------------------------------------------------------

        else
        {
            // Being far enough from the player is NOT enough
            // reason to stop if we're parked against a wall.
            if (
                distance >=
                desiredDistance &&
                !nearAnyWall
                )
            {
                return;
            }
        }
    }


    // =========================================================
    // NORMALIZE DIRECTION
    // =========================================================

    float directionX =
        0.0f;

    float directionY =
        0.0f;


    // =========================================================
    // ROCK DODGE TAKES PRIORITY
    // =========================================================

    if (dodgingRock)
    {
        directionX =
            opponentDodgeDirection.x;

        directionY =
            opponentDodgeDirection.y;


        // ---------------------------------------------------------
        // ALSO LEAN SLIGHTLY AWAY FROM PLAYER
        // ---------------------------------------------------------

        float awayX =
            -deltaX /
            distance;

        float awayY =
            -deltaY /
            distance;


        directionX +=
            awayX * 0.35f;

        directionY +=
            awayY * 0.35f;


        // Normalize combined dodge direction.
        float dodgeLength =
            std::sqrt(
                directionX * directionX +
                directionY * directionY
            );


        if (
            dodgeLength >
            0.001f
            )
        {
            directionX /=
                dodgeLength;

            directionY /=
                dodgeLength;
        }
    }


    // =========================================================
    // NORMAL AI MOVEMENT
    // =========================================================

    else
    {
        directionX =
            deltaX /
            distance;

        directionY =
            deltaY /
            distance;


        if (moveAway)
        {
            directionX *=
                -1.0f;

            directionY *=
                -1.0f;
        }
    }

    

    // =========================================================
// DON'T DODGE INTO A WALL
// =========================================================

    if (dodgingRock)
    {
        // ---------------------------------------------------------
        // REMOVE ONLY THE COMPONENT THAT POINTS INTO THE WALL
        // ---------------------------------------------------------

        if (
            nearLeftWall &&
            directionX < 0.0f
            )
        {
            directionX =
                0.0f;
        }


        if (
            nearRightWall &&
            directionX > 0.0f
            )
        {
            directionX =
                0.0f;
        }


        if (
            nearTopWall &&
            directionY < 0.0f
            )
        {
            directionY =
                0.0f;
        }


        if (
            nearBottomWall &&
            directionY > 0.0f
            )
        {
            directionY =
                0.0f;
        }


        // ---------------------------------------------------------
        // NORMALIZE THE REMAINING DODGE
        // ---------------------------------------------------------

        float adjustedLength =
            std::sqrt(
                directionX * directionX +
                directionY * directionY
            );


        if (
            adjustedLength >
            0.001f
            )
        {
            directionX /=
                adjustedLength;

            directionY /=
                adjustedLength;
        }


        // ---------------------------------------------------------
        // EXTREME CASE:
        // WALLS BLOCKED THE ENTIRE DODGE
        // ---------------------------------------------------------

        else
        {
            sf::Vector2f arenaCenter(
                (
                    arenaLeft +
                    arenaRight
                    ) / 2.0f,

                (
                    arenaTop +
                    arenaBottom
                    ) / 2.0f
            );


            float centerX =
                arenaCenter.x -
                opponentCenter.x;

            float centerY =
                arenaCenter.y -
                opponentCenter.y;


            float centerDistance =
                std::sqrt(
                    centerX * centerX +
                    centerY * centerY
                );


            if (
                centerDistance >
                0.001f
                )
            {
                directionX =
                    centerX /
                    centerDistance;

                directionY =
                    centerY /
                    centerDistance;
            }
        }
    }

    if (
        moveAway &&
        !dodgingRock &&
        (
            nearHorizontalWall ||
            nearVerticalWall
            )
        )
    {
        sf::Vector2f arenaCenter(
            (
                arenaLeft +
                arenaRight
                ) / 2.0f,

            (
                arenaTop +
                arenaBottom
                ) / 2.0f
        );


        float centerX =
            arenaCenter.x -
            opponentCenter.x;

        float centerY =
            arenaCenter.y -
            opponentCenter.y;


        float centerDistance =
            std::sqrt(
                centerX * centerX +
                centerY * centerY
            );


        if (
            centerDistance >
            0.001f
            )
        {
            directionX =
                centerX /
                centerDistance;

            directionY =
                centerY /
                centerDistance;
        }
    }



    float currentOpponentSpeed =
        opponentSpeed;


    // =========================================================
    // ROCK EVASION SPEED
    // =========================================================

    if (dodgingRock)
    {
        currentOpponentSpeed *=
            1.65f;
    }


    // =========================================================
    // CPU DASH
    // =========================================================

    if (opponentDashing)
    {
        if (
            opponentDashClock
            .getElapsedTime()
            .asSeconds() <
            opponentDashDuration
            )
        {
            currentOpponentSpeed *=
                opponentDashMultiplier;
        }

        else
        {
            opponentDashing =
                false;
        }
    }

    float newX =
        opponentPosition.x +
        directionX *
        currentOpponentSpeed *
        deltaTime;

    float newY =
        opponentPosition.y +
        directionY *
        currentOpponentSpeed *
        deltaTime;


    // =========================================================
    // ARENA BOUNDARIES
    // =========================================================

    const float margin =
        20.0f;


    if (
        newX <
        arenaLeft - margin
        )
    {
        newX =
            arenaLeft - margin;
    }


    if (
        newX >
        arenaRight - margin
        )
    {
        newX =
            arenaRight - margin;
    }


    if (
        newY <
        arenaTop - margin
        )
    {
        newY =
            arenaTop - margin;
    }


    if (
        newY >
        arenaBottom - margin
        )
    {
        newY =
            arenaBottom - margin;
    }


    // =========================================================
    // PLAYER COLLISION
    // =========================================================

    const float playerSize =
        40.0f;


    bool overlapX =
        newX <
        humanPosition.x + playerSize &&
        newX + playerSize >
        humanPosition.x;


    bool overlapY =
        newY <
        humanPosition.y + playerSize &&
        newY + playerSize >
        humanPosition.y;


    if (
        overlapX &&
        overlapY
        )
    {
        return;
    }


    opponent->setPosition(
        newX,
        newY
    );
}

void SquidGame::updateOpponentState()
{
    if (
        opponent == nullptr ||
        humanPlayer == nullptr
        )
    {
        return;
    }


    // ---------------------------------------------------------
    // DON'T MAKE A NEW DECISION EVERY FRAME
    // ---------------------------------------------------------

    if (
        opponentDecisionClock
        .getElapsedTime()
        .asSeconds() <
        opponentDecisionInterval
        )
    {
        return;
    }


    opponentDecisionClock.restart();


    // =========================================================
    // DECIDE STATE
    // =========================================================

    if (
        opponentHealth <= 35.0f
        )
    {
        opponentState =
            OpponentState::Recover;
    }


    else if (
        humanHealth >
        opponentHealth + 15.0f
        )
    {
        opponentState =
            OpponentState::Evade;
    }


    else if (
        opponentHealth >
        humanHealth + 15.0f
        )
    {
        opponentState =
            OpponentState::Pressure;
    }


    else
    {
        opponentState =
            OpponentState::Approach;
    }


   
}

void SquidGame::tryOpponentMelee()
{
    if (
        opponent == nullptr ||
        humanPlayer == nullptr
        )
    {
        return;
    }


    if (
        opponentStamina <
        meleeStaminaCost
        )
    {
        return;
    }


    if (
        opponentMeleeClock
        .getElapsedTime()
        .asSeconds() <
        opponentMeleeCooldown
        )
    {
        return;
    }


    sf::Vector2f opponentPosition =
        opponent->getPosition();

    sf::Vector2f humanPosition =
        humanPlayer->getPosition();


    sf::Vector2f opponentCenter(
        opponentPosition.x + 20.0f,
        opponentPosition.y + 20.0f
    );

    sf::Vector2f humanCenter(
        humanPosition.x + 20.0f,
        humanPosition.y + 20.0f
    );


    float deltaX =
        humanCenter.x -
        opponentCenter.x;

    float deltaY =
        humanCenter.y -
        opponentCenter.y;


    float distance =
        std::sqrt(
            deltaX * deltaX +
            deltaY * deltaY
        );


    if (
        distance >
        meleeRange
        )
    {
        return;
    }


    if (
        distance <
        0.001f
        )
    {
        return;
    }


    opponentMeleeClock.restart();


    opponentStamina -=
        meleeStaminaCost;
    opponentStaminaRegenClock.restart();


    if (
        opponentStamina <
        0.0f
        )
    {
        opponentStamina =
            0.0f;
    }


    humanHealth -=
        meleeDamage;


    if (
        humanHealth <
        0.0f
        )
    {
        humanHealth =
            0.0f;
    }


    humanHealthRegenClock.restart();


    // =========================================================
    // KNOCK PLAYER AWAY
    // =========================================================

    float directionX =
        deltaX /
        distance;

    float directionY =
        deltaY /
        distance;


    float newHumanX =
        humanPosition.x +
        directionX *
        meleeKnockback;

    float newHumanY =
        humanPosition.y +
        directionY *
        meleeKnockback;


    const float margin =
        20.0f;


    if (
        newHumanX <
        arenaLeft - margin
        )
    {
        newHumanX =
            arenaLeft - margin;
    }


    if (
        newHumanX >
        arenaRight - margin
        )
    {
        newHumanX =
            arenaRight - margin;
    }


    if (
        newHumanY <
        arenaTop - margin
        )
    {
        newHumanY =
            arenaTop - margin;
    }


    if (
        newHumanY >
        arenaBottom - margin
        )
    {
        newHumanY =
            arenaBottom - margin;
    }


    humanPlayer->setPosition(
        newHumanX,
        newHumanY
    );
}

void SquidGame::tryOpponentRock()
{
    if (
        opponent == nullptr ||
        humanPlayer == nullptr
        )
    {
        return;
    }


    if (!opponent->isCPU())
    {
        return;
    }


    if (
        humanHealth <= 0.0f ||
        opponentHealth <= 0.0f
        )
    {
        return;
    }


    // =========================================================
    // FIRE RATE DEPENDS ON AI STATE
    // =========================================================

    float currentCooldown =
        1.15f;


    if (
        opponentState ==
        OpponentState::Pressure
        )
    {
        currentCooldown =
            0.85f;
    }


    else if (
        opponentState ==
        OpponentState::Evade
        )
    {
        currentCooldown =
            1.25f;
    }


    else if (
        opponentState ==
        OpponentState::Recover
        )
    {
        currentCooldown =
            1.55f;
    }


    if (
        opponentRockClock
        .getElapsedTime()
        .asSeconds() <
        currentCooldown
        )
    {
        return;
    }


    // =========================================================
    // FIND PLAYER
    // =========================================================

    sf::Vector2f opponentPosition =
        opponent->getPosition();

    sf::Vector2f humanPosition =
        humanPlayer->getPosition();


    sf::Vector2f opponentCenter(
        opponentPosition.x + 20.0f,
        opponentPosition.y + 20.0f
    );


    sf::Vector2f humanCenter(
        humanPosition.x + 20.0f,
        humanPosition.y + 20.0f
    );


    // =========================================================
    // SMALL AIM INACCURACY
    // =========================================================

    float aimOffsetX =
        static_cast<float>(
            (std::rand() % 41) - 20
            );

    float aimOffsetY =
        static_cast<float>(
            (std::rand() % 41) - 20
            );


    sf::Vector2f targetPosition(
        humanCenter.x +
        aimOffsetX,

        humanCenter.y +
        aimOffsetY
    );


    float deltaX =
        targetPosition.x -
        opponentCenter.x;

    float deltaY =
        targetPosition.y -
        opponentCenter.y;


    float distance =
        std::sqrt(
            deltaX * deltaX +
            deltaY * deltaY
        );


    if (
        distance <
        0.001f
        )
    {
        return;
    }


    float directionX =
        deltaX /
        distance;

    float directionY =
        deltaY /
        distance;


    // =========================================================
    // CREATE ROCK
    // =========================================================

    Rock rock;


    rock.shape.setRadius(
        6.0f
    );


    rock.shape.setOrigin(
        6.0f,
        6.0f
    );


    // Different color so we can immediately
    // tell CPU rocks apart while testing.
    rock.shape.setFillColor(
        sf::Color(
            220,
            120,
            120
        )
    );


    const float spawnDistance =
        32.0f;


    rock.shape.setPosition(
        opponentCenter.x +
        directionX *
        spawnDistance,

        opponentCenter.y +
        directionY *
        spawnDistance
    );


    rock.velocity =
        sf::Vector2f(
            directionX *
            rockSpeed,

            directionY *
            rockSpeed
        );


    rock.active =
        true;


    rock.thrownByHuman =
        false;


    rocks.push_back(
        rock
    );


    opponentRockClock.restart();
}

void SquidGame::tryOpponentDash(
    float distance
)
{
    if (
        opponent == nullptr ||
        humanPlayer == nullptr
        )
    {
        return;
    }


    if (opponentDashing)
    {
        return;
    }


    if (
        opponentStamina <
        dashCost
        )
    {
        return;
    }


    if (
        opponentDashCooldownClock
        .getElapsedTime()
        .asSeconds() <
        opponentDashCooldown
        )
    {
        return;
    }


    bool shouldDash =
        false;


    // =========================================================
    // PRESSURE:
    // DASH IN TO CLOSE DISTANCE
    // =========================================================

    if (
        opponentState ==
        OpponentState::Pressure
        )
    {
        if (
            distance > 110.0f &&
            distance < 320.0f
            )
        {
            shouldDash =
                true;
        }
    }


    // =========================================================
    // EVADE:
    // DASH AWAY IF PLAYER IS CROWDING
    // =========================================================

    else if (
        opponentState ==
        OpponentState::Evade
        )
    {
        if (
            distance <
            170.0f
            )
        {
            shouldDash =
                true;
        }
    }


    // =========================================================
    // RECOVER:
    // EVEN MORE DESPERATE TO CREATE SPACE
    // =========================================================

    else if (
        opponentState ==
        OpponentState::Recover
        )
    {
        if (
            distance <
            230.0f
            )
        {
            shouldDash =
                true;
        }
    }


    if (!shouldDash)
    {
        return;
    }


    opponentStamina -=
        dashCost;


    if (
        opponentStamina <
        0.0f
        )
    {
        opponentStamina =
            0.0f;
        opponentStaminaRegenClock.restart();
    }


    opponentDashing =
        true;


    opponentDashClock.restart();

    opponentDashCooldownClock.restart();
}
void SquidGame::checkFightResult()
{
    if (gameFinished)
    {
        return;
    }


    // =========================================================
    // PLAYER LOST
    // =========================================================

    if (
        humanHealth <= 0.0f
        )
    {
        humanHealth =
            0.0f;

        gameFinished =
            true;

        fightResult =
            FightResult::HumanLost;


        if (humanPlayer != nullptr)
        {
            humanPlayer->eliminate();
        }


        resultText.setString(
            "YOU LOST"
        );

        resultText.setPosition(
            525.0f,
            300.0f
        );


        resultButtonText.setString(
            "Retry"
        );

        resultButtonText.setPosition(
            605.0f,
            405.0f
        );


        updateBars();

        return;
    }


    // =========================================================
    // PLAYER WON
    // =========================================================

    if (
        opponentHealth <= 0.0f
        )
    {
        opponentHealth =
            0.0f;

        gameFinished =
            true;

        fightResult =
            FightResult::HumanWon;


        if (opponent != nullptr)
        {
            opponent->eliminate();
        }


        resultText.setString(
            "YOU WON!!"
        );

        resultText.setPosition(
            510.0f,
            300.0f
        );


        resultButtonText.setString(
            "Continue"
        );

        resultButtonText.setPosition(
            585.0f,
            405.0f
        );


        updateBars();

        return;
    }
}

bool SquidGame::isFinished() const
{
    return gameFinished;
}


bool SquidGame::didHumanWin() const
{
    return
        fightResult ==
        FightResult::HumanWon;
}


bool SquidGame::didHumanLose() const
{
    return
        fightResult ==
        FightResult::HumanLost;
}
bool SquidGame::consumeResultButtonClick()
{
    if (!resultButtonClicked)
    {
        return false;
    }


    resultButtonClicked =
        false;

    return true;
}

std::vector<Participant*> SquidGame::getFinalists() const
{
    return finalists;
}

// =============================================================
// DASH SLASH EFFECT
// =============================================================

void SquidGame::drawDashSlash(
    sf::RenderWindow& window,
    sf::Vector2f position,
    sf::Vector2f direction
)
{
    float directionLength =
        std::sqrt(
            direction.x *
            direction.x +

            direction.y *
            direction.y
        );


    if (
        directionLength <
        0.001f
        )
    {
        return;
    }


    direction.x /=
        directionLength;

    direction.y /=
        directionLength;


    float angle =
        std::atan2(
            direction.y,
            direction.x
        ) *
        180.0f /
        3.14159265f;


    // =========================================================
    // THREE SPEED SLASHES
    // =========================================================

    for (
        int i = 0;
        i < 3;
        i++
        )
    {
        float slashLength =
            30.0f -
            (
                i *
                6.0f
                );


        sf::RectangleShape slash;


        slash.setSize(
            sf::Vector2f(
                slashLength,
                3.0f
            )
        );


        slash.setOrigin(
            slashLength,
            1.5f
        );


        slash.setRotation(
            angle
        );


        slash.setPosition(
            position.x -
            direction.x *
            (
                12.0f +
                i *
                9.0f
                ),

            position.y -
            direction.y *
            (
                12.0f +
                i *
                9.0f
                )
        );


        slash.setFillColor(
            sf::Color(
                255,
                255,
                255,
                190 -
                i *
                50
            )
        );


        window.draw(
            slash
        );
    }
}