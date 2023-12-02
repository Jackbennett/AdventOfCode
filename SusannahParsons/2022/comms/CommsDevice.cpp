#include "CommsDevice.h"
#include <iostream>
CommsDevice::CommsDevice()
{
    cout << "Running CommsDevice compiler\n";
    mSignalPos=1;
}


void CommsDevice::addSignal(char signal)
{
    updateStartOfMessageBuffer(signal);
    updateStartOfPacketBuffer(signal);
    //Look for start of packet signal
    checkForSignal(startOfPacketMarkerCompletePosition,mStartOfPacketSignalBuffer,sizeStartOfPacketMarker,mSignalPos);
    checkForSignal(startOfMessageMarkerPosition,mStartOfMessageSignalBuffer,sizeOfMessageMarker,mSignalPos);
    mSignalPos++;
}
int CommsDevice::getStartOfPacketMarkerCompletePosition()
{
    return startOfPacketMarkerCompletePosition;
}
int CommsDevice::getStartOfMessageMarkerPosition()
{
    return startOfMessageMarkerPosition;
}
void CommsDevice::updateStartOfMessageBuffer(char signal)
{
    mStartOfMessageSignalBuffer.push_back(signal);
    if(mStartOfMessageSignalBuffer.size()>sizeOfMessageMarker){
        mStartOfMessageSignalBuffer.pop_front();
    }
}

void CommsDevice::updateStartOfPacketBuffer(char signal)
{
    mStartOfPacketSignalBuffer.push_back(signal);
    if(mStartOfPacketSignalBuffer.size()>sizeStartOfPacketMarker){
        mStartOfPacketSignalBuffer.pop_front();
    }
}
void CommsDevice::checkForSignal(int& signalPos, deque<char>signalBuffer, int signalSize, int currentSignalPos)
{
    if(signalPos==0 && signalBuffer.size()==signalSize){
        //Still searching for start of marker
        //Put the contents of the deque in a set
        unordered_set<char> checkForPacketMarker;
        for (auto it = signalBuffer.cbegin(); it != signalBuffer.cend(); ++it) {
            checkForPacketMarker.insert(*it);
        }
        //If the set contains signalSize values, then this is the marker
        if(checkForPacketMarker.size()==signalSize){
            //Found start of marker.
            signalPos = currentSignalPos;
        }
    }
}
