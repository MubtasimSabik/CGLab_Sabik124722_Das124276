#include "GeometryNode.h"
#include "Node.h"


GeometryNode::GeometryNode(model_object* geo_obj, const std::string& name) : Node(name) {
	geometry_obj = geo_obj;
}

model_object* GeometryNode::getGeometry() {
	return geometry_obj;
}

void GeometryNode::setGeometry(model_object* geo_obj) {
	geometry_obj = geo_obj;
}