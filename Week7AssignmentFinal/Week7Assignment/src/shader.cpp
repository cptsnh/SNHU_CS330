#include <shader.h>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	load(vertexSource, fragmentSource);
}

Shader::Shader(const Path& vertexPath, const Path& fragmentPath)
{
	
    try {
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        // load our shader
        load(vShaderStream.str(), fShaderStream.str());

    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::OPENINING SHADER FILES\n" << std::endl;

    }
}

void Shader::load(const std::string& vertexSource, const std::string& fragmentSource)
{
    /////////////////// build and compile the vertex shader program /////////////////////
    const char* vShaderCode = vertexSource.c_str();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // 1 = single shader
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    // check for vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /////////////////// build and compile the fragment shader program /////////////////////
    const char* vFragmentCode = fragmentSource.c_str();
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &vFragmentCode, NULL);
    glCompileShader(fragmentShader);

    // check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /////////////////// link the shaders /////////////////////
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // shaders no longer needed after program is created
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

GLint Shader::getUniformLocation(const std::string& uniformName) const
{
    return glGetUniformLocation(shaderProgram, uniformName.c_str());
//    return 0;
}

void Shader::Bind()
{
    // use the triangle shader program
    glUseProgram(shaderProgram);
    setTextures();
}

void Shader::SetMat4(const std::string& uniformName, const glm::mat4& mat4) const
{
    auto uniformLoc = getUniformLocation(uniformName);
    if (uniformLoc != -1) {
  //      Bind();
        glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat4));

    }
}
  
// set the texture (i.e., texture0, texture1, etc)
void Shader::SetInt(const std::string& uniformName, int value) const
{
    auto uniformLoc = getUniformLocation(uniformName);
    if (uniformLoc != -1) {
  //      Bind();

        // use 1i for integer
        glUniform1i(uniformLoc, value);

    }
}

void Shader::setTextures() {

    this->SetInt("tex0", 0);
    this->SetInt("tex1", 1);
    this->SetInt("tex2", 2);
    this->SetInt("tex3", 3);
    this->SetInt("tex4", 4);
    this->SetInt("tex5", 5);
    this->SetInt("tex6", 6);
    this->SetInt("tex7", 7);
    this->SetInt("tex8", 8);
    this->SetInt("tex9", 9);
    for (auto i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i]->Bind();
    }


}

void Shader::AddTexture(const std::shared_ptr<Texture>& texture) {

    

    textures.emplace_back(texture);
//    std::cout << "texture num: " + textures.size() << "\n";
//    glActiveTexture(GL_TEXTURE0 + (textures.size() - 1));
//    auto& t = textures[0];
//    t.get()->Bind();

 //   auto& t = textures.emplace_back(texture);
 //   t.get()->Bind();
}


void Shader::SetVec3(const std::string& uniformName, const glm::vec3& vec3) const {
    
    auto uniformLoc = getUniformLocation(uniformName);
    
    if (uniformLoc != -1) {
        glUniform3fv(uniformLoc, 1, glm::value_ptr(vec3));
    }

}

void Shader::SetFloat(const std::string& uniformName, const float value) const
{
    auto uniformLoc = getUniformLocation(uniformName);

    if (uniformLoc != -1) {
        glUniform1f(uniformLoc, value);
    }

}
