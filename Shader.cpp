#include <vector>
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char *vert_path, const char *frag_path)
	: m_vertpath(vert_path), m_fragpath(frag_path)
{
	m_id = load();
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::enable() const
{
	glUseProgram(m_id);
}

void Shader::disable() const
{
	glUseProgram(0);
}

void Shader::setUniform1f(const GLchar *name, const float val)
{
	glUniform1f(getUniformLocation(name), val);
}

void Shader::setUniform1i(const GLchar *name, const int val)
{
	glUniform1i(getUniformLocation(name), val);
}

void Shader::setUniform2f(const GLchar *name, const glm::vec2& val)
{
	glUniform2f(getUniformLocation(name), val.x, val.y);
}

void Shader::setUniform3f(const GLchar *name, const glm::vec3& val)
{
	glUniform3f(getUniformLocation(name), val.x, val.y, val.z);
}

void Shader::setUniform4f(const GLchar *name, const glm::vec4 &val)
{
	float farr[4];
	const float *pSource = (const float *)glm::value_ptr(val);
	for (int i = 0; i < 4; ++i)
		farr[i] = pSource[i];
	glUniform4f(getUniformLocation(name), farr[0], farr[1], farr[2], farr[3]);
}

void Shader::setUniformMat4(const GLchar *name, const glm::mat4& val)
{
	float farr[16] = {0.0};
	const float *pSource = (const float*)glm::value_ptr(val);
	for (int i = 0; i < 16; ++i)
		farr[i] = pSource[i];
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, farr);
}

GLuint Shader::load()
{
	GLint status;
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();

	std::string vert_stdstr = FileUtils::read_file(m_vertpath);
	std::string frag_stdstr = FileUtils::read_file(m_fragpath);

	const char *vert_cstr = vert_stdstr.c_str();
	const char *frag_cstr = frag_stdstr.c_str();

	glShaderSource(vertex_shader, 1, &vert_cstr, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> errmsg(length);
		glGetShaderInfoLog(vertex_shader, length, &length, &errmsg[0]);
		printf("ERROR: Failed to compile vertex shader:\n%s\n", errmsg.data());
		glDeleteShader(vertex_shader);
		return (0);
	}

	glShaderSource(fragment_shader, 1, &frag_cstr, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> errmsg(length);
		glGetShaderInfoLog(fragment_shader, length, &length, &errmsg[0]);
		printf("ERROR: Failed to compile fragment shader:\n%s\n", errmsg.data());
		glDeleteShader(fragment_shader);
		return (0);
	}

	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);

	return program;
}

/**
 * TODO
 * @param name TODO
 * @return TODO
 */
GLint Shader::getUniformLocation(const GLchar *name)
{
	return (glGetUniformLocation(m_id, name));
}
