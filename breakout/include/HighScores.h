#ifndef HIGH_SCORES_H
#define HIGH_SCORES_H

#include <set>
#include <ctime>
#include <string>

class Score
{
    char name[16];
    int score;
    std::time_t date;
public:
    Score(const char* n = "no name", int sc = 0, std::time_t t = 0U);
    bool operator<(const Score& obj) const;
    std::string getDateAsString() const;
    friend std::ostream& operator<<(std::ostream& out, const Score& obj);
    int getScore() const { return score; }
};

class HighScores
{
public:
    HighScores(int gameNumber);
    void WriteHighScoresFile();
    bool eligible(int score);
    int getHightestScore() const;
    void updateHighScores(const Score&);

private:
    std::multiset<Score> highScores;
    std::string filename;
    bool highScoresFileExists;
    friend std::ostream& operator<<(std::ostream& out, const HighScores& scores);
};


#endif // HIGH_SCORES_H
