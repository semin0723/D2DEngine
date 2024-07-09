#pragma once

enum class Object_Layer {
	Default,
	Background,
	Player,
	Monster,
	Effect,

	End = 32,
};

enum class Button_State {
	Normal,
	Hover,
	Pressed,
	Released,
	Clicked,

};