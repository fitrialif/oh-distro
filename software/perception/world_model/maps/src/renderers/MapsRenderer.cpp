#include <iostream>
#include <sstream>
#include <unordered_map>

#include <gtkmm.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <lcm/lcm-cpp.hpp>

#include <drc_utils/Clock.hpp>
#include <gtkmm-renderer/RendererBase.hpp>

#include <lcmtypes/drc/map_command_t.hpp>
#include <lcmtypes/drc/map_macro_t.hpp>
#include <lcmtypes/drc/data_request_t.hpp>
#include <lcmtypes/occ_map/pixel_map_t.hpp>
#include <lcmtypes/bot_core/image_t.hpp>
#include <lcmtypes/drc/map_request_bbox_t.hpp>

#include <bot_vis/viewer.h>

// TODO: should use c++ version
#include <lcmtypes/occ_map_pixel_map_t.h>

#include <occ_map/PixelMap.hpp>

#include <maps/ViewClient.hpp>
#include <maps/Utils.hpp>
#include <maps/BotWrapper.hpp>
#include "MeshRenderer.hpp"
#include "InteractiveBox.hpp"

namespace maps {

class MapsRenderer : public gtkmm::RendererBase, ViewClient::Listener {
protected:
  enum InputMode {
    InputModeCamera=0,
    InputModeRect,
    InputModeDepth
  };

  enum MacroCommand {
    MacroCommandClearMap,
    MacroCommandHighResScan
  };

  struct Frustum {
    std::vector<Eigen::Vector4f> mPlanes;
    float mNear;
    float mFar;
    Eigen::Vector3f mPos;
    Eigen::Vector3f mDir;
  };

  struct ViewMetaData {
    typedef std::shared_ptr<ViewMetaData> Ptr;
    MapsRenderer* mRenderer;
    int64_t mId;
    bool mVisible;
    Eigen::Vector3f mColor;
    std::string mLabel;
    std::shared_ptr<Gtk::HBox> mBox;
    Gtk::ToggleButton* mToggleButton;
    Eigen::Isometry3f mLatestTransform;

    void onCancelButton() {
      maps::ViewBase::Spec spec;
      spec.mMapId = 0;
      spec.mViewId = mId;
      spec.mResolution = spec.mFrequency = 0;
      spec.mTimeMin = spec.mTimeMax = 0;
      spec.mActive = false;
      spec.mType = maps::ViewBase::TypePointCloud;
      mRenderer->mViewClient.request(spec);
      mRenderer->requestDraw();
    }
    void onToggleButton() {
      mVisible = mToggleButton->get_active();
      mRenderer->requestDraw();
    }
  };

protected:
  // view control parameters
  double mMinZ;
  double mMaxZ;
  double mPointSize;
  int mColorMode;
  int mMeshMode;

  // view list parameters
  Gtk::VBox* mViewListBox;
  typedef std::unordered_map<int64_t,ViewMetaData::Ptr > DataMap;
  DataMap mViewData;
  Glib::Dispatcher mViewDataDispatcher;

  // request parameters
  int mInputMode;
  Gtk::ComboBox* mInputModeComboBox;
  int mRequestType;
  double mRequestFrequency;
  double mRequestResolution;
  int mRequestTimeWindow;
  bool mRequestRelativeLocation;
  bool mRequestRawScan;
  bool mDragging;
  Eigen::Vector2f mDragPoint1;
  Eigen::Vector2f mDragPoint2;  
  Eigen::Vector2f mBoxCorner1;
  Eigen::Vector2f mBoxCorner2;
  GLdouble mModelViewGl[16];
  GLdouble mProjectionGl[16];
  GLint mViewportGl[4];
  Eigen::Isometry3f mModelViewMatrix;
  Eigen::Matrix4f mProjectionMatrix;
  std::vector<int> mViewport;
  float mBaseValue;
  bool mBoxValid;
  Frustum mFrustum;
  Gtk::ToggleButton* mAdjustRequestBoxToggle;
  Gtk::ToggleButton* mShowRequestBoxToggle;
  bool mShowRequestBox;
  bool mRequestBoxInit;
  int mRequestBoxDataSource;
  InteractiveBox mInteractiveBox;

  // command parameters
  int mMacroCommand;

  // for pixel map rendering
  std::shared_ptr<occ_map::PixelMap<float> > mPixelMap;

  MeshRenderer mMeshRenderer;
  ViewClient mViewClient;
  BotWrapper::Ptr mBotWrapper;
  
public:

  MapsRenderer(BotViewer* iViewer, const int iPriority,
               const lcm_t* iLcm,
               const BotParam* iParam, const BotFrames* iFrames)
    : gtkmm::RendererBase("Maps", iViewer, iPriority, iLcm, iParam, iFrames) {

    // set up robot time clock
    drc::Clock::instance()->setLcm(getLcm());
    drc::Clock::instance()->setVerbose(false);

    // create and show ui widgets
    setupWidgets();

    // set up internal variables
    mBoxValid = false;
    mDragging = false;
    mBotWrapper.reset(new BotWrapper(getLcm(), getBotParam(), getBotFrames()));
    mMeshRenderer.setBotObjects(getLcm(), getBotParam(), getBotFrames());
    mMeshRenderer.setCameraChannel("CAMERALEFT");
    mViewClient.setBotWrapper(mBotWrapper);
    mViewClient.addListener(this);
    mViewClient.addViewChannel("MAP_CONTROL_HEIGHT");
    mViewClient.addViewChannel("MAP_DEBUG");

    // set callback for pixel maps
    // TODO: temporary channel
    getLcm()->subscribe("TERRAIN_DIST_MAP", &MapsRenderer::onPixelMap, this);

    // start listening for view data
    mViewClient.start();
  }

  void onPixelMap(const lcm::ReceiveBuffer* iBuf,
                  const std::string& iChannel,
                  const occ_map::pixel_map_t* iMessage) {
    // TODO: this assumes float type
    // TODO: pixel map should support c++ lcm type
    // for now transcode to c type
    int encodedSize = iMessage->getEncodedSize();
    std::vector<uint8_t> bytes(encodedSize);
    iMessage->encode(&bytes[0], 0, encodedSize);
    occ_map_pixel_map_t msg;
    occ_map_pixel_map_t_decode(&bytes[0], 0, encodedSize, &msg);

    // form convenience wrapper object and set mesh texture
    mPixelMap.reset(new occ_map::PixelMap<float>(&msg));
    Eigen::Projective3f xform = Eigen::Projective3f::Identity();
    xform(0,0) = xform(1,1) = 1/mPixelMap->metersPerPixel;
    xform(0,3) = -mPixelMap->xy0[0]/mPixelMap->metersPerPixel;
    xform(1,3) = -mPixelMap->xy0[1]/mPixelMap->metersPerPixel;
    mMeshRenderer.setTexture(mPixelMap->dimensions[0],
                             mPixelMap->dimensions[1],
                             sizeof(float)*mPixelMap->dimensions[0],
                             bot_core::image_t::PIXEL_FORMAT_FLOAT_GRAY32,
                             (uint8_t*)mPixelMap->data, xform);
    requestDraw();
  }

  void onInputModeChanged() {
    if (mInputMode == InputModeCamera) {
      getBotEventHandler()->picking = 0;
    }
  }

  void onAdjustBoxToggleChanged() {
    getBotEventHandler()->picking = mAdjustRequestBoxToggle->get_active();
  }

  void setupWidgets() {
    Gtk::Container* container = getGtkContainer();
    Gtk::Notebook* notebook = Gtk::manage(new Gtk::Notebook());
    container->add(*notebook);
    std::vector<int> ids;
    std::vector<std::string> labels;

    // view controls
    {
      Gtk::VBox* appearanceBox = Gtk::manage(new Gtk::VBox());
      notebook->append_page(*appearanceBox, "Appearance");

      ids = { MeshRenderer::ColorModeFlat, MeshRenderer::ColorModeHeight,
              MeshRenderer::ColorModeRange, MeshRenderer::ColorModeNormal,
              MeshRenderer::ColorModeCamera, MeshRenderer::ColorModeMap };
      labels = { "Flat", "Height", "Range", "Normal", "Camera", "Pixelmap"};
      mColorMode = MeshRenderer::ColorModeHeight;
      addCombo("Color Mode", mColorMode, labels, ids, appearanceBox);

      ids = { MeshRenderer::MeshModePoints, MeshRenderer::MeshModeWireframe,
              MeshRenderer::MeshModeFilled };
      labels = { "Points", "Wireframe", "Filled"};
      mMeshMode = MeshRenderer::MeshModePoints;
      addCombo("Draw Mode", mMeshMode, labels, ids, appearanceBox);

      mPointSize = 3;
      addSlider("Point Size", mPointSize, 0.1, 10, 0.1, appearanceBox);

      mMinZ = 0;
      addSlider("Z Scale Min", mMinZ, -1, 2, 0.01, appearanceBox);

      mMaxZ = 1;
      addSlider("Z Scale Max", mMaxZ, -1, 2, 0.01, appearanceBox);
    }

    // view list box (will fill in dynamically)
    {
      mViewListBox = Gtk::manage(new Gtk::VBox());
      Gtk::Button* clearButton = Gtk::manage(new Gtk::Button("Clear All"));
      clearButton->signal_clicked().connect
        (sigc::mem_fun(*this, &MapsRenderer::onClearViewsButton));
      mViewListBox->pack_start(*clearButton, false, false);
      notebook->append_page(*mViewListBox, "Views");
    }

    // simple request tab
    {
      Gtk::VBox* requestBox = Gtk::manage(new Gtk::VBox());
      notebook->append_page(*requestBox, "Request");

      Gdk::Color color;
      color.set_rgb_p(0.8,1.0,0.8);
      Gtk::HBox* box = Gtk::manage(new Gtk::HBox());
      Gtk::Button* button = Gtk::manage(new Gtk::Button("Create Box"));
      button->signal_clicked().connect
        (sigc::mem_fun(*this, &MapsRenderer::onCreateBoxButton));
      box->pack_start(*button, false, false);
      mAdjustRequestBoxToggle = Gtk::manage(new Gtk::ToggleButton());
      mAdjustRequestBoxToggle->set_label("Adjust Box");
      mAdjustRequestBoxToggle->modify_bg(Gtk::STATE_ACTIVE, color);
      mAdjustRequestBoxToggle->modify_bg(Gtk::STATE_PRELIGHT, color);
      mAdjustRequestBoxToggle->signal_toggled().connect
        (sigc::mem_fun(*this, &MapsRenderer::onAdjustBoxToggleChanged));
      box->pack_start(*mAdjustRequestBoxToggle, false, false);
      mShowRequestBoxToggle = Gtk::manage(new Gtk::ToggleButton());
      mShowRequestBoxToggle->set_label("Show Box");
      mShowRequestBoxToggle->modify_bg(Gtk::STATE_ACTIVE, color);
      mShowRequestBoxToggle->modify_bg(Gtk::STATE_PRELIGHT, color);
      mShowRequestBox = false;
      bind(mShowRequestBoxToggle, "Show Request Box", mShowRequestBox);
      box->pack_start(*mShowRequestBoxToggle, false, false);
      requestBox->pack_start(*box, false, false);

      mRequestTimeWindow = 0;
      labels = { "Laser", "Stereo Head", "Stereo L.Hand", "Stereo R.Hand" };
      ids = { drc::map_request_bbox_t::LASER,
              drc::map_request_bbox_t::STEREO_HEAD,
              drc::map_request_bbox_t::STEREO_LHAND,
              drc::map_request_bbox_t::STEREO_RHAND };
      addCombo("Data Source", mRequestBoxDataSource, labels, ids, requestBox);
      addSpin("Time Window (s)", mRequestTimeWindow, 0, 30, 1, requestBox);
      mRequestRawScan = false;
      addCheck("Unfiltered Scan?", mRequestRawScan, requestBox);
      button = Gtk::manage(new Gtk::Button("Send Request"));
      button->signal_clicked().connect
        (sigc::mem_fun(*this, &MapsRenderer::onSendBoxRequestButton));
      requestBox->pack_start(*button, false, false);
      mRequestBoxInit = false;
    }

    // request controls box
    if (false) {
      Gtk::VBox* requestBox = Gtk::manage(new Gtk::VBox());
      notebook->append_page(*requestBox, "Request");

      Gtk::Button* clearButton = Gtk::manage(new Gtk::Button("Clear"));
      clearButton->signal_clicked().connect
        (sigc::mem_fun(*this, &MapsRenderer::onClearRequestButton));
      requestBox->add(*clearButton);

      ids = { InputModeCamera, InputModeRect, InputModeDepth };
      labels = { "Move View", "Drag Rect", "Adjust Depth" };
      mInputMode = InputModeCamera;
      mInputModeComboBox =
        addCombo("Input Mode", mInputMode, labels, ids, requestBox);
      mInputModeComboBox->signal_changed().connect
        (sigc::mem_fun(*this, &MapsRenderer::onInputModeChanged));

      ids = { ViewBase::TypeOctree, ViewBase::TypePointCloud,
              ViewBase::TypeDepthImage, ViewBase::TypeDepthImage+1 };
      labels = { "Octree", "Cloud", "Depth", "Stereo" };
      mRequestType = ViewBase::TypeOctree;
      addCombo("Request Type", mRequestType, labels, ids, requestBox);

      mRequestFrequency = 0.1;
      addSpin("Frequency (Hz)", mRequestFrequency, 0, 10, 0.1, requestBox);

      mRequestResolution = 0.1;
      addSpin("Resolution (m)", mRequestResolution, 0.01, 1, 0.01, requestBox);

      mRequestTimeWindow = 0;
      addSpin("Time Window (s)", mRequestTimeWindow, 0, 30, 1, requestBox);

      mRequestRelativeLocation = false;
      addCheck("Relative Position?", mRequestRelativeLocation, requestBox);

      mRequestRawScan = false;
      addCheck("Unfiltered Scan?", mRequestRawScan, requestBox);

      Gtk::Button* requestButton = Gtk::manage(new Gtk::Button("Send Request"));
      requestButton->signal_clicked().connect
        (sigc::mem_fun(*this, &MapsRenderer::onRequestButton));
      requestBox->add(*requestButton);
    }

    // macro command box
    if (false) {
      Gtk::VBox* commandBox = Gtk::manage(new Gtk::VBox());
      notebook->append_page(*commandBox, "Command");

      ids = { MacroCommandClearMap, MacroCommandHighResScan };
      labels = { "Clear Map", "High-Res Scan" };
      mMacroCommand = MacroCommandClearMap;
      addCombo("Command", mMacroCommand, labels, ids, commandBox);

      Gtk::Button* commandButton = Gtk::manage(new Gtk::Button("Send Command"));
      commandButton->signal_clicked().connect
        (sigc::mem_fun(*this, &MapsRenderer::onCommandButton));
      commandBox->add(*commandButton);
    }

    notebook->show_all();

    // handler for updating ui widgets when views are added
    mViewDataDispatcher.connect
      (sigc::mem_fun(*this, &MapsRenderer::addViewWidgets));
  }

  ~MapsRenderer() {
  }

  // view client callbacks
  void notifyData(const int64_t iViewId) {
    addViewMetaData(iViewId);
    DataMap::const_iterator item = mViewData.find(iViewId);
    ViewClient::ViewPtr view = mViewClient.getView(iViewId);
    if ((item != mViewData.end()) && (view != NULL)) {
      Eigen::Isometry3f headToLocal;
      if (mBotWrapper->getTransform("head", "local", headToLocal,
                                    view->getUpdateTime())) {
        Eigen::Matrix3f rotMatx = headToLocal.linear();
        float theta = atan2(rotMatx(1,0), rotMatx(0,0));
        Eigen::Matrix3f rotation;
        rotation = Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ());
        headToLocal.linear() = rotation;
        item->second->mLatestTransform = headToLocal;
      }
    }
    requestDraw();
  }
  void notifyCatalog(const bool iChanged) {
    if (!iChanged) return;
    std::vector<ViewClient::ViewPtr> views = mViewClient.getAllViews();
    DataMap::const_iterator iter;
    for (iter = mViewData.begin(); iter != mViewData.end(); ) {
      bool found = false;
      for (size_t i = 0; i < views.size(); ++i) {
        if (views[i]->getId() == iter->first) {
          found = true;
          break;
        }
      }
      if (!found) mViewData.erase(iter++);
      else ++iter;
    }
    requestDraw();
  }

  void onClearRequestButton() {
    mBoxValid = false;
    mInputModeComboBox->set_active(InputModeCamera);
    requestDraw();
  }

  void onRequestButton() {
    if (!mBoxValid) return;
    ViewBase::Spec spec;
    spec.mActive = true;
    // TODO: HACK for stereo depth
    if (mRequestType == ViewBase::TypeDepthImage+1) {
      spec.mType = ViewBase::TypeDepthImage;
      spec.mViewId = drc::data_request_t::STEREO_MAP_HEAD;
    }
    else {
      spec.mType = ViewBase::Type(mRequestType);
    }
    spec.mResolution = mRequestResolution;
    spec.mFrequency = mRequestFrequency;
    spec.mRelativeTime = false;
    if (mRequestTimeWindow > 0) {
      spec.mTimeMin = -mRequestTimeWindow*1e6;
      spec.mTimeMax = 0;
      spec.mRelativeTime = true;
    }
    spec.mClipPlanes = mFrustum.mPlanes;
    spec.mRelativeLocation = mRequestRelativeLocation;
    spec.mMapId = mRequestRawScan ? 2 : 1;

    // compute depth image transform from gl view parameters
    if (spec.mType == ViewBase::TypeDepthImage) {
      bool orthographic = Utils::isOrthographic(mProjectionMatrix.matrix());
      int idx = (orthographic ? 2 : 3);
      mProjectionMatrix(2, idx) = 1;
      mProjectionMatrix(2, 5-idx) = 0;
      mProjectionMatrix(3,2) = fabs(mProjectionMatrix(3,2));
      Eigen::Projective3f view = Eigen::Projective3f::Identity();
      view(0,0) = mViewport[2]/2;  view(0,3) = mViewport[2]/2 + mViewport[0];
      view(1,1) = mViewport[3]/2;  view(1,3) = mViewport[3]/2 + mViewport[1];
      Eigen::Translation3f subView(-mBoxCorner1[0], -mBoxCorner1[1], 0);
      Eigen::Affine3f rotation = Eigen::Affine3f::Identity();
      rotation(1,1) = rotation(2,2) = -1;
      spec.mTransform =
        subView*view*mProjectionMatrix*rotation*mModelViewMatrix;
      spec.mWidth = ceil(mBoxCorner2[0]-mBoxCorner1[0]);
      spec.mHeight = ceil(mBoxCorner2[1]-mBoxCorner1[1]);
    }

    // recast bound planes and transform with respect to sensor head
    if (spec.mRelativeLocation) {
      Eigen::Isometry3f headToLocal;
      if (mBotWrapper->getTransform("head", "local", headToLocal)) {
        Eigen::Matrix3f rotMatx = headToLocal.linear();
        float theta = atan2(rotMatx(1,0), rotMatx(0,0));
        Eigen::Matrix3f rotation;
        rotation = Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ());
        headToLocal.linear() = rotation;
        Eigen::Matrix4f planeTransform = headToLocal.matrix().transpose();
        for (size_t i = 0; i < spec.mClipPlanes.size(); ++i) {
          spec.mClipPlanes[i] = planeTransform*spec.mClipPlanes[i];
        }
        spec.mTransform = spec.mTransform*headToLocal;
      }
    }
    mViewClient.request(spec);
    mInputModeComboBox->set_active(InputModeCamera);
  }

  void onCommandButton() {
    if (mMacroCommand == MacroCommandClearMap) {
      drc::map_command_t command;
      command.utime = drc::Clock::instance()->getCurrentTime();
      command.map_id = -1;
      command.command = drc::map_command_t::CLEAR;
      getLcm()->publish("MAP_COMMAND", &command);
    }
    else if (mMacroCommand == MacroCommandHighResScan) {
      drc::map_macro_t macro;
      macro.utime = drc::Clock::instance()->getCurrentTime();
      macro.command = drc::map_macro_t::CREATE_DENSE_MAP;
      getLcm()->publish("MAP_MACRO", &macro);
    }
  }

  void onCreateBoxButton() {
    Eigen::Isometry3f headToLocal;
    Eigen::Vector3f position(0,0,0);
    if (mBotWrapper->getTransform("head", "local", headToLocal)) {
      position = headToLocal.translation();
      position[0] += 0.5;
    }
    mInteractiveBox.createBox(position, 0.5);
    mRequestBoxInit = true;
    mShowRequestBoxToggle->set_active(true);
    requestDraw();
  }

  void onSendBoxRequestButton() {
    if (!mShowRequestBox) {
      std::cout << "No box shown, so request not sent" << std::endl;
      return;
    }
    drc::map_request_bbox_t msg;
    Eigen::Vector3f position, scale;
    Eigen::Quaternionf orientation;
    mInteractiveBox.getBoxParameters(position, scale, orientation);
    msg.center[0] = (int16_t)(position[0]*128 + 0.5f);
    msg.center[1] = (int16_t)(position[1]*128 + 0.5f);
    msg.center[2] = (int16_t)(position[2]*128 + 0.5f);
    msg.size[0] = (uint8_t)(scale[0]*64 + 0.5f);
    msg.size[1] = (uint8_t)(scale[1]*64 + 0.5f);
    msg.size[2] = (uint8_t)(scale[2]*64 + 0.5f);
    msg.time_window = mRequestTimeWindow;
    Eigen::Vector3f rpy = orientation.matrix().eulerAngles(2,1,0);
    for (int i = 0; i < 3; ++i) msg.rpy[i] = rpy[i]*1800/acos(-1);
    msg.params = mRequestBoxDataSource;
    if (mRequestRawScan) msg.params |= drc::map_request_bbox_t::RAW_MASK;
    getLcm()->publish("MAP_REQUEST_BBOX", &msg);
    mAdjustRequestBoxToggle->set_active(false);
  }

  void onClearViewsButton() {
    mViewClient.clearAll();
  }

  double pickQuery(const double iRayStart[3], const double iRayDir[3]) {
    if (mInputMode == InputModeCamera) {
      getBotEventHandler()->picking = 0;
      return -1;
    }
    else if (!mAdjustRequestBoxToggle->get_active()) {
      getBotEventHandler()->picking = 0;
      return -1;
    }
    else {
      return 0;
    }
  }

  bool mousePress(const GdkEventButton* iEvent,
                  const double iRayStart[3], const double iRayDir[3]) {
    if (mAdjustRequestBoxToggle->get_active()) {
      Eigen::Vector3f origin(iRayStart[0], iRayStart[1], iRayStart[2]);
      Eigen::Vector3f dir(iRayDir[0], iRayDir[1], iRayDir[2]);
      Eigen::Vector2f clickPt(iEvent->x, iEvent->y);
      return mInteractiveBox.mousePress(clickPt, iEvent->button, origin, dir);
    }

    if (mInputMode == InputModeRect) {
      if (iEvent->button == 1) {
        mDragging = true;
        mBoxValid = false;
        mDragPoint1 = Eigen::Vector2f(iEvent->x, iEvent->y);
        mDragPoint2 = mDragPoint1;
        requestDraw();
        return true;
      }
    }
    else if (mInputMode == InputModeDepth) {
      if (mBoxValid) {
        if ((iEvent->button == 1) || (iEvent->button == 3)) {
          mDragging = true;
          mDragPoint1 = Eigen::Vector2f(iEvent->x, iEvent->y);
          mDragPoint2 = mDragPoint1;
          mBaseValue = (iEvent->button == 1) ? mFrustum.mNear : mFrustum.mFar;
          requestDraw();
          return true;
        }
      }
    }
    return false;
  }

  bool mouseRelease(const GdkEventButton* iEvent,
                    const double iRayStart[3], const double iRayDir[3]) {
    if (mAdjustRequestBoxToggle->get_active()) {
      Eigen::Vector3f origin(iRayStart[0], iRayStart[1], iRayStart[2]);
      Eigen::Vector3f dir(iRayDir[0], iRayDir[1], iRayDir[2]);
      Eigen::Vector2f curPt(iEvent->x, iEvent->y);
      return mInteractiveBox.mouseRelease(curPt, iEvent->button, origin, dir);
    }

    if (mInputMode == InputModeRect) {
      if (iEvent->button == 1) {
        mDragging = false;

        if ((mDragPoint2 - mDragPoint1).norm() < 1) {
          requestDraw();
          return false;
        }

        // compute min and max extents of drag
        Eigen::Vector2f dragPoint1, dragPoint2;
        mBoxCorner1[0] = std::min(mDragPoint1[0], mDragPoint2[0]);
        mBoxCorner1[1] = std::min(mDragPoint1[1], mDragPoint2[1]);
        mBoxCorner2[0] = std::max(mDragPoint1[0], mDragPoint2[0]);
        mBoxCorner2[1] = std::max(mDragPoint1[1], mDragPoint2[1]);
        
        // get view info
        getViewInfo();

        // eye position and look direction
        Eigen::Vector3f pos =
          -mModelViewMatrix.linear().inverse()*mModelViewMatrix.translation();
        Eigen::Vector3f dir = -mModelViewMatrix.linear().block<1,3>(2,0);
        dir.normalize();
        mFrustum.mPos = pos;
        mFrustum.mDir = dir;

        // compute four corner rays
        int height = getGlDrawingArea()->get_allocation().get_height();
        double u1(mBoxCorner1[0]), v1(height - mBoxCorner1[1]);
        double u2(mBoxCorner2[0]), v2(height - mBoxCorner2[1]);
        mFrustum.mNear = 5;
        mFrustum.mFar = 10;

        // first four planes
        mFrustum.mPlanes.resize(6);
        mFrustum.mPlanes[0] = computePlane(u1,v1, u2,v1);
        mFrustum.mPlanes[1] = computePlane(u2,v1, u2,v2);
        mFrustum.mPlanes[2] = computePlane(u2,v2, u1,v2);
        mFrustum.mPlanes[3] = computePlane(u1,v2, u1,v1);

        // front and back
        updateFrontAndBackPlanes(mFrustum);

        mBoxValid = true;
        mInputModeComboBox->set_active(InputModeCamera);

        requestDraw();
        return true;
      }
    }
    else if (mInputMode == InputModeDepth) {
      mDragging = false;
    }
    return false;
  }

  bool mouseMotion(const GdkEventMotion* iEvent,
                   const double iRayStart[3], const double iRayDir[3]) {
    bool button1 = (iEvent->state & GDK_BUTTON1_MASK) != 0;
    bool button2 = (iEvent->state & GDK_BUTTON2_MASK) != 0;
    bool button3 = (iEvent->state & GDK_BUTTON3_MASK) != 0;

    if (mAdjustRequestBoxToggle->get_active()) {
      Eigen::Vector3f origin(iRayStart[0], iRayStart[1], iRayStart[2]);
      Eigen::Vector3f dir(iRayDir[0], iRayDir[1], iRayDir[2]);
      Eigen::Vector2f curPt(iEvent->x, iEvent->y);
      int buttonMask = (button3 << 2) | (button2 << 1) | button1;
      bool handled = mInteractiveBox.mouseMotion(curPt, buttonMask,
                                                 origin, dir);
      if (handled) requestDraw();
      return handled;
    }

    if (mInputMode == InputModeRect) {
      if (button1 && mDragging) {
        mDragPoint2 = Eigen::Vector2f(iEvent->x, iEvent->y);
        requestDraw();
        return true;
      }
    }
    else if (mInputMode == InputModeDepth) {
      if (mBoxValid && mDragging) {
        mDragPoint2 = Eigen::Vector2f(iEvent->x, iEvent->y);
        float dist = mDragPoint2[1] - mDragPoint1[1];
        float scaledDist = dist/100;
        if (button1) {
          mFrustum.mNear = std::max(0.0f, mBaseValue+scaledDist);
          requestDraw();
          return true;
        }
        else if (button3) {
          mFrustum.mFar = std::max(0.0f, mBaseValue+scaledDist);
          requestDraw();
          return true;
        }
      }
    }
    return false;
  }

  void getViewInfo() {
    glGetDoublev(GL_MODELVIEW_MATRIX, mModelViewGl);
    glGetDoublev(GL_PROJECTION_MATRIX, mProjectionGl);
    glGetIntegerv(GL_VIEWPORT, mViewportGl);
    mViewport.resize(4);
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        mModelViewMatrix(i,j) = mModelViewGl[4*j+i];
        mProjectionMatrix(i,j) = mProjectionGl[4*j+i];
      }
      mViewport[i] = mViewportGl[i];
    }
  }

  void draw() {
    // draw each view
    std::vector<ViewClient::ViewPtr> views = mViewClient.getAllViews();
    for (size_t v = 0; v < views.size(); ++v) {
      drawView(views[v]);
    }

    if (mRequestBoxInit) {
      getViewInfo();
      mInteractiveBox.setBoxValid(mShowRequestBox);
      mInteractiveBox.drawBox();
    }

    // draw user selection for view box
    drawViewSelection();
  }

  void drawViewSelection() {
    if (mDragging && (mInputMode == InputModeRect)) {
      int width = getGlDrawingArea()->get_allocation().get_width();
      int height = getGlDrawingArea()->get_allocation().get_height();
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      glOrtho(0, width, height, 0, -1, 1);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();
      glDisable(GL_DEPTH_TEST);

      glColor3f(0,0,1);
      glBegin(GL_LINE_LOOP);
      glVertex2f(mDragPoint1[0], mDragPoint1[1]);
      glVertex2f(mDragPoint2[0], mDragPoint1[1]);
      glVertex2f(mDragPoint2[0], mDragPoint2[1]);
      glVertex2f(mDragPoint1[0], mDragPoint2[1]);
      glEnd();

      glEnable(GL_DEPTH_TEST);
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
    }

    if (mBoxValid) {
      updateFrontAndBackPlanes(mFrustum);
      drawFrustum(mFrustum, Eigen::Vector3f(0,0,1));
    }
  }

  void drawFrustum(const Frustum& iFrustum, const Eigen::Vector3f& iColor) {
    std::vector<Eigen::Vector3f> vertices;
    std::vector<std::vector<int> > faces;
    maps::Utils::polyhedronFromPlanes(iFrustum.mPlanes, vertices, faces);
    glColor3f(iColor[0], iColor[1], iColor[2]);
    glLineWidth(3);
    for (size_t i = 0; i < faces.size(); ++i) {
      glBegin(GL_LINE_LOOP);
      for (size_t j = 0; j < faces[i].size(); ++j) {
        Eigen::Vector3f pt = vertices[faces[i][j]];
        glVertex3f(pt[0], pt[1], pt[2]);
      }
      glEnd();
    }
  }

  void drawView(const ViewClient::ViewPtr& iView) {
    // try to find ancillary data for this view; add if it doesn't exist
    int64_t id = iView->getId();
    addViewMetaData(id);
    ViewMetaData::Ptr data = mViewData[id];
    if (!data->mVisible) return;

    // set mesh properties
    mMeshRenderer.setRangeOrigin(data->mLatestTransform.translation());
    mMeshRenderer.setScaleRange(mMinZ, mMaxZ);
    mMeshRenderer.setPointSize(mPointSize);
    Eigen::Projective3f worldToMap = iView->getTransform();
    Eigen::Projective3f mapToWorld = worldToMap.inverse();
    Eigen::Matrix3f calib;
    Eigen::Isometry3f pose;
    bool ortho;
    maps::Utils::factorViewMatrix(worldToMap, calib, pose, ortho);
    mMeshRenderer.setNormalZero(-pose.linear().col(2));

    // draw frustum
    ViewBase::Spec viewSpec;
    if (mViewClient.getSpec(id, viewSpec)) {
      if (viewSpec.mClipPlanes.size() > 0) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        if (viewSpec.mRelativeLocation) {
          glMultMatrixf(data->mLatestTransform.data());
        }
        Frustum frustum;
        frustum.mPlanes = viewSpec.mClipPlanes;
        drawFrustum(frustum, data->mColor);
        glPopMatrix();
      }
    }

    // see whether we need to (and can) get a mesh representation
    bool usePoints = false;
    maps::TriangleMesh::Ptr mesh;
    if (mMeshMode == MeshRenderer::MeshModePoints) {
      usePoints = true;
    }
    else {
      mesh = iView->getAsMesh(false);
      if (mesh == NULL) usePoints = true;
    }

    // just a point cloud
    if (usePoints) {
      mesh.reset(new maps::TriangleMesh());
      maps::PointCloud::Ptr cloud = iView->getAsPointCloud(false);
      mesh->mVertices.reserve(cloud->size());
      for (size_t i = 0; i < cloud->size(); ++i) {
        mesh->mVertices.push_back((*cloud)[i].getVector3fMap());
      }
    }

    // add ground polygon if using pixelmap
    if ((mPixelMap != NULL) && (mColorMode == MeshRenderer::ColorModeMap)) {
      float z = 0;  // TODO: for future user-selected height shift
      std::vector<Eigen::Vector4f> pts(4);
      pts[0] = Eigen::Vector4f(mPixelMap->xy0[0], mPixelMap->xy0[1], z, 1);
      pts[1] = Eigen::Vector4f(mPixelMap->xy0[0], mPixelMap->xy1[1], z, 1);
      pts[2] = Eigen::Vector4f(mPixelMap->xy1[0], mPixelMap->xy1[1], z, 1);
      pts[3] = Eigen::Vector4f(mPixelMap->xy1[0], mPixelMap->xy0[1], z, 1);
      Eigen::Projective3f transform = worldToMap;
      for (int k = 0; k < 4; ++k) {
        pts[k] = transform*pts[k];
        pts[k] /= pts[k][3];
        mesh->mVertices.push_back(pts[k].head<3>());
      }
      int index = (int)mesh->mVertices.size() - 4;
      mesh->mFaces.push_back(Eigen::Vector3i(index, index+1, index+2));
      mesh->mFaces.push_back(Eigen::Vector3i(index, index+2, index+3));
    }

    // set up mesh renderer
    mMeshRenderer.setColor(data->mColor[0], data->mColor[1], data->mColor[2]);
    mMeshRenderer.setColorMode((MeshRenderer::ColorMode)mColorMode);
    mMeshRenderer.setMeshMode((MeshRenderer::MeshMode)mMeshMode);
    if (usePoints) mMeshRenderer.setMeshMode(MeshRenderer::MeshModePoints);
    mMeshRenderer.setData(mesh->mVertices, mesh->mNormals,
                          mesh->mFaces, mapToWorld);

    // draw this view's data
    mMeshRenderer.draw();
  }

  Eigen::Vector4f computePlane(const double p1x, const double p1y,
                               const double p2x, const double p2y) {
    double x,y,z;
    gluUnProject(p1x,p1y,0,mModelViewGl,mProjectionGl,mViewportGl, &x,&y,&z);
    Eigen::Vector3f p1(x,y,z);
    gluUnProject(p1x,p1y,1,mModelViewGl,mProjectionGl,mViewportGl, &x,&y,&z);
    Eigen::Vector3f p2(x,y,z);
    gluUnProject(p2x,p2y,1,mModelViewGl,mProjectionGl,mViewportGl, &x,&y,&z);
    Eigen::Vector3f p3(x,y,z);
    Eigen::Vector4f plane;
    Eigen::Vector3f d1(p2-p1), d2(p3-p1);
    Eigen::Vector3f normal = d1.cross(d2);
    normal.normalize();
    plane.head<3>() = normal;
    plane[3] = -normal.dot(p1);
    return plane;
  }

  void updateFrontAndBackPlanes(Frustum& ioFrustum) {
    Eigen::Vector4f plane;
    Eigen::Vector3f pt;
    plane.head<3>() = ioFrustum.mDir;
    plane[3] = -ioFrustum.mDir.dot(ioFrustum.mPos +
                                   ioFrustum.mDir*ioFrustum.mNear);
    ioFrustum.mPlanes[4] = plane;
    plane = -plane;
    plane[3] = ioFrustum.mDir.dot(ioFrustum.mPos +
                                  ioFrustum.mDir*ioFrustum.mFar);
    ioFrustum.mPlanes[5] = plane;
  }

  void addViewMetaData(const int64_t iId) {
    // add new metadata if none exists for this id
    DataMap::const_iterator item = mViewData.find(iId);
    if (item != mViewData.end()) return;

    ViewMetaData::Ptr data(new ViewMetaData());
    data->mRenderer = this;
    data->mId = iId;
    data->mVisible = true;
    data->mLatestTransform = Eigen::Isometry3f::Identity();
    if (data->mId != 1) {
      switch(iId) {
      case drc::data_request_t::OCTREE_SCENE:
        data->mLabel = "Octree Scene";
        data->mColor = Eigen::Vector3f(0,0,0);
        break;
      case drc::data_request_t::HEIGHT_MAP_SCENE:
        data->mLabel = "Heightmap Scene";
        data->mColor = Eigen::Vector3f(1,0,0);
        break;
      case drc::data_request_t::HEIGHT_MAP_CORRIDOR:
        data->mLabel = "Heightmap Corridor";
        data->mColor = Eigen::Vector3f(1,0,0);
        break;
      case drc::data_request_t::HEIGHT_MAP_COARSE:
        data->mLabel = "Heightmap Coarse";
        data->mColor = Eigen::Vector3f(1,0.5,0);
        break;
      case drc::data_request_t::DEPTH_MAP_SCENE:
        data->mLabel = "Depthmap Scene";
        data->mColor = Eigen::Vector3f(0.5,0,0.5);
        break;
      case drc::data_request_t::DEPTH_MAP_WORKSPACE:
        data->mLabel = "Depthmap Workspace";
        data->mColor = Eigen::Vector3f(0,0,1);
        break;
      case drc::data_request_t::STEREO_MAP_HEAD:
        data->mLabel = "Stereo Head";
        data->mColor = Eigen::Vector3f(0.1,1,0.1);
        break;
      case drc::data_request_t::STEREO_MAP_LHAND:
        data->mLabel = "Stereo L.Hand";
        data->mColor = Eigen::Vector3f(0.1,0.7,0.1);
        break;
      case drc::data_request_t::STEREO_MAP_RHAND:
        data->mLabel = "Stereo R.Hand";
        data->mColor = Eigen::Vector3f(0.1,0.4,0.1);
        break;
      case drc::data_request_t::DENSE_CLOUD_BOX:
        data->mLabel = "Dense Cloud Box";
        data->mColor = Eigen::Vector3f(1,0,1);
        break;
      case 1000:
        data->mLabel = "Heightmap Controller";
        data->mColor = Eigen::Vector3f(0.5,0,0);
        break;
      default:
        data->mLabel = static_cast<std::ostringstream*>
          (&(std::ostringstream() << data->mId) )->str();
        data->mColor = Eigen::Vector3f((double)rand()/RAND_MAX,
                                       (double)rand()/RAND_MAX,
                                       (double)rand()/RAND_MAX);
        break;
      }
    }
    else {
      data->mColor = Eigen::Vector3f(1,0,0);
      data->mLabel = "Server Map";
    }

    // create widget and add to list
    mViewDataDispatcher();

    // add to data list
    mViewData[iId] = data;
  }

  void addViewWidgets() {
    DataMap::const_iterator iter;
    for (iter = mViewData.begin(); iter != mViewData.end(); ++iter) {
      ViewMetaData::Ptr data = iter->second;
      if (data->mBox != NULL) continue;

      data->mBox.reset(new Gtk::HBox());
      data->mToggleButton =
        Gtk::manage(new Gtk::ToggleButton("                    "));
      Gdk::Color color;
      color.set_rgb_p(data->mColor[0], data->mColor[1], data->mColor[2]);
      data->mToggleButton->modify_bg(Gtk::STATE_ACTIVE, color);
      color.set_rgb_p((data->mColor[0]+1)/2, (data->mColor[1]+1)/2,
                      (data->mColor[2]+1)/2);
      data->mToggleButton->modify_bg(Gtk::STATE_PRELIGHT, color); 
      color.set_rgb_p(0.8, 0.8, 0.8);
      data->mToggleButton->modify_bg(Gtk::STATE_NORMAL, color);
      data->mToggleButton->signal_toggled().connect
        (sigc::mem_fun(*data, &ViewMetaData::onToggleButton));
      data->mToggleButton->set_active(true);
      data->mBox->pack_start(*(data->mToggleButton), false, false);
      Gtk::Label* label = Gtk::manage(new Gtk::Label(data->mLabel));
      data->mBox->pack_start(*label, false, false);
      if (iter->first != 1) {
        Gtk::Button* cancelButton = Gtk::manage(new Gtk::Button("X"));
        data->mBox->pack_start(*cancelButton, false, false);
        cancelButton->signal_clicked().connect
          (sigc::mem_fun(*data, &ViewMetaData::onCancelButton));
      }
      mViewListBox->pack_start(*(data->mBox), false, false);
      data->mBox->show_all();
    }
  }
};

}


// this is the single setup method exposed for integration with the viewer
void maps_renderer_setup(BotViewer* iViewer, const int iPriority,
                         const lcm_t* iLcm,
                         const BotParam* iParam,
                         const BotFrames* iFrames) {
  new maps::MapsRenderer(iViewer, iPriority, iLcm, iParam, iFrames);
}
