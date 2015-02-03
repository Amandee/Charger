#include "monster.h"
#include "IwGx.h"
#include <iostream>
#include "game.h"

using namespace std;

//Always remember to initialize g_p's to 0
MonsterManager* g_pMonsterManager = 0;
DeadMonsterManager* g_pDeadMonsterManager = 0;

// ============================== Constant Variables ===================================
const float COLLISION_DISTANCE = 1.5;
const unsigned WEAPON_BOW = 0;
const unsigned WEAPON_MAGIC = 1;
const unsigned WEAPON_ARMOR = 2;

// ==========================================================================
//
// ============================ Monster class ===============================
//
// ==========================================================================

/*******************************************************************
 Constructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
Monster::Monster()
: weapon(0)
{
    //Empty
}
/*******************************************************************
 Destructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
Monster::~Monster()
{
	//Empty
}

/*******************************************************************
 Function: Init
 Does nothing
 
 @params:    None
 @returns:   None
 ******************************************************************/
void Monster::Init()
{
    //Empty
}

/*******************************************************************
 Function: Update
 Calls the CSprite Update
 
 @params:    float, float
 @returns:   None
 ******************************************************************/
void Monster::Update(float deltaTime, float alphaMul)
{
	CSprite::Update(deltaTime, alphaMul);
}

/*******************************************************************
 Function: Render
 Calls the CSprite Render
 
 @params:    None
 @returns:   None
 ******************************************************************/
void Monster::Render()
{
	CSprite::Render();
};

// ==========================================================================
//
// ========================= MonsterManager class ===========================
//
// ==========================================================================

/*******************************************************************
 Constructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
MonsterManager::MonsterManager()
:m_Current(0), m_Next(0)
{
	dragonspeed = 0;
	monstermovement = 50;
	threeseconds = 3;
	monsterSummon = 2;
	monsterSummonTime = 2;
}

/*******************************************************************
 Destructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
MonsterManager::~MonsterManager()
{
    //Empty
}

/*******************************************************************
 Function: Update
 Goes through every monster of the list of monsters and updates them
 
 @params:    float, float
 @returns:   None
 ******************************************************************/
void MonsterManager::Update(float deltaTime)
{
	for (std::list<Monster*>::iterator it = m_Monsters.begin(); it != m_Monsters.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}

/*******************************************************************
 Function: Render
 Goes through every monster and renders them
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MonsterManager::Render()
{
	for (std::list<Monster*>::iterator it = m_Monsters.begin(); it != m_Monsters.end(); ++it)
    {
		(*it)->Render();
    }
}

/*******************************************************************
 Function: Add
 Pushes the monster into the list
 
 @params:    Monster*
 @returns:   None
 ******************************************************************/
void MonsterManager::Add(Monster* Monster)
{
	m_Monsters.push_back(Monster);
}

/*******************************************************************
 Function: Remove
 Removes the monster from the list
 
 @params:    Monster*
 @returns:   None
 ******************************************************************/
void MonsterManager::Remove(Monster* Monster)
{
	m_Monsters.remove(Monster);
}

/*******************************************************************
 Function: create_enemies
 Creates the monsters during the game
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MonsterManager::create_enemies()
{
	
	Game* game = (Game*)g_pSceneManager->Find("game");
    //Creates the monster and initializes them
    //To choose which weapon that the monster would use
    monster_rand_weapon = rand() % 3;
    monster = new Monster();
    
    monster->m_Y = (float)IwGxGetScreenHeight() * 0.44f;
    
    monster->Init(); //Does nothing, literally
    
    //Checks the weapons of the monsters to get the correct sprite/atlas corresponding to their weapon
    if (monster_rand_weapon == WEAPON_BOW)
    {
        monster->SetAtlas(g_pResources->getEnemyBowAtlas());
    }
    else if (monster_rand_weapon == WEAPON_MAGIC)
    {
        monster->SetAtlas(g_pResources->getEnemyStaffAtlas());
    }
    else if (monster_rand_weapon == WEAPON_ARMOR)
    {
        monster->SetAtlas(g_pResources->getEnemySSAtlas());
    }
    else
    {
        cout << endl << endl << "in function: create_enemies -> ERROR, Not suppose to come here" << endl << endl;
    }
    
    //Continues initializing the stats of the monster
    monster->SetAnimDuration(0.5);
    monster->set_weapon(monster_rand_weapon);
    //Sets the score of the monsters
    monster->set_score(1);
    monster->set_dragon(0);
   
    monster->m_H = (float)monster->GetAtlas()->GetFrameHeight();
    monster->m_ScaleX = (float)IwGxGetScreenWidth() * 0.17f / monster->GetAtlas()->GetFrameWidth();
	
    monster->m_ScaleY = monster->m_ScaleX;
	monster->m_W = (float)monster->GetAtlas()->GetFrameWidth()  * monster->m_ScaleX;
	monster->m_X = (float)IwGxGetScreenWidth() + monster->m_W;
    monster->m_AnchorX = 0.6;
    monster->m_AnchorY = 0.5;
    
    //Adds the monster to the game and into the list for the monster manager
    game->AddChild(monster);
    g_pMonsterManager->Add(monster);
}

/*******************************************************************
 Function: Move
 Moves the monster accordingly
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MonsterManager::Move()
{
    //Moves all the monsters in the monster manager
	for (std::list<Monster*>::iterator it = m_Monsters.begin(); it != m_Monsters.end(); ++it)
	{
        (*it)->m_X = (*it)->m_X - .1 * monstermovement;
	}
    
    //Every 3 seconds the monsters would increase their movement speeds by a certain rate.
    if(g_AlarmOccured)
	{
		threeseconds -= .1;
	}
	if (threeseconds < 0.1)
	{
		monstermovement += 2.5;
		threeseconds = 3;
	}
}

/*******************************************************************
 Function: endlessLoop
 Continiously creates the monsters with faster speeds and faster spawn time accordingly for difficulty
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MonsterManager::endlessLoop()
{
	if (g_AlarmOccured)
	{	
		monsterSummon -= .1;
		g_AlarmOccured = false;
	}
	g_AlarmOccured = false;
    
	if (monsterSummon < .1)
	{
        create_enemies();
		Update();
		monsterSummon = monsterSummonTime;
	}
}

/*******************************************************************
 Function: death
 Deals with the monsters that die or dying
 
 @params:    Monster*
 @returns:   None
 ******************************************************************/
void MonsterManager::death(Monster* monster)
{
    //The animations for the death of the monsters accordingly to the weapon
	if (monster->get_weapon() == WEAPON_BOW)
	{
		monster->SetAtlas(g_pResources->getEnemyBowDeath());
	}
	else if (monster->get_weapon() == WEAPON_MAGIC)
	{
		monster->SetAtlas(g_pResources->getEnemyStaffDeath());
        
	}
	else if (monster->get_weapon() == WEAPON_ARMOR)
	{
		monster->SetAtlas(g_pResources->getEnemySSDeath());
	}
    else
    {
        cout << endl << endl << "ERROR, Should never come here function: death in MonsterManager" << endl << endl;
    }
    
    //The sprite/atlas/animation of the monster dying
	monster->m_W = monster->GetAtlas()->GetFrameWidth();
	monster->m_H = monster->GetAtlas()->GetFrameHeight();
	monster->SetAnimDuration(0.5f);
	float temp = monster->m_X;
	monster->m_X = temp - 20;
	monster->SetAnimRepeat(1);
	monster->m_AnchorX = 0.5;
    
    //Add the dying monster to the dead monster manager
	g_pDeadMonsterManager->Add(monster);
	Update();
}

/*******************************************************************
 Function: lowerSummon
 lowers the spawn time of the monster
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MonsterManager::lowerSummon()
{
	if (monsterSummonTime > .65)
	{
		monsterSummonTime -= .03;
	}
}

/*******************************************************************
 Function: reset
 Resets the protected variables to their initial state
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MonsterManager::reset()
{
	monstermovement = 50;
	dragonspeed = 0;
	threeseconds = 3;
	monsterSummon = 2;
	monsterSummonTime = 2;
}

/*******************************************************************
 Function: makeDragon
 Makes the dragon
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MonsterManager::makeDragon()
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	dragon = new Monster();
	dragon->Init(); //Does nothing
	
    //Just building the sprites
	monster_rand_weapon = rand() % 3;
	if (monster_rand_weapon == WEAPON_BOW)
	{
		dragon->SetAtlas(g_pResources->getEnemyBowAtlas());
	}
	else if (monster_rand_weapon == WEAPON_MAGIC)
	{
		dragon->SetAtlas(g_pResources->getEnemyStaffAtlas());
	}
	else if (monster_rand_weapon == WEAPON_ARMOR)
	{
		dragon->SetAtlas(g_pResources->getEnemySSAtlas());
	}
    else
    {
        cout << endl << endl << "ERROR, Should never come here function: makeDragon in MonsterManager" << endl << endl;
    }
    
    //continues initialization of the dragon
	dragon->SetAnimDuration(0.5);
	dragon->set_weapon(0);
	dragon->set_score(1);
	dragon->set_dragon(1);
	dragon->m_W = (float)dragon->GetAtlas()->GetFrameWidth();
	dragon->m_H = (float)dragon->GetAtlas()->GetFrameHeight();
	dragon->m_X = (float)IwGxGetScreenWidth();
	dragon->m_Y = (float)IwGxGetScreenHeight() * 0.44f;
	dragon->m_AnchorX = 0.5;
	dragon->m_AnchorY = 0.5;
	dragon->m_ScaleX = (float)IwGxGetScreenWidth() * 0.17f / dragon->GetAtlas()->GetFrameWidth();
	dragon->m_ScaleY = dragon->m_ScaleX;
	dragonspeed += 9;
    
	game->AddChild(dragon);
	g_pMonsterManager->Add(dragon);
}

/*******************************************************************
 function: charge
 Takes care of the movement of the dragon.
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MonsterManager::charge()
{
    //Movement of the dragon
	if (dragon->m_X < dragon->m_W * 3)
    {
		dragon->m_X = dragon->m_X - 6;
	}
	else
    {
		dragon->m_X = dragon->m_X - (9 + dragonspeed);
	}
    
    //Goes through the list of monsters and removes all the monsters that the dragon charges through
    //(*it) is the regular enemies that are attacking the hero.
	Game* game = (Game*)g_pSceneManager->Find("game");
	for (std::list<Monster*>::iterator it = m_Monsters.begin(); it != m_Monsters.end(); it++)
	{
		if (dragon->m_X < (*it)->m_X)
		{
			dragon->increaseScore();
			delete (*it);
			game->RemoveChild((*it));
			m_Monsters.remove(*it++);
			Update();
		}
	}
}

/*******************************************************************
 function: check_touched
 Returns the monsters that touch the hero
 
 @params:    float , float
 @returns:   Monster*
 ******************************************************************/
Monster* MonsterManager::check_touched(float hero_x, float hero_y)
{
	//Checks the two top corners, middle-bottom corners, and the middle top of the hero sprite and sees if it collides with the monsters
	for (std::list<Monster*>::iterator it = m_Monsters.begin(); it != m_Monsters.end(); ++it)
	{
		if ((*it)->m_X <= hero_x)//middle
		{
			return *it;
		}
	}
	return 0;
}

/*******************************************************************
 function: return_first
 Returns the first monster in the list
 
 @params:    None
 @returns:   Monster*
 ******************************************************************/
Monster* MonsterManager::return_first()
{
	for (std::list<Monster*>::iterator it = m_Monsters.begin(); it != m_Monsters.end(); ++it)
	{
		return *it;
	}
	return 0;
}

// ==========================================================================
//
// ====================== DeadMonsterManager class ==========================
//
// ==========================================================================

/*******************************************************************
 Constructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
DeadMonsterManager::DeadMonsterManager() :
m_Current(0), m_Next(0)
{
	//Empty
}

/*******************************************************************
 Destructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
DeadMonsterManager::~DeadMonsterManager()
{
    //Empty
}

/*******************************************************************
 function: Move
 Moves the dying monster appropriately
 
 @params:    None
 @returns:   None
 ******************************************************************/
void DeadMonsterManager::Move()
{
	// Move the same speed as the ground
	Game* game = (Game*)g_pSceneManager->Find("game");
	for (std::list<Monster*>::iterator it = m_DeadMonsters.begin(); it != m_DeadMonsters.end(); ++it)
	{
        //Goes through every dying monster and moves them appropriately
		if ((*it)->m_X > (*it)->m_W * 2)
		{
			(*it)->m_X = (*it)->m_X - .1 * g_pMonsterManager->returnMonsterMovement();
		}
		else
		{
			(*it)->m_X = (*it)->m_X - 4;
		}
	}
}

/*******************************************************************
 function: Death
 Dying Monster gets removed from the game
 
 @params:    None
 @returns:   None
 ******************************************************************/
void DeadMonsterManager::Death()
{
    //Goes through the list of the dying monsters and remove them from the game
	Game* game = (Game*)g_pSceneManager->Find("game");
	for (std::list<Monster*>::iterator it = m_DeadMonsters.begin(); it != m_DeadMonsters.end(); ++it)
	{
		delete (*it);
		game->RemoveChild((*it));
		m_DeadMonsters.remove(*it++);
	}
}

/*******************************************************************
 function: Update
 Updates the dying monsters
 
 @params:    float
 @returns:   None
 ******************************************************************/
void DeadMonsterManager::Update(float deltaTime)
{
	for (std::list<Monster*>::iterator it = m_DeadMonsters.begin(); it != m_DeadMonsters.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}

/*******************************************************************
 function: Render
 Renders the dying monsters
 
 @params:    None
 @returns:   None
 ******************************************************************/
void DeadMonsterManager::Render()
{
	for (std::list<Monster*>::iterator it = m_DeadMonsters.begin(); it != m_DeadMonsters.end(); ++it)
		(*it)->Render();
}

/*******************************************************************
 function: Add
 Adds the monster into the dying monster list
 
 @params:    Monster*
 @returns:   None
 ******************************************************************/
void DeadMonsterManager::Add(Monster* Monster)
{
	m_DeadMonsters.push_back(Monster);
}

/*******************************************************************
 function: Remove
 Removes the monster from the dying monster list
 
 @params:    Monster*
 @returns:   None
 ******************************************************************/
void DeadMonsterManager::Remove(Monster* Monster)
{
	m_DeadMonsters.remove(Monster);
}

/*******************************************************************
 function: DeadMonsterManager
 returns the first dying monster if valid
 
 @params:
 @returns:   Monster*
 ******************************************************************/
Monster* DeadMonsterManager::return_first()
{
	for (std::list<Monster*>::iterator it = m_DeadMonsters.begin(); it != m_DeadMonsters.end(); ++it)
	{
		return *it;
	}
	return 0;
};



