#ifndef TEXT_H
#define TEXT_H

#include <glm/glm.hpp>
#include <GL\glew.h>
#include <freetype-2.6.1/include/ft2build.h>
#include FT_FREETYPE_H

#include <string>

//#define WIDTH 640
//#define HEIGHT 480
//
//unsigned char image[HEIGHT][WIDTH];

class Text
{
public:
	Text(std::string text, std::string font);
	~Text();

	void setText(std::string text);
	void setFont(std::string font);
	void setCharSize(float charSize);
	void setRotation(float angle);
	void setColor(glm::vec3 color);
	void setPosition(glm::vec2 position);
	void setScale(glm::vec2 scale);

	std::string getText(){ return _text; }
	std::string getFont(){ return _font; }
	float getCharSize(){ return _charSize; }
	float getRotation(){ return _angle; }
	glm::vec3 getColor(){ return _color; }
	glm::vec2 getPosition(){ return _position; }
	glm::vec2 getScale(){ return _scale; }

	void move(glm::vec2 newPos);
	void rotate(float newAngle);

	void drawBitmap(FT_Bitmap* bitmap, glm::vec2 coordinates);
	void render(FT_Face&, FT_Error&);
private:
	std::string _text;
	std::string _font;
	float _charSize;
	float _angle;
	glm::vec3 _color;
	glm::vec2 _position;
	glm::vec2 _scale;

	FT_GlyphSlot _slot;
	FT_UInt _glyphIndex;
	FT_Matrix _matrix; // transformation matrix
	FT_Vector _pen; // untransformed origin

	float _pt = 50;
	float _dpi = 100;

	glm::vec2 _resolution = {640, 480};
};
#endif