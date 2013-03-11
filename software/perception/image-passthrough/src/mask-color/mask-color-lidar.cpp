#include <fstream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <pcl/range_image/range_image.h>
#include <lcm/lcm-cpp.hpp>
#include <bot_lcmgl_client/lcmgl.h>
#include <maps/SensorDataReceiver.hpp>
#include <maps/MapManager.hpp>
#include <maps/LocalMap.hpp>
#include <maps/Collector.hpp>


#include <drc_utils/Clock.hpp>


#include <bot_param/param_client.h>
#include <bot_frames/bot_frames.h>
#include <bot_frames_cpp/bot_frames_cpp.hpp>

#include <pointcloud_tools/pointcloud_vis.hpp> // visualize pt clds
#include <image_io_utils/image_io_utils.hpp> // to simplify jpeg/zlib compression and decompression
#include <lcmtypes/bot_core.hpp>


using namespace maps;
using namespace std;


class State {
public:
  boost::shared_ptr<lcm::LCM> mLcm;
  boost::shared_ptr<Collector> mCollector;
  int mActiveMapId;
  bot_lcmgl_t* mLcmGl;
  
  std::string mask_channel_;
  void maskHandler(const lcm::ReceiveBuffer* rbuf, const std::string& channel, const  bot_core::image_t* msg);   
  bot_core::image_t last_mask_;    
  
  image_io_utils*  imgutils_;

  uint8_t* getMask(){
      return imgutils_->unzipImage(   &last_mask_ );
  }
  
  
  

  State() {
    mLcm.reset(new lcm::LCM());
    mCollector.reset(new Collector());
    mCollector->setLcm(mLcm);
    mActiveMapId = 0;
    mLcmGl = bot_lcmgl_init(mLcm->getUnderlyingLCM(), "test-points");
    
    drc::Clock::instance()->setLcm(mLcm);
    
    mask_channel_="CAMERALEFT_MASKZIPPED";
    mLcm->subscribe( mask_channel_ ,&State::maskHandler,this);
    last_mask_.utime =0; // use this number to determine initial image
    
    
    imgutils_ = new image_io_utils( mLcm->getUnderlyingLCM(), 1024, 544);
    
  }
  
  ~State() {
    bot_lcmgl_destroy(mLcmGl);
  }
};


void State::maskHandler(const lcm::ReceiveBuffer* rbuf, const std::string& channel, const  bot_core::image_t* msg){
  last_mask_= *msg;  
  cout << "got mask\n";  
}


class DataProducer {
private:  
  
  // Added by mfallon:
  BotParam* botparam_;
  BotFrames* botframes_;
  bot::frames* botframes_cpp_;    
  pointcloud_vis* pc_vis_;

  int64_t last_timeMin_;
  protected:
    State* mState;  
public:
  DataProducer(State* iState);
  
  void operator()();
};



DataProducer::DataProducer(State* iState) : mState(iState) {
  botparam_ = bot_param_new_from_server(mState->mLcm->getUnderlyingLCM(), 0);  
  botframes_= bot_frames_get_global(mState->mLcm->getUnderlyingLCM(), botparam_);  
  
  
  // Vis Config:
  pc_vis_ = new pointcloud_vis( mState->mLcm->getUnderlyingLCM() );
  // obj: id name type reset
  // pts: id name type reset objcoll usergb rgb
  pc_vis_->obj_cfg_list.push_back( obj_cfg(91000,"Pose - Null",5,1) );
  pc_vis_->ptcld_cfg_list.push_back( ptcld_cfg(91001,"Cloud - Null"           ,1,1, 91000,1, { 0.0, 1.0, 1.0} ));
  
  pc_vis_->obj_cfg_list.push_back( obj_cfg(91002,"Pose - Camera",5,1) );
  pc_vis_->ptcld_cfg_list.push_back( ptcld_cfg(91003,"Cloud from RI"           ,1,1, 91000,0, { 1.0, 0.0, 1.0} ));
  
}

void DataProducer::operator()() {
  const float kPi = 4*tan(1);
  const float degToRad = kPi/180;
  while (true) {
    // get submap we created earlier
    LocalMap::Ptr localMap =
      mState->mCollector->getMapManager()->getMap(mState->mActiveMapId);

    // find time range of desired swath (from 45 to 135 degrees)
    int64_t timeMin, timeMax;
    double ang_min = 10 *M_PI/180; // leading edge from the right hand side of sweep
    double ang_max = 170 *M_PI/180;
    //double ang_min = 45*degToRad;
    //double ang_max= 135*degToRad;
    
    int current_utime = drc::Clock::instance()->getCurrentTime();
    //cout << ang_min << " min | " << ang_max << " max\n";
         

    
    mState->mCollector->getLatestSwath(ang_min, ang_max,
                                         timeMin, timeMax); // these didnt work
    cout << timeMin << " timeMin | " << timeMax << " timeMax | "
         << current_utime << " utime\n";
    if (timeMin == last_timeMin_){
      cout << "repeat\n";
      // wait for timer expiration
      boost::asio::io_service service;
      boost::asio::deadline_timer timer(service);
      timer.expires_from_now(boost::posix_time::seconds(1));
      timer.wait();      
      continue; 
    }
    last_timeMin_ = timeMin;
    cout << "process\n";
    
    LocalMap::SpaceTimeBounds bounds;
    bounds.mTimeMin = timeMin;
    bounds.mTimeMax = timeMax;

    // get and publish point cloud corresponding to this time range
    // (for debugging)
    maps::PointCloud::Ptr cloud = localMap->getAsPointCloud(0, bounds);
    bot_lcmgl_t* lcmgl = mState->mLcmGl;
    bot_lcmgl_color3f(lcmgl, 0, 1, 0);
    bot_lcmgl_point_size(lcmgl, 3);
    for (int i = 0; i < cloud->size(); ++i) {
      maps::PointCloud::PointType point = (*cloud)[i];
      bot_lcmgl_begin(lcmgl, LCMGL_POINTS);
      bot_lcmgl_vertex3f(lcmgl, point.x, point.y, point.z);
      bot_lcmgl_end(lcmgl);
    }
    bot_lcmgl_switch_buffer(lcmgl);

    
    
    
    //////////////////////// Output the input cloud (a cloud in world frame) ///////////////////
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZRGB> ());
    cloud2 = localMap->getAsPointCloud(0, bounds);      

    Eigen::Isometry3d null_pose;
    null_pose.setIdentity();
    Isometry3dTime null_poseT = Isometry3dTime(current_utime, null_pose);
    pc_vis_->pose_to_lcm_from_list(91000, null_poseT);  
    pc_vis_->ptcld_to_lcm_from_list(91001, *cloud2, current_utime, current_utime);      
    
    if(1==0){
      cout << "buff\n";
      cout << cloud2->points.size() << "\n";
      if (cloud2->points.size() > 0) {
        pcl::PCDWriter writer;
        stringstream ss2;
        ss2 << "/home/mfallon/drc/software/perception/vehicle-tracker/data/vehicle_"
        << timeMax << ".pcd";
        writer.write (ss2.str(), *cloud2, false);
      }
    }
    

    
    Eigen::Isometry3d ref_pose;
    botframes_cpp_->get_trans_with_utime( botframes_ ,  "CAMERA", "local", current_utime, ref_pose);   // ...? not sure what to use
    
    

    
    
    
/*    
    // set up sample camera pose
    Eigen::Vector3f trans(0,0,0);
    Eigen::Matrix3f rot;
    rot.col(0) = -Eigen::Vector3f::UnitY();
    rot.col(1) = -Eigen::Vector3f::UnitZ();
    rot.col(2) = Eigen::Vector3f::UnitX();
    Eigen::Isometry3f pose = Eigen::Isometry3f::Identity();
    pose.linear() = rot;
    pose.translation() = trans;
*/
    
    // set up sample camera projection parameters
    Eigen::Matrix4f projector = Eigen::Matrix4f::Identity();
    int width=1024;
    int height=544;
    if (1==0){ // default example
      width = 200;
      height = 200;
      projector(0,0) = projector(1,1) = 50;  // focal length of 50 pixels
      projector(0,2) = width/2.0;            // cop at center of image
      projector(1,2) = height/2.0;
    }else if (1==0){ // correct
      width =1024;
      height =544;
      projector(0,0) = projector(1,1) = 610.1778;  // focal length of 50 pixels
      projector(0,2) = width/2.0;                  // cop at center of image
      projector(1,2) = height/2.0;
    }else{
      width =256;//256;
      height =136;
      projector(0,0) = projector(1,1) = 152.54445;  // focal length of 50 pixels
      projector(0,2) = width/2.0;                  // cop at center of image
      projector(1,2) = height/2.0;
    }
    // create range image
    Eigen::Isometry3f ref_pose_f = isometryDoubleToFloat(ref_pose);
    maps::RangeImage rangeImage =
    localMap->getAsRangeImage(width, height, ref_pose_f, projector, bounds);
      
      
    

      
    Eigen::Isometry3d fixrotation_pose;
    fixrotation_pose.setIdentity();
    fixrotation_pose.translation() << 0,0,0;    
    Eigen::Quaterniond fix_r = euler_to_quat(0.0*M_PI/180.0, -90.0*M_PI/180.0 , 90.0*M_PI/180.0);
    fixrotation_pose.rotate(fix_r);    
    ref_pose = ref_pose*fixrotation_pose; 
    

    
    
    

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud3 (new pcl::PointCloud<pcl::PointXYZRGB> ());
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        Eigen::Vector3f point;
        rangeImage.mImage->getPoint(j,i, point);
        //cout << point[0] << ", " << point[1] << ", " << point[2] << "\n";
        pcl::PointXYZRGB pt1;
        pt1.x = point[0];       pt1.y = point[1];    pt1.z = point[2];  
        pt1.r = 0;           pt1.g =0;          pt1.b =255;
        cloud3->points.push_back(pt1);          
      }
    }
  
  int decimate_=4;
    
    
    if( mState->last_mask_.utime!=0){
      cout <<"got mask and depth\n";     
    // cout <<"got mask and depth\n";
    uint8_t* mask_buf =  mState->getMask();
    //imgutils_->sendImage(mask_buf, msg->utime, 1024, 544, 1, string("UNZIPPED")  );

    // Colorise the depth points using the mask
    int j2=0;
    int w = 1024;
    int h = 544;
    
    for(int v=0; v<h; v=v+ decimate_) { // t2b
      for(int u=0; u<w; u=u+decimate_ ) {  //l2r
          if (mask_buf[v*w + u] > 0){ // if the mask is not black, apply it as red
            cloud3->points[j2].r = 255;//mask_buf[v*w + u];
            cloud3->points[j2].g = 0;//cloud3->points[j2].g/4;
            cloud3->points[j2].b = 0;//cloud3->points[j2].b/4; // reduce other color for emphaise
          }
          j2++;
      }
    }         
      
      
    }
    
  

    Isometry3dTime ref_poseT = Isometry3dTime(current_utime, ref_pose);
    pc_vis_->pose_to_lcm_from_list(91002, ref_poseT);  
    pc_vis_->ptcld_to_lcm_from_list(91003, *cloud3, current_utime, current_utime);      
  

    // get range image pixel values and store to file
    float* ranges = rangeImage.mImage->getRangesArray();
    std::ofstream ofs("/tmp/ranges.txt");
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        ofs << ranges[i*width + j] << " ";
      }
      ofs << std::endl;
    }
    ofs.close();


    

  }
}



int main() {
  // create state object instance
  State state;

  // create new submap
  LocalMap::Spec mapSpec;
  mapSpec.mId = 1;
  mapSpec.mPointBufferSize = 5000;
  mapSpec.mActive = true;
  mapSpec.mBoundMin = Eigen::Vector3f(-1,-1,-1)*10;
  mapSpec.mBoundMax = Eigen::Vector3f(1,1,1)*10;
  mapSpec.mResolution = 0.01;
  state.mActiveMapId = state.mCollector->getMapManager()->createMap(mapSpec);

  // start running wrapper
  std::string laserChannel("SCAN");
  state.mCollector->getDataReceiver()->
    addChannel(laserChannel,
               SensorDataReceiver::SensorTypePlanarLidar,
               laserChannel, "local");
  state.mCollector->start();

  // start producing data
  DataProducer producer(&state);
  boost::thread producerThread(boost::ref(producer));

  // main lcm loop
  while (0 == state.mLcm->handle());

  // join pending threads
  producerThread.join();
}
