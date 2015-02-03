#ifndef __MONSTER_H_
#define __MONSTER_H_

#include <list>
#include "scene.h"
#include "Iw2DSceneGraph.h"
#include "Iw2DSceneGraphCore.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include "resources.h"
#include "IwTween.h"
#include "hero.h"

class Game;

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class MonsterManager;
class DeadMonsterManager;

/****************************************Monster*************************************************/
class Monster : public CSprite
{
protected:

	int                 weapon;
	int                 score;
	int                 dragon;
	
    //Manages all monsters
	float               movement;
	
public:
    
    //Helper functions
	int			 get_score()	const			{ return score; }
	int			 get_weapon()   const			{ return weapon; }
	int			 get_dragon()   const			{ return dragon; }
	void		 set_weapon(int setweapon)      { weapon = setweapon; }
	void		 set_score(int setscore)		{ score = setscore; }
	void		 set_dragon(int setdragon)		{ dragon = setdragon; }
	void		 increaseScore()				{ score++; }
	
public:
	Monster();
	virtual ~Monster();
	virtual void    Init();
	virtual void    Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	virtual void    Render();
};

/****************************************Monster Manager*************************************************/
class MonsterManager
{
protected:
    
    //The different kind of monsters
	Monster*                m_Current;                          // Currently active scene
	Monster*                monster;
	Monster*                m_Next;                             // Next monster
    Monster*                dragon;                             // Dragon monster
	std::list<Monster*>     m_Monsters;                         // Monster list
	
    //Weapon and movement of monster
    int                     monster_rand_weapon;				// Random monster
	int                     monstermovement;					// monster speed
    int                     dragonspeed;						// dragon speed
   
    //Timings of the monsters
    float                   threeseconds;						// when moverate of monsters should increase
	float                   monsterSummon;						// spawn rate of monsters
	float                   monsterSummonTime;					// What time monster should summon

public:
    
	Monster*    GetCurrent()                { return m_Current; }
    int         returnMonsterMovement()     { return monstermovement; } // To get the same movement as the monsters that are alive.

public:
    
	MonsterManager();
	~MonsterManager();
    void		Update(float deltaTime = 0.0f);
	void		Render();
    
    //Helper functions
    void		Add(Monster* monster);
	void		Remove(Monster* monster);
    
    //Deals with the monsters and their characteristics
    void	    create_enemies();
    void		Move();
	void		endlessLoop();
    void		death(Monster* monster);
	void		lowerSummon();			// Lower the time it takes to spawn a monster
    void		reset();

    //Deals with the dragons
    void		makeDragon();			// Make the Dragon
	void		charge();				// Charge the dragon
    
    //Returns the monsters that touch the hero
	Monster*	check_touched(float hero_x, float hero_y);

    //Returns the first monster on the list
	Monster*	return_first();

    //======= Unused
//    static void OnSwitchComplete(CTween* pTween);
//    void    FinishSwitch();
//    void SwitchTo(Scene* scene);
};

/****************************************Dead Monster Manager************************************************* */
class DeadMonsterManager
{
protected:
	Monster*              m_Current;              // Currently active scene
	Monster*			  monster;
	Monster*              m_Next;                 // Next scene (scene that is being switched to)
	std::list<Monster*>   m_DeadMonsters;         // Dead monsters list

public:
	
    Monster*  GetCurrent()                { return m_Current; }

public:

	DeadMonsterManager();
	~DeadMonsterManager();
	void		Update(float deltaTime = 0.0f);
	void		Render();
    
    //Helper functions
	void		Add(Monster* monster);
	void		Remove(Monster* monster);
    
    //Characteristics of the dying monsters
	void		Death(); // Kills all dead monsters
	void		Move();
    
    //Returns first dying monster on the list
	Monster*	return_first(); // For deletion
};

extern DeadMonsterManager* g_pDeadMonsterManager;
extern MonsterManager* g_pMonsterManager;

#endif  //__MONSTER_H_

