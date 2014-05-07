#include "Line.h"

Line::Line(const Ogre::String& name,bool depthCheck) : Ogre::ManualObject(name) {
  setDynamic(true);
  mDepthCheck=depthCheck;
}
  
void Line::_begin() {
  ManualObject::clear();
  setDepthCheck(mDepthCheck);
}
  
void Line::setDepthCheck(bool depthCheck) {
  mDepthCheck=depthCheck;
  ManualObject::begin(mDepthCheck? "Line/Simple" : "Line/NoDepth", Ogre::RenderOperation::OT_LINE_LIST);
  if (mDepthCheck==false)
    ManualObject::setRenderQueueGroupAndPriority(Ogre::RENDER_QUEUE_OVERLAY,10);
  else
    ManualObject::setRenderQueueGroupAndPriority(Ogre::RENDER_QUEUE_MAIN,10);
}
  
void Line::_end() {
  ManualObject::end();
}

void Line::add (const Ogre::Vector3 from, const Ogre::Vector3 to, const Ogre::ColourValue colourFrom, const Ogre::ColourValue colourTo) {
  ManualObject::position(from);
  ManualObject::colour(colourFrom);
  ManualObject::position(to);
  ManualObject::colour(colourTo);
}