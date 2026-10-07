#include <iostream> // For cout << and cin >>
#include <vector> // For vectors
using namespace std;

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