#pragma once

#include "dot/Events/KeyboardInput.hpp"
#include "dot/Utilities/WorkingDirectory.hpp"
#include "dot/ResourceAllocator.hpp"
#include "dot/Window.hpp"
#include "dot/Events/MouseInput.hpp"

namespace dot
{

class EntitySystem;

struct SharedContext
{
	dot::KeyboardInput* keyInput;
	dot::MouseInput* mouseInput;
	dot::EntitySystem* entities;
	dot::WorkingDirectory* workingDir;
	dot::TextureAllocator* textures;

	dot::Window* window;
}; // struct SharedContext

}; // namespace dot