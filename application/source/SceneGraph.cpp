#include "SceneGraph.h"
#include "Node.h"

SceneGraph& SceneGraph::getInstance() {
	static SceneGraph instance;
	return instance;
}

std::string SceneGraph::getName() const {
	return name;
}

void SceneGraph::setName(const std::string& newName) {
	name = newName;
}

Node* SceneGraph::getRoot() const {
	return root;
}

void SceneGraph::setRoot(Node* newRoot) {
	if (newRoot == nullptr) {
		throw std::invalid_argument("Root node cannot be null");
	}
	root = newRoot;
}

std::string SceneGraph::printGraph() const {
	if (root == nullptr) {
		return "";
	}
	return root->toString();
}

SceneGraph::SceneGraph() : root(nullptr) {}

SceneGraph::~SceneGraph() {
	if (root != nullptr) {
		delete root;
	}
}
