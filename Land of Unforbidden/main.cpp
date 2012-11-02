//  main.cpp
//  Land of Unforbidden

#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <ctype.h>
#include <cstdlib>

using namespace std;

//****Global Variables****
string  GLOBAL_strCharacterType         = "";
int     GLOBAL_intCharacterType         = 0;
string  GLOBAL_characterName            = "";
char    GLOBAL_charPathDirection        = ' ';
int     GLOBAL_charHealth               = 100;
int     GLOBAL_enemyHealth              = 100;
char    GLOBAL_charTemporary            = ' ';
int     GLOBAL_intTempAttack            = 0;
char    GLOBAL_charContinue             = 'Y';
string  GLOBAL_arrayInventory[0];
string  GLOBAL_arrayItems[0];
int     GLOBAL_intItemNumber            = 0;
string  GLOBAL_tempNewItem              = "";

//****Function Prototypes****
char    returnChar(string);     //Return Yes/No/Other to single character
string  returnCharPick(int);    //Return Character type
void    returnCharInfo();       //Return Character Information
string  nameCharacter();        //Get characters name
void    characterSelect();      //Main Character Selection Function
char    beginPath();            //Begin the Path
char    whichDirection(char);   //Pick the direction
int     charAttack(int, int);   //Character Attack
void    flee();                 //Fleeing health reduction
void    firstFight(char);       //First fight
string  randomItem();           //Random Item
void    checkForDead();         //Checks GLOBAL_charContinue for N and kills program if so
void    endOfGame();            //End of game, checks if you want to play again
void    addItem();              //Add item to array
void    checkInventory();       //Display Inventory
void    pause(int);             //Pause Function
string  randomItemCreator();    //Creates the random item
void    clearScreen();          //Clears screen

int main()
{
    do{
        clearScreen();
        characterSelect();
        GLOBAL_characterName = nameCharacter();
        cout << "The path of the " << GLOBAL_strCharacterType << " is a unique path.  " << GLOBAL_characterName << ", you have been selected to..." << endl;
        GLOBAL_charTemporary = beginPath();
        firstFight(GLOBAL_charTemporary);
        checkForDead();     //checks for death after fight
        
        checkInventory();
        endOfGame();
    }   while(GLOBAL_charContinue == 'Y');
    return 0;
}

//**** My Functions ****

// CLEAR SCREEN
void clearScreen(){
    for(int i = 0; i < 25; i++) //this will output 25 newline characters
    {
        cout << "\n";
    }
}
// END CLEAR SCREEN

// BEGIN RANDOM ITEM CREATOR
string randomItemCreator(){
    int randomItemSelector  = 0;
    string randomItemReturn = "";
    
    GLOBAL_arrayItems[1] = "Hammer";
    GLOBAL_arrayItems[2] = "Sword";
    GLOBAL_arrayItems[3] = "Vasoline";
    GLOBAL_arrayItems[4] = "Bow";
    GLOBAL_arrayItems[5] = "+5 Health";
    GLOBAL_arrayItems[6] = "+10 Health";
    GLOBAL_arrayItems[7] = "Axe";
    
    srand(static_cast<int>(time(0)));
    randomItemSelector = 1 + rand() % (7 - 1 + 1);
    randomItemReturn = GLOBAL_arrayItems[randomItemSelector];
    
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
void checkInventory(){
    int tempItemNumber  = 0;
    tempItemNumber = GLOBAL_intItemNumber;
    cout << "Inventory:" << endl;
    while(tempItemNumber > 0){
        cout << GLOBAL_arrayInventory[tempItemNumber] << endl;
        tempItemNumber -= 1;
    }
}
// END CHECK INVENTORY

// BEGIN ADD ITEM
void addItem(){
    GLOBAL_intItemNumber += 1;
    GLOBAL_arrayInventory[GLOBAL_intItemNumber] = GLOBAL_tempNewItem;
}
// END ADD ITEM

// BEGIN END OF GAME
void endOfGame(){
    string tempContinue         = "";
    cout << "Congratulations, you are victorious!!!  Would you like to play again? ";
    cin >> tempContinue;
    GLOBAL_charContinue = returnChar(tempContinue);
    if(GLOBAL_charContinue == 'Y'){
        GLOBAL_charHealth = 100;
    }
}
// END END OF GAME

// BEGIN CHECK FOR DEAD
void checkForDead(){
    string isDead     = "";
    if(GLOBAL_charContinue != 'Y'){
        cout << "You are dead, would you like to play again? ";
        cin >> isDead;
        isDead = returnChar(isDead);
        if(isDead == "N"){
            exit(0);
        }
        else{
            GLOBAL_charContinue = 'Y';
            GLOBAL_charHealth = 100;
        }
    }
}
// END CHECK FOR DEAD

// BEGIN RANDOM ITEM
string randomItem(){
    GLOBAL_tempNewItem = randomItemCreator();
    cout << "You have earned " << GLOBAL_tempNewItem << endl;
    addItem();
    
    return GLOBAL_tempNewItem;
}
// END RANDOM ITEM

// BEGIN FIRST ATTACK
void firstFight(char attackFlee){
    if(attackFlee == 'F'){
        flee();
    }
    else if(attackFlee == 'A'){
        switch (GLOBAL_charPathDirection) {
            case 'N':
                GLOBAL_enemyHealth *= .10;
                cout << "The Butterfly has " << GLOBAL_enemyHealth << " health." << endl;
                while ((GLOBAL_enemyHealth > 0) && (GLOBAL_charHealth > 0)) {
                    GLOBAL_intTempAttack = charAttack(1, 3);
                    cout << "Butterfly attacks with " << GLOBAL_intTempAttack << "." << endl;
                    GLOBAL_charHealth -= GLOBAL_intTempAttack;
                    cout << "Your health is now " << GLOBAL_charHealth << "." << endl;
                    GLOBAL_intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << GLOBAL_intTempAttack << "." << endl;
                    GLOBAL_enemyHealth -= GLOBAL_intTempAttack;
                    cout << "The Butterfly has " << GLOBAL_enemyHealth << " health." << endl;
                    pause(1);
                }
                if(GLOBAL_charHealth <= 0){
                    GLOBAL_charContinue = 'N';
                }
                else{
                    cout << "You have killed the Butterfly.  ";
                    randomItem();
                    GLOBAL_enemyHealth = 100;
                }
                break;
            case 'S':
                GLOBAL_enemyHealth *= .35;
                cout << "The Wolf has " << GLOBAL_enemyHealth << " health." << endl;
                while ((GLOBAL_enemyHealth > 0) && (GLOBAL_charHealth > 0)) {
                    GLOBAL_intTempAttack = charAttack(1, 4);
                    cout << "Wolf attacks with " << GLOBAL_intTempAttack << "." << endl;
                    GLOBAL_charHealth -= GLOBAL_intTempAttack;
                    cout << "Your health is now " << GLOBAL_charHealth << "." << endl;
                    GLOBAL_intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << GLOBAL_intTempAttack << "." << endl;
                    GLOBAL_enemyHealth -= GLOBAL_intTempAttack;
                    cout << "The Wolf has " << GLOBAL_enemyHealth << " health." << endl;
                    pause(1);
                }
                if(GLOBAL_charHealth <= 0){
                    GLOBAL_charContinue = 'N';
                }
                else{
                    cout << "You have killed the Wolf.  ";
                    randomItem();
                    GLOBAL_enemyHealth = 100;
                }
                break;
            case 'W':
                GLOBAL_enemyHealth *= .60;
                cout << "The Witch has " << GLOBAL_enemyHealth << " health." << endl;
                while ((GLOBAL_enemyHealth > 0) && (GLOBAL_charHealth > 0)) {
                    GLOBAL_intTempAttack = charAttack(1, 5);
                    cout << "Witch attacks with " << GLOBAL_intTempAttack << "." << endl;
                    GLOBAL_charHealth -= GLOBAL_intTempAttack;
                    cout << "Your health is now " << GLOBAL_charHealth << "." << endl;
                    GLOBAL_intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << GLOBAL_intTempAttack << "." << endl;
                    GLOBAL_enemyHealth -= GLOBAL_intTempAttack;
                    cout << "The Witch has " << GLOBAL_enemyHealth << " health." << endl;
                    pause(1);
                }
                if(GLOBAL_charHealth <= 0){
                    GLOBAL_charContinue = 'N';
                }
                else{
                    cout << "You have killed the Witch.  ";
                    randomItem();
                    GLOBAL_enemyHealth = 100;
                }
                break;
            case 'E':
                GLOBAL_enemyHealth *= .80;
                cout << "The Yeti has " << GLOBAL_enemyHealth << " health." << endl;
                while ((GLOBAL_enemyHealth > 0) && (GLOBAL_charHealth > 0)) {
                    GLOBAL_intTempAttack = charAttack(1, 8);
                    cout << "Yeti attacks with " << GLOBAL_intTempAttack << "." << endl;
                    GLOBAL_charHealth -= GLOBAL_intTempAttack;
                    cout << "Your health is now " << GLOBAL_charHealth << "." << endl;
                    GLOBAL_intTempAttack = charAttack(1, 10);
                    cout << "You attack with " << GLOBAL_intTempAttack << "." << endl;
                    GLOBAL_enemyHealth -= GLOBAL_intTempAttack;
                    cout << "The Yeti has " << GLOBAL_enemyHealth << " health." << endl;
                    pause(1);
                }
                if(GLOBAL_charHealth <= 0){
                    GLOBAL_charContinue = 'N';
                }
                else{
                    cout << "You have killed the Yeti.  ";
                    randomItem();
                    GLOBAL_enemyHealth = 100;
                }
                break;
            default:
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
    GLOBAL_charHealth = GLOBAL_charHealth * .95;
    cout << "You take a 5% hit for fleeing, your health is now " << GLOBAL_charHealth << endl;
}
// END FLEEING FUNCTION

// BEGIN CHARACTER ATTACK
int charAttack(int lowerStrength, int upperStrength){
    int attackPower         = 0.0;
    srand(static_cast<int>(time(0)));
    attackPower = lowerStrength + rand() % (upperStrength - lowerStrength + 1);
    return attackPower;
}
// END CHARACTER ATTACK

// BEGIN PATH DIRECTION
char beginPath(){
    string direction        = "";
    char charDirection      = ' ';
    string attackFlee       = "";
    char charAttackFlee     = ' ';
    
    do{
        do{
            cout << "The path begins here, head North, South, West, or East? ";
            cin >> direction;
            charDirection = returnChar(direction);
            charDirection = whichDirection(charDirection);
            GLOBAL_charPathDirection = charDirection;
        }   while((GLOBAL_charPathDirection != 'N') && (GLOBAL_charPathDirection != 'S') && (GLOBAL_charPathDirection != 'W') && (GLOBAL_charPathDirection != 'E'));
        
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
void characterSelect(){
    
    string characterType    = "";
    char cAnswer            = 'N';
    string tempAnswer       = "";
    string infoReturn       = "";
    
    do{
        
        cout << "Welcome to the Land of the Unforbidden.  Please select your character. (1) Rogue, (2) Warrior, (3) Paladin, or (4) Archer: ";
        cin >> GLOBAL_intCharacterType;
        
        characterType = returnCharPick(GLOBAL_intCharacterType);
        
        if (characterType == "N"){
            cout << "Looks like you haven't picked a valid character." << endl;
        }
        else{
            cout << "Are you sure you would like to be a(n) " << characterType << "?  Type 'info', for more information about your character, otherwise yes to continue: ";
            cin >> tempAnswer;
            characterType = GLOBAL_strCharacterType;
            // Testing Function
            cAnswer = returnChar(tempAnswer);
            
            if(cAnswer == 'I'){
                returnCharInfo();
                cout << "Would you still like this character? ";
                cin >> tempAnswer;
                cAnswer = returnChar(tempAnswer);
            }
        }
    }   while(cAnswer != 'Y');
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
void returnCharInfo()
{
    string arrayCharInfo[9];
    string giveInfo = "";
    
    arrayCharInfo[1] = "Information about the Rogue.";
    arrayCharInfo[2] = "Information about the Warrior.";
    arrayCharInfo[3] = "Information about the Paladin.";
    arrayCharInfo[4] = "Information about the Archer.";
    arrayCharInfo[5] = "Sorry, Not a valid character.";
    arrayCharInfo[6] = "Sorry, Not a valid character.";
    arrayCharInfo[7] = "Sorry, Not a valid character.";
    arrayCharInfo[8] = "Sorry, Not a valid character.";
    arrayCharInfo[9] = "Information about the Secret characater, Cerberus.";
    
    if((GLOBAL_intCharacterType >= 1) && (GLOBAL_intCharacterType <= 9)){
        giveInfo = arrayCharInfo[GLOBAL_intCharacterType];
    }
    else{
        giveInfo = "Looks like you haven't picked a valid character.2 ";
    }
    cout << giveInfo << endl;
    //return giveInfo;
}
// END RETURN CHARACTER INFORMATION