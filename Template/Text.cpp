#include "text.h"
Text::Text(std::string text, std::string font)
{
	_text = text;
	_font = font;
	_charSize = 12;
	_angle = 0;
	_color = { 256, 256, 256 };
	_position = { 0, 0 };
	_scale = { 1, 1 };
}

Text::~Text()
{

}

void Text::setText(std::string text)
{
	_text = text;
}

void Text::setFont(std::string font)
{
	_font = font;
}

void Text::setCharSize(float charSize)
{
	_charSize = charSize;
}

void Text::setRotation(float angle)
{
	_angle = (angle / 360) * 3.14159 * 2; // kulma asteissa
}

void Text::setColor(glm::vec3 color)
{
	_color = color;
}

void Text::setPosition(glm::vec2 position)
{
	_position = position;
}

void Text::setScale(glm::vec2 scale)
{
	_scale = scale;
}

void Text::render(FT_Face &face, FT_Error &error)
{
	error = FT_Set_Char_Size(face, 64 *_charSize, 64 * _charSize, _pt, _dpi);

	_slot = face->glyph; // small shortcut

	// set up matrix
	_matrix.xx = (FT_Fixed)(cos(_angle) * 0x10000L);
	_matrix.xy = (FT_Fixed)(-sin(_angle) * 0x10000L);
	_matrix.yx = (FT_Fixed)(sin(_angle) * 0x10000L);
	_matrix.yy = (FT_Fixed)(cos(_angle) * 0x10000L);

	// pen position in 26.6 cartesian space coordinates
	// start at (300, 200)
	_pen.x = 300 * 64;
	_pen.y = (_resolution.y - 200) * 64; // pen.y = ( my_target_height - 200 ) * 64;

	for (int i = 0; i < _text.size(); i++)
	{
		FT_Set_Transform(face, &_matrix, &_pen);

		error = FT_Load_Char(face, _text.at(i), FT_LOAD_RENDER);
		if (error)
		{
			continue; // ignore errors
		}
		// now, draw to our target surface (convert position)
		//drawBitmap(&_slot->bitmap, glm::vec2(_slot->bitmap_left, _resolution.y - _slot->bitmap_top));

		_pen.x += _slot->advance.x;
		_pen.y += _slot->advance.y;
	}
}

void Text::move(glm::vec2 newpos)
{
	_position = newpos;
}

void Text::rotate(float newAngle)
{
	_angle = newAngle;
}
