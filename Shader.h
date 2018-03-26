#ifndef SHADER_H_
#define SHADER_H_

#include "FileUtils.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const char *vert_path, const char *frag_path);
	~Shader();

	void enable() const;
	void disable() const;

	void setUniform1f(const GLchar *name, const float val);
	void setUniform1i(const GLchar *name, const int val);
	void setUniform2f(const GLchar *name, const glm::vec2& val);
	void setUniform3f(const GLchar *name, const glm::vec3& val);
	void setUniform4f(const GLchar *name, const glm::vec4 &val);
	void setUniformMat4(const GLchar *name, const glm::mat4& val);

	inline GLuint get_id() const { return m_id; }

private:
	GLuint load();
	GLint getUniformLocation(const GLchar *name);

	GLuint m_id;
	const char *m_vertpath;
	const char *m_fragpath;

};


#endif // SHADER_H_
