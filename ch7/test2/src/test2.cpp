#include "ros/ros.h"
#include "std_msgs/Int64.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "test2/pose.h"

int flag = 0;
std_msgs::Int64 pose_width, pose_high, pose_x;

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    sub = n.subscribe("pose", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const test2::pose::ConstPtr& pose)
  {
          if(flag==0){
              pose_width.data = pose->size_x;
              pose_high.data = pose->size_y;
              pose_x.data = pose->pose_x;
              flag = 1;
          }
          else{
              if((pose->size_x>pose_width.data+20)&&(pose->size_y>pose_high.data+20)){
                  ROS_INFO("go forward");
                  pose_width.data = pose->size_x;
                  pose_high.data = pose->size_y;
                  pose_x.data = pose->pose_x;
                  geometry_msgs::Twist msg;
                  msg.linear.x = 0.3;
                  msg.angular.z = 0;
                  pub.publish(msg);
              }
              else if((pose->size_x<pose_width.data-20)&&(pose->size_y<pose_high.data-20)){
                  ROS_INFO("go back");
                  pose_width.data = pose->size_x;
                  pose_high.data = pose->size_y;
                  pose_x.data = pose->pose_x;
                  geometry_msgs::Twist msg;
                  msg.linear.x = -0.3;
                  msg.angular.z = 0;
                  pub.publish(msg);
              }
              else if( (pose->pose_x + pose->size_x/2) < (pose_x.data + pose_width.data/2 - 30) ){
                  ROS_INFO("turn left");
                  pose_width.data = pose->size_x;
                  pose_high.data = pose->size_y;
                  pose_x.data = pose->pose_x;
                  geometry_msgs::Twist msg;
                  msg.linear.x = 0;
                  msg.angular.z = 0.3;
                  pub.publish(msg);
              }
              else if( (pose->pose_x + pose->size_x/2) > (pose_x.data + pose_width.data/2 + 30) ){
                  ROS_INFO("turn right");
                  pose_width.data = pose->size_x;
                  pose_high.data = pose->size_y;
                  pose_x.data = pose->pose_x;
                  geometry_msgs::Twist msg;
                  msg.linear.x = 0;
                  msg.angular.z = -0.3;
                  pub.publish(msg);
              }
          }
   }

private:
  ros::NodeHandle n;
  ros::Publisher pub;
  ros::Subscriber sub;

};

int main(int argc, char** argv){
    ros::init(argc, argv, "test2");
    SubscribeAndPublish SAPObject;
    ros::spin();

    return 0;
}
