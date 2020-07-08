#include "IAssembler.h"

IAssembler* IAssembler::m_Instance = nullptr;

IAssembler* IAssembler::instance()
{
    if (m_Instance == nullptr)
        m_Instance = new IAssembler;

    return m_Instance;
}
