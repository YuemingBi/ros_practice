#include "ros/ros.h"
#include "test3/turtlesrv.h"
#include "sstream"

int main(int argc, char **argv){
    ros::init(argc, argv, "circular_motion");
    ros::NodeHandle n;
    std::stringstream ss;
    ss << argv[1] << "/cmd_vel";
    ros::ServiceClient client = n.serviceClient<test3::turtlesrv>("motion_control");
    test3::turtlesrv srv;
    srv.request.turtlename = ss.str();
    srv.request.x = atof(argv[3]);
    srv.request.z = atof(argv[4]);
    std::string name = argv[2];

    if(name=="begin"){
        srv.request.data = true;
        ROS_INFO("Start moving");
    }
    else if(name=="stop"){
        srv.request.data = false;
        ROS_INFO("Stop moving");
    }

    if(client.call(srv)){
        ROS_INFO("Start moving");
    }
    else{
        ROS_INFO("Stop moving");
    }

    return 0;
}
