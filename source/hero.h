#ifndef __HERO_H_
#define __HERO_H_

#include <list>
#include "Iw2DSceneGraph.h"
#include "Iw2D.h"
#include "IwGx.h"
#include "resources.h"
#include "scene.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Hero : public CSprite
{
protected:

    //REAL STANCE
    //0 - SWORD/SHIELD
    //1 - BOW
    //2 - STAFF
	int stance; // 0 = bow, 1 = shield, 2 = sword.    <- wtf manz
	Hero* heroSprite;

public:
    
	Hero();
	virtual ~Hero();
	virtual void    Init();
	virtual void    Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	virtual void    Render();

public:
    
	int			 get_stance() const		{ return stance;}
	
    //State of heros (init and destroy)
    Hero*		 returnHero();
    void		 hero_dead();

    //The different stances
    void		 sword_shield();
	void		 bow();
	void		 staff();
	void		 run();
	
    //Unused
//  void		 deleteHero();
};

extern Hero* g_pHero;

#endif  