#pragma once

#include <vector>
#include <functional>
#include <map>
#include "dot/Utilities/Bitmask.hpp"

namespace dot
{

struct FrameData
{
	unsigned id; // TextureID
	int x;
	int y;
	int width;
	int height;

	float displayTimeSeconds; // How long to display the frame
};

using AnimationAction = std::function<void(void)>;

class Animation
{
public:
	Animation();

	void addFrame(unsigned textureID, int x, int y, int width, int height, float frameTime);

	const FrameData* getCurrentFrame() const;
	bool updateFrame(float deltaTime);
	void reset();

	void addFrameAction(unsigned frame, AnimationAction action);

	void setLooped(bool looped);
	bool isLooped() const;

private:
	void incrementFrame();
	void runActionForCurrentFrame();

	// Stores all frames for our animation
	std::vector<FrameData> m_frames;

	// current frame
	unsigned m_currentFrameIndex;

	float m_currentFrameTime;

	bool m_releaseFirstFrame;
	bool m_looped;

	std::map<int, std::vector<AnimationAction>> m_actions;

	Bitmask m_framesWithActions;
}; // class Animation


}; // namespace dot