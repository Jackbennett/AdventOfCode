#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Create a text string, which is used to output the text file
    string caloriesFileContent;

    // Read from the text file
    ifstream inputFile("input.txt");

    int elfNumber = 1;
    int caloryCount = 0;
    int greatestCalories = 0;
    int elfToAsk = 1;
    cout << "Calories elf:" << elfNumber << "\n";
    // Use a while loop together with the getline() function to read the file line by line
    while (getline (inputFile, caloriesFileContent)) {
      if(caloriesFileContent==""){
        if(greatestCalories < caloryCount){
            greatestCalories = caloryCount;
            elfToAsk = elfNumber;
        }
        cout << caloryCount << "\n";
        elfNumber++;
        caloryCount = 0;
        cout << "Calories elf:" << elfNumber << "\n";
        continue;
      }
      caloryCount = caloryCount + stoi(caloriesFileContent);
    }
    cout << caloryCount << "\n";

    cout << "Elf " << elfToAsk << " had the greatest calories, with " << greatestCalories;

    // Close the file
    inputFile.close();
    return 0;
}
