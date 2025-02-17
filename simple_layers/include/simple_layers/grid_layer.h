#ifndef GRID_LAYER_H_
#define GRID_LAYER_H_
#include <ros/ros.h>
#include <costmap_2d/layer.h>
#include <costmap_2d/layered_costmap.h>
#include <costmap_2d/GenericPluginConfig.h>
#include <dynamic_reconfigure/server.h>
#include "geometry_msgs/PoseStamped.h" 
#include "geometry_msgs/PoseArray.h"
#include <ros/callback_queue.h>

namespace simple_layer_namespace
{

class GridLayer : public costmap_2d::Layer, public costmap_2d::Costmap2D
{
public:
  GridLayer();
  void obs_callback(const geometry_msgs::PoseArray& poses);
  virtual void onInitialize();
  virtual void updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x,
                             double* max_y);
  virtual void updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j);
  bool isDiscretized()
  {
    return true;
  }

  virtual void matchSize();

private:
  void reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level);
  dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig> *dsrv_;
  std::vector<std::vector<double>> obstacle_pos_;
  bool obstacle_updated_;
  int obstacle_num_;
  ros::CallbackQueue my_queue;
};
}
#endif