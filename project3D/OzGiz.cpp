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
		glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(projectionView));

		if (sm_singleton->m_lineCount > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, sm_singleton->m_lineVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sm_singleton->m_lineCount * sizeof(GizmoLine), sm_singleton->m_lines);

			glBindVertexArray(sm_singleton->m_lineVAO);
			glDrawArrays(GL_LINES, 0, sm_singleton->m_lineCount * 2);
		}

		if (sm_singleton->m_triCount > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, sm_singleton->m_triVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sm_singleton->m_triCount * sizeof(GizmoTri), sm_singleton->m_tris);

			glBindVertexArray(sm_singleton->m_triVAO);
			glDrawArrays(GL_TRIANGLES, 0, sm_singleton->m_triCount * 3);
		}

		if (sm_singleton->m_transparentTriCount > 0) {
			// not ideal to store these, but Gizmos must work stand-alone
			GLboolean blendEnabled = glIsEnabled(GL_BLEND);
			GLboolean depthMask = GL_TRUE;
			glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);
			int src, dst;
			glGetIntegerv(GL_BLEND_SRC, &src);
			glGetIntegerv(GL_BLEND_DST, &dst);

			// setup blend states
			if (blendEnabled == GL_FALSE)
				glEnable(GL_BLEND);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);

			glBindBuffer(GL_ARRAY_BUFFER, sm_singleton->m_transparentTriVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sm_singleton->m_transparentTriCount * sizeof(GizmoTri), sm_singleton->m_transparentTris);

			glBindVertexArray(sm_singleton->m_transparentTriVAO);
			glDrawArrays(GL_TRIANGLES, 0, sm_singleton->m_transparentTriCount * 3);

			// reset state
			glDepthMask(depthMask);
			glBlendFunc(src, dst);
			if (blendEnabled == GL_FALSE)
				glDisable(GL_BLEND);
		}

		glUseProgram(shader);
	}
}