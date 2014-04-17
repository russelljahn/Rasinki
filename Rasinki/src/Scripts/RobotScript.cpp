#include "../Components/Script.h" 
 
#include "RobotScript.h"



RobotScript::RobotScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
    Start();
};



void RobotScript::Start() {
    Script::Start();
}



void RobotScript::Update() {
    Script::Update();
    gameObject->physics->setLinearVelocity(Ogre::Vector3(0, 0, 0));
    float movementSpeed = 1500.0f;
    int side = gameObject->game->camSide();

    gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Idle"));

    gameObject->transform->sceneNode->yaw(Ogre::Degree(-gameObject->game->getMouse()->getMouseState().X.rel) *.5);

    Ogre::Quaternion quat = gameObject->game->getCameraNode()->getOrientation();

    std::cout << quat << std::endl;

    if (quat.z > -0.2 && quat.z <= .45)
    {
        gameObject->game->getCameraNode()->roll(Ogre::Degree(-gameObject->game->getMouse()->getMouseState().Y.rel) *.5);
    }
    else if( quat.z <= -0.2 )
    {
        gameObject->game->getCameraNode()->setOrientation(quat.w, quat.x, quat.y, -0.2);
    }
    else
    {
        gameObject->game->getCameraNode()->setOrientation(quat.w, quat.x, quat.y, .45);
    }
    
    if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)) {
        Ogre::Vector3 veloc = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(0,0,1) * -movementSpeed;

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }
    if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)) {
        Ogre::Vector3 veloc = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(0,0,1) * movementSpeed;

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }
    if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W)) {
        Ogre::Vector3 veloc = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(1,0,0) * movementSpeed;

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }
    if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)) {
        Ogre::Vector3 veloc = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(1,0,0) * -movementSpeed;

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }

    // if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_SPACE)) {
    //     Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
    //     veloc.y += movementSpeed;

    //     gameObject->physics->setLinearVelocity(veloc);
    //     gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    // }

    Ogre::Vector3 subpos = gameObject->physics->getWorldPosition();

    // // Position it at 500 in Z direction
    // gameObject->game->getCamera()->setPosition(Ogre::Vector3(subpos.x - 500,subpos.y + 750,subpos.z));
    // // Look back along -Z
    // gameObject->game->getCamera()->lookAt(Ogre::Vector3(subpos.x,subpos.y + 200,subpos.z));
    // gameObject->game->getCamera()->setNearClipDistance(5);
}



void RobotScript::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {

}

// class RobotScript : public Script {

//     public:
//         RobotScript(GameObject *attachedGameObject);

//         RobotState *previousRobotState; // Only needed for memory deallocation right now
//         RobotState *currentRobotState;

//         void Start(){
//             Script::Start();
//             currentRobotState = new Standing(this->robot);
//         }

//         void Update(){
//             Script::Update();
//             previousRobotState = currentRobotState;
//             currentRobotState = currentRobotState->NextState();
//             currentRobotState->Update();

//             // Clean up memory allocation if necessary
//             if (previousRobotState != currentRobotState) {
//                 delete previousRobotState;
//             }
//         }

//         void OnCollision(Ogre::Vector3 point, GameObject* collidedWith);
//     private:
//         bool up;
//         bool down;
//         bool left;
//         bool right;
// };


// class RobotState {
//     public:
         
//         RobotState(RobotScript *attachedRobot);
//         ~RobotState();

//         RobotScript *robot;
     
//         virtual void Update();
//         virtual RobotState NextState();
// };

// class Standing : public RobotState {
//     public:
     
//         Standing(RobotScript *attachedRobot) : RobotState(RobotScript *attachedRobot);
//         ~Standing();
         
//         void Update() {
//             gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Idle"));
//         }

//         RobotState NextState() {
//             if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT)    || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)    ||
//                 gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT)   || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)    ||
//                 gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN)    || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)    ||
//                 gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP)      || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W))
//             {
//                 return new Walking(this->robot);
//             }
//             else {
//                 return this;
//             }
//         }
// };
 
 
// class Walking : public RobotState {
//     public:
     
//         Walking((RobotScript *attachedRobot) : RobotState(RobotScript *attachedRobot);
//         ~Walking();
         
//         void Update() {
//             gameObject->physics->setLinearVelocity(Ogre::Vector3(0, 0, 0));
//             float movementSpeed = 1500.0f;
//             int side = gameObject->game->camSide();

//             if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)) {
//                 Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();

//                 switch(side)
//                 {
//                     case 1:
//                         veloc.x = -movementSpeed;
//                         break;
//                     case 2:
//                         veloc.z = movementSpeed;
//                         break;
//                     case 3:
//                         veloc.x = movementSpeed;
//                         break;
//                     case 4:
//                         veloc.z = -movementSpeed;
//                         break;
//                     default:
//                         break;
//                 }

//                 gameObject->physics->setLinearVelocity(veloc);
//                 gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));

//                 // Ogre::Vector3 mDirection = mDestination - mNode->getPosition();    // B-A = A->B (see vector questions above)
//              //     Ogre::Vector3 src = mNode->getOrientation() * Vector3::UNIT_X;     // see (1)
//              //     Ogre::Real mDistance = mDirection.normalise();                     // strip out distance, we only want direction
//              //     Quaternion quat = src.getRotationTo(mDirection);             // Get a quaternion rotation operation 
//              //     mNode->rotate(quat);                                         // Actually rotate the object
//             }

//             if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)) {
//                 Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();

//                 switch(side)
//                 {
//                     case 1:
//                         veloc.x = movementSpeed;
//                         break;
//                     case 2:
//                         veloc.z = -movementSpeed;
//                         break;
//                     case 3:
//                         veloc.x = -movementSpeed;
//                         break;
//                     case 4:
//                         veloc.z = movementSpeed;
//                         break;
//                     default:
//                         break;
//                 }

//                 gameObject->physics->setLinearVelocity(veloc);
//                 gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
//             }


//             if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)) {
//                 Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
                
//                 switch(side)
//                 {
//                     case 1:
//                         veloc.z = movementSpeed;
//                         break;
//                     case 2:
//                         veloc.x = movementSpeed;
//                         break;
//                     case 3:
//                         veloc.z = -movementSpeed;
//                         break;
//                     case 4:
//                         veloc.x = -movementSpeed;
//                         break;
//                     default:
//                         break;
//                 }

//                 gameObject->physics->setLinearVelocity(veloc);
//                 gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
//             }

//             if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W)) {
//                 Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();

//                 switch(side)
//                 {
//                     case 1:
//                         veloc.z = -movementSpeed;
//                         break;
//                     case 2:
//                         veloc.x = -movementSpeed;
//                         break;
//                     case 3:
//                         veloc.z = movementSpeed;
//                         break;
//                     case 4:
//                         veloc.x = movementSpeed;
//                         break;
//                     default:
//                         break;
//                 }

//                 gameObject->physics->setLinearVelocity(veloc);
//                 gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
//             }
//         }

//         RobotState NextState() {
//             if (!gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT)    || !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)    ||
//                 !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT)   || !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)    ||
//                 !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN)    || !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)    ||
//                 !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP)      || !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W)) {
//                 return new Standing(gameObject);
//             }
//             else {
//                 return this;
//             }
//         }
// };
//  