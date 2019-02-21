#include "FlowForce.h"

Vector2 FlowForce::get_force(AutonomousAgent* agent) const
{
		if (m_flowfield == nullptr)
			return{ 0,0 };
		// find cell we're in
		int ix = int(agent->get_position().x / m_cellSize);
		int iy = int(agent->get_position().y / m_cellSize);
		// need a 1D index
		int index = iy * m_cols + ix;
		return{ m_flowfield[index].x * agent->GetMaxforce().x,
			m_flowfield[index].y * agent->GetMaxforce().y };
	
};
