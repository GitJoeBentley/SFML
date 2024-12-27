#include "Cat.h"
#include "Constants.h"

Cat::Cat()
{
    catTexture.loadFromFile(CatImageFile);
    setTexture(catTexture);
    // Position the cat

}

Cat::~Cat()
{
    //dtor
}
