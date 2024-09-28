#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <stb/stb_image.h>
#include <string>

class Texture {
public:
  Texture(const std::string &path);
  ~Texture();
  void Bind(unsigned int slot = 0) const;
  void Unbind() const;
  inline int GetWidth() const { return m_Width; }
  inline int GetHeight() const { return m_Height; }
  bool IsLoaded() const { return m_LocalBuffer != nullptr; }

private:
  unsigned int m_RendererID;
  std::string m_FilePath;
  unsigned char *m_LocalBuffer;
  int m_Width, m_Height, m_BPP;
};
