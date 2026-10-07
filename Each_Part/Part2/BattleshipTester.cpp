#include <iostream> // For cout << and cin >>
#include <vector> // For vectors
using namespace std;

// Pre definitions

// Structure to create all valid game coordinates
struct Coordinate{
    private:
        int x;
        int y;
        string coords;
    public:
        Coordinate(int x, int y) : x(x), y(y) {
            coords = (char)(y + 65) + to_string(x+1);
        }
        int getCol(){
            return x;
        }
        int getRow(){
            return y;
        }
    
        string getCoords(){
            return coords;
        }
};

// Global vector of valid coordinates
vector<Coordinate*> gameGridCoords;

// Function to create the game grid coordinate structures
void createCoordinates(){
    if (gameGridCoords.empty()){
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                Coordinate* gameCoords = new Coordinate(j, i);
                gameGridCoords.push_back(gameCoords);
            }
        }
    }
}

// Class for the battleships
class Battleship{
    private:
        int length;
        int number;
        vector<Coordinate*> location;
        bool placed = false;
        bool sunk = false;
    public:
        Battleship(int n, int l) : number(n), length(l) {}
    
        int getLength(){
            return length;
        }
    
        int getNumber(){
            return number;
        }
    
        void setPlaced(){
            placed = true;
        }
        
        bool getPlaced(){
            return placed;
        }
    
        void setSunk(){
            sunk = true;
        }
        
        bool getSunk(){
            return sunk;
        }
    
        vector<Coordinate*> getLocation(){
            return location;
        }
    
        void clearLocation(){
            location.clear();
        }
    
        void addLocationCoord(int row, int col){
            for (int i = 0; i < 100; i++){
                if ((gameGridCoords[i]->getRow() == row) && (gameGridCoords[i]->getCol() == col)){
                    location.push_back(gameGridCoords[i]);
                }
            }
        }
    
        
        
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

