#include "FileSystem.h"
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;


void FileTree::mkdir(string name) {

	//Check to see if there is a a dir with the same name under working dir
	for (int i = 0; i < int(this->working->subdir.size()); ++i) {
		if (this->working->subdir[i]->name == name) {
			cout << "This directory already exists in working path, choose a different name" << endl;
			return;
		}
	}
	
													//** NOTE ON MKDIR, TOUCH these are simplified
	Directory* newDir = new Directory(name);		//  push newDir pointer to vector
	
	newDir->parent = this->working;

	this->working->subdir.push_back(newDir);

}


void FileTree::touch(string name) {

	//Check to see if there is a a file with the same name under working dir
	for (int i = 0; i < int(this->working->files.size()); ++i) {
		if (this->working->files[i]->name == name) {
			cout << "This file name already exists in working path, choose a different name" << endl;
			return;
		}
	}

	File* newFile = new File(name);

	newFile->parent = this->working;

	this->working->files.push_back(newFile);
	
}


void FileTree::cd(string path) {

	Directory* temp{};

	vector<string> nametemp;
	vector<int> indix;

	bool found = false;
	int dif;

	if (path == "..") { // go to parent directory
		temp = static_cast<Directory*>(this->working->parent);
		found = true;
	}
	else if (path == "/") {// go to root
		temp = this->root;
		found = true;
	}
	else {
		// parse text  assuming begins with letter
		for (int i = 0; i < int(path.size()); ++i) {
			if (path[i] == '/') {
				indix.push_back(i);
			}
		}

		indix.push_back(255);// last max jump
		//indix will now contain location of all /

		if (path[0] >= 65 && path[0] < 123) {// must push that first location if absolute
			nametemp.push_back(path.substr(0, indix[0]));
		}
		

		for (int i = 0; i < int(indix.size()) - 1; ++i) {
			dif = abs(indix[i] - indix[i + 1]) - 1;
			nametemp.push_back(path.substr(indix[i] + 1, dif));
		}

		// at this point path is parsed and seperated into nametemp

		// start finding new working directory from root or from current
		path[0] == '/' ? temp = this->root : temp = this->working;

		// if path contains anything go into, else leave at root
		for (int i = 0; i< int(nametemp.size()); ++i) {
			for (int j = 0; j < int(temp->subdir.size()); ++j) {
				if (temp->subdir[j]->name == nametemp[i]) {
					temp = temp->subdir[j];

				}
			}
		}

		if (nametemp.back() == temp->name) {
			found = true;
		}
	}

	if(found){this->working = temp;}
	else { cout << "Error in path, specified path not found: " + path << endl; }
	
}


bool comparedir(Directory* first, Directory* last) {	// these two compare are used for 
	return (first->name < last->name);					// sort function to list things in alphabetical order
}

bool comparefile(File* first, File* last) {
	return (first->name < last->name);
}

void FileTree::ls() {
	// alphabetically sort subdir and files using compare functions above
	sort(this->working->subdir.begin(), this->working->subdir.end(),comparedir);
	sort(this->working->files.begin(), this->working->files.end(), comparefile);

	for (int i = 0; i < int(this->working->subdir.size()); ++i) {
		cout << this->working->subdir[i]->name << endl;
	}

	for (int i = 0; i < int(this->working->files.size()); ++i) {
		cout << this->working->files[i]->name << endl;
	}

}


void FileTree::ls(string path) {
	Directory* temp{};

	vector<string> nametemp;
	vector<int> indix;

	bool found = false;
	int dif;

	if (path == "..") { // go to parent directory
		temp = static_cast<Directory*>(this->working->parent);
		found = true;
	}
	else if (path == "/") {// go to root
		temp = this->root;
		found = true;
	}
	else {
		// parse text  assuming begins with letter
		for (int i = 0; i < int(path.size()); ++i) {
			if (path[i] == '/') {
				indix.push_back(i);
			}
		}

		indix.push_back(255);// last max jump
		//indix will now contain location of all /

		if (path[0] >= 65 && path[0] < 123) {// must push that first location if absolute
			nametemp.push_back(path.substr(0, indix[0]));
		}


		for (int i = 0; i < int(indix.size()) - 1; ++i) {
			dif = abs(indix[i] - indix[i + 1]) - 1;
			nametemp.push_back(path.substr(indix[i] + 1, dif));
		}

		// at this point path is parsed and seperated into nametemp

		// start finding new working directory from root or from current
		path[0] == '/' ? temp = this->root : temp = this->working;

		// if path contains anything go into, else leave at root
		for (int i = 0; i< int(nametemp.size()); ++i) {
			for (int j = 0; j < int(temp->subdir.size()); ++j) {
				if (temp->subdir[j]->name == nametemp[i]) {
					temp = temp->subdir[j];

				}
			}
		}

		if (nametemp.back() == temp->name) {
			found = true;
		}
	}

	if (found) { 
		// alphabetically sort subdir and files using compare functions above
		sort(temp->subdir.begin(), temp->subdir.end(), comparedir);
		sort(temp->files.begin(), temp->files.end(), comparefile);

		for (int i = 0; i < int(temp->subdir.size()); ++i) {
			cout << temp->subdir[i]->name << endl;
		}

		for (int i = 0; i < int(temp->files.size()); ++i) {
			cout << temp->files[i]->name << endl;
		}
	}
	else { cout << "Error in path, specified path not found: " + path << endl; }
}


string FileTree::printpath(){
	
	element* temp;// temp to run from current dir all the way to root

	string path = "";

	temp = this->working; // set temp to working directory so place isnt lost
	
	if (temp->name == "root") { // if at root
		path = '/';
		temp = temp->parent;
	}

	while (temp != NULL){// root's parent always ==  NULL

		path =   (temp->name == "root" ? "":"/" + temp->name)+ path;
		temp = temp->parent;
	} 

	

	return path;
}
