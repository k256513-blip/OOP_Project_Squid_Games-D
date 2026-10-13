#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "GameState.h"
#include "Participant.h"

class TugOfWar
{
private:
    // =========================
    // PARTICIPANTS
    // =========================

    std::vector<Participant*> participants;
    std::vector<Participant*> roundWinners;

    std::vector<Participant*> currentTeamA;
    std::vector<Participant*> currentTeamB;


    // =========================
    // MATCH / ROUND TRACKING
    // =========================

    int currentRound;
    int currentMatch;

    bool gameFinished;
    bool humanMatch;


    // =========================
    // MATCH STATE
    // =========================

    enum class MatchState
    {
        Setup,
        Ready,
        Playing,
        Result,
        Finished
    };

    MatchState matchState;


    // =========================
    // ROPE / FORCE SYSTEM
    // =========================

    float teamAForce;
    float teamBForce;
    float ropePosition;


    // =========================
    // HUMAN
    // =========================

    bool humanInTeamA;
    bool humanInTeamB;


    // =========================
    // CPU
    // =========================

    float cpuTeamAPullInterval;
    float cpuTeamBPullInterval;

    float cpuTeamAPullImpulse;
    float cpuTeamBPullImpulse;


    // =========================
    // ADRENALINE
    // =========================

    bool adrenalineActive;
    bool adrenalineForTeamA;


    // =========================
    // TIMERS
    // =========================

    sf::Clock matchClock;
    sf::Clock stateClock;

    sf::Clock humanPullClock;

    sf::Clock cpuTeamAPullClock;
    sf::Clock cpuTeamBPullClock;

    sf::Clock adrenalineClock;


    // =========================
    // RESULT
    // =========================

    bool teamAWon;


    // =========================
    // FONTS / TEXT
    // =========================

    sf::Font font;

    sf::Text title;
    sf::Text teamAText;
    sf::Text teamBText;
    sf::Text matchText;

    sf::Text timerText;
    sf::Text ropeText;

    sf::Text stateText;
    sf::Text resultText;

    sf::Text passedText;
    sf::Text eliminatedText;

    sf::Text continueButton;


    // =========================
    // UI
    // =========================

    sf::RectangleShape continueButtonBox;


    // =========================
    // INTERNAL FUNCTIONS
    // =========================

    void buildNextRound();

    void setupNextMatch();

    void setupCurrentMatch();

    void startReadyState();

    void startPlayingState();

    void resolveMatch();

    void resolveBye(Participant* participant);

    void finishRound();

    void simulateCPUMatch();

    void updateHumanMatch();

    void updateCPUMatch();

    void updateAdrenaline();

    void updateRope();

    void applyHumanPull();

    void applyCPUPull(
        const std::vector<Participant*>& team,
        float& teamForce
    );

    float calculateCPUPullInterval(
        const std::vector<Participant*>& team
    );

    float calculateCPUPullImpulse(
        const std::vector<Participant*>& team
    );

    bool containsHuman(
        const std::vector<Participant*>& team
    );

    void eliminateTeam(
        const std::vector<Participant*>& team
    );

    void passTeam(
        const std::vector<Participant*>& team
    );


public:
    TugOfWar();

    void setParticipants(
        const std::vector<Participant*>& survivors
    );

    GameState handleInput(sf::Event& event);

    void update();

    void draw(sf::RenderWindow& window);

    void reset();

    void startGame();
};