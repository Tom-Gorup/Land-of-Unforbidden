//  main.cpp
//  Land of Unforbidden

#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <vector>

using namespace std;

//****Global Variables****
//string  GLOBAL_arrayInventory[10];
vector<string> vectorInvetory;

//****Function Prototypes****
char    returnChar(string);                             //Return Yes/No/Other to single character
string  returnCharPick(int);                            //Return Character type
void    returnCharInfo(int);                            //Return Character Information
string  nameCharacter();                                //Get characters name
string  characterSelect(int &);                         //Main Character Selection Function
char    beginPath(char &);                              //Begin the Path
char    whichDirection(char);                           //Pick the direction
int     charAttack(int, int);                           //Character Attack
void    flee(int &);                                    //Fleeing health reduction
void    firstFight(char, int &, int &, char, int &, char &);    //First fight
void    randomItem(int &);                              //Random Item
void    checkForDead(int &, char &);                    //Checks GLOBAL_charContinue for N and kills program if so
void    endOfGame(int &, char &, char &, int &);                       //End of game, checks if you want to play again
void    addItem(string, int &);                         //Add item to array
void    checkInventory(int);                            //Display Inventory
void    pause(int);                                     //Pause Function
string  randomItemCreator();                            //Creates the random item
void    clearScreen();                                  //Clears the screen

int main()
{
    string  strCharacterType            = "";
    int     intCharacterType            = 0;
    string  characterName               = "";
    char    charTemporary               = ' ';
    int     charHealth                  = 100;
    int     enemyHealth                 = 100;
    char    charPathDirection           = ' ';
    int     intItemNumber               = 0;
    char    charContinue                = 'Y';
    char    charNoReset                 = 'Y';
    
    srand((unsigned)time(0));                           //initiate random number
    do{
        clearScreen();
        strCharacterType = characterSelect(intCharacterType);
        characterName = nameCharacter();
        cout << "The path of the " << strCharacterType << " is a unique path.  " << characterName << ", you have been selected to..." << endl;
        do{
        charTemporary = beginPath(charPathDirection);
        firstFight(charTemporary, charHealth, enemyHealth, charPathDirection, intItemNumber, charContinue);
        checkForDead(charHealth, charContinue);          //checks for death after fight
        
        checkInventory(intItemNumber);
        endOfGame(charHealth, charContinue, charNoReset, intItemNumber);
        }   while(charNoReset == 'Y');
    }   while(charContinue == 'Y');
    return 0;
}

//**** My Functions ****

// CLEAR SCREEN
void clearScreen(){
    for(int i = 0; i < 25; i++)                          //this will output 25 newline characters
    {
        cout << "\n";
    }
}
// END CLEAR SCREEN

// BEGIN RANDOM ITEM CREATOR
string randomItemCreator(){
    int randomItemSelector          = 0;
    string randomItemReturn         = "";
    string  GLOBAL_arrayItems[10]   = {""};
    
    GLOBAL_arrayItems[0] = "Hammer";
    GLOBAL_arrayItems[1] = "Sword";
    GLOBAL_arrayItems[2] = "Vasoline";
    GLOBAL_arrayItems[3] = "Bow";
    GLOBAL_arrayItems[4] = "+5 Health";
    GLOBAL_arrayItems[5] = "+10 Health";
    GLOBAL_arrayItems[6] = "Axe";
    
    randomItemSelector = 0+ rand() % (7 - 0 + 1);
    randomItemReturn = GLOBAL_arrayItems[randomItemSelector];
    
    vectorInvetory.push_back(randomItemReturn);
    
    return randomItemReturn;
}
// END RANDOM ITEM CREATOR

// BEGIN PAUSE FUNCTION
void pause(int dur){
    int temp = static_cast<int>(time(NULL)) + dur;
    while(temp > time(NULL));
}
// END PAUSE FUNCTION

// BEGIN CHECK INVENTORY
void checkInventory(int intInventoryNum){
    cout << "Inventory:" << endl;

    for(int i = 0; i < intInventoryNum; i++){
        cout << vectorInvetory[i] << "\n";
    }
}
// END CHECK INVENTORY

// BEGIN ADD ITEM
void addItem(string addedItem, int &addItemNumber){
    addItemNumber             += 1;
    //GLOBAL_arrayInventory[addItemNumber] = addedItem;
}
// END ADD ITEM

// BEGIN END OF GAME
void endOfGame(int &tempEndOfHealth, char &charEndOfCont, char &charSaveChar, int &intItemNumber){
    string tempSaveChar         = "";
    string tempContinue         = "";
    
    cout << "Congratulations, you are victorious!!!  Would you like to play again? ";
    cin >> tempContinue;

    charEndOfCont = returnChar(tempContinue);

    if(charEndOfCont == 'Y'){
        cout << "Would you like to save your current character (yes) or start fresh (no)? ";
        cin >> tempSaveChar;
        charSaveChar = returnChar(tempSaveChar);
        
        if(charSaveChar == 'N'){
            tempEndOfHealth = 100;
            vectorInvetory.clear();
            intItemNumber = 0;
        }
    }
    else{
        charEndOfCont = 'N';
    }
}
// END END OF GAME

// BEGIN CHECK FOR DEAD
void checkForDead(int &tempCheckHealth, char &charCheckForContinue){
    string isDead     = "";
    if(charCheckForContinue != 'Y'){
        cout << "You are dead, would you like to play again? ";
        cin >> isDead;
        isDead = returnChar(isDead);
        if(isDead == "N"){
            exit(0);
        }
        else{
            charCheckForContinue = 'Y';
            tempCheckHealth = 100;
        }
    }
}
// END CHECK FOR DEAD

// BEGIN RANDOM ITEM
void randomItem(int &intItemNumber){
    string tempRandNewItem  = "";
    tempRandNewItem = randomItemCreator();
    cout << "You have earned a(n) " << tempRandNewItem << endl;
    addItem(tempRandNewItem, intItemNumber);
}
// END RANDOM ITEM

// BEGIN FIRST ATTACK
void firstFight(char attackFlee, int &firstCharHealth, int &firstEnemyHealth, char firstDirection, int &itemNumber, char &charFirstFightCont){
    int intTempAttack           = 0;
    if(attackFlee == 'F'){
        flee(firstCharHealth);
    }
    else if(attackFlee == 'A'){
        switch (firstDirection) {
            case 'N':
                firstEnemyHealth *= .10;
                cout << "The Butterfly has " << firstEnemyHealth << " health." << endl;
                while ((firstEnemyHealth > 0) && (firstCharHealth > 0)) {
                    intTempAttack = charAttack(1, 3);
                    cout << "Butterfly attacks with " << intTempAttack << "." << endl;
                    firstCharHealth -= intTempAttack;
                    cout << "Your health is now " << firstCharHealth << "." << endl;
                    intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << intTempAttack << "." << endl;
                    firstEnemyHealth -= intTempAttack;
                    cout << "The Butterfly has " << firstEnemyHealth << " health." << endl;
                    pause(1);
                }
                if(firstCharHealth <= 0){
                    charFirstFightCont = 'N';
                }
                else{
                    cout << "You have killed the Butterfly.  ";
                    randomItem(itemNumber);
                    firstEnemyHealth = 100;
                }
                break;
            case 'S':
                firstEnemyHealth *= .35;
                cout << "The Wolf has " << firstEnemyHealth << " health." << endl;
                while ((firstEnemyHealth > 0) && (firstCharHealth > 0)) {
                    intTempAttack = charAttack(1, 4);
                    cout << "Wolf attacks with " << intTempAttack << "." << endl;
                    firstCharHealth -= intTempAttack;
                    cout << "Your health is now " << firstCharHealth << "." << endl;
                    intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << intTempAttack << "." << endl;
                    firstEnemyHealth -= intTempAttack;
                    cout << "The Wolf has " << firstEnemyHealth << " health." << endl;
                    pause(1);
                }
                if(firstCharHealth <= 0){
                    charFirstFightCont = 'N';
                }
                else{
                    cout << "You have killed the Wolf.  ";
                    randomItem(itemNumber);
                    firstEnemyHealth = 100;
                }
                break;
            case 'W':
                firstEnemyHealth *= .60;
                cout << "The Witch has " << firstEnemyHealth << " health." << endl;
                while ((firstEnemyHealth > 0) && (firstCharHealth > 0)) {
                    intTempAttack = charAttack(1, 5);
                    cout << "Witch attacks with " << intTempAttack << "." << endl;
                    firstCharHealth -= intTempAttack;
                    cout << "Your health is now " << firstCharHealth << "." << endl;
                    intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << intTempAttack << "." << endl;
                    firstEnemyHealth -= intTempAttack;
                    cout << "The Witch has " << firstEnemyHealth << " health." << endl;
                    pause(1);
                }
                if(firstCharHealth <= 0){
                    charFirstFightCont = 'N';
                }
                else{
                    cout << "You have killed the Witch.  ";
                    randomItem(itemNumber);
                    firstEnemyHealth = 100;
                }
                break;
            case 'E':
                firstEnemyHealth *= .80;
                cout << "The Yeti has " << firstEnemyHealth << " health." << endl;
                while ((firstEnemyHealth > 0) && (firstCharHealth > 0)) {
                    intTempAttack = charAttack(1, 8);
                    cout << "Yeti attacks with " << intTempAttack << "." << endl;
                    firstCharHealth -= intTempAttack;
                    cout << "Your health is now " << firstCharHealth << "." << endl;
                    intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << intTempAttack << "." << endl;
                    firstEnemyHealth -= intTempAttack;
                    cout << "The Yeti has " << firstEnemyHealth << " health." << endl;
                    pause(1);
                }
                if(firstCharHealth <= 0){
                    charFirstFightCont = 'N';
                }
                else{
                    cout << "You have killed the Yeti.  ";
                    randomItem(itemNumber);
                    firstEnemyHealth = 100;
                }
                break;
            default:
                cout << "ERROR" << endl;
                break;
        }
    }
    else{
        cout << "Something went wrong." << endl;
    }
}
// END FIRST ATTACK

// BEGIN FLEEING FUNCTION
void flee(int &fleeHealth){
    fleeHealth = fleeHealth * .95;
    cout << "You take a 5% hit for fleeing, your health is now " << fleeHealth << endl;
}
// END FLEEING FUNCTION

// BEGIN CHARACTER ATTACK
int charAttack(int lowerStrength, int upperStrength){
    int attackPower         = 0;
    attackPower = lowerStrength + rand() % (upperStrength - lowerStrength + 1);
    return attackPower;
}
// END CHARACTER ATTACK

// BEGIN PATH DIRECTION
char beginPath(char &charDirection){
    string direction        = "";
    string attackFlee       = "";
    char charAttackFlee     = ' ';
    
    do{
        do{
            cout << "The path begins here, head North, South, West, or East? ";
            cin >> direction;
            charDirection = returnChar(direction);
            charDirection = whichDirection(charDirection);
        }   while((charDirection != 'N') && (charDirection != 'S') && (charDirection != 'W') && (charDirection != 'E'));
        
        cout << "Attack or Flee? ";
        cin >> attackFlee;
        charAttackFlee = returnChar(attackFlee);
    }   while((charAttackFlee != 'A') && (charAttackFlee != 'F'));
    
    return charAttackFlee;
}
// END PATH DIRECTION

// BEGIN DIRECTION FUNCTION
char whichDirection(char charTempDirection){
    
    switch (charTempDirection) {
        case 'N':
            cout << "Heading North, you have encouted a Butterfly! ";
            break;
        case 'S':
            cout << "Heading South, you have encoutered a Wolf! ";
            break;
        case 'W':
            cout << "Heading West, you have encountered a Witch! ";
            break;
        case 'E':
            cout << "Heading East, you have encountered a Yeti! ";
            break;
        default:
            cout << "Invalid direction" << endl;
            break;
    }
    return charTempDirection;
}
// END DIRECTION FUNCTION

// BEGIN NAME CHARACTER FUNCTION
string nameCharacter(){
    string characterName        = "";
    cout << "What is your characters name? ";
    cin >> characterName;
    return characterName;
}
// END NAME CHARACTER FUNCTION

// BEGIN MAIN CHARACTER SELECT FUNCTION
string characterSelect(int &intSelectCharacterType){
    
    string characterType    = "";
    char cAnswer            = 'N';
    string tempAnswer       = "";
    string infoReturn       = "";
    
    do{
        
        cout << "Welcome to the Land of the Unforbidden.  Please select your character. (1) Rogue, (2) Warrior, (3) Paladin, or (4) Archer: ";
        cin >> intSelectCharacterType;
        
        characterType = returnCharPick(intSelectCharacterType);
        
        if (characterType == "N"){
            cout << "Looks like you haven't picked a valid character." << endl;
        }
        else{
            cout << "Are you sure you would like to be a(n) " << characterType << "?  Type 'info', for more information about your character, otherwise yes to continue: ";
            cin >> tempAnswer;
            // Testing Function
            cAnswer = returnChar(tempAnswer);
            
            if(cAnswer == 'I'){
                returnCharInfo(intSelectCharacterType);
                cout << "Would you still like this character? ";
                cin >> tempAnswer;
                cAnswer = returnChar(tempAnswer);
            }
        }
    }   while(cAnswer != 'Y');
    return characterType;
}
// END MAIN CHARACTER SELECT FUNCTION

// BEGIN RETURN CHARACTER
char returnChar(string temporaryString)
{
    char temporaryChar      = ' ';
    
    // Convert the input to char
    temporaryChar = temporaryString[0];
    temporaryChar = toupper(temporaryChar);
    
    return temporaryChar;
}
// END RETURN CHARACTER

// BEGIN RETURN CHARACTER PICK
string returnCharPick(int tempCharPick)
{
    string characterName    = "";
    string characterSelect[9];
    
    if(((tempCharPick >= 1) && (tempCharPick <= 4)) || (tempCharPick == 9)){
        characterSelect[1] = "Rogue";
        characterSelect[2] = "Warrior";
        characterSelect[3] = "Paladin";
        characterSelect[4] = "Archer";
        characterSelect[5] = "Not a Character";
        characterSelect[6] = "Not a Character";
        characterSelect[7] = "Not a Character";
        characterSelect[8] = "Not a Character";
        characterSelect[9] = "Cerberus";
        characterName = characterSelect[tempCharPick];
    }
    else{
        characterName = "N";
    }
    
    return characterName;
}
// END RETURN CHARACTER PICK

// BEGIN RETURN CHARACTER INFORMATION
void returnCharInfo(int tempCharacterType)
{
    string arrayCharInfo[9];
    string giveInfo = "";
    int intRetCharType = tempCharacterType;
    
    arrayCharInfo[1] = "Information about the Rogue.";
    arrayCharInfo[2] = "Information about the Warrior.";
    arrayCharInfo[3] = "Information about the Paladin.";
    arrayCharInfo[4] = "Information about the Archer.";
    arrayCharInfo[5] = "Sorry, Not a valid character.";
    arrayCharInfo[6] = "Sorry, Not a valid character.";
    arrayCharInfo[7] = "Sorry, Not a valid character.";
    arrayCharInfo[8] = "Sorry, Not a valid character.";
    arrayCharInfo[9] = "Information about the Secret characater, Cerberus.";
    
    if(9 >= intRetCharType >= 1){
        giveInfo = arrayCharInfo[intRetCharType];
    }
    else{
        giveInfo = "Looks like you haven't picked a valid character.";
    }
    cout << giveInfo << endl;
}
// END RETURN CHARACTER INFORMATION