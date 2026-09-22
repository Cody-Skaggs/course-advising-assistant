#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

struct Course {
	string courseNumber;
	string courseName;
	vector<string> prereqs;
	Course() {
		prereqs.resize(2);
	}
};

struct Node {
	Course course;
	Node *left;
	Node *right;

	//default contructor
	Node() {
		left = nullptr;
		right = nullptr;
	}
	//initilize with a course
	Node(Course aCourse) : Node() {
		course = aCourse;
	}
};

class BinarySearchTree {
private:
	Node* root;

	void addNode(Node* node, Course course);
	void inOrder(Node* node);
	void destroyTree(Node* node);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void insert(Course course);
	void InOrder();
	Course Search(string courseNumber);

};

void BinarySearchTree::destroyTree(Node* node) {
	if (node == nullptr) {
		return;
	}

	destroyTree(node->left);
	destroyTree(node->right);	
	delete node;

}

BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {

}

void BinarySearchTree::InOrder() {
	inOrder(root);
}

void BinarySearchTree::addNode(Node* node, Course course) {
	if (node->course.courseNumber.compare(course.courseNumber) > 0) {
		if (node->left == nullptr) {
			node->left = new Node(course);
		}
		else {
			this->addNode(node->left, course);
		}
	}
	else {
		if (node->right == nullptr) {
			node->right = new Node(course);
		}
		else {
			this->addNode(node->right, course);
		}
	}
}

void BinarySearchTree::insert(Course course) {
	if (root == nullptr) {
		root = new Node(course);
	}
	else {
		this->addNode(root, course);
	}
}

Course BinarySearchTree::Search(string courseNumber) {
	Node* current = root;

	while (current != nullptr) {
		if (current->course.courseNumber.compare(courseNumber) == 0) {
			return current->course;
		}
		if (current->course.courseNumber.compare(courseNumber) > 0){
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	Course course;
	return course;
}

void BinarySearchTree::inOrder(Node* node) {
	if (node != nullptr){
		inOrder(node->left);
		cout << node->course.courseNumber << " " << node->course.courseName << " " << endl;
		inOrder(node->right);
	}
}


void displayMenu() {
	cout << "1: Load Data Structure" << endl;
	cout << "2: Print Course List" << endl;
	cout << "3: Print Course" << endl;
	cout << "4: Exit Program" << endl;
}

void loadCourses(string fileName, BinarySearchTree* bst) {
	fstream inFile;
	string line;
	vector<string> prereqs;
	inFile.open(fileName);
	if (!inFile) {
		cout << "Error Opening File!" << endl;
	}
	else {
		cout << "File successfully opened!" << endl;
	}
	while (inFile.good()) {
		while (getline(inFile, line)) {
			Course course;
			stringstream ss(line);
			getline(ss, course.courseNumber, ',');
			getline(ss, course.courseName, ',');
			getline(ss, course.prereqs.at(0), ',');
			getline(ss, course.prereqs.at(1), ',');
			bst->insert(course);
		}
	}
	inFile.close();
	
}


int main() {
	//default binary search tree to hold all the courses
	BinarySearchTree* bst;
	bst = new BinarySearchTree();
	Course course;

	string fileName;
	string courseNumber;

	int choice = 0;
	while (choice != 4) {
		displayMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			//load data structures
			cout << "Please Enter the name of your file with the extension" << endl;
			cin >> fileName;
			loadCourses(fileName, bst);
			break;
		case 2:
			//print course in alphanumeric order
			bst->InOrder();
			break;
		case 3:
			//search and print specific course information
			cin >> courseNumber;
			course = bst->Search(courseNumber);
			if (!course.courseNumber.empty()) {
				cout << course.courseNumber << " " << course.courseName << endl;
				cout << "Prerequisites: ";
				if (course.prereqs.size() > 0) {
					for (unsigned int i = 0; i < course.prereqs.size(); ++i) {
						cout << course.prereqs.at(i) << " ";
					}
				}
				cout << endl;
			}
			break;
		}
	}
}
