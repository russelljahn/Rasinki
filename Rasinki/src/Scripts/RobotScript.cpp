#include "../Components/Script.h" 
 
#include "RobotScript.h"
#include "../Input.h"
#include <string>
#include "Pathfinder.h"

RobotScript::RobotScript(GameObject *attachedGameObject) : Script(attachedGameObject) {
    Start();
    currentTower = 1;
};



void RobotScript::Start() {
    Script::Start();
    glowTile = new Tower(this->gameObject->game);
    //glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
    glowTile->physics->disableCollider();
    glowTile->renderer->setMaterial("SquareGlow1");
    jumping = false;
    falling = false;
    can_move = true;
}



void RobotScript::Update() {
  
    Script::Update();

    HandleTower();

    if (!can_move){
        return;
    }

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
    if (Input::IsKeyDown(OIS::KC_1)) {
        if (currentTower != 1) {
            delete glowTile;
            glowTile = new Tower(this->gameObject->game);
            //glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .125, 2.5));
            glowTile->physics->disableCollider();
            glowTile->renderer->setMaterial("SquareGlow1");
        }
        currentTower = 1;
    }
    if (Input::IsKeyDown(OIS::KC_2)) {
        if (currentTower != 2) {
            delete glowTile;
            glowTile = new Cube(this->gameObject->game, 0);
            glowTile->transform->setWorldScale(Ogre::Vector3(2.5, .5, 2.5));
            glowTile->physics->disableCollider();
            glowTile->renderer->setMaterial("SquareGlow1");
        }
        currentTower = 2;
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

void RobotScript::sellTower(){
    Ogre::Vector3 forward = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(1,0,0)*250;
    GridSquare *squarey = grid->gridSquareAtPos(this->gameObject->physics->getWorldPosition() + forward);
    delete squarey->occupant;
    squarey->occupant = NULL;
    gameObject->game->playerList[0]->changeGold(13);
    return;
}

void RobotScript::upgradeTower(){
//TODO: Make this not just sell
    Ogre::Vector3 forward = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(1,0,0)*250;
    GridSquare *squarey = grid->gridSquareAtPos(this->gameObject->physics->getWorldPosition() + forward);
    delete squarey->occupant;
    squarey->occupant = NULL;

    Ogre::Vector3 squareyPosition = squarey->gameObject->physics->getWorldPosition();
    Tower *tower = new Tower(this->gameObject->game, "turret_02.mesh");
    Ogre::Vector3 scale = tower->transform->getWorldScale();
    tower->transform->setWorldScale(scale*1.25);
    tower->grid = grid;
    tower->Initialize();
    tower->physics->setWorldPosition(squareyPosition + Ogre::Vector3(00.0f, 65.0f, 40.0f));
    squarey->occupant = tower;
    upgraded = true;
    return;
}

void RobotScript::HandleTower() {
    Ogre::Vector3 forward = gameObject->transform->sceneNode->getOrientation() * Ogre::Vector3(1,0,0)*250;
    GridSquare *squarey = grid->gridSquareAtPos(this->gameObject->physics->getWorldPosition() + forward);

    if (squarey == NULL) {
        return;
    }
    if (upgraded){
        upgraded = false;
        return;
    }
    Ogre::Vector3 squareyPosition = squarey->gameObject->physics->getWorldPosition();    
    if (currentTower == 2)
        glowTile->transform->setWorldPosition(squareyPosition + Ogre::Vector3(0.0f, 10.0f, 0.0f));
    if (currentTower == 1)
        glowTile->transform->setWorldPosition(squareyPosition + Ogre::Vector3(0, 68, 40));
    if (squarey->IsOccupied() || squarey->HasEnemies()) {
        glowTile->renderer->setEnabled(false);
    }
    else if (!Pathfinder::ExistsValidPath(grid, 24, 24, 0, 0, squarey)) {
        glowTile->renderer->setMaterial("SquareGlow3");
        glowTile->renderer->setEnabled(true);
    }
    else {
        glowTile->renderer->setMaterial("SquareGlow1"); 
        glowTile->renderer->setEnabled(true);
    }

    if (Input::mouseReleased) {
        if (!squarey->IsOccupied() && !squarey->HasEnemies() && Pathfinder::ExistsValidPath(grid, 24, 24, 0, 0, squarey)) {
            if (currentTower == 1)
            {
                if ((gameObject->game->playerList[0]->getGold() - 25) >= 0)
                {
                    Tower *tower = new Tower(this->gameObject->game);
                    tower->physics->setWorldPosition(squareyPosition + Ogre::Vector3(00.0f, 65.0f, 40.0f));
                    tower->grid = grid;
                    tower->Initialize();
                    squarey->occupant = tower;
                    gameObject->game->playerList[0]->changeGold(-25);
                }
            }
            else if(currentTower == 2)
            {
                if ((gameObject->game->playerList[0]->getGold() - 5) >= 0)
                {
                    Barrier *barrier = new Barrier(this->gameObject->game);
                    barrier->physics->setWorldPosition(squareyPosition);
                    squarey->occupant = barrier;
                    gameObject->game->playerList[0]->changeGold(-5);
                }
            }
        }
        else if (squarey->IsOccupied()) {
          gameObject->game->disableGameWindow();
          gameObject->game->enableTowerMenu();
          can_move = false;
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
