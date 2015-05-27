#ifndef __AUDIO_MANAGER_CLASS_DEFINED__
#define __AUDIO_MANAGER_CLASS_DEFINED__

#include<string>
#include<map>
#include<fmod.hpp>

//Later if there is time we can map these elements to each effect and search by them
enum FX
{
	EXPLOSION_1,
	EXPLOSION_2,
	EXPLOSION_3,
	BLASTER_1,
	BLASTER_2,
	BLASTER_3
};

typedef std::map<std::string, FMOD::Sound*> SoundMap;

class AudioManager 
{
public:
	AudioManager();
	~AudioManager(); 

	void Update();
	void Load(const std::string&);
	void Stream(const std::string&);
	void Play(const std::string&);

private:
	void LoadOrStream(const std::string&, bool);
	FMOD::System* system;
	SoundMap sounds;
};

#endif