#include "Mapper.h"
Mapper::Mapper(string fileName, int rowToCheck, int newmaxXY)
:maxXY(newmaxXY)
{
    ifstream inputStream(fileName);
    string fileLine;
    while(getline(inputStream, fileLine)){
        char char_array[fileLine.size() + 1];
        strcpy(char_array, fileLine.c_str());
        char * stringItem;
        int itemNumber = 1;
        stringItem = strtok (char_array," ,=:");
        Sensor* sensor = new Sensor();
        Beacon* beacon = new Beacon();
        while (stringItem != NULL)
        {
            //Item 4 is sensor->x Item 6 is sensor->y, 12 is beacon->x, 14 is beacon->y
            if(itemNumber==4){
                sensor->x = stoi(string(stringItem));
            }
            if(itemNumber==6){
                sensor->y = stoi(string(stringItem));
            }
            if(itemNumber==12){
                beacon->x = stoi(string(stringItem));
            }
            if(itemNumber==14){
                beacon->y = stoi(string(stringItem));
            }
            itemNumber++;
            stringItem = strtok (NULL, " ,=:");
        }
        sensor->nearestBeacon = *beacon;
        sensors.insert(sensors.end(),*sensor);
        beacons.insert(beacons.end(),*beacon);
        delete sensor;
        delete beacon;
        sensor = new Sensor();
        beacon = new Beacon();
    }
    cout << "Sensors and beacons initialised\n";

//    set<int> cover = amountSensorsCoverRow(rowToCheck);//Part 1 answer
//    //Remove beacons
//    for(auto beacon : beacons){
//        if(beacon.y==rowToCheck){
//            cover.erase(beacon.x);
//        }
//    }
//    //Everything else we know there are no beacons
//    cout << "There are " << cover.size() << " tiles with definitely no beacons.\n";

    //Check using limits rather than each square
    //Iterate rows
    for(int row=minXY; row<=maxXY; row++){
        variant<int,bool> gapx = findGapInCoverage(row);
        if(holds_alternative<int>(gapx)){
            uint64_t col = get<int>(gapx);
            cout << "Found beacon! x " << col << " y " << row << "\n";
            cout << "Tuning frequency: " << (col * 4000000 + row) << "\n";
            break;
        }
    }
}

variant<int,bool> Mapper::findGapInCoverage(int rowy)
{
    set<Range> ranges;
    for(auto sensor: sensors){
        if(sensor.coversRow(rowy)){
            Range newRange = sensor.getXRangeCovered(rowy);
            //Keep values within limits
            newRange.minVal = (newRange.minVal < minXY) ? minXY : newRange.minVal;
            newRange.maxVal = (newRange.maxVal > maxXY) ? maxXY : newRange.maxVal;
            ranges.insert(ranges.end(),newRange);
        }
    }
    set<Range> mergedRanges;
    //How to merge the ranges?
    Range mergedRange = *ranges.begin();
    for(auto range : ranges){
        if(mergedRange.hasOverlap(range)){
            mergedRange = get<Range>(mergedRange.mergeRange(range));
        }else{
            //There's a gap!! We know there is only one, so just add one to the first range max and return
            return mergedRange.maxVal + 1;
        }
    }
    return false;
}

set<int> Mapper::amountSensorsCoverRow(int rowy)
{
    set<int> rowXCovered;
    for(auto sensor: sensors){
        int colX = sensor.x;
        //Check left
        while(sensor.pointInRange(Location(colX, rowy))){
            rowXCovered.insert(rowXCovered.end(), colX);
            colX--;
        }
        //Check right
        colX = sensor.x+1;
        while(sensor.pointInRange(Location(colX, rowy))){
            rowXCovered.insert(rowXCovered.end(), colX);
            colX++;
        }
    }
    return rowXCovered;
}
