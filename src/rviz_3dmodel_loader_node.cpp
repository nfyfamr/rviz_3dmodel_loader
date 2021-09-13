#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "model");
  ros::NodeHandle node_handle;
  ros::Rate r(1);
  ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Info);

  ros::Publisher vis_pub = node_handle.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );

  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time();
  marker.ns = "my_namespace";
  marker.id = 0;
  marker.type = visualization_msgs::Marker::MESH_RESOURCE;
  marker.action = visualization_msgs::Marker::ADD;

  marker.pose.position.x = -1.5;
  marker.pose.position.y = -1;
  marker.pose.position.z = -0.1;

  tf2::Quaternion q;
  q.setRPY( 90.0/180*3.14159, 0, 0.220013 );
  q.normalize();
  tf2::convert(q, marker.pose.orientation);
  marker.scale.x = 1.0465116279;
  marker.scale.y = 1.0151162791;
  marker.scale.z = 1;
  marker.color.a = 0.0; // Don't forget to set the alpha!
  marker.color.r = 0.0;
  marker.color.g = 0.0;
  marker.color.b = 0.0;
  //only if using a MESH_RESOURCE marker type:
  // marker.mesh_resource = "file:///home/user/ros_catkin_ws/src/model/src/scan.dae";
  marker.mesh_resource = "file:///Users/user/Desktop/ros_ws/src/model/src/scan.dae";
  
  marker.mesh_use_embedded_materials = true;

  while (ros::ok())
  {
    while (vis_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    vis_pub.publish( marker );

    r.sleep();
  }

  return 0;
}
