#include <iostream>
#include <fstream>
using namespace std;

enum PLAYSCORE{
    ROCKSCORE=1,
    PAPERSCORE=2,
    SCISSORSSCORE=3
};

enum PLAYCODE: char{
    ROCKCODE='A',
    PAPERCODE='B',
    SCISSORSCODE='C'
};

class PlayItem{
    public: int itemScore;
    public: int winItemScore;
    public: string name;
    public: char winCode;
    public: char loseCode;
    public: char drawCode;
    PlayItem(){
    }

    int getScore(PlayItem opponentItem){
        if(opponentItem.itemScore==itemScore){
            //A draw
            return (3 + itemScore);
        }else if(opponentItem.itemScore==winItemScore){
            //A win
            return (6 + itemScore);
        }else{
            //A loss
            return (0 + itemScore);
        }
    }

    char getRiggedItemCode(char code){
        switch(code){
            case 'X':
                return loseCode;
            case 'Y':
                return drawCode;
            case 'Z':
                return winCode;
            default:
                throw invalid_argument("Code doesn't represent anything");
        }
    }

};

class Rock : public PlayItem{
    public: Rock(){
        itemScore = ROCKSCORE;
        winItemScore = SCISSORSSCORE;//Rock wins against scissors
        name = "Rock";
        winCode = PAPERCODE;//paper will win against rock
        loseCode = SCISSORSCODE;//scissors will lose against rock
        drawCode = ROCKCODE;
    }

};

class Paper : public PlayItem{
    public: Paper(){
        itemScore = PAPERSCORE;
        winItemScore = ROCKSCORE;//Paper wins against rock
        name = "Paper";
        winCode = SCISSORSCODE;//scissors will win against paper
        loseCode = ROCKCODE;//rock will lose against paper
        drawCode = PAPERCODE;
    }
};

class Scissors : public PlayItem{
    public: Scissors(){
        itemScore = SCISSORSSCORE;
        winItemScore = PAPERSCORE;//Scissors win against paper
        name = "Scissors";
        winCode = ROCKCODE;//rock will win against scissors
        loseCode = PAPERCODE;//paper will lose against scissors
        drawCode = SCISSORSCODE;
    }
};

PlayItem decodePlay(char code){
    switch(code){
    case ROCKCODE:
        return Rock();
    case PAPERCODE:
        return Paper();
    case SCISSORSCODE:
        return Scissors();
    default:
        throw invalid_argument("Code doesn't represent anything");
    }
}

int main() {
    // Create a text string, which is used to output the text file
    string roundFileContent;

    // Read from the text file
    ifstream inputFile("strategyInput.txt");

    int roundNumber = 1;
    int scoreTally = 0;
    while (getline (inputFile, roundFileContent)) {
        cout << "Round: " << roundNumber << "\n";
        char elfCode = roundFileContent.front();
        char myCode = roundFileContent.back();
        PlayItem elfPlay = decodePlay(elfCode);
        PlayItem myPlay = decodePlay(elfPlay.getRiggedItemCode(myCode));
        cout << "Elf plays " << elfPlay.name << " vs " << " I play " << myPlay.name << "\n";
        int score = myPlay.getScore(elfPlay);
        cout << "score: " << score << "\n";
        scoreTally = scoreTally + score;
        roundNumber++;
    }
    cout << "My total score: " << scoreTally;
    // Close the file
    inputFile.close();
    return 0;
}








