#include <unordered_set>
#include <deque>
#ifndef CommsDevice_H
#define CommsDevice_H
using namespace std;

class CommsDevice{

public:
    CommsDevice();
    void addSignal(char signal);
    int getStartOfPacketMarkerCompletePosition();
    int getStartOfMessageMarkerPosition();
private:
    const int sizeStartOfPacketMarker = 4;
    const int sizeOfMessageMarker = 14;
    deque<char> mStartOfMessageSignalBuffer;
    deque<char> mStartOfPacketSignalBuffer;
    int mSignalPos;
    int startOfPacketMarkerCompletePosition = 0;
    int startOfMessageMarkerPosition = 0;

    void updateStartOfMessageBuffer(char signal);
    void updateStartOfPacketBuffer(char signal);
    void checkForSignal(int& signalPos, deque<char> signalBuffer, int signalSize, int currentSignalPos);
};

#endif
