#pragma once

#include <string>
#include "Course.h"

class BinarySearchTree {
private:
	struct Node {
		Course course;
		Node* left;
		Node* right;

		explicit Node(const Course& course)
			: course(course), left(nullptr), right(nullptr) {
		}
	};

	Node* root;

	bool addNode(Node* node, const Course& course);
	void inOrder(Node* node) const;
	void destroyTree(Node* node);

public:
	BinarySearchTree();
	~BinarySearchTree();
	BinarySearchTree(const BinarySearchTree&) = delete; // Disable copy constructor
	BinarySearchTree& operator=(const BinarySearchTree&) = delete; // Disable copy assignment

	bool insert(const Course& course);
	void printInOrder() const;
	Course search(const std::string& courseNumber) const;
};
