#include "dot/Animation.hpp"

using dot::Animation;
using dot::FrameData;
using dot::AnimationAction;

Animation::Animation()
	: m_frames(0),
	m_currentFrameIndex(0),
	m_currentFrameTime(0.f),
	m_releaseFirstFrame(true),
	m_looped(true)
{

}

void Animation::addFrame(unsigned textureID, int x, int y, int width, int height, float frameTime)
{
	FrameData data;
	data.id = textureID;
	data.x = x;
	data.y = y;
	data.width = width;
	data.height = height;
	data.displayTimeSeconds = frameTime;
	m_frames.push_back(data);

}

const FrameData* Animation::getCurrentFrame() const
{
	if (m_frames.size() > 0)
	{
		return &m_frames[m_currentFrameIndex];
	}
	return nullptr;
}

bool Animation::updateFrame(float deltaTime)
{
	if (m_releaseFirstFrame)
	{
		runActionForCurrentFrame();
		m_releaseFirstFrame = false;
		return true;
	}
	if (m_frames.size() > 1 && (m_looped || m_currentFrameIndex < m_frames.size()-1))
	{
		m_currentFrameTime += deltaTime;
		if (m_currentFrameTime >= m_frames[m_currentFrameIndex].displayTimeSeconds)
		{
			m_currentFrameTime = 0.f;
			incrementFrame();
			runActionForCurrentFrame();
			return true;
		}
	}
	return false;
}

void Animation::setLooped(bool looped)
{
	m_looped = looped;
}

void Animation::incrementFrame()
{
	m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames.size();
}

void Animation::reset()
{
	m_currentFrameIndex = 0;
	m_currentFrameTime = 0.f;
	m_releaseFirstFrame = true;
}

void Animation::addFrameAction(unsigned frame, AnimationAction action)
{
	if(frame < m_frames.size())
	{
		auto actionKey = m_actions.find(frame);
		if (actionKey == m_actions.end())
		{
			m_framesWithActions.setBit(frame);
			m_actions.insert(std::make_pair(frame, std::vector<AnimationAction>{action}));
		}
		else
		{
			actionKey->second.emplace_back(action);
		}
	}
}

void Animation::runActionForCurrentFrame()
{
	if (m_actions.size() > 0)
	{
		if (m_framesWithActions.getBit(m_currentFrameIndex))
		{
			auto actionsToRun = m_actions.at(m_currentFrameIndex);
			for (auto f : actionsToRun)
			{
				f();
			}
		}
	}
}