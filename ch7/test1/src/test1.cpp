#include "ros/ros.h"
#include "test1/Size.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Int32.h"

int flag = 0;
std_msgs::Int32 size_width, size_high, size_x;

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    sub = n.subscribe("Size", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const test1::Size::ConstPtr& size)
  {
      if(flag==0){
          size_width.data = size->width;
          size_high.data = size->high;
          size_x.data = size->x;
          flag = 1;
      }
      else{
          if((size->width>size_width.data+50)&&(size->high>size_high.data+50)){
            ROS_INFO("go forward");
            //ROS_INFO("size->width:%d size_width:%d", size->width, size_width.data);
            size_width.data = size->width;
            size_high.data = size->high;
            size_x.data = size->x;
            geometry_msgs::Twist msg;
            msg.linear.x = 0.3;
            msg.angular.z = 0;
            pub.publish(msg);
          }
          else if((size->width<size_width.data-50)&&(size->high<size_high.data-50)){
            ROS_INFO("go back");
            size_width.data = size->width;
            size_high.data = size->high;
            size_x.data = size->x;
            geometry_msgs::Twist msg;
            msg.linear.x = -0.3;
            msg.angular.z = 0;
            pub.publish(msg);
          }
          else if( (size->x + size->width/2) < (size_x.data + size_width.data/2 - 50) ){
            ROS_INFO("turn right");
            size_width.data = size->width;
            size_high.data = size->high;
            size_x.data = size->x;
            geometry_msgs::Twist msg;
            msg.linear.x = 0;
            msg.angular.z = -0.3;
            pub.publish(msg);
          }
          else if( (size->x + size->width/2) > (size_x.data + size_width.data/2 + 50) ){
            ROS_INFO("turn left");
            size_width.data = size->width;
            size_high.data = size->high;
            size_x.data = size->x;
            geometry_msgs::Twist msg;
            msg.linear.x = 0;
            msg.angular.z = 0.3;
            pub.publish(msg);
          }
      }
   }

private:
  ros::NodeHandle n;
  ros::Publisher pub;
  ros::Subscriber sub;

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test1");
  SubscribeAndPublish SAPObject;
  ros::spin();

  return 0;
}
