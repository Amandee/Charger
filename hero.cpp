#include "hero.h"
Hero* g_pHero = 0;

// =========================== CONSTANT VARIABLES ================================
const unsigned STANCE_SWORD_SHIELD = 0;
const unsigned STANCE_BOW = 1;
const unsigned STANCE_STAFF = 2;
const unsigned STANCE_RUNNING = 5;

/*******************************************************************
 Constructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
Hero::Hero()
:stance(STANCE_RUNNING)
{
	
}

/*******************************************************************
 Destructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
Hero::~Hero()
{
	
}

/*******************************************************************
 function: Init
 Initializes the Hero with stance to 0;
 
 @params:    None
 @returns:   None
 ******************************************************************/
void Hero::Init()
{
	stance = 0;
}

/*******************************************************************
 function: Update
 Calls the CSprite Update
 
 @params:    float, float
 @returns:   None
 ******************************************************************/
void Hero::Update(float deltaTime, float alphaMul)
{
	CSprite::Update(deltaTime, alphaMul);
}

/*******************************************************************
 function: Render
 Calls the CSprite Render
 
 @params:    None
 @returns:   None
 ******************************************************************/
void Hero::Render()
{
	CSprite::Render();
};

/*******************************************************************
 function: returnHero
 Builds the hero sprite and returns the initialized hero
 
 @params:    None
 @returns:   Hero*
 ******************************************************************/
Hero* Hero::returnHero()
{
	heroSprite = new Hero();
	heroSprite->SetAtlas(g_pResources->getHeroRun());
	heroSprite->SetAnimDuration(0.5f);
	heroSprite->m_H = heroSprite->GetAtlas()->GetFrameHeight();
	heroSprite->m_Y = (float)IwGxGetScreenHeight() * 0.45;
	// Point on sprite is in the middle
	heroSprite->m_ScaleX = (float)IwGxGetScreenWidth() * 0.25f / heroSprite->GetAtlas()->GetFrameWidth();
	heroSprite->m_ScaleY = heroSprite->m_ScaleX;
	heroSprite->m_W = heroSprite->GetAtlas()->GetFrameWidth() * heroSprite->m_ScaleX;
	heroSprite->m_X = (float)IwGxGetScreenWidth() * 0.20f;
	heroSprite->m_AnchorX = 0;
	heroSprite->m_AnchorY = 0.5;
    stance = STANCE_RUNNING;
	return heroSprite;
}

/*******************************************************************
 function: hero_dead
 Does the hero death sprite. Uses animation
 
 @params:    None
 @returns:   None
 ******************************************************************/
void Hero::hero_dead()
{
	heroSprite->SetAtlas(g_pResources->getHeroDeath());
	heroSprite->m_W = heroSprite->GetAtlas()->GetFrameWidth() * heroSprite->m_ScaleX;
	heroSprite->m_H = heroSprite->GetAtlas()->GetFrameHeight();
	heroSprite->SetAnimDuration(1.55f);
	heroSprite->SetAnimRepeat(1);
	stance = STANCE_RUNNING;
}

/*******************************************************************
 function: sword_shield
 Animation for the sword and shield
 
 @params:    None
 @returns:   None
 ******************************************************************/
void Hero::sword_shield()
{
	heroSprite->SetAtlas(g_pResources->getHeroSS());
	heroSprite->m_W = heroSprite->GetAtlas()->GetFrameWidth() * heroSprite->m_ScaleX;
	heroSprite->m_H = heroSprite->GetAtlas()->GetFrameHeight();
	heroSprite->SetAnimDuration(0.5f);
	heroSprite->SetAnimRepeat(1);
	stance = STANCE_SWORD_SHIELD;
}

/*******************************************************************
 function: bow
 Animation for the bow
 
 @params:    None
 @returns:   None
 ******************************************************************/
void Hero::bow()
{
	heroSprite->SetAtlas(g_pResources->getHeroBow());
	heroSprite->m_W = heroSprite->GetAtlas()->GetFrameWidth() * heroSprite->m_ScaleX;
	heroSprite->m_H = heroSprite->GetAtlas()->GetFrameHeight();
	heroSprite->SetAnimDuration(0.5f);
	heroSprite->SetAnimRepeat(1);
	stance = STANCE_BOW;
}

/*******************************************************************
 function: staff
 Animation for the staff
 
 @params:    None
 @returns:   None
 ******************************************************************/
void Hero::staff()
{
	heroSprite->SetAtlas(g_pResources->getHeroStaff());
	heroSprite->m_W = heroSprite->GetAtlas()->GetFrameWidth() * heroSprite->m_ScaleX;
	heroSprite->m_H = heroSprite->GetAtlas()->GetFrameHeight();
	heroSprite->SetAnimDuration(0.5f);
	heroSprite->SetAnimRepeat(1);
	stance = STANCE_STAFF;
}

/*******************************************************************
 function: run
 Animation for the running
 
 @params:    None
 @returns:   None
 ******************************************************************/
void Hero::run()
{
	heroSprite->SetAtlas(g_pResources->getHeroRun());
	heroSprite->m_W = heroSprite->GetAtlas()->GetFrameWidth() * heroSprite->m_ScaleX;
	heroSprite->m_H = heroSprite->GetAtlas()->GetFrameHeight();
	heroSprite->SetAnimDuration(0.5f);
	heroSprite->SetAnimRepeat(-1);
	stance = STANCE_RUNNING;
}

//UNUSED
/*
void Hero::deleteHero()
{
	delete heroSprite;
}
*/



