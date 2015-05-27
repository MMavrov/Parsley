#include"AudioManager.h"

AudioManager::AudioManager()
{
	FMOD::System_Create(&system);
	system->init(100, FMOD_INIT_NORMAL, 0);
}

AudioManager::~AudioManager()
{
	SoundMap::iterator iterator;
	for (iterator = sounds.begin(); iterator != sounds.end(); ++iterator)
	{
		iterator->second->release();
	}
	sounds.clear();

	system->release();
	system = 0;
}

void AudioManager::Update()
{
	system->update();
}

void AudioManager::LoadOrStream(const std::string& path, bool stream)
{
	if(sounds.find(path) != sounds.end()) return;

	FMOD::Sound* sound;
	if (stream)
	{
		system->createStream(path.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
	}
	else
	{
		system->createSound(path.c_str(), FMOD_DEFAULT, 0, &sound);
	}

	sounds.insert(std::make_pair(path, sound));
}

void AudioManager::Load(const std::string& path)
{
	LoadOrStream(path, false);
}

void AudioManager::Stream(const std::string& path)
{
	LoadOrStream(path, true);
}

void AudioManager::Play(const std::string& path)
{
	SoundMap::iterator sound = sounds.find(path);

	if (sound == sounds.end()) return;

	system->playSound(sound->second, 0, false, 0);
}