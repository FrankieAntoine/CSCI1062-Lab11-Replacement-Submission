#include <iostream> // For cout << and cin >>
#include <algorithm> // For Find()
#include <vector> // For vectors
#include <unistd.h> // for sleep()
using namespace std;

// Pre definitions for code to work
class Battleship;
class Grid;
void displayGrid(Grid* grid);
bool changeChar(Grid* grid, int row, int col, char modifier, bool overrideVar = false);
pair <int, int> coordinateInterpreter(string coords);
bool placeShipOnGrid(Grid* grid, Battleship* battleship, string coordinateOne, string coordinateTwo);
bool battleShipPlacementCheck(string coordInputOne, string coordInputTwo, int lengthOfShip);
int obtainUserInputInt(string message = "");
string obtainUserInputCoord(string message = "");
bool validCoordCheck(string coord);

// Function to clear the screen
void clearScreen(){
    cout << "\033[2J\033[1;1H";
}

// Function to give a one second pause
void oneSecDelay(){
    sleep(1);
}

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

// Class representing a single row of the grid
class Row {
    char* data; // pointer to a row
public:
    Row(char* d) : data(d) {}
    char& operator[](int col) { return data[col]; }
};

// Class ro represent all of the grids in the game
class Grid {
    char arr[10][10]; // fixed size 10x10 grid
public:
    Grid() {
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                arr[i][j] = '.';
    }

    Row operator[](int row) { return Row(arr[row]); }
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

// class for the players
class Player{
    private:
        string name;
        vector<Battleship*> battleships;
        vector<Coordinate*> hitSpaces;
        Grid fullGrid;
        Grid hiddenGrid;
        
    public:
        Player(string n) : name(n) {}
    
        string getName(){
            return name;
        }
    
        Grid* getGrid(int type = 0){
            if (type == 1){
                return &fullGrid;
            }
            return &hiddenGrid;
        }
    
        vector<Battleship*> getShips(){
            return battleships;
        }
        
        vector<Battleship*> getAvalShips(){
            vector<Battleship*> avalShips;
            for (int i = 0; i < battleships.size(); i++){
                if (!battleships[i]->getPlaced()){
                    avalShips.push_back(battleships[i]);
                }
            }
            return avalShips;
        }
    
        Battleship* getShip(int shipNumber){
            return battleships[shipNumber-1];
        }
    
        void addShip(Battleship* battleship){
            battleships.push_back(battleship);
        }
    
        vector<Coordinate*> getHitSpaces(){
            return hitSpaces;
        }
        
        // Main player turn function
        string turn(Player* enemy){
            displayGrid(enemy->getGrid());
            bool flag = false;
            string userInput;
            Coordinate* hitSpace;
            while (!flag){
                cout << name << ", what space would you like to shoot at?" << endl;
                cin >> userInput;
                userInput[0] = toupper(userInput[0]);
                for (int i = 0; i < gameGridCoords.size(); i++){
                    if (userInput == gameGridCoords[i]->getCoords()){
                        hitSpace = gameGridCoords[i];
                        flag = true;
                    }
                }
                for (int i = 0; i < hitSpaces.size(); i++){
                    if (hitSpaces[i]->getCoords() == userInput){
                        cout << "SPACE PREVIOUSLY SELECTED: ";
                        flag = false;
                    }
                }
                if (!flag){
                    cout << "INVALID COORDINATE INPUT" << endl;
                    oneSecDelay();
                }
            }
            hitSpaces.push_back(hitSpace);
            return userInput;
            
        }
    
        void placeShip(Battleship* battleship){
            string coordInputOne = "";
            string coordInputTwo = "";
            bool flag = false;
            
            displayGrid(getGrid(1));
            
            
            
            while (flag == false){
                coordInputOne = obtainUserInputCoord(name + ", enter the starting coordinates ship number " 
                                                          + to_string(battleship->getNumber()) + ", the " 
                                                          + to_string(battleship->getLength()) 
                                                          + " long ship (Eg. 'A1'): ");
                
                flag = validCoordCheck(coordInputOne);
                if (flag){
                    auto [y, x] = coordinateInterpreter(coordInputOne);
                    if (!(changeChar(getGrid(1), y, x, (battleship->getNumber() + '0')))){
                        flag = false;
                    }
                }
                if (!flag){
                    cout << "ERROR: INVALID INPUT" << endl;
                }
            }
                    
                
            
            displayGrid(getGrid(1));
            flag = false;
            
            while (flag == false){
                coordInputTwo = obtainUserInputCoord(name + ", enter the ending coordinates ship number " 
                                                          + to_string(battleship->getNumber()) + ", the " 
                                                          + to_string(battleship->getLength()) 
                                                          + " long ship"
                                                          + " starting at " + coordInputOne);
                
                if (validCoordCheck(coordInputTwo)){
                    if (battleShipPlacementCheck(coordInputOne, coordInputTwo, battleship->getLength())){
                        auto [y, x] = coordinateInterpreter(coordInputTwo);
                        if (!(changeChar(getGrid(1), y, x, (battleship->getNumber() + '0')))){
                            flag = false;
                        }
                        
                        else{flag = true;}
                        
                        if (!(placeShipOnGrid(getGrid(1), battleship, coordInputOne, coordInputTwo))){
                            flag = false;
                        }
                    }
                }
                
                if (!flag){
                    cout << "ERROR: INVALID INPUT" << endl;
                }
            }
        
        }
};

// Function to obtain user input for integers
int obtainUserInputInt(string message){
    cout << message << endl;
    
    string userInput = "";
    int number = 0;
    
    cin >> userInput;
    
    try{
        number = stoi(userInput);

    } catch(const std::invalid_argument& e){
        cout << "Invalid Input, try again" << endl;
        oneSecDelay();
    }
    
    return number;
}

// Function to obtain user input for coordinates
string obtainUserInputCoord(string message){
    cout << message << endl;
    
    string coord = "";
    
    cin >> coord;
    coord[0] = toupper(coord[0]);
    
    return coord;
}

// Function to check if valid coordinate
bool validCoordCheck(string coord){
    for (int i = 0; i < gameGridCoords.size(); i++){
        if (coord == gameGridCoords[i]->getCoords()){
            return true;
        }
    }
    cout << "Invalid Coordinate!" << endl;
    oneSecDelay();
    return false;
}

// Function that interptets user coordinate input
pair <int, int> coordinateInterpreter(string coord){
    
    int y = (((int)coord[0]) - 65);
    int x = stoi(coord.substr(1)) - 1;
    
    return {y, x};
}

// Function to change a character in a given grid griven a row, col, and modifier
bool changeChar(Grid* grid, int row, int col, char modifier, bool overrideVar){
    if (!overrideVar){
        if (((*grid)[row][col] == '.') || ((*grid)[row][col] == modifier)){
            (*grid)[row][col] = modifier;
            return true;
        }
        else{
            cout << "ERROR: INVALID GRID PLACEMEMNT" << endl;
            oneSecDelay();
            return false;
        }
    }else{
        (*grid)[row][col] = modifier;
        return true;
    }
    
}

// Function to rid a grid of a given character
void purgeChar(Grid* grid, char purgedChar, char modifier = '.'){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if ((*grid)[i][j] == purgedChar){
                (*grid)[i][j] = modifier;
            }
        }
    }
}

// Function to find a given character
bool findChar(Grid* grid, char it){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if ((*grid)[i][j] == it){
                return true;
            }
        }
    }
    return false;
}

// Function to display to the user how many ships they still must place at the start of the game
void displayAvailableShips(vector<Battleship*> battleships){
    cout << "Ship Storage: " << endl;
    for (int i = 0; i < battleships.size(); i++){
        cout << "Ship number: " << battleships[i]->getNumber() << "; length: ";
        for (int j = 0; j < battleships[i]->getLength(); j++){
            cout << battleships[i]->getNumber();
        }
        cout << endl;
    }
    cout << endl;
}

// Function to add ship objects to the players
void setUpGrid(Player* player, vector<int> ships){
    for (int i = 0; i < ships.size(); i++){
        Battleship* newShip = new Battleship(i+1, ships[i]);
        player->addShip(newShip);
    }
    
    int shipNumberInput;
    
    while(true){
        displayGrid(player->getGrid(1));
        if (player->getAvalShips().size() != 0){
            displayAvailableShips(player->getAvalShips());
            shipNumberInput = obtainUserInputInt(player->getName() + ", enter the number of the ship you'd like to place: ");
        } else{
            shipNumberInput = obtainUserInputInt(player->getName() + " This is your grid, enter -1 to continue"
                            + " or the ship number of the ship you would like to re-place. (ex. 2)");
        }
        
        if ((shipNumberInput == -1) && (ships.size() == 0)){
            break;
        }
        else if ((shipNumberInput > 0) && (shipNumberInput <= (player->getShips().size()))){
            if (findChar(player->getGrid(1), (player->getShip(shipNumberInput)->getNumber() + '0'))){
                ships.push_back(player->getShip(shipNumberInput)->getLength());
            }
            purgeChar(player->getGrid(1), (player->getShip(shipNumberInput)->getNumber() + '0'));
            player->placeShip(player->getShip(shipNumberInput));
            
            auto it = find(ships.begin(), ships.end(), player->getShip(shipNumberInput)->getLength());
            if (it != ships.end()) {
                ships.erase(it);
            } else {
                cout << "Internal error: ship length not found" << endl;
                oneSecDelay();
            }
            
            player->getShip(shipNumberInput)->setPlaced();
        }
        
    }
}

// Function to display the given players grid
void displayGrid(Grid* grid){
    
    clearScreen();
    cout << "     ";
    
    for (int i = 1; i < 11; i++){
        if (i >= 10){
            cout << " " << "[0" << i << ']' << endl << endl;
        }
        else{
            cout << " " << "[00" << i << ']';
        }
        
    }
    for (int i = 0; i < 10; i++){
        cout << " [" << (char)(i + 65) << "] ";
        for (int j = 0; j < 10; j++){
            cout << "   " << (*grid)[i][j] << "  ";
            if (j == 9){
                cout << endl << endl;
            }
        }
    }
}

// Function to check if a valid second coordinate has been inputed
bool battleShipPlacementCheck(string coordInputOne, string coordInputTwo, int lengthOfShip){
    
    auto [y1, x1] = coordinateInterpreter(coordInputOne);
    auto [y2, x2] = coordinateInterpreter(coordInputTwo);
    
    if (y1 == y2){
        if (abs(x1 - x2) == lengthOfShip - 1){return true;}
    }
    
    else if(x1 == x2){
        if (abs(y1 - y2) == lengthOfShip - 1){return true;}
    }
    
    return false;
}

// Funtion to modify the grid for a ship
bool placeShipOnGrid(Grid* grid, Battleship* battleship, string coordinateOne, string coordinateTwo){
    battleship->clearLocation();
    auto [y1, x1] = coordinateInterpreter(coordinateOne);
    auto [y2, x2] = coordinateInterpreter(coordinateTwo);
    if (y1 == y2){
        for (int i = 0; i < abs(x1 - x2) + 1; i++){
            if (x1 < x2){
                battleship->addLocationCoord(y1, x1+i);
                if (!(changeChar(grid, y1, x1+i, (battleship->getNumber() + '0')))){
                    purgeChar(grid, (battleship->getNumber() + '0'));
                    return false;
                }
            }
            else{
                battleship->addLocationCoord(y1, x2+i);
                if (!(changeChar(grid, y1, x2+i, (battleship->getNumber() + '0')))){
                    purgeChar(grid, (battleship->getNumber() + '0'));
                    return false;
                }
            }
        }
    }

    else if(x1 == x2){
        for (int i = 0; i < abs(y1 - y2) + 1; i++){
            if (y1 < y2){
                battleship->addLocationCoord(y1+i, x1);
                if (!(changeChar(grid, y1+i, x1, (battleship->getNumber() + '0')))){
                    purgeChar(grid, (battleship->getNumber() + '0'));
                    return false;
                }
            }
            else{
                battleship->addLocationCoord(y2+i, x1);
                if (!(changeChar(grid, y2+i, x1, (battleship->getNumber() + '0')))){
                    purgeChar(grid, (battleship->getNumber() + '0'));
                    return false;

                }
            }
        }
    }
    return true;
}

// Function to check a given coordinate if a ship is on it
bool checkGridForShip(Player* enemy, string chosenCords){
    for (int i = 0; i < enemy->getShips().size(); i++){
        for (Coordinate* coordinate : enemy->getShips()[i]->getLocation()){
            if (coordinate->getCoords() == chosenCords){
                return true;
                
            }
        }
    }
    return false;
}

// Function to check if the ship is sunk or not
bool checkHitShip(Player* enemy, string hitCoords){
    int hitCount = 0;
    
    for (int i = 0; i < enemy->getShips().size(); i++){
        if (!enemy->getShips()[i]->getSunk()){
            for (Coordinate* coordinate : enemy->getShips()[i]->getLocation()){
                if (coordinate->getCoords() == hitCoords){
                    for (int j = 0; j < enemy->getShips()[i]->getLocation().size(); j++){
                        auto [y, x] = coordinateInterpreter(enemy->getShips()[i]->getLocation()[j]->getCoords());
                        if ((*enemy->getGrid())[y][x] == 'X'){
                            hitCount++;
                        }
                        if (hitCount == enemy->getShips()[i]->getLength()){
                            enemy->getShips()[i]->setSunk();
                            return true;
                        }
                    }
                }
            }
        }
    }
    
    return false;
    
}

// Function to check how many sunken ships there are, if all ships are sunk for the given player the game is done
bool checkSunkShips(Player* enemy){
    int sunkCount = 0;
    
    for (int i = 0; i < enemy->getShips().size(); i++){
        if (enemy->getShips()[i]->getSunk()){
            sunkCount++;
        }
    }
    if (sunkCount == enemy->getShips().size()){
        return true;
    }
    return false;
}

// Final message at the end of the game, delcaring the winner
void declareWinner(Player* player, Player* enemy){
    clearScreen();
    cout << enemy->getName() << "'s ships are all sunk!" << endl;
    cout << player->getName() << ", Is The Winner!!" << endl;
}

// Function for the rules and the beginning of the game
bool rules(){
    cout << "Welcome to Battleships!\n\n"
         << "The Objectives of this game are as follows:\n"
         << "Each player has a fleet of ships hidden on their own 10x10 grid.\n"
         << "The goal is to sink all of your opponent's ships before they sink yours.\n\n"
         << "How to Play:\n"
         << "- On your turn, select a coordinate to 'fire' at (e.g. A5).\n"
         << "- If a ship occupies that coordinate, it will be marked as a hit 'X'.\n"
         << "- If the coordinate is empty, it will be marked as a miss 'O'.\n"
         << "- Ships are sunk when all of their coordinates are hit.\n"
         << "- The game ends when one player sinks all of the opponent's ships.\n\n"
         << "Let's get started! Would you like to play? (Y/N): ";
    
    string userInput;
    cin >> userInput;
    
    if ((userInput == "y") || (userInput == "Y")){
        return true;
    }
    return false;
}

// Function for the main game loop
void gameLoop(){
    
    // Create the players
    Player p1("Player 1");
    Player p2("Player 2");
    
    vector<int> ships = {2, 3, 3, 4, 5};
    
    setUpGrid(&p1, ships);
    setUpGrid(&p2, ships);
        
    Player* player = &p1;
    Player* enemy = &p2;
    Player* temp;
    
    // Main game loop
    while (true){
        string chosenCords;
        chosenCords = player->turn(enemy);
        
        auto [y, x] = coordinateInterpreter(chosenCords);
            
        if (checkGridForShip(enemy, chosenCords)){
            changeChar(enemy->getGrid(), y, x, 'X', true);
            clearScreen();
            displayGrid(enemy->getGrid());
            cout << "Ship Hit!" << endl;
            oneSecDelay();
            if (checkHitShip(enemy, chosenCords)){
                cout << "Ship Sunk!" << endl;
                oneSecDelay();
                if (checkSunkShips(enemy)){
                    declareWinner(player, enemy);
                    oneSecDelay();
                    break;
                }
            }
        }else{
            changeChar(enemy->getGrid(), y, x, 'O', true);
            clearScreen();
            displayGrid(enemy->getGrid());
            cout << "Miss!" << endl;
            oneSecDelay();
        }
        
        // Switch players each turn
        temp = player;
        player = enemy;
        enemy = temp;
        
    }
    
} 

// main function
int main(){
    
    clearScreen();
    
    // Beggining of the game
    if (!rules()){
        return 0;
    }
    
    // Create the game coordinates
    createCoordinates();
    
    // Run the main game loop
    gameLoop();
    
    // Clean memory since created dynamically
    for (Coordinate* c : gameGridCoords) {
        delete c;
    }
    
    gameGridCoords.clear();
    
    // End of code
    return 0;
}