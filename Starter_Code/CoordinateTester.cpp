#include <iostream> // For cout << and cin >>
#include <vector> // For vectors
using namespace std;

// Structure to create all valid game coordinates
struct Coordinate{
    
    // TODO: Impliment the Coordinate structure
    
};

// Global vector of valid coordinates

// TODO: Create Global variable gameGridCoords

// Function to create the game grid coordinate structures
void createCoordinates(){
    
    // TODO: Create function to create the game grid coordinates and add them into the global variable
    
}

int main(){
    
    createCoordinates();
    
    Coordinate c1(0, 0);
    Coordinate c2(9, 9);
    
    cout << "Coordinate one has a row value of " << c1.getRow() << ", a column value of " << c1.getCol() << " and a string value of " << c1.getCoords() << "." << endl;
    cout << "Coordinate Two has a row value of " << c2.getRow() << ", a column value of " << c2.getCol() << " and a string value of " << c2.getCoords() << "." << endl;
    
    cout << "The game grid has a total size of " << gameGridCoords.size() << " coodinates." << endl;
    
    /*
    
    Correct Output:
    
    Coordinate one has a row value of 0, a column value of 0 and a string value of A1.
    Coordinate Two has a row value of 9, a column value of 9 and a string value of J10.
    The game grid has a total size of 100 coodinates.
    
    */
    
    return 0;
}