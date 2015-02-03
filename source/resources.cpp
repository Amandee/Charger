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

#include "resources.h"
#include "Iw2D.h"
#include <iostream>
// Global resources
Resources* g_pResources = 0;


Resources::Resources()
{
    // Set bool to false

	mainMenu = false;
	game = false;
	scoreboard = false;








	


}

Resources::~Resources()
{


	
	//delete NatureBG;

	if (mainMenu)
	{
		delete Font;

		delete BlackBG;
		delete WhiteBG;

		delete HeroBow;
		delete HeroBowAtlas;

		delete HeroSS;
		delete HeroSSAtlas;

		delete HeroStaff;
		delete HeroStaffAtlas;

		delete HeroRun;
		delete HeroRunAtlas;

		delete HeroDeath;
		delete HeroDeathAtlas;

		delete GameGround;
		delete StartButtonPressed;
		delete StartButtonIdle;
		delete Title;
		delete MenuBG;


		delete GameBG_1;
		delete GameBG_2;
		delete GameBG_3;
		delete GameBG_4;
		delete GameBG_5;
		delete GameBG_6;
		delete GameBG_7;
		delete GameBG_8;
		delete GameBG_9;
		delete GameBG_10;

		delete NatureBG_1;
		delete NatureBG_2;
		delete NatureBG_3;
		delete NatureBG_4;
		delete NatureBG_5;
		delete NatureBG_6;
		delete NatureBG_7;
		delete NatureBG_8;
		delete NatureBG_9;
		delete NatureBG_10;
		delete NatureBG_11;
		delete NatureBG_12;

		delete EnemySS;
		delete EnemyStaff;
		delete EnemyBow;
		
		delete BowButton;
		delete SSButton;
		delete StaffButton;

		delete ButtonPressed;
		delete ButtonIdle;

		delete EnemyBowDeath;
		delete EnemySSDeath;
		delete EnemyStaffDeath;

		delete GameBG_11;
		delete GameBG_12;
		delete GameBG_13;
		delete GameBG_14;
		delete GameBG_15;
		delete GameBG_16;
		delete GameBG_17;
		delete GameBG_18;
		delete GameBG_19;
	}

	if (game)
	{

		
	





		
		delete EnemySSAtlas;
		delete EnemyStaffAtlas;
		delete EnemyBowAtlas;
	
		delete EnemyBowDeathAtlas;
		delete EnemySSDeathAtlas;
		delete EnemyStaffDeathAtlas;


	
	}

	if (scoreboard)
	{
		delete MenuButtonPressed;
		delete MenuButtonIdle;
		delete ReplayButtonPressed;
		delete ReplayButtonIdle;
		delete ShareButtonPressed;
		delete ShareButtonIdle;
		delete TrophiesButtonPressed;
		delete TrophiesButtonIdle;
		delete ADBG;

		delete ScoreBoardBG;
	}
}




void Resources::MainMenu()
{

	// Font
	Font = Iw2DCreateFont("fonts/archer.gxfont");


	// Menu Screen
	StartButtonIdle = Iw2DCreateImage("textures/startbutton_idle.png");
	StartButtonPressed = Iw2DCreateImage("textures/startbutton_pressed.png");
	Title = Iw2DCreateImage("textures/title.png");
	MenuBG = Iw2DCreateImage("textures/bg_title.jpg");

	BlackBG = Iw2DCreateImage("textures/black.jpg");
	WhiteBG = Iw2DCreateImage("textures/white.jpg");

	NatureBG_1 = Iw2DCreateImage("textures/nature_1.png");
	NatureBG_2 = Iw2DCreateImage("textures/nature_2.png");
	NatureBG_3 = Iw2DCreateImage("textures/nature_3.png");
	NatureBG_4 = Iw2DCreateImage("textures/nature_4.png");
	NatureBG_5 = Iw2DCreateImage("textures/nature_5.png");
	NatureBG_6 = Iw2DCreateImage("textures/nature_6.png");
	NatureBG_7 = Iw2DCreateImage("textures/nature_7.png");
	NatureBG_8 = Iw2DCreateImage("textures/nature_8.png");
	NatureBG_9 = Iw2DCreateImage("textures/nature_9.png");
	NatureBG_10 = Iw2DCreateImage("textures/nature_10.png");
	NatureBG_11 = Iw2DCreateImage("textures/nature_11.png");
	NatureBG_12 = Iw2DCreateImage("textures/nature_12.png");
	GameGround = Iw2DCreateImage("textures/gameground.png");

	// Hero stance

	HeroSS = Iw2DCreateImage("textures/hero_ss.png");
	HeroStaff = Iw2DCreateImage("textures/hero_staff.png");
	HeroBow = Iw2DCreateImage("textures/hero_bow.png");
	HeroRun = Iw2DCreateImage("textures/hero_run.png");
	HeroDeath = Iw2DCreateImage("textures/hero_death.png");

	// Hero atlas



	int frame_w = (int)(HeroBow->GetWidth() / 4);
	int frame_h = (int)(HeroBow->GetHeight() / 2);
	HeroBowAtlas = new CAtlas(frame_w, frame_h, 8, HeroBow);


	frame_w = (int)(HeroSS->GetWidth() / 4);
	frame_h = (int)(HeroSS->GetHeight() / 2);
	HeroSSAtlas = new CAtlas(frame_w, frame_h, 8, HeroSS);


	frame_w = (int)(HeroStaff->GetWidth() / 4);
	frame_h = (int)(HeroStaff->GetHeight() / 2);
	HeroStaffAtlas = new CAtlas(frame_w, frame_h, 8, HeroStaff);

	frame_w = (int)(HeroRun->GetWidth() / 4);
	frame_h = (int)(HeroRun->GetHeight() / 2);
	HeroRunAtlas = new CAtlas(frame_w, frame_h, 8, HeroRun);

	frame_w = (int)(HeroDeath->GetWidth() / 4);
	frame_h = (int)(HeroDeath->GetHeight() / 2);
	HeroDeathAtlas = new CAtlas(frame_w, frame_h, 8, HeroDeath);
	

	GameBG_1 = Iw2DCreateImage("textures/bg_1.jpg");
	GameBG_2 = Iw2DCreateImage("textures/bg_2.jpg");
	GameBG_3 = Iw2DCreateImage("textures/bg_3.jpg");
	GameBG_4 = Iw2DCreateImage("textures/bg_4.jpg");
	GameBG_5 = Iw2DCreateImage("textures/bg_5.jpg");
	GameBG_6 = Iw2DCreateImage("textures/bg_6.jpg");
	GameBG_7 = Iw2DCreateImage("textures/bg_7.jpg");
	GameBG_8 = Iw2DCreateImage("textures/bg_8.jpg");
	GameBG_9 = Iw2DCreateImage("textures/bg_9.jpg");
	GameBG_10 = Iw2DCreateImage("textures/bg_10.jpg");

	mainMenu = true;


	GameBG_11 = Iw2DCreateImage("textures/bg_11.jpg");
	GameBG_12 = Iw2DCreateImage("textures/bg_12.jpg");
	GameBG_13 = Iw2DCreateImage("textures/bg_13.jpg");
	GameBG_14 = Iw2DCreateImage("textures/bg_14.jpg");
	GameBG_15 = Iw2DCreateImage("textures/bg_15.jpg");
	GameBG_16 = Iw2DCreateImage("textures/bg_16.jpg");
	GameBG_17 = Iw2DCreateImage("textures/bg_17.jpg");
	GameBG_18 = Iw2DCreateImage("textures/bg_18.jpg");
	GameBG_19 = Iw2DCreateImage("textures/bg_19.jpg");




	// Enemies

	EnemyBow = Iw2DCreateImage("textures/enemybow.png");
	EnemySS = Iw2DCreateImage("textures/enemyss.png");
	EnemyStaff = Iw2DCreateImage("textures/enemystaff.png");

	EnemyBowDeath = Iw2DCreateImage("textures/enemybowdeath.png");
	EnemySSDeath = Iw2DCreateImage("textures/enemyssdeath.png");
	EnemyStaffDeath = Iw2DCreateImage("textures/enemystaffdeath.png");


	// Buttons

	BowButton = Iw2DCreateImage("textures/bowbutton.png");
	SSButton = Iw2DCreateImage("textures/ssbutton.png");
	StaffButton = Iw2DCreateImage("textures/staffbutton.png");

	// Buttons BG for the 3 buttons

	ButtonPressed = Iw2DCreateImage("textures/buttonpressed.png");
	ButtonIdle = Iw2DCreateImage("textures/buttonidle.png");
}

void Resources::Game()
{

	
	


	// Load fonts



	// Create enemy atlas


	int frame_w = (int)(EnemySS->GetWidth() / 4);
	int frame_h = (int)(EnemySS->GetHeight() / 2);
	EnemySSAtlas = new CAtlas(frame_w, frame_h, 8, EnemySS);

	frame_w = (int)(EnemyBow->GetWidth() / 4);
	frame_h = (int)(EnemyBow->GetHeight() / 2);
	EnemyBowAtlas = new CAtlas(frame_w, frame_h, 8, EnemyBow);

	frame_w = (int)(EnemyStaff->GetWidth() / 4);
	frame_h = (int)(EnemyStaff->GetHeight() / 2);
	EnemyStaffAtlas = new CAtlas(frame_w, frame_h, 8, EnemyStaff);

	frame_w = (int)(EnemySSDeath->GetWidth() / 4);
	frame_h = (int)(EnemySSDeath->GetHeight() / 2);
	EnemySSDeathAtlas = new CAtlas(frame_w, frame_h, 8, EnemySSDeath);

	frame_w = (int)(EnemyBowDeath->GetWidth() / 4);
	frame_h = (int)(EnemyBowDeath->GetHeight() / 2);
	EnemyBowDeathAtlas = new CAtlas(frame_w, frame_h, 8, EnemyBowDeath);

	frame_w = (int)(EnemyStaffDeath->GetWidth() / 4);
	frame_h = (int)(EnemyStaffDeath->GetHeight() / 2);
	EnemyStaffDeathAtlas = new CAtlas(frame_w, frame_h, 8, EnemyStaffDeath);

	game = true;
}

void Resources::ScoreBoard()
{
	// Scoreboard Screen
	MenuButtonIdle = Iw2DCreateImage("textures/menubutton_idle.png");
	MenuButtonPressed = Iw2DCreateImage("textures/menubutton_pressed.png");
	ReplayButtonIdle = Iw2DCreateImage("textures/replaybutton_idle.png");
	ReplayButtonPressed = Iw2DCreateImage("textures/replaybutton_pressed.png");
	ShareButtonIdle = Iw2DCreateImage("textures/sharebutton_idle.png");
	ShareButtonPressed = Iw2DCreateImage("textures/sharebutton_pressed.png");
	TrophiesButtonIdle = Iw2DCreateImage("textures/trophiesbutton_idle.png");
	TrophiesButtonPressed = Iw2DCreateImage("textures/trophiesbutton_pressed.png");
	ScoreBoardBG = Iw2DCreateImage("textures/bg_score.jpg");
	ADBG = Iw2DCreateImage("textures/ad_bg.jpg");
	scoreboard = true;
}