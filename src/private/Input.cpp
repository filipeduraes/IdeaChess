#include "Input.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <unordered_map>
#include "Vector2Int.h"
#include <cstdint>
#include <SDL_mouse.h>

const std::unordered_map<SDL_Keycode, KeyCode> Input::sdlKeysMapping =
{
	{ SDLK_a, KeyCode::A }, { SDLK_b, KeyCode::B }, { SDLK_c, KeyCode::C }, { SDLK_d, KeyCode::D },
	{ SDLK_e, KeyCode::E }, { SDLK_f, KeyCode::F }, { SDLK_g, KeyCode::G }, { SDLK_h, KeyCode::H },
	{ SDLK_i, KeyCode::I }, { SDLK_j, KeyCode::J }, { SDLK_k, KeyCode::K }, { SDLK_l, KeyCode::L },
	{ SDLK_m, KeyCode::M }, { SDLK_n, KeyCode::N }, { SDLK_o, KeyCode::O }, { SDLK_p, KeyCode::P },
	{ SDLK_q, KeyCode::Q }, { SDLK_r, KeyCode::R }, { SDLK_s, KeyCode::S }, { SDLK_t, KeyCode::T },
	{ SDLK_u, KeyCode::U }, { SDLK_v, KeyCode::V }, { SDLK_w, KeyCode::W }, { SDLK_x, KeyCode::X },
	{ SDLK_y, KeyCode::Y }, { SDLK_z, KeyCode::Z },
	{ SDLK_0, KeyCode::N0 }, { SDLK_1, KeyCode::N1 }, { SDLK_2, KeyCode::N2 }, { SDLK_3, KeyCode::N3 },
	{ SDLK_4, KeyCode::N4 }, { SDLK_5, KeyCode::N5 }, { SDLK_6, KeyCode::N6 }, { SDLK_7, KeyCode::N7 },
	{ SDLK_8, KeyCode::N8 }, { SDLK_9, KeyCode::N9 },
	{ SDLK_LSHIFT, KeyCode::LeftShift }, { SDLK_RSHIFT, KeyCode::RightShift },
};

const std::unordered_map<uint32_t, EventType> Input::sdlEventsMapping =
{
	{ SDL_KEYDOWN, EventType::KeyDown },
	{ SDL_KEYUP, EventType::KeyUp },
	{ SDL_MOUSEBUTTONDOWN, EventType::MouseDown },
	{ SDL_MOUSEBUTTONUP, EventType::MouseUp },
	{ SDL_QUIT, EventType::Quit },
};

const std::unordered_map<uint8_t, MouseButton> Input::sdlMouseButtonMapping =
{
	{ SDL_BUTTON_LEFT, MouseButton::Left },
	{ SDL_BUTTON_MIDDLE, MouseButton::Middle },
	{ SDL_BUTTON_RIGHT, MouseButton::Right },
};

void Input::PollInput(const SDL_Event& event)
{
	eventType = EventType::None;

	if (sdlEventsMapping.contains(event.type))
	{
		eventType = sdlEventsMapping.at(event.type);
	}

	ProcessKeys(event);
	ProcessMouse(event);
}

void Input::Cleanup()
{
	lastPressedKey = KeyCode::None;
	lastPressedMouseButton = MouseButton::None;
}

bool Input::IsKeyPressed(KeyCode keyCode) const
{
	return pressedKeys.contains(keyCode);
}

bool Input::IsKeyDown(KeyCode keyCode) const
{
	return eventType == EventType::KeyDown && lastPressedKey == keyCode;
}

bool Input::IsKeyUp(KeyCode keyCode) const
{
	return eventType == EventType::KeyUp && lastPressedKey == keyCode;
}

bool Input::IsMouseButtonPressed(MouseButton mouseButton) const
{
	return (pressedMouseButton & static_cast<uint8_t>(mouseButton)) != 0;
}

bool Input::IsMouseButtonDown(MouseButton mouseButton) const
{
	return eventType == EventType::MouseDown && lastPressedMouseButton == mouseButton;
}

bool Input::IsMouseButtonUp(MouseButton mouseButton) const
{
	return eventType == EventType::MouseUp && lastPressedMouseButton == mouseButton;
}

Vector2Int Input::GetMousePosition() const
{
	return mousePosition;
}

EventType Input::GetLastEvent() const
{
	return eventType;
}

void Input::ProcessKeys(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
		{
			if (sdlKeysMapping.contains(event.key.keysym.sym))
			{
				lastPressedKey = sdlKeysMapping.at(event.key.keysym.sym);
				pressedKeys.insert(lastPressedKey);
			}
			break;
		}
		case SDL_KEYUP:
		{
			if (sdlKeysMapping.contains(event.key.keysym.sym))
			{
				lastPressedKey = sdlKeysMapping.at(event.key.keysym.sym);
				pressedKeys.erase(sdlKeysMapping.at(event.key.keysym.sym));
			}
			break;
		}
	}
}

void Input::ProcessMouse(const SDL_Event& event)
{
	if (eventType == EventType::MouseDown)
	{
		if (sdlMouseButtonMapping.contains(event.button.button))
		{
			lastPressedMouseButton = sdlMouseButtonMapping.at(event.button.button);
			pressedMouseButton |= static_cast<uint8_t>(lastPressedMouseButton);
		}
	}
	else if (eventType == EventType::MouseUp)
	{
		if (sdlMouseButtonMapping.contains(event.button.button))
		{
			lastPressedMouseButton = sdlMouseButtonMapping.at(event.button.button);
			pressedMouseButton &= ~static_cast<uint8_t>(lastPressedMouseButton);
		}
	}
	else if (event.type == SDL_MOUSEMOTION) 
	{
		mousePosition = Vector2Int(event.motion.x, event.motion.y);
	}
}
