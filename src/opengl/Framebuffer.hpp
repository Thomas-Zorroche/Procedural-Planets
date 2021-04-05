#pragma once

class Framebuffer
{
public:
	Framebuffer(float width = 64.0f, float height = 64.0f);

	unsigned int id() const { return _id; }
	void resize(float width, float height);

private:
	unsigned int _id;
	unsigned int _textureID;
	unsigned int _rboID;
};