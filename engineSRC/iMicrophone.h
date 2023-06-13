#pragma once
#include "allStaticLib.h"
#include "zelpMath.h"

//alpha verze
struct IMicrophone {
private:
	ALLEGRO_AUDIO_DEPTH audio_depth;
	ALLEGRO_AUDIO_RECORDER* recorder;
	ALLEGRO_EVENT_QUEUE* event_queue;
	int16_t min_sample_val;
	int16_t max_sample_val;
	int sample_range;
	unsigned int frequency;
	unsigned int samples_per_fragment;
	unsigned int playback_fragment_count;
	unsigned int playback_samples_per_fragment;
	int patterned;		//vzorkovani
	int prev;
	int offsetY;
	int gain;			//hlasitost
	int sample_count;
public:
	int16_t sample_center = { 0 };
	int16_t* input = {NULL};
public:
	IMicrophone(ALLEGRO_AUDIO_DEPTH audio_depth = ALLEGRO_AUDIO_DEPTH_INT16);
	~IMicrophone();
	bool init();
	void update();
};
