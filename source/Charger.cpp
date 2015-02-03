#include "s3e.h"
#include "IwDebug.h"
#include "Iw2DSceneGraph.h"
#include "IwGx.h"
#include <iostream>

//Own files
#include "audio.h"
#include "input.h"
#include "resources.h"
#include "Charger.h"
#include "scene.h"
#include "mainMenu.h"
#include "monster.h"
#include "game.h"
#include "hero.h"

using namespace std;
using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

#define FRAME_TIME  (30.0f / 1000.0f)

// Global tweener is used by tweens that need to run outside of a scene
CTweenManager*  g_pTweener = 0;

//Declared Extern in Charger.h
bool g_AlarmOccured = false;

// Alarm call back function, called by Marmalade when the timer expires
static int32 Alarm(void *systemData, void *userData)
{
	// Restart the alarm again for 100 millseconds from now
	s3eTimerSetTimer(100, &Alarm, NULL);
	g_AlarmOccured = true;

	return 0;
}

// Main entry point for the application
int main()
{
    // Initialise graphics system(s)
    Iw2DInit();

    // Sets the seed for the random number generator
	srand(time(NULL));
    
	// Tweener
	g_pTweener = new CTweenManager();

	// Resource manager
	g_pResources = new Resources();
	g_pResources->MainMenu();

	// Input manager
	g_pInput = new Input();

    // Audio manager
	g_pAudio = new Audio();
	
    // Scene manager
	g_pSceneManager = new SceneManager();

    // Monster manager, manages all monsters
	g_pMonsterManager = new MonsterManager();
    
    // Dead Monster manager, manages all monsters that died
	g_pDeadMonsterManager = new DeadMonsterManager();
    
    // Hero manager, used to manage the hero.
	g_pHero = new Hero();
    
	// MainMenu Scene
	MainMenu* main_menu = new MainMenu();
	main_menu->SetName("mainmenu");
	main_menu->Init();
	
	// Game scene
	Game* game = new Game();
	game->Init();
	game->SetName("game");

    // Adds the scenes into the the manager
    g_pSceneManager->Add(main_menu);
	g_pSceneManager->Add(game);

	// Sets the first scene to the main menu
	g_pAudio->PlayMusic("audio/title.wav");
		
	g_pSceneManager->SwitchTo(main_menu);

	//game->start();
	s3eTimerSetTimer(100, &Alarm, NULL);

    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        //Used for the time to allow OS to process events
		uint64 new_time = s3eTimerGetMs();

		// Update global Tweener
		g_pTweener->Update(FRAME_TIME);

        // Update input system
		g_pInput->Update();
        
        // Update audio system
		g_pAudio->Update();
        
		// Update scene manager
		g_pSceneManager->Update(FRAME_TIME);

		// Update monster manager

        //Update the hero
		g_pHero->Update();

        //Clears the screen
		Iw2DSurfaceClear(0x000000);
        
        // Your rendering/app code goes here.
        g_pSceneManager->Render();

        //Draws Surface to screen
        Iw2DSurfaceShow();

        // Sleep for 0ms to allow the OS to process events etc.
		int yield = (int)(FRAME_TIME * 1000 - (s3eTimerGetMs() - new_time));
		if (yield < 0) {
			yield = 0;
        }
        
		// Yield to OS
		s3eDeviceYield(yield);
    }

    //Terminate modules being used
	delete g_pTweener;
    delete g_pResources;
    delete g_pInput;
    delete g_pAudio;
	delete g_pSceneManager;
	delete g_pMonsterManager;
	delete g_pDeadMonsterManager;
	delete g_pHero;
    
	Iw2DTerminate();

    cout << endl << "Game has ended" << endl << endl;
    // Return
    return 0;
}
