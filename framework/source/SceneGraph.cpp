#define _DISABLE_EXTENDED_ALIGNED_STORAGE

#include "SceneGraph.h"
#include "Node.h"
#include "CameraNode.h"
#include "GeometryNode.h"
#include "PointLightNode.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <structs.hpp>
#include <utils.hpp>
#include <ctime>

/* constructor for SceneGraph */
SceneGraph::SceneGraph()
	: root_{ std::make_shared<Node>(Node{nullptr, "root"}) } {}

/* return the name of the scene graph */
std::string SceneGraph::getName() const {
	return name_;
}

/* print the scene graph */
std::string SceneGraph::printGraph() const {
	std::string graph = "Graph: ";
	for (auto const& node : root_->getChildrenList()) {
		graph.append(node->getName());
		graph.append(", ");
	}
	return graph;
}

/* return pointer to the root node of the scene graph */
std::shared_ptr<Node> SceneGraph::getRoot() const {
	return root_;
}

/* set the root of the scene graph */
void SceneGraph::setRoot(std::shared_ptr<Node> const& root) {
	root_ = root;
}

/* set a name for the scene graph */
void SceneGraph::setName(std::string const& name) {
	name_ = name;
}

/* print the scene graph */
std::ostream& SceneGraph::print(std::ostream& os) const {
	root_->print(os);
	return os;
}

/* store traverse function for root node */
void SceneGraph::traverse(node_traverse_func func) {
	func(root_);
	root_->traverse(func);
}

/* return an active camera */
std::shared_ptr<CameraNode> SceneGraph::getActiveCamera() {
	std::shared_ptr<CameraNode> camera;
	node_traverse_func find_camera = [&](std::shared_ptr<Node> node) {
		auto cam_node = std::dynamic_pointer_cast<CameraNode>(node);
		if (cam_node && cam_node->getEnabled()) {
			camera = cam_node;
		}
	};
	getInstance().traverse(find_camera);
	return camera;
}

std::shared_ptr<PointLightNode> SceneGraph::getLight() {
	std::shared_ptr<PointLightNode> light;
	node_traverse_func find_light = [&](std::shared_ptr<Node> node) {
		auto light_node = std::dynamic_pointer_cast<PointLightNode>(node);
		if (light_node) {
			light = light_node;
			return;
		}
	};
	getInstance().traverse(find_light);
	return light;
}

std::shared_ptr<Node> SceneGraph::find(std::string const& name) {
	return getInstance().getRoot()->getChildren(name);
}

/* destructor for SceneGraph */
SceneGraph::~SceneGraph() {}

SceneGraph& SceneGraph::getInstance() {
	static SceneGraph instance;
	return instance;
}

/* output operator */
std::ostream& operator<<(std::ostream& os, SceneGraph const& s) {
	return s.print(os);
}

void init_solar() {
	std::srand(std::time(0));

	auto& scene_graph = SceneGraph::getInstance();
	auto root = scene_graph.getRoot();

	auto camera = std::make_shared<CameraNode>(root, "Camera");
	camera->setEnabled(true);
	root->addChild(camera);

	auto stars = std::make_shared<GeometryNode>(root, "Stars", "stars");
	root->addChild(stars);
	stars->scale(80.0f);

	Color sun_color{ 255, 255, 0 }; // yellow sun
	float sun_brightness = 10000;
	auto point_light = std::make_shared<PointLightNode>(root, "PointLight", sun_color, sun_brightness);
	root->addChild(point_light);
	auto sun_shape = std::make_shared<GeometryNode>(point_light, "Sun Geometry", "planet");
	point_light->addChild(sun_shape);

	float distance_to_sun = 10.0f;
	// planets and orbits
	for (const auto& planet_name : planets) {
		distance_to_sun += 6.0f + 8.0f * RAND_FLOAT();

		auto holder = std::make_shared<Node>(root, planet_name + " Holder");
		root->addChild(holder);
		auto shapes = std::make_shared<GeometryNode>(holder, planet_name + " Geometry", "planet");
		holder->addChild(shapes);
		holder->rotate(RAND_FLOAT(), SUN_AXIS);
		shapes->translate({ distance_to_sun, 0, 0 });
		shapes->scale(0.5f);

		auto orbit = std::make_shared<GeometryNode>(root, planet_name + " Orbit", "orbit");
		root->addChild(orbit);
		orbit->scale(distance_to_sun);
		orbit->setColor(Color{ 255, 255, 255 }); // white orbits

		auto planet_color = utils::random_color();
		shapes->setColor(planet_color);
	}

	auto earth = root->getChildren("Earth Geometry");
	assert(earth != nullptr);

	auto moon_holder = std::make_shared<Node>(earth, "Moon Holder");
	earth->addChild(moon_holder);
	auto moon_shape = std::make_shared<GeometryNode>(moon_holder, "Moon Geometry", "planet");
	moon_holder->addChild(moon_shape);

	float moon_earth_distance = 12.0f;
	moon_shape->scale(0.4f);
	moon_shape->translate({ moon_earth_distance, 0, 0 });

	auto moon_orbit = std::make_shared<GeometryNode>(earth, "Moon Orbit", "orbit");
	earth->addChild(moon_orbit);
	moon_orbit->scale(moon_earth_distance * 0.6f);

	auto moon_color = Color{ 128, 128, 128 }; // grey moon
	moon_orbit->setColor(Color{ 255, 255, 255 });
	moon_shape->setColor(moon_color);
}
