#include <texture.h>

/*
* Author: Chris Trimmer
* Assignment: Week 7 (Final Project)
* Date: 04/14/2023
*
* References:
* Ideas, structure, and support from the following sources:
*   http://www.opengl-tutorial.org/beginners-tutorials/
*   https://www.khronos.org/opengl/wiki/Getting_Started#Tutorials_and_How_To_Guides
*   https://learnopengl.com/Introduction
*   https://www.youtube.com/@snhucomputerscience
*	https://www.songho.ca/opengl/gl_cylinder.html
*/


// make sure path is const
Texture::Texture(const std::filesystem::path& path)
{
    /////////////////////////////////////////////  cutting from here ////////////////////////////////////////////


     // load textures
    stbi_set_flip_vertically_on_load(true);
    auto texturePath = path.string();
    //    Path texturePath = std::filesystem::current_path() / "assets" / "textures";


    // local variables supporting texture attributes
    int textureWidth, textureHeight, numChannels;


    /////////////////////////////////////////////////// load and bind texture
    unsigned char* textureData = stbi_load(texturePath.c_str(), &textureWidth, &textureHeight, &numChannels, STBI_rgb_alpha);
    
    glGenTextures(1, &this->textureHandle);
    glBindTexture(GL_TEXTURE_2D, this->textureHandle);

    if (textureData) {

        // these not supported until gl4.2 (change major and minor from 3.3 to 4.2)
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, textureWidth, textureHeight);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else {
        std::cerr << "Could not load texture: " << texturePath << "\n";
    }

    // release texture memory
    stbi_image_free(textureData);



}

void Texture::Bind()
{
 
    glBindTexture(GL_TEXTURE_2D, this->textureHandle);

    // old - keep for reference
    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, this->matrixTexture);

    /*
        default behaviour of applying texture: GL_REPEAT (set values with Uv in types.h)
        WRAP_S = x
        WRAP_T = y

        GL_MIRRORED_REPEAT = alternates between flipping the tiles upside down/right side up
        GL_CLAMP_TO_EDGE = redraws last pixel on edges of image across entire face of object
        GL_CLAMP_TO_BORDER = defaults as black
    */

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


}


// old - save for references
// 
//   /////////////////////////////////////////////////// load and bind Face Texture
//   unsigned char* dataFace = stbi_load(faceTexturePath.c_str(), &textureWidth, &textureHeight, &numChannels, STBI_rgb_alpha);
//   glGenTextures(1, &this->faceTexture);
//   glBindTexture(GL_TEXTURE_2D, this->faceTexture);

//   if (dataFace) {

//       // these not supported until gl4.2 (change major and minor from 3,3 to 4,2)
//       glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, textureWidth, textureHeight);
//       glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGBA, GL_UNSIGNED_BYTE, dataFace);

//       glGenerateMipmap(GL_TEXTURE_2D);

//   }
//   else {
//       std::cerr << "Could not load texture: " << faceTexturePath << "\n";
//   }

//   // release texture memory
//   stbi_image_free(dataFace);


//   /////////////////////////////////////////////////// load and bind Matrix Texture
//   unsigned char* dataMatrix = stbi_load(matrixTexturePath.c_str(), &textureWidth, &textureHeight, &numChannels, STBI_rgb_alpha);
//   glGenTextures(1, &this->matrixTexture);
//   glBindTexture(GL_TEXTURE_2D, this->matrixTexture);

//   if (dataMatrix) {

//       // tells what the data looks like and what it is
//       // this one is depracated - use below two gl functions
////       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

//       // these not supported until gl4.2 (change major and minor from 3,3 to 4,2)
//       glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, textureWidth, textureHeight);
//       glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGBA, GL_UNSIGNED_BYTE, dataMatrix);

//       glGenerateMipmap(GL_TEXTURE_2D);

//   }
//   else {
//       std::cerr << "Could not load texture: " << matrixTexturePath << "\n";
//   }

//   // release texture memory
//   stbi_image_free(dataMatrix);

//   /////////////////////////////////////////////////// bind bricksTexture
//   unsigned char* dataBricks = stbi_load(bricksTexturePath.c_str(), &textureWidth, &textureHeight, &numChannels, STBI_rgb_alpha);
//   glGenTextures(1, &this->bricksTexture);
//   glBindTexture(GL_TEXTURE_2D, this->bricksTexture);

//   if (dataBricks) {

//       // these not supported until gl4.2 (change major and minor from 3,3 to 4,2)
//       glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, textureWidth, textureHeight);
//       glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGBA, GL_UNSIGNED_BYTE, dataBricks);

//       glGenerateMipmap(GL_TEXTURE_2D);

//   }
//   else {
//       std::cerr << "Could not load texture: " << bricksTexturePath << "\n";
//   }

//   // release texture memory
//   stbi_image_free(dataBricks);

//   /////////////////////////////////////////////  cutting end here ////////////////////////////////////////////

