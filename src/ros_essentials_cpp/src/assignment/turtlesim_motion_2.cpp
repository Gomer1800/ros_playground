

//subscriber for the topic that will show the location of the robot

//publisher to the topic that will make the robot move

//what is the topic of the posiiton? /turtle1/pose

//what is the topic that makes the robot move? /turtle1/cmd_vel

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <sstream>

int main(int argc, char **argv)
{
	// Initiate new ROS node named "talker"
	ros::init(argc, argv, "turtlesim_motion_2");

	//create a node handle: it is reference assigned to a new node
	ros::NodeHandle node;
	//create a publisher with a topic /turtle1/cmd_vel that will send a geometry_msgs/Twist message
	ros::Publisher speed_publisher = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

	//Rate is a class the is used to define frequency for a loop. Here we send a message each two seconds.
	ros::Rate loop_rate(1.0); //1/2 message per second

    float i = 0;
   while (ros::ok()) // Keep spinning loop until user presses Ctrl+C
   {
       //create a new /turtle1/cmd_vel ROS message.
	   //Message definition in this link http://docs.ros.org/api/geometry_msgs/html/msg/Twist.html
	   geometry_msgs::Twist msg;

	   //assign the speed data to ROS msg.linear.x and msg.angular.z fields
       msg.linear.x = 0.5 + i;
       msg.angular.z = 2.0;

       //print the content of the message in the terminal
       ROS_INFO("[C++ motion] I published linear \nx: %f linear y: %f \nangular z: %f\n", msg.linear.x, msg.linear.y, msg.angular.z);

       //Publish the message
       speed_publisher.publish(msg);

       ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages

      loop_rate.sleep(); // Sleep for the rest of the cycle, to enforce the loop rate
      i += .05;
   }
   return 0;
}