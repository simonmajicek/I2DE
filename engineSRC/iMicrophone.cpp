#include "iMicrophone.h"

IMicrophone::IMicrophone(ALLEGRO_AUDIO_DEPTH audio_depth) {
	this->audio_depth = audio_depth;
	this->min_sample_val = 32768;	//0x8000
	this->max_sample_val = 32767;	//0x7fff
	this->sample_range = 65535;		//0xffff
	this->frequency = 22050;		//44100 for HQ recording
	this->samples_per_fragment = 320 * 4;
	this->playback_fragment_count = 4;
	this->playback_samples_per_fragment = 4096;
	this->patterned = 512;		//320
	this->prev = 0;
	this->offsetY = 200;
	this->gain = 0;

	this->event_queue = al_create_event_queue();
}

IMicrophone::~IMicrophone() {
	al_destroy_audio_recorder(this->recorder);
}

bool IMicrophone::init() {
	this->recorder = al_create_audio_recorder(1000, this->samples_per_fragment, this->frequency, audio_depth, ALLEGRO_CHANNEL_CONF_1);
	if (!this->recorder) { 
		std::cout << "Unable to create audio recorder" << std::endl; 
		return false; 
	}
	al_register_event_source(this->event_queue, al_get_audio_recorder_event_source(this->recorder));
	al_start_audio_recorder(this->recorder);
	return true;
}

void IMicrophone::update() {
	ALLEGRO_EVENT events;

	al_wait_for_event(this->event_queue, &events);
	//while (al_get_next_event(this->event_queue, &events)) {
		if (events.type == ALLEGRO_EVENT_AUDIO_RECORDER_FRAGMENT) {
			ALLEGRO_AUDIO_RECORDER_EVENT* re = al_get_audio_recorder_event(&events);
			input = (int16_t*)re->buffer;
			this->sample_count = re->samples;
			const int R = sample_count / this->patterned;

			//calc volume
			for (int i = 0; i < sample_count; ++i) {
				if (this->gain < abs(input[i] - sample_center))
					this->gain = abs(input[i] - sample_center);
			}

			//const int R = sample_count / this->patterned;

			offsetY = 0;
			//pathetic visualisation
			for (int i = 0; i < this->patterned; ++i) {
				int j, c = 0;

				/* Take the average of R samples so it fits on the screen */
				for (j = i * R; j < i * R + R && j < sample_count; ++j) {
					c += (input[j] * 3) - sample_center;
				}
				c /= R;

				/* Draws a line from the previous sample point to the next */
				al_draw_line(i - 1, offsetY + 128 + ((prev - min_sample_val) /
					(float)sample_range) * 256 - 128, i, offsetY + 128 +
					((c - min_sample_val) / (float)sample_range) * 256 - 128,
					al_map_rgb(255, 255, 255), 1.2);

				prev = c;
			}



			/* draw volume bar */
			al_draw_filled_rectangle((gain / (float)max_sample_val) * this->patterned, 20,
				0, 30, al_map_rgba(0, 255, 0, 128));

		}
	//}
}
