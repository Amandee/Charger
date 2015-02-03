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

#include "IwGx.h"
#include "game.h"
#include <iostream>
#include <fstream.h>
#include <sstream>
using namespace std;

//Used for the timing delay when the attack stance buttons are pushed
bool timerDone;

// ================================= CONSTANT VARIABLES =====================================
const unsigned char GROUND_MOVEMENT_SPEED = 4;
const unsigned STANCE_SWORD_SHIELD = 0;
const unsigned STANCE_BOW = 1;
const unsigned STANCE_STAFF = 2;
const unsigned char NATURE_MOVEMENT_SPEED = 1;

/*******************************************************************
Constructor

@params:    None
@returns:   None
******************************************************************/
Game::Game()
{
	//Empty
}

/*******************************************************************
Destructor

@params:    None
@returns:   None
*******************************************************************/
Game::~Game()
{
	//Empty
}

/*******************************************************************
function: Init
... DOESN'T DO ANYTHING

@params:    None
@returns:   None
******************************************************************/
void Game::Init()
{
	Scene::Init();
}

/*******************************************************************
function: Update


@params:    float, float
@returns:   None
******************************************************************/
void Game::Update(float deltaTime, float alphaMul)
{
	//If not in active state, do not update
	if (!m_IsActive) {
		return;
	}

	//Calls the Scene Update
	Scene::Update(deltaTime, alphaMul);
	
	changeBackgrounds();


	// ========================== MOVING THE GROUND FLOOR =======================================
	//This part represents the moving ground where the Hero and Monsters walk on
	ground_floor->m_X = ground_floor->m_X - GROUND_MOVEMENT_SPEED;
	if (ground_floor->m_X <= -(float)IwGxGetScreenWidth())
	{
		//Resets the position so it looks seemlessly moving
		ground_floor->m_X = 0;
	}

	nature_bg->m_X = nature_bg->m_X - NATURE_MOVEMENT_SPEED;
	nature_bg2->m_X = nature_bg2->m_X - NATURE_MOVEMENT_SPEED;
	if (nature_bg->m_X <= -(float)IwGxGetScreenWidth() || nature_bg2->m_X <= -(float)IwGxGetScreenWidth())
	{
		changeNature();
	
	}

	// ======================= MOVING/SPAWNING DRAGON & MOVING MONSTERS =========================
	// Check if the score is equal to the value of the dragon if so spawn the dragon
	// Else if not true, just keep moving the enemies
/*	if (score == intRandomDragon)
	{
		// Make dragon
		if (!dragon)
		{
			g_pMonsterManager->makeDragon();
			dragon = true;
		}
		// Charge dragon
		g_pMonsterManager->charge();
	}*/
	//else
	//{
		//The monsters continue to move and the dragon does not spawn
		g_pDeadMonsterManager->Move();
		g_pMonsterManager->Move();
		dragon = false;
	//}

	// ===================================================================================================
	// ============================================ LOSE =================================================
	// ===================================================================================================
	//When the game enters lose state which is when the hero dies from the monsters
	if (lose)
	{
		
		// Check if score board is made, if it isnt make it
		if (!scoreBoardActive)
		{
			return; // Set scoreboard made to true
		}
		// Can't touch anything till scoreboard is finished
		if (replayButton->m_Y != (float)IwGxGetScreenHeight() * 0.63f)
		{

			return;
		}

		// ======================================= Replay Button ==================================================
		// Check if touch input is on the restart button
		if (replayButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{

			// Pressed button animation
			replayButton->SetImage(g_pResources->getReplayButtonPressed());
			//Restart game
			// Checks to see if the user touched it and let go
			if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
			{
				g_pTweener->Tween(0.1f,
					FLOAT, &blackBG->m_Alpha, 1.0f,
					EASING, Ease::sineIn,
					END);
				RemoveChild(blackBG);
				RemoveChild(whiteBG);
				delete whiteBG;
				g_pInput->Reset();
				delete blackBG;
				restartGame();
			}
		}
		// Reset to idle
		else
		{
			replayButton->SetImage(g_pResources->getReplayButtonIdle());
		}

		// ========================================== Menu Button ==================================================
		if (backToMenuButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Pressed button animation
			backToMenuButton->SetImage(g_pResources->getMenuButtonPressed());
			if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
			{
				//Back to menu
				g_pTweener->Tween(0.1f,
					FLOAT, &blackBG->m_Alpha, 1.0f,
					EASING, Ease::sineIn,
					END);
				RemoveChild(blackBG);
				RemoveChild(whiteBG);
				delete whiteBG;
				delete blackBG;
				g_pInput->Reset();
				toMainMenu();
			}
		}
		else
		{
			backToMenuButton->SetImage(g_pResources->getMenuButtonIdle());
		}
		// ======================================== Not used till next update ==============================================
		/*
		// ========================================== Share Button =================================================
		if (shareButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Pressed button animation
			shareButton->SetImage(g_pResources->getShareButtonPressed());

			// Checks if user releases while on button
			if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
			{
				//TODO
			}
		}
		else
		{
			shareButton->SetImage(g_pResources->getShareButtonIdle());
		}

		// ========================================== Trophies ======================================================
		if (trophiesButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Pressed button animation
			trophiesButton->SetImage(g_pResources->getTrophiesButtonPressed());

			// Checks if user releases while on button
			if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
			{
				//TODO
			}
		}
		else
		{
			trophiesButton->SetImage(g_pResources->getTrophiesButtonIdle());
		}
		*/
		return;
	}

	// Continuously makes monsters through the endless loop
	g_pMonsterManager->endlessLoop();
	// Check for any collision
	collision_Hero_Monsters();

	// ========================================== 3 buttons for attack ======================================================
	// Hit box for the buttons, then make sure the animation finishes, and then make sure that the user clicks the button
	// Inputs are the mouse/finger clicks

	// SWORD/SHIELD hit box button stance
	if (ssBG->HitTest(g_pInput->m_X, g_pInput->m_Y) && timerDone == true && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		timerDone = false; // Make timer animation false to make sure animation finishes

		g_pHero->sword_shield(); // Change Stance

		// Add the timer so after 0.5 seconds it will go to the normal stance and timerDone will be true
		m_Timers.Add(new Timer(0.5f, 1, &Game::normalHero, (void*)this));

		g_pInput->Reset(); // Reset Input

		// Set it to pressed and fade it out and change it back once fade is done
		ssFadeBG->m_Alpha = 1;
		g_pAudio->PlaySound("audio/Sword.wav");
		g_pTweener->Tween(0.5f,
			FLOAT, &ssFadeBG->m_Alpha, 0.0f,
			EASING, Ease::linear,
			END);
	}

	// STAFF hit box button stance
	//The code for the STAFF and BOW have the same concepts of the SWORD/SHIELD
	else if (staffBG->HitTest(g_pInput->m_X, g_pInput->m_Y) && timerDone == true && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		timerDone = false;
		g_pHero->staff();
		m_Timers.Add(new Timer(0.5f, 1, &Game::normalHero, (void*)this));
		g_pInput->Reset();
		g_pAudio->PlaySound("audio/Fire.wav");
		// Set it to pressed and fade it out and change it back once fade is done
		staffFadeBG->m_Alpha = 1;

		g_pTweener->Tween(0.5f,
			FLOAT, &staffFadeBG->m_Alpha, 0.0f,
			EASING, Ease::linear,
			END);
	}

	// BOW hit box button stance
	else if (bowBG->HitTest(g_pInput->m_X, g_pInput->m_Y) && timerDone == true && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		timerDone = false;
		g_pHero->bow();
		m_Timers.Add(new Timer(0.5f, 1, &Game::normalHero, (void*)this));
		g_pInput->Reset();
		g_pAudio->PlaySound("audio/Arrow.wav");
		// Set it to pressed and fade it out and change it back once fade is done
		bowFadeBG->m_Alpha = 1;
		g_pTweener->Tween(0.5f,
			FLOAT, &bowFadeBG->m_Alpha, 0.0f,
			EASING, Ease::linear,
			END);
	}
}

/*******************************************************************
function: Render
Pretty self explanatory

@params:    None
@returns:   None
******************************************************************/
void Game::Render()
{
	Scene::Render();
}

/*******************************************************************
function: start
Initialize the game whenever the menu transitions to the game

@params:    None
@returns:   None
******************************************************************/
void Game::start()
{
	//creates the Background
	background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getBG_1());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	

	// Background2 is another background that previous background will change into
	background2 = new CSprite();
	background2->m_X = (float)IwGxGetScreenWidth() / 2;
	background2->m_Y = (float)IwGxGetScreenHeight() / 2;
	background2->SetImage(g_pResources->getWhiteBG());
	background2->m_W = background2->GetImage()->GetWidth();
	background2->m_H = background2->GetImage()->GetHeight();
	background2->m_AnchorX = 0.5;
	background2->m_AnchorY = 0.5;
	// Fit background to screen size
	background2->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background2->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background2);
	AddChild(background);

	//creates nature floor
	nature_bg = new CSprite();
	nature_bg->SetImage(g_pResources->getNature_1());
	nature_bg->m_W = nature_bg->GetImage()->GetWidth();
	nature_bg->m_H = nature_bg->GetImage()->GetHeight();
	nature_bg->m_X = 0;
	nature_bg->m_Y = 0;
	nature_bg->m_AnchorY = 0;
	nature_bg->m_ScaleY = (float)IwGxGetScreenHeight() * 0.65f / nature_bg->GetImage()->GetHeight();
	nature_bg->m_ScaleX = (float)IwGxGetScreenWidth() / nature_bg->GetImage()->GetWidth();
	
	nature_bg2 = new CSprite();
	nature_bg2->SetImage(g_pResources->getNature_2());
	nature_bg2->m_W = nature_bg->GetImage()->GetWidth();
	nature_bg2->m_H = nature_bg->GetImage()->GetHeight();
	nature_bg2->m_X = (float)IwGxGetScreenWidth();
	nature_bg2->m_Y = 0;
	nature_bg2->m_AnchorY = 0;
	nature_bg2->m_ScaleY = (float)IwGxGetScreenHeight() * 0.65f / nature_bg2->GetImage()->GetHeight();
	nature_bg2->m_ScaleX = (float)IwGxGetScreenWidth() / nature_bg2->GetImage()->GetWidth();

	//creates the Ground floor
	ground_floor = new CSprite();
	ground_floor->SetImage(g_pResources->getGameGround());
	ground_floor->m_W = ground_floor->GetImage()->GetWidth();
	ground_floor->m_H = ground_floor->GetImage()->GetHeight();
	ground_floor->m_X = 0;
	ground_floor->m_Y = (float)IwGxGetScreenHeight();
	ground_floor->m_AnchorY = 1;
	ground_floor->m_ScaleY = (float)IwGxGetScreenHeight() * 0.50f / ground_floor->GetImage()->GetHeight();
	ground_floor->m_ScaleX = (float)IwGxGetScreenWidth() * 2 / ground_floor->GetImage()->GetWidth();

	// Create score label (displays actual score)
	scoreLabel = new CLabel();
	scoreLabel->m_X = (float)IwGxGetScreenWidth() / 2;
	scoreLabel->m_Y = (float)IwGxGetScreenHeight() * 0.05f;
	scoreLabel->m_Text = "0";
	scoreLabel->m_W = (float)IwGxGetScreenWidth();
	scoreLabel->m_Font = g_pResources->getFont();
	scoreLabel->m_ScaleX = (float)IwGxGetScreenWidth() * 0.13f / 100;
	scoreLabel->m_ScaleY = (float)IwGxGetScreenWidth() * 0.13f / 100;
	scoreLabel->m_Color = CColor(0xff, 0xff, 0xff, 0xff);

	// ================================== backgrounds for buttons ==================================
	// Sword/shield button
	ssBG = new CSprite();
	ssBG->SetImage(g_pResources->getButtonIdle());
	ssBG->m_W = ssBG->GetImage()->GetWidth();
	ssBG->m_H = ssBG->GetImage()->GetHeight();
	ssBG->m_X = (float)IwGxGetScreenWidth() * 0.0175f;
	ssBG->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	ssBG->m_AnchorY = 0.5;
	ssBG->m_ScaleY = (float)IwGxGetScreenHeight() * 0.30f / ssBG->GetImage()->GetHeight();
	ssBG->m_ScaleX = (float)IwGxGetScreenWidth() * 0.31f / ssBG->GetImage()->GetWidth();

	// Staff button
	staffBG = new CSprite();
	staffBG->SetImage(g_pResources->getButtonIdle());
	staffBG->m_W = staffBG->GetImage()->GetWidth();
	staffBG->m_H = staffBG->GetImage()->GetHeight();
	staffBG->m_X = (float)IwGxGetScreenWidth() * 0.345f;
	staffBG->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	staffBG->m_AnchorY = 0.5;
	staffBG->m_ScaleY = (float)IwGxGetScreenHeight() * 0.30f / staffBG->GetImage()->GetHeight();
	staffBG->m_ScaleX = (float)IwGxGetScreenWidth() * 0.31f / staffBG->GetImage()->GetWidth();

	// Bow button
	bowBG = new CSprite();
	bowBG->SetImage(g_pResources->getButtonIdle());
	bowBG->m_W = ssBG->GetImage()->GetWidth();
	bowBG->m_H = ssBG->GetImage()->GetHeight();
	bowBG->m_X = (float)IwGxGetScreenWidth() * 0.6725f;
	bowBG->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	bowBG->m_AnchorY = 0.5;
	bowBG->m_ScaleY = (float)IwGxGetScreenHeight() * 0.30f / ssBG->GetImage()->GetHeight();
	bowBG->m_ScaleX = (float)IwGxGetScreenWidth() * 0.31f / ssBG->GetImage()->GetWidth();

	// ================================== Fading backgrounds for buttons ==================================
	// Sword/shield button
	ssFadeBG = new CSprite();
	ssFadeBG->SetImage(g_pResources->getButtonPressed());
	ssFadeBG->m_W = ssBG->GetImage()->GetWidth();
	ssFadeBG->m_H = ssBG->GetImage()->GetHeight();
	ssFadeBG->m_X = (float)IwGxGetScreenWidth() * 0.0175f;
	ssFadeBG->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	ssFadeBG->m_AnchorY = 0.5;
	ssFadeBG->m_ScaleY = (float)IwGxGetScreenHeight() * 0.30f / ssBG->GetImage()->GetHeight();
	ssFadeBG->m_ScaleX = (float)IwGxGetScreenWidth() * 0.31f / ssBG->GetImage()->GetWidth();
	ssFadeBG->m_Alpha = 0; // Make it invisible till pressed

	// Staff button
	staffFadeBG = new CSprite();
	staffFadeBG->SetImage(g_pResources->getButtonPressed());
	staffFadeBG->m_W = staffBG->GetImage()->GetWidth();
	staffFadeBG->m_H = staffBG->GetImage()->GetHeight();
	staffFadeBG->m_X = (float)IwGxGetScreenWidth() * 0.345f;
	staffFadeBG->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	staffFadeBG->m_AnchorY = 0.5;
	staffFadeBG->m_ScaleY = (float)IwGxGetScreenHeight() * 0.30f / staffBG->GetImage()->GetHeight();
	staffFadeBG->m_ScaleX = (float)IwGxGetScreenWidth() * 0.31f / staffBG->GetImage()->GetWidth();
	staffFadeBG->m_Alpha = 0; // Make it invisible till pressed

	// Bow button
	bowFadeBG = new CSprite();
	bowFadeBG->SetImage(g_pResources->getButtonPressed());
	bowFadeBG->m_W = ssBG->GetImage()->GetWidth();
	bowFadeBG->m_H = ssBG->GetImage()->GetHeight();
	bowFadeBG->m_X = (float)IwGxGetScreenWidth() * 0.6725f;
	bowFadeBG->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	bowFadeBG->m_AnchorY = 0.5;
	bowFadeBG->m_ScaleY = (float)IwGxGetScreenHeight() * 0.30f / ssBG->GetImage()->GetHeight();
	bowFadeBG->m_ScaleX = (float)IwGxGetScreenWidth() * 0.31f / ssBG->GetImage()->GetWidth();
	bowFadeBG->m_Alpha = 0; // Make it invisible till pressed

	// ================================== Sprites of stances of buttons ==================================
	//The actual sprites of the stance
	//Sword/shield
	ssButton = new CSprite();
	ssButton->SetImage(g_pResources->getSSButton());
	ssButton->m_W = ssButton->GetImage()->GetWidth();
	ssButton->m_H = ssButton->GetImage()->GetHeight();
	ssButton->m_X = (float)IwGxGetScreenWidth() * 0.1725;
	ssButton->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	ssButton->m_AnchorY = 0.5;
	ssButton->m_AnchorX = 0.5;
	ssButton->m_ScaleX = (float)IwGxGetScreenWidth() * 0.15f / ssButton->GetImage()->GetWidth();
	ssButton->m_ScaleY = ssButton->m_ScaleX;

	//Staff
	staffButton = new CSprite();
	staffButton->SetImage(g_pResources->getStaffButton());
	staffButton->m_W = staffButton->GetImage()->GetWidth();
	staffButton->m_H = staffButton->GetImage()->GetHeight();
	staffButton->m_X = (float)IwGxGetScreenWidth() * 0.50f;
	staffButton->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	staffButton->m_AnchorY = 0.5;
	staffButton->m_AnchorX = 0.5;
	staffButton->m_ScaleX = (float)IwGxGetScreenWidth() * 0.15f / staffButton->GetImage()->GetWidth();
	staffButton->m_ScaleY = staffButton->m_ScaleX;

	//Bow
	bowButton = new CSprite();
	bowButton->SetImage(g_pResources->getBowButton());
	bowButton->m_W = bowButton->GetImage()->GetWidth();
	bowButton->m_H = bowButton->GetImage()->GetHeight();
	bowButton->m_X = (float)IwGxGetScreenWidth() * 0.82725;
	bowButton->m_Y = (float)IwGxGetScreenHeight() * 0.80f;
	bowButton->m_AnchorY = 0.5;
	bowButton->m_AnchorX = 0.5;
	bowButton->m_ScaleX = (float)IwGxGetScreenWidth() * 0.15f / bowButton->GetImage()->GetWidth();
	bowButton->m_ScaleY = bowButton->m_ScaleX;

	//Black background
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
	blackBG->m_Alpha = 1.0;
	blackBG->m_IsVisible = true;

	//Adds all the CSprites
	AddChild(background);
	AddChild(nature_bg);
	AddChild(nature_bg2);
	AddChild(ground_floor);

	AddChild(scoreLabel);

	AddChild(ssBG);
	AddChild(staffBG);
	AddChild(bowBG);

	AddChild(ssFadeBG);
	AddChild(staffFadeBG);
	AddChild(bowFadeBG);

	AddChild(ssButton);
	AddChild(staffButton);
	AddChild(bowButton);

	AddChild(blackBG);
	// Initializes everything to their beginning value
	createBackgrounds();
	createNature();
	score = 0;
	backgroundCounter = 1;
	natureCounter = 2;
	if_initial_game_start = true;
	bgCounterForScore = 1;
	// Reads from the text file to see what the highest score is.
	string line;
	ifstream highScoreFile("ram://high_score.txt");
	if (highScoreFile.is_open())
	{
		while (getline(highScoreFile, line))
		{
			cout << line;
		}
		high_score = atoi(line.c_str());
	}
	else
	{
		high_score = 0;
		stringstream ss;
		ss << high_score;
		string str = ss.str();
		highScoreFile >> str;
		cout << endl << endl << "FILE DOES NOT EXIST" << endl << endl;
	}

	intRandomDragon = rand() % 25 + 25;
	dragon = false;
	lose = false;
	scoreBoardActive = false;
	timerDone = true;

	// Initializes Hero
	hero1 = g_pHero->returnHero();
	AddChild(hero1);

	// Creates the monsters
	g_pMonsterManager->create_enemies();

	updateScore();

	g_pTweener->Tween(1.0f,
		FLOAT, &blackBG->m_Alpha, 0.0f,
		EASING, Ease::linear,
		END);
}

/*******************************************************************
function: restartGame
Restarts the game when the losing state transitions to the game

@params:    None
@returns:   None
******************************************************************/
void Game::restartGame()
{
	// Reinitializes values

	g_pAudio->PlayMusic("audio/Battle.wav");
	score = 0;
	intRandomDragon = rand() % 25 + 25;
	dragon = false;
	lose = false;
	scoreBoardActive = false;
	timerDone = true;
	backgroundCounter = 1;
	bgCounterForScore = 1;
	natureCounter = 2;

	// Restarts background
	background->SetImage(g_pResources->getBG_1());
	background2->SetImage(g_pResources->getWhiteBG());
	background->m_Alpha = 1.0f;
	background2->m_Alpha = 0.0f;
	nature_bg->SetImage(g_pResources->getNature_1());
	nature_bg2->SetImage(g_pResources->getNature_2());
	nature_bg->m_X = 0;
	nature_bg2->m_X = (float)IwGxGetScreenWidth();
	// Remove all the monsters
	g_pMonsterManager->reset();

	// Sets hero to normal
	g_pHero->run();

	// Creates the monsters
	g_pMonsterManager->create_enemies();

	updateScore();

	//Handles the monsters
	Monster* all_monsters = g_pMonsterManager->return_first();
	while (all_monsters != 0)
	{
		RemoveChild(all_monsters);
		g_pMonsterManager->Remove(all_monsters);
		delete all_monsters;
		all_monsters = g_pMonsterManager->return_first();
	}

	//Handles the dead monsters
	all_monsters = g_pDeadMonsterManager->return_first();
	while (all_monsters != 0)
	{
		RemoveChild(all_monsters);
		g_pDeadMonsterManager->Remove(all_monsters);
		delete all_monsters;
		all_monsters = g_pDeadMonsterManager->return_first();
	}

	//Deletes and cleans
	RemoveChild(adBG);
	RemoveChild(highScoreTxtLabel);
	RemoveChild(scoreBoardBG);
	RemoveChild(replayButton);
	RemoveChild(backToMenuButton);
	RemoveChild(endScoreLabel);
	RemoveChild(highScoreLabel);
	//RemoveChild(trophiesButton);
	//RemoveChild(shareButton);
	delete highScoreTxtLabel;
	delete endScoreLabel;
	delete highScoreLabel;
	delete backToMenuButton;
	delete replayButton;
	//delete trophiesButton;
	//delete shareButton;
	delete scoreBoardBG;
	delete adBG;

	//Black Background
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
	blackBG->m_Alpha = 1.0;
	blackBG->m_IsVisible = true;

	AddChild(blackBG);

	g_pTweener->Tween(1.0f,
		FLOAT, &blackBG->m_Alpha, 0.0f,
		EASING, Ease::linear,
		END);
}
/*******************************************************************
function: createBackgrounds
createBackgrounds creates a vector of all the backgrounds.


@params:   None
@returns:  None
*******************************************************************/
void Game::createBackgrounds()
{
	
	backgrounds.push_back(g_pResources->getBG_1());
	backgrounds.push_back(g_pResources->getBG_2());
	backgrounds.push_back(g_pResources->getBG_3());
	backgrounds.push_back(g_pResources->getBG_4());
	backgrounds.push_back(g_pResources->getBG_5());
	backgrounds.push_back(g_pResources->getBG_6());
	backgrounds.push_back(g_pResources->getBG_7());
	backgrounds.push_back(g_pResources->getBG_8());
	backgrounds.push_back(g_pResources->getBG_9());
	backgrounds.push_back(g_pResources->getBG_10());
	backgrounds.push_back(g_pResources->getBG_11());
	backgrounds.push_back(g_pResources->getBG_12());
	backgrounds.push_back(g_pResources->getBG_13());
	backgrounds.push_back(g_pResources->getBG_14());
	backgrounds.push_back(g_pResources->getBG_15());
	backgrounds.push_back(g_pResources->getBG_16());
	backgrounds.push_back(g_pResources->getBG_17());
	backgrounds.push_back(g_pResources->getBG_18());
	backgrounds.push_back(g_pResources->getBG_19());
}
/*******************************************************************
function: changeBackgrounds
changeBackgrounds changes background depending on score.


@params:   None
@returns:  None
*******************************************************************/
void Game::changeBackgrounds()
{
	if (score % bgCounterForScore == 0 && score != 0)
	{
		if (background->m_Alpha == 1.0f)
		{
			background2->SetImage(backgrounds[backgroundCounter]);
			g_pTweener->Tween(0.5f,
				FLOAT, &background->m_Alpha, 0.0f,
				EASING, Ease::linear,
				END);
			g_pTweener->Tween(0.5f,
				FLOAT, &background2->m_Alpha, 1.0f,
				EASING, Ease::linear,
				END);
		}
		else
		{
			background->SetImage(backgrounds[backgroundCounter]);
			g_pTweener->Tween(0.5f,
				FLOAT, &background2->m_Alpha, 0.0f,
				EASING, Ease::linear,
				END);
			g_pTweener->Tween(0.5f,
				FLOAT, &background->m_Alpha, 1.0f,
				EASING, Ease::linear,
				END);
		}
		if (backgroundCounter >= 18)
		{
			backgroundCounter = 0;
		}
		else
		{
			backgroundCounter++;
		}
		bgCounterForScore += 10;
	}
	
}


/*******************************************************************
function: createNature
createNature creates a vector of all the nature.


@params:   None
@returns:  None
*******************************************************************/
void Game::createNature()
{

	nature.push_back(g_pResources->getNature_1());
	nature.push_back(g_pResources->getNature_2());
	nature.push_back(g_pResources->getNature_3());
	nature.push_back(g_pResources->getNature_4());
	nature.push_back(g_pResources->getNature_5());
	nature.push_back(g_pResources->getNature_6());
	nature.push_back(g_pResources->getNature_7());
	nature.push_back(g_pResources->getNature_8());
	nature.push_back(g_pResources->getNature_9());
	nature.push_back(g_pResources->getNature_10());
	nature.push_back(g_pResources->getNature_11());
	nature.push_back(g_pResources->getNature_12());
}

/*******************************************************************
function: changeNature
changeNature changes Nature.


@params:   None
@returns:  None
*******************************************************************/
void Game::changeNature()
{
	
	if (nature_bg->m_X <= -(float)IwGxGetScreenWidth())
	{
		nature_bg->SetImage(nature[natureCounter]);
		nature_bg->m_X = (float)IwGxGetScreenWidth();
	
	}
	else if (nature_bg2->m_X <= -(float)IwGxGetScreenWidth())
	{
		nature_bg2->SetImage(nature[natureCounter]);
		nature_bg2->m_X = (float)IwGxGetScreenWidth();
	}
	else
	{
		std::cout << "ERROR SHOULD NOT REACH HERE" << endl;
	}


	if (natureCounter >= 12)
	{
		natureCounter = 0;
	}
	else
	{
		natureCounter++;
	}
	

}
/*******************************************************************
function: pauseGame

@params:    None
@returns:   None
******************************************************************/
void Game::pauseGame()
{
	//TODO
}

/*******************************************************************
function: resumeGame

@params:    None
@returns:   None
******************************************************************/
void Game::resumeGame()
{
	//TODO
}

/*******************************************************************
function: updateScore
Updates the score and its label whenever it changes.

@params:   None
@returns:  None
*******************************************************************/
void Game::updateScore()
{
	// Add to score and update highest score
	// Update score label text to show new score and level

	//This deals with the highest score and adjusting it whenever a new high score is made
	if (high_score < score)
	{
		high_score = score;
		ofstream highestScoreFile;
		highestScoreFile.open("ram://high_score.txt", std::ofstream::out | std::ofstream::trunc);
		if (highestScoreFile.is_open())
		{
			highestScoreFile << high_score;
			highestScoreFile.close();
		}
		else
		{
			cout << endl << endl << "ERROR: FILE DID NOT OPEN" << endl << endl;
		}
	}
	
	snprintf(high_scr, 16, "%d", high_score);
	snprintf(scr, 16, "%d", score);
	if (score > 9 && score < 100)
	{
		scoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.49f;
	}
	else if (score > 99 && score < 1000)
	{
		scoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.48f;
	}
	else if (score > 999)
	{
		scoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.47f;
	}
	scoreLabel->m_Text = scr;
}

/*******************************************************************
function: scoreBoard
scoreBoard is the screen that displays the score as the player dies,
going into lose state.

THIS PART IS THE LOSE STATE SCREEN

@params:   None
@returns:  None
*******************************************************************/
void Game::scoreBoard()
{
	if (if_initial_game_start)
	{
		g_pResources->ScoreBoard();
		if_initial_game_start = false;
	}
	//If retrying the game and alreaady played for the first time
	
	if_initial_game_start = false;

	
	//Scoreboard background
	scoreBoardBG = new CSprite();
	scoreBoardBG->m_X = (float)IwGxGetScreenWidth() / 2;
	scoreBoardBG->m_Y = (float)IwGxGetScreenHeight() / 2;
	scoreBoardBG->SetImage(g_pResources->getScoreBoardBG());
	scoreBoardBG->m_W = scoreBoardBG->GetImage()->GetWidth();
	scoreBoardBG->m_H = scoreBoardBG->GetImage()->GetHeight();
	scoreBoardBG->m_AnchorX = 0.5;
	scoreBoardBG->m_AnchorY = 0.5;
	// Fit background to screen size
	scoreBoardBG->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	scoreBoardBG->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();

	//AD PART
	adBG = new CSprite();
	adBG->m_X = 0;
	adBG->m_Y = 0;
	adBG->SetImage(g_pResources->getADBG());
	adBG->m_W = adBG->GetImage()->GetWidth();
	adBG->m_H = adBG->GetImage()->GetHeight();
	adBG->m_ScaleX = (float)IwGxGetScreenWidth() / adBG->GetImage()->GetWidth();
	adBG->m_ScaleY = (float)IwGxGetScreenHeight() * 0.20f / adBG->GetImage()->GetHeight();

	//The text for the Score sprites
	endScoreLabel = new CLabel();
	endScoreLabel->m_Y = (float)IwGxGetScreenHeight() * 0.16f;
	endScoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.48f;
	endScoreLabel->m_Text = scr;
	endScoreLabel->m_Font = g_pResources->getFont();
	endScoreLabel->m_ScaleX = (float)IwGxGetScreenWidth() * 0.20f / 100;
	endScoreLabel->m_ScaleY = (float)IwGxGetScreenWidth() * 0.20f / 100;
	endScoreLabel->m_Color = CColor(0xff, 0xff, 0xff, 0xff);

	//The text for the HighScore sprites
	highScoreLabel = new CLabel();
	highScoreLabel->m_Y = (float)IwGxGetScreenHeight() * 0.40f; 
	highScoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.60f;
	highScoreLabel->m_Text = high_scr;
	highScoreLabel->m_Font = g_pResources->getFont();
	highScoreLabel->m_ScaleX = (float)IwGxGetScreenWidth() * 0.10f / 100;
	highScoreLabel->m_ScaleY = (float)IwGxGetScreenWidth() * 0.10f / 100;
	highScoreLabel->m_Color = CColor(0xff, 0xff, 0xff, 0xff);

	highScoreTxtLabel = new CLabel();
	highScoreTxtLabel->m_Y = (float)IwGxGetScreenHeight() * 0.40f;
	highScoreTxtLabel->m_X = (float)IwGxGetScreenWidth() * 0.35f;
	highScoreTxtLabel->m_Text = "High Score : ";
	highScoreTxtLabel->m_Font = g_pResources->getFont();
	highScoreTxtLabel->m_ScaleX = (float)IwGxGetScreenWidth() * 0.10f / 100;
	highScoreTxtLabel->m_ScaleY = (float)IwGxGetScreenWidth() * 0.10f / 100;
	highScoreTxtLabel->m_Color = CColor(0xff, 0xff, 0xff, 0xff);


	//The Replay Button
	replayButton = new CSprite();
	replayButton->SetImage(g_pResources->getReplayButtonIdle());
	replayButton->m_X = (float)IwGxGetScreenWidth() / 2;
	replayButton->m_Y = (float)IwGxGetScreenHeight();
	replayButton->m_W = replayButton->GetImage()->GetWidth();
	replayButton->m_H = replayButton->GetImage()->GetHeight();
	replayButton->m_ScaleX = (float)IwGxGetScreenWidth() * 0.175f / replayButton->GetImage()->GetWidth();
	replayButton->m_ScaleY = replayButton->m_ScaleX;
	replayButton->m_AnchorX = 0.5;

	//Go to menu button
	backToMenuButton = new CSprite();
	backToMenuButton->SetImage(g_pResources->getMenuButtonIdle());
	backToMenuButton->m_X = (float)IwGxGetScreenWidth() / 2;
	backToMenuButton->m_Y = (float)IwGxGetScreenHeight();
	backToMenuButton->m_W = backToMenuButton->GetImage()->GetWidth();
	backToMenuButton->m_H = backToMenuButton->GetImage()->GetHeight();
	backToMenuButton->m_ScaleX = (float)IwGxGetScreenWidth() * 0.175f / backToMenuButton->GetImage()->GetWidth();
	backToMenuButton->m_ScaleY = backToMenuButton->m_ScaleX;
	backToMenuButton->m_AnchorX = 0.5;
	

	
	
	
// Not used until next update!	
	/*
	//Trophies button
	trophiesButton = new CSprite();
	trophiesButton->SetImage(g_pResources->getTrophiesButtonIdle());
	trophiesButton->m_X = (float)IwGxGetScreenWidth() * 0.5475f;
	trophiesButton->m_Y = (float)IwGxGetScreenHeight() * 0.78f;
	trophiesButton->m_W = trophiesButton->GetImage()->GetWidth();
	trophiesButton->m_H = trophiesButton->GetImage()->GetHeight();
	trophiesButton->m_ScaleX = (float)IwGxGetScreenWidth() * 0.082f / trophiesButton->GetImage()->GetWidth();
	trophiesButton->m_ScaleY = trophiesButton->m_ScaleX;
	trophiesButton->m_AnchorX = 0.5;

	//Share button
	shareButton = new CSprite();
	shareButton->SetImage(g_pResources->getShareButtonIdle());
	shareButton->m_X = (float)IwGxGetScreenWidth() * 0.455f;
	shareButton->m_Y = (float)IwGxGetScreenHeight() * 0.78f;
	shareButton->m_W = shareButton->GetImage()->GetWidth();
	shareButton->m_H = shareButton->GetImage()->GetHeight();
	shareButton->m_AnchorX = 0.5;
	shareButton->m_ScaleX = (float)IwGxGetScreenWidth() * 0.082f / shareButton->GetImage()->GetWidth();
	shareButton->m_ScaleY = shareButton->m_ScaleX;
*/
	//For displaying the score accurately in the middle of the screen
	if (score > 9 && score < 100)
	{
		endScoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.47f;
	}
	else if (score > 99 && score < 1000)
	{
		endScoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.46f;
	}
	else if (score > 999)
	{
		endScoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.44f;
	}

	//For displaying the highscore
	if (high_score > 9 && high_score < 100)
	{
		highScoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.59f;
	}
	else if (high_score > 99 && high_score < 1000)
	{
		highScoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.58f;
	}
	else if (high_score > 999)
	{
		highScoreLabel->m_X = (float)IwGxGetScreenWidth() * 0.56f;
	}

	AddChild(scoreBoardBG);
	AddChild(adBG);
	AddChild(endScoreLabel);
	AddChild(highScoreLabel);
	AddChild(highScoreTxtLabel);
	AddChild(replayButton);
	AddChild(backToMenuButton);
//	AddChild(trophiesButton);
//	AddChild(shareButton);
	scoreBoardActive = true;

	//Tween to transition to replay game
	g_pTweener->Tween(0.5f,
		FLOAT, &replayButton->m_Y, (float)IwGxGetScreenHeight() * 0.63f,
		EASING, Ease::sineIn,
		END);
	//Tween to transition to the menu
	g_pTweener->Tween(0.5f,
		FLOAT, &backToMenuButton->m_Y, (float)IwGxGetScreenHeight() * 0.82f,
		EASING, Ease::sineIn,
		END);

	// Crashes when using both
	/*g_pTweener->Tween(0.5f,
	FLOAT, &shareButton->m_Y, (float)IwGxGetScreenHeight() * 0.65f,
	EASING, Ease::sineIn,
	END);
	g_pTweener->Tween(0.5f,
	FLOAT, &trophiesButton->m_Y, (float)IwGxGetScreenHeight() * 0.66f,
	EASING, Ease::sineIn,
	END);*/
}

/*******************************************************************
function: toMainMenu
transitions the screen accordingly and changes the scene to the main menu

@params:    None
@returns:   None
******************************************************************/
void Game::toMainMenu()
{

	g_pAudio->PlayMusic("audio/title.wav");
	MainMenu* main_menu = (MainMenu*)g_pSceneManager->Find("mainmenu");
	main_menu->black();
	main_menu->returnToScreen();
	// Reset input x and y so it doesn't interfer with start button
	g_pInput->m_X = 0;
	g_pInput->m_Y = 0;

	g_pSceneManager->SwitchTo(main_menu);
}

/*******************************************************************
function: toScoreBoard
transition the screen of the game to the score board

@params:    CTween*
@returns:   None
******************************************************************/
void Game::toScoreBoard(CTween* pTween)
{


	Game* game = (Game*)g_pSceneManager->Find("game");
	game->scoreBoard();
}

/*******************************************************************
function: collision_Hero_Monsters
checks whether the hero collides with a monster

@params:    None
@returns:   None
******************************************************************/
void Game::collision_Hero_Monsters()
{
	// Checks if the monster is less than a certain x axis, sets the variable to the collided monster
	collided_monsters = g_pMonsterManager->check_touched(hero1->m_X + hero1->m_W, hero1->m_Y);

	//If no monsters collided, don't go through rest of the statement.
	if (collided_monsters == 0)
	{
		return;
	}

	//This is when the hero accurately chooses the correct stance against the enemy's weapon, doing so would make the hero kill the enemy
	if (collided_monsters->get_weapon() == g_pHero->get_stance())
	{
		//These if statements play the sounds corresponding to the specific stance
		if (g_pHero->get_stance() == STANCE_SWORD_SHIELD)
		{
			g_pAudio->PlaySound("audio/testbeep.wav");
		}
		else if (g_pHero->get_stance() == STANCE_BOW)
		{
			g_pAudio->PlaySound("audio/armor_hit.wav");
		}
		else if (g_pHero->get_stance() == STANCE_STAFF)
		{
			g_pAudio->PlaySound("audio/Bloop 1.wav");
		}
		//THIS IS THE ERROR STATEMENT, it should never come here
		else
		{
			cout << endl << endl << "in function: collision_Hero_Monsters -> ERROR, Not suppose to come here" << endl << endl;
		}

		//Increments the game score accordingly to the monsters score
		//Some monsters have higher scores than others
		score += collided_monsters->get_score();

		//Every 10 monsters lower timer to summon monsters faster
		g_pMonsterManager->lowerSummon();

		// Don't spawn monsters on dragon kill
		// if it is a dragon update the randomdragon number
		if (collided_monsters->get_dragon() == 1)
		{
			intRandomDragon += rand() % 25 + 25;
		}

		updateScore();

		// Death Animation
		g_pMonsterManager->death(collided_monsters);
		m_Timers.Add(new Timer(0.45f, 1, &Game::deadEnemy, (void*)this));
		g_pMonsterManager->Remove(collided_monsters);

		//wtf manz?
		RemoveChild(hero1);
		AddChild(hero1);
	}
	//When the hero chooses the wrong stance against the enemy's weapon, the hero will do its death animation, setting the lose state to true
	else
	{
		//???? What is this for ?????
		collided_monsters = g_pMonsterManager->check_touched(hero1->m_X + hero1->m_W/2, hero1->m_Y);
		
		if (collided_monsters != 0)
		{
			// Lost
			
			m_Timers.Clear(); // Clear the timers so you don't change back to normal form
			lose = true;
			// Flash on flash off
			g_pAudio->PlayMusic("audio/RIP.wav");
			hero_deathAnimation();
		}
	}
}

/*******************************************************************
function: hero_deathAnimation
The state where the hero is dying.

@params:    None
@returns:   None
******************************************************************/
void Game::hero_deathAnimation()
{
	g_pHero->hero_dead();

	//flashes the screen white for a split second right when the hero dies
	//White background
	whiteBG = new CSprite();
	whiteBG->m_X = (float)IwGxGetScreenWidth() / 2;
	whiteBG->m_Y = (float)IwGxGetScreenHeight() / 2;
	whiteBG->SetImage(g_pResources->getWhiteBG());
	whiteBG->m_W = whiteBG->GetImage()->GetWidth();
	whiteBG->m_H = whiteBG->GetImage()->GetHeight();
	whiteBG->m_AnchorX = 0.5;
	whiteBG->m_AnchorY = 0.5;
	// Fit background to screen size
	whiteBG->m_ScaleX = (float)IwGxGetScreenWidth();
	whiteBG->m_ScaleY = (float)IwGxGetScreenHeight();
	whiteBG->m_Alpha = 0.0;
	whiteBG->m_IsVisible = true;

	//Black background
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
	AddChild(whiteBG);

	//Tweens the background a quick white flash
	g_pTweener->Tween(0.05f,
		FLOAT, &whiteBG->m_Alpha, 1.0f,
		EASING, Ease::linear,
		END);
	g_pTweener->Tween(0.05f,
		FLOAT, &whiteBG->m_Alpha, 0.0f,
		EASING, Ease::linear,
		DELAY, 0.05f,
		END);
	//Then tweens a black screen transition into the actual score board with the lose state
	g_pTweener->Tween(1.0f,
		FLOAT, &blackBG->m_Alpha, 1.0f,
		EASING, Ease::linear,
		DELAY, 0.6f,
		ONCOMPLETE, toScoreBoard,
		END);

	//Resets
	timerDone = true;
	g_pInput->m_X = 0;
	g_pInput->m_Y = 0;
}

/*******************************************************************
function: deadEnemy
Handles killing off the dead enemies

@params:    Timer*, void*
@returns:   None
******************************************************************/
void Game::deadEnemy(Timer* timer, void* userData)
{
	g_pDeadMonsterManager->Death();
}

/*******************************************************************
function: normalHero
Change stance to normal

@params:    Timer*, void*
@returns:   None
******************************************************************/
void Game::normalHero(Timer* timer, void* userData)
{
	g_pHero->run();
	timerDone = true;
}

// === UNUSED ===
/*
// Remove hero
void Game::removeHero()
{
RemoveChild(g_pHero);
g_pHero->deleteHero();
}

// Not needed because instead of one layer of button we added a fade layer on top of button background layer

void Game::toChangeBGButtons(CTween* pTween)
{
Game* game = (Game*)g_pSceneManager->Find("game");
game->changeBGButtons();
}

void Game::changeBGButtons()
{
ssFadeBG->m_Alpha = 0;
staffFadeBG->m_Alpha = 0;
bowFadeBG->m_Alpha = 0;
}
*/


