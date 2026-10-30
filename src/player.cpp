#include <cmath>
#include <vector>
#include "player.h"

static std::string directionToString(Direction dir)
{
    switch (dir)
    {
    case Direction::Down:
        return "Down";
    case Direction::DownLeft:
        return "DownLeft";
    case Direction::Left:
        return "Left";
    case Direction::UpLeft:
        return "UpLeft";
    case Direction::Up:
        return "Up";
    case Direction::UpRight:
        return "UpRight";
    case Direction::Right:
        return "Right";
    case Direction::DownRight:
        return "DownRight";
    }
    return "";
}

Player::Player(Vector2 startPosition)
    : position(startPosition)
{
    const std::vector<Direction> directions = {
        Direction::Down,
        Direction::DownLeft,
        Direction::Left,
        Direction::UpLeft,
        Direction::Up,
        Direction::UpRight,
        Direction::Right,
        Direction::DownRight};

    for (Direction dir : directions)
    {
        std::string dirStr = directionToString(dir);

        // Idle (14 frames)
        animations[MovementState::Idle][dir] =
            std::make_unique<Animation>(
                "assets/animations/player/idle/Idle_" + dirStr + ".png",
                14,
                0.1f);

        // Walk (9 frames)
        animations[MovementState::Walk][dir] =
            std::make_unique<Animation>(
                "assets/animations/player/walk/Walk_" + dirStr + ".png",
                9,
                0.1f);

        // Run (5 frames)
        animations[MovementState::Run][dir] =
            std::make_unique<Animation>(
                "assets/animations/player/run/Run_" + dirStr + ".png",
                5,
                0.1f);
    }

    currentAnimation = animations[MovementState::Idle][Direction::Down].get();
}

void Player::handleInput(float deltaTime)
{
    Vector2 movement{0.0f, 0.0f};
    bool sprinting = IsKeyDown(KEY_LEFT_SHIFT);

    if (IsKeyDown(KEY_A))
        movement.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        movement.x += 1.0f;
    if (IsKeyDown(KEY_W))
        movement.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        movement.y += 1.0f;

    // Normalize movement vector
    if (movement.x != 0.0f || movement.y != 0.0f)
    {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement.x /= length;
        movement.y /= length;
    }

    float speed = sprinting ? runSpeed : walkSpeed;
    position.x += movement.x * speed * deltaTime;
    position.y += movement.y * speed * deltaTime;

    updateState(movement, sprinting);
}

void Player::updateState(Vector2 movement, bool sprinting)
{
    MovementState newState;
    Direction newDirection = currentDirection;

    bool wasMoving = (currentState == MovementState::Walk || currentState == MovementState::Run);
    bool isMoving = (movement.x != 0.0f || movement.y != 0.0f);

    if (!isMoving)
    {
        newState = MovementState::Idle;
        newDirection = lastMovementDirection; // Idle with last movement direction
    }
    else
    {
        newState = sprinting ? MovementState::Run : MovementState::Walk;

        // Determine direction based on current movement vector
        if (movement.y > 0 && movement.x == 0)
            newDirection = Direction::Down;
        else if (movement.y < 0 && movement.x == 0)
            newDirection = Direction::Up;
        else if (movement.x > 0 && movement.y == 0)
            newDirection = Direction::Right;
        else if (movement.x < 0 && movement.y == 0)
            newDirection = Direction::Left;
        else if (movement.x > 0 && movement.y > 0)
            newDirection = Direction::DownRight;
        else if (movement.x < 0 && movement.y > 0)
            newDirection = Direction::DownLeft;
        else if (movement.x > 0 && movement.y < 0)
            newDirection = Direction::UpRight;
        else if (movement.x < 0 && movement.y < 0)
            newDirection = Direction::UpLeft;

        bool isDiagonal = (movement.x != 0.0f && movement.y != 0.0f);

        if (!wasMoving || isDiagonal)
        {
            lastMovementDirection = newDirection;
        }
    }

    if (newState != currentState || newDirection != currentDirection)
    {
        currentState = newState;
        currentDirection = newDirection;
        selectAnimation();
    }
}

void Player::selectAnimation()
{
    auto stateIt = animations.find(currentState);
    if (stateIt == animations.end())
        return;

    auto dirIt = stateIt->second.find(currentDirection);
    if (dirIt == stateIt->second.end())
        return;

    if (currentAnimation != dirIt->second.get())
    {
        currentAnimation = dirIt->second.get();
        currentAnimation->reset();
    }
}

void Player::update(float deltaTime)
{
    handleInput(deltaTime);

    if (currentAnimation)
        currentAnimation->update(deltaTime);
}

void Player::draw(float scale) const
{
    if (currentAnimation)
        currentAnimation->draw(position, scale);
}
