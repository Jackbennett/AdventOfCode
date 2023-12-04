#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class CleanupPair{
    public:
        vector<int> elf1Sections;
        vector<int> elf2Sections;
        int shortSectionStart;
        int shortSectionEnd;
        int longSectionStart;
        int longSectionEnd;
        CleanupPair(string sectionInfo){
            string firstSection = sectionInfo.substr(0, sectionInfo.find(','));
            string secondSection = sectionInfo.substr(sectionInfo.find(',')+1);
            elf1Sections = getSectionFromString(firstSection);
            elf2Sections = getSectionFromString(secondSection);
            if(elf1Sections.size()>elf2Sections.size()){
                longSectionStart = elf1Sections.front();
                longSectionEnd = elf1Sections.back();
                shortSectionStart = elf2Sections.front();
                shortSectionEnd = elf2Sections.back();
            }else{
                longSectionStart = elf2Sections.front();
                longSectionEnd = elf2Sections.back();
                shortSectionStart = elf1Sections.front();
                shortSectionEnd = elf1Sections.back();
            }
        }
        bool oneRangeContainsOther(){
            return longSectionStart<=shortSectionStart && longSectionEnd >= shortSectionEnd;
        }
        bool rangesOverlap(){
            vector<int> intersectionFirstTwo;
            //Sections are already sorted, so should be ok to go straight on with set_intersection
            set_intersection(elf1Sections.begin(), elf1Sections.end(),
                          elf2Sections.begin(), elf2Sections.end(),
                          back_inserter(intersectionFirstTwo));
            return intersectionFirstTwo.size() > 0;
        }
    private:
        vector<int> getSectionFromString(string section){
            int startSection = stoi(section.substr(0, section.find('-')));
            int endSection  = stoi(section.substr(section.find('-')+1));
            vector<int> newSection(endSection-startSection+1);
            generate(newSection.begin(), newSection.end(),
                         [i=startSection]() mutable {
                            return i++;
                         }
                     );
            return newSection;
        }
};

runCleanup(ifstream & inputFile, string fileContent){
    int tallyPairsWithContainingRange = 0;
    int tallyRangesOverlap = 0;
    while (getline (inputFile, fileContent)) {
        CleanupPair newElfPair(fileContent);
        if(newElfPair.oneRangeContainsOther()){
            tallyPairsWithContainingRange++;
        }
        if(newElfPair.rangesOverlap()){
            tallyRangesOverlap++;
        }
    }
    cout << "Pairs in which one range is fully contained by the other " << tallyPairsWithContainingRange;
    cout << "Pairs which have an overlap " << tallyRangesOverlap;
}

int main() {
    string fileContent;
    // Read from the text file
    ifstream inputFile("cleanupInput.txt");
    runCleanup(inputFile, fileContent);
    // Close the file
    inputFile.close();
    return 0;
}
