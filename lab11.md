In this lab we will cover the principles of <u>***Classes***</u> and <u>***Vectors***</u> in C++. The lab has starter code that implements an incomplete simulation of [*Battleship*](https://en.wikipedia.org/wiki/Battleship_(game)) and two tester files for parts one and two of the lab. During the first two parts of the lab, you will use the tester files to implement the missing components in the lab, and in parts three and four you will be working with the code directly from `battleship.cpp` to complete the working simulation.


# Vectors

A **vector** in C++ is a dynamic array from the Standard Template Library (STL) that automatically grows or shrinks as you add or remove elements. It’s safer and more flexible than a regular array because it manages memory for you and provides useful built‑in functions.

## Example Usage

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> nums;      // create empty vector
    nums.push_back(10);         // add elements
    nums.push_back(20);

    std::cout << nums[0];       // access element
    std::cout << nums.size();   // get size

    nums.pop_back();            // remove last element
}
```

Use vectors whenever you need a resizable list of values with easy and safe access.


# Classes and Structures

In C++, **classes** and **structures** (structs) are user-defined types that let you group related data and functions together. They help organize code, model real-world objects, and support object‑oriented programming.

## Key Difference

By default:

* **struct** members are **public**
* **class** members are **private**

Otherwise, they work almost identically.

---

## Example: Struct

A struct is often used for simple data containers.

```cpp
struct Point {
    int x;
    int y;
};

int main() {
    Point p{3, 5};
    std::cout << p.x << ", " << p.y;
}
```

---

## Example: Class

A class typically includes functions (methods) and controls how its data is accessed.

```cpp
class Player {
private:
    int health;

public:
    Player(int h) : health(h) {}

    void takeDamage(int amount) {
        health -= amount;
    }

    int getHealth() const {
        return health;
    }
};

int main() {
    Player p(100);
    p.takeDamage(25);
    std::cout << p.getHealth();
}
```

---

## When to Use Each

* Use a **struct** for lightweight objects that mainly store data.
* Use a **class** when you need encapsulation, behavior (methods), or more complex functionality.

Both are essential tools for organizing code and building clear, modular programs in C++.

---

## Pointers

When accessing members in classes and structs using pointers, you must be sure to use `->` not `.`.

```cpp
class Player {
private:
    int health;

public:
    Player(int h) : health(h) {}

    void takeDamage(int amount) {
        health -= amount;
    }

    int getHealth() const {
        return health;
    }
};

int main() {
    Player* p = new Player(100); // Dynamically created object
    p->takeDamage(25); // Pointer using "->" not '.' for member functions
    std::cout << p->getHealth(); // Pointer using "->" not '.' for member Variables
}
```

---


# Battleship: Rules and Objectives

Battleship is a two-player strategy game where each player attempts to locate and sink the opponent's fleet before their own ships are destroyed. The game is played on two 10x10 grids—one showing your own ships and one used to track your guesses about your opponent's grid.

---
## 🎯 Objective of the Game

The main goal of Battleship is simple:
**Be the first player to sink all of your opponent's ships.**

To do this, players take turns calling out grid coordinates, attempting to guess where the opponent has hidden their ships.

---
## 🚢 Game Setup

Each player secretly places a fleet of ships on their own grid. Ships can be placed horizontally or vertically but **cannot overlap**.

A standard fleet typically includes:

* **Carrier** – 5 spaces
* **Battleship** – 4 spaces
* **Cruiser** – 3 spaces
* **Submarine** – 3 spaces
* **Destroyer** – 2 spaces

---
## 🕹️ How Gameplay Works

### 1. **Taking Turns**

On your turn, call out a coordinate (e.g., `B7`):

* If the opponent has a ship on that space, they must say **"Hit"**.
* If not, they say **"Miss"**.

You mark the result on your tracking grid.

### 2. **Sinking a Ship**

When all cells of a particular ship have been hit, the opponent must declare:
**"You sunk my ship!"**

### 3. **Winning the Game**

The game ends when one player has all their ships completely sunk.

---
## 🎯 Strategy Notes

* Spread your ships to avoid easy patterns.
* Track your hits so you can follow up efficiently.
* Use logical deduction to find ship orientations after a hit.

---

In our implementation in our `battleship.cpp` file, we will aim to have a working simulation of two players passing the device back and forth until one player has sunk all of the opponent’s ships. By the end of this lab, you will have the skills to use vectors to store data and access it in multiple different ways, create structures and classes with public and private variables, use constructors to initialize objects, and create getter and setter functions within a class to access the private member variables of a given class or structure.

# CoordinateTester.cpp

Currently this file is ***Not*** compileable. You will find three TODO's in the `CoordinateTester.cpp`:
- Create a coordinate structure.
- Create a global variable called `gameGridCoords`.
- Create a function to initialize all of the game coords into `gameGridCoords`.

## Struct Coordinate
In this structure, you will need to have three **private** members:
- An integer number to represent the x coordinate.
- An integer number to represent the y coordinate.
- A string to represent the x and y component in terms of the game grid (e.g., `A1`).

The structure will also need some **public** members too:
- A Constructor that initializes the coordinate given the x, y coord (<u>In that order</u>).
  - The constructor also needs to create the string coord after the x, y coords have been initialized.
    - The format will look something like this: `coords = (char)(y + 65) + to_string(x+1);`.
- **Getter** functions for each of the **private** members.
  - Note: To keep things simple and consistent, <u>**all getter and setter**</u> functions will just be called (get or set) then the member variable name (e.g., `int length;`, `setLength();`, `getLength();`).

## GameGridCoords and CreateCoordinates()

These two things go hand in hand. 
- You must make `gameGridCoords` a *vector* of `Coordinate` **pointers** as a <u>global variable</u>.
- You must make `createCoordinates()` a function that creates all of the game coordinate pointers **dynamically** in the game and puts them into `gameGridCoords`.
  - The game grid is a 10 x 10 grid that has a total of 100 spaces.
  - The very **begining** grid space should be `A1`, which is `(0, 0)`.
  - The very **last** grid space should be `J10`, which is `(9, 9)`.

Once all of these components have been correctly completed, you will be able to compile and run the `CoordinateTester.cpp` file.
The correct output for this file is as follows:

```bash
Coordinate one has a row value of 0, a column value of 0 and a string value of A1.
Coordinate Two has a row value of 9, a column value of 9 and a string value of J10.
The game grid has a total size of 100 coordinates.
```

<u>**Show your TA your work, then switch your driver and navigator roles before moving on.**</u>

# BattleshipTester.cpp

Now that we have our working Coordinate structure and gameGridCoords vector of every game coordinate, we can copy all of these implementations and paste them in `BattleshipTester.cpp` at the first TODO. This way once we have implemented the Battleship class we can test it to make sure we have done everything correctly.

In this part of the lab, we are going to implement the entirety of the `Battleship` class.
## Member variables
The `Battleship` class will have five **private** member variables:
- An integer number to represent the length called `length`.
- An integer number to represent the ship number called `number`.
- A vector of Coordinate pointers called `location`.
- A boolean variable to represent if the ship has been placed called `placed`.
- A boolean variable to represent if the ship has been sunk called `sunk`.

## Member Functions
The member functions of the Battleship class get a little more *complicated*.
- A **getter** function for <u>**Every**</u> member variable.
- A **setter** function for **Each of the following** member variables.
  - `placed`
  - `sunk`

Each getter and setter takes ***no arguments***, the setters just set the boolean variables to **true**.

`Location` is special, location needs member functions called `clearLocation()` and `addLocationCoord()` (And the getter).
- `clearLocation()` just empties the location vector.
- `addLocationCoord()` takes two arguments, int `row` and int `col`.
  - Given both the row and the column, the `addLocationCoord()` iterates through the **global** `gameGridCoords` vector and if the gameGrid coordinate at that iteration has the same row and col value, that gameGrid Coordinate pointer is added to the location vector.

Once the Battleship class has been completed, you will be able to run the BattleshipTester.cpp file to test if it works. The correct output for this file is as follows:

```bash
This battleship, battleship number 1, has a length of 2 and is not placed.
This battleship has the starting coordinates of A1, and the ending coordinates of A2 and is now placed
Suddenly an enemy ship attacked ship number 1!
Ship Number 1 is sunk!
```

<u>**Show your TA your work, then switch your driver and navigator roles before moving on.**</u>

# Battleship.cpp

Now that we have our `Coordinate` structure, `Battleship` class, `gameGridCoords` vector, and function to create all of the game grid coords, we can start working on the `battleship.cpp` file.

Start by copying each component that you have worked on thus far and paste it into your `battleship.cpp` file in their respective places. You will find that the file is still **Not** compileable. To make this file compileable we will need to complete three TODO's (You can find with a quick CTRL + F then type "TODO"):
- Complete the beginning of the `setUpGrid()` Function.
- Complete the entirety `checkGridForShip()` Function.
- Complete the entirety `checkSunkShips()` Function.

## SetUpGrid() Function
The `void setUpGrid(Player* player, vector<int> ships)` function is given a Player **pointer** that represents the **current player in play** and a vector of **integers** that represent **each ship and their respective lengths** (A vector of lengths that correspond to the ship number which is index + 1). It's responsibility is to set up the player's grids at the beginning of the game by asking the player what ship they'd like to place and then obtain two coordinates from them. The responsibility of the beginning of this function is to:
- **Iterate through the given ships vector**.
- **Dynamically create a new Battleship pointer** constructed with the current iteration + 1 (If i == 0, ship number = 1) for the ship number and the ship length that corresponds to that ship (e.g., ship number 1 would have a length of ships[0], ship number 5 would have a length of ships[4]).
- **Add each new ship to the player** once created using `Player::addShip(Battleship* battleship)`.
  - *Remember that the player variable in this function is a* `Player*`.

## CheckGridForShip() Function
The `bool checkGridForShip(Player* enemy, string chosenCords)` function is given a Player **pointer** that represents the **current opponent in play** and a **string** that represents the **chosen coordinates from the player in their turn**. It's responsibility is to check to see if the given string coord has a ship on it in the given Player's **fullGrid** (The grid that has the ship locations on it) and return true if there is and false if not.
For this function you will need to:
- **Iterate** through each of the given **Player's ship's location coordinates** and compare that **Coordinate's string coordinates**, `coords`, with the chosen coordinates.
- If the chosen coords equals **any** of the ships' location coordinates, return true; otherwise, return false.
  - *You will need to use a variety of for loops and getters to achieve this*.

## CheckSunkShips() Function
The `bool checkSunkShips(Player* enemy)` function is given a Player **pointer** that represents the **current opponent in play**. It's responsibility is to check all of the given Player's ships to see if they are sunk. If all of the Player's ships are sunk, it return true; otherwise, return false.
For this function you will need to:
- **Iterate** through the **Player's ships** and see if they are sunk.
- If all of them are sunk, return true. Else, return false.

If each of these have been implemented properly, you will be able to compile and run the game. Try playing through a game to get a sense of how it works and ensure everything is working in proper working order. Before you can show your TA your work, **Comment out the code within the `clearScreen()` function so it does not do anything and so your TA can see if it is working properly** then play the game.

<u>**Show your TA your work, then switch your driver and navigator roles before moving on.**</u>

# Finishing up

Now that we have a working game, there is only one more thing to do in the lab: ***Make your own interesting change or feature in the game on your own***!
This change can be a variety of things but it must be a <u>**decently significant change to gameplay**</u>. These changes could include but are not limited to:
- Increasing the gameGrid size (14 x 14?)
- Adding a new game object that do different things (maybe power ups?)
- Add more interesting dialogue or gameplay in the game loop (Add ship names instead of just having numbers?)

If you are stuck, look over each of the functions in the `battleship.cpp` file and what they do. The easiest idea should be to make the grid bigger since you would only need to change the bounds of the game grid coords and the display grid function.

<u>**Once you have created something interesting, Show your TA your work to finish the lab.**</u>

For keeping a record of your completed lab, you should also submit your code here on Canvas. Download your .cpp files and package them into a zip file (your TA can help you do this if you don't know how), then upload it to the assignment page before submitting. Make sure the author names are listed at the top of your main file!