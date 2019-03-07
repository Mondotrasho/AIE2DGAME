#include "OzGiz.h"
#include "../MathsLib/MathsLib/Vector3.h"


OzGiz::~OzGiz()
{
}

void OzGiz::draw(Matrix4 mat)
{
}

void OzGiz::addLine(Vector3& start, Vector3& end, Vector4 colour, float thickness)
{
	if (sm_singleton != nullptr &&
		sm_singleton->m_lineCount < sm_singleton->m_maxLines) {
		sm_singleton->m_lines[sm_singleton->m_lineCount].start.pos.x = start.x;
		sm_singleton->m_lines[sm_singleton->m_lineCount].start.pos.y = start.y;
		sm_singleton->m_lines[sm_singleton->m_lineCount].start.pos.z = start.z;
		sm_singleton->m_lines[sm_singleton->m_lineCount].start.pos.w = 1;
		sm_singleton->m_lines[sm_singleton->m_lineCount].start.colour.r = colour.r;
		sm_singleton->m_lines[sm_singleton->m_lineCount].start.colour.g = colour.g;
		sm_singleton->m_lines[sm_singleton->m_lineCount].start.colour.b = colour.b;
		sm_singleton->m_lines[sm_singleton->m_lineCount].start.colour.a = colour.a;

		sm_singleton->m_lines[sm_singleton->m_lineCount].end.pos.x = end.x;
		sm_singleton->m_lines[sm_singleton->m_lineCount].end.pos.y = end.y;
		sm_singleton->m_lines[sm_singleton->m_lineCount].end.pos.z = end.z;
		sm_singleton->m_lines[sm_singleton->m_lineCount].end.pos.w = 1;
		sm_singleton->m_lines[sm_singleton->m_lineCount].end.colour.r = colour.r;
		sm_singleton->m_lines[sm_singleton->m_lineCount].end.colour.g = colour.g;
		sm_singleton->m_lines[sm_singleton->m_lineCount].end.colour.b = colour.b;
		sm_singleton->m_lines[sm_singleton->m_lineCount].end.colour.a = colour.a;

		sm_singleton->m_lineCount++;
	}
}
void OzGiz::draw(const Matrix4& projectionView) {
	if (sm_singleton != nullptr &&
		(sm_singleton->m_lineCount > 0)) {
		int shader = 0;
		glGetIntegerv(GL_CURRENT_PROGRAM, &shader);

		glUseProgram(sm_singleton->m_shader);

		unsigned int projectionViewUniform = glGetUniformLocation(sm_singleton->m_shader, "ProjectionView");
		
		GLfloat modelviewmatrix[16];
		int f = 0;
		for (int i ; i < 4; i++){
			for (int j = 0; j < 4; ++j)
			{
				modelviewmatrix[f] = projectionView[i][j];
				f++;
			}
			
		
			
		}
		glUniformMatrix4fv(projectionViewUniform, 1, false, modelviewmatrix);

		if (sm_singleton->m_lineCount > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, sm_singleton->m_lineVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sm_singleton->m_lineCount * sizeof(GizmoLine), sm_singleton->m_lines);

			glBindVertexArray(sm_singleton->m_lineVAO);
			glDrawArrays(GL_LINES, 0, sm_singleton->m_lineCount * 2);
		}

		

		glUseProgram(shader);
	}
}