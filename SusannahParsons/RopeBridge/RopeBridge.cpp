#include "RopeBridge.h"
RopeBridge::RopeBridge()
:rope({place(0,0),place(0,0),place(0,0),place(0,0),place(0,0),place(0,0),place(0,0),place(0,0),place(0,0),place(0,0)})//Initialise starting position
{
    //Add start to tail places visited
    place start(0,0);
    tailPlaces.insert(tailPlaces.begin(),start);
}

void RopeBridge::moveHead(char direction, int moves)
{
    switch(direction){
    case 'R':
        for(int i=0; i< moves; i++){
            rope[0].x++;
            moveRope();
        }
        break;
    case 'L':
        for(int i=0; i< moves; i++){
            rope[0].x--;
            moveRope();
        }
        break;
    case 'U':
        for(int i=0; i< moves; i++){
            rope[0].y++;
            moveRope();
        }
        break;
    case 'D':
        for(int i=0; i< moves; i++){
            rope[0].y--;
            moveRope();
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

void RopeBridge::moveRope()
{
    for(int i=1; i<rope.size(); i++){
//        cout << rope[i-1].x << " , " << rope[i-1].y << "\n";
//        cout << "Moving piece " << i << " with respect to " << (i-1) << "\n";
        //0 was the head, the first piece will always be i-1, so start at i=1
        int xDiff = rope[i].x-rope[i-1].x;
        int yDiff = rope[i].y-rope[i-1].y;
//        cout << "xDiff: " << xDiff << " yDiff: " << yDiff << "\n";
        if(abs(xDiff)>1 && abs(yDiff)==0){
            //Move 1 x in rope[i-1] direction
            (xDiff<0) ? rope[i].x++ : rope[i].x--;
        }else if(abs(yDiff)>1 && abs(xDiff)==0){
            //Move 1 y in rope[i-1] direction
            (yDiff<0) ? rope[i].y++ : rope[i].y--;
        }else if((abs(xDiff)>1 && abs(yDiff)>0) || (abs(yDiff)>1 && abs(xDiff)>0)){
            //Diagonal move 1 y and 1 x in rope[i-1] direction
            (xDiff<0) ? rope[i].x++ : rope[i].x--;
            (yDiff<0) ? rope[i].y++ : rope[i].y--;
        }else{
            //rope[i] is still near rope[i-1]
            continue;
        }
    }

//    cout << "Tail moves to x: " << rope[9].x << " y: " << rope[9].y << "\n";
    place newPlace(rope.back().x, rope.back().y);
    tailPlaces.insert(tailPlaces.begin(), newPlace);
}

int RopeBridge::numberTailPlaces()
{
    return tailPlaces.size();
}
void RopeBridge::showPosition()
{
    for(int i = 0; i<rope.size(); i++){
        cout << rope[i].x << "," << rope[i].y << "\n";
    }
}
