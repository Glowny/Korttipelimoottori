#pragma once

#include "SFML\Audio.hpp"


class SoundManager
{
public:
	SoundManager(const SoundManager&){}
	SoundManager(void){}
	~SoundManager(void){}
	void InitialiseSound();

	void playClick(){sClick.play();}

	void playVictory()
	{
		sVictory.setVolume(50);
		sVictory.play();
	}
	void playNotice(){sNotice.play();}

	void playFail()
	{
		sFail.setVolume(50);
		sFail.play();
	}
	void playMusic();

	void muteSounds();
	void normaliseSounds();
	void setMusicVolume(int volume);
	void setSoundVolume(int volume);

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
};

