#pragma once
#include <raylib.h>

class GameCamera
{
private:
    Camera2D camera{};
    Vector2 targetPosition{};
    float smoothSpeed{5.0f};

public:
    GameCamera(Vector2 startPosition, float zoom = 1.0f);

    void followTarget(Vector2 target, float deltaTime);
    void setZoom(float zoom);

    void begin() const;
    void end() const;

    Vector2 getPosition() const;
    Vector2 screenToWorld(Vector2 screenPos) const;
    Vector2 worldToScreen(Vector2 worldPos) const;
};
