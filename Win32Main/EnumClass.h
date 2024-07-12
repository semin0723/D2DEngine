#pragma once

enum class Object_Layer {
	Default,
	Background,
	Player,
	Monster,
	Effect,

	UI = 31,
	End = 32,
};

enum class Button_State {
	Normal,
	Hover,
	Pressed,
	Released,
	Clicked,

};

enum class Tile_State {
	Default,
	Road,
	Empty,
	Tower,

};

enum class Tower_Type {
	Default,
	Tower1_1,
	Tower1_2,
	Tower1_3,

};

enum class Money_Type {
	Default,
	Credit,
	Special,

};