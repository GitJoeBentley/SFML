#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED
#include <SFML/Graphics.hpp>

const sf::Vector2u RenderWindowSize(1040u, 760u);
const sf::Vector2f MidWindow(static_cast<float>(RenderWindowSize.x) / 2.f, static_cast<float>(RenderWindowSize.y)/2.f);
const sf::Vector2f GameWindowSize(720.0f, 720.0f);
const float TopEdge = GameWindowSize.y / 10.0f;
const float GameBorderWidth = 20.0f;
const std::string ResourcesPath = "../resources/";
const std::string PaddleImageFile = ResourcesPath + "paddle.png";
const std::string TicSoundFile = ResourcesPath + "tic.wav";
const float PaddleSpeed = 660.f;
const sf::Vector2f BallStartPosition(sf::Vector2f(GameWindowSize.x / 2.0f + GameBorderWidth, 0.97f * GameWindowSize.y));
const sf::Vector2f PaddleStartPosition(sf::Vector2f(GameWindowSize.x / 2.0f + GameBorderWidth, 0.995f * GameWindowSize.y));

#endif // CONSTANTS_H_INCLUDED
