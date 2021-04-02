/*
 * I am not an eloquent, nor any kind of experienced programmer, and this
 * is a toy project. Regardless, I am deeply sorry to show you this 
 * sphaghetti filled, patched on, mess of a program, that only generates
 * the lowest form of humour imaginable.
 *
 * ~ An Anonymous fellow /g/entooman. 
*/ 

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <fstream>

#include "../libs/images.h"
#include "../libs/logo.h"
#include "../libs/words.h"

//This is what's called "bad practice".
using namespace std;

fstream fileOpen;

string img;

//Defines the variables that store the generated sentence in a class. 
class text {
    public:
       string first, second, last;
};

text genText;

//Randomly generates words to be used in the generated meme. 
text wordGen(void) {
    srand(time(NULL));

    int one = rand() % 24;
    int two = rand() % 20;
    int three = rand() % 34;

    genText.first = words1[one];
    genText.second = words2[two];
    genText.last = words3[three];

    return genText;
}

//Opens a text file designated by the user, and writes the previously
//generated ascii meme to that file. 
void saveMeme(string usrInput) {
    transform(usrInput.begin(), usrInput.end(), usrInput.begin(), ::tolower);

    if ((usrInput == "y") || (usrInput == "yes")) {
        string fileName;

        cout << "Enter a file name and path to save your meme to: ";
        cin >> fileName;

        fileOpen.open(fileName, ios::out);

        fileOpen << genText.first << genText.second;
        fileOpen << '\n' << img << '\n';
        fileOpen << '\n' << genText.last;

        fileOpen.close();
        cout << '\n' << "File saved successfully!" << '\n';
    }
    else if ((usrInput == "n") || (usrInput == "no")) {
        ;
    }
}

//Parses user input to matching image. 
string imgChoice(string usrInput) {
    transform(usrInput.begin(), usrInput.end(), usrInput.begin(), ::tolower);

    if (usrInput == "") {
        cout << "Error: please enter a valid meme image.";
        cin >> usrInput;
	imgChoice(usrInput);
    }
    else if (usrInput == "coomer") {
        img = coomer;
    }
    else if (usrInput == "troll") {
        img = troll;
    }
    else if (usrInput == "doge") {
        img = doge;
    }
    else if (usrInput == "walter") {
        img = walter;
    }
    else if (usrInput == "peter") {
        img = peter;
    }
    else if (usrInput == "cheems") {
        img = cheems;
    }
    else {
        cout << "unable to recognise image input. Try again: ";
        cin >> usrInput;
        imgChoice(usrInput);
    }
    return img;
}

int main() {
    //Defines string to store user inputted text. 
    string usrInput;
    int i = 1;

    cout << logo << endl;
    while(i == 1) {
	cout << "Enter your image, i.e. Coomer, Troll, Doge, Walter, Peter, Cheems: ";

        //Takes input, and assigns matching image.
        cin >> usrInput;
        imgChoice(usrInput);

        //Generates words to be used in the meme.
        wordGen();

        //Prints the meme.
        cout << endl << genText.first << genText.second << endl; 
        cout << endl << img << endl; 
        cout << genText.last << endl << endl;

        //Annoying queries the user if they wish to save their image.
        cout << "Save the meme to a text file? y/n: ";
        cin >> usrInput;
        saveMeme(usrInput);

        //Annoying queries the user if they wish to torture themselves
        //by generating another shitty meme.
        cout << "Generate another meme y/n: ";
        cin >> usrInput;

        //Ugly input parser to make sure the program closes
        //it wasn't before :(
        if ((usrInput == "n") || (usrInput == "no")) {
        exit(0);
        return 0;
        }
        else if ((usrInput == "y") || (usrInput == "yes")) {
            ;
        }
    }
}
