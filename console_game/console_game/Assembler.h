#pragma once
#include "IAssembler.h"
#include "Renderer.h"


class Assembler : public IAssembler
{
private:
	Field m_Field;
	Field m_Piority;
public:
	Assembler();
	virtual ~Assembler();

	void add(Frame& frame, const Position& pos, const Pixel& priority) override;
	void view_field();
	void view_priority();
private:

};

