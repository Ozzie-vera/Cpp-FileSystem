#pragma once

#ifndef FileSystem
#define FileSystem

#include<vector>
#include<string>
#include<iostream>
using namespace std;



class element {

public:
	string name;
	element* parent;	// this pointer can point to subclasses as well
						// will always point to the a parent directory

	static int instance_counter;

	element(string name) {
		this->name = name;
		this->parent = NULL;
		cout<< "instance counter: "<< ++instance_counter<<endl;

	}
	~element() {
		cout << "instance counter: "<< --instance_counter << endl;
	}
};

class File : public element {

public:
	string data;
	

	File(string name/*, string data*/):element(name) {
		//this->data = data;
		cout << "File Constructor" << endl;
	}
	~File() {
		cout << "File Deconstructor" << endl;

	}
};

class Directory : public element {

public:

	vector<Directory*> subdir;
	vector<File*> files;

	Directory(string name) :element(name) {
		cout << "Directory Constructor" << endl;
		
	}

	~Directory() {
		cout << "Directory Deconstructor" << endl;

		//delete files first
		if (!(this->files.empty())) {	// if Files vector is NOT empty
										//delete files on root dir
			File* temp;
			for (int i = 0; i < static_cast<int>(this->files.size()); ++i) {

				temp = this->files[i];
				delete temp;
			}
			this->files.clear();
		}
		
		//delete other subdirectories
		if (!(this->subdir.empty())) {	// if subdir vector is NOT empty
										//delete dirs on root dir
			Directory* temp;
			for (int i = 0; i < static_cast<int>(this->subdir.size()); ++i) {

				temp = this->subdir[i];
				delete temp;
			}
			this->subdir.clear();
		}

	}
};





class FileTree {

public:
	Directory* root;
	Directory* working;

	FileTree() { //default root
		this->root = new Directory("root");
		this->working = root;
	}

	~FileTree() {
		delete root;
	}


	


	void mkdir(string);
	void touch(string);
	void cd(string);
	void ls();
	void ls(string);
	string printpath();
	
	
	
	

};


#endif

