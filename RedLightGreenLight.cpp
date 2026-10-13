#include "RedLightGreenLight.h"

#include <cstdlib>
#include <ctime>
#include <string>


// =============================================================
// CONSTRUCTOR
// =============================================================

RedLightGreenLight::RedLightGreenLight(

    HumanPlayer& player,

    CPUPlayer& cpu1,
    CPUPlayer& cpu2,
    CPUPlayer& cpu3,
    CPUPlayer& cpu4,
    CPUPlayer& cpu5,
    CPUPlayer& cpu6,
    CPUPlayer& cpu7,
    CPUPlayer& cpu8,
    CPUPlayer& cpu9,
    CPUPlayer& cpu10,
    CPUPlayer& cpu11,
    CPUPlayer& cpu12,
    CPUPlayer& cpu13,
    CPUPlayer& cpu14,
    CPUPlayer& cpu15
)

    : player(player),

    cpu1(cpu1),
    cpu2(cpu2),
    cpu3(cpu3),
    cpu4(cpu4),
    cpu5(cpu5),
    cpu6(cpu6),
    cpu7(cpu7),
    cpu8(cpu8),
    cpu9(cpu9),
    cpu10(cpu10),
    cpu11(cpu11),
    cpu12(cpu12),
    cpu13(cpu13),
    cpu14(cpu14),
    cpu15(cpu15)

{
    // =========================================================
    // STARTING POSITIONS
    // =========================================================

    // =========================================================
// STARTING GRID
// Entire grid stays on the sandy ground.
// =========================================================

// LEFT COLUMN
    player.setPosition(120, 270);

    cpu1.setPosition(120, 325);
    cpu2.setPosition(120, 380);
    cpu3.setPosition(120, 435);
    cpu4.setPosition(120, 490);
    cpu5.setPosition(120, 545);
    cpu6.setPosition(120, 600);
    cpu7.setPosition(120, 655);


    // RIGHT COLUMN
    cpu8.setPosition(320, 270);
    cpu9.setPosition(320, 325);
    cpu10.setPosition(320, 380);
    cpu11.setPosition(320, 435);
    cpu12.setPosition(320, 490);
    cpu13.setPosition(320, 545);
    cpu14.setPosition(320, 600);
    cpu15.setPosition(320, 655);


    // =========================================================
    // CPU POINTER ARRAY
    // =========================================================

    cpuPlayers[0] = &cpu1;
    cpuPlayers[1] = &cpu2;
    cpuPlayers[2] = &cpu3;
    cpuPlayers[3] = &cpu4;
    cpuPlayers[4] = &cpu5;

    cpuPlayers[5] = &cpu6;
    cpuPlayers[6] = &cpu7;
    cpuPlayers[7] = &cpu8;
    cpuPlayers[8] = &cpu9;
    cpuPlayers[9] = &cpu10;

    cpuPlayers[10] = &cpu11;
    cpuPlayers[11] = &cpu12;
    cpuPlayers[12] = &cpu13;
    cpuPlayers[13] = &cpu14;
    cpuPlayers[14] = &cpu15;


    // =========================================================
    // SPRITE CROP COORDINATES
    //
    // EACH SOURCE SHEET CONTAINS FOUR CHARACTER DESIGNS.
    // WE USE THE RIGHT-FACING IDLE / WALK POSES.
    // =========================================================

    idleX[0] = 64;
    idleX[1] = 224;
    idleX[2] = 64;
    idleX[3] = 224;

    idleX[4] = 64;
    idleX[5] = 224;
    idleX[6] = 64;
    idleX[7] = 224;


    idleY[0] = 32;
    idleY[1] = 32;
    idleY[2] = 192;
    idleY[3] = 192;

    idleY[4] = 32;
    idleY[5] = 32;
    idleY[6] = 192;
    idleY[7] = 192;


    walkX[0] = 64;
    walkX[1] = 224;
    walkX[2] = 64;
    walkX[3] = 224;

    walkX[4] = 64;
    walkX[5] = 224;
    walkX[6] = 64;
    walkX[7] = 224;


    walkY[0] = 96;
    walkY[1] = 96;
    walkY[2] = 256;
    walkY[3] = 256;

    walkY[4] = 96;
    walkY[5] = 96;
    walkY[6] = 256;
    walkY[7] = 256;


    // =========================================================
    // SOURCE FILES
    // =========================================================
    std::string playerSetA[5] =
    {
        "PlayersSetA1.png",
        "PlayersSetA2.png",
        "PlayersSetA3.png",
        "PlayersSetA4.png",
        "PlayersSetA5.png"
    };


    std::string playerSetB[5] =
    {
        "PlayersSetB1.png",
        "PlayersSetB2.png",
        "PlayersSetB3.png",
        "PlayersSetB4.png",
        "PlayersSetB5.png"
    };

    // =========================================================
// PLAYER 1 SPRITE
// =========================================================

    playerIdleTexture.loadFromFile(
        playerSetA[0]
    );

    playerIdleTexture.setSmooth(
        false
    );


    for (
        int frame = 0;
        frame < 5;
        frame++
        )
    {
        playerWalkTextures[frame]
            .loadFromFile(
                playerSetA[frame]
            );

        playerWalkTextures[frame]
            .setSmooth(
                false
            );
    }


    playerSprite.setTexture(
        playerIdleTexture
    );


    // Design 0, right-facing idle
    playerSprite.setTextureRect(
        sf::IntRect(
            64,
            32,
            16,
            32
        )
    );


    playerSprite.setScale(
        2.0f,
        2.0f
    );


    playerWalkFrame =
        0;


    playerAnimationClock.restart();
    playerMovementVisualClock.restart();


    // =========================================================
    // LOAD CPU SPRITES
    // =========================================================

    for (
        int i = 0;
        i < 15;
        i++
        )
    {
        int designIndex =
            i % 8;


        // -----------------------------------------------------
        // DESIGNS 0 - 3 USE FIRST FOUR-PLAYER SHEET
        // DESIGNS 4 - 7 USE SECOND FOUR-PLAYER SHEET
        // -----------------------------------------------------

        std::string* selectedFiles;


        if (
            designIndex < 4
            )
        {
            selectedFiles =
                playerSetA;
        }

        else
        {
            selectedFiles =
                playerSetB;
        }


        // -----------------------------------------------------
        // IDLE
        // -----------------------------------------------------

        cpuIdleTextures[i].loadFromFile(
            selectedFiles[0]
        );


        cpuIdleTextures[i].setSmooth(
            false
        );


        // -----------------------------------------------------
        // WALK FRAMES
        // -----------------------------------------------------

        for (
            int frame = 0;
            frame < 5;
            frame++
            )
        {
            cpuWalkTextures[i][frame]
                .loadFromFile(
                    selectedFiles[frame]
                );


            cpuWalkTextures[i][frame]
                .setSmooth(
                    false
                );
        }


        // -----------------------------------------------------
        // DEFAULT SPRITE STATE
        // -----------------------------------------------------

        cpuSprites[i].setTexture(
            cpuIdleTextures[i]
        );


        cpuSprites[i].setTextureRect(
            sf::IntRect(
                idleX[designIndex],
                idleY[designIndex],
                16,
                32
            )
        );


        cpuSprites[i].setScale(
            2.0f,
            2.0f
        );


        cpuWalkFrame[i] =
            0;


        cpuAnimationClocks[i].restart();

        cpuMovementVisualClocks[i].restart();
    }


    // =========================================================
// RLGL BACKGROUND
// =========================================================

    if (
        backgroundTexture.loadFromFile(
            "RLGLBackground.png"
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
 // FINISH LINE
 // Uses the white line already drawn in the background.
 // The SFML rectangle remains invisible and is used only
 // for finish detection.
 // =========================================================

    finishLine.setSize(
        sf::Vector2f(
            6.0f,
            508.0f
        )
    );

    finishLine.setPosition(
        1210.0f,
        212.0f
    );

    finishLine.setFillColor(
        sf::Color::Transparent
    );

    // =========================================================
    // FONT
    // =========================================================

    font.loadFromFile(
        "arial.ttf"
    );

    // =========================================================
// PLAYER 1 MARKER
// =========================================================

    playerOneLabel.setFont(
        font
    );

    playerOneLabel.setString(
        "P1"
    );

    playerOneLabel.setCharacterSize(
        16
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
    // LIGHT TEXT
    // =========================================================

    lightText.setFont(
        font
    );


    lightText.setString(
        "GREEN LIGHT"
    );


    lightText.setCharacterSize(
        40
    );


    lightText.setPosition(
        500,
        40
    );


    lightText.setFillColor(
        sf::Color::Green
    );


    // =========================================================
    // RESULT TEXT
    // =========================================================

    resultText.setFont(
        font
    );


    resultText.setCharacterSize(
        60
    );


    resultText.setPosition(
        350,
        300
    );


    resultText.setFillColor(
        sf::Color::Red
    );

    // =========================================================
// DOLL TEXTURES
// =========================================================

    std::string dollFiles[11] =
    {
        "doll1.png",
        "doll2.png",
        "doll3.png",
        "doll4.png",
        "doll5.png",
        "doll6.png",
        "doll7.png",
        "doll8.png",
        "doll9.png",
        "doll10.png",
        "doll11.png"
    };


    for (
        int i = 0;
        i < 11;
        i++
        )
    {
        dollTextures[i].loadFromFile(
            dollFiles[i]
        );

        dollTextures[i].setSmooth(
            false
        );
    }


    // ---------------------------------------------------------
    // DOLL STARTING FRAME
    // ---------------------------------------------------------

    dollFrame =
        5;


    dollSprite.setTexture(
        dollTextures[dollFrame]
    );


    // Crop around actual doll inside 320x320 image
    dollSprite.setTextureRect(
        sf::IntRect(
            128,
            120,
            64,
            120
        )
    );


    dollSprite.setScale(
        1.0f,
        1.0f
    );


    dollSprite.setPosition(
        608.0f,
        75.0f
    );


    dollAnimationClock.restart();


    // =========================================================
    // GUARD TEXTURES
    // =========================================================

    std::string guardFiles[5] =
    {
        "FourGuarArmed1.png",
        "FourGuarArmed2.png",
        "FourGuarArmed3.png",
        "FourGuarArmed4.png",
        "FourGuarArmed5.png"
    };


    for (
        int i = 0;
        i < 5;
        i++
        )
    {
        guardTextures[i].loadFromFile(
            guardFiles[i]
        );

        guardTextures[i].setSmooth(
            false
        );
    }


    guardFrame =
        0;


    // =========================================================
    // SET UP ALL SIX GUARDS
    // =========================================================

    for (
        int i = 0;
        i < 6;
        i++
        )
    {
        guardSprites[i].setTexture(
            guardTextures[0]
        );


        // Front-facing armed guard
        guardSprites[i].setTextureRect(
            sf::IntRect(
                16,
                32,
                16,
                32
            )
        );


        guardSprites[i].setScale(
            2.0f,
            2.0f
        );
    }


    // =========================================================
    // GUARD POSITIONS
    // =========================================================

    // LEFT SIDE

    guardSprites[0].setPosition(
        300.0f,
        135.0f
    );

    guardSprites[1].setPosition(
        365.0f,
        135.0f
    );

    guardSprites[2].setPosition(
        430.0f,
        135.0f
    );


    // RIGHT SIDE

    guardSprites[3].setPosition(
        825.0f,
        135.0f
    );

    guardSprites[4].setPosition(
        890.0f,
        135.0f
    );

    guardSprites[5].setPosition(
        955.0f,
        135.0f
    );


    guardAnimationClock.restart();


    // =========================================================
    // CONTINUE BUTTON
    // =========================================================

    continueButtonBox.setSize(
        sf::Vector2f(
            200.0f,
            60.0f
        )
    );


    continueButtonBox.setPosition(
        520.0f,
        620.0f
    );


    continueButtonBox.setFillColor(
        sf::Color(
            60,
            60,
            60
        )
    );


    continueButtonBox.setOutlineColor(
        sf::Color::White
    );


    continueButtonBox.setOutlineThickness(
        2.0f
    );


    continueButton.setFont(
        font
    );


    continueButton.setString(
        "Continue"
    );


    continueButton.setCharacterSize(
        28
    );


    continueButton.setFillColor(
        sf::Color::White
    );


    continueButton.setPosition(
        560.0f,
        632.0f
    );


    // =========================================================
    // CPU RESULT TEXT
    // =========================================================

    cpuResultText.setFont(
        font
    );


    cpuResultText.setCharacterSize(
        24
    );


    cpuResultText.setPosition(
        350,
        500
    );


    cpuResultText.setFillColor(
        sf::Color::White
    );

    playerOneLabel.setFont(font);
    playerOneLabel.setString("P1");
    playerOneLabel.setCharacterSize(16);
    playerOneLabel.setFillColor(sf::Color::Yellow);
    playerOneLabel.setOutlineColor(sf::Color::Black);
    playerOneLabel.setOutlineThickness(2.0f);


    // =========================================================
// RLGL AUDIO
// =========================================================

    greenLightBuffer.loadFromFile(
        "Green_Light.mp3"
    );

    redLightBuffer.loadFromFile(
        "Red_light.mp3"
    );

    gunshotBuffer.loadFromFile(
        "Gunshot.wav"
    );


    greenLightSound.setBuffer(
        greenLightBuffer
    );

    redLightSound.setBuffer(
        redLightBuffer
    );

    gunshotSound.setBuffer(
        gunshotBuffer
    );

    // =========================================================
    // GAME VALUES
    // =========================================================

    greenLight =
        true;
    initialGreenSoundPlayed =
        false;

    playerFinished =
        false;

    playerEliminated =
        false;

    playerFinishPosition =
        0;

    cpuCheckedRedLight =
        false;

    nextFinishPosition =
        1;


    std::srand(
        static_cast<unsigned int>(
            std::time(
                nullptr
            )
            )
    );


    lightDuration =
        3.0f;


    lightClock.restart();

    cpuClock.restart();
}


// =============================================================
// HANDLE INPUT
// =============================================================

GameState RedLightGreenLight::handleInput(
    sf::Event& event
)
{
    if (
        event.type ==
        sf::Event::KeyPressed
        )
    {
        if (
            event.key.code ==
            sf::Keyboard::W
            )
        {
            if (
                greenLight &&
                !playerFinished &&
                !playerEliminated
                )
            {
                player.move(
                    1.5f,
                    0.0f
                );


                playerMovementVisualClock
                    .restart();
            }


            else if (
                !greenLight
                )
            {
                playerEliminated =
                    true;


                player.eliminate();
                gunshotSound.stop();
                gunshotSound.play();
            }
        }
    }


    // =========================================================
    // RESULT BUTTON
    // =========================================================

    if (
        playerFinished ||
        playerEliminated
        )
    {
        if (
            event.type ==
            sf::Event::MouseButtonPressed
            )
        {
            if (
                event.mouseButton.button ==
                sf::Mouse::Left
                )
            {
                float mouseX =
                    static_cast<float>(
                        event.mouseButton.x
                        );


                float mouseY =
                    static_cast<float>(
                        event.mouseButton.y
                        );


                if (
                    continueButtonBox
                    .getGlobalBounds()
                    .contains(
                        mouseX,
                        mouseY
                    )
                    )
                {
                    return
                        GameState::GameSelection;
                }
            }
        }
    }


    return
        GameState::Playing;
}


// =============================================================
// UPDATE
// =============================================================

void RedLightGreenLight::update()
{
    if (
        playerFinished ||
        playerEliminated
        )
    {
        return;
    }

    // =========================================================
// INITIAL GREEN LIGHT AUDIO
// =========================================================

    if (
        !initialGreenSoundPlayed
        )
    {
        greenLightSound.stop();
        greenLightSound.play();

        initialGreenSoundPlayed =
            true;
    }


    // =========================================================
    // GUARD IDLE ANIMATION
    // =========================================================

    if (
        guardAnimationClock
        .getElapsedTime()
        .asSeconds() >=
        0.18f
        )
    {
        guardAnimationClock.restart();

        guardFrame++;

        if (
            guardFrame >=
            5
            )
        {
            guardFrame =
                0;
        }


        for (
            int i = 0;
            i < 6;
            i++
            )
        {
            guardSprites[i].setTexture(
                guardTextures[guardFrame]
            );


            guardSprites[i].setTextureRect(
                sf::IntRect(
                    16,
                    32,
                    16,
                    32
                )
            );
        }
    }


    // =========================================================
    // CHANGE LIGHT
    // =========================================================

    if (
        lightClock
        .getElapsedTime()
        .asSeconds() >=
        lightDuration
        )
    {
        greenLight =
            !greenLight;


        // VERY IMPORTANT
        lightClock.restart();


        cpuCheckedRedLight =
            false;


        // =====================================================
        // LIGHT AUDIO
        // =====================================================

        greenLightSound.stop();
        redLightSound.stop();


        if (
            greenLight
            )
        {
            greenLightSound.play();
        }

        else
        {
            redLightSound.play();

            redLightGraceClock.restart();
        }


        // =====================================================
        // RANDOM LIGHT DURATION
        // =====================================================

        int randomTime =
            0;


        if (
            greenLight
            )
        {
            randomTime =
                2 +
                (
                    std::rand() %
                    4
                    );
        }

        else
        {
            randomTime =
                2 +
                (
                    std::rand() %
                    3
                    );
        }


        lightDuration =
            static_cast<float>(
                randomTime
                );
    }


    // =========================================================
    // GREEN LIGHT
    // =========================================================

    if (
        greenLight
        )
    {
        lightText.setString(
            "GREEN LIGHT"
        );


        lightText.setFillColor(
            sf::Color::Green
        );


        if (
            cpuClock
            .getElapsedTime()
            .asSeconds() >=
            0.2f
            )
        {
            cpuClock.restart();


            for (
                int i = 0;
                i < 15;
                i++
                )
            {
                if (
                    cpuPlayers[i]
                    ->isAlive() &&

                    !cpuPlayers[i]
                    ->hasFinished()
                    )
                {
                    if (
                        cpuPlayers[i]
                        ->shouldMove()
                        )
                    {
                        float movementAmount;


                        if (
                            i < 3
                            )
                        {
                            movementAmount =
                                12.0f;
                        }

                        else
                        {
                            movementAmount =
                                10.0f;
                        }


                        cpuPlayers[i]
                            ->move(
                                movementAmount,
                                0.0f
                            );


                        cpuMovementVisualClocks[i]
                            .restart();
                    }
                }
            }
        }
    }


    // =========================================================
    // RED LIGHT
    // =========================================================

    else
    {
        lightText.setString(
            "RED LIGHT"
        );


        lightText.setFillColor(
            sf::Color::Red
        );


        // =====================================================
        // PLAYER MOVEMENT CHECK
        // =====================================================

        if (
            redLightGraceClock
            .getElapsedTime()
            .asSeconds() >=
            0.2f
            )
        {
            if (
                sf::Keyboard::isKeyPressed(
                    sf::Keyboard::W
                )
                )
            {
                if (
                    !playerEliminated
                    )
                {
                    playerEliminated =
                        true;


                    player.eliminate();


                    gunshotSound.stop();
                    gunshotSound.play();
                }
            }
        }


        // =====================================================
        // CPU RED LIGHT CHECK
        // =====================================================

        if (
            !cpuCheckedRedLight
            )
        {
            cpuCheckedRedLight =
                true;


            bool somebodyEliminated =
                false;


            for (
                int i = 0;
                i < 15;
                i++
                )
            {
                if (
                    cpuPlayers[i]
                    ->isAlive() &&

                    !cpuPlayers[i]
                    ->hasFinished() &&

                    cpuPlayers[i]
                    ->getPosition().x <
                    finishLine
                    .getPosition().x &&

                    cpuPlayers[i]
                    ->getsCaught()
                    )
                {
                    cpuPlayers[i]
                        ->eliminate();


                    somebodyEliminated =
                        true;
                }
            }


            if (
                somebodyEliminated
                )
            {
                gunshotSound.stop();
                gunshotSound.play();
            }
        }
    }


    // =========================================================
    // PLAYER FINISH
    // =========================================================

    if (
        !playerFinished &&
        !playerEliminated &&
        player
        .getPosition().x >=
        finishLine
        .getPosition().x
        )
    {
        playerFinished =
            true;


        playerFinishPosition =
            nextFinishPosition;


        nextFinishPosition++;
    }


    // =========================================================
    // CPU FINISHES
    // =========================================================

    for (
        int i = 0;
        i < 15;
        i++
        )
    {
        if (
            cpuPlayers[i]
            ->isAlive() &&

            !cpuPlayers[i]
            ->hasFinished() &&

            cpuPlayers[i]
            ->getPosition().x >=
            finishLine
            .getPosition().x
            )
        {
            cpuPlayers[i]
                ->finish();


            cpuPlayers[i]
                ->setFinishPosition(
                    nextFinishPosition
                );


            nextFinishPosition++;
        }
    }
}

// =============================================================
// DRAW
// =============================================================

void RedLightGreenLight::draw(
    sf::RenderWindow& window
)
{
    // =========================================================
// BACKGROUND
// =========================================================

    window.draw(
        backgroundSprite
    );

    // =========================================================
// DOLL
// =========================================================

    window.draw(
        dollSprite
    );


    // =========================================================
    // GUARDS
    // =========================================================

    for (
        int i = 0;
        i < 6;
        i++
        )
    {
        window.draw(
            guardSprites[i]
        );
    }

    // =========================================================
// PLAYER 1 SPRITE
// =========================================================

    sf::Vector2f playerPosition =
        player.getPosition();


    playerSprite.setPosition(
        playerPosition.x + 4.0f,
        playerPosition.y - 12.0f
    );


    // ---------------------------------------------------------
    // IS PLAYER 1 CURRENTLY MOVING?
    // ---------------------------------------------------------

    bool playerVisuallyMoving =
        greenLight &&
        !playerFinished &&
        !playerEliminated &&
        playerMovementVisualClock
        .getElapsedTime()
        .asSeconds() <
        0.23f;


    // =========================================================
    // PLAYER WALK ANIMATION
    // =========================================================

    if (
        playerVisuallyMoving
        )
    {
        if (
            playerAnimationClock
            .getElapsedTime()
            .asSeconds() >=
            0.08f
            )
        {
            playerAnimationClock
                .restart();


            playerWalkFrame++;


            if (
                playerWalkFrame >=
                5
                )
            {
                playerWalkFrame =
                    0;
            }
        }


        playerSprite.setTexture(
            playerWalkTextures[
                playerWalkFrame
            ]
        );


        playerSprite.setTextureRect(
            sf::IntRect(
                64,
                96,
                16,
                32
            )
        );
    }


    // =========================================================
    // PLAYER IDLE
    // =========================================================

    else
    {
        playerSprite.setTexture(
            playerIdleTexture
        );


        playerSprite.setTextureRect(
            sf::IntRect(
                64,
                32,
                16,
                32
            )
        );


        playerWalkFrame =
            0;
    }


    // =========================================================
    // DRAW PLAYER
    // =========================================================

    if (
        player.isAlive()
        )
    {
        window.draw(
            playerSprite
        );


        // -----------------------------------------------------
        // P1 MARKER
        // -----------------------------------------------------

        sf::FloatRect playerBounds =
            playerSprite
            .getGlobalBounds();


        playerOneLabel.setPosition(
            playerBounds.left +
            playerBounds.width / 2.0f -
            10.0f,

            playerBounds.top -
            22.0f
        );


        window.draw(
            playerOneLabel
        );
    }


    // =========================================================
    // CPU SPRITES
    // =========================================================

    for (
        int i = 0;
        i < 15;
        i++
        )
    {
        int designIndex =
            i % 8;


        sf::Vector2f cpuPosition =
            cpuPlayers[i]
            ->getPosition();


        // -----------------------------------------------------
        // KEEP SPRITE CENTRED OVER ORIGINAL CPU POSITION
        // -----------------------------------------------------

        cpuSprites[i].setPosition(
            cpuPosition.x + 4.0f,
            cpuPosition.y - 12.0f
        );


        // -----------------------------------------------------
        // DID THIS CPU MOVE RECENTLY?
        // -----------------------------------------------------

        bool cpuVisuallyMoving =
            greenLight &&

            cpuPlayers[i]
            ->isAlive() &&

            !cpuPlayers[i]
            ->hasFinished() &&

            cpuMovementVisualClocks[i]
            .getElapsedTime()
            .asSeconds() <
            0.23f;


        // =====================================================
        // WALKING
        // =====================================================

        if (
            cpuVisuallyMoving
            )
        {
            if (
                cpuAnimationClocks[i]
                .getElapsedTime()
                .asSeconds() >=
                0.08f
                )
            {
                cpuAnimationClocks[i]
                    .restart();


                cpuWalkFrame[i]++;


                if (
                    cpuWalkFrame[i] >=
                    5
                    )
                {
                    cpuWalkFrame[i] =
                        0;
                }
            }


            cpuSprites[i].setTexture(
                cpuWalkTextures[i][
                    cpuWalkFrame[i]
                ]
            );


            cpuSprites[i].setTextureRect(
                sf::IntRect(
                    walkX[designIndex],
                    walkY[designIndex],
                    16,
                    32
                )
            );
        }


        // =====================================================
        // IDLE
        // =====================================================

        else
        {
            cpuSprites[i].setTexture(
                cpuIdleTextures[i]
            );


            cpuSprites[i].setTextureRect(
                sf::IntRect(
                    idleX[designIndex],
                    idleY[designIndex],
                    16,
                    32
                )
            );


            cpuWalkFrame[i] =
                0;
        }


        // =====================================================
        // DRAW ONLY LIVING CPUs
        // =====================================================

        if (
            cpuPlayers[i]
            ->isAlive()
            )
        {
            window.draw(
                cpuSprites[i]
            );
        }
    }

    // =========================================================
// RESET DOLL
// =========================================================

    dollFrame =
        0;


    dollSprite.setTexture(
        dollTextures[dollFrame]
    );


    dollSprite.setTextureRect(
        sf::IntRect(
            128,
            120,
            64,
            120
        )
    );


    dollAnimationClock.restart();


    // =========================================================
    // RESET GUARDS
    // =========================================================

    guardFrame =
        0;


    for (
        int i = 0;
        i < 6;
        i++
        )
    {
        guardSprites[i].setTexture(
            guardTextures[0]
        );


        guardSprites[i].setTextureRect(
            sf::IntRect(
                16,
                32,
                16,
                32
            )
        );
    }


    guardAnimationClock.restart();


    // =========================================================
    // FINISH LINE / LIGHT
    // =========================================================

    


    window.draw(
        lightText
    );


    // =========================================================
    // PLAYER RESULT
    // =========================================================

    if (
        playerFinished
        )
    {
        resultText.setString(
            "YOU FINISHED #" +
            std::to_string(
                playerFinishPosition
            ) +
            "!"
        );


        resultText.setPosition(
            470,
            120
        );


        resultText.setCharacterSize(
            42
        );


        window.draw(
            resultText
        );


        window.draw(
            continueButtonBox
        );


        window.draw(
            continueButton
        );
    }


    else if (
        playerEliminated
        )
    {
        resultText.setString(
            "YOU ARE ELIMINATED!"
        );


        resultText.setCharacterSize(
            38
        );


        resultText.setPosition(
            430,
            560
        );


        window.draw(
            resultText
        );


        window.draw(
            continueButtonBox
        );


        window.draw(
            continueButton
        );
    }


    // =========================================================
    // CPU RESULTS
    // =========================================================

    std::string cpuResults =
        "";


    for (
        int i = 0;
        i < 15;
        i++
        )
    {
        if (
            cpuPlayers[i]
            ->hasFinished()
            )
        {
            cpuResults +=
                cpuPlayers[i]
                ->getName() +

                " finished #" +

                std::to_string(
                    cpuPlayers[i]
                    ->getFinishPosition()
                ) +

                "\n";
        }
    }


    cpuResultText.setString(
        cpuResults
    );


    cpuResultText.setCharacterSize(
        16
    );


    cpuResultText.setPosition(
        350,
        230
    );


    if (
        playerFinished ||
        playerEliminated
        )
    {
        window.draw(
            cpuResultText
        );
    }
}


// =============================================================
// IS FINISHED
// =============================================================

bool RedLightGreenLight::isFinished()
{
    return
        playerFinished ||
        playerEliminated;
}


// =============================================================
// RESET
// =============================================================

void RedLightGreenLight::reset()
{
    // =========================================================
    // PLAYER
    // =========================================================

    player.setPosition(
        120,
        270
    );

    playerWalkFrame =
        0;


    playerAnimationClock.restart();

    playerMovementVisualClock.restart();


    playerSprite.setTexture(
        playerIdleTexture
    );


    playerSprite.setTextureRect(
        sf::IntRect(
            64,
            32,
            16,
            32
        )
    );

    // =========================================================
    // REVIVE CPUs
    // =========================================================

    for (
        int i = 0;
        i < 15;
        i++
        )
    {
        cpuPlayers[i]
            ->revive();
    }


    // =========================================================
// RESET STARTING GRID
// =========================================================

   


    // LEFT COLUMN
    cpu1.setPosition(120, 325);
    cpu2.setPosition(120, 380);
    cpu3.setPosition(120, 435);
    cpu4.setPosition(120, 490);
    cpu5.setPosition(120, 545);
    cpu6.setPosition(120, 600);
    cpu7.setPosition(120, 655);


    // RIGHT COLUMN
    cpu8.setPosition(320, 270);
    cpu9.setPosition(320, 325);
    cpu10.setPosition(320, 380);
    cpu11.setPosition(320, 435);
    cpu12.setPosition(320, 490);
    cpu13.setPosition(320, 545);
    cpu14.setPosition(320, 600);
    cpu15.setPosition(320, 655);


    // =========================================================
    // RESET ANIMATION
    // =========================================================

    for (
        int i = 0;
        i < 15;
        i++
        )
    {
        cpuWalkFrame[i] =
            0;


        cpuAnimationClocks[i]
            .restart();


        cpuMovementVisualClocks[i]
            .restart();


        int designIndex =
            i % 8;


        cpuSprites[i].setTexture(
            cpuIdleTextures[i]
        );


        cpuSprites[i].setTextureRect(
            sf::IntRect(
                idleX[designIndex],
                idleY[designIndex],
                16,
                32
            )
        );
    }


    // =========================================================
    // RESET GAME VALUES
    // =========================================================

    greenLight =
        true;
    initialGreenSoundPlayed =
        false;

    playerFinished =
        false;


    playerEliminated =
        false;


    playerFinishPosition =
        0;


    cpuCheckedRedLight =
        false;


    nextFinishPosition =
        1;


    lightDuration =
        3.0f;


    lightClock.restart();

    cpuClock.restart();

    dollFrame =
        5;

    lightText.setString(
        "GREEN LIGHT"
    );


    lightText.setFillColor(
        sf::Color::Green
    );
}


// =============================================================
// PREPARE NEXT GAME
// =============================================================

void RedLightGreenLight::prepareNextGame()
{
    player.resetForNextGame();


    for (
        int i = 0;
        i < 15;
        i++
        )
    {
        cpuPlayers[i]
            ->resetForNextGame();
    }
}