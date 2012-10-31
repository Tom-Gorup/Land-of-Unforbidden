//
//  functions.h
//  Land of Unforbidden

#include <iostream>

using namespace std;

// BEGIN NAME CHARACTER FUNCTION
string nameCharacter(){
    string characterName        = "";
    cout << "What is your characters name? ";
    cin >> characterName;
    return characterName;
}
// END NAME CHARACTER FUNCTION

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

// BEGIN CHARACTER ATTACK
int charAttack(int lowerStrength, int upperStrength){
    int attackPower         = 0.0;
    srand(static_cast<int>(time(0)));
    attackPower = lowerStrength + rand() % (upperStrength - lowerStrength + 1);
    return attackPower;
}
// END CHARACTER ATTACK