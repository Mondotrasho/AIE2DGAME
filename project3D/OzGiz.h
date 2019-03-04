#pragma once
#include "../MathsLib/MathsLib/Vector4.h"
#include "../MathsLib/MathsLib/Matrix4.h"
#include "gl_core_4_4.h"
#include <cstdio>

class Vector3;

struct GizmoVertex {
	Vector4 pos;
	Vector4 colour;
};

struct GizmoLine {
	GizmoVertex start;
	GizmoVertex end;
};

//my gizmos
class OzGiz
{
public:
	int m_maxLines;
	int m_lineCount;
	GizmoLine* m_lines;

	unsigned int	m_shader;

	GLuint m_lineVBO;
	GLuint m_lineVAO;

	OzGiz(unsigned int maxLines, unsigned int maxTris,
		unsigned int max2DLines, unsigned int max2DTris)
		: m_maxLines(maxLines),
		m_lineCount(0),
		m_lines(new GizmoLine[maxLines]) {

		// create shaders
		const char* vsSource = "#version 150\n \
					 in vec4 Position; \
					 in vec4 Colour; \
					 out vec4 vColour; \
					 uniform mat4 ProjectionView; \
					 void main() { vColour = Colour; gl_Position = ProjectionView * Position; }";

		const char* fsSource = "#version 150\n \
					 in vec4 vColour; \
                     out vec4 FragColor; \
					 void main()	{ FragColor = vColour; }";


		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vs, 1, (const char**)&vsSource, 0);
		glCompileShader(vs);

		glShaderSource(fs, 1, (const char**)&fsSource, 0);
		glCompileShader(fs);

		m_shader = glCreateProgram();
		glAttachShader(m_shader, vs);
		glAttachShader(m_shader, fs);
		glBindAttribLocation(m_shader, 0, "Position");
		glBindAttribLocation(m_shader, 1, "Colour");
		glLinkProgram(m_shader);

		int success = GL_FALSE;
		glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
		if (success == GL_FALSE) {
			int infoLogLength = 0;
			glGetProgramiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* infoLog = new char[infoLogLength + 1];

			glGetProgramInfoLog(m_shader, infoLogLength, 0, infoLog);
			printf("Error: Failed to link Gizmo shader program!\n%s\n", infoLog);
			delete[] infoLog;
		}

		glDeleteShader(vs);
		glDeleteShader(fs);

		// create VBOs
		glGenBuffers(1, &m_lineVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_lineVBO);
		glBufferData(GL_ARRAY_BUFFER, m_maxLines * sizeof(GizmoLine), m_lines, GL_DYNAMIC_DRAW);

		glGenVertexArrays(1, &m_lineVAO);
		glBindVertexArray(m_lineVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_lineVBO);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), (void*)16);

	}

	~OzGiz();
	void draw(Matrix4 mat);
	static void addLine(Vector3& start, Vector3& end,Vector4 colour, float thickness = 1);
	static void clear() {
		sm_singleton->m_lineCount = 0;
	}

	static void OzGiz::create(unsigned int maxLines, unsigned int maxTris,
		unsigned int max2DLines, unsigned int max2DTris) {
		if (sm_singleton == nullptr)
			sm_singleton = new OzGiz(maxLines, maxTris, max2DLines, max2DTris);
	}
	static OzGiz*	sm_singleton;
};

