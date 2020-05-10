#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"

void callback(const turtlesim::Pose::ConstPtr& pose){
    ROS_INFO("x: %f", pose->x);
    ROS_INFO("y: %f", pose->y);
    ROS_INFO("theta: %f", pose->theta);
    ROS_INFO("linear_velocity: %f", pose->linear_velocity);
    ROS_INFO("angular_velocity: %f", pose->angular_velocity);
    ROS_INFO("---");
}

int main(int argc, char ** argv){
    ros::init(argc, argv, "pose_subscriber");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, callback);
    ros::Rate loop_rate(10);

    while(ros::ok()){
        geometry_msgs::Twist msg;
        msg.linear.x = 0.5;
        msg.angular.z = 0.5;
        //ROS_INFO("vel_publish: linear.x=%.1f angular.z=%.1f", msg.linear.x, msg.angular.z);
        pub.publish(msg);
        loop_rate.sleep();
        ros::spinOnce();
    }

    return 0;
}
