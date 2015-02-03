/*
* (C) 2001-2012 Marmalade. All Rights Reserved.
*
* This document is protected by copyright, and contains information
* proprietary to Marmalade.
*
* This file consists of source code released by Marmalade under
* the terms of the accompanying End User License Agreement (EULA).
* Please do not use this program/source code before you have read the
* EULA and have agreed to be bound by its terms.
*/

#include "MainMenu.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include <iostream>

// ============================= CONSTANT VARIABLES ===================================
const unsigned char GROUND_MOVEMENT_SPEED = 4;

/*******************************************************************
 Constructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
MainMenu::MainMenu()
:if_initial_game_start(false)
{
    
}

/*******************************************************************
 Destructor
 
 @params:    None
 @returns:   None
 ******************************************************************/
MainMenu::~MainMenu()
{
	
}

/*******************************************************************
 Function: Init
 Initializes the main menu
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MainMenu::Init()
{
	Scene::Init();
    
    // the boolean to show that the game has started.
	if_initial_game_start = true;
	
    // Create menu background
	background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getMenuBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
    
	// Create Start Game button
	startButton = new CSprite();
	startButton->SetImage(g_pResources->getStartButtonIdle());
	startButton->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	startButton->m_Y = (float)IwGxGetScreenHeight() * 0.5f;
	startButton->m_W = startButton->GetImage()->GetWidth();
	startButton->m_H = startButton->GetImage()->GetHeight();
	startButton->m_AnchorX = 0.5f;
	startButton->m_AnchorY = 0.5f;
	startButton->m_ScaleX = (float)IwGxGetScreenWidth() * 0.24f / startButton->GetImage()->GetWidth();
	startButton->m_ScaleY = startButton->m_ScaleX;
    
    // Create the title of the game on the menu
	title = new CSprite();
	title->SetImage(g_pResources->getTitle());
	title->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	title->m_Y = (float)IwGxGetScreenHeight() * 0.2f;
	title->m_W = title->GetImage()->GetWidth();
	title->m_H = title->GetImage()->GetHeight();
	title->m_AnchorX = 0.5f;
	title->m_AnchorY = 0.5f;
	title->m_ScaleX = (float)IwGxGetScreenWidth() * 0.40f / title->GetImage()->GetWidth();
	title->m_ScaleY = startButton->m_ScaleX;
    
    // Create the hero that continues walking in the menu
	animatedHero = new CSprite();
	animatedHero->SetAtlas(g_pResources->getHeroRun());
	animatedHero->SetAnimDuration(0.5f);
	animatedHero->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	animatedHero->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	animatedHero->m_H = animatedHero->GetAtlas()->GetFrameHeight();
	animatedHero->m_W = animatedHero->GetAtlas()->GetFrameWidth();
	animatedHero->m_ScaleX = (float)IwGxGetScreenWidth() * 0.25f / animatedHero->GetAtlas()->GetFrameWidth();
	animatedHero->m_ScaleY = animatedHero->m_ScaleX;
	animatedHero->m_AnchorX = 0.35;
	animatedHero->m_AnchorY = 0.5;
    
    // Ground is the ground floor that continues to move
	ground = new CSprite();
	ground->SetImage(g_pResources->getGameGround());
	ground->m_W = ground->GetImage()->GetWidth();
	ground->m_H = ground->GetImage()->GetHeight();
	ground->m_X = 0;
	ground->m_Y = (float)IwGxGetScreenHeight() + (float)IwGxGetScreenHeight() * 0.40f;
	ground->m_AnchorY = 1;
	ground->m_ScaleY = (float)IwGxGetScreenHeight() * 0.50f / ground->GetImage()->GetHeight();
	ground->m_ScaleX = (float)IwGxGetScreenWidth() * 2 / ground->GetImage()->GetWidth();
	
    //Adds the CSprites
    AddChild(background);
    AddChild(startButton);
    AddChild(title);
	AddChild(ground);
	AddChild(animatedHero);
	// black screen
	blackBG = new CSprite();
	blackBG->m_X = (float)IwGxGetScreenWidth() / 2;
	blackBG->m_Y = (float)IwGxGetScreenHeight() / 2;
	blackBG->SetImage(g_pResources->getBlackBG());
	blackBG->m_W = blackBG->GetImage()->GetWidth();
	blackBG->m_H = blackBG->GetImage()->GetHeight();
	blackBG->m_AnchorX = 0.5;
	blackBG->m_AnchorY = 0.5;
	// Fit background to screen size
	blackBG->m_ScaleX = (float)IwGxGetScreenWidth();
	blackBG->m_ScaleY = (float)IwGxGetScreenHeight();
	blackBG->m_Alpha = 0.0;
	blackBG->m_IsVisible = true;
	
    AddChild(blackBG);
}

/*******************************************************************
 Function: Update
 Sets the moving ground and checks if any buttons are pressed
 
 @params:    float, float
 @returns:   None
 ******************************************************************/
void MainMenu::Update(float deltaTime, float alphaMul)
{
    // If game is inactive,=, does not do rest of the function
	if (!m_IsActive)
    {
		return;
    }
    
	// Moves Ground floor
	ground->m_X = ground->m_X - GROUND_MOVEMENT_SPEED;
	// Reset ground
	if (ground->m_X <= -(float)IwGxGetScreenWidth())
	{
		ground->m_X = 0;
	}
    
	Scene::Update(deltaTime, alphaMul);
	
    // Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this)
	{
		// Checks if user is pressing down on button
		if (startButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Changed to press
			startButton->SetImage(g_pResources->getStartButtonPressed());
            
			// Checks if user lets go
			if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
			{
				g_pInput->Reset();
				g_pTweener->Tween(1.0f,
                                  FLOAT, &blackBG->m_Alpha, 1.0f,
                                  EASING, Ease::sineIn,
                                  END);
				//Starts the game when the button for play is pressed
				
                startGame();
			}
		}
		else
		{
			// Sets back to idle
			startButton->SetImage(g_pResources->getStartButtonIdle());
		}
	}
}

/*******************************************************************
 Function: Render
 Scene renders
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MainMenu::Render()
{
	Scene::Render();
}

/*******************************************************************
 Function: startGame
 Starts the actual game
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MainMenu::startGame()
{
	// Switch to game scene
	if (g_AlarmOccured)
	{
		g_AlarmOccured = false;
	}
    
	Game* game = (Game*)g_pSceneManager->Find("game");
	
    //If first time playing the game
    if (if_initial_game_start)
	{
		g_pResources->Game();
		game->start();
	}
    //If retrying the game and alreaady played for the first time
	else
	{
		game->restartGame();
	}
    
	if_initial_game_start = false;
	g_pAudio->PlayMusic("audio/Battle.wav");
	g_pSceneManager->SwitchTo(game);
}

/*******************************************************************
 Function: black
 Used for transitiong, valids the black background to start the tween
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MainMenu::black()
{
	blackBG->m_Alpha = 1;
}

/*******************************************************************
 Function: returnToScreen
 Tweens to transition the screen
 
 @params:    None
 @returns:   None
 ******************************************************************/
void MainMenu::returnToScreen()
{

	startButton->SetImage(g_pResources->getStartButtonIdle());
	// Fade from black to white
	g_pTweener->Tween(1.0f,
		FLOAT, &blackBG->m_Alpha, 0.0f,
		EASING, Ease::linear,
		END);

}

