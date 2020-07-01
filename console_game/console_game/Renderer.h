#pragma once
#include <array>
#include <Windows.h>

typedef std::array<std::array<char, 72>, 282> Field_type ;

class Renderer
{
private:
	Field_type m_field;
	Field_type m_prev_field;
	HANDLE HOUT;// = GetStdHandle(STD_OUTPUT_HANDLE);
public:

private:
	void set_cursor_position(int x, int y) const;
	void cls() const;
	void draw_thread();
	void full_screen();

public:
	void set_field(const Field_type field);
	void draw(bool big_change = false);

	Renderer(bool set_full_screen = true);
	virtual ~Renderer();

};

