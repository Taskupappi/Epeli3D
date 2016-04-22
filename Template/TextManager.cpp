#include "TextManager.h"

TextManager::TextManager(glm::vec2 window)
{
	loadFont("times.ttf");
}

TextManager::~TextManager()
{
	for (auto it = _fonts.begin(); it != _fonts.end(); ++it)
	{
		FT_Done_Face(it->second);
	}
	FT_Done_FreeType(_library);

	_texts.clear();
	_fonts.clear();
}

void TextManager::loadFont(std::string font)
{
	_filepath = _filepath + font;
	const char* filepath = _filepath.c_str();

	_error = FT_Init_FreeType(&_library);

	if (_error)
	{
		// Error occured during library initialization
		std::cout << "Failed to initialize library" << std::endl;
	}

	_error = FT_New_Face(_library, filepath, _faceIndex, &_face);

	if (_error == FT_Err_Unknown_File_Format)
	{
		// the font file could be opened and read, but it appears
		// that its font format is unsupported
		std::cout << "Font format is not supported" << std::endl;
	}
	else if (_error)
	{
		// another error code means that the font file could not
		// be opened or read, or that it is broken
		std::cout << "Font file could not be opened or read" << std::endl;
	}
	else
	{
		_fonts.insert(std::make_pair(font, _face));
		std::cout << "Font has been loaded" << std::endl;
	}
}

//Text* TextManager::addText(Text &text)
//{
//	_texts.push_back(text);
//
//	std::string font = text.getFont();
//
//	auto it = _fonts.find(font);
//	if (it == _fonts.end())
//	{
//		loadFont(font);
//	}
//
//	Text* pointer = &text;
//	return pointer;
//}

//void TextManager::render()
//{
//	for (auto it = _texts.begin(); it != _texts.end(); ++it)
//	{
//		auto itFind = _fonts.find(it->getFont());
//		if (itFind != _fonts.end())
//		{
//			FT_Set_Pixel_Sizes(itFind->second, 0, 50); // (face, width, height)
//			it->render(itFind->second, _error);
//		}
//	}
//}

void TextManager::addText(std::string label, std::string text, std::string font)
{
	Text temp(text, font); 	//fontin lisäys
	_texts.insert(std::make_pair(label, temp));

	auto it = _fonts.find(font);
	if (it == _fonts.end())
	{
		loadFont(font);
	}
}

//Text* TextManager::getText(std::string text)
//{
//	Text* pointer;
//
//	auto it = _texts.find(text);
//	if (it != _texts.end())
//	{
//		pointer = &it->second;
//	}
//	else
//	{
//		// handle error
//		pointer = nullptr;
//	}
//
//	return pointer;
//}

//void TextManager::move(Text text, glm::vec2 position)
//{
//	text.move(position);
//}
//
//void TextManager::rotate(Text text, float angle)
//{
//	text.rotate(angle);
//}

void TextManager::render()
{
	if (_fonts.size() != 0)
	{
		for (auto it = _texts.begin(); it != _texts.end(); ++it)
		{
			int i = _fonts.size();
			auto itFind = _fonts.find(it->second.getFont());
			if (itFind != _fonts.end())
			{
				it->second.render(itFind->second, _error);
			}
		}
	}
	else
	{
		// handle exception
	}
}

