#include "shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& msg)
{
    GLint success = 0;
    GLchar error[512] = {0};
    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        std::cerr << msg << ": '" << error << "'" << std::endl;
    }
}

static GLuint CreateShader(const std::string& text, GLenum type)
{
    GLuint shader = glCreateShader(type);

    if(shader == 0)
        std::cerr << "Shader creation failed" << std::endl;
    const GLchar* shader_source[1];
    GLint shader_source_len[1];
    shader_source[0] = text.c_str();
    shader_source_len[0] = text.length();

    glShaderSource(shader, 1, shader_source, shader_source_len);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader compilation failed ");

    return shader;
}

static std::string LoadShader(const std::string& shader_file)
{
    std::cout << shader_file << std::endl;
    std::ifstream file;
    file.open(shader_file.c_str());
    std::string out;
    std::string line;
    if(file.is_open())
    {
        while(file.good())
        {
            std::getline(file, line);
            out.append(line + "\n");
        }
    }
    else
        std::cerr << "Unable to load shader: " << shader_file << std::endl;
    return out;
}
void shader::Update(const transform& trans, const Camera& cam)
{
    glUniformMatrix4fv(_uniforms[TRANSFORM], 1, GL_FALSE, &trans.GetModel()[0][0]);
    glUniformMatrix4fv(_uniforms[CAMERA], 1, GL_FALSE, &cam.GetViewProjection()[0][0]);
}
shader::shader(const std::string& shader_file)
{
    _shader_program = glCreateProgram();
    _shader_list[0] = CreateShader(LoadShader(shader_file + ".vertex"), GL_VERTEX_SHADER);
    _shader_list[1] = CreateShader(LoadShader(shader_file + ".fragment"), GL_FRAGMENT_SHADER);
    for(size_t i = 0; i < SHADER_LIST_SIZE; i++)
        glAttachShader(_shader_program, _shader_list[i]);
    glBindAttribLocation(_shader_program, 0, "position");
    glBindAttribLocation(_shader_program, 1, "texture");
    glBindAttribLocation(_shader_program, 2, "normal");
    glLinkProgram(_shader_program);
    CheckShaderError(_shader_program, GL_LINK_STATUS, true, "Shader linking failed ");
    glValidateProgram(_shader_program);
    CheckShaderError(_shader_program, GL_VALIDATE_STATUS, true, "Shader invalid ");
    _uniforms[TRANSFORM] = glGetUniformLocation(_shader_program, "transform");
    _uniforms[NORMAL] = glGetUniformLocation(_shader_program, "Normal");
    _uniforms[CAMERA] = glGetUniformLocation(_shader_program, "camera");
}

void shader::Bind() { glUseProgram(_shader_program); }

shader::~shader()
{
    for(size_t i = 0; i < SHADER_LIST_SIZE; i++)
    {
        glDetachShader(_shader_program, _shader_list[i]);
        glDeleteShader(_shader_list[i]);
    }
    glDeleteProgram(_shader_program);
}
