#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <string>

const float CellWidth = 20.0f;

const sf::Vector2u GameSize(1000, 1000);
const sf::Vector2f MidWindow(GameSize.x / 2.0f, GameSize.y / 2.0f);
const sf::Vector2f BottomWindow(GameSize.x / 2.0f, 8.5f * GameSize.y / 10.0f);
const sf::Vector2f TopWindow(GameSize.x / 2.0f, 0.5f * GameSize.y / 10.0f);
const sf::Vector2f CellSize(CellWidth, CellWidth);

const int NumRows = 40;
const int NumCols = NumRows;
const float GameWindowSize = NumRows * CellWidth;
const float WindowHorizontalOffset = 100.0f;
const float WindowVerticalOffset = 150.0f;

const std::vector<std::string> FontNames = {"arial","courier","komikap","kristan","showcard"};

const std::string ResourcePath = "resources/";
const std::string BorderImageFile = ResourcePath + "bricks.jpg";
const std::string PlayerImageFile = ResourcePath + "player.jpg";
const std::string ArrowImageFile = ResourcePath + "arrow.jpg";
const std::string ButtonImageFile = ResourcePath + "buttons.png";
const std::string ContinueImageFile = ResourcePath + "continue.png";
const std::string OpeningImageFile = ResourcePath + "opening_background.png";
const std::string CatImageFile = ResourcePath + "cat.png";

const std::string MusicStartFile = ResourcePath + "start.ogg";
const std::string StartSoundFile = ResourcePath + "start_sound.ogg";

const std::string ArialFile = ResourcePath + "arial.ttf";
const std::string CourierFile = ResourcePath + "courier.ttf";
const std::string KristanFile = ResourcePath + "kristan.ttf";
const std::string KomikapFile = ResourcePath + "komikap.ttf";

const std::string RubberSoundFile = ResourcePath + "bounce.wav";
const std::string StepSoundFile = ResourcePath + "step.wav";
const std::string HitWallSoundFile = ResourcePath + "slam.wav";
const std::string LossSoundFile = ResourcePath + "loss.wav";
const std::string WinSoundFile = ResourcePath + "win.wav";
const std::string BombSoundFile = ResourcePath + "explosion.wav";
const std::string FartSoundFile = ResourcePath + "fart.wav";
const std::string LightSoundFile = ResourcePath + "light.wav";
const std::string TickSoundFile = ResourcePath + "tick.wav";
const std::string CatSoundFile = ResourcePath + "cat.wav";

const std::string HowToPlayFile = ResourcePath + "howtoplay.txt";

#endif
