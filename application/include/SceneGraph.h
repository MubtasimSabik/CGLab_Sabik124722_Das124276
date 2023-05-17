#pragma once
#include <string>
#include "Node.h"

class SceneGraph {
public:
	static SceneGraph& getInstance();  // Singleton instance getter

	std::string getName() const;
	void setName(const std::string& name);
	Node* getRoot() const;
	void setRoot(Node* root);
	std::string printGraph() const;

private:
	SceneGraph();  // Private constructor for Singleton pattern
	SceneGraph(const SceneGraph&) = delete;  // Delete copy constructor
	SceneGraph& operator=(const SceneGraph&) = delete;  // Delete copy assignment operator
	~SceneGraph();  // Destructor

	std::string name;
	Node* root;
};