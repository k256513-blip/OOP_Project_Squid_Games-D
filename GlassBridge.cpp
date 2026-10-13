#include "GlassBridge.h"

#include <cstdlib>
#include <string>


// =============================================================
// CONSTRUCTOR
// =============================================================

GlassBridge::GlassBridge()
    : bridge{}
{
    gameStarted = false;
    gameFinished = false;

    waitingForHumanInput = false;

    turnIndex = 0;
    currentParticipant = nullptr;

    nextMoveDelay = 1.0f;


    // ---------------------------------------------------------
    // FONT
    // ---------------------------------------------------------

    font.loadFromFile("arial.ttf");


    // ---------------------------------------------------------
    // TITLE
    // ---------------------------------------------------------

    title.setFont(font);
    title.setString("GLASS STEPPING STONES");
    title.setCharacterSize(34);
    title.setFillColor(sf::Color::White);
    title.setPosition(420, 30);


    // ---------------------------------------------------------
    // TURN TEXT
    // ---------------------------------------------------------

    turnText.setFont(font);
    turnText.setCharacterSize(22);
    turnText.setFillColor(sf::Color::White);
    turnText.setPosition(40, 90);
    turnText.setString("Turn to move:");


    // ---------------------------------------------------------
    // TIMER TEXT
    // ---------------------------------------------------------

    timerText.setFont(font);
    timerText.setCharacterSize(22);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(520, 90);
    timerText.setString("Timer: --");


    // ---------------------------------------------------------
    // INSTRUCTION TEXT
    // ---------------------------------------------------------

    instructionText.setFont(font);
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(730, 90);

    instructionText.setString(
        "Press A = Left     D = Right"
    );


    // ---------------------------------------------------------
    // STATUS TEXT
    // ---------------------------------------------------------

    statusText.setFont(font);
    statusText.setCharacterSize(22);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(40, 650);
    statusText.setString("");

    // ---------------------------------------------------------
// RESULT TITLE
// ---------------------------------------------------------

    resultTitle.setFont(font);
    resultTitle.setString("GLASS BRIDGE COMPLETE");
    resultTitle.setCharacterSize(42);
    resultTitle.setFillColor(sf::Color::White);
    resultTitle.setPosition(370, 170);


    // ---------------------------------------------------------
    // SURVIVOR TEXT
    // ---------------------------------------------------------

    survivorText.setFont(font);
    survivorText.setCharacterSize(22);
    survivorText.setFillColor(sf::Color::White);
    survivorText.setPosition(470, 250);


    // ---------------------------------------------------------
    // CONTINUE BUTTON
    // ---------------------------------------------------------

    continueButtonBox.setSize(
        sf::Vector2f(220, 60)
    );

    continueButtonBox.setPosition(
        530, 560
    );

    continueButtonBox.setFillColor(
        sf::Color(60, 60, 60)
    );

    continueButtonBox.setOutlineColor(
        sf::Color::White
    );

    continueButtonBox.setOutlineThickness(
        2.0f
    );


    continueButton.setFont(font);
    continueButton.setString("Continue");
    continueButton.setCharacterSize(28);
    continueButton.setFillColor(
        sf::Color::White
    );

    continueButton.setPosition(
        585, 573
    );
}



// =============================================================
// SET PARTICIPANTS
// =============================================================

void GlassBridge::setParticipants(
    const std::vector<Participant*>& survivors
)
{
    participants = survivors;

    activeParticipants.clear();
    passedParticipants.clear();
    participantData.clear();

    for (Participant* participant : participants)
    {
        if (participant->isAlive())
        {
            activeParticipants.push_back(participant);

            ParticipantBridgeData data;

            data.participant = participant;
            data.row = 0;
            data.onLeft = true;
            data.finished = false;

            participantData.push_back(data);
        }
    }
}


// =============================================================
// GENERATE BRIDGE
// =============================================================

void GlassBridge::generateBridge()
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        bridge[i].safeIsLeft =
            (std::rand() % 2 == 0);

        bridge[i].leftBroken = false;
        bridge[i].rightBroken = false;
    }
}


// =============================================================
// CREATE TURN ORDER
// =============================================================

void GlassBridge::createTurnOrder()
{
    turnOrder.clear();

    for (Participant* participant : activeParticipants)
    {
        if (
            participant->isAlive()
            )
        {
            ParticipantBridgeData* data =
                getBridgeData(participant);

            if (
                data != nullptr &&
                !data->finished
                )
            {
                turnOrder.push_back(participant);
            }
        }
    }


    // ---------------------------------------------------------
    // SIMPLE FISHER-YATES SHUFFLE
    // ---------------------------------------------------------

    for (
        int i =
        static_cast<int>(turnOrder.size()) - 1;

        i > 0;

        i--
        )
    {
        int randomIndex =
            std::rand() % (i + 1);

        Participant* temp =
            turnOrder[i];

        turnOrder[i] =
            turnOrder[randomIndex];

        turnOrder[randomIndex] =
            temp;
    }


    turnIndex = 0;
}


// =============================================================
// SELECT NEXT PARTICIPANT
// =============================================================

void GlassBridge::selectNextParticipant()
{
    // =========================================================
    // KEEP LOOKING UNTIL WE FIND A VALID PARTICIPANT
    // =========================================================

    while (true)
    {
        // -----------------------------------------------------
        // NEED A NEW SHUFFLE BAG
        // -----------------------------------------------------

        if (
            turnOrder.empty() ||
            turnIndex >=
            static_cast<int>(turnOrder.size())
            )
        {
            createTurnOrder();
        }


        // -----------------------------------------------------
        // NOBODY LEFT TO MOVE
        // -----------------------------------------------------

        if (turnOrder.empty())
        {
            currentParticipant = nullptr;

            checkMinimumSurvivors();

            return;
        }


        // -----------------------------------------------------
        // TAKE NEXT NAME
        // -----------------------------------------------------

        Participant* candidate =
            turnOrder[turnIndex];

        turnIndex++;


        ParticipantBridgeData* data =
            getBridgeData(candidate);


        // -----------------------------------------------------
        // SKIP STALE ENTRIES
        // -----------------------------------------------------

        if (
            data == nullptr ||
            !candidate->isAlive() ||
            data->finished ||
            data->row >= ROW_COUNT
            )
        {
            continue;
        }


        // -----------------------------------------------------
        // VALID PARTICIPANT FOUND
        // -----------------------------------------------------

        currentParticipant =
            candidate;

        break;
    }


    waitingForHumanInput =
        !currentParticipant->isCPU();


    turnText.setString(
        "Turn to move: " +
        currentParticipant->getName()
    );


    if (waitingForHumanInput)
    {
        timerText.setString(
            "Timer: 03"
        );

        humanChoiceClock.restart();
    }

    else
    {
        timerText.setString(
            "Timer: --"
        );
    }


    moveClock.restart();
}


// =============================================================
// GET PARTICIPANT BRIDGE DATA
// =============================================================

GlassBridge::ParticipantBridgeData*
GlassBridge::getBridgeData(
    Participant* participant
)
{
    for (
        ParticipantBridgeData& data :
        participantData
        )
    {
        if (data.participant == participant)
        {
            return &data;
        }
    }

    return nullptr;
}

GameState GlassBridge::handleInput(
    sf::Event& event
)
{
    // =========================================================
    // GAME FINISHED
    // =========================================================

    if (gameFinished)
    {
        if (
            event.type ==
            sf::Event::MouseButtonPressed &&
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
                return GameState::GameSelection;
            }
        }


        return GameState::GlassBridge;
    }


    // =========================================================
    // NORMAL GAME INPUT
    // =========================================================

    if (!gameStarted)
    {
        return GameState::GlassBridge;
    }


    if (
        waitingForHumanInput &&
        currentParticipant != nullptr &&
        event.type ==
        sf::Event::KeyPressed
        )
    {
        if (
            event.key.code ==
            sf::Keyboard::A
            )
        {
            resolveHumanChoice(true);
        }

        else if (
            event.key.code ==
            sf::Keyboard::D
            )
        {
            resolveHumanChoice(false);
        }
    }


    return GameState::GlassBridge;
}


// =============================================================
// UPDATE
// =============================================================

void GlassBridge::update()
{
    if (!gameStarted)
        return;

    if (gameFinished)
        return;


    // ---------------------------------------------------------
    // WAITING TO SELECT NEXT PARTICIPANT
    // ---------------------------------------------------------

    if (currentParticipant == nullptr)
    {
        if (
            moveClock.getElapsedTime().asSeconds()
            >= nextMoveDelay
            )
        {
            selectNextParticipant();
        }

        return;
    }


    // ---------------------------------------------------------
    // HUMAN TURN
    // ---------------------------------------------------------

    if (waitingForHumanInput)
    {
        float remainingTime =
            3.0f -
            humanChoiceClock
            .getElapsedTime()
            .asSeconds();


        if (remainingTime < 0.0f)
            remainingTime = 0.0f;


        int displayTime =
            static_cast<int>(
                remainingTime + 0.99f
                );


        timerText.setString(
            "Timer: 0" +
            std::to_string(displayTime)
        );


        // -----------------------------------------------------
        // HUMAN FAILED TO CHOOSE
        // -----------------------------------------------------

        if (remainingTime <= 0.0f)
        {
            statusText.setString(
                currentParticipant->getName() +
                " ran out of time!"
            );

            eliminateParticipant(
                currentParticipant
            );

            currentParticipant = nullptr;
            waitingForHumanInput = false;

            nextMoveDelay =
                generateMoveDelay();

            moveClock.restart();
            checkMinimumSurvivors();
        }
    }


    // ---------------------------------------------------------
    // CPU TURN
    // ---------------------------------------------------------

    else
    {
        if (
            moveClock
            .getElapsedTime()
            .asSeconds()
            >= nextMoveDelay
            )
        {
            resolveCPUChoice();
        }
    }
}

// =============================================================
// RESOLVE HUMAN CHOICE
// =============================================================

void GlassBridge::resolveHumanChoice(
    bool chooseLeft
)
{
    if (currentParticipant == nullptr)
        return;


    ParticipantBridgeData* data =
        getBridgeData(currentParticipant);


    if (data == nullptr)
        return;


    int targetRow =
        data->row;


    if (
        targetRow < 0 ||
        targetRow >= ROW_COUNT
        )
    {
        return;
    }


    // ---------------------------------------------------------
    // DON'T ALLOW JUMPING ONTO BROKEN GLASS
    // ---------------------------------------------------------

    if (
        chooseLeft &&
        bridge[targetRow].leftBroken
        )
    {
        statusText.setString(
            "LEFT panel is broken!"
        );

        return;
    }


    if (
        !chooseLeft &&
        bridge[targetRow].rightBroken
        )
    {
        statusText.setString(
            "RIGHT panel is broken!"
        );

        return;
    }


    resolveChoice(
        currentParticipant,
        chooseLeft
    );
}


// =============================================================
// RESOLVE CPU CHOICE
// =============================================================

void GlassBridge::resolveCPUChoice()
{
    if (currentParticipant == nullptr)
        return;


    ParticipantBridgeData* data =
        getBridgeData(currentParticipant);


    if (data == nullptr)
        return;


    int targetRow =
        data->row;

    if (
        targetRow < 0 ||
        targetRow >= ROW_COUNT
        )
    {
        currentParticipant = nullptr;
        waitingForHumanInput = false;

        nextMoveDelay =
            generateMoveDelay();

        moveClock.restart();

        return;
    }


    bool chooseLeft;


    // ---------------------------------------------------------
    // IF ONE PANEL IS BROKEN, CPU ALWAYS CHOOSES THE OTHER
    // ---------------------------------------------------------

    if (
        bridge[targetRow].leftBroken
        )
    {
        chooseLeft = false;
    }

    else if (
        bridge[targetRow].rightBroken
        )
    {
        chooseLeft = true;
    }

    else
    {
        chooseLeft =
            cpuChoosesLeft(
                currentParticipant,
                targetRow
            );
    }


    resolveChoice(
        currentParticipant,
        chooseLeft
    );
}


// =============================================================
// RESOLVE CHOICE
// =============================================================

void GlassBridge::resolveChoice(
    Participant* participant,
    bool chooseLeft
)
{
    ParticipantBridgeData* data =
        getBridgeData(participant);


    if (data == nullptr)
        return;


    int targetRow =
        data->row;


    bool correctChoice =
        (
            chooseLeft ==
            bridge[targetRow].safeIsLeft
            );


    // =========================================================
    // SAFE PANEL
    // =========================================================

    if (correctChoice)
    {
        recordSuccessfulJump(
            participant,
            targetRow,
            chooseLeft
        );

        data->row++;

        data->onLeft =
            chooseLeft;


        statusText.setString(
            participant->getName() +
            " chose correctly!"
        );


        // -----------------------------------------------------
        // REACHED FINISH
        // -----------------------------------------------------

        if (data->row >= ROW_COUNT)
        {
            passParticipant(
                participant
            );
        }
    }


    // =========================================================
    // WRONG PANEL
    // =========================================================

    else
    {
        if (chooseLeft)
        {
            bridge[targetRow]
                .leftBroken = true;
        }

        else
        {
            bridge[targetRow]
                .rightBroken = true;
        }


        statusText.setString(
            participant->getName() +
            " fell!"
        );


        eliminateParticipant(
            participant
        );
    }


    // ---------------------------------------------------------
    // END CURRENT TURN
    // ---------------------------------------------------------

    currentParticipant = nullptr;

    waitingForHumanInput = false;

    timerText.setString(
        "Timer: --"
    );


    nextMoveDelay =
        generateMoveDelay();

    moveClock.restart();


    checkMinimumSurvivors();
}

// =============================================================
// CPU CHOOSES LEFT
// =============================================================

bool GlassBridge::cpuChoosesLeft(
    Participant* participant,
    int row
)
{
    // ---------------------------------------------------------
    // BROKEN PANEL = AUTOMATIC CHOICE
    // ---------------------------------------------------------

    if (bridge[row].leftBroken)
        return false;

    if (bridge[row].rightBroken)
        return true;


    // ---------------------------------------------------------
    // SEARCH FOR A MEMORY OF THIS ROW
    // ---------------------------------------------------------

    MemoryData* bestMemory = nullptr;


    for (MemoryData& memory : cpuMemory)
    {
        if (
            memory.participant == participant &&
            memory.row == row
            )
        {
            bestMemory = &memory;
        }
    }


    // ---------------------------------------------------------
    // NO MEMORY = 50 / 50
    // ---------------------------------------------------------

    if (bestMemory == nullptr)
    {
        return
            (std::rand() % 2 == 0);
    }


    // ---------------------------------------------------------
    // DETERMINE MEMORY ACCURACY
    // ---------------------------------------------------------

    int successChance;


    if (bestMemory->observedDistance <= 1)
    {
        successChance = 95;
    }

    else if (bestMemory->observedDistance == 2)
    {
        successChance = 85;
    }

    else if (bestMemory->observedDistance == 3)
    {
        successChance = 80;
    }

    else
    {
        successChance = 60;
    }


    // ---------------------------------------------------------
    // DOES THE CPU REMEMBER CORRECTLY?
    // ---------------------------------------------------------

    bool remembersCorrectly =
        (std::rand() % 100) <
        successChance;


    if (remembersCorrectly)
    {
        return
            bestMemory->safeWasLeft;
    }

    else
    {
        return
            !bestMemory->safeWasLeft;
    }
}

// =============================================================
// RECORD SUCCESSFUL JUMP
// =============================================================

void GlassBridge::recordSuccessfulJump(
    Participant* participant,
    int row,
    bool safeWasLeft
)
{
    ParticipantBridgeData* jumperData =
        getBridgeData(participant);

    if (jumperData == nullptr)
        return;


    for (
        ParticipantBridgeData& observerData :
        participantData
        )
    {
        Participant* observer =
            observerData.participant;


        // -----------------------------------------------------
        // ONLY CPUs NEED STORED MEMORY
        // -----------------------------------------------------

        if (!observer->isCPU())
            continue;


        // -----------------------------------------------------
        // DEAD / FINISHED PLAYERS DON'T NEED NEW MEMORIES
        // -----------------------------------------------------

        if (
            !observer->isAlive() ||
            observerData.finished
            )
        {
            continue;
        }


        // -----------------------------------------------------
        // THE JUMPER DOESN'T NEED TO OBSERVE THEMSELVES
        // -----------------------------------------------------

        if (observer == participant)
            continue;


        // -----------------------------------------------------
        // ONLY PLAYERS BEHIND THE JUMP CAN OBSERVE IT
        // -----------------------------------------------------

        if (observerData.row > row)
            continue;


        int distance =
            row - observerData.row + 1;


        MemoryData memory;

        memory.participant =
            observer;

        memory.row =
            row;

        memory.safeWasLeft =
            safeWasLeft;

        memory.observedDistance =
            distance;


        cpuMemory.push_back(
            memory
        );
    }
}



// =============================================================
// ELIMINATE PARTICIPANT
// =============================================================

void GlassBridge::eliminateParticipant(
    Participant* participant
)
{
    if (participant == nullptr)
        return;


    participant->eliminate();

    // =========================================================
// HUMAN PLAYER FELL
// END THIS ATTEMPT IMMEDIATELY
// =========================================================

    if (!participant->isCPU())
    {
        gameFinished = true;

        currentParticipant = nullptr;
        waitingForHumanInput = false;

        statusText.setString(
            "PLAYER 1 ELIMINATED"
        );

        continueButton.setString(
            "Retry"
        );

        return;
    }


    ParticipantBridgeData* data =
        getBridgeData(participant);


    if (data != nullptr)
    {
        data->finished = true;
    }
}


// =============================================================
// PASS PARTICIPANT
// =============================================================

void GlassBridge::passParticipant(
    Participant* participant
)
{
    if (participant == nullptr)
        return;


    ParticipantBridgeData* data =
        getBridgeData(participant);


    if (data != nullptr)
    {
        data->finished = true;
    }


    passedParticipants.push_back(
        participant
    );


    statusText.setString(
        participant->getName() +
        " PASSED!"
    );
}


// =============================================================
// TOTAL SURVIVORS
// =============================================================

int GlassBridge::getTotalSurvivors()
{
    int survivorCount = 0;


    for (
        ParticipantBridgeData& data :
        participantData
        )
    {
        if (
            data.participant->isAlive()
            )
        {
            survivorCount++;
        }
    }


    return survivorCount;
}


// =============================================================
// CHECK GAME END
// =============================================================

void GlassBridge::checkMinimumSurvivors()
{
    // ---------------------------------------------------------
    // SAFETY RULE:
    // NEVER REDUCE THE TOURNAMENT BELOW TWO SURVIVORS
    // ---------------------------------------------------------

    if (getTotalSurvivors() <= 2)
    {
        gameFinished = true;

        statusText.setString(
            "GLASS BRIDGE COMPLETE - "
            "2 PARTICIPANTS REMAIN"
        );

        currentParticipant = nullptr;
        waitingForHumanInput = false;

        return;
    }


    // ---------------------------------------------------------
    // NORMAL END:
    // EVERY LIVING PARTICIPANT HAS CROSSED
    // ---------------------------------------------------------

    if (allRemainingParticipantsFinished())
    {
        gameFinished = true;

        statusText.setString(
            "GLASS BRIDGE COMPLETE"
        );

        currentParticipant = nullptr;
        waitingForHumanInput = false;
    }
}


// =============================================================
// DRAW
// =============================================================

void GlassBridge::draw(
    sf::RenderWindow& window
)
{
    window.draw(title);
    window.draw(turnText);
    window.draw(timerText);
    window.draw(instructionText);
    window.draw(statusText);

    // =========================================================
// GAME COMPLETE SCREEN
// =========================================================

    if (gameFinished)
    {
        // =====================================================
        // PLAYER 1 WAS ELIMINATED
        // RETRY SCREEN ONLY
        // =====================================================

        bool playerAlive = false;

        for (
            ParticipantBridgeData& data :
            participantData
            )
        {
            if (!data.participant->isCPU())
            {
                playerAlive =
                    data.participant->isAlive();

                break;
            }
        }


        if (!playerAlive)
        {
            window.draw(
                continueButtonBox
            );

            window.draw(
                continueButton
            );

            return;
        }


        // =====================================================
        // PLAYER 1 SURVIVED
        // =====================================================

        window.draw(
            resultTitle
        );


        // -----------------------------------------------------
        // ONLY SHOW SURVIVOR LIST IF EXACTLY 2 REMAIN
        // -----------------------------------------------------

        if (getTotalSurvivors() == 2)
        {
            std::string survivors =
                "SURVIVORS\n\n";


            for (
                ParticipantBridgeData& data :
                participantData
                )
            {
                if (
                    data.participant->isAlive()
                    )
                {
                    survivors +=
                        data.participant->getName();

                    survivors += "\n";
                }
            }


            survivorText.setString(
                survivors
            );

            window.draw(
                survivorText
            );
        }


        window.draw(
            continueButtonBox
        );

        window.draw(
            continueButton
        );

        return;
    }


    // =========================================================
    // BRIDGE
    // =========================================================

    const float startX = 300.0f;
    const float startY = 250.0f;

    const float panelWidth = 75.0f;
    const float panelHeight = 55.0f;

    const float rowSpacing = 85.0f;

    const float leftY = 250.0f;
    const float rightY = 390.0f;


    for (int i = 0; i < ROW_COUNT; i++)
    {
        float x =
            startX +
            (i * rowSpacing);


        // -----------------------------------------------------
        // LEFT PANEL
        // -----------------------------------------------------

        sf::RectangleShape leftPanel;

        leftPanel.setSize(
            sf::Vector2f(
                panelWidth,
                panelHeight
            )
        );

        leftPanel.setPosition(
            x,
            leftY
        );

        leftPanel.setFillColor(
            sf::Color(120, 180, 200)
        );

        leftPanel.setOutlineColor(
            sf::Color::White
        );

        leftPanel.setOutlineThickness(
            2.0f
        );


        // -----------------------------------------------------
        // RIGHT PANEL
        // -----------------------------------------------------

        sf::RectangleShape rightPanel;

        rightPanel.setSize(
            sf::Vector2f(
                panelWidth,
                panelHeight
            )
        );

        rightPanel.setPosition(
            x,
            rightY
        );

        rightPanel.setFillColor(
            sf::Color(120, 180, 200)
        );

        rightPanel.setOutlineColor(
            sf::Color::White
        );

        rightPanel.setOutlineThickness(
            2.0f
        );


        window.draw(leftPanel);
        window.draw(rightPanel);

        // -----------------------------------------------------
// BROKEN LEFT PANEL
// -----------------------------------------------------

        if (bridge[i].leftBroken)
        {
            sf::Text brokenText;

            brokenText.setFont(font);
            brokenText.setString("X");
            brokenText.setCharacterSize(38);
            brokenText.setFillColor(
                sf::Color::Red
            );

            brokenText.setPosition(
                x + 25.0f,
                leftY + 3.0f
            );

            window.draw(brokenText);
        }


        // -----------------------------------------------------
        // BROKEN RIGHT PANEL
        // -----------------------------------------------------

        if (bridge[i].rightBroken)
        {
            sf::Text brokenText;

            brokenText.setFont(font);
            brokenText.setString("X");
            brokenText.setCharacterSize(38);
            brokenText.setFillColor(
                sf::Color::Red
            );

            brokenText.setPosition(
                x + 25.0f,
                rightY + 3.0f
            );

            window.draw(brokenText);
        }
    }


    // =========================================================
    // STARTING PARTICIPANTS
    // =========================================================

    float participantX = 80.0f;
    float participantY = 230.0f;

    int participantCount = 0;


    for (
        ParticipantBridgeData& data :
        participantData
        )
    {
        if (
            data.row == 0 &&
            !data.finished &&
            data.participant->isAlive()
            )
        {
            sf::RectangleShape participantCube;

            participantCube.setSize(
                sf::Vector2f(25, 25)
            );

            participantCube.setFillColor(
                data.participant->getColor()
            );

            participantCube.setOutlineColor(
                sf::Color::Black
            );

            participantCube.setOutlineThickness(
                1.0f
            );


            int column =
                participantCount % 5;

            int row =
                participantCount / 5;


            participantCube.setPosition(
                participantX +
                column * 35.0f,

                participantY +
                row * 45.0f
            );


            window.draw(participantCube);

            participantCount++;
        }
    }

    // =========================================================
// PARTICIPANTS ON BRIDGE
// =========================================================

    for (
        ParticipantBridgeData& data :
        participantData
        )
    {
        if (
            data.row > 0 &&
            data.row <= ROW_COUNT &&
            !data.finished &&
            data.participant->isAlive()
            )
        {
            sf::RectangleShape participantCube;

            participantCube.setSize(
                sf::Vector2f(25, 25)
            );

            participantCube.setFillColor(
                data.participant->getColor()
            );

            participantCube.setOutlineColor(
                sf::Color::Black
            );

            participantCube.setOutlineThickness(
                1.0f
            );


            float x =
                startX +
                ((data.row - 1) * rowSpacing) +
                25.0f;


            float y;

            if (data.onLeft)
            {
                y =
                    leftY +
                    15.0f;
            }

            else
            {
                y =
                    rightY +
                    15.0f;
            }


            participantCube.setPosition(
                x,
                y
            );


            window.draw(
                participantCube
            );
        }
    }

    // =========================================================
// PLAYER STATUS BOX
// =========================================================

    sf::RectangleShape statusBox;

    statusBox.setSize(
        sf::Vector2f(260.0f, 360.0f)
    );

    statusBox.setPosition(
        20.0f,
        170.0f
    );

    statusBox.setFillColor(
        sf::Color(30, 30, 30, 220)
    );

    statusBox.setOutlineColor(
        sf::Color::White
    );

    statusBox.setOutlineThickness(
        2.0f
    );

    window.draw(statusBox);


    // ---------------------------------------------------------
    // STATUS TITLE
    // ---------------------------------------------------------

    sf::Text statusTitle;

    statusTitle.setFont(font);
    statusTitle.setString("PARTICIPANTS");
    statusTitle.setCharacterSize(20);
    statusTitle.setFillColor(
        sf::Color::White
    );

    statusTitle.setPosition(
        40.0f,
        185.0f
    );

    window.draw(statusTitle);


    // ---------------------------------------------------------
    // PLAYER STATUS LIST
    // ---------------------------------------------------------

    float statusY = 220.0f;

    for (
        ParticipantBridgeData& data :
        participantData
        )
    {
        sf::Text playerStatus;

        playerStatus.setFont(font);
        playerStatus.setCharacterSize(16);

        std::string stateText;


        if (!data.participant->isAlive())
        {
            stateText = "ELIMINATED";

            playerStatus.setFillColor(
                sf::Color::Red
            );
        }

        else if (data.finished)
        {
            stateText = "PASSED";

            playerStatus.setFillColor(
                sf::Color::Green
            );
        }

        else
        {
            stateText = "ALIVE";

            playerStatus.setFillColor(
                sf::Color::White
            );
        }


        playerStatus.setString(
            data.participant->getName() +
            ": " +
            stateText
        );

        playerStatus.setPosition(
            40.0f,
            statusY
        );

        window.draw(playerStatus);


        statusY += 20.0f;
    }


    // =========================================================
    // FINISH LINE
    // =========================================================

    sf::RectangleShape finishLine;

    finishLine.setSize(
        sf::Vector2f(
            5.0f,
            260.0f
        )
    );

    finishLine.setPosition(
        1170.0f,
        220.0f
    );

    finishLine.setFillColor(
        sf::Color::White
    );

    window.draw(finishLine);


    sf::Text finishText;

    finishText.setFont(font);
    finishText.setString("FINISH");
    finishText.setCharacterSize(18);
    finishText.setFillColor(
        sf::Color::White
    );

    finishText.setPosition(
        1180.0f,
        330.0f
    );

    window.draw(finishText);
}


// =============================================================
// RESET
// =============================================================

void GlassBridge::reset()
{
    participants.clear();

    activeParticipants.clear();
    passedParticipants.clear();
    participantData.clear();

    turnOrder.clear();
    cpuMemory.clear();

    turnIndex = 0;

    currentParticipant = nullptr;

    gameStarted = false;
    gameFinished = false;
    continueButton.setString(
        "Continue"
    );

    waitingForHumanInput = false;

    nextMoveDelay = 1.0f;

    turnText.setString(
        "Turn to move:"
    );

    timerText.setString(
        "Timer: --"
    );

    statusText.setString("");
    survivorText.setString("");
}


// =============================================================
// START GAME
// =============================================================

void GlassBridge::startGame()
{
    gameStarted = true;
    gameFinished = false;

    waitingForHumanInput = false;

    currentParticipant = nullptr;

    generateBridge();

    createTurnOrder();

    nextMoveDelay =
        generateMoveDelay();

    moveClock.restart();

    statusText.setString(
        "Glass Bridge started."
    );
}


// =============================================================
// GENERATE MOVE DELAY
// =============================================================

float GlassBridge::generateMoveDelay()
{
    // 0.75 to 1.25 seconds

    int randomValue =
        std::rand() % 51;

    return
        0.5f +
        (randomValue / 100.0f);
}

// =============================================================
// ALL REMAINING PARTICIPANTS FINISHED
// =============================================================

bool GlassBridge::allRemainingParticipantsFinished()
{
    for (
        ParticipantBridgeData& data :
        participantData
        )
    {
        if (
            data.participant->isAlive() &&
            !data.finished
            )
        {
            return false;
        }
    }

    return true;
}