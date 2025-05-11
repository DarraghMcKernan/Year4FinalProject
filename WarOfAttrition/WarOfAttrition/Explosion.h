#pragma once
#include "globals.h"

class Explosion {
public:
    Explosion(sf::Vector2f t_spawnPos)
    {
        position = t_spawnPos;
        totalLifetime = static_cast<float>((rand() % 40) + 60) / 100.0f;//0.6 to 1 second
        delay = static_cast<float>(rand() % 60) / 100.0f;//0 to 0.6 seconds
        currentTime = 0.0f;
        started = false;
        frameCount = 5;
        animationSpeed = totalLifetime / frameCount;

        explosion.setTexture(explosionTexture);
        explosion.setTextureRect(sf::IntRect(0, 0, 64, 64));
        explosion.setOrigin(64 / 2.f, 64 / 2.f);
        explosion.setPosition(position);

        float scale = static_cast<float>(rand() % 75 + 25) / 100.0f;//.25 to 1
        explosion.setScale(scale, scale);
    }

    void update(float deltaTime)
    {
        if (started == false)
        {
            delay -= deltaTime;
            if (delay <= 0.0f)
            {
                started = true;
                delay = 0.0f;
            }
            else return;
        }

        currentTime += deltaTime;
        float spritesheetProgress = currentTime / totalLifetime;
        int currentFrame = static_cast<int>(spritesheetProgress * frameCount);
        currentFrame = std::min(currentFrame, frameCount - 1);

        explosion.setTextureRect(sf::IntRect(currentFrame * 64, 0, 64, 64));
    }

    void draw(sf::RenderWindow& window)
    {
        if (started == true && isComplete() == false)
        {
            window.draw(explosion);
        }
    }

    bool isComplete()
    {
        if (currentTime >= totalLifetime)
        {
            return true;
        }
        return false;
    }

private:
    sf::Vector2f position;
    sf::Sprite explosion;
    sf::Vector2i frameSize;
    int frameCount;
    float totalLifetime;
    float currentTime;
    float delay;
    float animationSpeed;
    bool started;
};