#include "BinarySearchTree.h"

#include <iostream>

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
	if (root != nullptr) {
		destroyTree(root);
	}

}

void BinarySearchTree::printInOrder() const {
	inOrder(root);
}

bool BinarySearchTree::addNode(Node* node, const Course& course) {
	if (node->course.courseNumber.compare(course.courseNumber) > 0) { // If the course number of the current node is greater than the course number of the new course, go left
		if (node->left == nullptr) {
			node->left = new Node(course);
			return true;
		}
		else { // If the left child is not null, recursively call addNode on the left child
			return this->addNode(node->left, course);
		}
	}
	else if (node->course.courseNumber.compare(course.courseNumber) < 0) { // If the course number of the current node is less than the course number of the new course, go right
		if (node->right == nullptr) {
			node->right = new Node(course);
			return true;
		}
		else {
			return this->addNode(node->right, course);
		}
	}
	else {
		return false; // If the course number is equal, do not add the course (no duplicates allowed)
	}
}

bool BinarySearchTree::insert(const Course& course) {
	if (root == nullptr) {
		root = new Node(course);
	}
	else {
		return this->addNode(root, course);
	}
}

Course BinarySearchTree::search(const std::string& courseNumber) const {
	Node* current = root;

	while (current != nullptr) {
		if (current->course.courseNumber.compare(courseNumber) == 0) {
			return current->course;
		}
		if (current->course.courseNumber.compare(courseNumber) > 0) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	Course course;
	return course;
}

void BinarySearchTree::inOrder(Node* node) const {
	if (node != nullptr) {
		inOrder(node->left);
		std::cout << node->course.courseNumber << " " << node->course.courseName << " " << std::endl;
		inOrder(node->right);
	}
}