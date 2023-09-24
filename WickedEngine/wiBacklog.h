#pragma once
#include "CommonInclude.h"
#include "wiGraphicsDevice.h"
#include "wiCanvas.h"
#include "wiColor.h"

#include <string>

namespace wi::backlog
{
	// Do not modify the order, as this is exposed to LUA scripts as int!
	enum class LogLevel
	{
		None,
		Default,
		Warning,
		Error,
		Fatal,
	};

	void Toggle();
	void Scroll(int direction);
	void Update(const wi::Canvas& canvas, float dt = 1.0f / 60.0f);
	void Draw(
		const wi::Canvas& canvas,
		wi::graphics::CommandList cmd,
		wi::graphics::ColorSpace colorspace = wi::graphics::ColorSpace::SRGB
	);
	void DrawOutputText(
		const wi::Canvas& canvas,
		wi::graphics::CommandList cmd,
		wi::graphics::ColorSpace colorspace = wi::graphics::ColorSpace::SRGB
	);

	std::string getText();
	void clear();
#define post_backlog(...) post(__FILE__, __LINE__, __VA_ARGS__)
	void post(const char* file, int line, const std::string& input, LogLevel level = LogLevel::Default);
	std::string& postf_buffer(const char* file, int line, int length);
#define post_backlogf(...) postf(__FILE__, __LINE__, __VA_ARGS__)
	template<typename... Args>
	void postf(const char* file, int line, LogLevel level, const char* format, Args... args)
	{
		int length = std::snprintf(nullptr, 0, format, args...);
		std::string& buffer = postf_buffer(file, line, length);
		std::snprintf(&buffer[0], length + 1, format, args...);
		post(file, line, buffer, level);
	}
	template<typename... Args>
	inline void postf(const char* file, int line, const char* format, Args... args)
	{
		postf(file, line, LogLevel::Default, format, args...);
	}

	void historyPrev();
	void historyNext();

	bool isActive();

	void setBackground(wi::graphics::Texture* texture);
	void setFontSize(int value);
	void setFontRowspacing(float value);
	void setFontColor(wi::Color color);

	void Lock();
	void Unlock();

	void BlockLuaExecution();
	void UnblockLuaExecution();

	void SetLogLevel(LogLevel newLevel);


	// These are no longer used, but kept here to not break user code:
	inline void input(const char input) {}
	inline void acceptInput() {}
	inline void deletefromInput() {}
};
