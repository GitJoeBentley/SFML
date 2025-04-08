#include "SoundEffect.h"
#include "constants.h"

SoundEffect::SoundEffect()
{
    soundBuffer[PaddleHitWall].loadFromFile(ResourcePath + "PaddleHitWall.wav");
    soundBuffer[BallHitWall].loadFromFile(ResourcePath + "BallHitWall.wav");
    soundBuffer[BallHitTile].loadFromFile(ResourcePath + "BallHitTile.wav");
    soundBuffer[EndOfGame].loadFromFile(ResourcePath + "EndOfGame.wav");
    soundBuffer[PaddleMissBall+0].loadFromFile(ResourcePath + "PaddleMissBall0.wav");
    soundBuffer[PaddleMissBall+1].loadFromFile(ResourcePath + "PaddleMissBall1.wav");
    soundBuffer[PaddleMissBall+2].loadFromFile(ResourcePath + "PaddleMissBall2.wav");
    soundBuffer[PaddleMissBall+3].loadFromFile(ResourcePath + "PaddleMissBall3.wav");

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

