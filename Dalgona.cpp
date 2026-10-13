#include "Dalgona.h"

#include <cstdlib>
#include <ctime>

Dalgona::Dalgona(
    HumanPlayer* player1,
    CPUPlayer* player2,
    CPUPlayer* player3,
    CPUPlayer* player4,
    CPUPlayer* player5,
    CPUPlayer* player6
)
{
    participants.push_back(player1);
    participants.push_back(player2);
    participants.push_back(player3);
    participants.push_back(player4);
    participants.push_back(player5);
    participants.push_back(player6);

    std::srand(
        static_cast<unsigned int>(
            std::time(nullptr)
            )
    );

    font.loadFromFile("snapitc.ttf");

    title.setFont(font);
    title.setString("DALGONA");
    title.setCharacterSize(50);
    title.setPosition(540, 30);

    resultText.setFont(font);
    resultText.setCharacterSize(50);
    resultText.setPosition(430, 300);
    resultText.setFillColor(sf::Color::Green);

    // =========================================================
// BACKGROUND
// =========================================================

    if (
        backgroundTexture.loadFromFile(
            "Dalgona.jpg"
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

    continueButtonBox.setSize(
        sf::Vector2f(180, 60)
    );

    continueButtonBox.setPosition(
        550, 660
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
        585, 672
    );

    for (int i = 0; i < 4; i++)
    {
        compartments[i].setSize(
            sf::Vector2f(360, 260)
        );

        compartments[i].setFillColor(
            sf::Color(40, 40, 40)
        );

        compartments[i].setOutlineColor(
            sf::Color::White
        );

        compartments[i].setOutlineThickness(2.0f);

        cookies[i].setRadius(70);
        cookies[i].setPointCount(64);

        cookies[i].setFillColor(
            sf::Color(210, 170, 100)
        );

        playerNames[i].setFont(font);
        playerNames[i].setCharacterSize(22);
        playerNames[i].setFillColor(
            sf::Color::White
        );

        eliminatedText[i].setFont(font);
        eliminatedText[i].setString("ELIMINATED");
        eliminatedText[i].setCharacterSize(28);
        eliminatedText[i].setFillColor(
            sf::Color::Red
        );

        passedText[i].setFont(font);
        passedText[i].setString("PASSED");
        passedText[i].setCharacterSize(28);
        passedText[i].setFillColor(
            sf::Color::Green
        );

        for (int j = 0; j < 4; j++)
        {
            sequenceText[i][j].setFont(font);
            sequenceText[i][j].setCharacterSize(24);
            sequenceText[i][j].setFillColor(
                sf::Color::Black
            );
        }

        circleShapes[i].setRadius(25);
        circleShapes[i].setPointCount(32);
        circleShapes[i].setFillColor(
            sf::Color::Transparent
        );
        circleShapes[i].setOutlineColor(
            sf::Color::Black
        );
        circleShapes[i].setOutlineThickness(4);

        triangleShapes[i].setPointCount(3);

        triangleShapes[i].setPoint(
            0,
            sf::Vector2f(0, 50)
        );

        triangleShapes[i].setPoint(
            1,
            sf::Vector2f(50, 50)
        );

        triangleShapes[i].setPoint(
            2,
            sf::Vector2f(25, 0)
        );

        triangleShapes[i].setFillColor(
            sf::Color::Transparent
        );

        triangleShapes[i].setOutlineColor(
            sf::Color::Black
        );

        triangleShapes[i].setOutlineThickness(4);

        squareShapes[i].setSize(
            sf::Vector2f(50, 50)
        );

        squareShapes[i].setFillColor(
            sf::Color::Transparent
        );

        squareShapes[i].setOutlineColor(
            sf::Color::Black
        );

        squareShapes[i].setOutlineThickness(4);
    }

    compartments[0].setPosition(60, 100);
    compartments[1].setPosition(460, 100);
    compartments[2].setPosition(860, 100);
    compartments[3].setPosition(260, 420);

    for (int i = 0; i < 4; i++)
    {
        float compartmentX =
            compartments[i].getPosition().x;

        float compartmentY =
            compartments[i].getPosition().y;

        cookies[i].setPosition(
            compartmentX + 110,
            compartmentY + 80
        );

        playerNames[i].setPosition(
            compartmentX + 10,
            compartmentY + 10
        );

        eliminatedText[i].setPosition(
            compartmentX + 90,
            compartmentY + 115
        );

        passedText[i].setPosition(
            compartmentX + 125,
            compartmentY + 115
        );

        circleShapes[i].setPosition(
            compartmentX + 155,
            compartmentY + 125
        );

        triangleShapes[i].setPosition(
            compartmentX + 155,
            compartmentY + 125
        );

        squareShapes[i].setPosition(
            compartmentX + 155,
            compartmentY + 125
        );

        sequenceText[i][0].setPosition(
            compartmentX + 170,
            compartmentY + 55
        );

        sequenceText[i][1].setPosition(
            compartmentX + 105,
            compartmentY + 125
        );

        sequenceText[i][2].setPosition(
            compartmentX + 225,
            compartmentY + 125
        );

        sequenceText[i][3].setPosition(
            compartmentX + 170,
            compartmentY + 200
        );
    }

    playerShapes[0] = DalgonaShape::Circle;
    playerShapes[1] = DalgonaShape::Triangle;
    playerShapes[2] = DalgonaShape::Square;
    playerShapes[3] = DalgonaShape::Triangle;

    memorizationPhase = false;
    inputPhase = false;

    currentSequenceIndex = 0;

    
    playerCompleted = false;
    gameFinished = false;

    currentBatchStart = 0;
    currentBatchSize = 0;
    totalBatches = 0;
    currentBatchNumber = 0;
    humanBatchSlot = -1;


    for (int i = 0; i < 4; i++)
    {
        cpuPlayers[i] = nullptr;
        cpuSequenceIndex[i] = 0;
        
    }

    memorizationClock.restart();
    cpuClock.restart();
}
GameState Dalgona::handleInput(sf::Event& event)
{
    if (gameFinished)
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePosition(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
            );

            if (continueButtonBox.getGlobalBounds().contains(mousePosition))
            {
                return GameState::GameSelection;
            }
        }

        return GameState::Dalgona;
    }

    // The human is not in this batch.
    // There is nothing for the human to control right now.
    if (humanBatchSlot == -1)
    {
        return GameState::Dalgona;
    }

    // Ignore input once the human has already completed this batch.
    if (playerCompleted ||
        !currentBatch[humanBatchSlot]->isAlive())
    {
        return GameState::Dalgona;
    }

    if (memorizationPhase)
    {
        return GameState::Dalgona;
    }

    if (event.type == sf::Event::KeyPressed)
    {
        char pressedKey = '\0';

        switch (event.key.code)
        {
        case sf::Keyboard::A: pressedKey = 'A'; break;
        case sf::Keyboard::S: pressedKey = 'S'; break;
        case sf::Keyboard::D: pressedKey = 'D'; break;
        case sf::Keyboard::F: pressedKey = 'F'; break;
        case sf::Keyboard::Q: pressedKey = 'Q'; break;
        case sf::Keyboard::W: pressedKey = 'W'; break;
        case sf::Keyboard::E: pressedKey = 'E'; break;
        case sf::Keyboard::R: pressedKey = 'R'; break;
        case sf::Keyboard::Z: pressedKey = 'Z'; break;
        case sf::Keyboard::X: pressedKey = 'X'; break;
        case sf::Keyboard::C: pressedKey = 'C'; break;
        case sf::Keyboard::V: pressedKey = 'V'; break;
        default:
            break;
        }

        if (pressedKey == '\0')
        {
            return GameState::Dalgona;
        }

        if (pressedKey ==
            sequences[humanBatchSlot][currentSequenceIndex])
        {
            currentSequenceIndex++;

            if (currentSequenceIndex >=
                static_cast<int>(sequences[humanBatchSlot].size()))
            {
                currentBatch[humanBatchSlot]->finish();
                playerCompleted = true;
            }
        }
        else
        {
            
            currentSequenceIndex = 0;

            currentBatch[humanBatchSlot]->eliminate();

            playerCompleted = true;

            inputPhase = false;
            memorizationPhase = false;

            gameFinished = true;
            continueButton.setString(
                "Retry"
            );
        }
    }

    return GameState::Dalgona;
}

void Dalgona::update()
{
    if (gameFinished)
        return;

    // Memorization phase
    if (memorizationPhase)
    {
        if (memorizationClock.getElapsedTime().asSeconds() >= 2.5f)
        {
            memorizationPhase = false;
            inputPhase = true;

            currentSequenceIndex = 0;

            for (int i = 0; i < 4; i++)
            {
                cpuSequenceIndex[i] = 0;
            }
        }

        return;
    }

    // Let the CPUs attempt their sequences
    updateCPUs();

    // Check whether everyone in the current batch
    // has either passed or been eliminated.
    bool batchFinished = true;

    for (int i = 0; i < currentBatchSize; i++)
    {
        if (currentBatch[i]->isAlive() &&
            !currentBatch[i]->hasFinished())
        {
            batchFinished = false;
            break;
        }
    }

    if (!batchFinished)
        return;

    // This batch is completely resolved.
    currentBatchStart += currentBatchSize;

    // Are there any contestants left to process?
    if (currentBatchStart >=
        static_cast<int>(participants.size()))
    {
        gameFinished = true;
        inputPhase = false;
        memorizationPhase = false;
        return;
    }

    // Move on to the next batch.
    setupNextBatch();
}

void Dalgona::updateCPUs()
{
    if (!inputPhase)
        return;


    for (int i = 0; i < currentBatchSize; i++)
    {
        if (cpuPlayers[i] == nullptr)
            continue;


        if (!currentBatch[i]->isAlive())
            continue;


        if (currentBatch[i]->hasFinished())
            continue;


        if (
            cpuSequenceIndex[i] >=
            static_cast<int>(
                sequences[i].size()
                )
            )
        {
            currentBatch[i]->finish();

            continue;
        }


        if (
            cpuClock
            .getElapsedTime()
            .asSeconds() < 0.25f
            )
        {
            continue;
        }


        cpuClock.restart();


        // =============================================
        // CPU SUCCESSFUL INPUT
        // =============================================

        if (cpuPlayers[i]->shouldMove())
        {
            cpuSequenceIndex[i]++;


            if (
                cpuSequenceIndex[i] >=
                static_cast<int>(
                    sequences[i].size()
                    )
                )
            {
                currentBatch[i]->finish();
            }
        }


        // =============================================
        // CPU FAILED INPUT
        // ONE MISTAKE = ELIMINATION
        // =============================================

        else
        {
            currentBatch[i]->eliminate();
        }
    }
}

void Dalgona::draw(sf::RenderWindow& window)
{
    window.draw(title);

    // =========================================================
// BACKGROUND
// =========================================================

    window.draw(
        backgroundSprite
    );

    for (int i = 0; i < currentBatchSize; i++)
    {
        window.draw(compartments[i]);

        playerNames[i].setString(
            currentBatch[i]->getName()
        );

        window.draw(playerNames[i]);

        if (currentBatch[i]->isAlive())
        {
            if (currentBatch[i]->hasFinished())
            {
                window.draw(passedText[i]);
            }
            else
            {
                window.draw(cookies[i]);

                if (memorizationPhase)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        std::string letter = "";

                        letter += sequences[i][j];

                        sequenceText[i][j].setString(
                            letter
                        );

                        window.draw(
                            sequenceText[i][j]
                        );
                    }
                }

                // Shape depends on the slot in the current batch
                if (i == 0)
                {
                    window.draw(circleShapes[i]);
                }
                else if (i == 1)
                {
                    window.draw(triangleShapes[i]);
                }
                else if (i == 2)
                {
                    window.draw(squareShapes[i]);
                }
                else if (i == 3)
                {
                    window.draw(triangleShapes[i]);
                }
            }
        }
        else
        {
            window.draw(eliminatedText[i]);
        }
    }

    if (gameFinished)
    {
        window.draw(continueButtonBox);
        window.draw(continueButton);
    }
}
void Dalgona::reset()
{
    memorizationPhase = true;
    inputPhase = false;

    currentSequenceIndex = 0;

   
    playerCompleted = false;
    gameFinished = false;
    continueButton.setString(
        "Continue"
    );

    currentBatchStart = 0;
    currentBatchSize = 0;
    currentBatchNumber = 0;

    humanBatchSlot = -1;

    for (int i = 0; i < 4; i++)
    {
        cpuPlayers[i] = nullptr;
        
        cpuSequenceIndex[i] = 0;
    }

    currentBatch.clear();
    participants.clear();

    memorizationClock.restart();
    cpuClock.restart();
}


void Dalgona::startGame()
{
    memorizationPhase = true;
    inputPhase = false;

    currentSequenceIndex = 0;

    
    playerCompleted = false;

    memorizationClock.restart();
    cpuClock.restart();
}

void Dalgona::generateSequences()
{
    const char keys[] =
    {
        'A', 'S', 'D', 'F',
        'Q', 'W', 'E', 'R',
        'Z', 'X', 'C', 'V'
    };

    int keyCount = 12;

    for (int i = 0; i < 4; i++)
    {
        sequences[i].clear();

        char previousKey = '\0';

        for (int j = 0; j < 4; j++)
        {
            char newKey;

            do
            {
                int randomIndex =
                    std::rand() % keyCount;

                newKey = keys[randomIndex];

            } while (newKey == previousKey);

            sequences[i].push_back(newKey);

            previousKey = newKey;
        }
    }
}


void Dalgona::setParticipants(
    const std::vector<Participant*>& survivors
)
{
    participants = survivors;
    for (Participant* participant : participants)
    {
        participant->resetForNextGame();
    }

    // Randomize the order of the surviving contestants.
    // This determines which batch each contestant enters.
    for (int i = static_cast<int>(participants.size()) - 1;
        i > 0;
        i--)
    {
        int randomIndex = std::rand() % (i + 1);

        Participant* temp = participants[i];
        participants[i] = participants[randomIndex];
        participants[randomIndex] = temp;
    }

    currentBatchStart = 0;
    currentBatchSize = 0;
    currentBatchNumber = 0;

    humanBatchSlot = -1;

    gameFinished = false;

    setupNextBatch();
}

void Dalgona::setupNextBatch()
{
    currentBatch.clear();

    if (currentBatchStart >=
        static_cast<int>(participants.size()))
    {
        gameFinished = true;
        return;
    }

    currentBatchSize =
        static_cast<int>(participants.size()) -
        currentBatchStart;

    if (currentBatchSize > 4)
    {
        currentBatchSize = 4;
    }

    // Put the next group of survivors into the current batch
    for (int i = 0; i < currentBatchSize; i++)
    {
        currentBatch.push_back(
            participants[currentBatchStart + i]
        );
    }
    humanBatchSlot = -1;

    for (int i = 0; i < currentBatchSize; i++)
    {
        if (!currentBatch[i]->isCPU())
        {
            humanBatchSlot = i;
            break;
        }
    }

    currentBatchNumber++;

    // Reset this batch's state
    memorizationPhase = true;
    inputPhase = false;

    currentSequenceIndex = 0;

    
    playerCompleted = false;

    for (int i = 0; i < 4; i++)
    {
        cpuPlayers[i] = nullptr;
        cpuSequenceIndex[i] = 0;
        
    }

    // Identify which slots contain CPUs
    for (int i = 0; i < currentBatchSize; i++)
    {
        if (currentBatch[i]->isCPU())
        {
            cpuPlayers[i] =
                static_cast<CPUPlayer*>(currentBatch[i]);
        }
    }

    memorizationClock.restart();
    cpuClock.restart();

    generateSequences();
}