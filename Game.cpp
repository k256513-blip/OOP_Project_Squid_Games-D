#include "Game.h"
#include <string>


Game::Game()
    : player("Player 1", sf::Color::Blue),

    cpu1("Player 2", 70, sf::Color::Red),
    cpu2("Player 3", 80, sf::Color::Green),
    cpu3("Player 4", 60, sf::Color::Yellow),
    cpu4("Player 5", 90, sf::Color::Magenta),
    cpu5("Player 6", 50, sf::Color::Cyan),

    cpu6("Player 7", 75, sf::Color(255, 128, 0)),
    cpu7("Player 8", 65, sf::Color(128, 0, 255)),
    cpu8("Player 9", 85, sf::Color(255, 105, 180)),
    cpu9("Player 10", 55, sf::Color(128, 128, 128)),
    cpu10("Player 11", 95, sf::Color(255, 255, 255)),

    cpu11("Player 12", 68, sf::Color(139, 69, 19)),
    cpu12("Player 13", 72, sf::Color(0, 128, 128)),
    cpu13("Player 14", 88, sf::Color(255, 215, 0)),
    cpu14("Player 15", 62, sf::Color(0, 191, 255)),
    cpu15("Player 16", 78, sf::Color(160, 32, 240)),

    redLightGreenLight(
        player,
        cpu1,
        cpu2,
        cpu3,
        cpu4,
        cpu5,
        cpu6,
        cpu7,
        cpu8,
        cpu9,
        cpu10,
        cpu11,
        cpu12,
        cpu13,
        cpu14,
        cpu15
    ),

    dalgona(
        &player,
        &cpu1,
        &cpu2,
        &cpu3,
        &cpu4,
        &cpu5
    ),

    tugOfWar()
{
    window.create(
        sf::VideoMode(1280, 720),
        "Squid Games"
    );

    currentState = GameState::MainMenu;
    currentGameIndex = 0;
    playerLives = 3;
    selectedBotCount = 15;

    paused = false;
    participants.push_back(&player);

    participants.push_back(&cpu1);
    participants.push_back(&cpu2);
    participants.push_back(&cpu3);
    participants.push_back(&cpu4);
    participants.push_back(&cpu5);
    participants.push_back(&cpu6);
    participants.push_back(&cpu7);
    participants.push_back(&cpu8);
    participants.push_back(&cpu9);
    participants.push_back(&cpu10);
    participants.push_back(&cpu11);
    participants.push_back(&cpu12);
    participants.push_back(&cpu13);
    participants.push_back(&cpu14);
    participants.push_back(&cpu15);

    font.loadFromFile("arial.ttf");

    // =========================================================
// LIVES UI
// =========================================================

    

    livesLabel.setFont(font);
    livesLabel.setString("Lives:");
    livesLabel.setCharacterSize(24);
    livesLabel.setFillColor(sf::Color::White);
    livesLabel.setPosition(30, 20);

    for (int i = 0; i < 3; i++)
    {
        heartTexts[i].setFont(font);
        heartTexts[i].setString(L"\u2665");
        heartTexts[i].setCharacterSize(28);
        heartTexts[i].setFillColor(sf::Color::Red);
        heartTexts[i].setPosition(
            110.0f + (i * 30.0f),
            15.0f
        );
    }


    // =========================================================
    // GAME OVER SCREEN
    // =========================================================

    gameOverBox.setSize(
        sf::Vector2f(520, 240)
    );

    gameOverBox.setPosition(
        380, 220
    );

    gameOverBox.setFillColor(
        sf::Color(30, 30, 30, 220)
    );

    gameOverBox.setOutlineColor(
        sf::Color::White
    );

    gameOverBox.setOutlineThickness(3.0f);


    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(56);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(470, 265);


    returnToMenuButtonBox.setSize(
        sf::Vector2f(280, 60)
    );

    returnToMenuButtonBox.setPosition(
        500, 370
    );

    returnToMenuButtonBox.setFillColor(
        sf::Color(60, 60, 60)
    );

    returnToMenuButtonBox.setOutlineColor(
        sf::Color::White
    );

    returnToMenuButtonBox.setOutlineThickness(2.0f);


    returnToMenuButton.setFont(font);
    returnToMenuButton.setString("Return to Main Menu");
    returnToMenuButton.setCharacterSize(26);
    returnToMenuButton.setFillColor(sf::Color::White);
    returnToMenuButton.setPosition(525, 385);

    // =========================================================
// BOT COUNT DISPLAY
// =========================================================

    botCountText.setFont(font);

    botCountText.setCharacterSize(24);

    botCountText.setFillColor(
        sf::Color::White
    );

    botCountText.setPosition(
        950.0f,
        620.0f
    );

    botCountText.setString(
        "Bots: 15   [ / ]"
    );


    // =========================================================
    // PAUSE SYSTEM
    // =========================================================

    pauseOverlay.setSize(
        sf::Vector2f(1280, 720)
    );

    pauseOverlay.setFillColor(
        sf::Color(255, 255, 255, 70)
    );


    resumeButtonBox.setSize(
        sf::Vector2f(220, 60)
    );

    resumeButtonBox.setPosition(
        530, 280
    );

    resumeButtonBox.setFillColor(
        sf::Color(60, 60, 60)
    );

    resumeButtonBox.setOutlineColor(
        sf::Color::White
    );

    resumeButtonBox.setOutlineThickness(
        2.0f
    );


    mainMenuButtonBox.setSize(
        sf::Vector2f(220, 60)
    );

    mainMenuButtonBox.setPosition(
        530, 370
    );

    mainMenuButtonBox.setFillColor(
        sf::Color(60, 60, 60)
    );

    mainMenuButtonBox.setOutlineColor(
        sf::Color::White
    );

    mainMenuButtonBox.setOutlineThickness(
        2.0f
    );


    resumeButton.setFont(font);
    resumeButton.setString("Resume");
    resumeButton.setCharacterSize(28);
    resumeButton.setFillColor(
        sf::Color::White
    );

    resumeButton.setPosition(
        585, 293
    );


    mainMenuButton.setFont(font);
    mainMenuButton.setString("Main Menu");
    mainMenuButton.setCharacterSize(28);
    mainMenuButton.setFillColor(
        sf::Color::White
    );

    mainMenuButton.setPosition(
        565, 383
    );


    // =========================================================
    // COMING SOON SCREEN
    // =========================================================

    comingSoonText.setFont(font);
    comingSoonText.setCharacterSize(50);
    comingSoonText.setPosition(400, 250);
    comingSoonText.setFillColor(sf::Color::White);


    continueButton.setFont(font);
    continueButton.setString("Continue");
    continueButton.setCharacterSize(32);
    continueButton.setPosition(500, 400);
    continueButton.setFillColor(sf::Color::White);


    // =========================================================
    // START COUNTDOWN
    // =========================================================

    countdownBox.setSize(
        sf::Vector2f(300, 140)
    );

    countdownBox.setPosition(
        490, 290
    );

    countdownBox.setFillColor(
        sf::Color(60, 60, 60, 230)
    );

    countdownBox.setOutlineColor(
        sf::Color::White
    );

    countdownBox.setOutlineThickness(
        3.0f
    );


    countdownText.setFont(font);
    countdownText.setCharacterSize(72);
    countdownText.setFillColor(
        sf::Color::White
    );

    countdownText.setString("3");

    countdownText.setPosition(
        625, 315
    );


    countdownActive = false;
    countdownNumber = 3;
}


// =============================================================
// START COUNTDOWN
// =============================================================

void Game::startCountdown()
{
    countdownActive = true;
    countdownNumber = 3;

    countdownText.setString("3");

    countdownClock.restart();
}


void Game::drawLives()
{
    window.draw(livesLabel);

    for (int i = 0; i < 3; i++)
    {
        if (i < playerLives)
        {
            heartTexts[i].setFillColor(sf::Color::Red);
        }
        else
        {
            heartTexts[i].setFillColor(
                sf::Color(80, 80, 80)
            );
        }

        window.draw(heartTexts[i]);
    }
}

void Game::resetAllParticipants()
{
    for (Participant* participant : participants)
    {
        participant->revive();
        participant->resetForNextGame();
    }
}

void Game::triggerGameOver()
{
    countdownActive = false;
    paused = false;
    currentState = GameState::GameOver;
}



// =============================================================
// MAIN GAME LOOP
// =============================================================

void Game::run()
{
    while (window.isOpen())
    {
        sf::Event event;


        // =====================================================
        // COUNTDOWN
        // =====================================================

        if (countdownActive && !paused)
        {
            if (
                countdownClock.getElapsedTime().asSeconds()
                >= 1.0f
                )
            {
                countdownClock.restart();

                countdownNumber--;


                if (countdownNumber == 0)
                {
                    countdownText.setString("GO!");
                }

                else if (countdownNumber < 0)
                {
                    countdownActive = false;


                    // -------------------------------------------------
                    // IMPORTANT:
                    // Reset AGAIN after the countdown.
                    //
                    // The first reset cleared the previous game's
                    // results/positions.
                    //
                    // This second reset makes the game's internal
                    // clocks begin from zero AFTER the countdown.
                    // -------------------------------------------------

                    if (currentState == GameState::Playing)
                        redLightGreenLight.reset();
                    else if (currentState == GameState::Dalgona)
                        dalgona.startGame();
                    else if (currentState == GameState::TugOfWar)
                        tugOfWar.startGame();
                    else if (currentState == GameState::GlassBridge)
                        glassBridge.startGame();
                    else if (currentState == GameState::Intermission)
                        intermission.startGame();
                    else if (currentState == GameState::SquidGame)
                        squidGame.startGame();
                }

                else
                {
                    countdownText.setString(
                        std::to_string(countdownNumber)
                    );
                }
            }
        }


        // =====================================================
        // EVENT PROCESSING
        // =====================================================

        while (window.pollEvent(event))
        {

            if (
                currentState == GameState::GameOver &&
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left
                )
            {
                float mouseX =
                    static_cast<float>(event.mouseButton.x);

                float mouseY =
                    static_cast<float>(event.mouseButton.y);

                if (
                    returnToMenuButtonBox.getGlobalBounds().contains(
                        mouseX,
                        mouseY
                    )
                    )
                {
                    playerLives = 3;

                    selectedGames.clear();
                    currentGameIndex = 0;

                    resetAllParticipants();

                    currentState = GameState::MainMenu;
                }

                continue;
            }

            // -------------------------------------------------
            // CLOSE WINDOW
            // -------------------------------------------------

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }


            // -------------------------------------------------
            // ESCAPE = PAUSE
            // -------------------------------------------------

            if (
                event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape
                )
            {
                if (
                    currentState != GameState::MainMenu &&
                    currentState != GameState::GameSelection
                    )
                {
                    paused = !paused;
                }

                continue;
            }


            // -------------------------------------------------
            // PAUSE MENU
            // -------------------------------------------------

            if (
                paused &&
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left
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


                // RESUME

                if (
                    resumeButtonBox.getGlobalBounds().contains(
                        mouseX,
                        mouseY
                    )
                    )
                {
                    paused = false;
                    continue;
                }


                // MAIN MENU

                if (
                    mainMenuButtonBox.getGlobalBounds().contains(
                        mouseX,
                        mouseY
                    )
                    )
                {
                    paused = false;

                    countdownActive = false;

                    selectedGames.clear();

                    currentGameIndex = 0;

                    currentState =
                        GameState::MainMenu;

                    continue;
                }

                continue;
            }


            // =================================================
            // GAME SELECTION
            // =================================================

            if (currentState ==
                GameState::GameSelection)
            {


                // =========================================================
// BOT COUNT CONTROLS
// =========================================================

                if (
                    event.type ==
                    sf::Event::KeyPressed
                    )
                {
                    // -----------------------------------------------------
                    // DECREASE BOT COUNT
                    // -----------------------------------------------------

                    if (
                        event.key.code ==
                        sf::Keyboard::LBracket
                        )
                    {
                        if (selectedBotCount > 1)
                        {
                            selectedBotCount--;
                        }


                        botCountText.setString(
                            "Bots: " +
                            std::to_string(
                                selectedBotCount
                            ) +
                            "   [ / ]"
                        );


                        continue;
                    }


                    // -----------------------------------------------------
                    // INCREASE BOT COUNT
                    // -----------------------------------------------------

                    if (
                        event.key.code ==
                        sf::Keyboard::RBracket
                        )
                    {
                        if (selectedBotCount < 15)
                        {
                            selectedBotCount++;
                        }


                        botCountText.setString(
                            "Bots: " +
                            std::to_string(
                                selectedBotCount
                            ) +
                            "   [ / ]"
                        );


                        continue;
                    }
                }


                // =========================================================
// DEBUG: INTERMISSION TEST
// =========================================================

                if (
                    event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::I
                    )
                {
                    // -----------------------------------------------------
                    // RESET EVERYONE FOR A CLEAN TEST
                    // -----------------------------------------------------

                    // =========================================================
// SET ACTIVE PARTICIPANTS FOR THIS SESSION
// =========================================================

                    for (
                        int i = 0;
                        i < static_cast<int>(
                            participants.size()
                            );
                            i++
                        )
                    {
                        Participant* participant =
                            participants[i];


                        participant->resetForNextGame();


                        // -----------------------------------------------------
                        // PLAYER 1 IS ALWAYS ACTIVE
                        // -----------------------------------------------------

                        if (i == 0)
                        {
                            participant->revive();
                        }


                        // -----------------------------------------------------
                        // ONLY THE SELECTED NUMBER OF CPUs ARE ACTIVE
                        //
                        // participants[1] = Player 2
                        // participants[2] = Player 3
                        // etc.
                        // -----------------------------------------------------

                        else if (
                            i <= selectedBotCount
                            )
                        {
                            participant->revive();
                        }


                        // -----------------------------------------------------
                        // UNUSED CPUs START ELIMINATED
                        // -----------------------------------------------------

                        else
                        {
                            participant->eliminate();
                        }
                    }



                    // -----------------------------------------------------
                    // CREATE A SMALL 4-PLAYER TEST GROUP
                    // -----------------------------------------------------

                    std::vector<Participant*> testParticipants;

                    testParticipants.push_back(&player);
                    testParticipants.push_back(&cpu1);
                    testParticipants.push_back(&cpu8);
                    testParticipants.push_back(&cpu14);


                    // -----------------------------------------------------
                    // START INTERMISSION
                    // -----------------------------------------------------

                    intermission.reset();
                    intermission.setParticipants(
                        testParticipants
                    );

                    currentState =
                        GameState::Intermission;

                    mainMenu.stopMusic();

                    startCountdown();

                    continue;
                }

                GameState newState =
                    gameSelection.handleInput(event);


                if (newState == GameState::Playing)
                {

                    // New tournament session = fresh lives.

                    playerLives = 3;

                    gameCheckpoint.clear();

                    // =========================================================
// NEW SESSION PARTICIPANT SETUP
// =========================================================

// First reset everybody.
// This prepares all Participant objects for a fresh session.

                    for (Participant* participant : participants)
                    {
                        participant->revive();
                        participant->resetForNextGame();
                    }


                    // ---------------------------------------------------------
                    // BUILD THE ACTIVE SESSION ROSTER
                    // ---------------------------------------------------------

                    sessionParticipants.clear();


                    // Player 1 is always included.

                    sessionParticipants.push_back(
                        &player
                    );


                    // Add only the selected number of CPUs.
                    //
                    // participants[0] = Player 1
                    // participants[1] = Player 2
                    // participants[2] = Player 3
                    // etc.

                    for (
                        int i = 1;
                        i <= selectedBotCount &&
                        i < static_cast<int>(
                            participants.size()
                            );
                        i++
                        )
                    {
                        sessionParticipants.push_back(
                            participants[i]
                        );
                    }


                    selectedGames.clear();


                    if (gameSelection.isRedLightSelected())
                    {
                        selectedGames.push_back(
                            MiniGameType::RedLightGreenLight
                        );
                    }


                    if (gameSelection.isDalgonaSelected())
                    {
                        selectedGames.push_back(
                            MiniGameType::Dalgona
                        );
                    }


                    if (gameSelection.isTugOfWarSelected())
                    {
                        selectedGames.push_back(
                            MiniGameType::TugOfWar
                        );
                    }


                    if (gameSelection.isGlassBridgeSelected())
                    {
                        selectedGames.push_back(
                            MiniGameType::GlassBridge
                        );
                    }


                    if (gameSelection.isSquidGameSelected())
                    {
                        selectedGames.push_back(
                            MiniGameType::SquidGame
                        );
                    }


                    currentGameIndex = 0;


                    // -------------------------------------------------
                    // SAFETY:
                    // Don't access selectedGames[0] if nothing
                    // was selected.
                    // -------------------------------------------------

                    if (selectedGames.empty())
                    {
                        currentState =
                            GameState::GameSelection;

                        continue;
                    }

                    // =========================================================
// SAVE CHECKPOINT FOR FIRST GAME
// =========================================================

                    saveGameCheckpoint();


                    // -------------------------------------------------
// START FIRST SELECTED GAME
// -------------------------------------------------

                    if (
                        selectedGames[0] ==
                        MiniGameType::RedLightGreenLight
                        )
                    {
                        mainMenu.stopMusic();

                        saveGameCheckpoint();

                        redLightGreenLight.reset();

                        currentState =
                            GameState::Playing;

                        startCountdown();
                    }


                    else if (
                        selectedGames[0] ==
                        MiniGameType::Dalgona
                        )
                    {
                        mainMenu.stopMusic();

                        saveGameCheckpoint();

                        dalgona.reset();

                        dalgona.setParticipants(
                            getSurvivors()
                        );

                        currentState =
                            GameState::Dalgona;

                        startCountdown();
                    }


                    else if (
                        selectedGames[0] ==
                        MiniGameType::TugOfWar
                        )
                    {
                        mainMenu.stopMusic();

                        saveGameCheckpoint();

                        tugOfWar.reset();

                        tugOfWar.setParticipants(
                            getSurvivors()
                        );

                        currentState =
                            GameState::TugOfWar;

                        startCountdown();
                    }


                    else if (
                        selectedGames[0] ==
                        MiniGameType::GlassBridge
                        )
                    {
                        mainMenu.stopMusic();

                        saveGameCheckpoint();

                        glassBridge.reset();

                        glassBridge.setParticipants(
                            getSurvivors()
                        );

                        currentState =
                            GameState::GlassBridge;

                        startCountdown();
                    }


                    else if (
                        selectedGames[0] ==
                        MiniGameType::SquidGame
                        )
                    {
                        mainMenu.stopMusic();


                        // =========================================================
                        // STANDALONE SQUID GAME
                        // PLAYER 1 + ONE RANDOM CPU
                        // =========================================================

                        std::vector<Participant*> finalists;


                        finalists.push_back(
                            &player
                        );


                        if (
                            sessionParticipants.size() > 1
                            )
                        {
                            int randomCPUIndex =
                                1 +
                                (
                                    std::rand() %
                                    (
                                        static_cast<int>(
                                            sessionParticipants.size()
                                            ) - 1
                                        )
                                    );


                            finalists.push_back(
                                sessionParticipants[
                                    randomCPUIndex
                                ]
                            );
                        }


                        saveGameCheckpoint();


                        squidGame.reset();

                        squidGame.setParticipants(
                            finalists
                        );


                        currentState =
                            GameState::SquidGame;


                        startCountdown();
                    }

    }

    else
    {
        currentState =
            newState;
    }
}


            // =================================================
            // RED LIGHT, GREEN LIGHT
            // =================================================

            else if (
                currentState ==
                GameState::Playing
                )
            {
                // -------------------------------------------------
                // IMPORTANT:
                // Don't let W/input reach RLGL during countdown.
                // -------------------------------------------------

                if (!countdownActive)
                {
                    GameState newState =
                        redLightGreenLight.handleInput(event);


                    if (
                        newState ==
                        GameState::GameSelection
                        )
                    {
                        // =====================================================
                        // PLAYER 1 WAS ELIMINATED
                        // =====================================================

                        if (!isPlayerAlive())
                        {
                            playerLives--;


                            // -------------------------------------------------
                            // LIVES REMAIN
                            // -> RESTORE THIS GAME'S CHECKPOINT
                            // -> RETRY RLGL
                            // -------------------------------------------------

                            if (playerLives > 0)
                            {
                                restoreGameCheckpoint();

                                redLightGreenLight.reset();

                                currentState =
                                    GameState::Playing;

                                startCountdown();

                                continue;
                            }


                            // -------------------------------------------------
                            // NO LIVES REMAIN
                            // -> END THE SESSION
                            // -------------------------------------------------

                            else
                            {
                                triggerGameOver();

                                continue;
                            }
                        }


                        // =====================================================
                        // PLAYER SURVIVED
                        // -> NORMAL GAME PROGRESSION
                        // =====================================================

                        currentGameIndex++;


                        if (
                            currentGameIndex >=
                            selectedGames.size()
                            )
                        {
                            currentState =
                                GameState::MainMenu;
                        }

                        else if (
                            selectedGames[currentGameIndex] ==
                            MiniGameType::RedLightGreenLight
                            )
                        {
                            redLightGreenLight.reset();

                            currentState =
                                GameState::Playing;

                            startCountdown();
                        }

                        else if (
                            selectedGames[currentGameIndex] ==
                            MiniGameType::Dalgona
                            )
                        {
                            // Save exactly who survived RLGL.
                            saveGameCheckpoint();

                            dalgona.reset();

                            dalgona.setParticipants(
                                getSurvivors()
                            );

                            currentState =
                                GameState::Dalgona;

                            startCountdown();
                        }

                        else if (
                            selectedGames[currentGameIndex] ==
                            MiniGameType::TugOfWar
                            )
                        {
                            tugOfWar.reset();
                            tugOfWar.setParticipants(getSurvivors());
                            currentState = GameState::TugOfWar;
                            startCountdown();
                        }

                        else
                        {
                            if (
                                selectedGames[currentGameIndex] ==
                                MiniGameType::GlassBridge
                                )
                            {
                                comingSoonText.setString(
                                    "GLASS STEPPING STONES"
                                );
                            }

                            else if (
                                selectedGames[currentGameIndex] ==
                                MiniGameType::SquidGame
                                )
                            {
                                comingSoonText.setString(
                                    "SQUID GAME"
                                );
                            }

                            currentState =
                                GameState::GameComingSoon;
                        }
                    }

                    else
                    {
                        currentState = newState;
                    }
                }
            }


            // =================================================
            // DALGONA
            // =================================================

            else if (
                currentState ==
                GameState::Dalgona
                )
            {
                // -------------------------------------------------
                // IMPORTANT:
                // Don't let keyboard input reach Dalgona during
                // the countdown.
                // -------------------------------------------------

                if (!countdownActive)
                {
                    GameState newState =
                        dalgona.handleInput(event);


                    if (
                        newState ==
                        GameState::GameSelection
                        )
                    {
                        // =====================================================
                        // PLAYER 1 FAILED DALGONA
                        // =====================================================

                        if (!isPlayerAlive())
                        {
                            playerLives--;


                            // -------------------------------------------------
                            // LIVES REMAIN
                            // -------------------------------------------------

                            if (playerLives > 0)
                            {
                                restoreGameCheckpoint();


                                dalgona.reset();

                                dalgona.setParticipants(
                                    getSurvivors()
                                );


                                currentState =
                                    GameState::Dalgona;


                                startCountdown();

                                continue;
                            }


                            // -------------------------------------------------
                            // NO LIVES LEFT
                            // -------------------------------------------------

                            else
                            {
                                triggerGameOver();

                                continue;
                            }
                        }


                        // =====================================================
                        // PLAYER SURVIVED
                        // =====================================================

                        currentGameIndex++;


                        if (
                            currentGameIndex >=
                            selectedGames.size()
                            )
                        {
                            currentState =
                                GameState::MainMenu;
                        }

                        else if (
                            selectedGames[currentGameIndex] ==
                            MiniGameType::RedLightGreenLight
                            )
                        {
                            redLightGreenLight.reset();

                            currentState =
                                GameState::Playing;

                            startCountdown();
                        }

                        else if (
                            selectedGames[currentGameIndex] ==
                            MiniGameType::Dalgona
                            )
                        {
                            dalgona.reset();
                            dalgona.setParticipants(getSurvivors());

                            currentState =
                                GameState::Dalgona;

                            startCountdown();
                        }

                        else if (
                            selectedGames[currentGameIndex] ==
                            MiniGameType::TugOfWar
                            )
                        {
                            saveGameCheckpoint();

                            tugOfWar.reset();
                            tugOfWar.setParticipants(getSurvivors());
                            currentState = GameState::TugOfWar;
                            startCountdown();
                        }

                        else
                        {
                            if (
                                selectedGames[currentGameIndex] ==
                                MiniGameType::GlassBridge
                                )
                            {
                                comingSoonText.setString(
                                    "GLASS STEPPING STONES"
                                );
                            }

                            else if (
                                selectedGames[currentGameIndex] ==
                                MiniGameType::SquidGame
                                )
                            {
                                comingSoonText.setString(
                                    "SQUID GAME"
                                );
                            }

                            currentState =
                                GameState::GameComingSoon;
                        }
                    }

                    else
                    {
                        currentState = newState;
                    }
                }
            }
            // =================================================
// TUG OF WAR
// =================================================

else if (
    currentState ==
    GameState::TugOfWar
    )
    {
        // -------------------------------------------------
        // Don't allow input during the global countdown.
        // -------------------------------------------------

        if (!countdownActive)
        {
            GameState newState =
                tugOfWar.handleInput(event);


            if (
                newState ==
                GameState::GameSelection
                )
            {
                // =====================================================
                // PLAYER 1 LOST TUG OF WAR
                // =====================================================

                if (!isPlayerAlive())
                {
                    playerLives--;


                    if (playerLives > 0)
                    {
                        restoreGameCheckpoint();

                        tugOfWar.reset();

                        tugOfWar.setParticipants(
                            getSurvivors()
                        );

                        currentState =
                            GameState::TugOfWar;

                        startCountdown();

                        continue;
                    }

                    else
                    {
                        triggerGameOver();

                        continue;
                    }
                }


                // =====================================================
                // PLAYER SURVIVED
                // =====================================================

                currentGameIndex++;


                // -------------------------------------------------
                // NO MORE SELECTED GAMES
                // -------------------------------------------------

                if (
                    currentGameIndex >=
                    selectedGames.size()
                    )
                {
                    currentState =
                        GameState::MainMenu;
                }


                // -------------------------------------------------
                // NEXT GAME: RLGL
                // -------------------------------------------------

                else if (
                    selectedGames[currentGameIndex] ==
                    MiniGameType::RedLightGreenLight
                    )
                {
                    saveGameCheckpoint();

                    redLightGreenLight.reset();

                    currentState =
                        GameState::Playing;

                    startCountdown();
                }


                // -------------------------------------------------
                // NEXT GAME: DALGONA
                // -------------------------------------------------

                else if (
                    selectedGames[currentGameIndex] ==
                    MiniGameType::Dalgona
                    )
                {
                    saveGameCheckpoint();

                    dalgona.reset();

                    dalgona.setParticipants(
                        getSurvivors()
                    );

                    currentState =
                        GameState::Dalgona;

                    startCountdown();
                }


                // -------------------------------------------------
                // NEXT GAME: TUG OF WAR
                // -------------------------------------------------

                else if (
                    selectedGames[currentGameIndex] ==
                    MiniGameType::TugOfWar
                    )
                {
                    saveGameCheckpoint();

                    tugOfWar.reset();

                    tugOfWar.setParticipants(
                        getSurvivors()
                    );

                    currentState =
                        GameState::TugOfWar;

                    startCountdown();
                }


                // -------------------------------------------------
                // NEXT GAME: GLASS BRIDGE
                // -------------------------------------------------

                else if (
                    selectedGames[currentGameIndex] ==
                    MiniGameType::GlassBridge
                    )
                {
                    // Save exactly who survived Tug of War.
                    saveGameCheckpoint();

                    glassBridge.reset();

                    glassBridge.setParticipants(
                        getSurvivors()
                    );

                    currentState =
                        GameState::GlassBridge;

                    startCountdown();
                }


                // -------------------------------------------------
                // NEXT GAME: SQUID GAME
                // -------------------------------------------------

                else if (
                    selectedGames[currentGameIndex] ==
                    MiniGameType::SquidGame
                    )
                {
                    comingSoonText.setString(
                        "SQUID GAME"
                    );

                    currentState =
                        GameState::GameComingSoon;
                }
            }

            else
            {
                currentState =
                    newState;
            }
        }
        }


        // =================================================
        // GLASS BRIDGE
        // =================================================

else if (
    currentState ==
    GameState::GlassBridge
    )
    {
        if (!countdownActive)
        {
            GameState newState =
                glassBridge.handleInput(event);


            if (
                newState ==
                GameState::GameSelection
                )
            {
                // =====================================================
                // PLAYER 1 FAILED GLASS BRIDGE
                // =====================================================

                if (!isPlayerAlive())
                {
                    playerLives--;


                    if (playerLives > 0)
                    {
                        restoreGameCheckpoint();

                        glassBridge.reset();

                        glassBridge.setParticipants(
                            getSurvivors()
                        );

                        currentState =
                            GameState::GlassBridge;

                        startCountdown();

                        continue;
                    }

                    else
                    {
                        triggerGameOver();

                        continue;
                    }
                }


                // =====================================================
                // PLAYER SURVIVED GLASS BRIDGE
                // =====================================================

                currentGameIndex++;


                // -------------------------------------------------
                // NO MORE SELECTED GAMES
                // -------------------------------------------------

                if (
                    currentGameIndex >=
                    selectedGames.size()
                    )
                {
                    currentState =
                        GameState::MainMenu;
                }


                // -------------------------------------------------
// NEXT GAME IS SQUID GAME
// -------------------------------------------------

                else if (
                    selectedGames[currentGameIndex] ==
                    MiniGameType::SquidGame
                    )
                {
                    std::vector<Participant*> survivors =
                        getSurvivors();


                    // ---------------------------------------------
                    // MORE THAN TWO SURVIVORS
                    // -> INTERMISSION FIRST
                    // ---------------------------------------------

                    if (survivors.size() > 2)
                    {
                        intermission.reset();

                        intermission.setParticipants(
                            survivors
                        );

                        currentState =
                            GameState::Intermission;

                        startCountdown();
                    }


                    // ---------------------------------------------
                    // EXACTLY TWO SURVIVORS
                    // -> START SQUID GAME
                    // ---------------------------------------------

                    else
                    {
                        saveGameCheckpoint();

                        squidGame.reset();

                        squidGame.setParticipants(
                            survivors
                        );

                        currentState =
                            GameState::SquidGame;

                        startCountdown();
                    }
                }


                // -------------------------------------------------
                // SAFETY FALLBACK
                // -------------------------------------------------

                else
                {
                    currentState =
                        GameState::MainMenu;
                }
            }

            else
            {
                currentState =
                    newState;
            }
        }
        }


        // =================================================
        // INTERMISSION
        // =================================================

else if (
    currentState ==
    GameState::Intermission
    )
    {
        if (!countdownActive)
        {
            GameState newState =
                intermission.handleInput(event);


            if (
                newState ==
                GameState::GameSelection
                )
            {
                std::vector<Participant*> survivors =
                    getSurvivors();

                saveGameCheckpoint();

                squidGame.reset();

                squidGame.setParticipants(
                    survivors
                );

                currentState =
                    GameState::SquidGame;

                startCountdown();
            }

            else
            {
                currentState =
                    newState;
            }
        }
        }

        // =================================================
 // SQUID GAME
 // =================================================

else if (
    currentState ==
    GameState::SquidGame
    )
    {
        if (!countdownActive)
        {
            squidGame.handleInput(
                event
            );


            // =====================================================
            // RESULT BUTTON CLICKED
            // =====================================================

            if (
                squidGame
                .consumeResultButtonClick()
                )
            {
                // =================================================
                // PLAYER LOST
                // =================================================

                if (
                    squidGame
                    .didHumanLose()
                    )
                {
                    // Save the SAME two finalists before reset.
                    std::vector<Participant*> retryFinalists =
                        squidGame.getFinalists();


                    playerLives--;


                    // ---------------------------------------------
                    // NO LIVES LEFT
                    // ---------------------------------------------

                    if (
                        playerLives <= 0
                        )
                    {
                        triggerGameOver();

                        continue;
                    }


                    // ---------------------------------------------
                    // LIVES REMAIN
                    // -> RESTORE CHECKPOINT
                    // -> RETRY SQUID GAME
                    // ---------------------------------------------

                    restoreGameCheckpoint();


                    squidGame.reset();


                    squidGame.setParticipants(
                        retryFinalists
                    );


                    currentState =
                        GameState::SquidGame;


                    startCountdown();

                    continue;
                }


                // =================================================
                // PLAYER WON
                // =================================================

                else if (
                    squidGame
                    .didHumanWin()
                    )
                {
                    // Placeholder for the future ending.
                    //
                    // Leave the YOU WON screen here for now.
                }
            }
        }
        }
            // =================================================
            // GAME COMING SOON
            // =================================================

            else if (
                currentState ==
                GameState::GameComingSoon
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
                            continueButton
                            .getGlobalBounds()
                            .contains(
                                mouseX,
                                mouseY
                            )
                            )
                        {
                            currentGameIndex++;


                            if (
                                currentGameIndex >=
                                selectedGames.size()
                                )
                            {
                                currentState =
                                    GameState::MainMenu;
                            }

                            else if (
                                selectedGames[currentGameIndex] ==
                                MiniGameType::RedLightGreenLight
                                )
                            {
                                redLightGreenLight.reset();

                                currentState =
                                    GameState::Playing;

                                startCountdown();
                            }

                            else if (
                                selectedGames[currentGameIndex] ==
                                MiniGameType::Dalgona
                                )
                            {
                                dalgona.reset();
                                dalgona.setParticipants(getSurvivors());

                                currentState =
                                    GameState::Dalgona;

                                startCountdown();
                            }

                            else if (
                                selectedGames[currentGameIndex] ==
                                MiniGameType::TugOfWar
                                )
                            {
                                tugOfWar.reset();
                                tugOfWar.setParticipants(getSurvivors());
                                currentState = GameState::TugOfWar;
                                startCountdown();
                            }

                            else
                            {
                                if (
                                    selectedGames[currentGameIndex] ==
                                    MiniGameType::GlassBridge
                                    )
                                {
                                    comingSoonText.setString(
                                        "GLASS STEPPING STONES"
                                    );
                                }

                                else if (
                                    selectedGames[currentGameIndex] ==
                                    MiniGameType::SquidGame
                                    )
                                {
                                    comingSoonText.setString(
                                        "SQUID GAME"
                                    );
                                }

                                currentState =
                                    GameState::GameComingSoon;
                            }
                        }
                    }
                }
            }
        }


        // =====================================================
        // DRAWING / GAME UPDATE
        // =====================================================

        if (
            currentState ==
            GameState::MainMenu
            )
        {
            // =========================================================
            // ENSURE MENU MUSIC IS PLAYING
            // =========================================================

            mainMenu.playMusic();


            currentState =
                mainMenu.handleInput(window);


            window.clear();


            mainMenu.draw(
                window
            );
        }

        else if (
    currentState ==
    GameState::GameSelection
    )
{
    window.clear();

    gameSelection.draw(window);

    window.draw(botCountText);
}


        else if (
            currentState ==
            GameState::Playing
            )
        {
            if (
                !paused &&
                !countdownActive
                )
            {
                redLightGreenLight.update();
            }

            window.clear();

            redLightGreenLight.draw(window);
        }


        else if (
            currentState ==
            GameState::Dalgona
            )
        {
            if (
                !paused &&
                !countdownActive
                )
            {
                dalgona.update();
            }

            window.clear();

            dalgona.draw(window);
        }

        else if (
            currentState ==
            GameState::TugOfWar
            )
        {
            if (
                !paused &&
                !countdownActive
                )
            {
                tugOfWar.update();
            }

            window.clear();

            tugOfWar.draw(window);
        }

        else if (
            currentState ==
            GameState::GlassBridge
            )
        {
            if (
                !paused &&
                !countdownActive
                )
            {
                glassBridge.update();
            }

            window.clear();

            glassBridge.draw(window);
        }

        else if (
            currentState ==
            GameState::Intermission
            )
        {
            if (
                !paused &&
                !countdownActive
                )
            {
                intermission.update();
            }

            window.clear();

            intermission.draw(window);
        }

        else if (
            currentState ==
            GameState::SquidGame
            )
            {
                if (
                    !paused &&
                    !countdownActive
                    )
                {
                    squidGame.update();
                }

                window.clear();

                squidGame.draw(
                    window
                );
                }



        else if (
            currentState ==
            GameState::GameComingSoon
            )
        {
            window.clear();

            window.draw(comingSoonText);
            window.draw(continueButton);
        }


        if (
            currentState == GameState::Playing ||
            currentState == GameState::Dalgona ||
            currentState == GameState::TugOfWar ||
            currentState == GameState::GlassBridge ||
            currentState == GameState::Intermission 
            ||
            currentState == GameState::SquidGame
            )
        {
            drawLives();
        }

        else if (
            currentState ==
            GameState::GameOver
            )
        {
            window.clear();

            window.draw(gameOverBox);
            window.draw(gameOverText);
            window.draw(returnToMenuButtonBox);
            window.draw(returnToMenuButton);
        }
        // =====================================================
        // PAUSE OVERLAY
        // =====================================================

        if (paused)
        {
            window.draw(pauseOverlay);

            window.draw(resumeButtonBox);
            window.draw(resumeButton);

            window.draw(mainMenuButtonBox);
            window.draw(mainMenuButton);
        }


        // =====================================================
        // COUNTDOWN OVERLAY
        // =====================================================

        if (countdownActive)
        {
            window.draw(countdownBox);
            window.draw(countdownText);
        }


        window.display();
    }

}
std::vector<Participant*> Game::getSurvivors()
{
    std::vector<Participant*> survivors;


    for (
        Participant* participant :
        sessionParticipants
        )
    {
        if (participant->isAlive())
        {
            survivors.push_back(
                participant
            );
        }
    }


    return survivors;
}

// =============================================================
// SAVE GAME CHECKPOINT
// =============================================================

void Game::saveGameCheckpoint()
{
    gameCheckpoint.clear();


    for (
        Participant* participant :
        sessionParticipants
        )
    {
        if (participant->isAlive())
        {
            gameCheckpoint.push_back(
                participant
            );
        }
    }
}


// =============================================================
// RESTORE GAME CHECKPOINT
// =============================================================

void Game::restoreGameCheckpoint()
{
    for (
        Participant* participant :
        sessionParticipants
        )
    {
        participant->resetForNextGame();


        bool shouldBeAlive = false;


        for (
            Participant* checkpointParticipant :
            gameCheckpoint
            )
        {
            if (
                participant ==
                checkpointParticipant
                )
            {
                shouldBeAlive = true;
                break;
            }
        }


        if (shouldBeAlive)
        {
            participant->revive();
        }

        else
        {
            participant->eliminate();
        }
    }
}


// =============================================================
// IS PLAYER 1 ALIVE?
// =============================================================

bool Game::isPlayerAlive()
{
    return player.isAlive();
}