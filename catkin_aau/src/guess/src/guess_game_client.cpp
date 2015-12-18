#include "ros/ros.h"
#include "guess/IsItCorrect.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "guess_game_client");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<guess::IsItCorrect>("guess_a_number");
  guess::IsItCorrect srv;
  std::string input;
  bool found = false;
  
  ROS_WARN("Enter a number from 1 to 100");
  
  while(!found)
  {
    std::getline(std::cin, input);
    srv.request.guessedNumber = atoi(input.c_str());

    client.call(srv);
    
    if(srv.response.correct == "higher")
    {
      ROS_WARN("Your guess is higher, try again !");
    }
    else if(srv.response.correct == "lower")
    {
      ROS_WARN("Your guess is lower, try again !");
    }
    else
    {
      ROS_WARN("You are correct, congratulations !");
      found = true;
      ROS_ERROR("Exiting");
    }

  }

  return 0;
}
