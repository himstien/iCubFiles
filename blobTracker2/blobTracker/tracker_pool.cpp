#include "tracker_pool.h"


TrackerPool::TrackerPool(double sig_x, double sig_y, double sig_xy, double alpha_pos, double alpha_shape, double k, 
			 double max_dist, int rows, int cols, bool fixed_shape){

  max_dist_ = max_dist;
  // Creation of the filters
  for(int ii=0; ii<rows; ii++){
    for(int jj=0; jj<cols; jj++){
      BlobTracker new_blob(jj*128/(cols+1), ii*128/(rows+1), sig_x, sig_y, sig_xy, alpha_pos, alpha_shape, k);
      new_blob.fix_shape(fixed_shape);
      trackers_.push_back(new_blob);
    }
  }
}



TrackerPool::~TrackerPool(){
}



void TrackerPool::update(int ev_x, int ev_y){
  for(int ii=0; ii<trackers_.size(); ii++){
    if(trackers_[ii].compute_p(ev_x, ev_y) > 0 && trackers_[ii].dist2event(ev_x, ev_y) < max_dist_)
      trackers_[ii].update_position(ev_x, ev_y);
  }  
}



void TrackerPool::get_tracker_center(std::vector<double> &cen_x, std::vector<double> &cen_y){
  double temp_x, temp_y;
  cen_x.clear();
  cen_y.clear();

  for(int ii=0; ii<trackers_.size(); ii++){
    trackers_[ii].get_center(temp_x, temp_y);
    cen_x.push_back(temp_x);
    cen_y.push_back(temp_y);
  }  
}



void TrackerPool::get_ellipse_parameters(std::vector<double> &a, std::vector<double> &b, std::vector<double> &alpha){
  a.clear();
  b.clear();
  alpha.clear();
  double temp_a, temp_b, temp_alpha;

  for(int ii=0; ii<trackers_.size(); ii++){
    trackers_[ii].get_ellipse_parameters(temp_a, temp_b, temp_alpha);
    a.push_back(temp_a);
    b.push_back(temp_b);
    alpha.push_back(temp_alpha);
  }  
}



void TrackerPool::display(yarp::sig::ImageOf<yarp::sig::PixelRgb> &img){
  for(int ii=0; ii<trackers_.size(); ii++){
      trackers_[ii].display(img);
  }
}

void TrackerPool::get_tracker(BlobTracker &blobT, int index){

  blobT = trackers_[index];
}	

