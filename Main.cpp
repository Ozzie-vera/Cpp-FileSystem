#include "FileSystem.h"
#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;


int element::instance_counter = 0;
 
int main() {

	cout << "Welcome to this Unix like file system implementation" << endl;
	
	//setting up File System
	FileTree* unix = new FileTree();


	//testing made easy
	//root
	unix->mkdir("home");
	unix->mkdir("User");
	unix->mkdir("temp");
	unix->mkdir("etc");

	unix->touch("file1 ");
	unix->touch("file2 ");

	unix->working = unix->root->subdir[0];
	//root/home
	unix->mkdir("Osbaldo");
	unix->mkdir("Desktop");
	unix->mkdir("Abercombie");
	

	

	
	string line, command, input;
	int j;
	bool applife = true;
	while (applife) {
		cout << "you@yourDesktop ";
		cout << unix->printpath() << endl;
		cout << "$ ";
		getline(cin, line);
		

		//counting how many "words" are in line
		j = 0;
		for (int i = 0; i < int(line.size()); ++i) {
			if (line[i] == ' ') {
				command = line.substr(0,i);
				input = line.substr(i + 1, int(line.size()));
				j++;
			}
		}

		switch (j) {


		case 0: // user input one word just need line
			if (line == "ls") {
				unix->ls();
			}
			else if (line == "help") {
				cout << "mkdir [dirname]		Create A Directory" << endl
					<< "touch [filename]		Create new file" << endl
					<< "cd    [path]		    Change current directory" << endl
					<< "ls    [path]		    list all directories and files in path" << endl
					<< "exit 		            exit Filesystem   " << endl;
			}
			else if (line == "exit") {
				cout << "Thanks for Using this Implementation of binary trees" << endl;
				delete unix;
				applife = false;
			}
			else { goto def; }
			break;


		case 1: //  command and input
			if (command == "mkdir") {
				unix->mkdir(input);
			}
			else if (command == "touch") {
				unix->touch(input);
			}
			else if (command == "cd") {
				unix->cd(input);
			}
			else if (command == "ls") {
				unix->ls(input);
			}
			else { goto def; }
			break;


		default:// simple error handling
		def:
			cout << "Error in processing command, please type 'help' for more information" << endl;
		}
		

	}

	



	return 0;
}
