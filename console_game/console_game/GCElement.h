#pragma once
class GCElement
{
public:
    GCElement() = default;
    virtual    ~GCElement() = default;

public:
    void* operator new(size_t);
    void        operator delete(void*);
};
