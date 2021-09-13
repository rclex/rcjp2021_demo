#include <iostream>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("rclcpp_node");
  auto publisher = node->create_publisher<std_msgs::msg::String>("chatter", 10);
  std_msgs::msg::String message;
  rclcpp::WallRate loop_rate(1s);

  while (rclcpp::ok()) {
    message.data = "Hello World from ";
    message.data += node->get_name();
    RCLCPP_INFO(node->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher->publish(message);
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
  return 0;
}
