#pragma once
#include <SDL_keycode.h>
#include <SDL_events.h>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include <Vector2Int.h>

enum class KeyCode : uint8_t
{
	None,
	A, B, C, D, E, F, G, H, I, J, K, L, M, 
	N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	N0, N1, N2, N3, N4, N5, N6, N7, N8, N9,
	LeftShift, RightShift
};

enum class MouseButton : uint8_t
{
	None   = 0,
	Left   = 1 << 0, 
	Middle = 1 << 1, 
	Right  = 1 << 2
};

enum class EventType : uint8_t 
{
	None,
	KeyDown, KeyUp,
	MouseDown, MouseUp,
	Quit
};

class Input
{
private:
	KeyCode lastPressedKey = KeyCode::None;
	MouseButton lastPressedMouseButton = MouseButton::None;

	std::unordered_set<KeyCode> pressedKeys;
	uint8_t pressedMouseButton = 0;
	EventType eventType = EventType::None;
	Vector2Int mousePosition;

	static const std::unordered_map<SDL_Keycode, KeyCode> sdlKeysMapping;
	static const std::unordered_map<uint32_t, EventType> sdlEventsMapping;
	static const std::unordered_map<uint8_t, MouseButton> sdlMouseButtonMapping;

public:
	void PollInput(const SDL_Event& event);
	void Cleanup();

	bool IsKeyPressed(KeyCode keyCode) const;
	bool IsKeyDown(KeyCode keyCode) const;
	bool IsKeyUp(KeyCode keyCode) const;
	bool IsMouseButtonPressed(MouseButton mouseButton) const;
	bool IsMouseButtonDown(MouseButton mouseButton) const;
	bool IsMouseButtonUp(MouseButton mouseButton) const;
	Vector2Int GetMousePosition() const;
	EventType GetLastEvent() const;

private:
	void ProcessKeys(const SDL_Event& event);
	void ProcessMouse(const SDL_Event& event);
};
