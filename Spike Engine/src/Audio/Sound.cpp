#include "Sound.h"
#include "Math/Math.h"

namespace Spike {

	Sound::Sound(Mix_Chunk* chunk)  /*Always use Spike::AudioManager to load sounds, please don't use this constructor!*/
	{
		m_Chunk = chunk;
	}
	void Sound::Play(bool loop)
	{
		if (m_Chunk != nullptr)
		{
			m_Channel = Mix_PlayChannel(-1, m_Chunk, loop ? -1 : 0);
		}
	}
	void Sound::Loop(int amount)
	{
		if (m_Chunk != nullptr)
		{
			m_Channel = Mix_PlayChannel(-1, m_Chunk, amount);
		}
	}
	void Sound::Stop()
	{
		if (m_Chunk && m_Channel != -1)
		{
			Mix_HaltChannel(m_Channel);
		}
	}
	void Sound::SetVolume(int volume)
	{
		if (m_Chunk)
		{
			m_Volume = (int)Math::Map(Math::Clamp(volume, 0, 128), 0, 100, 0, 128);
			if (!m_Muted)
				Mix_VolumeChunk(m_Chunk, m_Volume);
		}
	}
	void Sound::Mute(bool mute)
	{
		if (m_Chunk)
		{
			if (!mute)
				Unmute();
			else
			{
				if (!m_Muted)
					m_Volume = Mix_VolumeChunk(m_Chunk, 0);
				m_Muted = true;
			}
		}
	}
	void Sound::Unmute()
	{
		if (m_Chunk)
			Mix_VolumeChunk(m_Chunk, m_Volume);
		m_Muted = false;
	}

	void Sound::__UNLOAD()  /*Please never call this method!*/
	{
		Mix_FreeChunk(m_Chunk);
	}
}