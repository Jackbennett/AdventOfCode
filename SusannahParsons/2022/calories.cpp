#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Create a text string, which is used to output the text file
    string caloriesFileContent;

    // Read from the text file
    ifstream inputFile("input.txt");

    vector<int> caloryVector;

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
        caloryVector.push_back(caloryCount);
        cout << caloryCount << "\n";
        elfNumber++;
        caloryCount = 0;
        cout << "Calories elf:" << elfNumber << "\n";
        continue;
      }
      caloryCount = caloryCount + stoi(caloriesFileContent);
    }
    cout << caloryCount << "\n";

    cout << "Elf " << elfToAsk << " had the greatest calories, with " << greatestCalories << "\n";

    //Sort descending order
    sort(caloryVector.begin(), caloryVector.end());

    //Get the last three items
    int finalIndex = caloryVector.size()-1;

    int sumTopThreeCalories = 0;

    for(int i=0; i<3; i++){
        cout << " calory placement " << (i + 1) << ": "  << caloryVector[finalIndex-i] << "\n";
        sumTopThreeCalories = sumTopThreeCalories + caloryVector[finalIndex-i];
    }

    cout << "Total sum of top three calory count : " << sumTopThreeCalories << "\n";

    // Close the file
    inputFile.close();
    return 0;
}
