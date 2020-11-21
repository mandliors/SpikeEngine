#include "Music.h"
#include "Math/Math.h"

namespace Spike {

	Music::Music(Mix_Music* music)  /*Always use Spike::AudioManager to load musics, please don't use this constructor!*/
	{
		m_Music = music;
	}
	Music::~Music()
	{
		//Mix_FreeMusic(m_Music);
	}
	void Music::Play(bool loop)
	{
		if (m_Music != nullptr)
		{
			Mix_PlayMusic(m_Music, loop ? -1 : 0);
		}
	}
	void Music::SafePlay(bool loop) /*Only plays the music, if no music is played*/
	{
		if (m_Music != nullptr && !Mix_PlayingMusic())
		{
			Mix_PlayMusic(m_Music, loop ? -1 : 0);
		}
	}
	void Music::Loop(int amount)
	{
		if (m_Music != nullptr)
		{
			Mix_PlayMusic(m_Music, amount);
		}
	}
	void Music::Pause()  /*Pauses the music that is currently being played*/
	{
		Mix_PauseMusic();
	}
	void Music::Resume()  /*Resumes the music that is currently being played*/
	{
		Mix_ResumeMusic();
	}
	void Music::Stop()  /*Stops the music that is currently being played*/
	{
		Mix_HaltMusic();
	}
	void Music::SetVolume(int volume)
	{
		if (m_Music)
		{
			m_Volume = (int)Math::Map(Math::Clamp(volume, 0, 128), 0, 128, 0, 100);
			if (!m_Muted)
				Mix_VolumeMusic(m_Volume);
		}
	}
	void Music::Mute(bool mute)
	{
		if (m_Music)
		{
			if (!mute)
				Unmute();
			else
			{
				if (!m_Muted)
					m_Volume = Mix_VolumeMusic(0);
				m_Muted = true;
			}
		}
	}
	void Music::Unmute()
	{
		if (m_Music)
			Mix_VolumeMusic(m_Volume);
		m_Muted = false;
	}

	void Music::__UNLOAD()  /*Please never call this method!*/
	{
		Mix_FreeMusic(m_Music);
	}
}