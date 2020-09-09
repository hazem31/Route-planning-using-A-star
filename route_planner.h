#pragma once
/*
These files contain a class stub for a RoutePlanner class which accepts a RouteModel along with start and end coordinates.
The RouteModel data, along with the start and end points will be used for A* search,
which will be implemented in these files. Have a look a the video below for a brief overview of the contents.
*/
#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    float GetDistance() const { return distnace;}

    void AStarSearch();

    RouteModel::Node * NextNode();
  private:
    // Add private variables or methods declarations here.
    RouteModel &m_Model;
    RouteModel::Node *start_node , *end_node;
    float distnace;
    
    std::vector<RouteModel::Node *> open_list;

    float CalculateHValue( RouteModel::Node *node);

    std::vector<RouteModel::Node>  ConstructFinalPath(RouteModel::Node *current_node);

    void AddNeighbors(RouteModel::Node*);
};
