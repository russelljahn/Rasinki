#ifndef __LINE_H__
#define __LINE_H__


#include "GameObject.h"

class Line : public Ogre::ManualObject
{
  public:
    Line(const Ogre::String& name, bool depthCheck=true);
    void add (const Ogre::Vector3 from, 
          const Ogre::Vector3 to, 
          const Ogre::ColourValue colourFrom,
          const Ogre::ColourValue colourTo);
    void setDepthCheck(bool depthCheck);
    void _begin();
    void _end();
    
  private:
    bool mDepthCheck;
};

#endif