#pragma once
#include "allStaticLib.h"

struct ISound {
private:
	static unsigned int reserveSample;
public:
	float volume = {1.0f};
	float speed = {1.0f};
	ALLEGRO_SAMPLE* sample;
	ALLEGRO_SAMPLE_INSTANCE* instance;
public:
	ISound();
	~ISound();
	bool loadSound(std::string path);
	void setInstancePlaymode(ALLEGRO_PLAYMODE playmode);
	void playSample();
	void playInstance();
	void stop();
	void changeVolume(float volume);
	void changeSpeed(float speed);
};
