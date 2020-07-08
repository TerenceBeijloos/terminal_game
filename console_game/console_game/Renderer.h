#pragma once
#include <array>
#include <Windows.h>
#include <thread>

#include "Field.h"

class Renderer
{
private:
	Field m_prev_field;
	HANDLE HOUT;// = GetStdHandle(STD_OUTPUT_HANDLE);
	std::thread m_Draw_thd;
public:

private:
	void set_cursor_position(int x, int y) const;
	void cls() const;
	void draw_thread(const Field& field);
	void full_screen();
	void join();

public:
	void draw(const Field& field, bool big_change = false);

	Renderer(bool set_full_screen = true);
	virtual ~Renderer();

};

