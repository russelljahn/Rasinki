#include "Scripts/RobotState.h"

RobotState::RobotState(RobotScripts *attachedRobot) {
    this->gameObject = attachedGameObject;
}

RobotState::~RobotState() {
}

RobotState Standing::NextState() {
    if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT)    || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)    ||
        gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT)   || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)    ||
        gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN)    || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)    ||
        gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP)      || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W))
    {
        return new Walking(gameObject);
    }
    else {
        return this;
    }
}

void Standing::Update() {
    gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Idle"));
}

RobotState Walking::NextState() {
    if (!gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT)    || !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)    ||
        !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT)   || !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)    ||
        !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN)    || !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)    ||
        !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP)      || !gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W)) {
        return new Standing(gameObject);
    }
    else {
        return this;
    }
}

void Walking::Update() {
    gameObject->physics->setLinearVelocity(Ogre::Vector3(0, 0, 0));
    float movementSpeed = 1500.0f;
    int side = gameObject->game->camSide();

    if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_LEFT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_A)) {
        Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();

        switch(side)
        {
            case 1:
                veloc.x = -movementSpeed;
                break;
            case 2:
                veloc.z = movementSpeed;
                break;
            case 3:
                veloc.x = movementSpeed;
                break;
            case 4:
                veloc.z = -movementSpeed;
                break;
            default:
                break;
        }

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));

        // Ogre::Vector3 mDirection = mDestination - mNode->getPosition();    // B-A = A->B (see vector questions above)
     //     Ogre::Vector3 src = mNode->getOrientation() * Vector3::UNIT_X;     // see (1)
     //     Ogre::Real mDistance = mDirection.normalise();                     // strip out distance, we only want direction
     //     Quaternion quat = src.getRotationTo(mDirection);             // Get a quaternion rotation operation 
     //     mNode->rotate(quat);                                         // Actually rotate the object
    }

    if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_RIGHT) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_D)) {
        Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();

        switch(side)
        {
            case 1:
                veloc.x = movementSpeed;
                break;
            case 2:
                veloc.z = -movementSpeed;
                break;
            case 3:
                veloc.x = -movementSpeed;
                break;
            case 4:
                veloc.z = movementSpeed;
                break;
            default:
                break;
        }

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }


    if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_DOWN) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_S)) {
        Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();
        
        switch(side)
        {
            case 1:
                veloc.z = movementSpeed;
                break;
            case 2:
                veloc.x = movementSpeed;
                break;
            case 3:
                veloc.z = -movementSpeed;
                break;
            case 4:
                veloc.x = -movementSpeed;
                break;
            default:
                break;
        }

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }

    if (gameObject->game->getKeyboard()->isKeyDown(OIS::KC_UP) || gameObject->game->getKeyboard()->isKeyDown(OIS::KC_W)) {
        Ogre::Vector3 veloc = gameObject->physics->getLinearVelocity();

        switch(side)
        {
            case 1:
                veloc.z = -movementSpeed;
                break;
            case 2:
                veloc.x = -movementSpeed;
                break;
            case 3:
                veloc.z = movementSpeed;
                break;
            case 4:
                veloc.x = movementSpeed;
                break;
            default:
                break;
        }

        gameObject->physics->setLinearVelocity(veloc);
        gameObject->game->setAnimationState(gameObject->renderer->entity->getAnimationState("Walk"));
    }

}