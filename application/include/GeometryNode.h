#pragma once

#include "Node.h"
#include "structs.hpp"

class GeometryNode : public Node {
private:
	model_object* geometry_obj;

public:
	GeometryNode(model_object* geo_obj, const std::string& name);
	model_object* getGeometry();
	void setGeometry(model_object* geo_obj);
};