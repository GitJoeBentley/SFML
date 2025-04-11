#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <string>

const sf::Vector2u RenderWindowSize(1040u, 760u);
const sf::Vector2f MidWindow(static_cast<float>(RenderWindowSize.x) / 2.f, static_cast<float>(RenderWindowSize.y)/2.f);
const float GameBorderWidth = 20.0f;

const sf::Vector2f GameWindowSize(720.0f, 720.0f);
const float TopEdge = GameWindowSize.y / 10.0f;
const sf::Color Red = sf::Color(0xff1406ff);
const sf::Color Orange = sf::Color(0xffa500ff);
const sf::Color Yellow = sf::Color(0xfaeb36ff);
const sf::Color Green = sf::Color(0x09ff09ff);
const sf::Color Blue = sf::Color(0x080dffff);
const sf::Color Indigo = sf::Color(0x5b46adff);
const sf::Color Violet = sf::Color(0xa349a4ff);
const sf::Color Rose = sf::Color(0xffaec9ff);
const sf::Color LightGreen = sf::Color(0x77ff77ff);
const sf::Color Brown = sf::Color(0xb97a57ff);
const sf::Color RainbowColor[7] = {Red, Orange, Yellow, Green, Blue, Indigo, Violet};
const sf::Color RandomColor[10] = {Red, Orange, Yellow, Green, Blue, Indigo, Violet, Rose, LightGreen, Brown};


const std::string ResourcePath = "../resources/";


const std::string PaddleImageFile = ResourcePath + "paddle.png";
const std::string TicSoundFile = ResourcePath + "tic.wav";
const float PaddleSpeed = 660.f;
const std::vector<std::string> GameName =
    {"Easy Game","Basic Game","One Red Tile","Crazy Ball","The Crusher","Rainbow","Random Tiles","Two Balls","Falling Tiles","150 Tiles","Directions"};
const sf::Vector2f BallStartPosition(sf::Vector2f(GameWindowSize.x / 2.0f + GameBorderWidth, 0.965f * GameWindowSize.y));
const sf::Vector2f PaddleStartPosition(sf::Vector2f(GameWindowSize.x / 2.0f + GameBorderWidth, 0.995f * GameWindowSize.y));

#endif // CONSTANTS_H_INCLUDED
