#include "ros/ros.h"
#include "test3/turtlesrv.h"
#include "geometry_msgs/Twist.h"

bool control(test3::turtlesrv::Request &req, test3::turtlesrv::Response &res){
    if(req.data){
        ros::NodeHandle n;
        ros::Publisher pub = n.advertise<geometry_msgs::Twist>(req.turtlename, 1000);
        ros::Rate loop_rate(10);
        while(ros::ok()){
            geometry_msgs::Twist msg;
            msg.linear.x = req.x;
            msg.angular.z = req.z;
            ROS_INFO("vel_publish: linear.x=%.1f angular.z=%.1f", msg.linear.x, msg.angular.z);
            pub.publish(msg);
            loop_rate.sleep();
            ros::spinOnce();
        }

        return true;
    }
    else{
        ros::NodeHandle n;
        ros::Publisher pub = n.advertise<geometry_msgs::Twist>(req.turtlename, 1000);
        ros::Rate loop_rate(10);
        while(ros::ok()){
            geometry_msgs::Twist msg;
            msg.linear.x = 0;
            msg.angular.z = 0;
            ROS_INFO("vel_publish: linear.x=%.1f angular.z=%.1f", msg.linear.x, msg.angular.z);
            pub.publish(msg);
            loop_rate.sleep();
            ros::spinOnce();
        }
    }

      return false;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "motion_server");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("motion_control", control);
    ros::spin();

    return 0;
}
