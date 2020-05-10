#include "ros/ros.h"
#include "turtlesim/Spawn.h"
#include "ctime"

int main(int argc, char** argv){
    ros::init(argc, argv, "turtle_spawn");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;

    int input1 = 10;
    int number[2];
    srand(time(0));
    number[0] = rand()%input1;
    number[1] = rand()%input1;
    number[2] = rand()%input1;

    srv.request.x = number[0];
    srv.request.y = number[1];
    srv.request.theta = number[2];
    srv.request.name = argv[1];
    client.call(srv);
    ROS_INFO("show result: %s", srv.response.name.c_str());

    return 0;
}
