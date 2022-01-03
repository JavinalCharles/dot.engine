#pragma once

#include "Sigma/Events/KeyboardInput.hpp"
#include "Sigma/Utilities/WorkingDirectory.hpp"
#include "Sigma/ResourceAllocator.hpp"
#include "Sigma/Window.hpp"

namespace Sigma
{

class EntitySystem;

struct SharedContext
{
	Sigma::KeyboardInput* keyInput;
	Sigma::EntitySystem* entities;
	Sigma::WorkingDirectory* workingDir;
	Sigma::TextureAllocator* textures;

	Sigma::Window* window;
}; // struct SharedContext

}; // namespace Sigma