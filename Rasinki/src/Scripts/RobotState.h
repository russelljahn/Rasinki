#ifndef __ROBOTSTATE_H__
#define __ROBOTSTATE_H__

#include "GameObject.h"

class RobotState {
    public:
         
        RobotState(GameObject *attachedGameObject);
        ~RobotState();

        GameObject* gameObject;
     
        virtual void Update();
        virtual RobotState NextState();
};
 
 
class Standing : public RobotState {
    public:
     
        Standing(GameObject *attachedGameObject);
        ~Standing();
         
        void Update();
        RobotState NextState();
};
 
 
class Walking : public RobotState {
    public:
     
        Walking(GameObject *attachedGameObject);
        ~Walking();
         
        void Update();
        RobotState NextState();
};
 
 
// class Jumping : RobotState {
 
//     Jumping(Robot *attachedRobot) : RobotState(attachedRobot) {
//         // Play jumping animation.
//         // Apply force to move Robot up.
//     }
     
//     void Update() {
//         // Move Robot in midair by amount of movement keys.
//     }
 
//     RobotState NextState() {
//         if (Robot velocity is <= 0) {
//             return new Falling();
//         }
//         else {
//             return this;
//         }
//     }
// };
 
 
// class Falling : RobotState {
 
//     Falling(Robot *attachedRobot) : RobotState(attachedRobot) {
//         // Play falling animation.
//     }
     
//     void Update() {
//         // Move Robot in midair by amount of movement keys.
//     }
 
//     RobotState NextState() {
//         if (Robot is touching the ground) {
//             if (Robot is hitting movement keys) {
//                 return new Walking(robot);
//             }
//             else {
//                 return new Standing(robot);
//             }
//         }
//         else {
//             return this;
//         }
//     }
// };

#endif