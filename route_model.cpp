#include "route_model.h"
#include <iostream>

// mine 
RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
    auto temp = this->Nodes();
    int size = temp.size();
    for (size_t i = 0; i < size; i++)
    {
        auto v = RouteModel::Node(i,this,temp[i]);
        m_nodes.push_back(v); 
    }

    CreateNodeToRoadHashmap();
    
}
// mine
std::vector<RouteModel::Node>& RouteModel::SNodes(void)
{
    return m_nodes;
}


//mine
float RouteModel::Node::distance(RouteModel::Node other) const {
    return std::sqrt(std::pow(x - other.x,2) + std::pow(y - other.y,2));
}

//mine
void RouteModel::CreateNodeToRoadHashmap() {
    for( auto road : Roads())
    {
        if(road.type != Model::Road::Type::Footway)
        {
            for( auto node : Ways()[road.way].nodes)
            {
                if (node_to_rode.find(node) == node_to_rode.end())
                {
                    node_to_rode[node] = std::vector<const Model::Road *>();
                }
                node_to_rode[node].push_back(&road)
                
            }
        }
    }
}

//mine

 RouteModel::Node* RouteModel::Node::FindNeighbor(std::vector<int> node_indices) {
     Node *closest_node = nullptr;
     for(auto index : node_indices)
     {
         auto node = parent_model->SNodes()[index];
         if(!node.visited && this->distance(node) != 0)
         {
             if(closest_node == nullptr)
             {
                 closest_node = &node;
             }
             else if(this->distance(node) < this->distance(*closest_node))
             {
                 closest_node = &node;
             }
         }
     }
 }

 //mine 
 void RouteModel::Node::FindNeighbor() {
     for(auto &road : parent_model->node_to_rode[this->index])
     {
         RouteModel::Node *new_neighbor = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
         if(new_neighbor)
         {
             neighbors.push_back(new_neighbor);
         }
     }
 }


 //mine
  RouteModel::Node &RouteModel::FindClosestNode(float x, float y) {
    Node input;
    input.x = x;
    input.y = y;

    float min_dist = std::numeric_limits<float>::max();
    int closest_idx;
    float dist;
    for(auto &road : Roads())
    {
        if (road.type != Model::Road::Type::Footway) {
            for (int node_idx : Ways()[road.way].nodes) {
                dist = input.distance(SNodes()[node_idx]);
                if (dist < min_dist) {
                    closest_idx = node_idx;
                    min_dist = dist;
                }
            }
    }
  }