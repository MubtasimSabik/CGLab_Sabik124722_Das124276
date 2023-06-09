
#include "CameraNode.h"
#include "PointLightNode.h"
#include "Node.h"

#define RAND_FLOAT() ((float)std::rand() / (float)RAND_MAX)

class SceneGraph {
public:
	SceneGraph();
	std::string getName() const;
	std::string printGraph() const;
	std::shared_ptr<Node> getRoot() const;
	std::ostream& print(std::ostream& os) const;
	void traverse(node_traverse_func);
	~SceneGraph();
	static SceneGraph& getInstance();
	static std::shared_ptr<CameraNode> getActiveCamera();
	static std::shared_ptr<PointLightNode> getLight();
	static std::shared_ptr<Node> find(std::string const& name);

private:
	std::string name_;
	std::shared_ptr<Node> root_;
	void setName(std::string const& name);
	void setRoot(std::shared_ptr<Node> const& root);
};


const std::string planets[] = {
	"Mercury", "Venus",  "Earth",  "Mars",
	"Jupiter", "Saturn", "Uranus", "Neptune",
};

const float orbit_speeds[] = {
	0.25f,      // Mercury
	0.5f,       // Venus
	1.0f,       // Earth
	0.1f,       // Moon
	1.5f,       // Mars
	2.75f,      // Jupiter
	4.5f,       // Saturn
	6.5f,       // Uranus
	8.0f        // Neptune
};



const glm::vec3 SUN_AXIS{ 0, 1, 0 };

void init_solar();

std::ostream& operator<<(std::ostream& os, SceneGraph const& s);
