#ifndef __BLOB_TRACKER_H
#define __BLOB_TRACKER_H

#include <math.h>
#include <yarp/sig/all.h>
#include <vector>

class BlobTracker {
 public:
  BlobTracker(double x0, double y0, double sig_x, double sig_y, double sig_xy, double alpha_pos, double alpha_shape, double k);
  BlobTracker();	
  ~BlobTracker();

  double compute_p(int ev_x, int ev_y);

  void update_position(int ev_x, int ev_y);
    
  void displace(double dx, double dy);

  void fix_shape(bool fix);

  void move_to(double x, double y);

  void get_ellipse_parameters(double &a, double &b, double &alpha);

  void get_center(double &cen_x, double &cen_y);

  void display(yarp::sig::ImageOf<yarp::sig::PixelRgb> &img);

  double dist2event(int ev_x, int ev_y);	

 protected:
  double cen_x_, cen_y_, sig_x2_, sig_y2_, sig_xy_;
  double alpha_pos_, alpha_shape_;
  bool fixed_shape_;

  double k_;
  // Vector containing the degrees (in radians) for plotting the ellipse
  std::vector<double> theta_;

};

#endif /* __GAUSSIAN_BLOB_TRACKER_H */