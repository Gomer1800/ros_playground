#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "ros/service.h"
#include <math.h>

float x = 0;
float y = 0;
float z = 0;
float yaw = 0;

// Topic messages callback
void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
    x = msg->x;
    y = msg->y;
    yaw = msg->theta;

    ROS_INFO("[pose callback]\nx: %f\ny = %f\nyaw =: %f\n", x, y, yaw);
}

void move (ros::NodeHandle node, float speed, float distance)
{
    geometry_msgs::Twist velocity_message;

    float x0 = x;
    float y0 = y;
    float z0 = z;
    float yaw0 = yaw;

    velocity_message.linear.x = speed;
    static float distance_moved = 0.0;

    ros::Rate loop_rate(10);
    //ros::NodeHandle move_node;
    ros::Publisher velocity_publisher = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    bool not_reached = true;
    do
    {
        velocity_publisher.publish(velocity_message);
        ROS_INFO("Turtlesim moves forwards, distance: %f\n", distance);
        loop_rate.sleep();

        distance_moved = distance_moved + abs(0.5* sqrt(pow((x-x0),2) + pow((y-y0),2)));
        ROS_INFO("distance moved: %f\n",distance_moved);
        if (distance_moved >= distance){
            ROS_INFO("reached\n");
            not_reached = false;
        }
    }while(not_reached == true);

    velocity_message.linear.x = 0.0;
    velocity_publisher.publish(velocity_message);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "combo");
    ros::NodeHandle node;
    ros::Publisher velocity_publisher = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Subscriber pose_subscriber = node.subscribe("/turtle1/pose", 10, poseCallback);
    ros::Duration(2).sleep();
    ROS_INFO("move: ");
    move(node, 0.5, 2.0);
    ros::Duration(2).sleep();
    ROS_INFO("start reset: ");
    ROS_INFO("end reset: ");
    ros::spin();
    return 0;
}