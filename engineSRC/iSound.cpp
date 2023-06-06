#include "iSound.h"

unsigned int ISound::reserveSample = 10;

ISound::ISound() {
	al_reserve_samples(ISound::reserveSample);
}

ISound::~ISound() {
	al_destroy_sample_instance(this->instance);
	al_destroy_sample(this->sample);
}

bool ISound::loadSound(std::string path) {
	this->sample = al_load_sample(path.c_str());
	if (this->sample) {
		this->instance = al_create_sample_instance(this->sample);
		al_attach_sample_instance_to_mixer(this->instance, al_get_default_mixer());
	}
	else {std::cout << "Error load sample" << path << std::endl; return false;}
	return true;
}

void ISound::setInstancePlaymode(ALLEGRO_PLAYMODE playmode) {
	al_set_sample_instance_playmode(this->instance, playmode);
}

void ISound::playSample() {
	al_play_sample(this->sample, ISound::volume, 0.0f, ISound::speed, ALLEGRO_PLAYMODE_ONCE, 0);
}

void ISound::playInstance() {
	al_play_sample_instance(this->instance);
}

void ISound::stop() {
	al_stop_sample_instance(this->instance);
}

void ISound::changeVolume(float volume) {
	al_set_sample_instance_gain(this->instance, this->volume);
}

void ISound::changeSpeed(float speed) {
	al_set_sample_instance_speed(this->instance, this->speed);
}
