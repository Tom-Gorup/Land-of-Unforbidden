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
vector<string> vectorInvetory;                          //Vector of Inventory
int GLOBAL_arrayAttr[4] = {0};                          //Array of attributes
int GLOBAL_intCharacterType = 0;

//****Function Prototypes****
char    returnChar(string);                             //Return Yes/No/Other to single character
string  returnCharPick(int);                            //Return Character type
void    returnCharInfo(int);                            //Return Character Information
string  nameCharacter();                                //Get characters name
string  characterSelect(int &);                         //Main Character Selection Function
char    beginPath(char &);                              //Begin the Path
char    whichDirection(char);                           //Pick the direction
int     charAttack(int, int);                           //Character Attack
void    flee();                                         //Fleeing health reduction
void    firstFight(char, char, int &, char &);          //First fight
void    randomItem(int &);                              //Random Item
void    checkForDead(int &, char &);                    //Checks GLOBAL_charContinue for N and kills program if so
void    endOfGame(char &, char &, int &);               //End of game, checks if you want to play again
void    addItem(int &);                                 //Add item to array
void    checkInventory(int);                            //Display Inventory
void    pause(int);                                     //Pause Function
string  randomItemCreator();                            //Creates the random item
void    clearScreen();                                  //Clears the screen
void    useInventory(int, char &);                      //Select and use items in inventory
void    applyItem(int);                                 //Apply picked item and remove from inventory
void    initialAttr(int);                               //Update attributes
void    displayAttr();                                  //Display Attributes

int main()
{
    string  strCharacterType            = "";           //Character name
    int     intCharacterType            = 0;            //Character number
    string  characterName               = "";           //Character name from user
    char    charTemporary               = ' ';          //Attack or Flee
    int     charHealth                  = 100;          //Characters Health
    char    charPathDirection           = ' ';          //Direction picked, determines enemy
    int     intItemNumber               = 0;            //Current item number
    char    charContinue                = 'Y';          //Continue playing Y || N
    char    charNoReset                 = 'Y';          //Reset character attributes
    char    useItem                     = ' ';          //Use item in inventory Y || N
    
    srand((unsigned)time(0));                           //initiate random number
    do{
        clearScreen();
        strCharacterType = characterSelect(intCharacterType);
        initialAttr(intCharacterType);
        characterName = nameCharacter();                //Ask for characters name
        cout << "The path of the " << strCharacterType << " is a unique path.  " << characterName << ", you have been selected to..." << endl;
        do{
            charTemporary = beginPath(charPathDirection);
            firstFight(charTemporary, charPathDirection, intItemNumber, charContinue);
            checkForDead(charHealth, charContinue);     //checks for death after fight
        
            checkInventory(intItemNumber);              //Show current inventory
            useInventory(intItemNumber, useItem);       //Use inventory
            displayAttr();                              //Display Attributes
            
            endOfGame(charContinue, charNoReset, intItemNumber);
        }   while(charNoReset == 'Y');
    }   while(charContinue == 'Y');
    return 0;
}

//**** Functions ****

void displayAttr(){
    cout << "Health:     " << GLOBAL_arrayAttr[0] << "\n";
    cout << "Strength:   " << GLOBAL_arrayAttr[1] << "\n";
    cout << "Dexterity:  " << GLOBAL_arrayAttr[2] << "\n";
    cout << "Vitality:   " << GLOBAL_arrayAttr[3] << "\n";
}

// INITALIZE ATTRIBUTES
void initialAttr(int characterType){
    switch(characterType){
        case 1:     //Rogue
            GLOBAL_arrayAttr[0] = 100;      //Health
            GLOBAL_arrayAttr[1] = 30;       //Strength
            GLOBAL_arrayAttr[2] = 60;       //Dexterity
            GLOBAL_arrayAttr[3] = 60;       //Vitality
            break;
        case 2:     //Warrior
            GLOBAL_arrayAttr[0] = 100;
            GLOBAL_arrayAttr[1] = 70;
            GLOBAL_arrayAttr[2] = 40;
            GLOBAL_arrayAttr[3] = 40;
            break;
        case 3:     //Paladin
            GLOBAL_arrayAttr[0] = 100;
            GLOBAL_arrayAttr[1] = 45;
            GLOBAL_arrayAttr[2] = 45;
            GLOBAL_arrayAttr[3] = 60;
            break;
        case 4:     //Archer
            GLOBAL_arrayAttr[0] = 100;
            GLOBAL_arrayAttr[1] = 30;
            GLOBAL_arrayAttr[2] = 55;
            GLOBAL_arrayAttr[3] = 65;
            break;
        case 9:     //Cerberus
            GLOBAL_arrayAttr[0] = 100;
            GLOBAL_arrayAttr[1] = 90;
            GLOBAL_arrayAttr[2] = 90;
            GLOBAL_arrayAttr[3] = 30;
            break;
        default:
            cout << "Invalid character, should make it this far.";
            break;
    }
}
// END INTIALIZE ATTRIBUTES

// APPLY ITEM
void applyItem(int tempItemNum){
    string itemName = vectorInvetory[tempItemNum];
    cout << "Applying " << itemName << "\n";
    char charItemName = returnChar(itemName);
    
    switch(charItemName){
        case 'H':
            GLOBAL_arrayAttr[1] += 5;
            break;
        case 'S':
            GLOBAL_arrayAttr[1] +=7;
            break;
        case 'V':
            GLOBAL_arrayAttr[2] += 2;
            break;
        case 'B':
            GLOBAL_arrayAttr[1] += 3;
            break;
        case 'P':
            GLOBAL_arrayAttr[0] += 5;
            break;
        case 'L':
            GLOBAL_arrayAttr[0] += 10;
            break;
        case 'A':
            GLOBAL_arrayAttr[1] += 8;
            break;
        default:
            cout << "Invalid Item";
            break;
    }
    vectorInvetory.erase (vectorInvetory.begin()+tempItemNum);
}
// END APPLY ITEM

// USE INVENTORY
void useInventory(int curItemNumber, char &useItem){
    string tempUseItem      = "";
    int pickedItemNumber    = 0;
    string useThisItem      = "";
    int tempItemNum         = 0;

    cout << "Would you like to use an item from your inventory? ";
    cin >> tempUseItem;
    useItem = returnChar(tempUseItem);
    do{
        if(useItem == 'Y'){
            for(int i=1; i<=curItemNumber; i++){
                cout << i << ". " << vectorInvetory[i - 1] << "\n";
            }

            cout << "Which inventory number would you like to use? ";
            cin >> pickedItemNumber;
            while (pickedItemNumber > curItemNumber || pickedItemNumber - 1 < 0) {
                cout << "Please pick a valid inventory number. ";
                cin >> pickedItemNumber;
            }
            useThisItem = vectorInvetory[curItemNumber - 1];
            tempItemNum = pickedItemNumber - 1;
            applyItem(tempItemNum);
            cout << "Would you like to use another item? ";
            cin >> tempUseItem;
            useItem = returnChar(tempUseItem);
        }
    }   while(useItem == 'Y');
}
// END USE INVENTORY

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
    string  arrayItems[10]          = {""};
    
    arrayItems[0] = "Hammer +5 str";
    arrayItems[1] = "Sword +7 str";
    arrayItems[2] = "Vasoline Bottle +2 dex";
    arrayItems[3] = "Bow +3 str";
    arrayItems[4] = "Pint of Health +5 health";
    arrayItems[5] = "Liter of Health +10 health";
    arrayItems[6] = "Axe +8 str";
    
    randomItemSelector = 0+ rand() % (6 - 0 + 1);
    randomItemReturn = arrayItems[randomItemSelector];
    
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
void addItem(int &addItemNumber){
    addItemNumber             += 1;
}
// END ADD ITEM

// BEGIN END OF GAME
void endOfGame(char &charEndOfCont, char &charSaveChar, int &intItemNumber){
    string tempSaveChar         = "";
    string tempContinue         = "";
    
    cout << "Congratulations, you are victorious!!!  Would you like to play again? ";
    cin >> tempContinue;

    charEndOfCont = returnChar(tempContinue);

    if(charEndOfCont == 'Y'){
        cout << "Would you like to save your current character(yes) or start fresh(no)? ";
        cin >> tempSaveChar;
        charSaveChar = returnChar(tempSaveChar);
        
        if(charSaveChar == 'N'){
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
    string tempRandNewItem  = randomItemCreator();
    cout << "You have earned a(n) " << tempRandNewItem << endl;
    addItem(intItemNumber);
}
// END RANDOM ITEM

// BEGIN FIRST ATTACK
void firstFight(char attackFlee, char firstDirection, int &itemNumber, char &charFirstFightCont){
    int firstEnemyHealth        = 100;
    int intTempAttack           = 0;
    if(attackFlee == 'F'){
        flee();
    }
    else if(attackFlee == 'A'){
        switch (firstDirection) {
            case 'N':
                firstEnemyHealth *= .10;
                cout << "The Butterfly has " << firstEnemyHealth << " health." << endl;
                while ((firstEnemyHealth > 0) && (GLOBAL_arrayAttr[0] > 0)) {
                    intTempAttack = charAttack(1, 3);
                    cout << "Butterfly attacks with " << intTempAttack << "." << endl;
                    GLOBAL_arrayAttr[0] -= intTempAttack;
                    cout << "Your health is now " << GLOBAL_arrayAttr[0] << "." << endl;
                    intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << intTempAttack << "." << endl;
                    firstEnemyHealth -= intTempAttack;
                    cout << "The Butterfly has " << firstEnemyHealth << " health." << endl;
                    pause(1);
                }
                if(GLOBAL_arrayAttr[0] <= 0){
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
                while ((firstEnemyHealth > 0) && (GLOBAL_arrayAttr[0] > 0)) {
                    intTempAttack = charAttack(1, 4);
                    cout << "Wolf attacks with " << intTempAttack << "." << endl;
                    GLOBAL_arrayAttr[0] -= intTempAttack;
                    cout << "Your health is now " << GLOBAL_arrayAttr[0] << "." << endl;
                    intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << intTempAttack << "." << endl;
                    firstEnemyHealth -= intTempAttack;
                    cout << "The Wolf has " << firstEnemyHealth << " health." << endl;
                    pause(1);
                }
                if(GLOBAL_arrayAttr[0] <= 0){
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
                while ((firstEnemyHealth > 0) && (GLOBAL_arrayAttr[0] > 0)) {
                    intTempAttack = charAttack(1, 5);
                    cout << "Witch attacks with " << intTempAttack << "." << endl;
                    GLOBAL_arrayAttr[0] -= intTempAttack;
                    cout << "Your health is now " << GLOBAL_arrayAttr[0] << "." << endl;
                    intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << intTempAttack << "." << endl;
                    firstEnemyHealth -= intTempAttack;
                    cout << "The Witch has " << firstEnemyHealth << " health." << endl;
                    pause(1);
                }
                if(GLOBAL_arrayAttr[0] <= 0){
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
                while ((firstEnemyHealth > 0) && (GLOBAL_arrayAttr[0] > 0)) {
                    intTempAttack = charAttack(1, 8);
                    cout << "Yeti attacks with " << intTempAttack << "." << endl;
                    GLOBAL_arrayAttr[0] -= intTempAttack;
                    cout << "Your health is now " << GLOBAL_arrayAttr[0] << "." << endl;
                    intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << intTempAttack << "." << endl;
                    firstEnemyHealth -= intTempAttack;
                    cout << "The Yeti has " << firstEnemyHealth << " health." << endl;
                    pause(1);
                }
                if(GLOBAL_arrayAttr[0] <= 0){
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
void flee(){
    GLOBAL_arrayAttr[0] = GLOBAL_arrayAttr[0] * .95;
    cout << "You take a 5% hit for fleeing, your health is now " << GLOBAL_arrayAttr[0] << endl;
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
            cout << "Heading North, you have encountered a Butterfly! ";
            break;
        case 'S':
            cout << "Heading South, you have encountered a Wolf! ";
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
    string giveCharName    = "";
    
    switch (tempCharPick)
    {
        case 1 :
            giveCharName = "Rogue";
            break;
        case 2 :
            giveCharName = "Warrior.";
            break;
        case 3 :
            giveCharName = "Paladin";
            break;
        case 4 :
            giveCharName = "Archer";
            break;
        case 9 :
            giveCharName = "Cerberus.";
            break;
        default:
            giveCharName = "N";
            break;
    }    
    return giveCharName;
}
// END RETURN CHARACTER PICK

// BEGIN RETURN CHARACTER INFORMATION
void returnCharInfo(int tempCharacterType)
{
    string giveInfo     = "";
    
    switch (GLOBAL_intCharacterType)
    {
        case 1 :
            giveInfo = "Information about the Rogue";
            break;
        case 2 :
            giveInfo = "Information about the Warrior.";
            break;
        case 3 :
            giveInfo = "Information about the Paladin";
            break;
        case 4 :
            giveInfo = "Information about the Archer";
            break;
        case 9 :
            giveInfo = "Information about the secret character, Cerberus.";
            break;
        default:
            giveInfo = "It appears you have pick an invalid character.";
            break;
    }
    string arrayCharInfo[9];
    giveInfo = "";
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
