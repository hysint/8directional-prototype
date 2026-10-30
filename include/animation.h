#pragma once
#include <raylib.h>
#include <string>

class Animation
{
private:
    Texture2D texture{};
    int frameCount{};
    int columns{4};
    int rows{};

    int currentFrame{};

    float frameTime{};
    float frameTimeCounter{};

    float frameWidth{};
    float frameHeight{};

public:
    Animation(const std::string &filePath,
              int frameCount,
              float frameTime);

    ~Animation();

    void update(float deltaTime);
    void draw(Vector2 position, float scale) const;
    void reset();
};
