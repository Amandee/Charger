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

using namespace std;

//#include "game.h"

MainMenu::~MainMenu()
{
}

void MainMenu::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;

    Scene::Update(deltaTime, alphaMul);

    // Detect screen tap
    if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
		g_pInput->Reset();
        //Switch to Menu scene
		Game* game = (Game*)g_pSceneManager->Find("game");
		game->start();
		Audio::PlayMusic("audio/chiptune.wav", true);
		g_pSceneManager->SwitchTo(game);
           
		
    }
}

void MainMenu::Render()
{
    Scene::Render();
}

void MainMenu::Init()
{
    Scene::Init();
	/*
	IwGxInit();

	IwGxClear();

	// Use the built-in font to display a string at coordinate (120, 150)
	IwGxPrintString(120, 150, "Hello, World!");

	// Standard EGL-style flush of drawing to the surface
	IwGxFlush();

	// Standard EGL-style flipping of double-buffers
	IwGxSwapBuffers();

	// Sleep for 0ms to allow the OS to process events etc.
	s3eDeviceYield(0);*/

	
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
    AddChild(background);
	
   /* // Create Start Game button
	float y_pos = (float)IwGxGetScreenHeight() * 0.66f;
    playButton = new CSprite();
    playButton->SetImage(g_pResources->getPlacard());
    playButton->m_X = IwGxGetScreenWidth() / 2.0f;
    playButton->m_Y = y_pos;
    playButton->m_W = playButton->GetImage()->GetWidth();
    playButton->m_H = playButton->GetImage()->GetHeight();
    playButton->m_AnchorX = 0.5f;
    playButton->m_AnchorY = 0.5f;
    playButton->m_ScaleX = 0.5f;
    playButton->m_ScaleY = 0.5f;
    AddChild(playButton);

    // Create Start Game button text
    playText = new CSprite();
    playText->SetImage(g_pResources->getPlayButton());
    playText->m_X = (float)IwGxGetScreenWidth() / 2;
    playText->m_Y = y_pos;
    playText->m_W = playText->GetImage()->GetWidth();
    playText->m_H = playText->GetImage()->GetHeight();
    playText->m_AnchorX = 0.5f;
    playText->m_AnchorY = 0.5f;
	playText->m_ScaleX = 0.5f;
	playText->m_ScaleY = 0.5f;
    AddChild(playText);*/

    // Start menu music
  // Audio::PlayMusic("audio/frontend.mp3");

}

