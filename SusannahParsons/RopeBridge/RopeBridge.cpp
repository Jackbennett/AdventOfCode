#include "RopeBridge.h"
RopeBridge::RopeBridge()
:head(0,0),tail(0,0)//Initialise starting position
{
    //Add start to tail places
    place start(0,0);
    tailPlaces.insert(tailPlaces.begin(),start);
}

void RopeBridge::moveHead(char direction, int moves)
{
    switch(direction){
    case 'R':
        for(int i=0; i< moves; i++){
            head.x++;
            moveTail();
        }
        break;
    case 'L':
        for(int i=0; i< moves; i++){
            head.x--;
            moveTail();
        }
        break;
    case 'U':
        for(int i=0; i< moves; i++){
            head.y++;
            moveTail();
        }
        break;
    case 'D':
        for(int i=0; i< moves; i++){
            head.y--;
            moveTail();
        }
        break;
    };
}

void RopeBridge::testComparePlaces()
{
    cout << "Testing that my set of places works to remove duplicates\n";
    cout << "Head.x > Tail.x, Head.y == Tail.y\nExpect two places in set\n";
    place head(3,2);
    place tail(2,2);
    cout << "Insert first place\n";
    tailPlaces.insert(tailPlaces.begin(), head);
    cout << "Insert second place\n";
    tailPlaces.insert(tailPlaces.begin(), tail);
    cout << "Check size\n";
    cout << (tailPlaces.size()==2) << "\n";

    cout << "Head.x < Tail.x, Head.y == Tail.y\nExpect two places in set because both places are already in there!\n";
    place head2(2,2);
    place tail2(3,2);
    tailPlaces.insert(tailPlaces.begin(), head2);
    tailPlaces.insert(tailPlaces.begin(), tail2);
    cout << (tailPlaces.size()==2) << "\n";

    cout << "Head.y > Tail.y, Head.x == Tail.x\nExpect three places in set\n";
    place head3(2,3);
    place tail3(2,2);
    tailPlaces.insert(tailPlaces.begin(), head3);
    tailPlaces.insert(tailPlaces.begin(), tail3);
    cout << (tailPlaces.size()==3) << "\n";

    cout << "Head.y < Tail.y, Head.x == Tail.x\nExpect four three in set\n";
    place head4(2,2);
    place tail4(2,3);
    tailPlaces.insert(tailPlaces.begin(), head4);
    tailPlaces.insert(tailPlaces.begin(), tail4);
    cout << (tailPlaces.size()==3) << "\n";

    cout << "Head.x == Tail.x, Head.y == Tail.y\nExpect three places in set\n";
    place head5(2,2);
    place tail5(2,2);
    tailPlaces.insert(tailPlaces.begin(), head5);
    tailPlaces.insert(tailPlaces.begin(), tail5);
    cout << (tailPlaces.size()==3) << "\n";


}

void RopeBridge::moveTail()
{
//    cout << "Head moves to x: " << head.x << " y: " << head.y << "\n";
    int xDiff = tail.x-head.x;
    int yDiff = tail.y-head.y;
//    cout << "Difference in x " << xDiff << " difference in y " << yDiff << "\n";
    if(abs(xDiff)>1 && abs(yDiff)==0){
        //Move 1 x in head direction
        (xDiff<0) ? tail.x++ : tail.x--;
    }else if(abs(yDiff)>1 && abs(xDiff)==0){
        //Move 1 y in head direction
        (yDiff<0) ? tail.y++ : tail.y--;
    }else if((abs(xDiff)>1 || abs(yDiff)>1) && (abs(xDiff)==1  || abs(yDiff)==1)){
        //Diagonal move 1 y and 1 x in head direction
//        cout << "Diagonal move. xDiff: " << xDiff << " yDiff: " << yDiff << "\n";
        (xDiff<0) ? tail.x++ : tail.x--;
        (yDiff<0) ? tail.y++ : tail.y--;
    }else{
        //tail is still near head
//        cout << "Tail doesn't move\n";
        return;
    }
//    cout << "Tail moves to x: " << tail.x << " y: " << tail.y << "\n";
    place newPlace(tail.x, tail.y);
    tailPlaces.insert(tailPlaces.begin(), newPlace);
}

int RopeBridge::numberTailPlaces()
{
    return tailPlaces.size();
}
