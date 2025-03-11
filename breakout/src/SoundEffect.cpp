#include "SoundEffect.h"
#include "constants.h"

SoundEffect::SoundEffect()
{
    soundBuffer[PaddleHitWall].loadFromFile(ResourcesPath + "PaddleHitWall.wav");
    soundBuffer[BallHitWall].loadFromFile(ResourcesPath + "BallHitWall.wav");
    soundBuffer[BallHitTile].loadFromFile(ResourcesPath + "BallHitTile.wav");
    soundBuffer[EndOfGame].loadFromFile(ResourcesPath + "EndOfGame.wav");
    soundBuffer[PaddleMissBall+0].loadFromFile(ResourcesPath + "PaddleMissBall0.wav");
    soundBuffer[PaddleMissBall+1].loadFromFile(ResourcesPath + "PaddleMissBall1.wav");
    soundBuffer[PaddleMissBall+2].loadFromFile(ResourcesPath + "PaddleMissBall2.wav");
    soundBuffer[PaddleMissBall+3].loadFromFile(ResourcesPath + "PaddleMissBall3.wav");

    sound[PaddleHitBall].setBuffer(soundBuffer[PaddleHitBall]);
    sound[PaddleHitWall].setBuffer(soundBuffer[PaddleHitWall]);
    sound[BallHitWall].setBuffer(soundBuffer[BallHitWall]);
    sound[BallHitTile].setBuffer(soundBuffer[BallHitTile]);
    sound[EndOfGame].setBuffer(soundBuffer[EndOfGame]);
    sound[PaddleMissBall+0].setBuffer(soundBuffer[PaddleMissBall+0]);
    sound[PaddleMissBall+1].setBuffer(soundBuffer[PaddleMissBall+1]);
    sound[PaddleMissBall+2].setBuffer(soundBuffer[PaddleMissBall+2]);
    sound[PaddleMissBall+3].setBuffer(soundBuffer[PaddleMissBall+3]);
}

SoundEffect::~SoundEffect()
{
}

