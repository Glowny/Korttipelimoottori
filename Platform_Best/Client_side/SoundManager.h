#pragma once

#include "SFML\Audio.hpp"


class SoundManager
{
public:
	SoundManager(const SoundManager&){muteSounds = false; muteMusic = false;}
	SoundManager(void){muteSounds = false; muteMusic = false;}
	~SoundManager(void){}
	void InitialiseSound();

	void playClick()
	{
		sClick.play();
	}

	void playVictory()
	{
		sVictory.play();
	}
	void playNotice()
	{
		sNotice.play();
	}

	void playFail()
	{
		sFail.play();
	}
	void playCardPick()
	{
		cPick.play();	
	}
	void playCardDrop()
	{
		cDrop.play();
	}

	void playMusic();

	void toggleMuteSounds();
	void toggleMuteMusic();

	static SoundManager& getSound();

private:


	static SoundManager* _sound;

	sf::SoundBuffer selectionClick;
	sf::Sound sClick;
	sf::SoundBuffer victorySound;
	sf::Sound sVictory;
	sf::SoundBuffer noticeSound;
	sf::Sound sNotice;
	sf::SoundBuffer failSound;
	sf::Sound sFail;
	sf::SoundBuffer cardPick;
	sf::Sound cPick;
	sf::SoundBuffer cardDrop;
	sf::Sound cDrop;
	sf::Music backGroundMusic;
	
	
	bool muteSounds, muteMusic;
};

