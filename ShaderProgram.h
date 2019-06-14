#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <unordered_map>
#include <vector>
#include <string>

#include "common.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:

  ShaderProgram() : shaderProgram(-1) {};

  ShaderProgram(const std::unordered_map<GLenum, std::string> &inputShaders);

  virtual ~ShaderProgram() {};

  void Release(); //actual destructor

  virtual void StartUseShader() const;

  virtual void StopUseShader() const;

  GLuint GetProgram() const { return shaderProgram; }

  bool reLink();

  void SetUniform(const std::string &location, const glm::mat4 &value) const;

  void SetUniform(const std::string &location, float value) const;

  void SetUniform(const std::string &location, double value) const;

  void SetUniform(const std::string &location, int value) const;

  void SetUniform(const std::string &location, unsigned int value) const;

  void SetUniform(const std::string &location, const glm::vec4 &value) const;

  void SetUniform(const std::string &location, const glm::vec3 &value) const;

  void SetUniform(const std::string &location, const glm::vec2 &value) const;

private:
  static GLuint LoadShaderObject(GLenum type, const std::string &filename);

  GLuint shaderProgram;
  std::unordered_map<GLenum, GLuint> shaderObjects;
  std::vector <GLenum> nameShader = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER, 
    GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_COMPUTE_SHADER};
};


#endif