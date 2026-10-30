#include <cmath>
#include "animation.h"

Animation::Animation(const std::string &filePath,
                     int frameCount,
                     float frameTime)
    : frameCount(frameCount),
      currentFrame(0),
      frameTime(frameTime),
      frameTimeCounter(0.0f)
{
    texture = LoadTexture(filePath.c_str());

    columns = 4;
    rows = (frameCount + columns - 1) / columns; // Calculate rows from frame count

    frameWidth = static_cast<float>(texture.width) / columns;
    frameHeight = static_cast<float>(texture.height) / rows;
}

Animation::~Animation()
{
    UnloadTexture(texture);
}

void Animation::update(float deltaTime)
{
    frameTimeCounter += deltaTime;

    if (frameTimeCounter >= frameTime)
    {
        frameTimeCounter = 0.0f;
        currentFrame++;

        if (currentFrame >= frameCount)
            currentFrame = 0;
    }
}

void Animation::draw(Vector2 position, float scale) const
{
    int row = currentFrame / columns;
    int column = currentFrame % columns;

    Rectangle source{
        column * frameWidth,
        row * frameHeight,
        frameWidth,
        frameHeight};

    Rectangle destination{
        position.x,
        position.y,
        frameWidth * scale,
        frameHeight * scale};

    Vector2 origin{
        destination.width / 2.0f,
        destination.height / 2.0f};

    DrawTexturePro(texture,
                   source,
                   destination,
                   origin,
                   0.0f,
                   WHITE);
}

void Animation::reset()
{
    currentFrame = 0;
    frameTimeCounter = 0.0f;
}
