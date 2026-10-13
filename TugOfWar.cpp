#include "TugOfWar.h"
#include "CPUPlayer.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <string>


// ============================================================
// CONSTRUCTOR
// ============================================================

TugOfWar::TugOfWar()
{
    currentRound = 1;
    currentMatch = 0;

    gameFinished = false;
    humanMatch = false;

    matchState = MatchState::Setup;

    teamAForce = 0.0f;
    teamBForce = 0.0f;
    ropePosition = 0.0f;

    humanInTeamA = false;
    humanInTeamB = false;

    cpuTeamAPullInterval = 0.0f;
    cpuTeamBPullInterval = 0.0f;

    cpuTeamAPullImpulse = 0.0f;
    cpuTeamBPullImpulse = 0.0f;

    adrenalineActive = false;
    adrenalineForTeamA = false;

    teamAWon = false;

    font.loadFromFile("arial.ttf");


    // ========================================================
    // TITLE
    // ========================================================

    title.setFont(font);
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::White);
    title.setString("TUG OF WAR");
    title.setPosition(520, 50);


    // ========================================================
    // TEAM TEXT
    // ========================================================

    teamAText.setFont(font);
    teamAText.setCharacterSize(24);
    teamAText.setFillColor(sf::Color::White);
    teamAText.setPosition(180, 150);

    teamBText.setFont(font);
    teamBText.setCharacterSize(24);
    teamBText.setFillColor(sf::Color::White);
    teamBText.setPosition(850, 150);


    // ========================================================
    // TIMER
    // ========================================================

    timerText.setFont(font);
    timerText.setCharacterSize(28);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(605, 120);


    // ========================================================
    // ROPE DEBUG / STATUS TEXT
    // ========================================================

    ropeText.setFont(font);
    ropeText.setCharacterSize(22);
    ropeText.setFillColor(sf::Color::White);
    ropeText.setPosition(570, 500);


    // ========================================================
    // STATE TEXT
    // ========================================================

    stateText.setFont(font);
    stateText.setCharacterSize(48);
    stateText.setFillColor(sf::Color::White);
    stateText.setPosition(540, 270);


    // ========================================================
    // RESULT
    // ========================================================

    resultText.setFont(font);
    resultText.setCharacterSize(32);
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(480, 400);


    // ========================================================
    // PASSED / ELIMINATED
    // ========================================================

    passedText.setFont(font);
    passedText.setCharacterSize(22);
    passedText.setFillColor(sf::Color::Green);
    passedText.setPosition(80, 420);

    eliminatedText.setFont(font);
    eliminatedText.setCharacterSize(22);
    eliminatedText.setFillColor(sf::Color::Red);
    eliminatedText.setPosition(900, 420);


    // ========================================================
    // CONTINUE BUTTON
    // ========================================================

    continueButtonBox.setSize(
        sf::Vector2f(300, 55)
    );

    continueButtonBox.setPosition(
        490, 550
    );

    continueButtonBox.setFillColor(
        sf::Color(30, 30, 30, 180)
    );

    continueButtonBox.setOutlineColor(
        sf::Color(255, 255, 255, 100)
    );

    continueButtonBox.setOutlineThickness(2);

    continueButton.setFont(font);
    continueButton.setCharacterSize(22);
    continueButton.setFillColor(sf::Color::White);
    continueButton.setString("CONTINUE");
    continueButton.setPosition(585, 563);
}


// ============================================================
// SET PARTICIPANTS
// ============================================================

void TugOfWar::setParticipants(
    const std::vector<Participant*>& survivors
)
{
    participants = survivors;

    roundWinners.clear();

    currentRound = 1;
    currentMatch = 0;

    gameFinished = false;

    currentTeamA.clear();
    currentTeamB.clear();

    // Reset all surviving participants for the new game.
    for (Participant* participant : participants)
    {
        participant->resetForNextGame();
    }

    buildNextRound();
}


// ============================================================
// BUILD NEXT ROUND
// ============================================================

void TugOfWar::buildNextRound()
{
    currentMatch = 0;

    currentTeamA.clear();
    currentTeamB.clear();

    // Shuffle participants for the new round.
    for (int i = static_cast<int>(participants.size()) - 1;
        i > 0;
        i--)
    {
        int randomIndex = std::rand() % (i + 1);

        Participant* temp = participants[i];

        participants[i] = participants[randomIndex];
        participants[randomIndex] = temp;
    }

    setupCurrentMatch();
}


// ============================================================
// SETUP NEXT MATCH
// ============================================================

void TugOfWar::setupNextMatch()
{
    setupCurrentMatch();
}


// ============================================================
// SETUP CURRENT MATCH
// ============================================================

void TugOfWar::setupCurrentMatch()
{
    currentTeamA.clear();
    currentTeamB.clear();

    teamAForce = 0.0f;
    teamBForce = 0.0f;

    ropePosition = 0.0f;

    humanInTeamA = false;
    humanInTeamB = false;

    humanMatch = false;

    adrenalineActive = false;
    adrenalineForTeamA = false;

    teamAWon = false;

    passedText.setString("");
    eliminatedText.setString("");
    resultText.setString("");

    // --------------------------------------------------------
    // No participants left in this round.
    // --------------------------------------------------------

    if (participants.empty())
    {
        finishRound();
        return;
    }


    // --------------------------------------------------------
    // One participant = automatic bye.
    // --------------------------------------------------------

    if (participants.size() == 1)
    {
        resolveBye(participants[0]);

        participants.clear();

        finishRound();

        return;
    }


    // --------------------------------------------------------
    // Three participants:
    //
    // One gets a bye.
    // The remaining two fight.
    // --------------------------------------------------------

    if (participants.size() == 3)
    {
        resolveBye(participants[0]);

        participants.erase(
            participants.begin()
        );
    }


    // --------------------------------------------------------
    // Four or more:
    //
    // First four form a 2v2.
    // --------------------------------------------------------

    if (participants.size() >= 4)
    {
        currentTeamA.push_back(participants[0]);
        currentTeamA.push_back(participants[1]);

        currentTeamB.push_back(participants[2]);
        currentTeamB.push_back(participants[3]);

        participants.erase(
            participants.begin(),
            participants.begin() + 4
        );
    }

    // --------------------------------------------------------
    // Exactly two:
    //
    // 1v1.
    // --------------------------------------------------------

    else if (participants.size() == 2)
    {
        currentTeamA.push_back(participants[0]);
        currentTeamB.push_back(participants[1]);

        participants.erase(
            participants.begin(),
            participants.begin() + 2
        );
    }


    // --------------------------------------------------------
    // Determine whether Player 1 is involved.
    // --------------------------------------------------------

    humanInTeamA = containsHuman(currentTeamA);
    humanInTeamB = containsHuman(currentTeamB);

    humanMatch =
        humanInTeamA ||
        humanInTeamB;


    // --------------------------------------------------------
    // Calculate CPU values for this matchup.
    // --------------------------------------------------------

    cpuTeamAPullInterval =
        calculateCPUPullInterval(currentTeamA);

    cpuTeamBPullInterval =
        calculateCPUPullInterval(currentTeamB);

    cpuTeamAPullImpulse =
        calculateCPUPullImpulse(currentTeamA);

    cpuTeamBPullImpulse =
        calculateCPUPullImpulse(currentTeamB);


    // --------------------------------------------------------
    // Prepare clocks.
    // --------------------------------------------------------

    cpuTeamAPullClock.restart();
    cpuTeamBPullClock.restart();

    adrenalineClock.restart();


    matchState = MatchState::Setup;
}


// ============================================================
// START READY STATE
// ============================================================

void TugOfWar::startReadyState()
{
    if (gameFinished)
        return;

    teamAForce = 0.0f;
    teamBForce = 0.0f;
    ropePosition = 0.0f;

    adrenalineActive = false;

    stateText.setString("READY");
    stateText.setPosition(545, 270);

    matchState = MatchState::Ready;

    stateClock.restart();
}


// ============================================================
// START PLAYING STATE
// ============================================================

void TugOfWar::startPlayingState()
{
    if (gameFinished)
        return;

    stateText.setString("GO!");
    stateText.setPosition(575, 270);

    teamAForce = 0.0f;
    teamBForce = 0.0f;
    ropePosition = 0.0f;

    adrenalineActive = false;

    matchClock.restart();
    stateClock.restart();

    cpuTeamAPullClock.restart();
    cpuTeamBPullClock.restart();

    // CPU-only matches are simulated internally.
    if (!humanMatch)
    {
        simulateCPUMatch();
    }

    matchState = MatchState::Playing;
}


// ============================================================
// UPDATE
// ============================================================

void TugOfWar::update()
{
    if (gameFinished)
        return;


    // ========================================================
    // SETUP
    // ========================================================

    if (matchState == MatchState::Setup)
    {
        return;
    }


    // ========================================================
    // READY
    // ========================================================

    if (matchState == MatchState::Ready)
    {
        float elapsed =
            stateClock.getElapsedTime().asSeconds();

        if (elapsed >= 0.75f &&
            elapsed < 1.5f)
        {
            stateText.setString("GO!");
            stateText.setPosition(575, 270);
        }

        if (elapsed >= 1.5f)
        {
            startPlayingState();
        }

        return;
    }


    // ========================================================
    // PLAYING
    // ========================================================

    if (matchState == MatchState::Playing)
    {
        if (humanMatch)
        {
            updateHumanMatch();
        }
        else
        {
            updateCPUMatch();
        }

        return;
    }


    // ========================================================
    // RESULT
    // ========================================================

    if (matchState == MatchState::Result)
    {
        return;
    }


    // ========================================================
    // FINISHED
    // ========================================================

    if (matchState == MatchState::Finished)
    {
        return;
    }
}


// ============================================================
// HUMAN MATCH
// ============================================================

void TugOfWar::updateHumanMatch()
{
    // --------------------------------------------------------
    // CPU pulls
    // --------------------------------------------------------

    if (!currentTeamA.empty() &&
        cpuTeamAPullInterval > 0.0f)
    {
        if (
            cpuTeamAPullClock.getElapsedTime().asSeconds()
            >= cpuTeamAPullInterval
            )
        {
            cpuTeamAPullClock.restart();

            applyCPUPull(
                currentTeamA,
                teamAForce
            );
        }
    }


    if (!currentTeamB.empty() &&
        cpuTeamBPullInterval > 0.0f)
    {
        if (
            cpuTeamBPullClock.getElapsedTime().asSeconds()
            >= cpuTeamBPullInterval
            )
        {
            cpuTeamBPullClock.restart();

            applyCPUPull(
                currentTeamB,
                teamBForce
            );
        }
    }


    // --------------------------------------------------------
    // Update rope.
    // --------------------------------------------------------

    updateRope();


    // --------------------------------------------------------
    // Adrenaline.
    // --------------------------------------------------------

    updateAdrenaline();


    // --------------------------------------------------------
    // Victory.
    // --------------------------------------------------------

    if (ropePosition >= 30.0f)
    {
        ropePosition = 30.0f;

        teamAWon = true;

        resolveMatch();

        return;
    }

    if (ropePosition <= -30.0f)
    {
        ropePosition = -30.0f;

        teamAWon = false;

        resolveMatch();

        return;
    }


    // --------------------------------------------------------
    // 30-second timeout.
    // --------------------------------------------------------

    if (
        stateClock.getElapsedTime().asSeconds()
        >= 30.0f
        )
    {
        if (ropePosition > 0.0f)
        {
            teamAWon = true;
        }
        else if (ropePosition < 0.0f)
        {
            teamAWon = false;
        }
        else
        {
            // Extremely rare exact tie.
            // Golden pull tiebreaker.

            teamAWon =
                (std::rand() % 2 == 0);
        }

        resolveMatch();

        return;
    }
}


// ============================================================
// CPU MATCH
// ============================================================

void TugOfWar::updateCPUMatch()
{
    // --------------------------------------------------------
    // CPU-only matches are simulated beforehand.
    //
    // teamAWon now contains the simulated result.
    // We simply animate the rope toward that result.
    // --------------------------------------------------------

    float animationDuration = 2.5f;

    float elapsed =
        stateClock.getElapsedTime().asSeconds();

    float progress =
        elapsed / animationDuration;

    if (progress > 1.0f)
        progress = 1.0f;


    if (teamAWon)
    {
        ropePosition =
            30.0f * progress;
    }
    else
    {
        ropePosition =
            -30.0f * progress;
    }


    if (progress >= 1.0f)
    {
        resolveMatch();
    }
}


// ============================================================
// UPDATE ROPE
// ============================================================

void TugOfWar::updateRope()
{
    float deltaTime =
        matchClock.restart().asSeconds();

    // Protect against a huge frame spike.
    if (deltaTime > 0.05f)
        deltaTime = 0.05f;

    if (deltaTime <= 0.0f)
        return;


    // --------------------------------------------------------
    // Force decay.
    //
    // Force gradually disappears instead of lasting forever.
    // --------------------------------------------------------

    teamAForce *=
        std::pow(0.15f, deltaTime);

    teamBForce *=
        std::pow(0.15f, deltaTime);


    // --------------------------------------------------------
    // Adrenaline multiplier.
    // --------------------------------------------------------

    float effectiveTeamAForce =
        teamAForce;

    float effectiveTeamBForce =
        teamBForce;

    if (adrenalineActive)
    {
        if (adrenalineForTeamA)
        {
            effectiveTeamAForce *= 1.10f;
        }
        else
        {
            effectiveTeamBForce *= 1.10f;
        }
    }


    // --------------------------------------------------------
    // Net force.
    // Positive = Team A.
    // Negative = Team B.
    // --------------------------------------------------------

    float netForce =
        effectiveTeamAForce -
        effectiveTeamBForce;


    // --------------------------------------------------------
    // Move rope.
    // Team A is on the left.
    // Positive rope position therefore moves left.
    // --------------------------------------------------------

    ropePosition +=
        netForce *
        deltaTime *
        1.5f;


    // --------------------------------------------------------
    // Keep rope inside limits.
    // --------------------------------------------------------

    if (ropePosition > 30.0f)
        ropePosition = 30.0f;

    if (ropePosition < -30.0f)
        ropePosition = -30.0f;
}


// ============================================================
// HUMAN PULL
// ============================================================

void TugOfWar::applyHumanPull()
{
    if (!humanMatch)
        return;

    if (
        humanPullClock.getElapsedTime().asSeconds()
        < 0.12f
        )
    {
        return;
    }


    if (humanInTeamA)
    {
        teamAForce += 2.0f;
    }
    else if (humanInTeamB)
    {
        teamBForce += 2.0f;
    }


    humanPullClock.restart();
}


// ============================================================
// CPU PULL
// ============================================================

void TugOfWar::applyCPUPull(
    const std::vector<Participant*>& team,
    float& teamForce
)
{
    float impulse =
        calculateCPUPullImpulse(team);

    if (impulse <= 0.0f)
        return;


    // --------------------------------------------------------
    // Small random variation.
    //
    // This prevents identical-skill CPUs from producing
    // perfectly identical results every time.
    // --------------------------------------------------------

    float randomMultiplier =
        0.90f +
        (
            static_cast<float>(std::rand() % 21)
            / 100.0f
            );

    impulse *= randomMultiplier;


    teamForce += impulse;
}


// ============================================================
// CPU PULL INTERVAL
// ============================================================

float TugOfWar::calculateCPUPullInterval(
    const std::vector<Participant*>& team
)
{
    float totalSkill = 0.0f;
    int cpuCount = 0;

    for (Participant* participant : team)
    {
        if (participant->isCPU())
        {
            CPUPlayer* cpu =
                dynamic_cast<CPUPlayer*>(participant);

            if (cpu != nullptr)
            {
                totalSkill += cpu->getSkill();
                cpuCount++;
            }
        }
    }

    if (cpuCount == 0)
        return 0.0f;


    float averageSkill =
        totalSkill /
        static_cast<float>(cpuCount);


    // Skill 50  -> 0.80 sec
    // Skill 75  -> 0.70 sec
    // Skill 95  -> 0.62 sec

    float interval =
        0.80f -
        (
            (averageSkill - 50.0f)
            / 100.0f
            )
        * 0.40f;


    if (interval < 0.62f)
        interval = 0.62f;

    if (interval > 0.80f)
        interval = 0.80f;


    return interval;
}


// ============================================================
// CPU PULL IMPULSE
// ============================================================

float TugOfWar::calculateCPUPullImpulse(
    const std::vector<Participant*>& team
)
{
    float totalImpulse = 0.0f;

    for (Participant* participant : team)
    {
        if (participant->isCPU())
        {
            CPUPlayer* cpu =
                dynamic_cast<CPUPlayer*>(participant);

            if (cpu != nullptr)
            {
                float skill =
                    cpu->getSkill();

                float impulse =
                    4.0f +
                    (
                        (skill - 50.0f)
                        / 10.0f
                        )
                    * 0.5f;

                totalImpulse += impulse;
            }
        }
    }

    return totalImpulse;
}


// ============================================================
// ADRENALINE
// ============================================================

void TugOfWar::updateAdrenaline()
{
    if (adrenalineActive)
    {
        if (
            adrenalineClock.getElapsedTime().asSeconds()
            >= 5.0f
            )
        {
            adrenalineActive = false;
        }

        return;
    }


    // --------------------------------------------------------
    // Team B is losing badly.
    // --------------------------------------------------------

    if (ropePosition >= 23.0f)
    {
        adrenalineActive = true;
        adrenalineForTeamA = false;

        adrenalineClock.restart();

        return;
    }


    // --------------------------------------------------------
    // Team A is losing badly.
    // --------------------------------------------------------

    if (ropePosition <= -23.0f)
    {
        adrenalineActive = true;
        adrenalineForTeamA = true;

        adrenalineClock.restart();

        return;
    }
}


// ============================================================
// SIMULATE CPU MATCH
// ============================================================

void TugOfWar::simulateCPUMatch()
{
    float simulatedTeamAForce = 0.0f;
    float simulatedTeamBForce = 0.0f;

    float simulatedRope = 0.0f;

    float teamAPullTimer = 0.0f;
    float teamBPullTimer = 0.0f;

    float simulatedTime = 0.0f;

    bool simulatedAdrenaline = false;
    bool simulatedAdrenalineForTeamA = false;

    float adrenalineTimer = 0.0f;


    float teamAInterval =
        cpuTeamAPullInterval;

    float teamBInterval =
        cpuTeamBPullInterval;

    float teamAImpulse =
        cpuTeamAPullImpulse;

    float teamBImpulse =
        cpuTeamBPullImpulse;


    // --------------------------------------------------------
    // Run the match in tiny simulation steps.
    // Maximum: 30 seconds.
    // --------------------------------------------------------

    const float simulationStep = 0.01f;

    while (simulatedTime < 30.0f)
    {
        simulatedTime += simulationStep;

        teamAPullTimer += simulationStep;
        teamBPullTimer += simulationStep;


        // ----------------------------------------------------
        // Team A CPU pull
        // ----------------------------------------------------

        if (
            teamAInterval > 0.0f &&
            teamAPullTimer >= teamAInterval
            )
        {
            teamAPullTimer -= teamAInterval;

            float randomMultiplier =
                0.90f +
                (
                    static_cast<float>(std::rand() % 21)
                    / 100.0f
                    );

            simulatedTeamAForce +=
                teamAImpulse *
                randomMultiplier;
        }


        // ----------------------------------------------------
        // Team B CPU pull
        // ----------------------------------------------------

        if (
            teamBInterval > 0.0f &&
            teamBPullTimer >= teamBInterval
            )
        {
            teamBPullTimer -= teamBInterval;

            float randomMultiplier =
                0.90f +
                (
                    static_cast<float>(std::rand() % 21)
                    / 100.0f
                    );

            simulatedTeamBForce +=
                teamBImpulse *
                randomMultiplier;
        }


        // ----------------------------------------------------
        // Force decay.
        // ----------------------------------------------------

        simulatedTeamAForce *=
            std::pow(
                0.15f,
                simulationStep
            );

        simulatedTeamBForce *=
            std::pow(
                0.15f,
                simulationStep
            );


        // ----------------------------------------------------
        // Adrenaline.
        // ----------------------------------------------------

        if (simulatedAdrenaline)
        {
            adrenalineTimer += simulationStep;

            if (adrenalineTimer >= 5.0f)
            {
                simulatedAdrenaline = false;
            }
        }
        else
        {
            if (simulatedRope >= 23.0f)
            {
                simulatedAdrenaline = true;
                simulatedAdrenalineForTeamA = false;
                adrenalineTimer = 0.0f;
            }
            else if (simulatedRope <= -23.0f)
            {
                simulatedAdrenaline = true;
                simulatedAdrenalineForTeamA = true;
                adrenalineTimer = 0.0f;
            }
        }


        // ----------------------------------------------------
        // Effective forces.
        // ----------------------------------------------------

        float effectiveTeamAForce =
            simulatedTeamAForce;

        float effectiveTeamBForce =
            simulatedTeamBForce;

        if (simulatedAdrenaline)
        {
            if (simulatedAdrenalineForTeamA)
            {
                effectiveTeamAForce *= 1.10f;
            }
            else
            {
                effectiveTeamBForce *= 1.10f;
            }
        }


        // ----------------------------------------------------
        // Move rope.
        // ----------------------------------------------------

        float netForce =
            effectiveTeamAForce -
            effectiveTeamBForce;

        simulatedRope +=
            netForce *
            simulationStep *
            1.5f;


        // ----------------------------------------------------
        // Victory.
        // ----------------------------------------------------

        if (simulatedRope >= 30.0f)
        {
            teamAWon = true;
            return;
        }

        if (simulatedRope <= -30.0f)
        {
            teamAWon = false;
            return;
        }
    }


    // --------------------------------------------------------
    // Timeout.
    // --------------------------------------------------------

    if (simulatedRope > 0.0f)
    {
        teamAWon = true;
    }
    else if (simulatedRope < 0.0f)
    {
        teamAWon = false;
    }
    else
    {
        teamAWon =
            (std::rand() % 2 == 0);
    }
}


// ============================================================
// RESOLVE MATCH
// ============================================================

void TugOfWar::resolveMatch()
{
    if (matchState == MatchState::Result)
        return;


    // ========================================================
    // TEAM A WINS
    // ========================================================

    if (teamAWon)
    {
        passTeam(currentTeamA);
        eliminateTeam(currentTeamB);

        resultText.setString(
            "TEAM A WINS!"
        );

        resultText.setPosition(500, 350);
    }


    // ========================================================
    // TEAM B WINS
    // ========================================================

    else
    {
        passTeam(currentTeamB);
        eliminateTeam(currentTeamA);

        resultText.setString(
            "TEAM B WINS!"
        );

        resultText.setPosition(500, 350);
    }


    // ========================================================
    // PASSED LIST
    // ========================================================

    std::string passedString =
        "PASSED\n";

    if (teamAWon)
    {
        for (Participant* participant : currentTeamA)
        {
            passedString +=
                participant->getName();

            passedString +=
                "\n";
        }
    }
    else
    {
        for (Participant* participant : currentTeamB)
        {
            passedString +=
                participant->getName();

            passedString +=
                "\n";
        }
    }


    // ========================================================
    // ELIMINATED LIST
    // ========================================================

    std::string eliminatedString =
        "ELIMINATED\n";

    if (teamAWon)
    {
        for (Participant* participant : currentTeamB)
        {
            eliminatedString +=
                participant->getName();

            eliminatedString +=
                "\n";
        }
    }
    else
    {
        for (Participant* participant : currentTeamA)
        {
            eliminatedString +=
                participant->getName();

            eliminatedString +=
                "\n";
        }
    }


    passedText.setString(
        passedString
    );

    eliminatedText.setString(
        eliminatedString
    );


    matchState = MatchState::Result;

    stateClock.restart();
}


// ============================================================
// RESOLVE BYE
// ============================================================

void TugOfWar::resolveBye(
    Participant* participant
)
{
    if (participant == nullptr)
        return;

    roundWinners.push_back(
        participant
    );
}


// ============================================================
// FINISH ROUND
// ============================================================

void TugOfWar::finishRound()
{
    // =========================================================
    // TUG OF WAR ENDS AFTER ONE FULL ELIMINATION ROUND
    //
    // Every winning team member is promoted.
    // No extra tournament rounds are played.
    // =========================================================

    gameFinished = true;

    resultText.setString(
        "TUG OF WAR COMPLETE!"
    );

    resultText.setPosition(
        430,
        350
    );

    matchState =
        MatchState::Finished;
}


// ============================================================
// PASS TEAM
// ============================================================

void TugOfWar::passTeam(
    const std::vector<Participant*>& team
)
{
    for (Participant* participant : team)
    {
        if (participant != nullptr)
        {
            roundWinners.push_back(
                participant
            );
        }
    }
}


// ============================================================
// ELIMINATE TEAM
// ============================================================

void TugOfWar::eliminateTeam(
    const std::vector<Participant*>& team
)
{
    for (Participant* participant : team)
    {
        if (participant != nullptr)
        {
            participant->eliminate();
        }
    }
}


// ============================================================
// CONTAINS HUMAN
// ============================================================

bool TugOfWar::containsHuman(
    const std::vector<Participant*>& team
)
{
    for (Participant* participant : team)
    {
        if (participant != nullptr &&
            !participant->isCPU())
        {
            return true;
        }
    }

    return false;
}


// ============================================================
// DRAW
// ============================================================

void TugOfWar::draw(
    sf::RenderWindow& window
)
{
    window.draw(title);


    // ========================================================
    // GAME FINISHED
    // ========================================================

    if (gameFinished)
    {
        window.draw(resultText);

        return;
    }


    // ========================================================
    // TEAM NAMES
    // ========================================================

    std::string teamAString =
        "TEAM A\n";

    for (Participant* participant : currentTeamA)
    {
        teamAString +=
            participant->getName();

        teamAString +=
            "\n";
    }


    std::string teamBString =
        "TEAM B\n";

    for (Participant* participant : currentTeamB)
    {
        teamBString +=
            participant->getName();

        teamBString +=
            "\n";
    }


    teamAText.setString(
        teamAString
    );

    teamBText.setString(
        teamBString
    );


    window.draw(teamAText);
    window.draw(teamBText);


    // ========================================================
    // MATCH INFORMATION
    // ========================================================

    if (matchState != MatchState::Finished)
    {
        std::string matchInfo =
            "ROUND " +
            std::to_string(currentRound) +
            "   MATCH " +
            std::to_string(currentMatch + 1);

        matchText.setString(
            matchInfo
        );
    }


    // ========================================================
    // ROPE
    // ========================================================

    sf::RectangleShape rope;

    rope.setSize(
        sf::Vector2f(360.0f, 8.0f)
    );

    rope.setFillColor(
        sf::Color::White
    );

    rope.setPosition(
        460.0f,
        370.0f
    );

    window.draw(rope);


    // ========================================================
    // CENTER MARK
    // ========================================================

    sf::RectangleShape centerMark;

    centerMark.setSize(
        sf::Vector2f(4.0f, 35.0f)
    );

    centerMark.setFillColor(
        sf::Color::Red
    );

    centerMark.setPosition(
        638.0f,
        356.0f
    );

    window.draw(centerMark);


    // ========================================================
    // ROPE POSITION MARKER
    // ========================================================

    sf::RectangleShape ropeMarker;

    ropeMarker.setSize(
        sf::Vector2f(12.0f, 30.0f)
    );

    ropeMarker.setFillColor(
        sf::Color::Yellow
    );


    float ropeX =
        640.0f -
        (ropePosition * 5.5f);


    ropeMarker.setPosition(
        ropeX - 6.0f,
        359.0f
    );

    window.draw(ropeMarker);


    // ========================================================
    // TIMER
    // ========================================================

    if (matchState == MatchState::Playing &&
        humanMatch)
    {
        float elapsed =
            stateClock.getElapsedTime().asSeconds();

        float remaining =
            30.0f - elapsed;

        if (remaining < 0.0f)
            remaining = 0.0f;

        timerText.setString(
            "TIME: " +
            std::to_string(
                static_cast<int>(remaining)
            )
        );

        window.draw(timerText);
    }


    // ========================================================
    // ROPE STATUS
    // ========================================================

    ropeText.setString(
        "Rope: " +
        std::to_string(
            static_cast<int>(ropePosition)
        )
    );

    window.draw(ropeText);


    // ========================================================
    // READY / GO
    // ========================================================

    if (matchState == MatchState::Ready)
    {
        window.draw(stateText);
    }


    // ========================================================
    // PLAYING
    // ========================================================

    if (matchState == MatchState::Playing)
    {
        stateText.setString("FIGHT!");
        stateText.setPosition(565, 270);

        window.draw(stateText);
    }


    // ========================================================
    // RESULT
    // ========================================================

    if (matchState == MatchState::Result)
    {
        window.draw(resultText);

        window.draw(passedText);
        window.draw(eliminatedText);

        window.draw(
            continueButtonBox
        );

        window.draw(
            continueButton
        );
    }
}


// ============================================================
// HANDLE INPUT
// ============================================================

GameState TugOfWar::handleInput(
    sf::Event& event
)
{
    // ========================================================
    // HUMAN PULL
    // ========================================================

    if (
        matchState == MatchState::Playing &&
        humanMatch &&
        event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::W
        )
    {
        applyHumanPull();
    }


    // ========================================================
    // CONTINUE BUTTON
    // ========================================================

    if (
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


        if (
            matchState == MatchState::Result &&
            continueButtonBox
            .getGlobalBounds()
            .contains(mouseX, mouseY)
            )
        {
            currentMatch++;


            // ------------------------------------------------
            // If no participants remain waiting in this round,
            // the round is over.
            // ------------------------------------------------

            if (participants.empty())
            {
                finishRound();

                if (gameFinished)
                {
                    return GameState::GameSelection;
                }

                // A new tournament round was created.
                // Start its READY -> GO sequence.
                startReadyState();
            }
            else
            {
                setupNextMatch();

                if (gameFinished)
                {
                    return GameState::GameSelection;
                }

                startReadyState();
            }
        }
    }


    return GameState::TugOfWar;
}


// ============================================================
// RESET
// ============================================================

void TugOfWar::reset()
{
    participants.clear();
    roundWinners.clear();

    currentTeamA.clear();
    currentTeamB.clear();

    currentRound = 1;
    currentMatch = 0;

    gameFinished = false;
    humanMatch = false;

    matchState = MatchState::Setup;

    teamAForce = 0.0f;
    teamBForce = 0.0f;
    ropePosition = 0.0f;

    humanInTeamA = false;
    humanInTeamB = false;

    cpuTeamAPullInterval = 0.0f;
    cpuTeamBPullInterval = 0.0f;

    cpuTeamAPullImpulse = 0.0f;
    cpuTeamBPullImpulse = 0.0f;

    adrenalineActive = false;
    adrenalineForTeamA = false;

    teamAWon = false;

    teamAText.setString("");
    teamBText.setString("");

    timerText.setString("");
    ropeText.setString("");

    stateText.setString("");

    resultText.setString("");

    passedText.setString("");
    eliminatedText.setString("");

    matchClock.restart();
    stateClock.restart();
    humanPullClock.restart();

    cpuTeamAPullClock.restart();
    cpuTeamBPullClock.restart();

    adrenalineClock.restart();
}


// ============================================================
// START GAME
// ============================================================

void TugOfWar::startGame()
{
    if (gameFinished)
        return;

    startReadyState();
}