#include "blob_tracker.h"


BlobTracker::BlobTracker(double x0, double y0, double sig_x, double sig_y, double sig_xy, double alpha_pos, double alpha_shape){
  cen_x_ = x0;
  cen_y_ = y0;

  sig_x2_ = sig_x*sig_x;
  sig_y2_ = sig_y*sig_y;
  sig_xy_ = sig_xy;

  alpha_pos_ = alpha_pos;
  alpha_shape_ = alpha_shape;
}



BlobTracker::~BlobTracker() {
}



double BlobTracker::compute_p(int ev_x, int ev_y) {
  double dx = ev_x - cen_x_;
  double dy = ev_y - cen_y_;

  // We compute the determinant of the covariance matrix
  double det = sig_x2_*sig_y2_-sig_xy_*sig_xy_;

  // That we use for computing its inverse. We directly compute the resulting probability
  double tmp = 1/det*(dx*dx*sig_y2_-2*dx*dy*sig_xy_+dy*dy*sig_x2_);

  return 1.0/(2*M_PI*sqrt(det))*exp(-0.5*tmp);
}


double BlobTracker::dist2Event(int ev_x, int ev_y) {
  double dx = ev_x - cen_x_;
  double dy = ev_y - cen_y_;


  double dist = sqrt(dx*dx+dy*dy); //compute Euclidean distance

  return dist;

}


void BlobTracker::update_position(int ev_x, int ev_y) {
  double delta_sig_x2 = (ev_x-cen_x_)*(ev_x-cen_x_);
  double delta_sig_y2 = (ev_y-cen_y_)*(ev_y-cen_y_);
  double delta_sig_xy = (ev_x-cen_x_)*(ev_y-cen_y_);

  sig_x2_ = (1-alpha_shape_)*sig_x2_ + alpha_shape_*delta_sig_x2;
  sig_y2_ = (1-alpha_shape_)*sig_y2_ + alpha_shape_*delta_sig_y2;
  sig_xy_ = (1-alpha_shape_)*sig_xy_ + alpha_shape_*delta_sig_xy;

  cen_x_ = (1-alpha_pos_)*cen_x_ + alpha_pos_*ev_x;
  cen_y_ = (1-alpha_pos_)*cen_y_ + alpha_pos_*ev_y;
}



void BlobTracker::displace(double dx, double dy){
  cen_x_ += dx;
  cen_y_ += dy;
}



void BlobTracker::move_to(double x, double y){
  cen_x_ = x;
  cen_y_ = y;
}



void BlobTracker::get_ellipse_parameters(double &cen_x, double &cen_y, double &a, double &b, double &alpha){
  // We compute the eigenvalues of the covariance matrix
  double tmp = sqrt( (sig_x2_ - sig_y2_) * (sig_x2_ - sig_y2_) + 4*sig_xy_*sig_xy_ );
  double l_max = 0.5*(sig_x2_ + sig_y2_ + tmp);
  double l_min = 0.5*(sig_x2_ + sig_y2_ - tmp);

  a = sqrt(l_max);  
  b = sqrt(l_min);
  alpha = 0.5*atan2f(2*sig_xy_, sig_y2_ - sig_x2_);

  cen_x = cen_x_;
  cen_y = cen_y_;
}