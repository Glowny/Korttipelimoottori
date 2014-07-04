#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::_sound = 0;

SoundManager& SoundManager::getSound()
{
	if ( !_sound )
	{
		_sound = new SoundManager();
		_sound->InitialiseSound();
	}
	return *_sound;
}


void SoundManager::InitialiseSound()
{
	selectionClick.loadFromFile("Selection.wav");
	sClick.setBuffer(selectionClick);
	sClick.setVolume(20);

	noticeSound.loadFromFile("NoticePop-up.wav");
	sNotice.setBuffer(noticeSound);
	sNotice.setVolume(20);

	victorySound.loadFromFile("VictorySound.wav");
	sVictory.setBuffer(victorySound);
	sVictory.setVolume(50);

	failSound.loadFromFile("FailSound.wav");
	sFail.setBuffer(failSound);
	sFail.setVolume(50);

	cardPick.loadFromFile("cardPick.wav");
	cPick.setBuffer(cardPick);
	cPick.setVolume(50);

	cardDrop.loadFromFile("cardDrop.wav");
	cDrop.setBuffer(cardDrop);
	cDrop.setVolume(25);
	
}

void SoundManager::playMusic()
{
	backGroundMusic.openFromFile("BackgroundMusic.ogg");
	backGroundMusic.setLoop(true);
	backGroundMusic.setVolume(10);
	backGroundMusic.play();
}

void SoundManager::toggleMuteSounds()
{
	muteSounds = !muteSounds;
	if (muteSounds)
	{
	sNotice.setVolume(0);
	cDrop.setVolume(0);
	cPick.setVolume(0);
	sFail.setVolume(0);
	sClick.setVolume(0);
	sVictory.setVolume(0);
	}
	else
	{
	cDrop.setVolume(20);
	cPick.setVolume(50);
	sFail.setVolume(50);
	sClick.setVolume(20);
	sNotice.setVolume(20);
	sVictory.setVolume(50);
	}
}

void SoundManager::toggleMuteMusic()
{
	muteMusic = !muteMusic;
	if(muteMusic)
		backGroundMusic.setVolume(0);
	else
		backGroundMusic.setVolume(10);
}