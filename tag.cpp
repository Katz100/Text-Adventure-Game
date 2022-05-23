//tag.cpp
//December 16th, 2021
//Cody Hopkins
// N W W to beat the game

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void programGreeting();
void menu();
void game(string playerName);

//Specification B3 - Room Constructer, create different rooms for the player to navigate
struct Room {
  string room_title;
  string room_desc;
  bool visited = false;

  //Specification C4 - Abbreviated Room Description
  void display(){
    if (visited == false){
      cout << "\n" + room_title + "\n";
      cout << "\n" + room_desc + "\n";
      visited = true;
    }
    else if (visited == true){
      cout << "\n" + room_title + "\n";
    }
  }
};

int main() {
  programGreeting();
  
  

  menu();
  
return 0;
} 

void programGreeting(){
  cout << "\nThis is a simple text based adventure game where you navigate throuhg rooms to find your way out.\nCody Hopkins\nDecember 16, 2021\n";
}

//Specification B1 - Main menu, the first thing the player sees
void menu(){
  string playerName;
  //Specification C2 - Player Name
  cout << "\nPlease enter your name: ";
  cin >> playerName;
  cout << "\nWelcome, " + playerName + ". \nYou find yourself in a mysterious house with rooms around you. Select (N)orth,  (S)outh, (W)est, and (E)ast to navigate the rooms and find your way out.";

  
  int input;
  //Specification C3 - Input Validation
  while (input > 2 || input < 1){
    cout << "\n\n1. Start Game\n2. Quit\n>>> ";
    cin >> input;
  }
  if (input == 1){
    game(playerName);
  }
  else if (input == 2){
    cout << "Goodbye";
    exit(0);
  }
  else{
    cout << "\nError... returning to main menu.\n";
  }
}

void game(string playerName){
    //Specification B2 - Hold up to 6 monsters
    string monsters[6] = {"Bat", "Zombie", "Mummy", "Vampire", "Skeleton", "Goul"};

    //Specification A1 - Array of structures - create an array holding the different room types
    struct Room rooms[3][3];
    unsigned seed = time(0);
    srand(seed);
    rooms[1][1] = {"\nLiving Room\n", "\nThe main living room in this house, you see a couch and tv that appears to have not been used in a long time.\n"};
    rooms[1][2] = {"\nKitchen\n", "\nA kitchen with every appliance you need to start cooking\n"};
    rooms[0][2] = {"\nHallway\n", "\nA narrow hallway leading to the kitchen and bedroom with unrecogizable pictures hanging on the wall\n"};
    rooms[0][1] = {"\nBedroom\n", "\nA bedroom with a twin bed and desk with a lamp which appears to be broken\n"};
    rooms[0][0] = {"\nBathroom\n", "A regular bathroom connecting the bedroom. There is a window located west that has a broken lock\n"};
    rooms[1][0] = {"\nEntrance\n", "\nThe entrance to the main house. The main door is locked from the outside\n"};
    rooms[2][0] = {"\nDining Room\n", "There's a table in the middle of the room able to fit 8 people. It looks strange to eat here\n"};
    rooms[2][1] = {"\nMaster Bedroom\n", "\nA kingsized bed is placed in the room with torn up sheets and dust laying on the desk next to it\n"};
    //Specification C1 - Five rooms
    rooms[2][2] = {"\nBathroom\n", "A bathroom connected to the master bedroom. It appears to not have been cleaned in some time\n"};
  
  rooms[1][1].display();
  int row = 1;
  int columnn = 1;
  bool foundExit = false;

  while (foundExit == false){
      cout << "(E)ast, (W)est, (N)orth, (S)outh, (L)ook\n>>> ";
      string input;
      cin >> input;
      
      if (input == "E"){
        columnn+=1;
        if (columnn > 2){
          columnn-=1;
          cout << "\nYou can't go that way.";
        }
      }
      else if (row == 0 && columnn == 0 && input == "W"){
        cout << "You jump through the window and make it out\n";
        foundExit = true;
      }
      else if (input == "W"){
        columnn-=1;
        if (columnn < 0){
          columnn+=1;
          cout << "\nYou can't go that way.";
        }
      }
      else if (input == "N"){
        row-=1;
        if (row < 0){
          row+=1;
          cout << "\nYou can't go that way.";
        }
      }
      else if(input == "S"){
        row+=1;
        if (row > 2){
          row-=1;
          cout << "\nYou can't go that way.";
        }
      }
      //Specification C5 - Detailed Look
      else if(input == "L"){
        cout << rooms[row][columnn].room_desc;
      }
      
      else{
        cout << "Sorry, you can't go that way.";
      }
      if (foundExit == false){
      rooms[row][columnn].display();
      }
      //Specification A2 - Random Encounter - the chance for the player to encounter a monster in each room.
      int foundMonster = 1 + rand() % 5;
      int pickMonster = 0 + rand() % 5;
      if (foundMonster == 1 && input != "L" && foundExit == false){
        cout << "You encountered a " + monsters[pickMonster]+"\n";
        cout << "Each will throw a dice numbered 1 - 6. The one to have the highest numbers survives.\n";
        int playerDice = 0;
        int monsterDice = 0;

        //Specification A3 - Combat - the chance game the player goes through when encountering a monster.
        while (playerDice == monsterDice){
          cout << "\nEnter 1 to roll your dice\n>>> ";
          int pInput;
          cin >> pInput;
          playerDice = 1 + rand() % 6;
          cout << "You rolled a " << playerDice << endl;
          monsterDice = 1 + rand() % 6;
          cout << monsters[pickMonster] << " rolled a " << monsterDice << endl;
          if (playerDice > monsterDice){
            cout << "\nYou survived the encounter\n";
          }
          else if (monsterDice > playerDice){
            cout << "\nThe monster rolled a higher number, you have been devoured.";
            foundExit = true;
          }
          else {
            cout << "\nIt's a tie. Roll again.";
          }
        }
      }
 

  }
  cout << "\nWould like to play again? 1. Yes, 2. No\n>>> ";
  int playAgain;
  cin >> playAgain;
  if (playAgain == 1){
    cout << "\nReturning to main menu...\n";
    menu();
  }
  else if (playAgain == 2){
    cout << "\nThanks for playing!";
  }
  else {
    cout << "\nUnrecognized input, returning to main menu...\n";
    menu();
  }
}



