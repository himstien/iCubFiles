#ifndef __TRACKER_POOL_H
#define __TRACKER_POOL_H

#include "blob_tracker.h"

#include <math.h>
#include <yarp/sig/all.h>
#include <yarp/os/all.h>
#include <vector>
#include <string>

class TrackerPool {
 public:
  TrackerPool(double sig_x, double sig_y, double sig_xy, double alpha_pos, double alpha_shape, double k, double max_dist, int rows, int cols, bool fixed_shape);

  ~TrackerPool();

  void get_tracker (BlobTracker &, int);
  void update(int ev_x, int ev_y);

  void get_tracker_center(std::vector<double> &cen_x, std::vector<double> &cen_y);

  void get_ellipse_parameters(std::vector<double> &a, std::vector<double> &b, std::vector<double> &alpha);

  void display(yarp::sig::ImageOf<yarp::sig::PixelRgb> &img);

 protected:
  std::vector<BlobTracker> trackers_;
  yarp::os::Port image_port;

  double max_dist_;
};

#endif /* __GAUSSIAN_BLOB_TRACKER_H */