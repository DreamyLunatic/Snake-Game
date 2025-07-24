#include <raylib.h>
#pragma once


struct TextAttributes
{
	const char* pText;
	Vector2 position;

	Font font;
	int fontSize;
	int spacing;

	// Constructor to initialize const members
	TextAttributes(const char* text, Rectangle borders, Font f, int s)
		: pText(text), position({ borders.x, borders.y }), font(f), spacing(s), borders(borders)
	{
		FormatText(text, borders);
	}

	TextAttributes& operator=(const TextAttributes& other) {
		if (this != &other) { // Check for self-assignment
			// Perform member-wise copy
			pText = other.pText;
			position = other.position;
			font = other.font;
			fontSize = other.fontSize;
			spacing = other.spacing;
		}
		return *this;
	}

	void ChangeText(const char* text)
	{
		pText = text;
		FormatText(text, borders);
	}

	void FormatText(const char* text, Rectangle borders)
	{
		fontSize = 0;

		Vector2 textSize = MeasureTextEx(font, pText, fontSize, spacing);

		// Initial large step increment 
		while ((textSize.x < borders.width - borders.width / 6) && (textSize.y < borders.height - borders.height / 4)) {
			fontSize += 5;
			textSize = MeasureTextEx(font, pText, fontSize, spacing);
		} // Fine-tuning with smaller step increment 
		while ((textSize.x > borders.width - borders.width / 6) || (textSize.y > borders.height - borders.height / 4)) {
			fontSize--;
			textSize = MeasureTextEx(font, pText, fontSize, spacing);
		}

		position = { borders.x + (borders.width - textSize.x) / 2, borders.y + (borders.height - textSize.y) / 2 };
	}

private:
	Rectangle borders;
};