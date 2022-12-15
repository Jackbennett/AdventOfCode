#include "PacketPair.h"
PacketPair::PacketPair(string newleft)
{
    left = PacketList(newleft);
}

PacketPair::PacketPair()
{

}


variant<bool, size_t> PacketPair::correctOrder()
{
    while(true){
        //Get the equivalent items from the list
        variant<int, string, size_t> leftItem = left.getItem();
        variant<int, string, size_t> rightItem = right.getItem();
        if(holds_alternative<size_t>(leftItem) && holds_alternative<size_t>(rightItem)){
            return string::npos;
        }
        if(holds_alternative<size_t>(leftItem)){
            //Left finished first, order is correct
            return true;
        }
        if(holds_alternative<size_t>(rightItem)){
            //Right finished first, order is incorrect
            return false;
        }
        if(holds_alternative<int>(leftItem) && holds_alternative<int>(rightItem)){
            int li = get<int>(leftItem);
            int ri = get<int>(rightItem);
            if(li <  ri){
                return true;
            }else if(li > ri){
                return false;
            }//Carry on if ints are equal
        }
        if(holds_alternative<string>(leftItem) && holds_alternative<int>(rightItem)){
            string leftStringItem = get<string>(leftItem);
            variant<int, string, size_t> newRight = "[" + to_string(get<int>(rightItem)) + "]";
            rightItem = newRight;
        }
        if(holds_alternative<int>(leftItem) && holds_alternative<string>(rightItem)){
            string rightStringItem = get<string>(rightItem);
            variant<int, string, size_t> newLeft = "[" + to_string(get<int>(leftItem)) + "]";
            leftItem = newLeft;
        }
        if(holds_alternative<string>(leftItem) && holds_alternative<string>(rightItem)){
            //Both are now lists, recursive compare
            PacketPair pp;
            pp.left = PacketList(get<string>(leftItem));
            pp.right = PacketList(get<string>(rightItem));
            //Recursive call
            variant<bool, size_t> isCorrect = pp.correctOrder();
            if(holds_alternative<bool>(isCorrect)){
                bool orderIsCorrect = get<bool>(isCorrect);
                if(orderIsCorrect){
                    return true;
                }else{
                    return false;
                }
            }
        }
    }
}

string PacketPair::toString() const
{
    string plString = "(";
    for (auto & stringItem : left.listContent) {
            plString += stringItem + ",";
    }
    plString.erase(plString.size()-1);//Remove trailing comma
    plString += "   ,   ";
    for (auto & stringItem : right.listContent) {
            plString += stringItem + ",";
    }
    plString.erase(plString.size()-1);//Remove trailing comma
    plString += ")";
    return plString;
}
