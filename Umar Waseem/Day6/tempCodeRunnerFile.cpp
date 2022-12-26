#include <bits/stdc++.h>
using namespace std;

char array[26];

int main() {
    string line;
    
    ifstream myfile ("sample.txt");
    
    // read from file

    getline(myfile, line);

    const int N = line.length();
    for (int i = 0; i < 3; i++) {
        set<char> f;
        f.insert(line[i - 1]);
        f.insert(line[i - 2]);
        f.insert(line[i - 3]);
        if( f.size() == 4) {
            cout << i + 1;
        }
    }


    return 0;
}
