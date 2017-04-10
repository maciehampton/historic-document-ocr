
//send through tesseract
//use aspell to check spelling
//if not correct ask for user input with picture
//send ocr word into text file
#include "iostream"
#include "string"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(){
	
	string pathName;
	string result;
	cout<<"Please enter the picture's file path\n";
	cin>>pathName;
	string command = "tesseract "+pathName+" resultText.txt";
	const char* command2 = command.c_str();
	
	system (command2);
	
	command = "aspell --dont-backup resultText.txt";
	command2 = command.c_str();
	system(command2);
    return 1;
	

}
