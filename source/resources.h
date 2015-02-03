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

#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#define MAX_GEM_TYPES   5

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

/**
 * @class Resources
 *
 * @brief Resources class
 *
 * The that manages the lifetime of the following types of resources:
 * - Images
 * - Fonts
 * - Atlases
 */
class Resources
{
protected:
    CIw2DImage*     Gem;
	CIw2DImage*		GameBG_1;
	CIw2DImage*		GameBG_2;
	CIw2DImage*		GameBG_3; 
	CIw2DImage*		GameBG_4; 
	CIw2DImage*		GameBG_5;
	CIw2DImage*		GameBG_6; 
	CIw2DImage*		GameBG_7;
	CIw2DImage*		GameBG_8;
	CIw2DImage*		GameBG_9;
	CIw2DImage*		GameBG_10;
	CIw2DImage*		GameBG_11;
	CIw2DImage*		GameBG_12;
	CIw2DImage*		GameBG_13;
	CIw2DImage*		GameBG_14;
	CIw2DImage*		GameBG_15;
	CIw2DImage*		GameBG_16;
	CIw2DImage*		GameBG_17;
	CIw2DImage*		GameBG_18;
	CIw2DImage*		GameBG_19;
    CIw2DImage*     MenuButton;
    CIw2DImage*     Placard;
    CIw2DImage*     PauseIcon;
	CIw2DImage*     PlayButton;

	CIw2DImage*     NatureBG_1;
	CIw2DImage*     NatureBG_2;
	CIw2DImage*     NatureBG_3;
	CIw2DImage*     NatureBG_4;
	CIw2DImage*     NatureBG_5;
	CIw2DImage*     NatureBG_6;
	CIw2DImage*     NatureBG_7;
	CIw2DImage*     NatureBG_8;
	CIw2DImage*     NatureBG_9;
	CIw2DImage*     NatureBG_10;
	CIw2DImage*     NatureBG_11;
	CIw2DImage*     NatureBG_12;


	// Menu Screen
	CIw2DImage*     StartButtonPressed;
	CIw2DImage*     StartButtonIdle;
	CIw2DImage*     Title;
	CIw2DImage*     MenuBG;

	// ScoreBoard Screen
	CIw2DImage*     MenuButtonPressed;
	CIw2DImage*     MenuButtonIdle;
	CIw2DImage*     ReplayButtonPressed;
	CIw2DImage*     ReplayButtonIdle;
	CIw2DImage*     ShareButtonPressed;
	CIw2DImage*     ShareButtonIdle;
	CIw2DImage*     TrophiesButtonPressed;
	CIw2DImage*     TrophiesButtonIdle;
	CIw2DImage*     ScoreBoardBG;
	CIw2DImage*		ADBG;

	// Black BG
	CIw2DImage*     BlackBG;
	// White BG
	CIw2DImage*     WhiteBG;

	// Heroes and enemies images


	// Hero
	CIw2DImage*     HeroBow;
	CIw2DImage*     HeroStaff;
	CIw2DImage*     HeroSS;
	CIw2DImage*     HeroRun;
	CIw2DImage*     HeroDeath;

	// Enemy
	CIw2DImage*     EnemySS;
	CIw2DImage*     EnemyStaff;
	CIw2DImage*     EnemyBow;
	
	CIw2DImage*     EnemySSDeath;
	CIw2DImage*     EnemyStaffDeath;
	CIw2DImage*     EnemyBowDeath;

	CIw2DImage*     GameGround;
	//CIw2DImage*		NatureBG;

	// Buttons
	CIw2DImage*     BowButton;
	CIw2DImage*     SSButton;
	CIw2DImage*     StaffButton;

	CIw2DImage*     ButtonPressed;
	CIw2DImage*     ButtonIdle;


    CIw2DFont*      Font;
    CAtlas*         GemAtlas;

	// Heroes and enemies atlas
	CAtlas*			HeroBowAtlas;
	CAtlas*			HeroSSAtlas;
	CAtlas*			HeroStaffAtlas;
	CAtlas*			HeroRunAtlas;
	CAtlas*			HeroDeathAtlas;

	CAtlas*			EnemyBowAtlas;
	CAtlas*			EnemySSAtlas;
	CAtlas*			EnemyStaffAtlas;
	CAtlas*			EnemySSDeathAtlas;
	CAtlas*			EnemyBowDeathAtlas;
	CAtlas*			EnemyStaffDeathAtlas;

	// bool to only delete things that are made
	bool mainMenu;
	bool game;
	bool scoreboard;

public:

	void			MainMenu();
	void			Game();
	void			ScoreBoard();

	CIw2DImage*     getStartButtonIdle()                    { return StartButtonIdle; }
	CIw2DImage*     getStartButtonPressed()                 { return StartButtonPressed; }
	CIw2DImage*     getTitle()                 { return Title; }


	CIw2DImage*     getBG_1()                    { return GameBG_1; }
	CIw2DImage*     getBG_2()                    { return GameBG_2; }
	CIw2DImage*     getBG_3()                    { return GameBG_3; }
	CIw2DImage*     getBG_4()                    { return GameBG_4; }
	CIw2DImage*     getBG_5()                    { return GameBG_5; }
	CIw2DImage*     getBG_6()                    { return GameBG_6; }
	CIw2DImage*     getBG_7()                    { return GameBG_7; }
	CIw2DImage*     getBG_8()                    { return GameBG_8; }
	CIw2DImage*     getBG_9()                    { return GameBG_9; }
	CIw2DImage*     getBG_10()                    { return GameBG_10; }
	CIw2DImage*     getBG_11()                    { return GameBG_11; }
	CIw2DImage*     getBG_12()                    { return GameBG_12; }
	CIw2DImage*     getBG_13()                    { return GameBG_13; }
	CIw2DImage*     getBG_14()                    { return GameBG_14; }
	CIw2DImage*     getBG_15()                    { return GameBG_15; }
	CIw2DImage*     getBG_16()                    { return GameBG_16; }
	CIw2DImage*     getBG_17()                    { return GameBG_17; }
	CIw2DImage*     getBG_18()                    { return GameBG_18; }
	CIw2DImage*     getBG_19()                    { return GameBG_19; }


	CIw2DImage*     getNature_1()                    { return NatureBG_1; }
	CIw2DImage*     getNature_2()                    { return NatureBG_2; }
	CIw2DImage*     getNature_3()                    { return NatureBG_3; }
	CIw2DImage*     getNature_4()                    { return NatureBG_4; }
	CIw2DImage*     getNature_5()                    { return NatureBG_5; }
	CIw2DImage*     getNature_6()                    { return NatureBG_6; }
	CIw2DImage*     getNature_7()                    { return NatureBG_7; }
	CIw2DImage*     getNature_8()                    { return NatureBG_8; }
	CIw2DImage*     getNature_9()                    { return NatureBG_9; }
	CIw2DImage*     getNature_10()                    { return NatureBG_10; }
	CIw2DImage*     getNature_11()                    { return NatureBG_11; }
	CIw2DImage*     getNature_12()                    { return NatureBG_12; }

	CIw2DImage*     getMenuBG()                 { return MenuBG; }

	CIw2DImage*     getBlackBG()              { return BlackBG; }
	CIw2DImage*     getWhiteBG()              { return WhiteBG; }

    CIw2DFont*      getFont()                   { return Font; }


	CIw2DImage*     getBowButton()              { return BowButton; }
	CIw2DImage*     getStaffButton()              { return StaffButton; }
	CIw2DImage*     getSSButton()              { return SSButton; }

	CIw2DImage*     getButtonPressed()              { return ButtonPressed; }
	CIw2DImage*     getButtonIdle()              { return ButtonIdle; }

	// Enemies
	CAtlas*			getEnemySSAtlas()				{ return EnemySSAtlas; }
	CAtlas*			getEnemyStaffAtlas()				{ return EnemyStaffAtlas; }
	CAtlas*			getEnemyBowAtlas()				{ return EnemyBowAtlas; }
	CAtlas*			getEnemySSDeath()				{ return EnemySSDeathAtlas; }
	CAtlas*			getEnemyStaffDeath()				{ return EnemyStaffDeathAtlas; }
	CAtlas*			getEnemyBowDeath()				{ return EnemyBowDeathAtlas; }


	CIw2DImage*     getGameGround()              { return GameGround; }

	CAtlas*			getHeroBow()				{ return HeroBowAtlas; }
	CAtlas*			getHeroSS()				{ return HeroSSAtlas; }
	CAtlas*			getHeroStaff()				{ return HeroStaffAtlas; }
	CAtlas*			getHeroRun()				{ return HeroRunAtlas; }
	CAtlas*			getHeroDeath()				{ return HeroDeathAtlas; }

	CAtlas*			getGemAtlas()				{ return GemAtlas; }

	// Scoreboard 
	CIw2DImage*     getReplayButtonPressed()              { return ReplayButtonPressed; }
	CIw2DImage*     getReplayButtonIdle()              { return ReplayButtonIdle; }
	CIw2DImage*     getMenuButtonPressed()              { return MenuButtonPressed; }
	CIw2DImage*     getMenuButtonIdle()              { return MenuButtonIdle; }
	CIw2DImage*     getShareButtonPressed()              { return ShareButtonPressed; }
	CIw2DImage*     getShareButtonIdle()              { return ShareButtonIdle; }
	CIw2DImage*     getTrophiesButtonPressed()              { return TrophiesButtonPressed; }
	CIw2DImage*     getTrophiesButtonIdle()              { return TrophiesButtonIdle; }
	CIw2DImage*     getADBG()              { return ADBG; }
	CIw2DImage*     getScoreBoardBG()                 { return ScoreBoardBG; }

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


