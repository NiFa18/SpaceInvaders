/********************************************************************************************
 SpaceInvadors Game Controls
 
 File        : SI_controls.c
 Author      : Fabian Niedermann, Christian Gwerder
 Date        : 20.04.2013
 Last Update : 22.04.2013 Christian Gwerder
 
 ChangeLog   : Datei erstellt, FN, 20.04.13
               Funktion GC_clrWeaponDelay() ergänzt, CG, 22.04.13
               Header für jede Funktion ergänzt, CG, 22.04.13
               GC_updateGame() in erster Version implementiert, CG, 26.04.13
               GC_initGame(), GC_shoot(), GC_movePlayer() in erster Version implementiert, CG, 25.04.13
               GC_initGame() & GC_shoot() & ,GC_movePlayer() getestet CG, 26.04.13

 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Defenition of game control functions
 ********************************************************************************************/


#include "target.h"
#include "displayNeu.h"

#include "Types.h"
#include "SI_controls.h"
#include "SI_defines.h"
#include "GC_player.h"
#include "GC_shot.h"
#include "GC_enemy.h"

// Global Variables

extern SI_stateReg stateRegister;
extern int playerPositionX;
extern SI_shot shotArray[SI_MAXSHOTS];
extern SI_enemyLine enemyArray[SI_ENEMYLINES];

/***************************************************************************
 *   \brief initializes/restarts game (display, player position, enemies,...)
 *   \return void
 ***************************************************************************/
void GC_initGame()
{
  int i,j;
  
  // Initialize Display
  DisplayInit();
  
  // Initialize StateRegister
  stateRegister.restart = 0;
  stateRegister.shoot = 0;
  stateRegister.move = 0;
  
  //Initialize ShotArray
  for(i = SI_MAXSHOTS; i > 0 ; i--)
  {
    shotArray[i-1].x = 0;
    shotArray[i-1].y = 0;
  }
  
  //Initialize Player
  playerPositionX = SI_DISPWIDTH/2 - PL_SYMBOLWIDTH/2;
  printf("playerPositionX = %d\n",playerPositionX);
  PL_drawPlayer(playerPositionX);
  
  //initialize enemy Line
  for(i = SI_ENEMYLINES; i > 0; i--)
  {
    for(j = EN_LOCATIONWIDTH; j > 0; j--)
      enemyArray[i-1].enemyLocations[j-1] = 0;
    EN_drawEnemyLine(SI_ENEMYLINES-i);
  }  
  
  printf("GC_initGame(): Done\n");
}

/***************************************************************************
 *   \brief generates a shot at the current player position
 *   \return void
 ***************************************************************************/
void GC_shoot()
{
  int i;
  
  for(i = SI_MAXSHOTS-1; i >= 0; i--)
  {
    if((shotArray[i].x == 0)&&(shotArray[i].y == 0))
    {
      //Schuss in Mitte am oberen Ende des Players zeichnen
      shotArray[i].x = playerPositionX + PL_SYMBOLWIDTH/2 + 1;
      shotArray[i].y = PL_POSITIONY + PL_SYMBOLHEIGHT - 1;
      SH_drawShot(i);
      printf("SH_drawShot(shotArray[%d].x = %d, shotArray[%d].y = %d\n", i, shotArray[i].x, i, shotArray[i].y);
      break;
    }
  }
  
  printf("GC_shoot(): Done\n");
}

/***************************************************************************
 *   \brief moves player on screen left or right
 *   \return void
 ***************************************************************************/
void GC_movePlayer()
{
  if(stateRegister.move & SI_MOVE_LEFT)
  {
    PL_moveLeft();
  	printf("Move Player Left\n");
  }
  else if(stateRegister.move & SI_MOVE_RIGHT)
  {
    PL_moveRight();
    printf("Move Player Right\n");
  }
}

/***************************************************************************
 *   \brief updates game information (movement of shot, destruction of enemies,...)
 *   \return void
 ***************************************************************************/
void GC_updateGame()
{
  int i, j;
  //Process each shot
  for(i = SI_MAXSHOTS; i > 0; i--)
  {
    if((shotArray[i].x != 0)||(shotArray[i].y != 0))
    {
      //Move all shot up
      SH_moveShot(i);
      printf("SH_moveShot(shotArray[%d].x = %d, shotArray[%d].y = %d) up\n", i, shotArray[i].x, i, shotArray[i].y);
      
      //Check if Shot hits enemy & destroy enemy
      printf("Has Shot reached %d?\n", EN_TOPPOS - SI_ENEMYLINES*EN_SYMBOLHEIGHT-(SI_ENEMYLINES-1)*EN_GAPHEIGHT);
      if(shotArray[i].y >= EN_TOPPOS - SI_ENEMYLINES*EN_SYMBOLHEIGHT-(SI_ENEMYLINES-1)*EN_GAPHEIGHT)
      {
        for(j = 0; j < SI_ENEMYLINES; j--)
        {
          // Has Shot reached the enemyline j?
          if(shotArray[i].y >= EN_TOPPOS - (j+1)*EN_SYMBOLHEIGHT-j*EN_GAPHEIGHT)
          {
            if(enemyArray[j].enemyLocations[(shotArray[i].x-EN_SIDEBORDER)/EN_GAPWIDTH] == 1)
            { 
              EN_removeEnemy(j, (shotArray[i].x-EN_SIDEBORDER)/EN_GAPWIDTH);
              SH_removeShot(i);
            }
            break;
          }
        }
      }
    }  
  }
  
  printf("GC_updateGame(): Done\n");
}

/***************************************************************************
 *   \brief  clears WeaponDelay bit
 *   \return void
 ***************************************************************************/
void GC_clrWeaponDelay(void)
{
  stateRegister.shoot &= 0x3;
}