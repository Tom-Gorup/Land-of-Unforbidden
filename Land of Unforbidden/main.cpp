//
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
string GLOBAL_strCharacterType  = "";
char GLOBAL_charCharacterType   = ' ';
string GLOBAL_characterName     = "";
char GLOBAL_pathDirection       = ' ';
int GLOBAL_charHealth           = 100;
int GLOBAL_enemyHealth          = 100;
char GLOBAL_temporary           = ' ';
int GLOBAL_tempAttack           = 0;
char GLOBAL_charDead            = 'N';

//****Function Prototypes****
char returnChar(string);        //Return Yes/No/Other to single character
string returnCharPick(int);     //Return Character type
string returnCharInfo(int);     //Return Character Information
string nameCharacter();         //Get characters name
string characterSelect();       //Main Character Selection Function
char beginPath();               //Begin the Path
char whichDirection(char);      //Pick the direction
int charAttack(int, int);       //Character Attack
void flee();                    //Fleeing health reduction
void firstFight(char);          //First fight
string randomItem();            //Random Item
void checkForDead();

int main()
{
        GLOBAL_strCharacterType = characterSelect();
        GLOBAL_characterName = nameCharacter();
        cout << "The path of the " << GLOBAL_strCharacterType << " is a unique path.  " << GLOBAL_characterName << ", you have been selected to..." << endl;
        GLOBAL_temporary = beginPath();
        firstFight(GLOBAL_temporary);
        checkForDead();     //checks for death after fight
    return 0;
}

//**** My Functions ****

// BEGIN CHECK FOR DEAD
void checkForDead(){
    if(GLOBAL_charDead != 'N'){
        exit(0);
    }
}
// END CHECK FOR DEAD

// BEGIN RANDOM ITEM
string randomItem(){
    int randItemNumber          = 0.0;
    string randomItemReturn     = "";
    
    srand(static_cast<int>(time(0)));
    randItemNumber = 1 + rand() % (5 - 1 + 1);
    
    switch (randItemNumber) {
        case 1:
            randomItemReturn = "a Hammer";
            cout << "You have earned " << randomItemReturn << endl;
            break;
        case 2:
            randomItemReturn = "a Sword";
            cout << "You have earned " << randomItemReturn << endl;
            break;
        case 3:
            randomItemReturn = "+5 Health";
            GLOBAL_charHealth += 5;
            cout << "You have earned " << randomItemReturn << "." << endl;
            cout << "Your health is now " << GLOBAL_charHealth;
            break;
        case 4:
            randomItemReturn = "a Bow";
            cout << "You have earned " << randomItemReturn << endl;
            break;
        case 5:
            randomItemReturn = "some Vasoline";
            cout << "You have earned " << randomItemReturn << endl;
            break;
        default:
            break;
    }
    
    return randomItemReturn;
}
// END RANDOM ITEM

// BEGIN FIRST ATTACK
void firstFight(char attackFlee){    
    if(attackFlee == 'F'){
        flee();
    }
    else if(attackFlee == 'A'){
        switch (GLOBAL_pathDirection) {
            case 'N':
                GLOBAL_enemyHealth *= .10;
                cout << "The Butterfly has " << GLOBAL_enemyHealth << " health." << endl;
                 while ((GLOBAL_enemyHealth > 0) && (GLOBAL_charHealth > 0)) {
                    GLOBAL_tempAttack = charAttack(1, 3);
                    cout << "Butterfly attacks with " << GLOBAL_tempAttack << "." << endl;
                    GLOBAL_charHealth -= GLOBAL_tempAttack;
                    cout << "Your health is now " << GLOBAL_charHealth << "." << endl;
                    GLOBAL_tempAttack = charAttack(1, 10);
                    cout << "You attack with " << GLOBAL_tempAttack << "." << endl;
                    GLOBAL_enemyHealth -= GLOBAL_tempAttack;
                    cout << "The Butterfly has " << GLOBAL_enemyHealth << " health." << endl;
                }
                if(GLOBAL_charHealth <= 0){
                    cout << "You have Died!" << endl;
                    GLOBAL_charDead = 'Y';
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
                    GLOBAL_tempAttack = charAttack(1, 4);
                    cout << "Wolf attacks with " << GLOBAL_tempAttack << "." << endl;
                    GLOBAL_charHealth -= GLOBAL_tempAttack;
                    cout << "Your health is now " << GLOBAL_charHealth << "." << endl;
                    GLOBAL_tempAttack = charAttack(1, 10);
                    cout << "You attack with " << GLOBAL_tempAttack << "." << endl;
                    GLOBAL_enemyHealth -= GLOBAL_tempAttack;
                    cout << "The Wolf has " << GLOBAL_enemyHealth << " health." << endl;
                }
                if(GLOBAL_charHealth <= 0){
                    cout << "You have Died!" << endl;
                    GLOBAL_charDead = 'Y';
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
                    GLOBAL_tempAttack = charAttack(1, 5);
                    cout << "Witch attacks with " << GLOBAL_tempAttack << "." << endl;
                    GLOBAL_charHealth -= GLOBAL_tempAttack;
                    cout << "Your health is now " << GLOBAL_charHealth << "." << endl;
                    GLOBAL_tempAttack = charAttack(1, 10);
                    cout << "You attack with " << GLOBAL_tempAttack << "." << endl;
                    GLOBAL_enemyHealth -= GLOBAL_tempAttack;
                    cout << "The Witch has " << GLOBAL_enemyHealth << " health." << endl;
                }
                if(GLOBAL_charHealth <= 0){
                    cout << "You have Died!" << endl;
                    GLOBAL_charDead = 'Y';
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
                    GLOBAL_tempAttack = charAttack(1, 8);
                    cout << "Yeti attacks with " << GLOBAL_tempAttack << "." << endl;
                    GLOBAL_charHealth -= GLOBAL_tempAttack;
                    cout << "Your health is now " << GLOBAL_charHealth << "." << endl;
                    GLOBAL_tempAttack = charAttack(1, 10);
                    cout << "You attack with " << GLOBAL_tempAttack << "." << endl;
                    GLOBAL_enemyHealth -= GLOBAL_tempAttack;
                    cout << "The Yeti has " << GLOBAL_enemyHealth << " health." << endl;
                }
                if(GLOBAL_charHealth <= 0){
                    cout << "You have Died!" << endl;
                    GLOBAL_charDead = 'Y';
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
        GLOBAL_pathDirection = charDirection;
        }   while((GLOBAL_pathDirection != 'N') && (GLOBAL_pathDirection != 'S') && (GLOBAL_pathDirection != 'W') && (GLOBAL_pathDirection != 'E'));
            
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
string characterSelect(){
    
    int characterNumber     = ' ';
    string characterType    = "";
    char cAnswer            = 'N';
    string tempAnswer       = "";
    string infoReturn       = "";
    
    //Character Select
    while(cAnswer != 'Y'){
        
        cout << "Welcome to the Land of the Unforbidden.  Please select your character. (1) Rogue, (2) Warrior, (3) Paladin, or (4) Archer: ";
        cin >> characterNumber;
        characterType = returnCharPick(characterNumber);
        
        if ((characterType == "N") || (characterNumber > 9)){
            cout << "Looks like you haven't picked a valid character." << endl;
        }
        else{
            cout << "Are you sure you would like to be a(n) " << characterType << "?  Type 'info', for more information about your character, otherwise yes to continue: ";
            cin >> tempAnswer;
            // Testing Function
            cAnswer = returnChar(tempAnswer);
            
            if(cAnswer == 'I'){
                infoReturn = returnCharInfo(characterNumber);
                cout << infoReturn << endl;
                cout << "Would you still like this character? ";
                cin >> tempAnswer;
                cAnswer = returnChar(tempAnswer);
            }
        }
        
    }
    characterNumber = GLOBAL_charCharacterType;
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
    string characterName;
    
    switch (tempCharPick) {
        case 1:
            characterName = "Rogue";
            break;
        case 2:
            characterName = "Warrior";
            break;
        case 3:
            characterName  = "Paladin";
            break;
        case 4:
            characterName = "Archer";
            break;
        case 9:
            characterName = "Cerberus";
            break;
        default:
            characterName = "N";
            break;
    }
    return characterName;
}
// END RETURN CHARACTER PICK

// BEGIN RETURN CHARACTER INFORMATION
string returnCharInfo(int tempInfoChar)
{
    string charInfo         = "";
    
    switch (tempInfoChar) {
        case 1:
            charInfo = "Information about the Rogue.";
            break;
        case 2:
            charInfo = "Information about the Warrior.";
            break;
        case 3:
            charInfo = "Information about the Paladin.";
            break;
        case 4:
            charInfo = "Information about the Archer.";
            break;
        case 9:
            charInfo = "Information about the Secret characater, Cerberus.";
            break;
        default:
            charInfo = "Looks like you haven't picked a valid character.";
            break;
    }
    return charInfo;
}
// END RETURN CHARACTER INFORMATION