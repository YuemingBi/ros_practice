#include "ros/ros.h"
#include "geometry_msgs/PointStamped.h"
#include "tf/transform_listener.h"

void transformPoint(const tf::TransformListener& listener){
    geometry_msgs::PointStamped laser_point;
    laser_point.header.frame_id = "base_laser";

    laser_point.header.stamp = ros::Time();

    laser_point.point.x = 1.0;
    laser_point.point.y = 0.2;
    laser_point.point.z = 0.0;

    try{
        geometry_msgs::PointStamped base_point;
        listener.transformPoint("base_link", laser_point, base_point);
        ROS_INFO("base_laser:(%.2f, %.2f, %.2f)--->base_link:(%.2f, %.2f, %.2f) at time %.2f", laser_point.point.x, laser_point.point.y, laser_point.point.z, base_point.point.x, base_point.point.y, base_point.point.z, base_point.header.stamp.toSec());
    }
    catch(tf::TransformException& ex){
        ROS_ERROR("Receive an exception trying to transform a point from \"base_laser\" to \"base_link\": %s", ex.what());
    }
}

int main(int argc, char **argv){
    ros::init(argc, argv, "tf_listener");
    ros::NodeHandle n;
    tf::TransformListener listener(ros::Duration(10));

    ros::Timer timer = n.createTimer(ros::Duration(1.0), boost::bind(&transformPoint, boost::ref(listener)));

    ros::spin();
}
