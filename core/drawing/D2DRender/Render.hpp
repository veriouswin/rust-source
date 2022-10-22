#pragma once

namespace D2DRender {
	inline Vector2 GetScreenSize() {
		return Vector2(ScreenSize.x, ScreenSize.y);
	}

	inline Vector2 GetTextSize(float _fontsize, std::string _text) {
		auto text_size = Renderer::get_text_size(StringConverter::ToUnicode(_text), _fontsize);
		return Vector2(text_size.x, text_size.y);
	}

	inline void Text(int _x, int _y, float _fontsize, ImColor _color, std::string _text) {
		Renderer::text({ (float)_x, (float)_y }, _color, _fontsize, false, true, StringConverter::ToUnicode(_text));
	}

	inline void Rectangle(int _x, int _y, int _width, int _height, ImColor _color) {
		Renderer::rectangle_filled({ (float)_x, (float)_y }, { (float)_width, (float)_height }, _color);
	}

	inline void Outline(int _x, int _y, int _width, int _height, ImColor _color) {
		Rectangle(_x, _y, _width, 1, _color);
		Rectangle(_x, _y, 1, _height, _color);
		Rectangle(_x + _width - 1, _y, 1, _height, _color);
		Rectangle(_x, _y + _height - 1, _width, 1, _color);
	}

	inline void Line(int _from_x, int _from_y, int _to_x, int _to_y, ImColor _color) {
		Renderer::line({ (float)_from_x, (float)_from_y }, { (float)_to_x, (float)_to_y }, _color);
	}

	inline void Gradient(int _x, int _y, int _width, int _height, ImColor _color1, ImColor _color2, bool _horizontal) {
		Renderer::gradient_rect({ (float)_x, (float)_y }, { (float)_width, (float)_height }, _color1, _color2, _horizontal);
	}
}