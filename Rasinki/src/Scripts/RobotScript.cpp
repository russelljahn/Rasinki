#include "../Components/Script.h" 
 
#include "RobotScript.h"
#include "../Input.h"
#include <string>

RobotScript::RobotScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
    Start();
};



void RobotScript::Start() {
    Script::Start();
    glowTile = new Cube(this->gameObject->game, 0);
    glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    glowTile->physics->disableCollider();
    glowTile->renderer->setMaterial("SquareGlow1");
    jumping = false;
    falling = false;
}



void RobotScript::Update() {
    Script::Update();

    HandleTower();


    gameObject->physics->setLinearVelocity(Ogre::Vector3(0, 0, 0));
    float movementSpeed = 1500.0f;
    int side = gameObject->game->camSide();

    gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Idle"));

    gameObject->transform->sceneNode->yaw(Ogre::Degree(-gameObject->game->getMouse()->getMouseState().X.rel) *.5);

    Ogre::Quaternion quat = gameObject->game->getCameraNode()->getOrientation();

    if (quat.z > -0.2 && quat.z <= .35)
    {
        gameObject->game->getCameraNode()->roll(Ogre::Degree(-gameObject->game->getMouse()->getMouseState().Y.rel) *.5);
    }
    else if( quat.z <= -0.2 )
    {
        gameObject->game->getCameraNode()->setOrientation(quat.w, quat.x, quat.y, -0.1999);
    }
    else
    {
        gameObject->game->getCameraNode()->setOrientation(quat.w, quat.x, quat.y, .3499);
    }
    
    if (Input::IsKeyDown(OIS::KC_LEFT) || Input::IsKeyDown(OIS::KC_A)) {
        Ogre::Vector3 veloc = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(0,0,1) * -movementSpeed;

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }
    if (Input::IsKeyDown(OIS::KC_RIGHT) || Input::IsKeyDown(OIS::KC_D)) {
        Ogre::Vector3 veloc = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(0,0,1) * movementSpeed;

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }
    if (Input::IsKeyDown(OIS::KC_UP) || Input::IsKeyDown(OIS::KC_W)) {
        Ogre::Vector3 veloc = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(1,0,0) * movementSpeed;

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }
    if (Input::IsKeyDown(OIS::KC_DOWN) || Input::IsKeyDown(OIS::KC_S)) {
        Ogre::Vector3 veloc = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(1,0,0) * -movementSpeed;

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }

    if (Input::IsKeyDown(OIS::KC_SPACE) && !jumping && !falling) {
        Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
        veloc.y = movementSpeed*15;
        jumping = true;
        falling = false;

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }

    Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
    /* If you hit the apex of a jump... */
    if (veloc.y <= 0.0f && jumping && !falling) {
        falling = true;
        jumping = false;
    }


    Ogre::Vector3 subpos = gameObject->physics->getWorldPosition();

    // // Position it at 500 in Z direction
    // gameObject->game->getCamera()->setPosition(Ogre::Vector3(subpos.x - 500,subpos.y + 750,subpos.z));
    // // Look back along -Z
    // gameObject->game->getCamera()->lookAt(Ogre::Vector3(subpos.x,subpos.y + 200,subpos.z));
    // gameObject->game->getCamera()->setNearClipDistance(5);
}



void RobotScript::HandleTower() {
    Ogre::Vector3 forward = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(1,0,0)*250;
    GridSquare *squarey = grid->gridSquareAtPos(this->gameObject->physics->getWorldPosition() + forward);

    if (squarey == NULL) {
        return;
    }

    Ogre::Vector3 squareyPosition = squarey->gameObject->physics->getWorldPosition();    

    glowTile->transform->setWorldPosition(squareyPosition + Ogre::Vector3(0.0f, 10.0f, 0.0f ));

    if (Input::mouseReleased) {
       if (!squarey->IsOccupied()) {
            Tower *tower = new Tower(this->gameObject->game,0);
            tower->physics->setWorldPosition(squareyPosition + Ogre::Vector3(00.0f, 65.0f, 40.0f));
            squarey->occupant = tower;

            //this->gameObject->game->gameObjects.push_back(tower);    
        }
        else
        {
            delete squarey->occupant;
            squarey->occupant = NULL;
        }
    }
}



void RobotScript::OnCollision(Ogre::Vector3 point, GameObject* collidedWith) {
  /* If you're on the ground... */
    if (falling && collidedWith->name.compare("gridsquare") == 0) {
        falling = false;
        jumping = false;
    }

}