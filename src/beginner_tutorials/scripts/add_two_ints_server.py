#!/usr/bin/env python

from beginner_tutorials.srv import *
import rospy

def handle_add_two_ints(req):
    print "Returning [%s + %s = %s]"%(req.a, req.b, (req.a + req.b))
    return AddTwoIntsResponse(req.a + req.b)

def add_two_ints_server():
    rospy.init_node('add_two_ints_server')
    # declared new service 'add_two_ints', with AddTwoInts service type.
    # all requests are passed to handle_add_two_ints function
    s = rospy.Service('add_two_ints', AddTwoInts, handle_add_two_ints)
    print "Read to add two ints."
    # again, rospy.spin() keeps code from exiting until service is shutdown
    rospy.spin()

if __name__== "__main__":
    add_two_ints_server()
