#ifndef ANIMATION__H
#define ANIMATION__H

#include <vector>
#include "SFML/Graphics.hpp"

/**
* @class Animation
* 
* @brief Class representing an animation with frames.
*/
class Animation
{
	float m_startTime; ///< The time when the animation started
	float m_maxDuration; ///< The total duration of the animation
	std::vector<sf::Texture*> m_frames; ///< The frames of the animation
	bool m_bLoop; ///< Flag for looping the animation
	bool m_bFinished = false; ///< Flag for finished animation, default to false
	bool m_bReversed = false; ///< Flag for reversed animation, default to false

public:
	/**
	* @brief Constructor for the Animation class.
	* 
	* @param _maxDuration The total duration of the animation.
	* @param _animationLoop Flag indicating if the animation should loop.
	*/
	Animation(float _maxDuration, bool _animationLoop = false) 
		: m_maxDuration(_maxDuration), m_startTime(-1.f), m_bLoop(_animationLoop)
	{}

	/**
	* @brief Add a frame to the animation.
	* 
	* @param _frame Pointer to the texture frame to add.
	*/
	inline void AddFrame(sf::Texture* _frame) { m_frames.push_back(_frame); }

	/**
	* @brief Check if the animation has started.
	* 
	* @return True if the animation has started, false otherwise.
	*/
	inline bool hasStarted() const { return m_startTime >= 0.f; }

	/**
	* @brief Check if the animation has finished.
	* 
	* @return True if the animation has finished, false otherwise.
	*/
	inline bool IsFinished() const { return m_bFinished; }

	/**
	* @brief Set if the animation should loop or not.
	* 
	* @param _loop True to enable looping, false to disable.
	*/
	inline void SetLooping(bool _loop) { m_bLoop = _loop; }

	/**
	* @brief Set if the animation should play in reverse.
	* 
	* @param _reverse True to play in reverse, false otherwise.
	*/
	inline void SetInReverse(bool _reverse) { m_bReversed = _reverse; }

	/**
	* @brief Start the animation at the given current time.
	*
	* @param _currentTime The current time to start the animation.
	*/
	void Start(float _currentTime)
	{
		m_startTime = _currentTime;
		m_bFinished = false;
	}

	/**
	* @brief Stop the animation.
	*/
	void Stop()
	{
		m_startTime = -1.f;
		m_bFinished = true;
	}

	/**
	* @brief Get the current frame of the animation based on the current time.
	* 
	* @param _currentTime The current time to determine the frame.
	* @return Reference to the current frame texture.
	* 
	* @note If the animation haven't started, the first frame is returned.
	* @note If the animation is finished, the last frame is returned.
	* @note If there are no frames, an exception is thrown.
	*/
	sf::Texture& GetCurrentFrame(float _currentTime)
	{
		// Ensure there are frames in the animation
		if( m_frames.empty())
		{
			throw std::runtime_error("No frames in animation");
		}

		// If the animation has started
		if (m_startTime > 0)
		{
			// Calculate elapsed time since the animation started
			float elapsedTime = _currentTime - m_startTime;
			// Determine the current frame based on elapsed time
			int temp = m_frames.size() * elapsedTime / m_maxDuration;

			// If the current frame is within the range of frames
			if (temp < m_frames.size())
			{
				// Return the appropriate frame based on whether the animation is reversed
				return (m_bReversed ? *m_frames[m_frames.size() - temp] : *m_frames[temp]);
			}
			else
			{
				// If the animation has reached the end, if the animation is looping
				if (m_bLoop)
				{
					// Restart the animation
					m_startTime = _currentTime;
					//  Return the first or the last frame based on whether the animation is reversed
					return (m_bReversed ? *m_frames.back() : *m_frames.front());
				}
				// Else, Mark the animation as finished and return the last frame
				Stop();
				return *m_frames.back();
			}
		}
		return *m_frames.front();
	}

};

#endif // !ANIMATION__H

