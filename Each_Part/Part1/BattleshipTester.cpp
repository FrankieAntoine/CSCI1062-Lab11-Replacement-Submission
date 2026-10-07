#include <iostream> // For cout << and cin >>
#include <vector> // For vectors
using namespace std;

// Pre definitions

    // TODO: Copy code implimentations from CoordinateTester.cpp after part 1 to test part 2


// Class for the battleships
class Battleship{
    
    // TODO: Impliment the battleship class
    
};

int main(){
    
    createCoordinates();
    
    Battleship b1(1, 2);
    Coordinate c1(0, 0);
    Coordinate c2(1, 0);
    
    if (!b1.getPlaced()){
        cout << "This battleship, battleship number " << b1.getNumber() << ", has a length of " << b1.getLength() << " and is not placed." << endl;
    }
    
    b1.addLocationCoord(c1.getRow(), c1.getCol());
    b1.addLocationCoord(c2.getRow(), c2.getCol());
    b1.setPlaced();
    
    if (b1.getPlaced()){
        cout << "This battleship has the starting coordinates of " << b1.getLocation()[0]->getCoords() << ", and the ending coordinates of " << b1.getLocation()[1]->getCoords() << " and is now placed" << endl;
    }
    
    cout << "Suddenly an enemy ship attacked ship number " << b1.getNumber() << "!" << endl;
    
    b1.setSunk();
    b1.clearLocation();
    
    if ((b1.getLocation().size() == 0) && (b1.getSunk())){
        cout << "Ship Number "<< b1.getNumber() <<" is sunk!" << endl;
    }
    
    /*
    
    Correct Output:
    
    This battleship, battleship number 1, has a length of 2 and is not placed.
    This battleship has the starting coordinates of A1, and the ending coordinates of A2 and is now placed
    Suddenly an enemy ship attacked ship number 1!
    Ship Number 1 is sunk!
    
    */
    
    return 0;
}

