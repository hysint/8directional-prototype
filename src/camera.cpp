#include <cmath>
#include "camera.h"

GameCamera::GameCamera(Vector2 startPosition, float zoom)
{
    camera.target = startPosition;
    camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = zoom;
    targetPosition = startPosition;
}

void GameCamera::followTarget(Vector2 target, float deltaTime)
{
    float lerpFactor = 1.0f - std::pow(0.5f, smoothSpeed * deltaTime);

    targetPosition.x = targetPosition.x + (target.x - targetPosition.x) * lerpFactor;
    targetPosition.y = targetPosition.y + (target.y - targetPosition.y) * lerpFactor;

    camera.target = targetPosition;
}

void GameCamera::setZoom(float zoom)
{
    camera.zoom = zoom;
}

void GameCamera::begin() const
{
    BeginMode2D(camera);
}

void GameCamera::end() const
{
    EndMode2D();
}

Vector2 GameCamera::getPosition() const
{
    return camera.target;
}

Vector2 GameCamera::screenToWorld(Vector2 screenPos) const
{
    return GetScreenToWorld2D(screenPos, camera);
}

Vector2 GameCamera::worldToScreen(Vector2 worldPos) const
{
    return GetWorldToScreen2D(worldPos, camera);
}
