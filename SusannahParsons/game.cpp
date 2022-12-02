#include <iostream>
#include <fstream>
using namespace std;

class PlayItem{
    public: int itemScore;
    public: int winItemScore;
    public: string name;
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

};

class Rock : public PlayItem{
    public: Rock(){
        itemScore = 1;
        winItemScore = 3;//Rock wins against scissors
        name = "Rock";
    }

};

class Paper : public PlayItem{
    public: Paper(){
        itemScore = 2;
        winItemScore = 1;//Paper wins against rock
        name = "Paper";
    }
};

class Scissors : public PlayItem{
    public: Scissors(){
        itemScore = 3;
        winItemScore = 2;//Scissors win against paper
        name = "Scissors";
    }
};

PlayItem decodePlay(char code){
    switch(code){
    case 'A':
        return Rock();
    case 'B':
        return Paper();
    case 'C':
        return Scissors();
    case 'X':
        return Rock();
    case 'Y':
        return Paper();
    case 'Z':
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
        PlayItem myPlay = decodePlay(myCode);
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








