#include "ros/ros.h"
#include "guess/IsItCorrect.h"

int secretNumber = -1;

bool check(guess::IsItCorrect::Request  &req,
         guess::IsItCorrect::Response &res)
{
  ROS_INFO_STREAM("request: " << req.guessedNumber);

  if(req.guessedNumber > secretNumber)
  {
    res.correct = "higher";    
  }
  else if(req.guessedNumber < secretNumber)
  {
    res.correct = "lower";
  }
  else
  {
    res.correct = "correct";
  }
  ROS_INFO_STREAM("sending back: " << res.correct);

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "guess_game_service");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("guess_a_number", check);

  ROS_INFO("guess_game_service started");
  srand(time(NULL));

  secretNumber = rand() % 100 + 1;
  ROS_WARN_STREAM("Generated number is: " << secretNumber);

  ros::spin();

  return 0;
}
