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
		if(muteSounds)
			sClick.setVolume(0);
		else
			sClick.setVolume(20);
		sClick.play();
	}

	void playVictory()
	{
		sVictory.setVolume(50);
		sVictory.play();
	}
	void playNotice()
	{
		if(muteSounds)
			sNotice.setVolume(0);
		else
			sNotice.setVolume(20);
		sNotice.play();
	}

	void playFail()
	{
		sFail.setVolume(50);
		sFail.play();
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

	sf::Music backGroundMusic;

	bool muteSounds, muteMusic;
};

