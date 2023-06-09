#pragma once

#include <string>
#include <vector>

class Node {
private:
	Node* parent;
	std::vector<Node*> children;
	std::string name;

public:
	Node(const std::string& name);
	virtual ~Node();

	Node* getParent();
	void setParent(Node* parent);
	const std::vector<Node*>& getChildren() const;
	void addChild(Node* child);
	void removeChild(Node* child);
	const std::string& getName() const;

	std::string toString() const;
};