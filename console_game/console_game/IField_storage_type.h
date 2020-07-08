#pragma once
#include <array>
#include "Defines.h"

class Frame_type;
class Position;

class IField_storage_type
{
public:
	IField_storage_type() = default;
	virtual ~IField_storage_type() = default;

	virtual void fill(const Frame_type& c)												 = 0;
	virtual void fill(const Frame_type& c, const Position& begin, const Position& end)   = 0;
	virtual unsigned int size() const												     = 0;

	virtual const std::array<Frame_type, FIELD_HEIGHT>& operator[](unsigned int x) const = 0;
	virtual		  std::array<Frame_type, FIELD_HEIGHT>& operator[](unsigned int x)       = 0;
private:

};

