#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    return std::move(contents);
}

int main(int argc, const char **argv)
{
    /////////////////////////////////////////
    //Part1: The OSM data is read into the program.
    /////////////////////////////////////////
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;    
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    // TODO: Declare floats `start_x`, `start_y`, `end_x`, and `end_y` and get
    // user input for these values using std::cin. Pass the user input to the
    // RoutePlanner object below.


    float start_x,start_y,end_x,end_y;
    std::cout << "The map coordinates begin at (0,0) in lower left corner, and end at (100,100) in the up right corner "<< "\n";
    std::cout << "Enter a Start x from 0~100" <<"\n";
    std::cin >> start_x;
    std::cout << "Enter a Start y from 0~100" <<"\n";
    std::cin >> start_y;

    std::cout << "Enter a End x from 0~100" <<"\n";
    std::cin >> end_x;
    std::cout << "Enter a End y from 0~100" <<"\n";
    std::cin >> end_y;


    ///////////////////////////////////////////////////////////////
    //Part2: A RouteModel object is created to store the OSM data in usable data structures.
    ///////////////////////////////////////////////////////////////
    // Build Model.
    RouteModel model{osm_data};


    ///////////////////////////////////////////////////////////////
    //Part3:
    // A RoutePlanner object is created using the RouteModel.
    // This planner will eventually carry out the A* search on the model data
    // and store the search results in the RouteModel.
    ///////////////////////////////////////////////////////////////
    // Perform search and render results.
    RoutePlanner route_planner{model, 10, 10, 90, 90};

    route_planner.AStarSearch();
    std::cout<<"distance :"<<route_planner.GetDistance()<<std::endl;
    ///////////////////////////////////////////////////////////////
    //Part4: The RouteModel data is rendered using the IO2D library. Have a look at the video below for a brief overview of this file:
    ///////////////////////////////////////////////////////////////
    Render render{model};

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
