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
	selectionClick.loadFromFile("Selection.wav"); //Ääntä ei voi toistaa, pitää etsiä uusi.
	sClick.setBuffer(selectionClick);

	noticeSound.loadFromFile("NoticePop-up.wav");
	sNotice.setBuffer(noticeSound);

	victorySound.loadFromFile("VictorySound.wav");
	sVictory.setBuffer(victorySound);

	failSound.loadFromFile("FailSound.wav");
	sFail.setBuffer(failSound);
}

void SoundManager::playMusic()
{
	backGroundMusic.openFromFile("BackgroundMusic.ogg");
	backGroundMusic.setLoop(true);
	backGroundMusic.setVolume(10);
	backGroundMusic.play();
}

void SoundManager::muteSounds()
{
	sClick.setVolume(0);
	sNotice.setVolume(0);
	sFail.setVolume(0);
	sVictory.setVolume(0);
	backGroundMusic.setVolume(0);
}
void SoundManager::normaliseSounds()
{
	sClick.setVolume(100);
	sNotice.setVolume(100);
	sFail.setVolume(50);
	sVictory.setVolume(50);
	backGroundMusic.setVolume(10);
}

void SoundManager::setMusicVolume(int volume)
{
	
	
}

void SoundManager::setSoundVolume(int volume)
{
}