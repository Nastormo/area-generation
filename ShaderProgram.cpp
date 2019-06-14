#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::unordered_map<GLenum, std::string> &inputShaders)
{

  shaderProgram = glCreateProgram();

  for(int i = 0; i < nameShader.size(); ++i) {
    if (inputShaders.find(nameShader[i]) != inputShaders.end())
    {
      shaderObjects[nameShader[i]] = LoadShaderObject(nameShader[i], inputShaders.at(nameShader[i]));
      glAttachShader(shaderProgram, shaderObjects[nameShader[i]]);
    }
  }

  glLinkProgram(shaderProgram);

  GLint linkStatus;

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
  if (linkStatus != GL_TRUE)
  {
    GLchar infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "Shader program linking failed\n" << infoLog << std::endl;
    shaderProgram = 0;
  }

}

void ShaderProgram::Release()
{

  for(int i = 0; i < nameShader.size(); ++i) {
    if (shaderObjects.find(nameShader[i]) != shaderObjects.end())
    {
      glDetachShader(shaderProgram, shaderObjects[nameShader[i]]);
      glDeleteShader(shaderObjects[nameShader[i]]);
    }
  }

  glDeleteProgram(shaderProgram);
}

bool ShaderProgram::reLink()
{
  GLint linked;

  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);

  if (!linked)
  {
    GLint logLength, charsWritten;
    glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &logLength);

    auto log = new char[logLength];
    glGetProgramInfoLog(this->shaderProgram, logLength, &charsWritten, log);

    std::cerr << "Shader program link error: " << std::endl << log << std::endl;

    delete[] log;
    shaderProgram = 0;
    return false;
  }

  return true;
}


GLuint ShaderProgram::LoadShaderObject(GLenum type, const std::string &filename)
{
  std::ifstream fs(filename);

  if (!fs.is_open())
  {
    std::cerr << "ERROR: Could not read shader from " << filename << std::endl;
    return 0;
  }

  std::string shaderText((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

  GLuint newShaderObject = glCreateShader(type);

  const char *shaderSrc = shaderText.c_str();
  glShaderSource(newShaderObject, 1, &shaderSrc, nullptr);

  glCompileShader(newShaderObject);

  GLint compileStatus;
  glGetShaderiv(newShaderObject, GL_COMPILE_STATUS, &compileStatus);

  if (compileStatus != GL_TRUE)
  {
    GLchar infoLog[512];
    glGetShaderInfoLog(newShaderObject, 512, nullptr, infoLog);
    std::cerr << "Shader compilation failed : " << std::endl << infoLog << std::endl;
    return 0;
  }

  return newShaderObject;
}

void ShaderProgram::StartUseShader() const
{
  glUseProgram(shaderProgram);
}

void ShaderProgram::StopUseShader() const
{
  glUseProgram(0);
}

void ShaderProgram::SetUniform(const std::string &location, const glm::mat4 &value) const
{
  GLint uniformLocation = glGetUniformLocation(shaderProgram, location.c_str()); GL_CHECK_ERRORS;
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }

  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value)); GL_CHECK_ERRORS;
}

void ShaderProgram::SetUniform(const std::string &location, int value) const
{
  GLint uniformLocation = glGetUniformLocation(shaderProgram, location.c_str());
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  glUniform1i(uniformLocation, value);
}

void ShaderProgram::SetUniform(const std::string &location, unsigned int value) const
{
  GLint uniformLocation = glGetUniformLocation(shaderProgram, location.c_str());
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  glUniform1ui(uniformLocation, value);
}

void ShaderProgram::SetUniform(const std::string &location, float value) const
{
  GLint uniformLocation = glGetUniformLocation(shaderProgram, location.c_str());
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  glUniform1f(uniformLocation, value);
}

void ShaderProgram::SetUniform(const std::string &location, double value) const
{
  GLint uniformLocation = glGetUniformLocation(shaderProgram, location.c_str());
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  glUniform1d(uniformLocation, value);
}

void ShaderProgram::SetUniform(const std::string &location, const glm::vec4 &value) const
{
  GLint uniformLocation = glGetUniformLocation(shaderProgram, location.c_str());
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  float val[] = { value.x, value.y, value.z, value.w };
  glUniform4fv(uniformLocation, 1, val);
}

void ShaderProgram::SetUniform(const std::string &location, const glm::vec3 &value) const
{
  GLint uniformLocation = glGetUniformLocation(shaderProgram, location.c_str());
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  float val[] = { value.x, value.y, value.z };
  glUniform3fv(uniformLocation, 1, val);
}

void ShaderProgram::SetUniform(const std::string &location, const glm::vec2 &value) const
{
  GLint uniformLocation = glGetUniformLocation(shaderProgram, location.c_str());
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  float val[] = { value.x, value.y };
  glUniform2fv(uniformLocation, 1, val);
}
