/********************************************************************************************
 SpaceInvadors Game Controls
 
 File        : SI_controls.c
 Author      : Fabian Niedermann, Christian Gwerder
 Date        : 20.04.2013
 Last Update : 22.04.2013 Christian Gwerder
 
 ChangeLog   : Datei erstellt, FN, 20.04.13
               Funktion GC_clrWeaponDelay() ergänzt, CG, 22.04.13
               Header für jede Funktion ergänzt, CG, 22.04.13
               GC_initGame(), GC_shot() in erster Version implementiert, CG, 25.04.13
               GC_updateGame() in erster Version implementiert, CG, 26.04.13
               

 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Defenition of game control functions
 ********************************************************************************************/

#include "SI_controls.h"

#include "target.h"
#include "Types.h"
#include "SI_defines.h"

// Global Variables

extern SI_stateReg stateRegister;
extern int playerPositionX;
extern SI_shot shotArray[];
extern SI_enemyLine enemyArray[SI_ENEMYLINES];

/***************************************************************************
 *   \brief initializes/restarts game (display, player position, enemies,...)
 *   \return void
 ***************************************************************************/
void GC_initGame()
{
  int i,j;
  
  // Initialize StateRegister
  stateRegister.restart = 0;
  stateRegister.shoot = 0;
  stateRegister.move = 0;
  
  //Initialize ShotArray
  for(i = SI_MAXSHOTS; i > 0 ; i--)
  {
    shotArray[i].x = 0;
    shotArray[i].y = 0;
  }
  
  //Initialize Player
  playerPositionX = SI_DISPWIDTH/2 - PL_SYMBOLWIDTH/2;
  //PL_drawPlayer(playerPositionX);
  
  //initialize enemy Line
  for(i = SI_ENEMYLINES; i > 0; i--)
  {
    for(j = EN_LOCATIONWIDTH; j > 0; j--)
      enemyArray[i-1].enemyLocations[j-1] = 0;
    //EN_drawEnemyLine(SI_ENEMYLINES-i);
  }
    
  
}

/***************************************************************************
 *   \brief generates a shot at the current player position
 *   \return void
 ***************************************************************************/
void GC_shoot()
{
  int i;
  
  for(i = SI_MAXSHOTS; i > 0; i--)
  {
    if((shotArray[i].x != 0)||(shotArray[i].y != 0))
    {
      shotArray[i].x = playerPositionX + PL_SYMBOLWIDTH/2 + 1;
      shotArray[i].y = PL_POSITIONY + PL_SYMBOLHEIGHT - 1;
      //SH_drawShot(shotArray[i]);
      break;
    }
  }
}

/***************************************************************************
 *   \brief moves player on screen left or right
 *   \return void
 ***************************************************************************/
void GC_movePlayer()
{
  if(stateRegister.move & SI_MOVE_LEFT)
    //PL_moveLeft();
  	printf("Move Player Left\n");
  else if(stateRegister.move & SI_MOVE_RIGHT)
    //PL_moveRight();
    printf("Move Player Left\n");
}

/***************************************************************************
 *   \brief updates game information (movement of shot, destruction of enemies,...)
 *   \return void
 ***************************************************************************/
void GC_updateGame()
{
  int i, j;
  //Precess each shot up
  for(i = SI_MAXSHOTS; i > 0; i--)
  {
    if((shotArray[i].x != 0)||(shotArray[i].y != 0))
    {
       //Move all shot up
      //SH_moveShot(shotArray[i]);
      
      //Check if Shot hits enemy & destroy enemy
      if(shotArray[i].y >= EN_TOPPOS - SI_ENEMYLINES*EN_SYMBOLHEIGHT-(SI_ENEMYLINES-1)*EN_GAPWIDTH)
      {
        for(j = 0; j < SI_ENEMYLINES; j--)
        {
          // Has Shot reached the enemyline ?
          if(shotArray[i].y >= EN_TOPPOS - (j+1)*EN_SYMBOLHEIGHT-j*EN_GAPWIDTH)
          {
            if(enemyArray[j].enemyLocations[(shotArray[i].x-EN_SIDEBORDER)/EN_GAPWIDTH] == 1)
              //EN_removeEnemy(j, (shotArray[i].x-EN_SIDEBORDER)/EN_GAPWIDTH);
            break;
          }
        }
      }
    }  
  }
}

/***************************************************************************
 *   \brief  clears WeaponDelay bit
 *   \return void
 ***************************************************************************/
void GC_clrWeaponDelay(void)
{
  stateRegister.shoot &= 0x3;
}