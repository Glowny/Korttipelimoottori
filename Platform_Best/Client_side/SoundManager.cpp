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

	noticeSound.loadFromFile("NoticePop-up.wav");
	sNotice.setBuffer(noticeSound);

	victorySound.loadFromFile("VictorySound.wav");
	sVictory.setBuffer(victorySound);

	failSound.loadFromFile("FailSound.wav");
	sFail.setBuffer(failSound);

	cardAir.loadFromFile("cardAir.wav");
	cAir.setBuffer(cardAir);
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
}

void SoundManager::toggleMuteMusic()
{
	muteMusic = !muteMusic;
	if(muteMusic)
		backGroundMusic.setVolume(0);
	else
		backGroundMusic.setVolume(10);
}