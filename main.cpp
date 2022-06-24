#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <stdio.h>


using namespace std;

//function prototypes
void mainRead();
void mainWrite();
string directoryAppender(string);
void exisChecker();
void fileDeleter();
int fileList();
void directoryChanger();

//universal defenitions
const string directory = "/";



int main()
{
	// Defenitions
	string userFile;
	
	bool cont;

	do
	{
		//asking the user whether they want to read or write
		cout << "Enter 1 to read a file, 2 to write to a file, 3 to check whether a file already exists, and a 4 to delete a file.\n" << "Press 5 to list the files in the directory.\n" << "To view this programs documentation, press 0.\n";
		int rOrW;
		cin >> rOrW;

		// This is the menu
		switch (rOrW)
		{
		case 1:
			mainRead();
			break;
		case 2:
			mainWrite();
			break;
		case 3:
			exisChecker();
			break;
		case 4:
			fileDeleter();
			break;
		case 0:
			cout << "This feature hasn't been built yet, sorry. " << endl;
			break;
		case 5:
			fileList();
			break;
		
		default:
			cout << "That wasn't an approved character. please try again. " << endl;
			
		}
		
		
		cout << "Would you like to run this program again? Press 0 to run it again and 1 to end the program.\n ";
		cin >> cont;
	} while (!cont);
	
		
	system("pause");


}




// Used to append a directory to an incoming filename.
// Use in conjuction with the command metaFile = directoryAppender(userFile);
string directoryAppender(string incomingFile)
{
	string outgoingFile;
	
	outgoingFile = directory + incomingFile;

	return outgoingFile;
}





//The purpose of this function is to retreive and print to the terminal a file designated by the user

void mainRead()
{
	//creating variables
	fstream inputfile1;
	string userFile, metaFile;	// used to know what file to pull
	string lineData;	// used to print the data


	//getting the file name from the user
	cout << "Enter the name of the file whose data you want to be printed.\n Make sure to include any footers such as .txt\n";
	cin >> userFile;
	metaFile = directoryAppender(userFile);



	// printing the data
	inputfile1.open(metaFile, ios::in);
	if (!inputfile1)
	{
		cout << "Error opening " << userFile << "!" << endl;
	}
	else
	{
		cout << "Here is the data from your file:\n";

		while (inputfile1)
		{
			cout << lineData << endl;

			getline(inputfile1, lineData);
		}

		cout << "That is all the data from the file.\n";

	}


	// a "press any key to continue" mechanism
	system("pause");

	//closing the file
	inputfile1.close();
	cout << userFile << " is now closed.\n";

}




//The purpose of this function is to write a file designated by the user
void mainWrite()
{

	//creating variables
	string userFile, metaFile;	// used to know what file to write too
	char lineData;	// used to input the data
	int linesNum;		// used to know how many lines of data the user wants to enter
	string sections[4] = { "introduction section. ", "ingredients section. ", "instructions section. ", "notes section. " };//names of the recipe sections
	

	//getting the name of the file the user wants to create
	cout << "What is the name of the file you want to create? ";
	cin >> userFile;
	metaFile = directoryAppender(userFile);


	//creating the users file and opening
	fstream outputFile1;
	outputFile1.open(metaFile, ios::out);
	if (!outputFile1)
	{
		cout << "Error opening " << userFile << "!" << endl;
	}
	else
	{
		cout << userFile << " is now open." << endl;


		//writing data to testfile1
		cout << "now writing to " << userFile
			<< "\nMake sure to end each section with a ~ symbol." << endl;

		for (int count = 0; count <= 3; count++)
		{

			// getting the users data
			cout << "You are now writing to the " << sections[count] << endl;

			// writing the users data a character at a time using the put function
			cin.get(lineData);
			while (lineData != '~')
			{
				outputFile1.put(lineData);
				cin.get(lineData);
			}


		}

		cout << "done writing to " << userFile << endl;
	}
	// a "press any key to continue" mechanism
	system("pause");


	//closing the file testfile1
	outputFile1.close();
	cout << userFile << " is now closed." << endl;

}





//this function checks whether or not a specific file exists or not
void exisChecker()
{
	//variable defenitions
	string userFile, metaFile;
	fstream file;

	//getting the userFile from the user
	cout << "Enter the name of the file whose existence you want to check for." << endl;
	cin >> userFile;


	metaFile = directoryAppender(userFile);


	// The code that does the checking
	file.open(metaFile, ios::in);
	if (file.fail())
	{
		// The file does not exist
		cout << "That file name is not in use." << endl;

	}
	else        // The file already exists
	{
		cout << "The file " << userFile << " already exists." << endl;
	}

	file.close();

}




// this function asks the user to enter a file name, and then deletes it. may want to disable during normal operations so i don't accidently fuck my system
void fileDeleter()
{
	//getting the file name from the user
	string userFile, metaFile;
	int status;	//this variable is used to error check the deleter
	cout << "Enter the name of the file you want to delete.\n";
	cin >> userFile;
	metaFile = directoryAppender(userFile);

	//the deleting part + error checking
	status = remove(metaFile.c_str());
	if (status == 0)
		cout << "\nFile Deleted Successfully!";
	else
		cout << "\nError Occurred!";
	cout << endl;
}





// largely lifted from https://www.delftstack.com/howto/cpp/how-to-get-list-of-files-in-a-directory-cpp/
// this function is an int, but I don't acctually do anything with the return code
int fileList()
{
	
	for (const auto& file : std::filesystem::directory_iterator::directory_iterator(directory))
		cout << file.path() << endl;

	return EXIT_SUCCESS;

}




// this function would change the directory that is being used by the recipe program. it is currently not called by anything, and the most dangerous bits are disabled.
void directoryChanger() 
{
	// variable defenitions
	string newDirectory;

	// getting the new address from the user
	cout << "Enter the directory address with any slashes, /, changed to backslashes, \\." << endl;
	cin >> newDirectory;


	// To Do: error checking to see whether the directory the user entered exists or not
	

	// the following command would assign the new address to the global variable directory. it is currently disabled
	/* 
	directory = newDirectory;	
	*/


}
