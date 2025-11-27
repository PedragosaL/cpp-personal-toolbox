#ifndef ANIMATION_MANAGER__H
#define ANIMATION_MANAGER__H

#include <unordered_map>
#include <string>
#include "Animation.h"

/**
* @class SAnimationManager
* 
* @brief Singleton class that manages animations and a clock used for the animation.
*/
class SAnimationManager
{
	std::unordered_map<std::string, Animation*> m_animations; ///< Map of animations
	sf::Clock m_clock; ///< Clock to track time

	/**
	* @brief Private constructor to prohibit intanciate object.
	*/
	SAnimationManager() = default;
public:
	/**
	* @brief Destructor that cleans up allocated animations.
	*/
	~SAnimationManager();

	/**
	* @brief Get the singleton instance of the Animation Manager.
	* 
	* @return Reference to the singleton instance.
	*/
	static SAnimationManager& Get();

	/**
	* @brief Add an animation to the map.
	* 
	* @param _animName Name of the animation.
	* @param _anim Animation object to add.
	*/
	static void AddAnimation(const std::string& _animName, const Animation& _anim);

	/**
	* @brief Remove an animation from the map.
	* 
	* @param _animName Name of the animation to remove.
	*/
	static void RemoveAnimation(const std::string& _animName);

	/**
	* @brief Get a pointer to an animation.
	* 
	* @param _animName Name of the animation to retrieve.
	*/
	static Animation* GetAnimation(const std::string& _animName);

	/**
	* @brief Start an animation.
	* 
	* @param _animName Name of the animation to start.
	*/
	static void StartAnimation(const std::string& _animName);

	/**
	* @brief Start an animation in reverse.
	* 
	* @param _animName Name of the animation to start in reverse.
	*/
	static void StartAnimationInReverse(const std::string& _animName);

	/**
	* @brief Stop an animation.
	* 
	* @param _animName Name of the animation to stop.
	*/
	static void StopAnimation(const std::string& _animName);

	/**
	* @brief Get the current frame texture of an animation.
	* 
	* @param _animName Name of the animation.
	* @return Reference to the current frame texture.
	*/
	static sf::Texture& GetCurrentFrame(const std::string& _animName);

	/**
	* @brief Check if an animation has finished.
	* 
	* @param _animName Name of the animation.
	*/
	static bool IsAnimationFinished(const std::string& _animName);

	/**
	* @brief Check if an animation has started.
	* 
	* @param _animName Name of the animation.
	*/
	static bool HasAnimationStarted(const std::string& _animName);
};

// Macro definitions for easier access to Animation Manager functions
#define ADD_ANIM(name, anim) SAnimationManager::AddAnimation(name, anim)
#define REMOVE_ANIM(name) SAnimationManager::RemoveAnimation(name)
#define GET_ANIM(name) SAnimationManager::GetAnimation(name)
#define START_ANIM(name) SAnimationManager::StartAnimation(name)
#define START_ANIM_REVERSE(name) SAnimationManager::StartAnimationInReverse(name)
#define STOP_ANIM(name) SAnimationManager::StopAnimation(name)
#define GET_ANIM_FRAME(name) SAnimationManager::GetCurrentFrame(name)
#define IS_ANIM_FINISHED(name) SAnimationManager::IsAnimationFinished(name)
#define HAS_ANIM_STARTED(name) SAnimationManager::HasAnimationStarted(name)

#endif // !ANIMATION_MANAGER__H

