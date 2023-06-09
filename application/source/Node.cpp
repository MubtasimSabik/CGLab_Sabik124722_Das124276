#include "Node.h"

Node::Node(const std::string& name) : parent(nullptr), name(name) {}

Node::~Node() {
	// Delete all children
	for (Node* child : children) {
		delete child;
	}
}

Node* Node::getParent() {
	return parent;
}

void Node::setParent(Node* parent) {
	this->parent = parent;
}

const std::vector<Node*>& Node::getChildren() const {
	return children;
}

void Node::addChild(Node* child) {
	children.push_back(child);
	child->setParent(this);
}

void Node::removeChild(Node* child) {
	auto it = std::find(children.begin(), children.end(), child);
	if (it != children.end()) {
		children.erase(it);
		child->setParent(nullptr);
	}
}

const std::string& Node::getName() const {
	return name;
}

std::string Node::toString() const {
	return name;
}