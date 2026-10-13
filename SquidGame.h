#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "GameState.h"
#include "Participant.h"


class SquidGame
{
private:

    // =========================================================
    // FINALISTS
    // =========================================================

    std::vector<Participant*> finalists;

    Participant* humanPlayer;
    Participant* opponent;

    // =========================================================
// BACKGROUND
// =========================================================

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;


    // =========================================================
    // ARENA
    // =========================================================

    sf::RectangleShape arena;

    float arenaLeft;
    float arenaRight;
    float arenaTop;
    float arenaBottom;


    // =========================================================
    // GAME STATE
    // =========================================================

    bool gameStarted;
    bool gameFinished;

    enum class FightResult
    {
        None,
        HumanWon,
        HumanLost
    };

    FightResult fightResult;
    bool resultButtonClicked;
    // =========================================================
// OPPONENT AI
// =========================================================

    enum class OpponentState
    {
        Approach,
        Pressure,
        Evade,
        Recover
    };

    OpponentState opponentState;

    float opponentDecisionInterval;

    sf::Clock opponentDecisionClock;

    bool opponentDodging;

    sf::Vector2f opponentDodgeDirection;

    float opponentDodgeDuration;

    sf::Clock opponentDodgeClock;

    // =========================================================
// OPPONENT DASH
// =========================================================

    bool opponentDashing;

    float opponentDashDuration;
    float opponentDashMultiplier;
    float opponentDashCooldown;

    sf::Clock opponentDashClock;
    sf::Clock opponentDashCooldownClock;

    // =========================================================
    // MOVEMENT
    // =========================================================

    float playerSpeed;

    sf::Clock movementClock;

    float opponentSpeed;
    float opponentStopDistance;

    // =========================================================
// HEALTH
// =========================================================

    float humanHealth;
    float opponentHealth;

    const float maxHealth = 100.0f;


    float healthRegenRate;
    float healthRegenDelay;

    sf::Clock humanHealthRegenClock;
    sf::Clock opponentHealthRegenClock;

    // =========================================================
    // STAMINA
    // =========================================================

    float humanStamina;
    float opponentStamina;

    const float maxStamina = 100.0f;

    float dashCost;

    float staminaRegenRate;
    float staminaRegenDelay;

    sf::Clock humanStaminaRegenClock;

    bool humanDashing;
    float dashDuration;
    float dashMultiplier;

    sf::Clock dashClock;

    // =========================================================
// AIMING
// =========================================================

    sf::Vector2f humanAimDirection;

    sf::CircleShape aimIndicator;


    // =========================================================
// ROCK PROJECTILES
// =========================================================

    struct Rock
    {
        sf::CircleShape shape;
        sf::Vector2f velocity;

        bool active = false;

        bool thrownByHuman = true;
    };

    std::vector<Rock> rocks;

    float rockSpeed;
    float rockDamage;
    float rockCooldown;

    sf::Clock humanRockClock;
    sf::Clock opponentRockClock;

    // =========================================================
// MELEE ATTACK
// =========================================================

    float meleeDamage;
    float meleeRange;
    float meleeKnockback;
    float meleeStaminaCost;
    float meleeCooldown;

    sf::Clock humanMeleeClock;

    float opponentMeleeCooldown;

    sf::Clock opponentMeleeClock;
    sf::Clock opponentStaminaRegenClock;

    // =========================================================
    // HEALTH / STAMINA UI
    // =========================================================

    sf::RectangleShape humanHealthBack;
    sf::RectangleShape humanHealthBar;

    sf::RectangleShape opponentHealthBack;
    sf::RectangleShape opponentHealthBar;

    sf::RectangleShape humanStaminaBack;
    sf::RectangleShape humanStaminaBar;

    sf::RectangleShape opponentStaminaBack;
    sf::RectangleShape opponentStaminaBar;

    sf::Text humanHealthText;
    sf::Text opponentHealthText;

    sf::Text humanStaminaText;
    sf::Text opponentStaminaText;

    // =========================================================
// FINALIST SPRITES
// =========================================================

    sf::Texture humanIdleTexture;
    sf::Texture humanWalkTextures[5];

    sf::Texture opponentIdleTexture;
    sf::Texture opponentWalkTextures[5];

    sf::Sprite humanSprite;
    sf::Sprite opponentSprite;

    int humanWalkFrame;
    int opponentWalkFrame;

    sf::Clock humanAnimationClock;
    sf::Clock opponentAnimationClock;

    sf::Vector2f previousHumanVisualPosition;
    sf::Vector2f previousOpponentVisualPosition;

    sf::Vector2f humanVisualDirection;
    sf::Vector2f opponentVisualDirection;

    sf::Text playerOneLabel;


    // =========================================================
    // VISUAL HELPERS
    // =========================================================

    void drawDashSlash(
        sf::RenderWindow& window,
        sf::Vector2f position,
        sf::Vector2f direction
    );


    // =========================================================
    // UI
    // =========================================================

    sf::Font font;

    sf::Text title;
    sf::Text instructionText;
    sf::Text finalistText;

    sf::RectangleShape resultBox;
    sf::RectangleShape resultButton;

    sf::Text resultText;
    sf::Text resultButtonText;
    // =========================================================
    // INTERNAL HELPERS
    // =========================================================

    void findHumanAndOpponent();

    void updateHumanMovement(
        float deltaTime
    );
    void updateBars();
    void tryHumanMelee();
    void updateOpponentMovement(
        float deltaTime
    );
    void updateOpponentState();
    bool getOpponentDodgeDirection(
        sf::Vector2f& dodgeDirection
    );
    void tryOpponentMelee();
    void tryOpponentRock();
    void tryOpponentDash(
        float distance
    );
    void checkFightResult();
public:

    SquidGame();
    std::vector<Participant*> getFinalists() const;

    void setParticipants(
        const std::vector<Participant*>& survivors
    );


    void startGame();

    void reset();

    void update();

    void draw(
        sf::RenderWindow& window
    );


    GameState handleInput(
        sf::Event& event
    );

    void tryHumanDash();
    void updateStamina(float deltaTime);
    void updateHumanAim(
        const sf::RenderWindow& window
    );
    void throwHumanRock();

    void updateRocks(
        float deltaTime
    );
    void updateHealthRegen(
        float deltaTime
    );
    bool isFinished() const;

    bool didHumanWin() const;

    bool didHumanLose() const;
    bool consumeResultButtonClick();
};
