#pragma once
#include <raylib.h>
#include <map>
#include <memory>
#include "animation.h"

enum class MovementState
{
    Idle,
    Walk,
    Run
};

enum class Direction
{
    Down,
    DownLeft,
    Left,
    UpLeft,
    Up,
    UpRight,
    Right,
    DownRight
};

class Player
{
private:
    Vector2 position{};
    float walkSpeed{200.0f};
    float runSpeed{400.0f};

    MovementState currentState{MovementState::Idle};
    Direction currentDirection{Direction::Down};
    Direction lastMovementDirection{Direction::Down}; // Track last direction while moving

    std::map<MovementState, std::map<Direction, std::unique_ptr<Animation>>> animations;

    Animation *currentAnimation{nullptr};

private:
    void handleInput(float deltaTime);
    void updateState(Vector2 movement, bool sprinting);
    void selectAnimation();

public:
    Player(Vector2 startPosition);
    void update(float deltaTime);
    void draw(float scale) const;

    Vector2 getPosition() const { return position; }
};
