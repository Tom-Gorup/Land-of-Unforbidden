//
//  main.cpp
//  Land of Unforbidden
//
//  Created by Thomas Gorup on 10/29/12.
//  Copyright (c) 2012 Thomas Gorup. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <ctype.h>

using namespace std;

//****Global Variables****
string GLOBAL_characterType     = "";
string GLOBAL_characterName     = "";
string GLOBAL_direction         = "";
int GLOBAL_charHealth           = 100;

//****Function Prototypes****
char returnChar(string);        //Return Yes/No/Other to single character
string returnCharPick(int);     //Return Character type
string returnCharInfo(int);     //Return Character Information
string nameCharacter();         //Get characters name
string characterSelect();       //Main Character Selection Function
string beginPath();             //Begin the Path
int charAttack(int, int);       //Character Attack

int main()
{
    GLOBAL_characterType = characterSelect();
    GLOBAL_characterName = nameCharacter();
    cout << "The path of the " << GLOBAL_characterType << " is a unique path.  " << GLOBAL_characterName << ", you have been selected to..." << endl;
    GLOBAL_direction = beginPath();
    
    while (GLOBAL_charHealth > 0) {
        cout << "You health is: " << GLOBAL_charHealth << endl;
        GLOBAL_charHealth -= charAttack(1, 5);
        cout << "You have just been attacked, your health is now: " << GLOBAL_charHealth << endl;
    }
    return 0;
}

//**** My Functions ****

// BEGIN CHARACTER ATTACK
int charAttack(int lowerStrength, int upperStrength){
    int attackPower         = 0.0;
    srand(static_cast<int>(time(0)));
    attackPower = lowerStrength + rand() % (upperStrength - lowerStrength + 1);
    return attackPower;
}
// END CHARACTER ATTACK

// BEGIN PATH DIRECTION
string beginPath(){
    string direction        = "";
    char charDirection      = ' ';
    
    cout << "The path begins here, head North, South, West, or East? ";
    cin >> direction;
    charDirection = returnChar(direction);
    
    switch (charDirection) {
        case 'N':
            cout << "Heading North" << endl;
            break;
        case 'S':
            cout << "Heading South" << endl;
            break;
        case 'W':
            cout << "Heading West" << endl;
            break;
        case 'E':
            cout << "Heading East" << endl;
            break;
        default:
            cout << "Invalid direction" << endl;
            break;
    }
    return direction;
}
// END PATH DIRECTION

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