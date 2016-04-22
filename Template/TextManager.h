#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include <vector>
#include <map>
#include <iostream>
#include "Text.h"

class TextManager
{
public:
	TextManager(glm::vec2 window);
	~TextManager();

	void loadFont(std::string font);
	//Text* addText(Text &text);

	void move(Text text, glm::vec2 position);
	void rotate(Text, float angle);
	void render();

	void addText(std::string label, std::string text, std::string font);
	//Text* TextManager::getText(std::string text);
private:
	//std::vector<Text> _texts;
	std::map<std::string, FT_Face> _fonts;

	FT_Library _library;
	FT_Face _face;
	FT_Error _error;
	FT_UInt _glyphIndex;

	std::string _filepath = "../data/fonts/";
	int _faceIndex = 0;

	std::map<std::string, Text> _texts;
};
#endif

//When a new face object is created, all elements are set to 0 during initialization.
//To populate the structure with sensible values, 
//you should call FT_Set_Char_Size.Here is an example, 
//setting the character size to 16pt for a 300×300dpi device :
//
//error = FT_Set_Char_Size(
//	face,    /* handle to face object           */
//	0,       /* char_width in 1/64th of points  */
//	16 * 64,   /* char_height in 1/64th of points */
//	300,     /* horizontal device resolution    */
//	300);   /* vertical device resolution      */

//This function computes the character pixel size that corresponds 
//to the character width and height and device resolutions.
//However, if you want to specify the pixel sizes yourself, you can call FT_Set_Pixel_Sizes.
//
//error = FT_Set_Pixel_Sizes(
//face,   /* handle to face object */
//0,      /* pixel_width           */
//16);   /* pixel_height          */