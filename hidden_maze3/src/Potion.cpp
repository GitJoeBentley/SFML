#include "Potion.h"
#include "Constants.h"

Potion::Potion()
{
    potionTexture.loadFromFile(PotionImageFile);
    setTexture(potionTexture);
}
