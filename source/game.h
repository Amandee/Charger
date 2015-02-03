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

#if !defined(__GAME_H__)
#define __GAME_H__

#include "hero.h"
#include "audio.h"
#include "input.h"
#include "scene.h"
#include "monster.h"
#include "mainMenu.h"

class Game : public Scene
{
protected:

	char            scr[16];
	char            high_scr[16];
	int				score;
	int             high_score;
	int				intialcoord;
	int				intRandomDragon;    // Score number for when dragon comes
	int				backgroundCounter;  // Counter to know when to change background
	int				natureCounter;		// Counter to know which nature_Bg to change too
	int				bgCounterForScore;  // Counter to make sure to only change when score is 10/20/30/ etc
	bool			touched;			// variable to see if the user has touched the screen to play
	bool			lose;
	bool			dragon;				// Dragon for the charge
	bool			scoreBoardActive;   // Check to see if the scoreboard is on the screen
	bool			if_initial_game_start; // Check to see if game already ran


	//	int				heroMoveTimer;		// Time for hero to move
	//	int				MonsterMoveTimer;   // Timer to make monsters move at a certain time
	//  bool			running;			// boolean variable to see if the game is currently running

	// ===================================== UI Components =========================================
	CSprite*		background;
	CSprite*		background2;
	CSprite*		ground_floor;
	CSprite*		nature_bg;
	CSprite*		nature_bg2;

	// Score label
	CLabel*			scoreLabelText;
	CLabel*         scoreLabel;

	// Hero
	Hero*			hero1;

	// Buttons
	CSprite*		ssButton;
	CSprite*		staffButton;
	CSprite*		bowButton;

	// White and Black BG
	CSprite*		blackBG;
	CSprite*		whiteBG;
	
	// Backgrounds/Nature of game
	std::vector<CIw2DImage*> backgrounds;
	std::vector<CIw2DImage*> nature;

	// Buttons BG
	CSprite*		ssBG;
	CSprite*		staffBG;
	CSprite*		bowBG;

	// Fade BG buttons
	CSprite*		ssFadeBG;
	CSprite*		staffFadeBG;
	CSprite*		bowFadeBG;

	// Scoreboard
	CSprite*		endground;           // End of game bg
	CSprite*		replayButton;
	CSprite*		backToMenuButton;
	//CSprite*		trophiesButton;
	//CSprite*		shareButton;
	CLabel*			endScoreLabel;
	CLabel*         highScoreLabel;
	CLabel*			highScoreTxtLabel;
	CSprite*		scoreBoardBG;
	CSprite*		adBG;

	// Monster that collided with hero
	//Used to be called if_collided
	Monster*		collided_monsters;

private:

public:

	//Constructors and Destructor
	Game();
	~Game();

	//Initializes the game
	void            Init();

	// Update the game
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the game
	void            Render();

	// When the game starts and transitions from Main Menu to the game
	void			start();

	// When the game goes from lose state to back to the game
	void			restartGame();

	//Handles the pausing/resuming of the game
	//TODO
	void            pauseGame();
	void            resumeGame();

	//Dealing with score
	void			updateScore();
	void            updateHighScore();

	//Changing background relative to score
	void			createBackgrounds();
	void			changeBackgrounds();
	//Changing nature
	void			createNature();
	void			changeNature();


	// Removing all sprites to reset game.
	void			scoreBoard(); // End of game scores with restart and menu

	//Transition to different scenes/states
	void			toMainMenu();
	static void		toScoreBoard(CTween* pTween);

	// Dealing with the Hero or Monsters
	void			collision_Hero_Monsters();	// Check if collided with any monsters
	void			hero_deathAnimation(); // Death of hero
	static void 	normalHero(Timer* timer, void* userData);
	static void 	deadEnemy(Timer* timer, void* userData);



	//UNUSED
	//	static void		toDeadFlash(CTween* pTween); // to deadFlash
	//	void			deadFlash(); // Fade from black to regualr screen
	//  void			fadeToBlack();
	//  void			removeHero();
	// Tweener to change BG buttons to idle once completed fading
	//	static void		toChangeBGButtons(CTween* pTween);
	// Change background buttons to idle state
	//	void			changeBGButtons();
	//  void            switchToScene(const char* scene_name);

};

#endif  // __GAME_H__


