#include "ros/ros.h"
#include "turtlesim/Spawn.h"
#include "ctime"
#include "sstream"

int main(int argc, char **argv){
    ros::init(argc, argv, "spawn_client");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;

    int number[2];
    int count = 0;
    int input1 = 12;
    int input2 = 999999999;
    srand(time(0));
    number[0] = rand()%input1;
    number[1] = rand()%input1;
    number[2] = rand()%input1;
    count = rand()%input2;

    std::stringstream ss;
    ss << "turtle"<< count;

    srv.request.x = number[0];
    srv.request.y = number[1];
    srv.request.theta = number[2];
    srv.request.name = ss.str();
    client.call(srv);
    ROS_INFO("show result: %s", srv.response.name.c_str());

    return 0;
}
