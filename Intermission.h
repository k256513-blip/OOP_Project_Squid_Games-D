#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "GameState.h"
#include "Participant.h"


class Intermission
{
private:

    // =========================================================
    // PARTICIPANTS
    // =========================================================

    std::vector<Participant*> participants;
    std::vector<Participant*> activeParticipants;


    // =========================================================
    // INTERMISSION STATE
    // =========================================================

    enum class IntermissionState
    {
        Waiting,
        Voting,
        Result,
        Finished
    };

    IntermissionState state;

    bool gameStarted;
    bool gameFinished;


    // =========================================================
 // VOTING
 // =========================================================

    Participant* playerVote;

    bool playerHasVoted;

    // ---------------------------------------------------------
// VOTE RECORD
// ---------------------------------------------------------

    struct VoteRecord
    {
        Participant* voter;
        Participant* target;
    };

    std::vector<VoteRecord> votes;


    // ---------------------------------------------------------
    // VOTE BUTTON
    // ---------------------------------------------------------

    struct VoteButton
    {
        Participant* target = nullptr;

        sf::RectangleShape box;
        sf::Text text;
    };

    std::vector<VoteButton> voteButtons;


    // =========================================================
    // TIMERS
    // =========================================================

    sf::Clock votingClock;
    sf::Clock resultClock;


    // =========================================================
    // GRAPHICS
    // =========================================================

    sf::Font font;

    sf::Text title;
    sf::Text timerText;
    sf::Text statusTitle;
    sf::Text resultText;
    sf::Text finalText;
    sf::Text continueButton;

    sf::RectangleShape continueButtonBox;

    // =========================================================
// INTERNAL FUNCTIONS
// =========================================================

    void createVoteButtons();

    Participant* getHumanPlayer();
    void beginVotingRound();

    void castCPUVotes();

    void castAutomaticPlayerVote();

    void resolveVotes();

    void startResultPhase(
        Participant* eliminatedParticipant
    );

    void finishIntermission();

    Participant* chooseRandomValidTarget(
        Participant* voter,
        bool protectHuman
    );

    int getAliveCount();

public:

    // =========================================================
    // CONSTRUCTOR
    // =========================================================

    Intermission();


    // =========================================================
    // PARTICIPANTS
    // =========================================================

    void setParticipants(
        const std::vector<Participant*>& survivors
    );


    // =========================================================
    // MAIN FUNCTIONS
    // =========================================================

    GameState handleInput(sf::Event& event);

    void update();

    void draw(sf::RenderWindow& window);

    void reset();

    void startGame();
};
