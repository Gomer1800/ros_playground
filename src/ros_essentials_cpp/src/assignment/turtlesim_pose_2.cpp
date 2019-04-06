#include "ros/ros.h"
#include "turtlesim/Pose.h"

// Topic messages callback
void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
    ROS_INFO("[pose callback]\nx: %f\ny = %f\nyaw =: %f\n", msg->x, msg->y, msg->theta);
}

int main(int argc, char **argv)
{
    // Initiate a new ROS node named "turtlesim_pose_2"
	ros::init(argc, argv, "turtlesim_pose_2");
	//create a node handle: it is reference assigned to a new node
	ros::NodeHandle node;

    // Subscribe to a given topic, in this case "/turtle1/pose".
	//chatterCallback: is the name of the callback function that will be executed each time a message is received.
    ros::Subscriber pose_subscriber = node.subscribe("/turtle1/pose", 1000, poseCallback);

    // Enter a loop, pumping callbacks
    ros::spin();

    return 0;
}