#include <raylib.h>
#include <functional>
#include <tuple>
#include "Colors.h"
#include "TextAttributes.h"

#pragma once

template<typename... Args>
class Button
{
public:
	enum class ButtonState { STATIC, HOVER, PRESSED };

	Button(Rectangle buttonRect, std::function<void(Args...)> callback, const char* text, Font font, std::pair<Color, Color> colors, Args... args)
		: buttonRect(buttonRect), callback(callback), colors(colors), args(std::make_tuple(args...)), b_TextAttributes(text, buttonRect, font, 3)
	{
		darkerColors = { ColorManager::MakeDarker(colors.first), ColorManager::MakeDarker(colors.second) };
	}

	void Place(Rectangle rect) { buttonRect = rect; }

protected:
	void ChangeText(const char* text);
	virtual void Draw() {};
	virtual void Click();

	void SetCallback(std::function<void(Args...)> callback, Args ...args);

	TextAttributes GetTextAttributes() { return b_TextAttributes; }
	Rectangle GetBorders() const { return buttonRect; }
	Color GetColor(ButtonState bs);
private:
	TextAttributes b_TextAttributes;
	std::pair<Color, Color> colors;
	std::pair<Color, Color> darkerColors;

	Rectangle buttonRect;
	std::function<void(Args...)> callback;
	std::tuple<Args...> args;
};

template<typename ...Args>
void Button<Args...>::SetCallback(std::function<void(Args...)> callback, Args ...args)
{
	this->callback = callback;
	this->args = std::make_tuple(args...);
}

template<typename ...Args>
inline Color Button<Args...>::GetColor(ButtonState bs)
{
	return bs == ButtonState::STATIC  ? colors.first :
		   bs == ButtonState::HOVER   ? darkerColors.first :
		   bs == ButtonState::PRESSED ? darkerColors.second : colors.second;
}

template<typename ...Args>
void Button<Args...>::ChangeText(const char* text)
{
	b_TextAttributes.ChangeText(text);
}

template<typename... Args>
void Button<Args...>::Click()
{
	if (callback) std::apply(callback, args);
}

template<typename... Args>
class RoundedButton : public Button<Args...>
{
public:
	RoundedButton(Rectangle buttonRect, std::function<void(Args...)> callback, const char* text, Font font = GetFontDefault(), std::pair<Color, Color> colors = { YELLOW, BLUE }, Args... args)
		: Button<Args...>(buttonRect, callback, text, font, colors, args...), b_TextAttributes(this->GetTextAttributes())
	{ 
		this->buttonRect = this->GetBorders();

		staticColor = this->GetColor(this->ButtonState::STATIC);
		hoverColor = this->GetColor(this->ButtonState::HOVER);
		pressedColor = this->GetColor(this->ButtonState::PRESSED);

		currentColor = this->GetColor(this->ButtonState::STATIC);
	}

	void ChangeText(const char* text)
	{
		Button<Args...>::ChangeText(text);
		b_TextAttributes = TextAttributes(this->GetTextAttributes());
	}

	void Draw() override
	{
		if (CheckCollisionPointRec(GetMousePosition(), buttonRect))
		{
			currentColor = hoverColor;

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) currentColor = pressedColor;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) this->Click();
		}
		else
		{
			currentColor = staticColor;
		}

		DrawRectangleRounded(buttonRect, 0.3f, 32, currentColor);
		DrawRectangleRoundedLinesEx(buttonRect, 0.3f, 32, (buttonRect.width + buttonRect.height) / 80, ColorManager::BWInvert(currentColor));
		DrawTextEx(b_TextAttributes.font, b_TextAttributes.pText, b_TextAttributes.position, (float)b_TextAttributes.fontSize, b_TextAttributes.spacing, ColorManager::BWInvert(currentColor));
	}
private:
	TextAttributes b_TextAttributes;
	Rectangle buttonRect;

	Color staticColor;
	Color hoverColor;
	Color pressedColor;
	Color currentColor;
};

template<typename... Args>
class RegularButton : public Button<Args...>
{
public:
	RegularButton(Rectangle buttonRect, std::function<void(Args...)> callback, const char* text, Font font = GetFontDefault(), std::pair<Color, Color> colors = { YELLOW, BLUE }, Args... args)
		: Button<Args...>(buttonRect, callback, text, font, colors, args...), b_TextAttributes(this->GetTextAttributes())
	{
		this->buttonRect = this->GetBorders();

		staticColor = this->GetColor(this->ButtonState::STATIC);
		hoverColor = this->GetColor(this->ButtonState::HOVER);
		pressedColor = this->GetColor(this->ButtonState::PRESSED);

		currentColor = this->GetColor(this->ButtonState::STATIC);
	}

	void ChangeText(const char* text)
	{
		Button<Args...>::ChangeText(text);
		b_TextAttributes = TextAttributes(this->GetTextAttributes());
	}

	void Draw() override
	{
		if (CheckCollisionPointRec(GetMousePosition(), buttonRect))
		{
			currentColor = hoverColor;

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) currentColor = pressedColor;
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) this->Click();
		}
		else
		{
			currentColor = staticColor;
		}

		DrawRectangle(buttonRect.x, buttonRect.y, buttonRect.width, buttonRect.height, currentColor);
		DrawRectangleLinesEx(buttonRect, (buttonRect.width + buttonRect.height) / 80, ColorManager::BWInvert(currentColor));
		DrawTextEx(b_TextAttributes.font, b_TextAttributes.pText, b_TextAttributes.position, (float)b_TextAttributes.fontSize, b_TextAttributes.spacing, ColorManager::BWInvert(currentColor));
	}
private:
	TextAttributes b_TextAttributes;
	Rectangle buttonRect;

	Color staticColor;
	Color hoverColor;
	Color pressedColor;
	Color currentColor;
};
