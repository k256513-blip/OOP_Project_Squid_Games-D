#include "Intermission.h"


// =============================================================
// CONSTRUCTOR
// =============================================================

Intermission::Intermission()
{
    state = IntermissionState::Waiting;

    gameStarted = false;
    gameFinished = false;

    playerVote = nullptr;
    playerHasVoted = false;


    // ---------------------------------------------------------
    // FONT
    // ---------------------------------------------------------

    font.loadFromFile("arial.ttf");


    // ---------------------------------------------------------
    // TITLE
    // ---------------------------------------------------------

    title.setFont(font);
    title.setString("INTERMISSION PHASE");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::White);
    title.setPosition(440, 40);


    // ---------------------------------------------------------
    // TIMER
    // ---------------------------------------------------------

    timerText.setFont(font);
    timerText.setString("Voting ends in: --");
    timerText.setCharacterSize(22);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(930, 50);


    // ---------------------------------------------------------
    // STATUS TITLE
    // ---------------------------------------------------------

    statusTitle.setFont(font);
    statusTitle.setString("Current status:");
    statusTitle.setCharacterSize(24);
    statusTitle.setFillColor(sf::Color::White);
    statusTitle.setPosition(60, 120);


    // ---------------------------------------------------------
    // RESULT TEXT
    // ---------------------------------------------------------

    resultText.setFont(font);
    resultText.setString("");
    resultText.setCharacterSize(18);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(820, 180);


    // ---------------------------------------------------------
    // FINAL TEXT
    // ---------------------------------------------------------

    finalText.setFont(font);
    finalText.setString("");
    finalText.setCharacterSize(28);
    finalText.setFillColor(sf::Color::Green);
    finalText.setPosition(340, 500);


    // ---------------------------------------------------------
    // CONTINUE BUTTON
    // ---------------------------------------------------------

    continueButtonBox.setSize(
        sf::Vector2f(220, 60)
    );

    continueButtonBox.setPosition(
        530, 610
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
        585, 623
    );
}


// =============================================================
// SET PARTICIPANTS
// =============================================================

void Intermission::setParticipants(
    const std::vector<Participant*>& survivors
)
{
    participants = survivors;

    activeParticipants.clear();

    for (Participant* participant : participants)
    {
        if (participant->isAlive())
        {
            activeParticipants.push_back(
                participant
            );
        }
    }
}

// =============================================================
// GET HUMAN PLAYER
// =============================================================

Participant* Intermission::getHumanPlayer()
{
    for (Participant* participant : activeParticipants)
    {
        if (!participant->isCPU())
        {
            return participant;
        }
    }

    return nullptr;
}


// =============================================================
// CREATE VOTE BUTTONS
// =============================================================

void Intermission::createVoteButtons()
{
    voteButtons.clear();

    Participant* humanPlayer =
        getHumanPlayer();

    float startY = 180.0f;


    for (
        int i = 0;
        i < static_cast<int>(participants.size());
        i++
        )
    {
        Participant* participant =
            participants[i];


        // -----------------------------------------------------
        // ONLY ALIVE PLAYERS CAN BE VOTED
        // -----------------------------------------------------

        if (
            participant->isAlive() &&
            participant != humanPlayer
            )
        {
            VoteButton button;

            button.target =
                participant;


            // -------------------------------------------------
            // BUTTON BOX
            // -------------------------------------------------

            button.box.setSize(
                sf::Vector2f(150, 36)
            );

            button.box.setPosition(
                520.0f,
                startY
            );

            button.box.setFillColor(
                sf::Color(70, 70, 70)
            );

            button.box.setOutlineColor(
                sf::Color::White
            );

            button.box.setOutlineThickness(
                2.0f
            );


            // -------------------------------------------------
            // BUTTON TEXT
            // -------------------------------------------------

            button.text.setFont(font);

            button.text.setString(
                "Vote Out"
            );

            button.text.setCharacterSize(18);

            button.text.setFillColor(
                sf::Color::White
            );

            button.text.setPosition(
                555.0f,
                startY + 7.0f
            );


            voteButtons.push_back(
                button
            );
        }


        // -----------------------------------------------------
        // ALWAYS MOVE DOWN ONE PARTICIPANT ROW
        // -----------------------------------------------------

        startY += 55.0f;
    }
}

// =============================================================
// HANDLE INPUT
// =============================================================

GameState Intermission::handleInput(
    sf::Event& event
)
{
    if (!gameStarted)
    {
        return GameState::Intermission;
    }


    // =========================================================
    // VOTING
    // =========================================================

    if (
        state == IntermissionState::Voting &&
        !playerHasVoted
        )
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


            for (
                VoteButton& button :
                voteButtons
                )
            {
                if (
                    button.box
                    .getGlobalBounds()
                    .contains(
                        mouseX,
                        mouseY
                    )
                    )
                {
                    playerVote =
                        button.target;

                    playerHasVoted =
                        true;

                    resultText.setString(
                        "You voted to eliminate " +
                        playerVote->getName()
                    );

                    break;
                }
            }
        }
    }


    // =========================================================
    // FINISHED
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
    }


    return GameState::Intermission;
}


// =============================================================
// UPDATE
// =============================================================

void Intermission::update()
{
    if (!gameStarted)
        return;

    if (gameFinished)
        return;


    // =========================================================
    // VOTING
    // =========================================================

    if (
        state ==
        IntermissionState::Voting
        )
    {
        float remainingTime =
            5.0f -
            votingClock
            .getElapsedTime()
            .asSeconds();


        if (remainingTime < 0.0f)
            remainingTime = 0.0f;


        int displayTime =
            static_cast<int>(
                remainingTime + 0.99f
                );


        timerText.setString(
            "Voting ends in: " +
            std::to_string(
                displayTime
            ) +
            " seconds"
        );


        if (remainingTime <= 0.0f)
        {
            if (!playerHasVoted)
            {
                castAutomaticPlayerVote();
            }


            castCPUVotes();

            resolveVotes();
        }
    }


    // =========================================================
    // RESULT
    // =========================================================

    else if (
        state ==
        IntermissionState::Result
        )
    {
        if (
            resultClock
            .getElapsedTime()
            .asSeconds()
            >= 2.0f
            )
        {
            if (
                getAliveCount() <= 2
                )
            {
                finishIntermission();
            }

            else
            {
                beginVotingRound();
            }
        }
    }
}


// =============================================================
// GET ALIVE COUNT
// =============================================================

int Intermission::getAliveCount()
{
    int count = 0;

    for (Participant* participant : participants)
    {
        if (participant->isAlive())
        {
            count++;
        }
    }

    return count;
}


// =============================================================
// BEGIN VOTING ROUND
// =============================================================

void Intermission::beginVotingRound()
{
    if (getAliveCount() <= 2)
    {
        finishIntermission();
        return;
    }

    state = IntermissionState::Voting;

    votes.clear();

    playerVote = nullptr;
    playerHasVoted = false;

    resultText.setString("");

    createVoteButtons();

    votingClock.restart();
}


// =============================================================
// CHOOSE RANDOM VALID TARGET
// =============================================================

Participant* Intermission::chooseRandomValidTarget(
    Participant* voter,
    bool protectHuman
)
{
    std::vector<Participant*> possibleTargets;

    Participant* humanPlayer =
        getHumanPlayer();


    for (Participant* participant : activeParticipants)
    {
        if (!participant->isAlive())
            continue;

        if (participant == voter)
            continue;


        // -----------------------------------------------------
        // CPU IS LESS LIKELY TO TARGET PLAYER 1
        // -----------------------------------------------------

        if (
            protectHuman &&
            participant == humanPlayer
            )
        {
            // Add Player 1 once.
            possibleTargets.push_back(
                participant
            );
        }

        else
        {
            // Other targets receive greater weight.
            possibleTargets.push_back(
                participant
            );

            possibleTargets.push_back(
                participant
            );

            possibleTargets.push_back(
                participant
            );
        }
    }


    if (possibleTargets.empty())
        return nullptr;


    int randomIndex =
        std::rand() %
        static_cast<int>(
            possibleTargets.size()
            );


    return possibleTargets[
        randomIndex
    ];
}


// =============================================================
// AUTOMATIC PLAYER VOTE
// =============================================================

void Intermission::castAutomaticPlayerVote()
{
    Participant* humanPlayer =
        getHumanPlayer();


    if (
        humanPlayer == nullptr ||
        !humanPlayer->isAlive() ||
        playerHasVoted
        )
    {
        return;
    }


    playerVote =
        chooseRandomValidTarget(
            humanPlayer,
            false
        );


    if (playerVote != nullptr)
    {
        playerHasVoted = true;
    }
}


// =============================================================
// CAST CPU VOTES
// =============================================================

void Intermission::castCPUVotes()
{
    for (Participant* voter : activeParticipants)
    {
        if (!voter->isAlive())
            continue;

        if (!voter->isCPU())
            continue;


        Participant* target =
            chooseRandomValidTarget(
                voter,
                true
            );


        if (target != nullptr)
        {
            VoteRecord vote;

            vote.voter =
                voter;

            vote.target =
                target;

            votes.push_back(
                vote
            );
        }
    }
}


// =============================================================
// RESOLVE VOTES
// =============================================================

void Intermission::resolveVotes()
{
    Participant* humanPlayer =
        getHumanPlayer();


    // ---------------------------------------------------------
    // ADD PLAYER 1'S VOTE
    // ---------------------------------------------------------

    if (
        humanPlayer != nullptr &&
        humanPlayer->isAlive() &&
        playerVote != nullptr
        )
    {
        VoteRecord vote;

        vote.voter =
            humanPlayer;

        vote.target =
            playerVote;

        votes.push_back(
            vote
        );
    }


    // ---------------------------------------------------------
    // COUNT VOTES
    // ---------------------------------------------------------

    int highestVotes = 0;

    std::vector<Participant*> tiedPlayers;


    for (Participant* candidate : activeParticipants)
    {
        if (!candidate->isAlive())
            continue;


        int count = 0;


        for (VoteRecord& vote : votes)
        {
            if (
                vote.target ==
                candidate
                )
            {
                count++;
            }
        }


        if (count > highestVotes)
        {
            highestVotes = count;

            tiedPlayers.clear();

            tiedPlayers.push_back(
                candidate
            );
        }

        else if (
            count == highestVotes &&
            count > 0
            )
        {
            tiedPlayers.push_back(
                candidate
            );
        }
    }


    if (tiedPlayers.empty())
        return;


    Participant* eliminated =
        nullptr;


    // ---------------------------------------------------------
    // CLEAR WINNER
    // ---------------------------------------------------------

    if (tiedPlayers.size() == 1)
    {
        eliminated =
            tiedPlayers[0];
    }


    // ---------------------------------------------------------
    // TIE
    // ---------------------------------------------------------

    else
    {
        std::vector<Participant*>
            tieCandidates;


        for (
            Participant* participant :
            tiedPlayers
            )
        {
            // Player 1 cannot be randomly removed
            // through tie-breaking.

            if (
                participant !=
                humanPlayer
                )
            {
                tieCandidates.push_back(
                    participant
                );
            }
        }


        if (!tieCandidates.empty())
        {
            eliminated =
                tieCandidates[
                    std::rand() %
                        static_cast<int>(
                            tieCandidates.size()
                            )
                ];
        }

        else
        {
            // Extremely unlikely fallback.
            eliminated =
                tiedPlayers[0];
        }
    }


    if (eliminated != nullptr)
    {
        eliminated->eliminate();

        startResultPhase(
            eliminated
        );
    }
}


// =============================================================
// START RESULT PHASE
// =============================================================

void Intermission::startResultPhase(
    Participant* eliminatedParticipant
)
{
    state =
        IntermissionState::Result;


    std::string result =
        "VOTING HAS ENDED\n\n";


    // ---------------------------------------------------------
    // SHOW WHO VOTED FOR EACH PLAYER
    // ---------------------------------------------------------

    for (Participant* candidate : participants)
    {
        result +=
            candidate->getName();

        result += ": ";


        bool firstVote = true;


        for (VoteRecord& vote : votes)
        {
            if (
                vote.target ==
                candidate
                )
            {
                if (!firstVote)
                {
                    result += ", ";
                }


                result +=
                    vote.voter->getName();

                firstVote = false;
            }
        }


        result += "\n";
    }


    result += "\nELIMINATED: ";

    result +=
        eliminatedParticipant
        ->getName();


    resultText.setString(
        result
    );


    resultClock.restart();
}


// =============================================================
// FINISH INTERMISSION
// =============================================================

void Intermission::finishIntermission()
{
    state =
        IntermissionState::Finished;

    gameFinished = true;


    std::vector<Participant*>
        finalists;


    for (Participant* participant : participants)
    {
        if (participant->isAlive())
        {
            finalists.push_back(
                participant
            );
        }
    }


    if (finalists.size() >= 2)
    {
        finalText.setString(
            finalists[0]->getName() +
            " and " +
            finalists[1]->getName() +
            " have been selected for SQUID GAME"
        );
    }

    else
    {
        finalText.setString(
            "INTERMISSION COMPLETE"
        );
    }


    timerText.setString(
        "Voting has ended"
    );
}


// =============================================================
// DRAW
// =============================================================

void Intermission::draw(
    sf::RenderWindow& window
)
{
    window.draw(title);
    window.draw(timerText);
    window.draw(statusTitle);


    // =========================================================
    // PARTICIPANT STATUS LIST
    // =========================================================

    float startY = 180.0f;


    for (Participant* participant : participants)
    {
        sf::Text participantText;

        participantText.setFont(font);

        participantText.setCharacterSize(20);

        participantText.setPosition(
            80.0f,
            startY
        );


        if (participant->isAlive())
        {
            participantText.setString(
                participant->getName() +
                ": ALIVE"
            );

            participantText.setFillColor(
                sf::Color::White
            );
        }

        else
        {
            participantText.setString(
                participant->getName() +
                ": ELIMINATED"
            );

            participantText.setFillColor(
                sf::Color::Red
            );
        }


        window.draw(
            participantText
        );


        startY += 55.0f;
    }


    // =========================================================
    // VOTE BUTTONS
    // =========================================================

    if (
        state ==
        IntermissionState::Voting &&
        !playerHasVoted
        )
    {
        for (
            VoteButton& button :
            voteButtons
            )
        {
            window.draw(
                button.box
            );

            window.draw(
                button.text
            );
        }
    }


    // =========================================================
    // RESULT / FINAL
    // =========================================================

    window.draw(
        resultText
    );


    if (gameFinished)
    {
        window.draw(
            finalText
        );

        window.draw(
            continueButtonBox
        );

        window.draw(
            continueButton
        );
    }
}


// =============================================================
// RESET
// =============================================================

void Intermission::reset()
{
    participants.clear();
    activeParticipants.clear();
    votes.clear();
    voteButtons.clear();

    state = IntermissionState::Waiting;

    gameStarted = false;
    gameFinished = false;

    playerVote = nullptr;
    playerHasVoted = false;

    timerText.setString(
        "Voting ends in: --"
    );

    resultText.setString("");
    finalText.setString("");

}


// =============================================================
// START GAME
// =============================================================

void Intermission::startGame()
{
    gameStarted = true;
    gameFinished = false;

    beginVotingRound();
}
