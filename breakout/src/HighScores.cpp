// #define _CRT_SECURE_NO_WARNINGS

#include "HighScores.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include "constants.h"


Score::Score(const char* n, int sc, time_t t)
    : score(sc), date(t)
{
    std::strcpy(name,n);
}

bool Score::operator<(const Score& obj) const
{
    return score > obj.score;  // display in reverse order
}

std::string Score::getDateAsString() const
{
    tm* ptr2tm = localtime(&date);
    std::string datestring = std::to_string(ptr2tm->tm_mon + 1);
    datestring += '/';
    datestring += std::to_string(ptr2tm->tm_mday);
    datestring += '/';
    datestring += std::to_string((ptr2tm->tm_year + 1900) % 100);
    return datestring;
}

std::ostream& operator<<(std::ostream& out, const Score& obj)
{
    std::string temp(obj.name);
    out << std::left << std::setw(16) << temp.substr(0,15)
        << std::right << std::setw(3) << obj.score
        << std::setw(10) << obj.getDateAsString() << std::endl;
    return out;
}

////////////////  HighScores functions ////////////////////

HighScores::HighScores(int gameNumber)
    : filename(ResourcesPath + "highscores" + std::to_string(gameNumber) + ".bin"), highScoresFileExists(true)
{
    std::ifstream fin(filename,std::ios_base::binary);
    if (!fin)
    {
        std::cout << "Can't find high scores file, " << filename << ".  I'll create a new one." << std::endl;
        highScoresFileExists = false;
    }
    else
    {
        Score temp;
        while (fin.read(reinterpret_cast<char*>(&temp),sizeof(temp)))
        {
            highScores.insert(temp);
        }
        fin.close();
    }
}

void HighScores::updateHighScores(const Score& obj)
{
    highScores.insert(obj);
    if (highScores.size() > 10)
    {
        highScores.erase(--highScores.end());
    }
}

bool HighScores::eligible(int score)
{
    //Score is eligible for high scores if less than 10 scores on the list or score is  the lowest score on the list
    //std::cout << "*highscores.cbegin() = " << *(highScores.cbegin()) << std::endl;
    //std::cout << "*highscores.crbegin() = " << *(highScores.crbegin()) << std::endl;
    //std::cout << "highscores.crbegin()->getScore() = " << highScores.crbegin()->getScore() << std::endl;
    if (highScores.size() < 10) return true;
    if ( score > highScores.crbegin()->getScore()) return true;
    return false;
}

int HighScores::getHightestScore() const
{
    return highScores.cbegin()->getScore();
}

void HighScores::WriteHighScoresFile()
{
    std::ofstream fout(filename,std::ios_base::binary);

    auto count = 0;
    for (auto it = highScores.cbegin(); it != highScores.cend(); ++it, ++count )
    {
        if (count == 10)
            break;
        fout.write(reinterpret_cast<const char*>(&*it),sizeof(*it));
    }
    fout.close();
}

std::ostream& operator<<(std::ostream& out, const HighScores& scores)
{
    if (scores.highScores.size() < 1)
        out << "No high scores recorded" << std::endl;
    else
    {
        out << "\n   ********* High Scores *********" << std::endl << std::endl;
        out << "     Name          Score      Date" << std::endl;
        auto count = 1;
        for (auto it = scores.highScores.cbegin(); it != scores.highScores.cend(); ++it, ++count )
        {
            if (count == 11)
                break;
            out << std::right << std::setw(4) << count << ' ' <<  *it;
        }
    }
    return out;
}
