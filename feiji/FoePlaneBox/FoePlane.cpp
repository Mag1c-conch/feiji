#include "FoePlane.h"

CFoePlane::CFoePlane():m_x(0),m_y(0),m_blood(0),m_showid(0)
{
}

CFoePlane::~CFoePlane()
{
}

std::random_device CFoePlane::rd;