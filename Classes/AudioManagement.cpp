#include "AudioManagement.h"

AudioMM* AudioMM::inst = nullptr;

void AudioMM::checkString(string _name, int _type)
{
	switch (_type)
	{
	case AudioType::BGM:
		for (int i = 0; i < 100; i ++)
		{
			if (_name == bgm_name[i])
			{
				if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
				{
					SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				}

				SimpleAudioEngine::getInstance()->playBackgroundMusic(bgm_path[i], true);
			}
		}
		break;
	case AudioType::EFFECT:
		for (int i = 0; i < 100; i++)
		{
			if (_name == effect_name[i])
			{
				SimpleAudioEngine::getInstance()->playEffect(effect_path[i]);
			}
		}
		break;
    	default:
		log("unknown audio run");
		break;
	}
}

void AudioMM::runBGM(string _name)
{
	if (getBGMEnabled())
	{
		checkString(_name, AudioType::BGM);
	}
	else
	{
		log("bgm is not enabled!");
	}
}

void AudioMM::runEffect(string _name)
{
	if (getEffectEnabled())
	{
		checkString(_name, AudioType::EFFECT);
	}
	else
	{
		log("effect is not enabled!");
	}
}

void AudioMM::changeBGMState()
{
	isBGMEnabled ? isBGMEnabled = false : isBGMEnabled = true;

	if (isBGMEnabled == false)
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

void AudioMM::changeEffectState()
{
	isEffectEnabled ? isEffectEnabled = false : isEffectEnabled = true;

	if (isEffectEnabled == false)
	{
		SimpleAudioEngine::getInstance()->pauseAllEffects();
	}
}

bool AudioMM::getBGMEnabled()
{
	if (isBGMEnabled)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AudioMM::getEffectEnabled()
{
	if (isEffectEnabled)
	{
		return true;
	}
	else
	{
		return false;
	}
}
