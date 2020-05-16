#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    sub = n.subscribe("voiceWords", 1000, &SubscribeAndPublish::callback, this);
  }

  void callback(const std_msgs::String::ConstPtr& msg)
  {
      std::string dataString = msg->data;
      if(dataString.find("前进") != std::string::npos || dataString.find("向前") != std::string::npos){
            //ROS_INFO("go forward");
            geometry_msgs::Twist msg;
            msg.linear.x = 0.3;
            msg.angular.z = 0;
            pub.publish(msg);
      }
      else if(dataString.find("后退") != std::string::npos || dataString.find("向后") != std::string::npos){
            //ROS_INFO("go back");
            geometry_msgs::Twist msg;
            msg.linear.x = -0.3;
            msg.angular.z = 0;
            pub.publish(msg);
      }
      else if(dataString.find("左转") != std::string::npos || dataString.find("向左") != std::string::npos){
            //ROS_INFO("turn right");
            geometry_msgs::Twist msg;
            msg.linear.x = 0;
            msg.angular.z = 0.3;
            pub.publish(msg);
      }
      else if(dataString.find("右转") != std::string::npos || dataString.find("向左") != std::string::npos){
            //ROS_INFO("turn left");
            geometry_msgs::Twist msg;
            msg.linear.x = 0;
            msg.angular.z = -0.3;
            pub.publish(msg);
      }
      else if(dataString.find("转圈") != std::string::npos || dataString.find("转圈圈") != std::string::npos){
            geometry_msgs::Twist msg;
            msg.linear.x = 0.3;
            msg.angular.z = 0.3;
            pub.publish(msg);
      }
   }

private:
  ros::NodeHandle n;
  ros::Publisher pub;
  ros::Subscriber sub;

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "voice_teleop");
  SubscribeAndPublish SAPObject;
  ros::spin();

  return 0;
}
