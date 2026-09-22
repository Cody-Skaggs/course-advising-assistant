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

void BinarySearchTree::addNode(Node* node, const Course& course) {
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

void BinarySearchTree::insert(const Course& course) {
	if (root == nullptr) {
		root = new Node(course);
	}
	else {
		this->addNode(root, course);
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