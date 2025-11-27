#include "AnimationManager.h"

SAnimationManager::~SAnimationManager()
{
	// Clean up allocated animations
	for(auto& pair : m_animations)
	{
		delete pair.second;
	}
	m_animations.clear();
}

SAnimationManager& SAnimationManager::Get()
{
	// Singleton instance
	static SAnimationManager instance;
	return instance;
}

void SAnimationManager::AddAnimation(const std::string& _animName, const Animation& _anim)
{
	Get().m_animations[_animName] = new Animation(_anim);
}

void SAnimationManager::RemoveAnimation(const std::string& _animName)
{
	auto it = Get().m_animations.find(_animName);
	if (it != Get().m_animations.end())
	{
		delete it->second;
		Get().m_animations.erase(it);
	}
}

Animation* SAnimationManager::GetAnimation(const std::string& _animName)
{
	auto it = Get().m_animations.find(_animName);
	if (it != Get().m_animations.end())
	{
		return it->second;
	}
	return nullptr;
}

void SAnimationManager::StartAnimation(const std::string& _animName)
{
	Animation* anim = GetAnimation(_animName);
	if (anim)
	{
		anim->SetInReverse(false);
		anim->Start(Get().m_clock.getElapsedTime().asSeconds());
	}
}

void SAnimationManager::StartAnimationInReverse(const std::string& _animName)
{
	Animation* anim = GetAnimation(_animName);
	if (anim)
	{
		anim->SetInReverse(true);
		anim->Start(Get().m_clock.getElapsedTime().asSeconds());
	}
}

void SAnimationManager::StopAnimation(const std::string& _animName)
{
	Animation* anim = GetAnimation(_animName);
	if (anim)
	{
		anim->Stop();
	}
}

sf::Texture& SAnimationManager::GetCurrentFrame(const std::string& _animName)
{
	Animation* anim = GetAnimation(_animName);
	if (anim)
	{
		return anim->GetCurrentFrame(Get().m_clock.getElapsedTime().asSeconds());
	}
	throw std::runtime_error("Animation not found: " + _animName);
}

bool SAnimationManager::IsAnimationFinished(const std::string& _animName)
{
	Animation* anim = GetAnimation(_animName);
	if (anim)
	{
		return anim->IsFinished();
	}
	throw std::runtime_error("Animation not found: " + _animName);
}

bool SAnimationManager::HasAnimationStarted(const std::string& _animName)
{
	Animation* anim = GetAnimation(_animName);
	if (anim)
	{
		return anim->hasStarted();
	}
	throw std::runtime_error("Animation not found: " + _animName);
}