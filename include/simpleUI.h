//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																												//
// simpleUI by Ishakao | https://github.com/Ishakao/simpleUI													//
// Current Version 1.0.1																						//
//																												//
// Description:																									//
// simpleUI is a library for simple creating a beautiful and fast user interfaces.								//
// Based on raylib v5.5 by raysan5 (www.raylib.com | https://github.com/raysan5)								//
// simpleUI interfaces are based on a hierarchical structure of objects for convinient objects management		//	
//																												//
//      ! IF YOU NEED SOME RAYLIB FUNCTIONS/STRUCTURES USE RAYLIB_FUNCTIONAL:: NAMESPACE TO USE THEM !          //
//																												//
// Change Logs:																								    //
// Better child event system																					//
// Text class for management TextLabel and TextBox (TEXT_CHANGED events optimization)							//
// Additional events for objects (like TEXT_CHANGED on text-objects)											//
// Textures RAM & VRAM optimization																				//
// A few CPU optimizations																						//
// Spacial Grid optimization for ScrollFrame (millions of objects with thousands of FPS)					    //
// TextBox input can be on any language (any UTF-8 character)													//
// TextBox now supports clipboard and Y viewport																//
// Optimizated position and size calculate functions															//
// Self rectangles batcher and shaders. Now rounded rectangles are so optimized (minimal CPU overload)			//
// Textures atlassing (excluding TextureLabel)																	//
// Improved performance on big quantity of rectangles															//
// Several architecture changes. ODR fix, ::New(), ::Destroy(), GetRoot() to get singleton root Instance		//
// Textures draw optimization. Batching for textures and rectangles												//
//																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <cstdarg>
#include <cstring>

#define SIMPLEUI_INCLUDE_EXTENSION // Extension for simpleUI. Contains additional unnecesary 2D objects (GraphBuilder, ToggleSwitcher, !CheckBox, !MultiCheckBox, !ComboBox, !ProgressBar, !DropdownBox)
// IF YOU DON'T NEED SIMPLEUI EXTENSION THEN USE "#define EXCLUDE_SIMPLEUI_EXTENSION" BEFORE INCLUDING simpleUI.h

// use #define SIMPLEUI_IMPLEMENTATION before including simpleUI.h for stb implementation

#ifdef SIMPLEUI_IMPLEMENTATION
	#define STB_IMAGE_WRITE_IMPLEMENTATION
	#define STB_RECT_PACK_IMPLEMENTATION
#endif

#include "stb_image_write.h"
#include "stb_rect_pack.h"

namespace RAYLIB_FUNCTIONAL {
	#include <raylib.h>
	#include <rlgl.h>
}

using RAYLIB_FUNCTIONAL::Vector2;
using RAYLIB_FUNCTIONAL::Shader;
using RAYLIB_FUNCTIONAL::Image;
using RAYLIB_FUNCTIONAL::Texture;
using RAYLIB_FUNCTIONAL::Color;
using RAYLIB_FUNCTIONAL::Font;
using RAYLIB_FUNCTIONAL::Rectangle;
using RAYLIB_FUNCTIONAL::Vector3;
using RAYLIB_FUNCTIONAL::Vector4;
using RAYLIB_FUNCTIONAL::RenderTexture2D;
using RAYLIB_FUNCTIONAL::Texture2D;

using RAYLIB_FUNCTIONAL::SetMouseCursor;
using RAYLIB_FUNCTIONAL::SetTargetFPS;
using RAYLIB_FUNCTIONAL::SetWindowPosition;
using RAYLIB_FUNCTIONAL::SetExitKey;
using RAYLIB_FUNCTIONAL::SetWindowMinSize;
using RAYLIB_FUNCTIONAL::SetConfigFlags;
using RAYLIB_FUNCTIONAL::SetTraceLogLevel;
using RAYLIB_FUNCTIONAL::SetWindowSize;
using RAYLIB_FUNCTIONAL::InitWindow;
using RAYLIB_FUNCTIONAL::CloseWindow;
using RAYLIB_FUNCTIONAL::CodepointToUTF8;
using RAYLIB_FUNCTIONAL::GetWindowPosition;
using RAYLIB_FUNCTIONAL::GetScreenWidth;
using RAYLIB_FUNCTIONAL::GetScreenHeight;
using RAYLIB_FUNCTIONAL::GetFrameTime;
using RAYLIB_FUNCTIONAL::GetMousePosition;
using RAYLIB_FUNCTIONAL::GetMonitorRefreshRate;
using RAYLIB_FUNCTIONAL::GetCurrentMonitor;
using RAYLIB_FUNCTIONAL::GetMouseWheelMove;
using RAYLIB_FUNCTIONAL::GetCharPressed;
using RAYLIB_FUNCTIONAL::GetClipboardText;
using RAYLIB_FUNCTIONAL::IsKeyDown;
using RAYLIB_FUNCTIONAL::IsKeyPressed;
using RAYLIB_FUNCTIONAL::IsMouseButtonPressed;
using RAYLIB_FUNCTIONAL::IsMouseButtonReleased;
using RAYLIB_FUNCTIONAL::IsWindowMaximized;
using RAYLIB_FUNCTIONAL::IsWindowReady;
using RAYLIB_FUNCTIONAL::IsWindowFullscreen;
using RAYLIB_FUNCTIONAL::WindowShouldClose;
using RAYLIB_FUNCTIONAL::ToggleFullscreen;
using RAYLIB_FUNCTIONAL::MaximizeWindow;
using RAYLIB_FUNCTIONAL::MinimizeWindow;
using RAYLIB_FUNCTIONAL::RestoreWindow;

using RAYLIB_FUNCTIONAL::GenTextureMipmaps;
using RAYLIB_FUNCTIONAL::SetTextureFilter;
using RAYLIB_FUNCTIONAL::SetTextureWrap;

using RAYLIB_FUNCTIONAL::BeginDrawing;
using RAYLIB_FUNCTIONAL::ClearBackground;
using RAYLIB_FUNCTIONAL::EndDrawing;

using RAYLIB_FUNCTIONAL::TEXTURE_FILTER_TRILINEAR;
using RAYLIB_FUNCTIONAL::TEXTURE_FILTER_BILINEAR;
using RAYLIB_FUNCTIONAL::TEXTURE_WRAP_CLAMP;

using RAYLIB_FUNCTIONAL::FLAG_WINDOW_UNDECORATED;
using RAYLIB_FUNCTIONAL::FLAG_WINDOW_RESIZABLE;
using RAYLIB_FUNCTIONAL::FLAG_MSAA_4X_HINT;

using RAYLIB_FUNCTIONAL::PIXELFORMAT_UNCOMPRESSED_R8G8B8;
using RAYLIB_FUNCTIONAL::PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

using RAYLIB_FUNCTIONAL::MOUSE_BUTTON_LEFT;
using RAYLIB_FUNCTIONAL::MOUSE_BUTTON_RIGHT;
using RAYLIB_FUNCTIONAL::MOUSE_BUTTON_MIDDLE;

using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_DEFAULT;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_ARROW;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_CROSSHAIR;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_POINTING_HAND;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_RESIZE_ALL;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_NOT_ALLOWED;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_RESIZE_EW;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_RESIZE_NWSE;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_RESIZE_NESW;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_RESIZE_NS;
using RAYLIB_FUNCTIONAL::MOUSE_CURSOR_IBEAM;

using RAYLIB_FUNCTIONAL::LOG_NONE;

using RAYLIB_FUNCTIONAL::KEY_LEFT_SHIFT;
using RAYLIB_FUNCTIONAL::KEY_C;
using RAYLIB_FUNCTIONAL::KEY_V;
using RAYLIB_FUNCTIONAL::KEY_BACKSPACE;
using RAYLIB_FUNCTIONAL::KEY_LEFT_CONTROL;
using RAYLIB_FUNCTIONAL::KEY_DELETE;
using RAYLIB_FUNCTIONAL::KEY_LEFT;
using RAYLIB_FUNCTIONAL::KEY_RIGHT;
using RAYLIB_FUNCTIONAL::KEY_UP;
using RAYLIB_FUNCTIONAL::KEY_DOWN;
using RAYLIB_FUNCTIONAL::KEY_NULL;
using RAYLIB_FUNCTIONAL::KEY_F1;
using RAYLIB_FUNCTIONAL::KEY_F2;
using RAYLIB_FUNCTIONAL::KEY_F3;
using RAYLIB_FUNCTIONAL::KEY_ENTER;

using RAYLIB_FUNCTIONAL::SHADER_UNIFORM_FLOAT;
using RAYLIB_FUNCTIONAL::SHADER_UNIFORM_VEC4;
using RAYLIB_FUNCTIONAL::SHADER_UNIFORM_VEC2;

#include "SUIutils.h" 
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <set>
#include <tuple>
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <type_traits>
#include <atomic>
#include <cstddef>

#define RED_ANSI "\033[31m"
#define GREEN_ANSI "\033[32m"
#define YELLOW_ANSI "\033[33m"
#define BLUE_ANSI "\033[36m"
#define DEFAULT_ANSI "\033[0m"
#define DEFAULT_ATLAS_SIZE 2048

template<typename T, typename = void>
struct is_streamable : std::false_type {};

template<typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>> : std::true_type {};

template<typename T>
inline constexpr bool is_streamable_v = is_streamable<T>::value;

template<typename T>
void SIMPLEUI_THROW_WITH_INFO(const T v, long line, const char* file) {
	if constexpr (is_streamable_v<T>) {
		std::cerr << RED_ANSI << "Throw: _" << v << "_ on line " << line << " (" << file << ")" << DEFAULT_ANSI << std::endl;
	} else {
		std::cerr << RED_ANSI << "Throw (unstreamable | " << &v << " | size: " << sizeof(T) << ") on line " << line << " (" << file << ")" << DEFAULT_ANSI << std::endl;
	}
	throw(1);
}

#define SIMPLEUI_THROW(x) SIMPLEUI_THROW_WITH_INFO(x, __LINE__, __FILE__);

class TextLabel;
class Instance;
class Object2D;
class TextBox;
class ImageLabel;
class ScrollFrame;
class TextureLabel;
class LineEx;
class Atlas;

inline void FlushRectanglesBatch();
inline void updateObject2DVector(Object2D*);

struct RoundRectData {
	// Base rectangle data
	Vector2 Pos, Size;
	Color Color, BorderColor;
	float Transparency, Roundness, BorderTransparency;
	int BorderThickness = 0;
	float Rotation = 0;
	Vector2 Origin = { 0, 0 };

	// Texture data
	Texture2D Texture;
	Rectangle Source;
	Rectangle Destination;
	// Texture color = Color
};

inline void DrawTexturePro(Texture2D t, Rectangle s, Rectangle d, Vector2 o, float r, Color c) {
	FlushRectanglesBatch();
	RAYLIB_FUNCTIONAL::DrawTexturePro(t, s, d, o, r, c);
}
struct SpecialVector2 {
	template <size_t Index>
	struct num {
		float n{};

		SpecialVector2* getOwner() {
			size_t offset = (Index == 0) ? offsetof(SpecialVector2, x) : offsetof(SpecialVector2, y);
			return reinterpret_cast<SpecialVector2*>(reinterpret_cast<char*>(this) - offset);
		}

		operator float() const { return n; }

		template <typename T>
		num& operator=(T val) {
			float new_val = static_cast<float>(val);
			if (n != new_val) {
				n = new_val;
				SpecialVector2* owner = getOwner();
				if (owner->alarmWhenChanged and owner->parentalObj) {
					updateObject2DVector(owner->parentalObj);
				}
			}
			return *this;
		}

		num& operator=(const num& other) {
			return *this = other.n;
		}

		num& operator+=(float val) { return *this = (n + val); }
		num& operator-=(float val) { return *this = (n - val); }
		num& operator*=(float val) { return *this = (n * val); }
		num& operator/=(float val) { return *this = (n / val); }
	};

	using num_x = num<0>;
	using num_y = num<1>;

	Object2D* parentalObj = nullptr;
	bool alarmWhenChanged = true;

	num_x x;
	num_y y;

	SpecialVector2() = default;

	SpecialVector2(float x_val, float y_val, Object2D* parental = nullptr) : parentalObj(parental), x{ x_val }, y{ y_val } {}

	SpecialVector2(const Vector2& other) : x{ other.x }, y{ other.y } {}

	operator Vector2() const {
		return { x.n, y.n };
	}

	SpecialVector2& operator=(const SpecialVector2& other) {
		if (alarmWhenChanged and (x.n != other.x or y.n != other.y)) {
			alarmWhenChanged = false;
			x = other.x;
			y = other.y;
			alarmWhenChanged = true;

			if (parentalObj) {
				updateObject2DVector(parentalObj);
			}
		} else {
			x.n = other.x;
			y.n = other.y;
		}
		return *this;
	}

	bool operator==(const SpecialVector2& other) const {
		return other.x == x and other.y == y;
	}
};

struct AtlasTexture;

namespace SIMPLEUI_GLOBAL {
	inline int winWidth = 0;
	inline int winHeight = 0;
	inline int defaultSpacing = 0;
	inline float dt = 0;
	inline SpecialVector2 changeWindowSize = { 0,0 };
	inline bool changeWindowSizeB = false;
	inline bool windowSizeChanged = false;
	inline long accurateFPS = 0;
	inline bool programRunning = true;
	inline SpecialVector2 mousePosition;
	inline SpecialVector2 mouseScreenPosition;
	inline SpecialVector2 windowPosition;
	inline constexpr const char* BASIC_FONT_NAME = "Arial";
	inline constexpr const char* DEBUG_MENU_FONT_NAME = "rog";
	inline std::unordered_map<int, Shader> Shaders;
	inline long currentUniqueObjectID = 0;
	inline bool sceneDirty = false; // true in frame where any object size or position changed

	inline int TextureRoundnessShader = -1;
	inline int RectangleRoundnessShader = -1;
	inline int CurrentCustomShader = -1;
	inline std::vector<RoundRectData> CurrentRectanglesBatch;

	inline std::mutex ImagesLoadingMtx;
	inline std::unordered_map<std::string, std::pair<Image, AtlasTexture>> loadedImages;
	inline std::unordered_map<std::string, Image> pendingImages;

	inline size_t framesSinceStart = 0;

	inline TextBox* FocusedTextBox = nullptr;
	inline Object2D* PreviousHigherObject = nullptr;
	inline Object2D* higherObject = nullptr;

	inline std::vector<uint8_t> deletedObjectsByID;

	inline std::vector<Atlas*> AtlasArray;
	inline size_t AtlasTextureId = 1;
	inline unsigned int CurrentBatchTexture = 0;
}

inline void DrawRoundRectBatch(const RoundRectData&);

namespace RL_FUNCTIONS_PLUS {
	inline void BeginShaderMode(Shader shader) {
		SIMPLEUI_GLOBAL::CurrentCustomShader = shader.id;
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::BeginShaderMode(shader);
	}

	inline void EndShaderMode() {
		FlushRectanglesBatch();
		SIMPLEUI_GLOBAL::CurrentCustomShader = -1;
		RAYLIB_FUNCTIONAL::EndShaderMode();
	}

	inline void BeginTextureMode(RenderTexture2D texture) {
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::BeginTextureMode(texture);
	}

	inline void EndTextureMode() {
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::EndTextureMode();
	}

	inline void BeginBlendMode(int mode) {
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::BeginBlendMode(mode);
	}

	inline void EndBlendMode() {
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::EndBlendMode();
	}

	inline void BeginScissorMode(int x, int y, int width, int height) {
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::BeginScissorMode(x, y, width, height);
	}

	inline void EndScissorMode() {
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::EndScissorMode();
	}

	inline void DrawLineEx(Vector2 s, Vector2 e, float t, Color c) {
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::DrawLineEx(s, e, t, c);
	}

	inline void DrawTexturePro(Texture2D texture, Vector2 position, Vector2 size, Rectangle source, Rectangle destination, Vector2 origin, float rotation, Color color, float roundness) {
		const RoundRectData rec = { 
			position, 
			size, 
			color, {255,255,255,255},
			0.0f, roundness, 1.0f, 
			0, 
			rotation, 
			{ origin.x * destination.x, origin.y * destination.y },
			texture,
			source,
			destination
		};

		DrawRoundRectBatch(rec);
	}

	inline void DrawTexture(Texture2D t, int x, int y, Color c) {
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::DrawTexture(t, x, y, c);
	}

	inline void SetShaderValue(Shader shader, int a, const void* ptr, int type) {
		FlushRectanglesBatch();
		RAYLIB_FUNCTIONAL::SetShaderValue(shader, a, ptr, type);
	}
}

struct OffsetScale {
	int Offset = 0; // value in pixels
	float Scale = 0; // relative value
};

struct Padding {
	OffsetScale upper = { 0,0 };
	OffsetScale lower = { 0,0 };
	OffsetScale left = { 0,0 };
	OffsetScale right = { 0,0 };
};

struct AtlasTexture {
	size_t id = 0;
	Vector2 position = { 0,0 };
	Vector2 size = { 0,0 };
	Atlas* currentAtlas = nullptr;
};

class Atlas {
	RenderTexture2D tex;
	std::vector<AtlasTexture> textures;
	std::vector<stbrp_node> nodes;
	stbrp_context ctx;
	int padding;
	bool pleaseGenerateMipmaps = false;
public:
	Texture2D texture() { 
		if (pleaseGenerateMipmaps) {
			GenTextureMipmaps(&tex.texture);
			pleaseGenerateMipmaps = false;
		}
		return tex.texture; 
	}
	RenderTexture2D renderTexture() { 
		if (pleaseGenerateMipmaps) {
			GenTextureMipmaps(&tex.texture);
			pleaseGenerateMipmaps = false;
		}
		return tex; 
	}

	Rectangle source(const AtlasTexture& t) const {
		return {
			t.position.x,
			(float)tex.texture.height - t.position.y - t.size.y,
			t.size.x,
			-t.size.y
		};
	}

	void remove(AtlasTexture& tex) {
		for (int i = 0; i < textures.size(); i++) {
			if (textures[i].id == tex.id) {
				textures.erase(textures.begin() + i);
				tex.currentAtlas = nullptr;
				break;
			}
		}

		if (textures.size() == 0) {
			delete this;
		}
	}

	AtlasTexture add(Image img) {
		stbrp_rect r{};
		r.w = img.width + padding * 2;
		r.h = img.height + padding * 2;
		if (!stbrp_pack_rects(&ctx, &r, 1)) return { 0 };

		int x = r.x + padding;
		int y = r.y + padding;

		Texture2D src = LoadTextureFromImage(img);

		RL_FUNCTIONS_PLUS::BeginTextureMode(tex);
		RAYLIB_FUNCTIONAL::rlSetBlendFactorsSeparate(RL_ONE, RL_ZERO, RL_ONE, RL_ZERO, RL_FUNC_ADD, RL_FUNC_ADD);
		RL_FUNCTIONS_PLUS::BeginBlendMode(RAYLIB_FUNCTIONAL::BLEND_CUSTOM_SEPARATE);
		RL_FUNCTIONS_PLUS::DrawTexture(src, x, y, WHITE);
		RL_FUNCTIONS_PLUS::EndBlendMode();
		RL_FUNCTIONS_PLUS::EndTextureMode();

		pleaseGenerateMipmaps = true;

		UnloadTexture(src);

		AtlasTexture att{ SIMPLEUI_GLOBAL::AtlasTextureId++, {(float)x, (float)y} , {(float)img.width, (float)img.height}, this };

		textures.push_back(att);

		return att;
	}

	AtlasTexture add(int width, int height) {
		stbrp_rect r{};
		r.w = width + padding * 2;
		r.h = height + padding * 2;
		if (!stbrp_pack_rects(&ctx, &r, 1)) return { 0 };

		int x = r.x + padding;
		int y = r.y + padding;

		RL_FUNCTIONS_PLUS::BeginTextureMode(tex);
		RAYLIB_FUNCTIONAL::rlSetBlendFactorsSeparate(RL_ONE, RL_ZERO, RL_ONE, RL_ZERO, RL_FUNC_ADD, RL_FUNC_ADD);
		RL_FUNCTIONS_PLUS::BeginBlendMode(RAYLIB_FUNCTIONAL::BLEND_CUSTOM_SEPARATE);
		RAYLIB_FUNCTIONAL::DrawRectangle(x, y, width, height, BLANK);
		RL_FUNCTIONS_PLUS::EndBlendMode();
		RL_FUNCTIONS_PLUS::EndTextureMode();

		pleaseGenerateMipmaps = true;

		AtlasTexture att{ SIMPLEUI_GLOBAL::AtlasTextureId++, {(float)x, (float)y} , {(float)width, (float)height}, this };

		textures.push_back(att);

		return att;
	}

	void blankArea(AtlasTexture t) {
		if (t.currentAtlas != this) return;
		RAYLIB_FUNCTIONAL::rlSetBlendFactorsSeparate(RL_ONE, RL_ZERO, RL_ONE, RL_ZERO, RL_FUNC_ADD, RL_FUNC_ADD);
		RL_FUNCTIONS_PLUS::BeginBlendMode(RAYLIB_FUNCTIONAL::BLEND_CUSTOM_SEPARATE);
		RAYLIB_FUNCTIONAL::DrawRectangle(t.position.x, t.position.y, t.size.x + padding * 2, t.size.y + padding * 2, BLANK);
		RL_FUNCTIONS_PLUS::EndBlendMode();
	}

	Atlas(int size = DEFAULT_ATLAS_SIZE, int pad = 1) : padding(pad) {
		nodes.resize(size);
		tex = RAYLIB_FUNCTIONAL::LoadRenderTexture(size, size);
		SetTextureFilter(tex.texture, TEXTURE_FILTER_TRILINEAR);
		SetTextureWrap(tex.texture, TEXTURE_WRAP_CLAMP);
		std::cout << BLUE_ANSI << "Loaded new render texture for atlas (" << size << "x" << size << ")" << DEFAULT_ANSI << std::endl;
		stbrp_init_target(&ctx, size, size, nodes.data(), (int)nodes.size());
		RL_FUNCTIONS_PLUS::BeginTextureMode(tex);
		ClearBackground(BLANK);
		RL_FUNCTIONS_PLUS::EndTextureMode();

		SIMPLEUI_GLOBAL::AtlasArray.push_back(this);
	}

	Atlas(const Atlas&) = delete;
	Atlas& operator=(const Atlas&) = delete;

	~Atlas() {
		RAYLIB_FUNCTIONAL::UnloadRenderTexture(tex);

		for (int i = 0; i < SIMPLEUI_GLOBAL::AtlasArray.size(); i++) {
			if (SIMPLEUI_GLOBAL::AtlasArray[i] == this) {
				SIMPLEUI_GLOBAL::AtlasArray.erase(SIMPLEUI_GLOBAL::AtlasArray.begin() + i);
				break;
			}
		}
	}
};

namespace RL_FUNCTIONS_PLUS {
	inline void DrawTexturePro(AtlasTexture t, Vector2 pos, Vector2 size, Rectangle s, Rectangle d, Vector2 o, float r, Color c, float rot) {
		if (!t.currentAtlas) return;

		Texture2D tex = t.currentAtlas->texture();

		Rectangle src = { t.position.x + s.x, t.position.y + s.y, s.width, s.height };

		src.y = tex.height - src.y - src.height;
		src.height = -src.height;

		RL_FUNCTIONS_PLUS::DrawTexturePro(tex, pos, size, src, d, o, r, c, rot);
	}
}

inline AtlasTexture LoadTextureOnAtlas(const Image& image, int sizeOfAtlas = DEFAULT_ATLAS_SIZE) {
	for (Atlas* atlas : SIMPLEUI_GLOBAL::AtlasArray) {
		AtlasTexture t = atlas->add(image);
		if (t.id) return t;
	}

	for (int size = sizeOfAtlas; size <= 16384; size *= 2) {
		Atlas* atlas = new Atlas(size);
		AtlasTexture t = atlas->add(image);
		if (t.id) return t;

		std::cout << YELLOW_ANSI << "Image cannot be placed on atlas " << size << "x" << size << "." << DEFAULT_ANSI << std::endl;
		delete atlas;
	}

	return {};
}

inline AtlasTexture LoadRenderTextureOnAtlas(int width, int height, int sizeOfAtlas = DEFAULT_ATLAS_SIZE) {
	for (Atlas* atlas : SIMPLEUI_GLOBAL::AtlasArray) {
		AtlasTexture t = atlas->add(width, height);
		if (t.id) return t;
	}

	for (int size = sizeOfAtlas; size <= 16384; size *= 2) {
		Atlas* atlas = new Atlas(size);
		AtlasTexture t = atlas->add(width, height);
		if (t.id) return t;

		std::cout << YELLOW_ANSI << "Image cannot be placed on atlas " << sizeOfAtlas << "x" << sizeOfAtlas << "." << DEFAULT_ANSI << std::endl;
		delete atlas;
	}

	return {};
}

inline void UnloadTextureFromAtlas(AtlasTexture& t) {
	if (t.currentAtlas and t.id) {
		t.currentAtlas->remove(t);
		t.currentAtlas = nullptr;
		t.id = 0;
	}
}

inline void loadImage(const std::string& name, const std::string& path) {
	SIMPLEUI_GLOBAL::ImagesLoadingMtx.lock();

	if (SIMPLEUI_GLOBAL::pendingImages.find(name) != SIMPLEUI_GLOBAL::pendingImages.end()) {
		SIMPLEUI_GLOBAL::ImagesLoadingMtx.unlock();
		std::cout << YELLOW_ANSI << "Image: " << name << " already exists" << DEFAULT_ANSI << std::endl;
		return;
	}

	Image img = RAYLIB_FUNCTIONAL::LoadImage(path.c_str());
	if (!img.data) {
		SIMPLEUI_GLOBAL::ImagesLoadingMtx.unlock();
		std::cout << YELLOW_ANSI << "Image: " << name << " error while loading" << DEFAULT_ANSI << std::endl;
		return;
	}

	SIMPLEUI_GLOBAL::pendingImages.insert({ name, img });
	SIMPLEUI_GLOBAL::ImagesLoadingMtx.unlock();
}

inline void unloadImage(const std::string& name) {
	SIMPLEUI_GLOBAL::ImagesLoadingMtx.lock();

	auto it = SIMPLEUI_GLOBAL::loadedImages.find(name);
	if (it != SIMPLEUI_GLOBAL::loadedImages.end()) {
		UnloadImage(it->second.first);
		UnloadTextureFromAtlas(it->second.second);
		SIMPLEUI_GLOBAL::loadedImages.erase(it);
	}

	auto it1 = SIMPLEUI_GLOBAL::pendingImages.find(name);
	if (it1 != SIMPLEUI_GLOBAL::pendingImages.end()) {
		UnloadImage(it1->second);
		SIMPLEUI_GLOBAL::pendingImages.erase(it1);
	}

	SIMPLEUI_GLOBAL::ImagesLoadingMtx.unlock();
}

inline std::pair<Image, AtlasTexture> getImage(const std::string& name) {
	if (name == "") { return {}; }

	SIMPLEUI_GLOBAL::ImagesLoadingMtx.lock();
	auto it = SIMPLEUI_GLOBAL::loadedImages.find(name);
	if (it != SIMPLEUI_GLOBAL::loadedImages.end()) {
		SIMPLEUI_GLOBAL::ImagesLoadingMtx.unlock();
		return it->second;
	}

	auto it1 = SIMPLEUI_GLOBAL::pendingImages.find(name);
	if (it1 != SIMPLEUI_GLOBAL::pendingImages.end()) {
		SIMPLEUI_GLOBAL::ImagesLoadingMtx.unlock();
		return { it1->second, AtlasTexture{} };
	}
	SIMPLEUI_GLOBAL::ImagesLoadingMtx.unlock();

	std::cout << YELLOW_ANSI << "Image " << name << " was not found" << DEFAULT_ANSI << std::endl;
	return {};
}

inline int loadNewShader(const std::string& vs, const std::string& fs) {
	static int cur = 0;

	SIMPLEUI_GLOBAL::Shaders.emplace(cur, RAYLIB_FUNCTIONAL::LoadShader(vs.c_str(), fs.c_str()));

	return cur++;
}

inline Shader getShader(int id) {
	auto it = SIMPLEUI_GLOBAL::Shaders.find(id);
	if (it == SIMPLEUI_GLOBAL::Shaders.end()) {
		std::cout << YELLOW_ANSI << "Shader: " << id << " was not found" << DEFAULT_ANSI << std::endl;
		return SIMPLEUI_GLOBAL::Shaders.find(1)->second;
	}
	return it->second;
}

inline Vector2 GetMouseScreenPosition() {
	return { GetMouseScreenPositionX(), GetMouseScreenPositionY() };
}

inline Color mulColor(Color other, float t) {
	return Color{
		(unsigned char)(other.r * t),
		(unsigned char)(other.g * t),
		(unsigned char)(other.b * t),
		other.a
	};
}

inline float sui_lerp(float a, float b, float t) {
	return a + (b - a) * t;
}

inline std::unordered_map<std::string, Font> Fonts;
inline std::vector<std::tuple<const char*, std::string, int>> queuedFonts;

inline void addFontToQueqe(const char* name, std::string path, int size) {
	queuedFonts.emplace_back(name, path, size);
}

inline void createFont(const char* name, std::string path, int size) {
	static int codepointsCount = 0;
	static int* codepoints = RAYLIB_FUNCTIONAL::LoadCodepoints(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ЁАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯёабвгдежзийклмнопрстуфхцчшщъыьэюя", &codepointsCount);
	Font ft = RAYLIB_FUNCTIONAL::LoadFontEx(path.c_str(), size, codepoints, codepointsCount);
	if (ft.texture.id) {
		GenTextureMipmaps(&ft.texture);
		SetTextureFilter(ft.texture, TEXTURE_FILTER_TRILINEAR);
		Fonts.emplace(name, ft);
	} else {
		UnloadFont(ft);
	}
}

class SUI_Text {
	std::string text;
	bool changed = false;
public:
	bool isChanged() const {
		return changed;
	}

	const std::string& operator!() const {
		return text;
	}

	size_t size() const {
		return text.size();
	}

	void restate() {
		changed = false;
	}

	bool empty() const {
		return text.empty();
	}

	const char* c_str() const {
		return text.c_str();
	}

	std::string substr(size_t from, size_t count = ((size_t)0 - 1)) const {
		return text.substr(from, count);
	}

	char operator[](size_t other) const {
		return text[other];
	}

	const SUI_Text& operator=(const std::string& other) {
		if (text.size() != other.size()) {
			changed = true;
		} else {
			changed = text != other;
		}

		text = other;
		return other;
	}

	const SUI_Text& operator=(const char* other) {
		std::string st = other;

		if (text.size() != st.size()) {
			changed = true;
		} else {
			changed = text != st;
		}

		text = st;
		return other;
	}

	const SUI_Text& operator=(const SUI_Text& other) {
		if (text.size() != other.size()) {
			changed = true;
		} else {
			changed = text != !other;
		}

		text = !other;
		return other;
	}

	void operator+=(const std::string& other) {
		text += other;

		if (other.size()) {
			changed = true;
		}
	}

	bool operator==(const std::string& other) {
		if (text.size() != other.size()) {
			return false;
		} else {
			return text == other;
		}
	}

	bool operator==(const char* other) {
		return !strcmp(text.c_str(), other);
	}

	bool operator!=(const char* other) {
		return strcmp(text.c_str(), other);
	}

	bool operator!=(const std::string& other) {
		if (text.size() == other.size()) {
			return text != other;
		} else {
			return true;
		}
	}

	bool operator==(const SUI_Text& other) {
		if (text.size() != other.size()) {
			return false;
		} else {
			return text == !other;
		}
	}

	operator std::string() {
		return text;
	}

	SUI_Text(const SUI_Text& other) {
		text = !other;
		changed = true;
	}

	SUI_Text(const std::string& other) {
		text = other;
		changed = true;
	}

	SUI_Text(const char* other) {
		text = other;
		changed = true;
	}
};

namespace Tasks {
	class Task;
	inline std::mutex TasksMutex;
	inline std::vector<Task*> ActiveTasks;

	class Task {
	public:
		float TimeLeft{};
		std::function<void(void)> Callback{};

		void Cancel() {
			TasksMutex.lock();
			auto obj = find(ActiveTasks.begin(), ActiveTasks.end(), this);
			if (obj != ActiveTasks.end()) {
				ActiveTasks.erase(obj);
			}
			TasksMutex.unlock();
			delete this;
		}

		Task(float TimeInSeconds, std::function<void(void)> f) : TimeLeft(TimeInSeconds), Callback(f) {
			TasksMutex.lock();
			ActiveTasks.push_back(this);
			TasksMutex.unlock();
		}
		~Task() {}
	};

	inline Task* Create(float TimeInSeconds, std::function<void(void)> f) {
		Task* t = new Task(TimeInSeconds, f);

		return t;
	}

	inline void UpdateTasks(float dt) {
		TasksMutex.lock();
		for (int i = 0; i < ActiveTasks.size();) {
			if (ActiveTasks[i]->TimeLeft <= 0) {
				ActiveTasks[i]->Callback();
				delete ActiveTasks[i];

				ActiveTasks.erase(ActiveTasks.begin() + i);
			} else {
				ActiveTasks[i]->TimeLeft -= dt;
				i++;
			}
		}
		TasksMutex.unlock();
	}
}

struct IChangedSignal {
	virtual ~IChangedSignal() = default;
	virtual void Update() = 0;
};

inline std::vector<IChangedSignal*> ActiveSignals;
template <typename T>
class ChangedSignal : IChangedSignal {
public:
	std::string SignalClass = "~";

	void Update() {
		if (*SignalPTR != *LastValue) {
			Callback();
			delete LastValue;
			LastValue = new T(*SignalPTR);
		}
	}
private:
	T* SignalPTR = nullptr;
	T* LastValue;
	std::function<void(void)> Callback;
public:
	void Disconnect() {
		auto z = find(ActiveSignals.begin(), ActiveSignals.end(), this);
		if (z != ActiveSignals.end()) ActiveSignals.erase(z);
		delete this;
	}

	ChangedSignal() = delete;
	ChangedSignal(T& p, std::function<void(void)> func) : SignalPTR(&p), Callback(func), SignalClass(typeid(T).name()) {
		ActiveSignals.push_back(this);
		LastValue = new T(p);
	}
	~ChangedSignal() {
		if (!LastValue) return;
		delete LastValue;
	}
};

template <typename T>
class AtomicChangedSignal : IChangedSignal {
public:
	std::string SignalClass = "~";

	void Update() {
		if (SignalPTR.load() != *LastValue.load()) {
			Callback();
			delete LastValue.load();
			LastValue.store(new T(SignalPTR.load()));
		}
	}
private:
	std::atomic<T>& SignalPTR = nullptr;
	std::atomic<T*> LastValue;
	std::function<void(void)> Callback;
public:
	void Disconnect() {
		auto z = find(ActiveSignals.begin(), ActiveSignals.end(), this);
		if (z != ActiveSignals.end()) ActiveSignals.erase(z);
		delete this;
	}

	AtomicChangedSignal() = delete;
	AtomicChangedSignal(std::atomic<T>& p, std::function<void(void)> func) : SignalPTR(p), Callback(func), SignalClass(typeid(T).name()) {
		ActiveSignals.push_back(this);
		LastValue.store(new T(p.load()));
	}
	~AtomicChangedSignal() {
		if (!LastValue.load()) return;
		delete LastValue.load();
	}
};

enum EventType {
	TICK = 0,

	MOUSE_ENTER = 10,
	MOUSE_LEAVE = 11,
	MOUSE_CLICK = 12,
	MOUSE_HOLD_START = 13,
	MOUSE_HOLD_END = 14,

	CHILD_ADDED = 20,
	CHILD_REMOVED = 21,

	TEXT_CHANGED = 30
};

enum MouseButtonType {
	MOUSE_NONE = -1,
	MOUSE_LEFT = MOUSE_BUTTON_LEFT,
	MOUSE_RIGHT = MOUSE_BUTTON_RIGHT,
	MOUSE_MIDDLE = MOUSE_BUTTON_MIDDLE
};

namespace Animate {
	enum Function {
		Linear,

		Smooth,

		Quad,
		Cube,
		Quart,
		Quint,

		Sine,
		Circular,
		Exponential,

		Back,
		Bounce
	};

	enum Ease {
		In = 0,
		Out,
	};

	inline float getTime(Function f, Ease e, float t) {
		t = std::clamp(t, 0.0f, 1.0f);

		if (f == Linear) { return t; }

		if (f == Quad) {
			if (e == In) { return t * t; } else { float a = 1.0f - t; return 1.0f - a * a; }
		}

		if (f == Cube) {
			if (e == In) { return t * t * t; } else { float a = 1.0f - t; return 1.0f - a * a * a; }
		}

		if (f == Exponential) {
			const float k = 3.0f;

			if (e == In) {
				return (expf(k * t) - 1.0f) / (expf(k) - 1.0f);
			} else {
				return 1.0f - (expf(k * (1.0f - t)) - 1.0f) / (expf(k) - 1.0f);
			}
		}

		if (f == Sine) {
			if (e == In) { return 1.0f - cosf((PI * t) / 2.0f); } else { return sinf((PI * t) / 2.0f); }
		}

		if (f == Circular) {
			if (e == In) { return 1.0f - sqrtf(1.0f - t * t); } else { float a = t - 1.0f; return sqrtf(1.0f - a * a); }
		}

		if (f == Bounce) {
			auto bounceOut = [](float x) -> float {
				const float n1 = 7.5625f;
				const float d1 = 2.75f;

				if (x < 1.0f / d1) return n1 * x * x;
				else if (x < 2.0f / d1) { x -= 1.5f / d1; return n1 * x * x + 0.75f; } else if (x < 2.5f / d1) { x -= 2.25f / d1; return n1 * x * x + 0.9375f; } else { x -= 2.625f / d1; return n1 * x * x + 0.984375f; }
			};

			if (e == In) {
				return 1.0f - bounceOut(1.0f - t);
			} else {
				return bounceOut(t);
			}
		}

		return t;
	}

	class Animation;
	inline std::unordered_map<void*, Animation*> ActiveAnimations;

	inline void deleteCurrent(void* ptr) {
		auto an = ActiveAnimations.find(ptr);
		if (an != ActiveAnimations.end()) {
			delete an->second;
			ActiveAnimations.erase(an);
		}
	}

	class Animation {
		void* ptr = nullptr;
		Function func = Linear;
		Ease ease = In;
		float currentTime = 0.0f;
		float endTime = 0.0f;

		int startValueI{};
		int endValueI{};
		float startValueF{};
		float endValueF{};
		Color startValueC{};
		Color endValueC{};
		SpecialVector2::num_x startValueNX{};
		SpecialVector2::num_x startValueNY{};
		SpecialVector2::num_y endValueNX{};
		SpecialVector2::num_y endValueNY{};
		SpecialVector2 startValueV{};
		SpecialVector2 endValueV{};

		const char* type = "int";
	public:
		std::function<void(void)> Completed = []() {};

		bool Update() {
			currentTime += SIMPLEUI_GLOBAL::dt;
			if (currentTime >= endTime) {
				if (type == "int") { *(int*)ptr = endValueI; } else if (type == "float") { *(float*)ptr = endValueF; } else if (type == "color") { *(Color*)ptr = endValueC; } else if (type == "vector2") { *(SpecialVector2*)ptr = endValueV; } else if (type == "numx") { *(SpecialVector2::num_x*)ptr = endValueNX; } else if (type == "numy") { *(SpecialVector2::num_y*)ptr = endValueNY; }
				return true;
			}
			if (type == "int") { *(int*)ptr = sui_lerp(startValueI, endValueI, getTime(func, ease, currentTime / endTime)); } else if (type == "float") { *(float*)ptr = sui_lerp(startValueF, endValueF, getTime(func, ease, currentTime / endTime)); } else if (type == "color") { *(Color*)ptr = ColorLerp(startValueC, endValueC, getTime(func, ease, currentTime / endTime)); } else if (type == "vector2") { *(SpecialVector2*)ptr = SpecialVector2{ sui_lerp(startValueV.x, endValueV.x, getTime(func, ease, currentTime / endTime)), sui_lerp(startValueV.y, endValueV.y, getTime(func, ease, currentTime / endTime)) }; } else if (type == "numx") { *(SpecialVector2::num_x*)ptr = sui_lerp(startValueNX, endValueNX, getTime(func, ease, currentTime / endTime)); } else if (type == "numy") { *(SpecialVector2::num_y*)ptr = sui_lerp(startValueNY, endValueNY, getTime(func, ease, currentTime / endTime)); }
			return false;
		}

		Animation() = delete;
		Animation(int* ptr, float time, int endValue, const char* type, Function func = Linear, Ease ease = In) : type(type), startValueI(*ptr), endValueI(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(float* ptr, float time, float endValue, const char* type, Function func = Linear, Ease ease = In) : type(type), startValueF(*ptr), endValueF(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(Color* ptr, float time, Color endValue, const char* type, Function func = Linear, Ease ease = In) : type(type), startValueC(*ptr), endValueC(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(SpecialVector2* ptr, float time, SpecialVector2 endValue, const char* type, Function func = Linear, Ease ease = In) : type(type), startValueV(*ptr), endValueV(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(SpecialVector2::num_x* ptr, float time, float endValue, const char* type, Function func = Linear, Ease ease = In) : type(type), startValueNX(*ptr), endValueNX(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(SpecialVector2::num_y* ptr, float time, float endValue, const char* type, Function func = Linear, Ease ease = In) : type(type), startValueNY(*ptr), endValueNY(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
	};

	inline Animation* Create(int* ptr, float time, int endValue, Function func = Linear, Ease ease = In) {
		deleteCurrent((void*)ptr);
		Animation* s = new Animation(ptr, time, endValue, "int", func, ease);
		ActiveAnimations.insert({ ptr, s });
		return s;
	}
	inline Animation* Create(float* ptr, float time, float endValue, Function func = Linear, Ease ease = In) {
		deleteCurrent((void*)ptr);
		Animation* s = new Animation(ptr, time, endValue, "float", func, ease);
		ActiveAnimations.insert({ ptr, s });
		return s;
	}
	inline Animation* Create(Color* ptr, float time, Color endValue, Function func = Linear, Ease ease = In) {
		deleteCurrent((void*)ptr);
		Animation* s = new Animation(ptr, time, endValue, "color", func, ease);
		ActiveAnimations.insert({ ptr, s });
		return s;
	}
	inline Animation* Create(SpecialVector2* ptr, float time, SpecialVector2 endValue, Function func = Linear, Ease ease = In) {
		deleteCurrent((void*)ptr);
		Animation* s = new Animation(ptr, time, endValue, "vector2", func, ease);
		ActiveAnimations.insert({ ptr, s });
		return s;
	}
	inline Animation* Create(SpecialVector2::num_x* ptr, float time, float endValue, Function func = Linear, Ease ease = In) {
		deleteCurrent((void*)ptr);
		Animation* s = new Animation(ptr, time, endValue, "numx", func, ease);
		ActiveAnimations.insert({ ptr, s });
		return s;
	}
	inline Animation* Create(SpecialVector2::num_y* ptr, float time, float endValue, Function func = Linear, Ease ease = In) {
		deleteCurrent((void*)ptr);
		Animation* s = new Animation(ptr, time, endValue, "numy", func, ease);
		ActiveAnimations.insert({ ptr, s });
		return s;
	}

	inline void UpdateAnimations(float t) {
		for (auto it = ActiveAnimations.begin(); it != ActiveAnimations.end();) {
			if (it->second->Update()) {
				Animation* sas = it->second;
				it = ActiveAnimations.erase(it);
				sas->Completed();
				delete sas;
			} else {
				it++;
			}
		}
	}
};

enum class TextAnchorEnum {
	N = 0,
	NE = 1,
	E = 2,
	SE = 3,
	S = 4,
	SW = 5,
	W = 6,
	NW = 7,
	CENTER = 8,
};

inline SpecialVector2 getTextOffset(TextAnchorEnum anchor) {
	float offsetX{};
	float offsetY{};

	switch (anchor) {
	case TextAnchorEnum::N: { offsetX = 0.5; offsetY = 0; break; }
	case TextAnchorEnum::NE: { offsetX = 1; offsetY = 0; break; }
	case TextAnchorEnum::E: { offsetX = 1; offsetY = 0.5; break; }
	case TextAnchorEnum::SE: { offsetX = 1; offsetY = 1; break; }
	case TextAnchorEnum::S: { offsetX = 0.5; offsetY = 1; break; }
	case TextAnchorEnum::SW: { offsetX = 0; offsetY = 1; break; }
	case TextAnchorEnum::W: { offsetX = 0; offsetY = 0.5; break; }
	case TextAnchorEnum::NW: { offsetX = 0; offsetY = 0; break; }
	default: { offsetX = 0.5; offsetY = 0.5; };
	}

	return { offsetX, offsetY };
}

inline Vector3 getTextCFrame(const char* text, Font font, Rectangle rec, TextAnchorEnum anchor, int maxTextSize, int Spacing) {
	if (maxTextSize < 0 or maxTextSize > rec.height) maxTextSize = rec.height;

	int endX{};
	int endY{};
	float endSize = 1;
	float sizeMax = maxTextSize;
	SpecialVector2 textSize{};

	while (endSize < sizeMax) {
		float middle = (endSize + sizeMax + 1) / 2;
		textSize = MeasureTextEx(font, text, middle, Spacing);
		if (textSize.x <= rec.width and textSize.y <= rec.height) endSize = middle;
		else sizeMax = middle - 1;
	}

	if (endSize > maxTextSize) endSize = maxTextSize;
	SpecialVector2 ofst = getTextOffset(anchor);
	float offsetX = ofst.x;
	float offsetY = ofst.y;

	endX = offsetX * (rec.width - textSize.x); if (endX < 0) endX = 0;
	endY = offsetY * (rec.height - textSize.y);  if (endX < 0) endX = 0;

	return { (float)endX, (float)endY, (float)endSize };
}

enum InstanceType : int {
	INSTANCE = 0,

	OBJECT2D = 10,
	TEXTLABEL,
	TEXTBOX,
	IMAGELABEL,
	SCROLLFRAME,
	TEXTURELABEL,
	LINEEX,

	STRING_VALUE = 30,
	INT_VALUE,
	BOOL_VALUE,
	FLOAT_VALUE,
	OBJECT_VALUE,
	ADDRESS_VALUE,
	VECTOR2_VALUE,
	COLOR_VALUE,

	FOLDER = 40,

	// Additional classes from SUIextension.h
#ifndef EXCLUDE_SIMPLEUI_EXTENSION
	GRAPHBUILDER = 100,
	TOGGLESWITCHER,
	CHECKBOX,
	MULTICHECKBOX,
	COMBOBOX,
	DROPBOX,
	PROGRESSBAR
#endif
};

inline Instance* getAncestorWhichParentIsScrollFrame(Instance* ptr);
inline void Delete(Instance* ptr);
inline void updateChildren(Instance*);

template<typename F>
struct function_traits : function_traits<decltype(&F::operator())> {};

template<typename R, typename... Args>
struct function_traits<R(Args...)> {
	using result_type = R;
	static constexpr std::size_t arity = sizeof...(Args);

	template<std::size_t N>
	using arg = std::tuple_element_t<N, std::tuple<Args...>>;
};

template<typename R, typename... Args>
struct function_traits<R(*)(Args...)> : function_traits<R(Args...)> {};

template<typename C, typename R, typename... Args>
struct function_traits<R(C::*)(Args...)> : function_traits<R(Args...)> {};

template<typename C, typename R, typename... Args>
struct function_traits<R(C::*)(Args...) const> : function_traits<R(Args...)> {};

struct InstanceCallback {
	std::function<void(Instance*, Instance*)> func;

	InstanceCallback() = default;

	template<typename F, typename = std::enable_if_t<!std::is_same_v<std::decay_t<F>, InstanceCallback>>>
	InstanceCallback(F&& f) {
		if constexpr (std::is_invocable_v<F, Instance*, Instance*>) {
			func = std::forward<F>(f);
		} else if constexpr (std::is_invocable_v<F, Instance*>) {
			func = [f = std::forward<F>(f)](Instance* a, Instance*) mutable {
				f(a);
			};
		} else {
			std::string t = typeid(typename function_traits<std::decay_t<F>>::template arg<0>).name();
			std::cout << RED_ANSI << "Can't create function (" << t << "), expected types: (Instance*, ?Instance*)" << DEFAULT_ANSI << std::endl;
		}
	}

	void operator()(Instance* a, Instance* b = nullptr) const {
		if (func) {
			func(a, b);
		}
	}
};

class Instance {
	friend void Delete(Instance* ptr);
protected:
	size_t lastUpdateFrame = 0;
	bool updateWhenWillBeVisible = true;
	bool __ParentObject{};

	virtual void basicCloneOperation(Instance* copyfrom) {
		this->Parent = nullptr;
		this->Children.clear();
		this->childsRemovedInFrame.clear();
		this->childsAddedInFrame.clear();
		updateWhenWillBeVisible = true;
		SIMPLEUI_GLOBAL::sceneDirty = true;

		this->uniqueID = SIMPLEUI_GLOBAL::currentUniqueObjectID++;
		SIMPLEUI_GLOBAL::deletedObjectsByID.push_back(0);

		if (!copyfrom) return;

		for (Instance* c : copyfrom->Children) {
			c->Clone()->setParent(this);
		}
	}

	Instance(bool a) : __ParentObject(true), uniqueID(SIMPLEUI_GLOBAL::currentUniqueObjectID++) { SIMPLEUI_GLOBAL::deletedObjectsByID.push_back(0); };
	Instance(Instance* p);
	Instance() = delete;
	virtual ~Instance() {}
private:
	std::vector<std::pair<EventType, InstanceCallback>> events;
public:
	long uniqueID = -1;
	std::unordered_map<long, Instance*> childsAddedInFrame;
	std::unordered_map<long, Instance*> childsRemovedInFrame;
	void AddEvent(EventType t, InstanceCallback f, MouseButtonType m);

	bool hasEvent(EventType t) const {
		for (auto& [type, _] : events) {
			if (type == t) {
				return true;
			}
		}

		return false;
	}

	bool updateChildrenZIndex = true;

	Instance* Parent = nullptr;
	std::vector<Instance*> Children;

	std::string Name = "Instance";
	InstanceType Class = InstanceType::INSTANCE;

	void setParent(Instance* ptr);

	Instance* findChild(const std::string& name) const {
		for (auto obj : Children) {
			if (obj->Name == name) {
				return obj;
			}
		}

		return nullptr;
	}

	Instance* findChildOfClass(InstanceType cls) {
		for (Instance*& obj : Children) {
			if (obj->Class == cls) {
				return obj;
			}
		}

		return nullptr;
	}

	bool isAncestorOf(Instance* other) const {
		Instance* ptr = other;

		while (ptr->Parent != nullptr and !ptr->__ParentObject) {
			if (ptr->Parent == this) return true;
			ptr = ptr->Parent;
		}

		return false;
	}

	Instance* findFirstAncestorOfClass(InstanceType cls) {
		Instance* ptr = this;

		while (ptr->Parent != nullptr and !ptr->__ParentObject) {
			if (ptr->Parent->Class == cls) return ptr->Parent;
			ptr = ptr->Parent;
		}

		return nullptr;
	}

	Instance* findFirstDescendantOfClass(InstanceType cls) {
		std::function<Instance* (Instance*)> l = [=](Instance* ptr) -> Instance* {
			for (Instance* child : ptr->Children) {
				if (child->Class == cls) {
					return child;
				}

				Instance* res = l(child);

				if (res) {
					return res;
				}
			}

			return nullptr;
		};

		return l(this);
	}

	Instance* findFirstDescendant(const std::string& name) {
		std::function<Instance* (Instance*)> l;

		l = [&](Instance* ptr) -> Instance* {
			for (Instance* child : ptr->Children) {
				if (child->Name == name) {
					return child;
				}

				Instance* res = l(child);

				if (res) {
					return res;
				}
			}

			return nullptr;
		};

		return l(this);
	}

	std::vector<Instance*> getDescendants(const std::function<bool(Instance*)>& condition = [](Instance* _) { return true; }) {
		std::vector<Instance*> out;

		std::function<void(Instance*)> l = [&](Instance* ptr) {
			for (Instance* child : ptr->Children) {
				if (condition(child)) {
					out.push_back(child);
				}

				l(child);
			}
		};

		l(this);

		return out;
	}

	void deleteAllChildren() {
		while (Children.size() > 0) {
			Delete(Children[0]);
		}
	}

	bool isDescendantOf(Instance* maybeAncestor) const {
		const Instance* ptr = this;

		while (ptr->Parent != nullptr and !ptr->__ParentObject) {
			if (ptr->Parent == maybeAncestor) return true;
			ptr = ptr->Parent;
		}

		return false;
	}

	virtual void eventHandler() {
		if (events.empty()) return;

		for (const auto& [type, func] : events) {
			if (type == TICK) {
				func(this);
			} else if (type == CHILD_ADDED) {
				for (auto& [id, ptr] : childsAddedInFrame) {
					func(this, ptr);
				}
			} else if (type == CHILD_REMOVED) {
				for (auto& [id, ptr] : childsRemovedInFrame) {
					func(this, ptr);
				}
			}
		}

		childsAddedInFrame.clear();
		childsRemovedInFrame.clear();
	}

	void SetSizePosUpdateFlag() {
		updateWhenWillBeVisible = true;
	}

	virtual void Update(bool posOrSizeChanged) {
		if (lastUpdateFrame == SIMPLEUI_GLOBAL::framesSinceStart) return;
		lastUpdateFrame = SIMPLEUI_GLOBAL::framesSinceStart;

		if (updateChildrenZIndex) {
			updateChildren(this);
		}

		eventHandler();
		if (SIMPLEUI_GLOBAL::deletedObjectsByID[uniqueID]) return;

		for (int i = 0; i < Children.size(); i++) {
			Instance* child = Children[i];
			child->Update(posOrSizeChanged or updateWhenWillBeVisible);
		}

		updateWhenWillBeVisible = false;
	}

	static Instance* New(Instance* parent = nullptr) {
		Instance* i = new Instance(parent);
		return i;
	}

	void Destroy() {
		Delete(this);
	}

	virtual Instance* Clone() const {
		Instance* i = new Instance(*this);
		i->basicCloneOperation(const_cast<Instance*>(this));

		return i;
	}
};

// Create or get root object. It always a default Instance named "Root"
inline Instance* GetRoot() {
	static Instance* root = nullptr;
	if (!root) {
		root = Instance::New(nullptr);
		root->Name = "Root";
	}
	return root;
}

inline Instance* getAncestorWhichParentIsScrollFrame(Instance* ptr) {
	while (ptr->Parent != nullptr) {
		if (ptr->Parent->Class == SCROLLFRAME) return ptr;
		ptr = ptr->Parent;
	}

	return nullptr;
}

inline bool Is2DInheritor(InstanceType type) {
	if (type == INSTANCE or
		type == LINEEX or
		type == STRING_VALUE or
		type == BOOL_VALUE or
		type == VECTOR2_VALUE or
		type == INT_VALUE or
		type == FLOAT_VALUE or
		type == OBJECT_VALUE or
		type == ADDRESS_VALUE or
		type == COLOR_VALUE or
		type == FOLDER
		) {
		return false;
	}

	return true;
}

inline bool Is2DInheritor(Instance* obj) {
	return Is2DInheritor(obj->Class);
}

class StringValue : public Instance {
	constexpr static const char* DefaultName = "StringValue";
	constexpr static InstanceType DefaultClass = STRING_VALUE;
protected:
	StringValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	StringValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	StringValue() = delete;
	~StringValue() override = default;
public:
	std::string Value = "";

	StringValue* Clone() const {
		StringValue* i = new StringValue(*this);
		i->basicCloneOperation(const_cast<StringValue*>(this));

		return i;
	}

	static StringValue* New(Instance* parent = nullptr) {
		StringValue* i = new StringValue(parent);
		return i;
	}
};

class ObjectValue : public Instance {
	constexpr static const char* DefaultName = "ObjectValue";
	constexpr static InstanceType DefaultClass = OBJECT_VALUE;
protected:
	ObjectValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	ObjectValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	ObjectValue() = delete;
	~ObjectValue() override = default;
public:
	Instance* Value = nullptr;

	ObjectValue* Clone() const {
		ObjectValue* i = new ObjectValue(*this);
		i->basicCloneOperation(const_cast<ObjectValue*>(this));

		return i;
	}

	static ObjectValue* New(Instance* parent = nullptr) {
		ObjectValue* i = new ObjectValue(parent);
		return i;
	}
};

template<typename T>
class AddressValue : public Instance {
	constexpr static const char* DefaultName = "AddressValue";
	constexpr static InstanceType DefaultClass = ADDRESS_VALUE;
protected:
	AddressValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	AddressValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	AddressValue() = delete;
	~AddressValue() override = default;
public:
	T* Value = nullptr;

	AddressValue* Clone() const {
		AddressValue* i = new AddressValue(*this);
		i->basicCloneOperation(const_cast<AddressValue*>(this));

		return i;
	}

	static AddressValue* New(Instance* parent = nullptr) {
		AddressValue* i = new AddressValue(parent);
		return i;
	}
};

class BoolValue : public Instance {
	constexpr static const char* DefaultName = "BoolValue";
	constexpr static InstanceType DefaultClass = BOOL_VALUE;
protected:
	BoolValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	BoolValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	BoolValue() = delete;
	~BoolValue() override = default;
public:
	bool Value = 0;

	BoolValue* Clone() const {
		BoolValue* i = new BoolValue(*this);
		i->basicCloneOperation(const_cast<BoolValue*>(this));

		return i;
	}

	static BoolValue* New(Instance* parent = nullptr) {
		BoolValue* i = new BoolValue(parent);
		return i;
	}
};

class IntValue : public Instance {
	constexpr static const char* DefaultName = "IntValue";
	constexpr static InstanceType DefaultClass = INT_VALUE;
protected:
	IntValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	IntValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	IntValue() = delete;
	~IntValue() override = default;
public:
	int Value = 0;

	IntValue* Clone() const {
		IntValue* i = new IntValue(*this);
		i->basicCloneOperation(const_cast<IntValue*>(this));

		return i;
	}

	static IntValue* New(Instance* parent = nullptr) {
		IntValue* i = new IntValue(parent);
		return i;
	}
};

class FloatValue : public Instance {
	constexpr static const char* DefaultName = "FloatValue";
	constexpr static InstanceType DefaultClass = FLOAT_VALUE;
protected:
	FloatValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	FloatValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	FloatValue() = delete;
	~FloatValue() override = default;
public:
	float Value = 0.0f;

	FloatValue* Clone() const {
		FloatValue* i = new FloatValue(*this);
		i->basicCloneOperation(const_cast<FloatValue*>(this));

		return i;
	}

	static FloatValue* New(Instance* parent = nullptr) {
		FloatValue* i = new FloatValue(parent);
		return i;
	}
};

class Vector2Value : public Instance {
	constexpr static const char* DefaultName = "Vector2Value";
	constexpr static InstanceType DefaultClass = VECTOR2_VALUE;
protected:
	Vector2Value(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	Vector2Value(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	Vector2Value() = delete;
	~Vector2Value() override = default;
public:
	SpecialVector2 Value = { 0,0 };

	Vector2Value* Clone() const {
		Vector2Value* i = new Vector2Value(*this);
		i->basicCloneOperation(const_cast<Vector2Value*>(this));

		return i;
	}

	static Vector2Value* New(Instance* parent = nullptr) {
		Vector2Value* i = new Vector2Value(parent);
		return i;
	}
};

class ColorValue : public Instance {
	constexpr static const char* DefaultName = "ColorValue";
	constexpr static InstanceType DefaultClass = COLOR_VALUE;
protected:
	ColorValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	ColorValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	ColorValue() = delete;
	~ColorValue() override = default;
public:
	Color Value = { 255,255,255,255 };

	ColorValue* Clone() const {
		ColorValue* i = new ColorValue(*this);
		i->basicCloneOperation(const_cast<ColorValue*>(this));

		return i;
	}

	static ColorValue* New(Instance* parent = nullptr) {
		ColorValue* i = new ColorValue(parent);
		return i;
	}
};

class Folder : public Instance {
	constexpr static const char* DefaultName = "Folder";
	constexpr static InstanceType DefaultClass = FOLDER;
protected:
	Folder(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	Folder(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	Folder() = delete;
	~Folder() override = default;
public:
	Folder* Clone() const {
		Folder* i = new Folder(*this);
		i->basicCloneOperation(const_cast<Folder*>(this));

		return i;
	}

	static Folder* New(Instance* parent = nullptr) {
		Folder* i = new Folder(parent);
		return i;
	}
};

inline SpecialVector2 getCanvasRealPos(Object2D*);
inline SpecialVector2 getScrollFrameRS(Instance*);
inline SpecialVector2 getScrollFrameRP(Instance*);
inline bool isScrollFrameCropping(Instance*);

enum SUI_EEC {
	EEC_DEFAULT = 0, // Entered if current object is highest by ZIndex on mouse
	EEC_EVERY_ENTER, // Entered if current object on mouse
	EEC_IF_DESCENDANT_HIGHER // Entered if current object is ancestor of highest ZIndex object on mouse
};

inline void DrawRoundRectBatch(const RoundRectData& r) {
	SIMPLEUI_GLOBAL::CurrentCustomShader = SIMPLEUI_GLOBAL::RectangleRoundnessShader;
	if (r.Texture.id) {
		auto& cur = SIMPLEUI_GLOBAL::CurrentBatchTexture;
		if (cur and cur != r.Texture.id) FlushRectanglesBatch();
		cur = r.Texture.id;
	}
	SIMPLEUI_GLOBAL::CurrentRectanglesBatch.push_back(r);
}

struct RectVertex {
	float x, y, z;
	float lx, ly, hx, hy;
	float u, v, useTex;
	unsigned char r, g, b, a;
};

namespace RectGPU {
	constexpr int MaxQuads = 16384;
	inline unsigned int vao = 0;
	inline unsigned int vbo = 0;
	inline std::vector<RectVertex> verts;

	inline void Init() {
		std::vector<unsigned short> idx(MaxQuads * 6);
		for (int i = 0; i < MaxQuads; i++) {
			unsigned short b = (unsigned short)(i * 4);
			idx[i * 6 + 0] = b;
			idx[i * 6 + 1] = b + 1;
			idx[i * 6 + 2] = b + 3;
			idx[i * 6 + 3] = b + 1;
			idx[i * 6 + 4] = b + 2;
			idx[i * 6 + 5] = b + 3;
		}

		vao = RAYLIB_FUNCTIONAL::rlLoadVertexArray();
		RAYLIB_FUNCTIONAL::rlEnableVertexArray(vao);

		vbo = RAYLIB_FUNCTIONAL::rlLoadVertexBuffer(nullptr, MaxQuads * 4 * (int)sizeof(RectVertex), true);
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_POSITION, 3, RL_FLOAT, false, (int)sizeof(RectVertex), offsetof(RectVertex, x));
		RAYLIB_FUNCTIONAL::rlEnableVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_POSITION);
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD, 2, RL_FLOAT, false, (int)sizeof(RectVertex), offsetof(RectVertex, u));
		RAYLIB_FUNCTIONAL::rlEnableVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD);
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_COLOR, 4, RL_UNSIGNED_BYTE, true, (int)sizeof(RectVertex), offsetof(RectVertex, r));
		RAYLIB_FUNCTIONAL::rlEnableVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_COLOR);
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD, 4, RL_FLOAT, false, (int)sizeof(RectVertex), offsetof(RectVertex, lx));
		RAYLIB_FUNCTIONAL::rlEnableVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD);
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD2, 3, RL_FLOAT, false, (int)sizeof(RectVertex), offsetof(RectVertex, u));
		RAYLIB_FUNCTIONAL::rlEnableVertexAttribute(RL_DEFAULT_SHADER_ATTRIB_LOCATION_TEXCOORD2);

		RAYLIB_FUNCTIONAL::rlLoadVertexBufferElement(idx.data(), (int)(idx.size() * sizeof(unsigned short)), false);

		RAYLIB_FUNCTIONAL::rlDisableVertexArray();
	}

	inline RAYLIB_FUNCTIONAL::Matrix Mul(const RAYLIB_FUNCTIONAL::Matrix& l, const RAYLIB_FUNCTIONAL::Matrix& r) {
		RAYLIB_FUNCTIONAL::Matrix out;
		const float* a = &l.m0;
		const float* b = &r.m0;
		float* o = &out.m0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				o[4 * i + j] = a[4 * i] * b[j] + a[4 * i + 1] * b[4 + j] + a[4 * i + 2] * b[8 + j] + a[4 * i + 3] * b[12 + j];
			}
		}
		return out;
	}

	struct QuadTex {
		Rectangle dest = { 0, 0, 0, 0 };
		float u0 = 0, v0 = 0, u1 = 0, v1 = 0;
		float use = 0;
	};

	inline void PushQuad(Vector2 pos, Vector2 size, float roundness, float borderThickness, Color c, float rotation, Vector2 origin, const QuadTex& t) {
		float halfW = size.x * 0.5f;
		float halfH = size.y * 0.5f;
		float cx = pos.x + halfW;
		float cy = pos.y + halfH;
		float ox = pos.x + origin.x;
		float oy = pos.y + origin.y;
		float sn = sinf(rotation * DEG2RAD);
		float cs = cosf(rotation * DEG2RAD);
		float z = floorf(borderThickness) + std::clamp(roundness, 0.0f, 1.0f) * 0.99f;

		float x0, y0, x1, y1;
		if (t.use > 0.5f) {
			x0 = t.dest.x - cx;
			y0 = t.dest.y - cy;
			x1 = x0 + t.dest.width;
			y1 = y0 + t.dest.height;
		} else {
			x0 = -halfW - 1.0f;
			y0 = -halfH - 1.0f;
			x1 = halfW + 1.0f;
			y1 = halfH + 1.0f;
		}

		auto corner = [&](float lx, float ly, float fx, float fy) {
			float dx = cx + lx - ox;
			float dy = cy + ly - oy;
			verts.push_back({
				ox + dx * cs - dy * sn, oy + dx * sn + dy * cs, z,
				lx, ly, halfW, halfH,
				t.u0 + (t.u1 - t.u0) * fx, t.v0 + (t.v1 - t.v0) * fy, t.use,
				c.r, c.g, c.b, c.a
			});
		};

		corner(x0, y0, 0, 0);
		corner(x0, y1, 0, 1);
		corner(x1, y1, 1, 1);
		corner(x1, y0, 1, 0);
	}
}

inline void FlushRectanglesBatch() {
	auto& batch = SIMPLEUI_GLOBAL::CurrentRectanglesBatch;
	if (batch.empty()) return;

	static Shader shader = getShader(SIMPLEUI_GLOBAL::RectangleRoundnessShader);
	if (!RectGPU::vao) RectGPU::Init();

	auto& v = RectGPU::verts;
	v.clear();
	v.reserve(batch.size() * 8);

	for (const auto& r : batch) {
		RectGPU::QuadTex qt;
		if (r.Texture.id) {
			Rectangle s = r.Source;
			if (s.width < 0) s.x -= s.width;
			if (s.height < 0) s.y -= s.height;
			float tw = (float)r.Texture.width;
			float th = (float)r.Texture.height;
			qt.dest = r.Destination;
			qt.u0 = s.x / tw;
			qt.v0 = s.y / th;
			qt.u1 = (s.x + s.width) / tw;
			qt.v1 = (s.y + s.height) / th;
			qt.use = 1.0f;
		}

		unsigned char fillA = (unsigned char)(r.Color.a * (1 - r.Transparency));
		if (fillA) {
			RectGPU::PushQuad(r.Pos, r.Size, r.Roundness, 0.0f, { r.Color.r, r.Color.g, r.Color.b, fillA }, r.Rotation, r.Origin, qt);
		}

		unsigned char borderA = (unsigned char)(r.BorderColor.a * (1 - r.BorderTransparency));
		if (r.BorderThickness > 0 and borderA) {
			RectGPU::PushQuad(r.Pos, r.Size, r.Roundness, (float)r.BorderThickness, { r.BorderColor.r, r.BorderColor.g, r.BorderColor.b, borderA }, r.Rotation, r.Origin, RectGPU::QuadTex{});
		}
	}

	if (!v.empty()) {
		RAYLIB_FUNCTIONAL::rlDrawRenderBatchActive();
		RAYLIB_FUNCTIONAL::rlEnableShader(shader.id);

		RAYLIB_FUNCTIONAL::rlSetUniformMatrix(shader.locs[RAYLIB_FUNCTIONAL::SHADER_LOC_MATRIX_MVP], RectGPU::Mul(RAYLIB_FUNCTIONAL::rlGetMatrixModelview(), RAYLIB_FUNCTIONAL::rlGetMatrixProjection()));

		int diffuseLoc = shader.locs[RAYLIB_FUNCTIONAL::SHADER_LOC_COLOR_DIFFUSE];
		if (diffuseLoc >= 0) {
			float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			RAYLIB_FUNCTIONAL::rlSetUniform(diffuseLoc, white, RAYLIB_FUNCTIONAL::RL_SHADER_UNIFORM_VEC4, 1);
		}

		unsigned int texId = SIMPLEUI_GLOBAL::CurrentBatchTexture ? SIMPLEUI_GLOBAL::CurrentBatchTexture : RAYLIB_FUNCTIONAL::rlGetTextureIdDefault();
		RAYLIB_FUNCTIONAL::rlActiveTextureSlot(0);
		RAYLIB_FUNCTIONAL::rlEnableTexture(texId);

		size_t totalQuads = v.size() / 4;
		size_t done = 0;
		while (done < totalQuads) {
			int n = (int)std::min<size_t>(RectGPU::MaxQuads, totalQuads - done);
			RAYLIB_FUNCTIONAL::rlUpdateVertexBuffer(RectGPU::vbo, v.data() + done * 4, n * 4 * (int)sizeof(RectVertex), 0);
			RAYLIB_FUNCTIONAL::rlEnableVertexArray(RectGPU::vao);
			RAYLIB_FUNCTIONAL::rlDrawVertexArrayElements(0, n * 6, nullptr);
			done += n;
		}

		RAYLIB_FUNCTIONAL::rlDisableVertexArray();
		RAYLIB_FUNCTIONAL::rlDisableTexture();
	}

	batch.clear();
	SIMPLEUI_GLOBAL::CurrentBatchTexture = 0;
}

class Object2D : public Instance {
	constexpr static const char* DefaultName = "Object2D";
	constexpr static InstanceType DefaultClass = OBJECT2D;

	bool startedOnObject1 = false;
	bool startedOnObject2 = false;
	bool startedOnObject3 = false;

	bool lastActive = Active;
	int lastZIndex = ZIndex;
protected:
	bool posOrSizeChangedResult = false;
	std::vector<std::tuple<EventType, InstanceCallback, MouseButtonType>> events;

	void SameUpdate() {
		if (Active != lastActive or lastZIndex != ZIndex) {
			lastActive = Active;
			lastZIndex = ZIndex;

			if (Parent) {
				Parent->updateChildrenZIndex = true;
			}
		}

		childsRemovedInFrame.clear();
		childsAddedInFrame.clear();
	}

	void eventHandler() override;
	void PosOrSizeChanged();
	void updateAncestorWhichParentIsScroll();

	// Updating parent pointer in SpecialVector2 (after cloning)
	void UpdateAllVectorPointers() {
		PositionOFFSET.parentalObj = this;
		AnchorPositionOFFSET.parentalObj = this;
		Position.parentalObj = this;
		AnchorPosition.parentalObj = this;
		Size.parentalObj = this;
		SizeOFFSET.parentalObj = this;

		lastUpdateFrame = SIMPLEUI_GLOBAL::framesSinceStart - 1;
	}

	Object2D(bool a) : Instance(a) { 
		Name = DefaultName;
		Class = DefaultClass;

		updateAncestorWhichParentIsScroll();
	};

	Object2D(Instance* p) : Instance(p) { 
		Name = DefaultName;
		Class = DefaultClass;

		updateAncestorWhichParentIsScroll();
	}

	Object2D() = delete;
	~Object2D() override = default;
public:
	void VectorChanged() {
		PosOrSizeChanged();
	}

	bool hasEvent(EventType t) const {
		for (auto& [type, _, __] : events) {
			if (type == t) {
				return true;
			}
		}

		return false;
	}

	SpecialVector2 RealSize{}; // Absolute size in pixels (not for changing from somewhere)
	SpecialVector2 RealPos{}; // Absolute position in pixels (not for changing from somewhere)
	SUI_EEC EnterEventCondition = SUI_EEC::EEC_DEFAULT;

	SpecialVector2 PositionOFFSET{ 0, 0, this };
	SpecialVector2 AnchorPositionOFFSET{ 0, 0, this };
	SpecialVector2 Position{ 0, 0, this };
	SpecialVector2 AnchorPosition{ 0, 0, this };

	SpecialVector2 Size{ 0, 0, this };
	SpecialVector2 SizeOFFSET{ 0, 0, this };

	float Rotation = 0; // WIP
	SpecialVector2 Origin = { 0,0 }; // WIP

	float BackgroundTransparency{};
	Color BackgroundColor = { 255,255,255,255 };
	bool Visible = true;

	float Roundness = 0.0f;
	short Segments = 5; // Deprecated value, now simpleUI using SDF for corners

	short BorderThickness{};
	float BorderTransparency{};
	Color BorderColor{};

	int ZIndex = 0;
	bool Active = false;

	void getRealObject2Dsize() {
		SpecialVector2 sizePx = {};
		Object2D* self = this;
		Instance* current = Parent;
		Object2D* parent2D = nullptr;

		while (current) {
			if (!Is2DInheritor(current->Class)) {
				if (current->Parent) { current = current->Parent; continue; }
				parent2D = nullptr;
				break;
			}
			parent2D = static_cast<Object2D*>(current);

			if (parent2D->__ParentObject) {
				parent2D = nullptr;
			}

			break;
		}

		SpecialVector2 parentSizePx = parent2D ? parent2D->RealSize : SpecialVector2{ static_cast<float>(SIMPLEUI_GLOBAL::winWidth), static_cast<float>(SIMPLEUI_GLOBAL::winHeight) };

		sizePx.x = std::roundf(parentSizePx.x * self->Size.x + self->SizeOFFSET.x);
		sizePx.y = std::roundf(parentSizePx.y * self->Size.y + self->SizeOFFSET.y);

		RealSize = sizePx;
	}

	void getRealObject2Dposition() {
		SpecialVector2 posPx = { 0.0f, 0.0f };
		SpecialVector2 sizePx = RealSize;

		SpecialVector2 anchorPx = {
			std::roundf(sizePx.x * AnchorPosition.x + AnchorPositionOFFSET.x),
			std::roundf(sizePx.y * AnchorPosition.y + AnchorPositionOFFSET.y)
		};

		Instance* current = Parent;
		while (current) {
			if (!Is2DInheritor(current)) { current = current->Parent; continue; }

			Object2D* obj = static_cast<Object2D*>(current);

			SpecialVector2 parentSizePx = obj->RealSize;

			SpecialVector2 parentAnchorPx = {
				std::roundf(obj->RealSize.x * obj->AnchorPosition.x + obj->AnchorPositionOFFSET.x),
				std::roundf(obj->RealSize.y * obj->AnchorPosition.y + obj->AnchorPositionOFFSET.y)
			};

			SpecialVector2 parentLocalPx = {
				std::roundf(obj->Position.x * parentSizePx.x + obj->PositionOFFSET.x - parentAnchorPx.x),
				std::roundf(obj->Position.y * parentSizePx.y + obj->PositionOFFSET.y - parentAnchorPx.y)
			};

			SpecialVector2 parentPosPx = obj->RealPos;

			SpecialVector2 myLocalPx = {
				std::roundf(parentSizePx.x * Position.x + PositionOFFSET.x - anchorPx.x),
				std::roundf(parentSizePx.y * Position.y + PositionOFFSET.y - anchorPx.y)
			};

			if (obj->Class == SCROLLFRAME) {
				SpecialVector2 canvasPx = getCanvasRealPos(obj);
				posPx.x = std::roundf(parentPosPx.x + myLocalPx.x - canvasPx.x);
				posPx.y = std::roundf(parentPosPx.y + myLocalPx.y - canvasPx.y);
			} else {
				posPx.x = std::roundf(parentPosPx.x + myLocalPx.x);
				posPx.y = std::roundf(parentPosPx.y + myLocalPx.y);
			}

			RealPos = posPx;
			return;
		}

		SpecialVector2 rootSizePx = { static_cast<float>(SIMPLEUI_GLOBAL::winWidth), static_cast<float>(SIMPLEUI_GLOBAL::winHeight) };
		SpecialVector2 rootLocalPx = {
			std::roundf(rootSizePx.x * Position.x + PositionOFFSET.x - anchorPx.x),
			std::roundf(rootSizePx.y * Position.y + PositionOFFSET.y - anchorPx.y)
		};

		RealPos = rootLocalPx;
	}

	SpecialVector2 getMousePosition() {
		SpecialVector2 mousePos = SIMPLEUI_GLOBAL::mousePosition;
		return { (mousePos.x - RealPos.x) / RealSize.x, (mousePos.y - RealPos.y) / RealSize.y };
	}

	virtual void Draw() {
		if (Visible) {
			if (RealPos.x + RealSize.x + BorderThickness < 0
				or RealPos.x - BorderThickness > SIMPLEUI_GLOBAL::winWidth
				or RealPos.y + RealSize.y + BorderThickness < 0
				or RealPos.y - BorderThickness > SIMPLEUI_GLOBAL::winHeight) {
				return;
			}

			const RoundRectData rec = { RealPos, RealSize, BackgroundColor, BorderColor, BackgroundTransparency, Roundness, BorderTransparency, BorderThickness, Rotation, {Origin.x * RealSize.x, Origin.y * RealSize.y} };

			DrawRoundRectBatch(rec);
		}
	}

	bool pointInObject(SpecialVector2 pos) {
		SpecialVector2 mouse = SIMPLEUI_GLOBAL::mouseScreenPosition;
		SpecialVector2 windowPos = SIMPLEUI_GLOBAL::windowPosition;

		int width = SIMPLEUI_GLOBAL::winWidth;
		int height = SIMPLEUI_GLOBAL::winHeight;

		if (!(mouse.x >= windowPos.x and
			mouse.x <= windowPos.x + width and
			mouse.y >= windowPos.y and
			mouse.y <= windowPos.y + height)) return false;

		if (Parent and Parent->Class == SCROLLFRAME and isScrollFrameCropping(Parent)) {
			SpecialVector2 scrRS = getScrollFrameRS(Parent);
			SpecialVector2 scrRP = getScrollFrameRP(Parent);
			if (scrRP.x > pos.x or scrRP.x + scrRS.x < pos.x or
				scrRP.y > pos.y or scrRP.y + scrRS.y < pos.y) {
				return false;
			}
		}

		float px = pos.x;
		float py = pos.y;

		if (Rotation != 0.0f) {
			float ox = RealPos.x + Origin.x * RealSize.x;
			float oy = RealPos.y + Origin.y * RealSize.y;
			float sn = sinf(Rotation * DEG2RAD);
			float cs = cosf(Rotation * DEG2RAD);
			float dx = pos.x - ox;
			float dy = pos.y - oy;
			px = ox + dx * cs + dy * sn;
			py = oy - dx * sn + dy * cs;
		}

		return px >= RealPos.x and px <= RealPos.x + RealSize.x and
			py >= RealPos.y and py <= RealPos.y + RealSize.y;
	}

	bool MouseEntered = false; // works with MOUSE_ENTER MOUSE_LEAVE events

	void AddEvent(EventType t, InstanceCallback f, MouseButtonType m = MouseButtonType::MOUSE_NONE);

	void Update(bool posOrSizeChanged) override {
		if (lastUpdateFrame == SIMPLEUI_GLOBAL::framesSinceStart) return;
		lastUpdateFrame = SIMPLEUI_GLOBAL::framesSinceStart;

		eventHandler();
		if (SIMPLEUI_GLOBAL::deletedObjectsByID[uniqueID]) return;

		if (!Visible) {
			if (posOrSizeChanged or posOrSizeChangedResult) updateWhenWillBeVisible = true;
			return;
		}

		SameUpdate();

		if (updateChildrenZIndex) {
			updateChildren(this);
		}

		if (posOrSizeChanged or posOrSizeChangedResult or updateWhenWillBeVisible) {
			getRealObject2Dsize();
			getRealObject2Dposition();
		}

		Draw();

		bool tempRes = posOrSizeChanged or posOrSizeChangedResult or updateWhenWillBeVisible;
		posOrSizeChangedResult = false;
		updateWhenWillBeVisible = false;

		for (int i = 0; i < Children.size(); i++) {
			Instance* child = Children[i];
			child->Update(tempRes);
		}
	}

	Object2D* Clone() const override {
		Object2D* i = new Object2D(*this);
		i->UpdateAllVectorPointers();
		i->posOrSizeChangedResult = true;

		i->basicCloneOperation(const_cast<Object2D*>(this));

		return i;
	}

	static Object2D* New(Instance* parent = nullptr) {
		Object2D* i = new Object2D(parent);
		return i;
	}
};

inline void updateObject2DVector(Object2D* o) {
	o->VectorChanged();
}

class LineEx : public Instance { // it cannot contain Object2D inheritors inside itself  |  only necessary for drawing lines  | Unstable
	constexpr static const char* DefaultName = "LineEx";
	constexpr static InstanceType DefaultClass = LINEEX;

	std::pair<SpecialVector2, SpecialVector2> getRealObject2Dposition() {
		SpecialVector2 pos1 = { Position1.x, Position1.y };
		SpecialVector2 pos2 = { Position2.x, Position2.y };
		Instance* current = Parent;

		while (current) {
			Object2D* obj = dynamic_cast<Object2D*>(current);
			if (!obj) {
				if (current->Parent) {
					current = current->Parent;
					continue;
				}
				break;
			}

			SpecialVector2 parentPos = {
				obj->Position.x - obj->AnchorPosition.x * obj->Size.x,
				obj->Position.y - obj->AnchorPosition.y * obj->Size.y
			};

			if (obj->Class == SCROLLFRAME) {
				SpecialVector2 CanvasPosition = getCanvasRealPos(obj);

				pos1.x = parentPos.x + (pos1.x - CanvasPosition.x);
				pos1.y = parentPos.y + (pos1.y - CanvasPosition.y);

				pos2.x = parentPos.x + (pos2.x - CanvasPosition.x);
				pos2.y = parentPos.y + (pos2.y - CanvasPosition.y);
			} else {
				pos1.x = parentPos.x + pos1.x * obj->Size.x;
				pos1.y = parentPos.y + pos1.y * obj->Size.y;

				pos2.x = parentPos.x + pos2.x * obj->Size.x;
				pos2.y = parentPos.y + pos2.y * obj->Size.y;
			}

			current = obj->Parent;
		}

		return { {pos1.x * SIMPLEUI_GLOBAL::winWidth, pos1.y * SIMPLEUI_GLOBAL::winHeight}, {pos2.x * SIMPLEUI_GLOBAL::winWidth, pos2.y * SIMPLEUI_GLOBAL::winHeight} };
	}
protected:
	LineEx(bool a) : Instance(a) {
		Name = DefaultName;
		Class = DefaultClass;
	};

	LineEx(Instance* p) : Instance(p) {
		Name = DefaultName;
		Class = DefaultClass;
	}

	LineEx() = delete;
	~LineEx() override = default;
public:
	SpecialVector2 Position1{};
	SpecialVector2 Position2{};
	Color LineColor{};
	int Thickness = 5;
	int ZIndex = 0;
	bool Visible = true;

	void Draw() {
		if (Visible and Thickness) {
			auto [pos1, pos2] = getRealObject2Dposition();
			DrawLineEx(pos1, pos2, Thickness, LineColor);
		}
	}

	void Update(bool posOrSizeChanged) override {
		if (lastUpdateFrame == SIMPLEUI_GLOBAL::framesSinceStart) return;
		lastUpdateFrame = SIMPLEUI_GLOBAL::framesSinceStart;

		eventHandler();
		if (SIMPLEUI_GLOBAL::deletedObjectsByID[uniqueID]) return;
		Draw();
	}

	LineEx* Clone() const override {
		LineEx* i = new LineEx(*this);

		i->basicCloneOperation(const_cast<LineEx*>(this));

		return i;
	}

	static LineEx* New(Instance* parent = nullptr) {
		LineEx* i = new LineEx(parent);
		return i;
	}
};

inline void updateChildren(Instance* parent) {
	if (!parent) return;
	parent->updateChildrenZIndex = false;
	std::sort(parent->Children.begin(), parent->Children.end(), [](Instance* a, Instance* b) {
		int zA = 0;
		int zB = 0;

		if (Is2DInheritor(a->Class)) {
			zA = static_cast<Object2D*>(a)->ZIndex;
		}

		if (Is2DInheritor(b->Class)) {
			zB = static_cast<Object2D*>(b)->ZIndex;
		}

		return zA < zB;
	});
}

inline Font getFont(const std::string& name) {
	auto it = Fonts.find(name);
	if (it != Fonts.end())
		return it->second;

	return Fonts.find(SIMPLEUI_GLOBAL::BASIC_FONT_NAME)->second;
}

struct Clip {
	int x, y, w, h;
};
inline std::vector<Clip> clipStack;

inline Clip Intersect(const Clip& a, const Clip& b) {
	int x1 = std::max(a.x, b.x);
	int y1 = std::max(a.y, b.y);
	int x2 = std::min(a.x + a.w, b.x + b.w);
	int y2 = std::min(a.y + a.h, b.y + b.h);
	if (x2 <= x1 or y2 <= y1) return { 0, 0, 0, 0 };
	return { x1, y1, x2 - x1, y2 - y1 };
}

inline void PushClip(Clip last) {
	if (!clipStack.empty())
		last = Intersect(clipStack.back(), last);

	clipStack.push_back(last);
	RL_FUNCTIONS_PLUS::BeginScissorMode(last.x, last.y, last.w, last.h);
}

inline void PopClip() {
	RL_FUNCTIONS_PLUS::EndScissorMode();
	clipStack.pop_back();
	if (!clipStack.empty()) {
		Clip last = clipStack.back();
		RL_FUNCTIONS_PLUS::BeginScissorMode(last.x, last.y, last.w, last.h);
	}
}

class ScrollFrame : public Object2D {
	constexpr static const char* DefaultName = "ScrollFrame";
	constexpr static InstanceType DefaultClass = SCROLLFRAME;
	constexpr static unsigned int GridSectorSize = 512;

	struct ScrollSector {
		int X = 0;
		int Y = 0;
		std::unordered_map<long, Instance*> Objects;
	};

	std::unordered_map<int, std::unordered_map<int, ScrollSector*>> Grid;
	std::unordered_map<long, std::vector<ScrollSector*>> SectorsOnObject;

	std::vector<Instance*> Tick;
	std::unordered_map<long, Instance*> isTick;
public:
	std::vector<ScrollSector*> sectorsOnView;
private:
	void SectorsAddChild(Instance* child) {
		if (!child) return;

		UpdateSectors(child);

		if (child->hasEvent(TICK)) {
			Tick.push_back(child);
			isTick.insert({ child->uniqueID, child });
		}
	}

	void SectorsRemoveChild(long childID) {
		if (childID == -1) return;

		auto it4 = toUpdateSectors.find(childID);
		if (it4 != toUpdateSectors.end()) {
			toUpdateSectors.erase(it4);
		}

		auto it = SectorsOnObject.find(childID);
		if (it != SectorsOnObject.end()) {
			for (ScrollSector* sector : it->second) {
				auto it2 = sector->Objects.find(childID);
				if (it2 != sector->Objects.end()) {
					sector->Objects.erase(it2);
				}
			}
			SectorsOnObject.erase(it);
		}

		auto it2 = isTick.find(childID);
		if (it2 != isTick.end()) {
			Instance* ptr = it2->second;
			isTick.erase(it2);
			for (int i = 0; i < Tick.size(); i++) {
				if (Tick[i] == ptr) {
					Tick.erase(Tick.begin() + i);
					break;
				}
			}
		}
	}

	std::vector<std::pair<int, int>> getSectors(Instance* generalObj) const {
		std::vector<std::pair<int, int>> sectors;

		static std::function<void(Instance*, std::vector<std::pair<int, int>>&)> sectorsCalculate = [](Instance* obj, std::vector<std::pair<int, int>>& sect) {
			if (Is2DInheritor(obj)) {
				Object2D* casted = static_cast<Object2D*>(obj);

				SpecialVector2 parentSize = { 0,0 };

				Instance* currentParent = casted->Parent;

				while (currentParent) {
					if (Is2DInheritor(currentParent)) {
						parentSize = static_cast<Object2D*>(currentParent)->RealSize;
						break;
					} else {
						currentParent = currentParent->Parent;
					}
				}

				SpecialVector2 pos = {
					casted->Position.x * parentSize.x + casted->PositionOFFSET.x,
					casted->Position.y * parentSize.y + casted->PositionOFFSET.y
				};
				casted->getRealObject2Dsize();
				SpecialVector2 lastpos = { pos.x + casted->RealSize.x, pos.y + casted->RealSize.y };

				for (int i = std::floor(pos.x / GridSectorSize); i <= std::ceil(lastpos.x / GridSectorSize); i++) {
					for (int j = std::floor(pos.y / GridSectorSize); j <= std::ceil(lastpos.y / GridSectorSize); j++) {
						sect.push_back({ i, j });
					}
				}
			}

			for (Instance* child : obj->Children) {
				sectorsCalculate(child, sect);
			}
		};

		sectorsCalculate(generalObj, sectors);

		return sectors;
	}

	void addObjToSector(Instance* obj, int x, int y) {
		ScrollSector* sector = nullptr;
		auto it1 = Grid.find(x);
		bool founded = false;

		if (it1 != Grid.end()) {
			auto it2 = it1->second.find(y);
			if (it2 != it1->second.end()) {
				sector = it2->second;
				founded = true;
			}
		} else {
			Grid[x] = {};
		}

		if (not founded) {
			sector = new ScrollSector();
			sector->X = x;
			sector->Y = y;

			Grid[x][y] = sector;
		}

		sector->Objects.insert({ obj->uniqueID, obj });

		auto it3 = SectorsOnObject.find(obj->uniqueID);

		if (it3 == SectorsOnObject.end()) {
			SectorsOnObject[obj->uniqueID] = { sector };
		} else {
			SectorsOnObject[obj->uniqueID].push_back(sector);
		}
	}
private:
	SpecialVector2 lastFullSize{};
	SpecialVector2 lastCanvasFullPosition{};
	SpecialVector2 lastCanvasPos{};
	bool lastVisible = false;

	void checkAndUpdateCurrentSectors(bool force = false) {
		SpecialVector2 fullSize = RealSize;
		SpecialVector2 fullPos = { CanvasPosition.x * RealSize.x + CanvasPositionOFFSET.x, CanvasPosition.y * RealSize.y + CanvasPositionOFFSET.y };

		if (force or lastVisible != Visible or SIMPLEUI_GLOBAL::windowSizeChanged or lastFullSize.x != fullSize.x or lastFullSize.y != fullSize.y or
			lastCanvasFullPosition.x != fullPos.x or lastCanvasFullPosition.y != fullPos.y) {
			lastFullSize = fullSize;
			lastCanvasFullPosition = fullPos;
			lastVisible = Visible;
			sectorsOnView.clear();
			SpecialVector2 pos = fullPos;
			SpecialVector2 lastpos = { fullPos.x + fullSize.x, fullPos.y + fullSize.y };

			Vector2 start = {
				std::floor(pos.x / GridSectorSize),
				std::floor(pos.y / GridSectorSize)
			};

			Vector2 end = {
				std::ceil(lastpos.x / GridSectorSize),
				std::ceil(lastpos.y / GridSectorSize)
			};

			for (int i = start.x; i <= end.x; i++) {
				for (int j = start.y; j <= end.y; j++) {
					ScrollSector* s = nullptr;
					auto f = Grid.find(i);
					if (f == Grid.end()) {
						continue;
					}

					auto f2 = f->second.find(j);

					if (f2 == f->second.end()) {
						continue;
					} else {
						s = f2->second;
					}

					sectorsOnView.push_back(s);
				}
			}
		}
	}

	std::unordered_map<long, Instance*> toUpdateSectors;
	void secUpd(Instance* child) {
		if (!child) return;

		auto checkIt = SectorsOnObject.find(child->uniqueID);
		if (checkIt == SectorsOnObject.end()) { // new object in Scroll
			SectorsOnObject.insert({ child->uniqueID, {} });

			std::vector<std::pair<int, int>> sectors = getSectors(child);
			for (auto& [x, y] : sectors) {
				addObjToSector(child, x, y);
			}
		} else { // updating current sector
			for (ScrollSector* sector : checkIt->second) {
				auto it2 = sector->Objects.find(child->uniqueID);
				if (it2 != sector->Objects.end()) {
					sector->Objects.erase(it2);
				}
			}
			checkIt->second.clear();

			std::vector<std::pair<int, int>> sectors = getSectors(child);
			for (auto& [x, y] : sectors) {
				addObjToSector(child, x, y);
			}
		}
	}
protected:
	ScrollFrame(bool a) : Object2D(a) { Name = DefaultName; Class = DefaultClass; EnterEventCondition = EEC_IF_DESCENDANT_HIGHER; Active = true; };
	ScrollFrame(Instance* p) : Object2D(p) { Name = DefaultName; Class = DefaultClass; EnterEventCondition = EEC_IF_DESCENDANT_HIGHER; Active = true; }

	ScrollFrame() = delete;
	~ScrollFrame() override {
		for (auto& _ : Grid) {
			for (auto& [_, s] : _.second) {
				delete s;
			}
		}
	}
public:
	void UpdateSectors(Instance* child) {
		toUpdateSectors.insert({ child->uniqueID, child });
	}

	void UpdateObjectTickState(Instance* child) {
		auto it = isTick.find(child->uniqueID);
		bool hasTick = child->hasEvent(TICK);

		if (hasTick and it == isTick.end()) {
			isTick.insert({ child->uniqueID, child });
		} else if (!hasTick and it != isTick.end()) {
			isTick.erase(it);
		}
	}

	SpecialVector2 CanvasSize = { 0,0 };
	SpecialVector2 CanvasPosition = { 0,0 };
	SpecialVector2 CanvasSizeOFFSET = { 0,0 };
	SpecialVector2 CanvasPositionOFFSET = { 0,0 };
	SpecialVector2 CanvasAbsoluteSize = { 0,0 };
	SpecialVector2 CanvasAbsolutePosition = { 0,0 };
	float ScrollSpeed = 0.25;
	float ScrollSpeedOFFSET = 0;
	bool CropDescendants = true;
	Color SliderColor = { 15,15,15,255 };
	float SliderTransparency = 0.5;
	unsigned int SliderSize = 5;
	char Direction = 'Y';
	bool ScrollEnabled = true;
	bool Animated = false;

	void Draw(bool posOrSizeChanged) {
		Object2D::Draw();

		bool pushed = false;
		if (CropDescendants) {
			PushClip({ (int)RealPos.x, (int)RealPos.y, (int)RealSize.x, (int)RealSize.y });
			pushed = true;
		}

		for (auto& [id, ptr] : toUpdateSectors) {
			if (SIMPLEUI_GLOBAL::deletedObjectsByID[id]) continue;
			secUpd(ptr);
		}

		toUpdateSectors.clear();

		bool tempRes = posOrSizeChanged or posOrSizeChangedResult or updateWhenWillBeVisible;
		posOrSizeChangedResult = false;
		updateWhenWillBeVisible = false;

		for (ScrollSector* s : sectorsOnView) {
			for (auto& [id, ptr] : s->Objects) {
				if (SIMPLEUI_GLOBAL::deletedObjectsByID[id]) continue;
				ptr->Update(tempRes);
			}
		}

		for (Instance* s : Tick) {
			s->Update(tempRes);
		}

		checkAndUpdateCurrentSectors(true); // force update cuz sometimes calculate condition doesn't work

		if (pushed) PopClip();

		if (SliderTransparency != 1 and SliderSize != 0) {
			if (CanvasSize.y > 1 or CanvasSizeOFFSET.y > RealSize.y) {
				if (Direction == 'Y' or Direction == 'B') {
					float totalContentHeight = CanvasSizeOFFSET.y + CanvasSize.y * RealSize.y;
					if (totalContentHeight < RealSize.y) totalContentHeight = RealSize.y;

					float sliderHeight = RealSize.y * (RealSize.y / totalContentHeight);
					if (sliderHeight > RealSize.y) sliderHeight = RealSize.y;

					float maxScrollY = totalContentHeight - RealSize.y;
					float currentScrollY = (RealSize.y * CanvasPosition.y) + CanvasPositionOFFSET.y;

					float sliderY = RealPos.y;
					if (maxScrollY > 0) {
						sliderY += (RealSize.y - sliderHeight) * (currentScrollY / maxScrollY);
					}

					SpecialVector2 firstPoint = { RealPos.x + RealSize.x - SliderSize * 0.6f, sliderY };
					SpecialVector2 secondPoint = { firstPoint.x, sliderY + sliderHeight };
					RL_FUNCTIONS_PLUS::DrawLineEx(firstPoint, secondPoint, SliderSize, { SliderColor.r, SliderColor.g, SliderColor.b, (unsigned char)(SliderColor.a * (1 - SliderTransparency)) });
				}
			}

			if (CanvasSize.x > 1 or CanvasSizeOFFSET.x > RealSize.x) {
				if (Direction == 'X' or Direction == 'B') {
					float totalContentWidth = CanvasSizeOFFSET.x + CanvasSize.x * RealSize.x;
					if (totalContentWidth < RealSize.x) totalContentWidth = RealSize.x;

					float sliderWidth = RealSize.x * (RealSize.x / totalContentWidth);
					if (sliderWidth > RealSize.x) sliderWidth = RealSize.x;

					float maxScrollX = totalContentWidth - RealSize.x;
					float currentScrollX = (RealSize.x * CanvasPosition.x) + CanvasPositionOFFSET.x;

					float sliderX = RealPos.x;
					if (maxScrollX > 0) {
						sliderX += (RealSize.x - sliderWidth) * (currentScrollX / maxScrollX);
					}

					SpecialVector2 firstPoint = { sliderX, RealPos.y + RealSize.y - SliderSize * 0.6f };
					SpecialVector2 secondPoint = { sliderX + sliderWidth, firstPoint.y };
					RL_FUNCTIONS_PLUS::DrawLineEx(firstPoint, secondPoint, SliderSize, { SliderColor.r, SliderColor.g, SliderColor.b, (unsigned char)(SliderColor.a * (1 - SliderTransparency)) });
				}
			}
		}
	}

	void Update(bool posOrSizeChanged) override {
		if (lastUpdateFrame == SIMPLEUI_GLOBAL::framesSinceStart) return;
		lastUpdateFrame = SIMPLEUI_GLOBAL::framesSinceStart;

		if (CanvasSize.x < 0) CanvasSize.x = 0; if (CanvasSize.y < 0) CanvasSize.y = 0;
		if (Direction != 'X' and Direction != 'Y' and Direction != 'B') {
			Direction = 'Y';
		}

		eventHandler();
		if (SIMPLEUI_GLOBAL::deletedObjectsByID[uniqueID]) return;

		if (!Visible) {
			if (posOrSizeChanged or posOrSizeChangedResult) updateWhenWillBeVisible = true;
			return;
		}

		SpecialVector2 oldSize = RealSize;

		if (posOrSizeChanged or posOrSizeChangedResult or updateWhenWillBeVisible) {
			getRealObject2Dsize();
			getRealObject2Dposition();

			for (Instance* obj : Children) {
				obj->SetSizePosUpdateFlag();
				UpdateSectors(obj);
			}
		}

		if (oldSize.x != RealSize.x or oldSize.y != RealSize.y) { 
			for (Instance* child : Children) {
				UpdateSectors(child);
			}
		}

		for (auto& [id, ptr] : childsAddedInFrame) {
			SectorsAddChild(ptr);
		}

		for (auto& [id, ptr] : childsRemovedInFrame) {
			SectorsRemoveChild(id);
		}

		SameUpdate();

		if (updateChildrenZIndex) {
			updateChildren(this);
		}

		float maxScrollX = std::max(0.0f, (float)(CanvasSize.x * RealSize.x + CanvasSizeOFFSET.x - RealSize.x));
		float maxScrollY = std::max(0.0f, (float)(CanvasSize.y * RealSize.y + CanvasSizeOFFSET.y - RealSize.y));

		CanvasPositionOFFSET.x = std::max(0.0f, (float)CanvasPositionOFFSET.x);
		CanvasPositionOFFSET.y = std::max(0.0f, (float)CanvasPositionOFFSET.y);
		CanvasPosition.x = std::max(0.0f, (float)CanvasPosition.x);
		CanvasPosition.y = std::max(0.0f, (float)CanvasPosition.y);

		float currentScrollX = (RealSize.x * CanvasPosition.x) + CanvasPositionOFFSET.x;
		if (currentScrollX > maxScrollX) {
			CanvasPosition.x = std::floor(maxScrollX / RealSize.x);
			CanvasPositionOFFSET.x = maxScrollX - (RealSize.x * CanvasPosition.x);
		}

		float currentScrollY = (RealSize.y * CanvasPosition.y) + CanvasPositionOFFSET.y;
		if (currentScrollY > maxScrollY) {
			CanvasPosition.y = std::floor(maxScrollY / RealSize.y);
			CanvasPositionOFFSET.y = maxScrollY - (RealSize.y * CanvasPosition.y);
		}

		if (ScrollEnabled) {
			float WheelMove = GetMouseWheelMove();
			if (WheelMove != 0) {
				bool entered = false;

				bool enterAllowed = (
					EnterEventCondition == SUI_EEC::EEC_DEFAULT ? this == SIMPLEUI_GLOBAL::higherObject :
					(EnterEventCondition == SUI_EEC::EEC_EVERY_ENTER ? true :
						EnterEventCondition == SUI_EEC::EEC_IF_DESCENDANT_HIGHER ? ((SIMPLEUI_GLOBAL::higherObject == this and SIMPLEUI_GLOBAL::higherObject != nullptr) or (SIMPLEUI_GLOBAL::higherObject and SIMPLEUI_GLOBAL::higherObject != this and SIMPLEUI_GLOBAL::higherObject->isDescendantOf(this))) : false)
					);

				if (Visible and ((SIMPLEUI_GLOBAL::higherObject == this and SIMPLEUI_GLOBAL::PreviousHigherObject != this) or enterAllowed)) {
					entered = true;
				}

				if (entered) {
					bool isY = (Direction == 'Y' or (!IsKeyDown(KEY_LEFT_SHIFT) and Direction == 'B'));
					bool isX = (Direction == 'X' or (IsKeyDown(KEY_LEFT_SHIFT) and Direction == 'B'));

					if (isY) {
						float currentY = (RealSize.y * CanvasPosition.y) + CanvasPositionOFFSET.y;
						float totalStep = (RealSize.y * ScrollSpeed) + ScrollSpeedOFFSET;
						float newTotalY = currentY - (WheelMove * totalStep);

						newTotalY = std::clamp(newTotalY, 0.0f, maxScrollY);

						float newY1 = std::floor(newTotalY / RealSize.y);
						float newY = newTotalY - (RealSize.y * newY1);

						if (Animated) {
							Animate::Create(&CanvasPositionOFFSET.y, 0.125, newY);
							Animate::Create(&CanvasPosition.y, 0.125, newY1);
						} else {
							CanvasPositionOFFSET.y = newY;
							CanvasPosition.y = newY1;
						}
					} else if (isX) {
						float currentX = (RealSize.x * CanvasPosition.x) + CanvasPositionOFFSET.x;
						float totalStep = (RealSize.x * ScrollSpeed) + ScrollSpeedOFFSET;
						float newTotalX = currentX - (WheelMove * totalStep);

						newTotalX = std::clamp(newTotalX, 0.0f, maxScrollX);

						float newX1 = std::floor(newTotalX / RealSize.x);
						float newX = newTotalX - (RealSize.x * newX1);

						if (Animated) {
							Animate::Create(&CanvasPositionOFFSET.x, 0.125, newX);
							Animate::Create(&CanvasPosition.x, 0.125, newX1);
						} else {
							CanvasPositionOFFSET.x = newX;
							CanvasPosition.x = newX1;
						}
					}
				}
			}
		}

		bool canvasPosChanged = lastCanvasPos.x == (CanvasPosition.x * RealSize.x + CanvasPositionOFFSET.x) and
			lastCanvasPos.y == (CanvasPosition.y * RealSize.y + CanvasPositionOFFSET.y);

		lastCanvasPos = { (CanvasPosition.x * RealSize.x + CanvasPositionOFFSET.x), (CanvasPosition.y * RealSize.y + CanvasPositionOFFSET.y) };

		Draw(posOrSizeChanged or posOrSizeChangedResult or updateWhenWillBeVisible or !canvasPosChanged);
	}

	ScrollFrame* Clone() const override {
		ScrollFrame* i = new ScrollFrame(*this);
		i->UpdateAllVectorPointers();
		i->posOrSizeChangedResult = true;

		i->Grid.clear();
		i->SectorsOnObject.clear();
		i->Tick.clear();
		i->isTick.clear();
		i->sectorsOnView.clear();
		i->lastFullSize.x = -123123;

		i->basicCloneOperation(const_cast<ScrollFrame*>(this));

		return i;
	}

	static ScrollFrame* New(Instance* parent = nullptr) {
		ScrollFrame* i = new ScrollFrame(parent);
		return i;
	}
};

inline void Object2D::updateAncestorWhichParentIsScroll() {
	Instance* scrollChild = ((this->Parent and this->Parent->Class == SCROLLFRAME) ? this : getAncestorWhichParentIsScrollFrame(this));

	if (scrollChild) {
		static_cast<ScrollFrame*>(scrollChild->Parent)->UpdateSectors(scrollChild);
	}
}

inline SpecialVector2 getCanvasRealPos(Object2D* obj) {
	if (obj->Class == SCROLLFRAME) {
		ScrollFrame* scra = static_cast<ScrollFrame*>(obj);
		return
		{
			scra->CanvasPosition.x * scra->RealSize.x + scra->CanvasPositionOFFSET.x,
			scra->CanvasPosition.y * scra->RealSize.y + scra->CanvasPositionOFFSET.y
		};
	}
	return { 0,0 };
}

inline SpecialVector2 getScrollFrameRS(Instance* sc) {
	if (sc->Class == SCROLLFRAME) {
		ScrollFrame* scra = static_cast<ScrollFrame*>(sc);
		return scra->RealSize;
	}

	return { 0,0 };
}
inline SpecialVector2 getScrollFrameRP(Instance* sc) {
	if (sc->Class == SCROLLFRAME) {
		ScrollFrame* scra = static_cast<ScrollFrame*>(sc);
		return scra->RealPos;
	}

	return { 0,0 };
}
inline bool isScrollFrameCropping(Instance* sc) {
	if (sc->Class == SCROLLFRAME) {
		ScrollFrame* scra = static_cast<ScrollFrame*>(sc);
		return scra->CropDescendants;
	}

	return false;
}

class TextLabel : public Object2D {
	constexpr static float TextTextureUpdateAspect = 1.1;
	constexpr static const char* DefaultName = "TextLabel";
	constexpr static InstanceType DefaultClass = TEXTLABEL;

	std::string visibleText = "";
	int lastMaxVisible = -1;
	Vector3 textParams{};
	SpecialVector2 lastRealSize{};
	AtlasTexture cachedText{};
	SpecialVector2 newSize{};
	SpecialVector2 lastNewSize{};
	Vector3 lastParams = Vector3{};
	std::vector<int> charOffsets;

	void updateCharOffsets() {
		charOffsets.clear();
		for (int i = 0; i < Text.size();) {
			charOffsets.push_back(i);
			unsigned char c = Text[i];
			if (c < 0x80) i += 1;
			else if ((c & 0xE0) == 0xC0) i += 2;
			else if ((c & 0xF0) == 0xE0) i += 3;
			else if ((c & 0xF8) == 0xF0) i += 4;
			else i += 1;
		}
		charOffsets.push_back(Text.size());
	}

	void updateTexture() {
		updateCharOffsets();

		if (MaxVisibleSymbols > 0 and MaxVisibleSymbols < charOffsets.size()) {
			if (MaxVisibleRight) {
				size_t idx = charOffsets[std::max(3, (int)(charOffsets.size() - MaxVisibleSymbols)) - 3];
				visibleText = "...";
				visibleText += Text.substr(idx);
			} else {
				size_t idx = charOffsets[std::max(3, MaxVisibleSymbols) - 3];
				visibleText = Text.substr(0, idx);
				visibleText += "...";
			}
		} else {
			visibleText = !Text;
		}

		textParams = getTextCFrame(visibleText.c_str(), getFont(!FontFace), { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize, Spacing);
		lastRealSize = RealSize;
		lastParams = textParams;
		lastMaxVisible = MaxVisibleSymbols;

		newSize = MeasureTextEx(getFont(!FontFace), visibleText.c_str(), textParams.z, Spacing);

		if (cachedText.id == 0 or !cachedText.currentAtlas or lastNewSize.x < newSize.x or lastNewSize.y < newSize.y) {
			if (cachedText.id != 0) {
				UnloadTextureFromAtlas(cachedText);
			}

			if (Text.size()) {
				cachedText = LoadRenderTextureOnAtlas(newSize.x * TextTextureUpdateAspect, newSize.y * TextTextureUpdateAspect);
				lastNewSize = SpecialVector2{ newSize.x * TextTextureUpdateAspect, newSize.y * TextTextureUpdateAspect };
			}
		}

		if (cachedText.id and cachedText.currentAtlas) {
			bool hadClip = !clipStack.empty();
			Clip current;
			if (hadClip) current = clipStack.back();

			if (hadClip) RL_FUNCTIONS_PLUS::EndScissorMode();

			RL_FUNCTIONS_PLUS::BeginTextureMode(cachedText.currentAtlas->renderTexture());
			cachedText.currentAtlas->blankArea(cachedText);
			DrawTextEx(getFont(!FontFace), visibleText.c_str(), { cachedText.position.x, cachedText.position.y }, textParams.z, Spacing, { 255,255,255,255 });
			RL_FUNCTIONS_PLUS::EndTextureMode();

			if (hadClip) RL_FUNCTIONS_PLUS::BeginScissorMode(current.x, current.y, current.w, current.h);
		}
	}
protected:
	TextLabel(bool a) : Object2D(a) { Name = DefaultName; Class = DefaultClass; };
	TextLabel(Instance* p) : Object2D(p) { Name = DefaultName; Class = DefaultClass; }

	TextLabel() = delete;
	~TextLabel() override {
		if (cachedText.id != 0) {
			UnloadTextureFromAtlas(cachedText);
		}
	}
public:
	SUI_Text Text = "";
	SUI_Text FontFace = SIMPLEUI_GLOBAL::BASIC_FONT_NAME;
	float TextTransparency = 0.0f;
	TextAnchorEnum TextAnchor = TextAnchorEnum::CENTER;
	Color TextColor = { 0,0,0,255 };
	int TextSize = -1;
	int Spacing = SIMPLEUI_GLOBAL::defaultSpacing;
	int MaxVisibleSymbols = -1;
	bool MaxVisibleRight = false;

	const SUI_Text& GetText() const { // Deprecated functional. Now you can use ***->Text;
		return Text;
	}

	void SetText(const std::string& T) { // Deprecated functional. Now you can use ***->Text = ***;
		Text = T;
	}

	const SUI_Text& GetFont() const { // Deprecated functional. Now you can use ***->FontFace;
		return FontFace;
	}

	void SetFont(const std::string& F) { // Deprecated functional. Now you can use ***->FontFace = ***;
		FontFace = F;
	}

	void Draw() override {
		if (Visible) {
			if (RealPos.x + RealSize.x + BorderThickness < 0
				or RealPos.x - BorderThickness > SIMPLEUI_GLOBAL::winWidth
				or RealPos.y + RealSize.y + BorderThickness < 0
				or RealPos.y - BorderThickness > SIMPLEUI_GLOBAL::winHeight) {
				return;
			}

			Object2D::Draw();

			bool dirtyCondition = Text.isChanged() or FontFace.isChanged();
			Text.restate();
			FontFace.restate();

			if (lastParams.z != textParams.z or (cachedText.id == 0 and Text.size()) or dirtyCondition or lastMaxVisible != MaxVisibleSymbols) {
				updateTexture();
			} else {
				if (std::fabsf(lastRealSize.x - RealSize.x) >= TextTextureUpdateAspect or std::fabsf(lastRealSize.y - RealSize.y) >= TextTextureUpdateAspect) {
					lastRealSize = RealSize;
					newSize = MeasureTextEx(getFont(!FontFace), visibleText.c_str(), textParams.z, Spacing);
					textParams = getTextCFrame(visibleText.c_str(), getFont(!FontFace), { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize, Spacing);
				}
			}

			if (textParams.z > 1) {
				if (cachedText.id == 0) {
					updateTexture();
				}

				Rectangle sourceRec = { 0.0f, 0.0f, (float)newSize.x, (float)newSize.y };
				Rectangle destRec = { std::floorf(RealPos.x + textParams.x), std::floorf(RealPos.y + textParams.y), std::floorf(newSize.x), std::floorf((float)newSize.y) };

				RL_FUNCTIONS_PLUS::DrawTexturePro(cachedText, RealPos, RealSize, sourceRec, destRec, Origin, Rotation, { TextColor.r, TextColor.g, TextColor.b, (unsigned char)(TextColor.a * (1 - TextTransparency)) }, 0);
			}
		}
	}

	TextLabel* Clone() const override {
		TextLabel* i = new TextLabel(*this);
		i->UpdateAllVectorPointers();
		i->posOrSizeChangedResult = true;

		i->basicCloneOperation(const_cast<TextLabel*>(this));

		i->cachedText.id = 0;
		i->cachedText.currentAtlas = nullptr;
		i->updateTexture();

		return i;
	}

	static TextLabel* New(Instance* parent = nullptr) {
		TextLabel* i = new TextLabel(parent);
		return i;
	}
};

enum TextBoxType {
	TEXTBOX_RESIZING = 0,
	TEXTBOX_VIEWPORTED_X,
	TEXTBOX_VIEWPORTED_Y,
	TEXTBOX_VIEWPORTED_XY,
};

enum TextBoxNextLine {
	TEXTBOX_NEXTLINE_NOT_ALLOWED = 0,
	TEXTBOX_NEXTLINE_ENTER,
	TEXTBOX_NEXTLINE_CTRL_ENTER,
	TEXTBOX_NEXTLINE_SHIFT_ENTER
};

class TextBox : public Object2D {
	constexpr static float TextTextureUpdateAspect = 1.3;
	constexpr static const char* DefaultName = "TextBox";
	constexpr static InstanceType DefaultClass = TEXTBOX;

	int CursorIndex = -1;
	float CursorCooldown = 0.5f;
	float CursorTime = 0.0f;
	bool CursorVisible = false;

	bool deleteText = false;

	void updateCharOffsets() {
		charOffsets.clear();
		for (int i = 0; i < Text.size();) {
			charOffsets.push_back(i);
			unsigned char c = Text[i];
			if (c < 0x80) i += 1;
			else if ((c & 0xE0) == 0xC0) i += 2;
			else if ((c & 0xF0) == 0xE0) i += 3;
			else if ((c & 0xF8) == 0xF0) i += 4;
			else i += 1;
		}
		charOffsets.push_back(Text.size());
	}

	std::vector<int> getCharOffsets(const std::string& text) {
		std::vector<int> c;
		for (int i = 0; i < text.size();) {
			c.push_back(i);
			unsigned char c = text[i];
			if (c < 0x80) i += 1;
			else if ((c & 0xE0) == 0xC0) i += 2;
			else if ((c & 0xF0) == 0xE0) i += 3;
			else if ((c & 0xF8) == 0xF0) i += 4;
			else i += 1;
		}
		c.push_back(text.size());

		return c;
	}

	std::vector<int> charOffsets;
	int lines = 0;
	Vector2 highlightedIndexes{ -1,-1 };
	Vector3 textParams{};
	AtlasTexture cachedText;
	TextBox* lastFocused = nullptr;
	SpecialVector2 newSize{};
	SpecialVector2 lastRealSize{};
	Vector3 lastParams = Vector3{};
	char lastHideText = '\0';
	SpecialVector2 lastNewSize{};
	TextBoxType lastType = TextBoxType::TEXTBOX_RESIZING;
	int lastCursorIndex = -1;

	void updateTextParams() {
		if (Type != TextBoxType::TEXTBOX_RESIZING) {
			textParams.y = 0;
			textParams.x = 0;
			textParams.z = std::fmin(RealSize.y, ((TextSize > 0) ? TextSize : RealSize.y));
		} else {
			if (Text != "") {
				textParams = getTextCFrame(Text.c_str(), getFont(!FontFace), { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize, Spacing);
			} else {
				textParams = getTextCFrame(PlaceholderText.c_str(), getFont(!FontFace), { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize, Spacing);
			}
		}
	}

	void updateTexture() {
		updateTextParams();
		lastFocused = SIMPLEUI_GLOBAL::FocusedTextBox;
		lastParams = textParams;
		lastRealSize = RealSize;
		lastHideText = HideText;
		lastType = Type;

		if (Text != "") {
			newSize = MeasureTextEx(getFont(!FontFace), Text.c_str(), textParams.z, Spacing);
		} else {
			if (CursorIndex == -1 or SIMPLEUI_GLOBAL::FocusedTextBox != this) {
				newSize = MeasureTextEx(getFont(!FontFace), PlaceholderText.c_str(), textParams.z, Spacing);
			}
		}

		float reqX = (Type != TextBoxType::TEXTBOX_RESIZING) ? std::max(newSize.x, RealSize.x) : newSize.x;
		float reqY = (Type != TextBoxType::TEXTBOX_RESIZING) ? std::max(newSize.y, RealSize.y) : newSize.y;

		if (lastNewSize.x < reqX or lastNewSize.y < reqY) {
			if (cachedText.id != 0) {
				UnloadTextureFromAtlas(cachedText);
			}

			cachedText = LoadRenderTextureOnAtlas(reqX * TextTextureUpdateAspect, reqY * TextTextureUpdateAspect);
			lastNewSize = SpecialVector2{ reqX * TextTextureUpdateAspect, reqY * TextTextureUpdateAspect };
		}

		bool hadClip = !clipStack.empty();
		Clip current;
		if (hadClip) current = clipStack.back();

		if (hadClip) RL_FUNCTIONS_PLUS::EndScissorMode();

		RL_FUNCTIONS_PLUS::BeginTextureMode(cachedText.currentAtlas->renderTexture());
		cachedText.currentAtlas->blankArea(cachedText);

		if (Text != "") {
			lines = 1;

			std::string t;
			if (HideText == '\0') {
				t = Text;
			} else {
				for (int i = 0; i < charOffsets.size() - 1; i++) {
					t += HideText;
				}
			}

			for (char c : t) {
				if (c == '\n') lines++;
			}

			DrawTextEx(getFont(FontFace), t.c_str(), { cachedText.position.x,cachedText.position.y }, textParams.z, Spacing, { 255,255,255,255 });
		} else {
			lines = 0;
			if (CursorIndex == -1 or SIMPLEUI_GLOBAL::FocusedTextBox != this) {
				DrawTextEx(getFont(FontFace), PlaceholderText.c_str(), { cachedText.position.x,cachedText.position.y }, textParams.z, Spacing, { 255,255,255,255 });
			}
		}

		RL_FUNCTIONS_PLUS::EndTextureMode();
		if (hadClip) RL_FUNCTIONS_PLUS::BeginScissorMode(current.x, current.y, current.w, current.h);
	}
protected:
	TextBox(bool a) : Object2D(a) { Name = DefaultName; Class = DefaultClass; Active = true; }
	TextBox(Instance* p) : Object2D(p) { Name = DefaultName; Class = DefaultClass; Active = true; }

	TextBox() = delete;
	~TextBox() override {
		if (cachedText.id != 0) {
			UnloadTextureFromAtlas(cachedText);
		}
	}
public:
	Color CursorColor = { 0,0,0,255 };
	SUI_Text Text = "";
	SUI_Text FontFace = SIMPLEUI_GLOBAL::BASIC_FONT_NAME;
	SUI_Text PlaceholderText = "PlaceholderText";
	Color PlaceholderTextColor = { 150, 150, 150, 255 };
	Color TextColor = { 0,0,0,255 };
	TextAnchorEnum TextAnchor = TextAnchorEnum::CENTER;
	int TextSize = -1;
	int maxSymbols = -1;
	float TextTransparency = 0;
	std::string AllowedSymbols = "";
	std::string DisallowedSymbols = "";
	int Spacing = SIMPLEUI_GLOBAL::defaultSpacing;
	char HideText = '\0';
	bool ClearOnClick = true;
	TextBoxNextLine EnterInputCondition = TextBoxNextLine::TEXTBOX_NEXTLINE_ENTER;
	bool ClipboardPasteAllowed = true;
	bool ClipboardCopyAllowed = true;
	std::function<bool(const std::string&)> ClipboardPasteCondition;
	bool TextHighlightAllowed = true;
	SpecialVector2 viewportPosition{};
	bool CanType = true;
	bool CanClick = true;

	int CursorSize = 3;
	TextBoxType Type = TextBoxType::TEXTBOX_RESIZING;

	void Draw() override {
		if (!Visible) return;
		if (RealPos.x + RealSize.x + BorderThickness < 0
			or RealPos.x - BorderThickness > SIMPLEUI_GLOBAL::winWidth
			or RealPos.y + RealSize.y + BorderThickness < 0
			or RealPos.y - BorderThickness > SIMPLEUI_GLOBAL::winHeight) {
			return;
		}

		Object2D::Draw();

		bool updateCondition1 = PlaceholderText.isChanged() or FontFace.isChanged();

		if (updateCondition1 or lastType != Type or cachedText.id == 0 or lastHideText != HideText or lastParams.x != textParams.x or lastParams.y != textParams.y or lastParams.z != textParams.z or ((SIMPLEUI_GLOBAL::FocusedTextBox == this and lastFocused != this) or (lastFocused == this and SIMPLEUI_GLOBAL::FocusedTextBox != this))) {
			updateTexture();
		} else if (Text.isChanged()) {
			updateTexture();
		} else {
			if (lastRealSize.x != RealSize.x or lastRealSize.y != RealSize.y) {
				updateTextParams();
				if (Text == "") {
					newSize = MeasureTextEx(getFont(!FontFace), PlaceholderText.c_str(), textParams.z, Spacing);
				} else {
					newSize = MeasureTextEx(getFont(!FontFace), Text.c_str(), textParams.z, Spacing);
				}
			}
		}

		float viewX = (Type == TextBoxType::TEXTBOX_VIEWPORTED_X or Type == TextBoxType::TEXTBOX_VIEWPORTED_XY) ? viewportPosition.x : 0.0f;
		float viewY = (Type == TextBoxType::TEXTBOX_VIEWPORTED_Y or Type == TextBoxType::TEXTBOX_VIEWPORTED_XY) ? viewportPosition.y : 0.0f;

		if (textParams.z > 1) {
			if (cachedText.id == 0) {
				updateTexture();
			}

			SpecialVector2 sizeToDraw = (Type != TextBoxType::TEXTBOX_RESIZING) ? RealSize : newSize;

			Rectangle sourceRec = {
				std::floorf(viewX),
				std::floorf(viewY),
				std::floorf(sizeToDraw.x),
				std::floorf(sizeToDraw.y)
			};

			Rectangle destRec = { std::floorf(RealPos.x + textParams.x), std::floorf(RealPos.y + textParams.y), std::floorf(sizeToDraw.x), std::floorf(sizeToDraw.y) };

			Color clr;
			if (Text == "") {
				clr = { PlaceholderTextColor.r, PlaceholderTextColor.g, PlaceholderTextColor.b, (unsigned char)(PlaceholderTextColor.a * (1 - TextTransparency)) };
			} else {
				clr = { TextColor.r, TextColor.g, TextColor.b, (unsigned char)(TextColor.a * (1 - TextTransparency)) };
			}

			RL_FUNCTIONS_PLUS::DrawTexturePro(cachedText, RealPos, RealSize, sourceRec, destRec, Origin, Rotation, clr, 0);
		}

		if (Text.empty()) {
			if (CursorVisible and SIMPLEUI_GLOBAL::FocusedTextBox == this) {
				if (textParams.z > 1) {
					float sizeY = textParams.z;
					DrawLineEx(
						{ RealPos.x + getTextOffset(TextAnchor).x * RealSize.x - viewX, RealPos.y + textParams.y - viewY },
						{ RealPos.x + getTextOffset(TextAnchor).x * RealSize.x - viewX, RealPos.y + textParams.y + sizeY - viewY },
						CursorSize, CursorColor
					);
				}
			}
		}

		if (CursorIndex >= 0 and CursorVisible and !Text.empty() and textParams.z > 1) { // NOT OPTIMIZED
			int bytePos = (CursorIndex < (int)charOffsets.size()) ? charOffsets[CursorIndex] : Text.size();

			int startIndex = CursorIndex;
			while (startIndex > 0 and charOffsets.size() >= startIndex and Text[charOffsets[startIndex - 1]] != '\n') {
				startIndex--;
			}

			int start = (startIndex < (int)charOffsets.size()) ? charOffsets[startIndex] : Text.size();

			std::string textBeforeCursorOnThisLine = Text.substr(start, bytePos - start);

			if (HideText != '\0') {
				textBeforeCursorOnThisLine = "";
				for (int i = startIndex; i < CursorIndex; i++) {
					textBeforeCursorOnThisLine += HideText;
				}
			}

			int currentLine = 0;
			for (int i = 0; i < CursorIndex; i++) {
				if (Text[charOffsets[i]] == '\n') currentLine++;
			}

			SpecialVector2 size = MeasureTextEx(getFont(!FontFace), textBeforeCursorOnThisLine.c_str(), textParams.z, Spacing);

			if (size.x == 0 or size.y == 0) {
				size.y = MeasureTextEx(getFont(!FontFace), "A", textParams.z, Spacing).y;
				if (size.y == 0) size.y = textParams.z;
			}

			float yOffset = 0.0f;
			if (currentLine > 0) {
				std::string newlinesStr(currentLine, '\n');
				float totalH = MeasureTextEx(getFont(!FontFace), newlinesStr.c_str(), textParams.z, Spacing).y;
				float singleH = MeasureTextEx(getFont(!FontFace), "A", textParams.z, Spacing).y;
				yOffset = totalH - singleH;
			}

			DrawLineEx(
				{ RealPos.x + textParams.x + size.x - viewX, RealPos.y + textParams.y + yOffset - viewY },
				{ RealPos.x + textParams.x + size.x - viewX, RealPos.y + textParams.y + yOffset + size.y - viewY },
				CursorSize, CursorColor
			);
		}
	}

	void inputHandler() {
		if (SIMPLEUI_GLOBAL::FocusedTextBox == this and deleteText and ClearOnClick) {
			Text = "";
			CursorIndex = 0;
			deleteText = false;
			updateCharOffsets();
		}

		CursorTime += SIMPLEUI_GLOBAL::dt;
		if (CursorTime >= CursorCooldown) { CursorVisible = !CursorVisible; CursorTime = 0.0f; }

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and CanClick) {
			if (pointInObject(SIMPLEUI_GLOBAL::mousePosition) and SIMPLEUI_GLOBAL::FocusedTextBox != this and SIMPLEUI_GLOBAL::higherObject == this and ClearOnClick) {
				Text = "";
			}
			if (SIMPLEUI_GLOBAL::higherObject != this and SIMPLEUI_GLOBAL::higherObject) {
				if (SIMPLEUI_GLOBAL::higherObject->Class == TEXTBOX) {
					SIMPLEUI_GLOBAL::FocusedTextBox = static_cast<TextBox*>(SIMPLEUI_GLOBAL::higherObject);
				} else {
					SIMPLEUI_GLOBAL::FocusedTextBox = nullptr;
				}
			} else if (not SIMPLEUI_GLOBAL::higherObject) {
				SIMPLEUI_GLOBAL::FocusedTextBox = nullptr;
			} else if (pointInObject(SIMPLEUI_GLOBAL::mousePosition) and SIMPLEUI_GLOBAL::higherObject == this) {
				CursorTime = 0.0f;
				CursorVisible = true;
				SIMPLEUI_GLOBAL::FocusedTextBox = this;

				std::string text = "";
				if (HideText != '\0') {
					for (int i = 0; i < charOffsets.size(); i++) {
						text += HideText;
					}
				} else {
					text = !Text;
				}

				updateTextParams();
				std::string textBeforeCursor = "";
				if (HideText != '\0') {
					for (int i = 0; i < Text.size(); i++) {
						textBeforeCursor += HideText;
					}
				} else {
					textBeforeCursor = !Text;
				}

				float viewX = (Type == TextBoxType::TEXTBOX_VIEWPORTED_X or Type == TextBoxType::TEXTBOX_VIEWPORTED_XY) ? viewportPosition.x : 0.0f;
				float viewY = (Type == TextBoxType::TEXTBOX_VIEWPORTED_Y or Type == TextBoxType::TEXTBOX_VIEWPORTED_XY) ? viewportPosition.y : 0.0f;

				float textStartX = RealPos.x + textParams.x;
				float textStartY = RealPos.y + textParams.y;
				float clickX = SIMPLEUI_GLOBAL::mousePosition.x - textStartX + viewX;
				float clickY = SIMPLEUI_GLOBAL::mousePosition.y - textStartY + viewY;

				int currentLine = clickY / textParams.z + 1;

				CursorIndex = 0;

				if (!Text.empty() and !charOffsets.empty()) {
					int startIdx = 0;
					int currentL = 1;

					for (int i = 0; i < (int)charOffsets.size(); i++) {
						if (currentL == currentLine) {
							startIdx = i;
							break;
						}
						if (Text[charOffsets[i]] == '\n') {
							currentL++;
						}
					}

					if (currentL == currentLine) {
						int endIdx = startIdx;
						while (endIdx < (int)charOffsets.size() and Text[charOffsets[endIdx]] != '\n' and Text[charOffsets[endIdx]] != '\0') {
							endIdx++;
						}

						int byteStart = charOffsets[startIdx];
						int byteEnd = (endIdx < (int)charOffsets.size()) ? charOffsets[endIdx] : Text.size();

						CursorIndex = endIdx;

						for (int i = startIdx; i <= endIdx; i++) {
							int currentByte = (i < (int)charOffsets.size()) ? charOffsets[i] : Text.size();
							float widthCurr = MeasureTextEx(getFont(!FontFace), Text.substr(byteStart, currentByte - byteStart).c_str(), textParams.z, Spacing).x;

							int prevByte = (i > startIdx) ? charOffsets[i - 1] : byteStart;
							float widthPrev = (i > startIdx) ? MeasureTextEx(getFont(!FontFace), Text.substr(byteStart, prevByte - byteStart).c_str(), textParams.z, Spacing).x : 0.0f;

							if (clickX < (widthPrev + widthCurr) / 2.0) {
								CursorIndex = (i > startIdx) ? i - 1 : startIdx;
								break;
							}
						}
					} else if (currentLine > currentL) {
						CursorIndex = charOffsets.size();
					}
				}
			}
		}

		if (SIMPLEUI_GLOBAL::FocusedTextBox == this and Visible and CanType) {
			if (maxSymbols >= charOffsets.size() or maxSymbols < 0) {
				int symbolsLeft = maxSymbols - static_cast<int>(charOffsets.size());
				int addedSymbols = 0;
				std::string buf;

				int key = GetCharPressed();
				while (key > 0) {
					if (symbolsLeft > 0 or maxSymbols < 0) {
						int bytes = 0;
						const char* utf8 = CodepointToUTF8(key, &bytes);
						if (utf8 and bytes > 0) {
							std::string_view utf8View(utf8, bytes);

							bool allowed = (AllowedSymbols.size() ? AllowedSymbols.find(utf8View) != std::string::npos : true);
							bool disallowed = (DisallowedSymbols.size() ? DisallowedSymbols.find(utf8View) != std::string::npos : false);

							if (allowed and not disallowed) {
								symbolsLeft--;
								addedSymbols++;
								buf.append(utf8, bytes);
							}
						}
					}
					key = GetCharPressed();
				}

				if (addedSymbols > 0) {
					updateCharOffsets();
					int bytePos = (CursorIndex < (int)charOffsets.size()) ? charOffsets[CursorIndex] : Text.size();
					Text = Text.substr(0, bytePos) + buf + Text.substr(bytePos);
					CursorIndex += addedSymbols;
					updateCharOffsets();
					CursorVisible = true; CursorTime = 0.0f;
				}
			}
		}

		if (SIMPLEUI_GLOBAL::FocusedTextBox == this and Visible and CanType) {
			if (IsKeyPressed(KEY_BACKSPACE)) {
				if (IsKeyDown(KEY_LEFT_CONTROL)) {
					if (CursorIndex > 0) {
						int start = CursorIndex;
						while (start > 0) {
							unsigned char c = Text[charOffsets[start - 1]];

							if (c != ' ')
								break;

							start--;
						}

						if (start > 0) {
							unsigned char c = Text[charOffsets[start - 1]];

							if (c == '.' or c == ',' or c == ':' or
								c == ';' or c == '?' or c == '!' or
								c == '/' or c == '\\' or c == '\'' or
								c == '\"' or c == '\n') {
								start--;
							} else {
								while (start > 0) {
									c = Text[charOffsets[start - 1]];

									if (c == ' ' or c == '.' or c == ',' or
										c == ':' or c == ';' or c == '?' or
										c == '!' or c == '/' or c == '\\' or
										c == '\'' or c == '\"' or c == '\n')
									{
										break;
									}

									start--;
								}
							}
						}

						Text = Text.substr(0, charOffsets[start]) + Text.substr(charOffsets[CursorIndex]);
						CursorIndex = start;

						updateCharOffsets();
					}
				} else {
					if (CursorIndex > 0) {
						Text = Text.substr(0, charOffsets[CursorIndex - 1]) + Text.substr(charOffsets[CursorIndex]);
						CursorIndex--;

						updateCharOffsets();
					}
				}

				CursorVisible = true;
				CursorTime = 0.0f;
			}

			if (IsKeyPressed(KEY_DELETE)) {
				if (CursorIndex < (int)charOffsets.size() - 1) {
					Text = Text.substr(0, charOffsets[CursorIndex]) + Text.substr(charOffsets[CursorIndex + 1]);

					updateCharOffsets();
				}

				CursorVisible = true;
				CursorTime = 0.0f;
			}

			if (IsKeyPressed(KEY_LEFT)) {
				if (IsKeyDown(KEY_LEFT_CONTROL)) {
					while (CursorIndex > 0) {
						unsigned char c = Text[charOffsets[CursorIndex - 1]];

						if (c != ' ')
							break;

						CursorIndex--;
					}

					while (CursorIndex > 0) {
						unsigned char c = Text[charOffsets[CursorIndex - 1]];

						if (c == ' ')
							break;

						CursorIndex--;
					}
				} else {
					CursorIndex--;
				}

				if (CursorIndex < 0)
					CursorIndex = 0;

				CursorVisible = true;
				CursorTime = 0.0f;
			}

			if (IsKeyPressed(KEY_RIGHT)) {
				int maxIndex = (int)charOffsets.size() - 1;

				if (IsKeyDown(KEY_LEFT_CONTROL)) {
					while (CursorIndex < maxIndex) {
						unsigned char c = Text[charOffsets[CursorIndex]];

						if (c == ' ')
							break;

						CursorIndex++;
					}

					while (CursorIndex < maxIndex) {
						unsigned char c = Text[charOffsets[CursorIndex]];

						if (c != ' ')
							break;

						CursorIndex++;
					}
				} else {
					CursorIndex++;
				}

				if (CursorIndex > maxIndex)
					CursorIndex = maxIndex;

				CursorVisible = true;
				CursorTime = 0.0f;
			}

			if (IsKeyDown(KEY_LEFT_CONTROL) and IsKeyPressed(KEY_V) and ClipboardPasteAllowed) {
				std::string clipboardText = GetClipboardText();
				int symbolsLeft = maxSymbols - static_cast<int>(charOffsets.size());

				if (symbolsLeft > 0 or maxSymbols < 0) {
					std::string toPaste = clipboardText;

					bool allowed = true;
					if (ClipboardPasteCondition and !ClipboardPasteCondition(toPaste)) allowed = false;

					if (allowed) {
						updateCharOffsets();
						int bytePos = (CursorIndex < (int)charOffsets.size()) ? charOffsets[CursorIndex] : Text.size();
						Text = Text.substr(0, bytePos) + toPaste + Text.substr(bytePos);
						CursorIndex += getCharOffsets(toPaste).size() - 1;
						updateCharOffsets();
						CursorVisible = true; CursorTime = 0.0f;
					}
				}
			}

			if (EnterInputCondition != TextBoxNextLine::TEXTBOX_NEXTLINE_NOT_ALLOWED and (maxSymbols < charOffsets.size() or maxSymbols < 0)) {
				bool enter = IsKeyPressed(KEY_ENTER);

				if (enter) {
					bool ctrl = IsKeyDown(KEY_LEFT_CONTROL);
					bool shift = IsKeyDown(KEY_LEFT_SHIFT);

					bool allowed = false;

					if (EnterInputCondition == TextBoxNextLine::TEXTBOX_NEXTLINE_ENTER) allowed = true;
					if (EnterInputCondition == TextBoxNextLine::TEXTBOX_NEXTLINE_CTRL_ENTER and ctrl) allowed = true;
					if (EnterInputCondition == TextBoxNextLine::TEXTBOX_NEXTLINE_SHIFT_ENTER and shift) allowed = true;

					if (allowed) {
						updateCharOffsets();
						int bytePos = (CursorIndex < (int)charOffsets.size()) ? charOffsets[CursorIndex] : Text.size();
						Text = Text.substr(0, bytePos) + '\n' + Text.substr(bytePos);
						CursorIndex += 1;
						updateCharOffsets();
						CursorVisible = true; CursorTime = 0.0f;
					}
				}
			}

			if (IsKeyPressed(KEY_UP)) {
				int s = -1;
				int s1 = -1;
				int charI = -1;
				int charI1 = -1;
				for (int i = CursorIndex - 1; i >= 0; i--) {
					if (Text[charOffsets[i]] == '\n') {
						if (s == -1) {
							s = charOffsets[i + 1];
							charI = i + 1;
						} else {
							s1 = charOffsets[i + 1];
							charI1 = i + 1;
							break;
						}
					}

					if (i == 0) {
						if (s == -1) s = 0;
						if (s1 == -1) s1 = 0;
					}
				}

				if (s == -1 or s1 == -1) return;

				std::string textBeforeCursorOnLine = (s == -1 ? "" : Text.substr(s, charOffsets[CursorIndex] - s));
				std::string textBeforeCursorOnPreviousLine = (s1 == -1 ? "" : Text.substr(s1, ((s - s1 > 0) ? (s - s1 - 1) : 0)));

				float currentX = MeasureTextEx(getFont(FontFace), textBeforeCursorOnLine.c_str(), textParams.z, Spacing).x;

				int left = charI1;
				int right = (charI > 0) ? charI - 1 : charI1;
				int targetCharI = left;

				while (left <= right) {
					int mid = left + (right - left) / 2;
					std::string prefix = Text.substr(s1, charOffsets[mid] - s1);
					float midX = MeasureTextEx(getFont(FontFace), prefix.c_str(), textParams.z, Spacing).x;

					if (midX <= currentX) {
						targetCharI = mid;
						left = mid + 1;
					} else {
						right = mid - 1;
					}
				}

				if (targetCharI < ((charI > 0) ? charI - 1 : charI1)) {
					std::string prefix1 = Text.substr(s1, charOffsets[targetCharI] - s1);
					float x1 = MeasureTextEx(getFont(FontFace), prefix1.c_str(), textParams.z, Spacing).x;

					std::string prefix2 = Text.substr(s1, charOffsets[targetCharI + 1] - s1);
					float x2 = MeasureTextEx(getFont(FontFace), prefix2.c_str(), textParams.z, Spacing).x;

					if ((x2 - currentX) < (currentX - x1)) {
						targetCharI++;
					}
				}
				if (targetCharI == -1) return;
				CursorIndex = targetCharI;
				CursorVisible = true;
				CursorTime = 0.0f;
			}

			if (IsKeyPressed(KEY_DOWN)) {
				int s = -1;
				int s1 = -1;
				int s2 = -1;
				int charI = -1;
				int charI1 = -1;
				int charI2 = -1;

				for (int i = CursorIndex - 1; i >= 0; i--) {
					if (Text[charOffsets[i]] == '\n') {
						s = charOffsets[i + 1];
						charI = i + 1;
						break;
					}
				}

				if (s == -1) {
					s = 0;
					charI = 0;
				}

				for (size_t i = CursorIndex; i < charOffsets.size(); i++) {
					if (charOffsets[i] >= Text.size()) {
						if (s1 != -1 and s2 == -1) {
							s2 = Text.size();
							charI2 = i;
						}
						break;
					}

					if (Text[charOffsets[i]] == '\n') {
						if (s1 == -1) {
							s1 = charOffsets[i + 1];
							charI1 = i + 1;
						} else {
							s2 = charOffsets[i];
							charI2 = i;
							break;
						}
					}
				}

				if (s1 == -1) return;

				if (s2 == -1) {
					s2 = Text.size();
					charI2 = charOffsets.size() - 1;
				}

				std::string textBeforeCursorOnLine = Text.substr(s, charOffsets[CursorIndex] - s);
				float currentX = MeasureTextEx(getFont(FontFace), textBeforeCursorOnLine.c_str(), textParams.z, Spacing).x;

				int left = charI1;
				int right = charI2;
				int targetCharI = left;

				while (left <= right) {
					int mid = left + (right - left) / 2;
					std::string prefix = Text.substr(s1, charOffsets[mid] - s1);
					float midX = MeasureTextEx(getFont(FontFace), prefix.c_str(), textParams.z, Spacing).x;

					if (midX <= currentX) {
						targetCharI = mid;
						left = mid + 1;
					} else {
						right = mid - 1;
					}
				}

				if (targetCharI < charI2) {
					std::string prefix1 = Text.substr(s1, charOffsets[targetCharI] - s1);
					float x1 = MeasureTextEx(getFont(FontFace), prefix1.c_str(), textParams.z, Spacing).x;

					std::string prefix2 = Text.substr(s1, charOffsets[targetCharI + 1] - s1);
					float x2 = MeasureTextEx(getFont(FontFace), prefix2.c_str(), textParams.z, Spacing).x;

					if ((x2 - currentX) < (currentX - x1)) {
						targetCharI++;
					}
				}

				CursorIndex = targetCharI;
				CursorVisible = true;
				CursorTime = 0.0f;
			}
		}
	}

	void Update(bool posOrSizeChanged) override {
		if (lastUpdateFrame == SIMPLEUI_GLOBAL::framesSinceStart) return;
		lastUpdateFrame = SIMPLEUI_GLOBAL::framesSinceStart;

		if (!(SIMPLEUI_GLOBAL::FocusedTextBox == this)) { CursorIndex = -1; CursorVisible = false; deleteText = true; }

		eventHandler();
		if (SIMPLEUI_GLOBAL::deletedObjectsByID[uniqueID]) return;

		if (!Visible) { CursorIndex = -1; CursorVisible = false; Text = ""; if (posOrSizeChanged or posOrSizeChangedResult) updateWhenWillBeVisible = true; return; }

		inputHandler();

		if (posOrSizeChanged or posOrSizeChangedResult or updateWhenWillBeVisible) {
			getRealObject2Dsize();
			getRealObject2Dposition();
		}

		SameUpdate();

		if (updateChildrenZIndex) {
			updateChildren(this);
		}

		if (lastCursorIndex != CursorIndex) {
			bool calcX = (Type == TextBoxType::TEXTBOX_VIEWPORTED_X or Type == TextBoxType::TEXTBOX_VIEWPORTED_XY);
			bool calcY = (Type == TextBoxType::TEXTBOX_VIEWPORTED_Y or Type == TextBoxType::TEXTBOX_VIEWPORTED_XY);

			if (Text.empty() or CursorIndex == -1) {
				if (calcX) viewportPosition.x = 0.0f;
				if (calcY) viewportPosition.y = 0.0f;
			} else {
				int s = 0;
				for (int i = CursorIndex - 1; i >= 0; i--) {
					if (Text[charOffsets[i]] == '\n') {
						s = charOffsets[i + 1];
						break;
					}
				}

				if (!charOffsets.empty()) {
					std::string textBeforeCursorOnLine = Text.substr(s, charOffsets[CursorIndex] - s);
					std::string textBeforeCursor = Text.substr(0, charOffsets[CursorIndex]);
					SpecialVector2 textSizeY = MeasureTextEx(getFont(!FontFace), textBeforeCursor.c_str(), textParams.z, Spacing);
					SpecialVector2 textSizeX = MeasureTextEx(getFont(!FontFace), textBeforeCursorOnLine.c_str(), textParams.z, Spacing);

					SpecialVector2 textSize = { textSizeX.x, textSizeY.y };

					if (calcX) {
						float currentX = textSize.x;

						if (currentX - viewportPosition.x >= RealSize.x) {
							viewportPosition.x = currentX - RealSize.x;
						} else if (currentX < viewportPosition.x) {
							viewportPosition.x = currentX;
						}
					}

					if (calcY) {
						float currentY = textSize.y;
						if (currentY == 0) {
							viewportPosition.y = 0;
						} else {
							if (currentY - viewportPosition.y >= RealSize.y) {
								viewportPosition.y = currentY - RealSize.y;
							} else if (currentY - textParams.z < viewportPosition.y) {
								viewportPosition.y = currentY - textParams.z;
							}
						}
					}
				}
			}

			lastCursorIndex = CursorIndex;
		}

		Draw();

		bool tempRes = posOrSizeChanged or posOrSizeChangedResult or updateWhenWillBeVisible;
		posOrSizeChangedResult = false;
		updateWhenWillBeVisible = false;

		Text.restate();
		FontFace.restate();
		PlaceholderText.restate();

		for (int i = 0; i < Children.size(); i++) {
			Instance* child = Children[i];
			child->Update(tempRes);
		}
	};

	size_t size() {
		updateCharOffsets();
		return charOffsets.size();
	}

	void SetText(const std::string& t) {
		std::vector<int> offsets;
		for (int i = 0; i < t.size();) {
			unsigned char c = t[i];
			offsets.push_back(i);
			if (c < 0x80) i += 1;
			else if ((c & 0xE0) == 0xC0) i += 2;
			else if ((c & 0xF0) == 0xE0) i += 3;
			else if ((c & 0xF8) == 0xF0) i += 4;
			else i += 1;
		}

		if (offsets.size() > maxSymbols) {
			Text = t.substr(0, offsets[maxSymbols]);
			updateCharOffsets();
			CursorIndex = maxSymbols;
			return;
		}

		Text = t;
		updateCharOffsets();
		CursorIndex = t.size();
	}

	const SUI_Text& GetText() const {
		return Text;
	}

	TextBox* Clone() const override {
		TextBox* i = new TextBox(*this);
		i->UpdateAllVectorPointers();
		i->posOrSizeChangedResult = true;

		i->basicCloneOperation(const_cast<TextBox*>(this));

		i->cachedText.id = 0;
		i->cachedText.currentAtlas = nullptr;

		return i;
	}

	static TextBox* New(Instance* parent = nullptr) {
		TextBox* i = new TextBox(parent);
		return i;
	}
};

enum ImageOverlayFormat {
	IMAGE_STRETCH = 0, // STRETCH ON FULL SIZE
	IMAGE_FIT, // FIT WITH ASPECT SAVING
	IMAGE_CROP, // CUT EXCESS
};

class ImageLabel : public Object2D {
	constexpr static const char* DefaultName = "ImageLabel";
	constexpr static InstanceType DefaultClass = IMAGELABEL;

	AtlasTexture tex{};
	Image imageIfMemory{};
	std::string currentPair;

	void updateTexture() {
		if (tex.id == 0 and imageIfMemory.data and currentPair.empty()) {
			tex = LoadTextureOnAtlas(imageIfMemory);
		}
	}
protected:
	ImageLabel(bool a) : Object2D(a) { Name = DefaultName; Class = DefaultClass; };
	ImageLabel(Instance* p) : Object2D(p) { Name = DefaultName; Class = DefaultClass; }

	ImageLabel() = delete;

	~ImageLabel() override {
		if (tex.id != 0 and imageIfMemory.data) UnloadTextureFromAtlas(tex);
		if (imageIfMemory.data) UnloadImage(imageIfMemory);
	}
public:
	ImageOverlayFormat Overlay = ImageOverlayFormat::IMAGE_FIT;
	float ImageTransparency = 0.0f;
	Color ImageColor = { 255,255,255,255 };
	bool RoundImage = false;
	float Rotation = 0;
	SpecialVector2 Origin = { 0, 0 };
	SpecialVector2 OriginOFFSET = { 0, 0 };

	void setImage(const std::string& name = "") {
		if (imageIfMemory.data) {
			UnloadImage(imageIfMemory);
			UnloadTextureFromAtlas(tex);
		}

		auto pair = getImage(name);
		tex = pair.second;
		currentPair = name;
	}

	void Draw() override {
		if (!Visible) return;
		Object2D::Draw();

		if (RealPos.x + RealSize.x + BorderThickness < 0
			or RealPos.x - BorderThickness > SIMPLEUI_GLOBAL::winWidth
			or RealPos.y + RealSize.y + BorderThickness < 0
			or RealPos.y - BorderThickness > SIMPLEUI_GLOBAL::winHeight) {
			return;
		}

		updateTexture();

		if (tex.id) {
			Rectangle destRec = { RealPos.x + OriginOFFSET.x + RealSize.x * Origin.x, RealPos.y + OriginOFFSET.y + RealSize.y * Origin.y, RealSize.x, RealSize.y };
			Rectangle srcRec = { 0, 0, tex.size.x, tex.size.y };

			if (Overlay == ImageOverlayFormat::IMAGE_FIT) {
				float imageAspect = (float)tex.size.x / tex.size.y;
				float rectAspect = RealSize.x / RealSize.y;

				if (imageAspect > rectAspect) {
					float scaledHeight = RealSize.x / imageAspect;
					destRec.y += (RealSize.y - scaledHeight) / 2.0f;
					destRec.height = scaledHeight;
				} else {
					float scaledWidth = RealSize.y * imageAspect;
					destRec.x += (RealSize.x - scaledWidth) / 2.0f;
					destRec.width = scaledWidth;
				}
			} else if (Overlay == ImageOverlayFormat::IMAGE_CROP) {
				float imageAspect = (float)tex.size.x / tex.size.y;
				float rectAspect = RealSize.x / RealSize.y;

				if (imageAspect > rectAspect) {
					float cropWidth = tex.size.y * rectAspect;
					srcRec.x = (tex.size.x - cropWidth) / 2.0f;
					srcRec.width = cropWidth;
				} else {
					float cropHeight = tex.size.x / rectAspect;
					srcRec.y = (tex.size.y - cropHeight) / 2.0f;
					srcRec.height = cropHeight;
				}
			}

			srcRec.x = std::floorf(srcRec.x);
			srcRec.y = std::floorf(srcRec.y);
			srcRec.width = std::ceilf(srcRec.width);
			srcRec.height = std::ceilf(srcRec.height);

			destRec.x = std::floorf(destRec.x);
			destRec.y = std::floorf(destRec.y);
			destRec.width = std::ceilf(destRec.width);
			destRec.height = std::ceilf(destRec.height);

			RL_FUNCTIONS_PLUS::DrawTexturePro(tex, RealPos, RealSize, srcRec, destRec, { OriginOFFSET.x + Origin.x * RealSize.x, OriginOFFSET.y + Origin.y * RealSize.y }, Rotation, { ImageColor.r, ImageColor.g, ImageColor.b, (unsigned char)(ImageColor.a * (1 - ImageTransparency)) }, (RoundImage ? Roundness : 0));
		} else {
			if (currentPair == "" or imageIfMemory.data) return;
			setImage(currentPair);
		}
	}

	void UpdateImageFromMemory(const std::string& type, const std::vector<unsigned char>& data) {
		if (imageIfMemory.data) {
			UnloadImage(imageIfMemory);
		}

		imageIfMemory = RAYLIB_FUNCTIONAL::LoadImageFromMemory(type.c_str(), data.data(), data.size());

		if (!imageIfMemory.data) {
			std::cout << RED_ANSI << "UpdateFromMemory FAILED" << DEFAULT_ANSI << std::endl;
			return;
		}

		if (tex.id != 0 and tex.currentAtlas) UnloadTextureFromAtlas(tex);

		tex.id = 0;
		currentPair = "";
	}

	ImageLabel* Clone() const override {
		ImageLabel* i = new ImageLabel(*this);
		i->UpdateAllVectorPointers();
		i->posOrSizeChangedResult = true;

		i->basicCloneOperation(const_cast<ImageLabel*>(this));

		if (imageIfMemory.data) {
			Image im{};
			i->imageIfMemory = im;
			i->tex.id = 0;
		}

		return i;
	}

	static ImageLabel* New(Instance* parent = nullptr) {
		ImageLabel* i = new ImageLabel(parent);
		return i;
	}
};

class TextureLabel : public Object2D {
	constexpr static const char* DefaultName = "TextureLabel";
	constexpr static InstanceType DefaultClass = TEXTURELABEL;

	Image img{};
	bool imageLoadedWhileNotReady = false;
	Texture texture{};
	bool owner = false;

	void SetSize(int w, int h) {
		if (texture.id == 0 or texture.width != w or texture.height != h or !owner) {
			owner = true;
			if (texture.id != 0) UnloadTexture(texture);

			Image img = GenImageColor(w, h, BLANK);
			texture = LoadTextureFromImage(img);
			UnloadImage(img);
		}
	}
protected:
	TextureLabel(bool a) : Object2D(a) { Name = DefaultName; Class = DefaultClass; };
	TextureLabel(Instance* p) : Object2D(p) { Name = DefaultName; Class = DefaultClass; }

	TextureLabel() = delete;

	~TextureLabel() override {
		if (texture.id != 0 and owner) UnloadTexture(texture);
	}
public:
	float Rotation = 0;
	Color TextureColor = { 255,255,255,255 };
	SpecialVector2 Origin = { 0, 0 };

	void Draw() override {
		if (Visible) {
			Object2D::Draw();

			if (imageLoadedWhileNotReady) {
				imageLoadedWhileNotReady = false;

				if (img.data != nullptr) {
					if (texture.id != 0 and owner) UnloadTexture(texture);

					owner = true;
					texture = LoadTextureFromImage(img);
					SetTextureFilter(texture, TEXTURE_FILTER_TRILINEAR);
					UnloadImage(img);
				}
			}

			if (RealPos.x + RealSize.x + BorderThickness < 0
				or RealPos.x - RealSize.x - BorderThickness > SIMPLEUI_GLOBAL::winWidth
				or RealPos.y + RealSize.y + BorderThickness < 0
				or RealPos.y - RealSize.y - BorderThickness > SIMPLEUI_GLOBAL::winHeight) {
				return;
			}

			if (texture.id == 0) {
				return;
			}

			RL_FUNCTIONS_PLUS::DrawTexturePro(texture, RealPos, RealSize, { 0,0,(float)texture.width,(float)texture.height }, { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, Origin, Rotation, TextureColor, 0);
		}
	}

	void UpdateWithType(const std::string& type, std::vector<unsigned char>& data) {
		if (!IsWindowReady()) {
			if (imageLoadedWhileNotReady) {
				UnloadImage(img);
			}
		}

		img = RAYLIB_FUNCTIONAL::LoadImageFromMemory(type.c_str(), data.data(), data.size());

		if (img.data == nullptr) return;
		if (texture.id != 0 and owner) UnloadTexture(texture);

		if (IsWindowReady()) {
			imageLoadedWhileNotReady = false;

			owner = true;
			texture = LoadTextureFromImage(img);
			GenTextureMipmaps(&texture);
			SetTextureFilter(texture, TEXTURE_FILTER_TRILINEAR);
			UnloadImage(img);
		} else {
			imageLoadedWhileNotReady = true;
		}
	}

	void UpdateData(std::vector<char>& data, int w, int h) {
		SetSize(w, h);
		UpdateTexture(texture, data.data());
		owner = true;
	}

	TextureLabel* Clone() const override {
		TextureLabel* i = new TextureLabel(*this);
		i->UpdateAllVectorPointers();
		i->posOrSizeChangedResult = true;

		i->basicCloneOperation(const_cast<TextureLabel*>(this));

		i->owner = false;

		return i;
	}

	static TextureLabel* New(Instance* parent = nullptr) {
		TextureLabel* i = new TextureLabel(parent);
		return i;
	}
};

inline void Object2D::PosOrSizeChanged() {
	SIMPLEUI_GLOBAL::sceneDirty = true;
	posOrSizeChangedResult = true;
	Instance* scrollChild = (Parent and Parent->Class == SCROLLFRAME ? this : getAncestorWhichParentIsScrollFrame(this));

	if (scrollChild) {
		static_cast<ScrollFrame*>(scrollChild->Parent)->UpdateSectors(scrollChild);
	}
}

inline void Object2D::AddEvent(EventType t, InstanceCallback f, MouseButtonType m) {
	events.push_back({ t, f, m });

	Instance* asc = findFirstAncestorOfClass(SCROLLFRAME);

	if (asc) {
		static_cast<ScrollFrame*>(asc)->UpdateObjectTickState(this);
	}
}

inline void Instance::AddEvent(EventType t, InstanceCallback f, MouseButtonType m = MouseButtonType::MOUSE_NONE) {
	events.push_back({ t, f });

	Instance* asc = findFirstAncestorOfClass(SCROLLFRAME);

	if (asc) {
		static_cast<ScrollFrame*>(asc)->UpdateObjectTickState(this);
	}
}

inline void Instance::setParent(Instance* ptr) {
	if (ptr == this) return;

	SIMPLEUI_GLOBAL::sceneDirty = true;

	if (Parent != nullptr) {
		for (int i = 0; i < Parent->Children.size(); i++) {
			if (Parent->Children[i] == this) {
				Parent->Children.erase(Parent->Children.begin() + i);
				break;
			}
		}

		Parent->childsRemovedInFrame.insert({ this->uniqueID, this });
	}

	Parent = ptr;
	if (ptr) {
		ptr->Children.push_back(this);
		ptr->childsAddedInFrame.insert({ this->uniqueID, this });
		ptr->updateChildrenZIndex = true;

		ScrollFrame* prob = (ptr->Class == SCROLLFRAME ? static_cast<ScrollFrame*>(ptr) : (ScrollFrame*)nullptr);
		if (prob) {
			prob->UpdateSectors(this);
		}
	}
}

inline void Delete(Instance* ptr) {
	if (!ptr) return;
	if (ptr == GetRoot()) {
		std::cout << YELLOW_ANSI << "Root object has resistance from deleting" << DEFAULT_ANSI << std::endl;
		return;
	}

	if (ptr->Parent) {
		ptr->Parent->childsRemovedInFrame.insert({ ptr->uniqueID, ptr });
		SIMPLEUI_GLOBAL::deletedObjectsByID[ptr->uniqueID] = 1;

		auto it = ptr->Parent->childsAddedInFrame.find(ptr->uniqueID);
		if (it != ptr->Parent->childsAddedInFrame.end()) {
			ptr->Parent->childsAddedInFrame.erase(it);
		}

		Instance* scrollChild = getAncestorWhichParentIsScrollFrame(ptr);

		if (scrollChild and scrollChild != ptr) {
			static_cast<ScrollFrame*>(scrollChild->Parent)->UpdateSectors(scrollChild);
		}

		for (int i = 0; i < ptr->Parent->Children.size(); i++) {
			if (ptr->Parent->Children[i] == ptr) {
				ptr->Parent->Children.erase(ptr->Parent->Children.begin() + i);
				break;
			}
		}
	}

	std::vector<Instance*> z = ptr->Children;
	for (int i = 0; i < z.size(); i++) {
		Instance* child = z[i];
		Delete(child);
	}

	ptr->setParent(nullptr);
	ptr->Children.clear();
	z.clear();

	delete ptr;
}

inline Instance::Instance(Instance* p) : Parent(p), uniqueID(SIMPLEUI_GLOBAL::currentUniqueObjectID++) {
	SIMPLEUI_GLOBAL::sceneDirty = true;
	SIMPLEUI_GLOBAL::deletedObjectsByID.push_back(0);
	if (p) {
		p->Children.push_back(this);
		p->childsAddedInFrame.insert({ uniqueID, this });
		p->updateChildrenZIndex = true;

		ScrollFrame* prob = (p->Class == SCROLLFRAME ? static_cast<ScrollFrame*>(p) : (ScrollFrame*)nullptr);
		if (prob) {
			prob->UpdateSectors(this);
		}
	}
}

inline void Object2D::eventHandler() {
	if (events.empty()) return;

	bool mouseOnObject = false;
	bool mouseCalculated = false;
	bool hasStartHold1 = false;
	bool hasStartHold2 = false;
	bool hasStartHold3 = false;

	std::function<void(Instance*)> mouseReleased1;
	std::function<void(Instance*)> mouseReleased2;
	std::function<void(Instance*)> mouseReleased3;

	Instance* higherObject = SIMPLEUI_GLOBAL::higherObject;
	Instance* PreviousHigherObject = SIMPLEUI_GLOBAL::PreviousHigherObject;

	for (const auto& [type, func, mouse] : events) {
		switch (type) {
			case TICK: {
				func(this);
				break;
			} case MOUSE_ENTER: {
				bool entered = false;
				if (!mouseCalculated) {
					mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
					mouseCalculated = true;
				}

				if (mouseOnObject) {
					bool enterAllowed = (
						EnterEventCondition == SUI_EEC::EEC_DEFAULT ? this == higherObject :
						(EnterEventCondition == SUI_EEC::EEC_EVERY_ENTER ? true :
							EnterEventCondition == SUI_EEC::EEC_IF_DESCENDANT_HIGHER ? ((higherObject == this and higherObject != nullptr) or (higherObject and higherObject != this and higherObject->isDescendantOf(this))) : false)
						);

					if (Visible and ((higherObject == this and PreviousHigherObject != this) or enterAllowed)) {
						entered = true;
					}
				}

				if (entered and !MouseEntered) {
					MouseEntered = true;
					func(this);
				}
				break;
			} case MOUSE_LEAVE: {
				if (!mouseCalculated) {
					mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
					mouseCalculated = true;
				}

				bool enterAllowed = (
					EnterEventCondition == SUI_EEC::EEC_DEFAULT ? this == higherObject :
					(EnterEventCondition == SUI_EEC::EEC_EVERY_ENTER ? true :
						EnterEventCondition == SUI_EEC::EEC_IF_DESCENDANT_HIGHER ? (higherObject == this or (higherObject and higherObject != this and higherObject->isDescendantOf(this))) : false)
					);

				if (MouseEntered and (!Visible or !mouseOnObject or !enterAllowed)) {
					MouseEntered = false;
					func(this);
				}
				break;
			} case MOUSE_CLICK: {
				if (!mouseCalculated) {
					mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
					mouseCalculated = true;
				}

				if (IsMouseButtonPressed(mouse) and mouseOnObject and higherObject == this) {
					func(this);
				}
				break;
			} case MOUSE_HOLD_START: {
				if (!mouseCalculated) {
					mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
					mouseCalculated = true;
				}

				if (IsMouseButtonPressed(mouse) and mouseOnObject and higherObject == this) {
					if (mouse == MOUSE_LEFT) {
						startedOnObject1 = true;
					} else if (mouse == MOUSE_RIGHT) {
						startedOnObject2 = true;
					} else if (mouse == MOUSE_MIDDLE) {
						startedOnObject3 = true;
					}
					func(this);
				}

				if (mouse == MOUSE_LEFT) {
					hasStartHold1 = true;
				} else if (mouse == MOUSE_RIGHT) {
					hasStartHold2 = true;
				} else if (mouse == MOUSE_MIDDLE) {
					hasStartHold3 = true;
				}

				break;
			} case MOUSE_HOLD_END: {
				if (IsMouseButtonReleased(mouse)) {
					if (mouse == MOUSE_LEFT) {
						mouseReleased1 = func;
					} else if (mouse == MOUSE_RIGHT) {
						mouseReleased2 = func;
					} else if (mouse == MOUSE_MIDDLE) {
						mouseReleased3 = func;
					}
				}
				break;
			} case CHILD_ADDED: {
				for (auto& [id, ptr] : childsAddedInFrame) {
					func(this, ptr);
				}
				break;
			} case CHILD_REMOVED: {
				for (auto& [id, ptr] : childsRemovedInFrame) {
					func(this, ptr);
				}
				break;
			} case TEXT_CHANGED: {
				if (Class == TEXTLABEL) {
					if (static_cast<TextLabel*>(this)->Text.isChanged()) {
						func(this);
					}
				} else if (Class == TEXTBOX) {
					if (static_cast<TextBox*>(this)->Text.isChanged()) {
						func(this);
					}
				}
				break;
			}
		}
	}

	if (not hasStartHold1 and IsMouseButtonPressed(MOUSE_LEFT) and higherObject == this) {
		if (!mouseCalculated) {
			mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
			mouseCalculated = true;
		}

		if (mouseOnObject) {
			startedOnObject1 = true;
		}
	}

	if (not hasStartHold2 and IsMouseButtonPressed(MOUSE_RIGHT) and higherObject == this) {
		if (!mouseCalculated) {
			mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
			mouseCalculated = true;
		}

		if (mouseOnObject) {
			startedOnObject2 = true;
		}
	}

	if (not hasStartHold3 and IsMouseButtonPressed(MOUSE_MIDDLE) and higherObject == this) {
		if (!mouseCalculated) {
			mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
			mouseCalculated = true;
		}

		if (mouseOnObject) {
			startedOnObject3 = true;
		}
	}

	if (mouseReleased1 and startedOnObject1) {
		if (!mouseCalculated) {
			mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
			mouseCalculated = true;
		}

		if (mouseOnObject) mouseReleased1(this);
	}
	if (mouseReleased2 and startedOnObject2) {
		if (!mouseCalculated) {
			mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
			mouseCalculated = true;
		}

		if (mouseOnObject) mouseReleased2(this);
	}
	if (mouseReleased3 and startedOnObject3) {
		if (!mouseCalculated) {
			mouseOnObject = pointInObject(SIMPLEUI_GLOBAL::mousePosition);
			mouseCalculated = true;
		}

		if (mouseOnObject) mouseReleased3(this);
	}

	if (IsMouseButtonReleased(MOUSE_LEFT)) {
		startedOnObject1 = false;
	}
	if (IsMouseButtonReleased(MOUSE_RIGHT)) {
		startedOnObject2 = false;
	}
	if (IsMouseButtonReleased(MOUSE_MIDDLE)) {
		startedOnObject3 = false;
	}
}

inline std::vector<unsigned char> PngBytesToJpgBytes(const std::string& path, int quality = 60) {
	std::ifstream f(path, std::ios::binary);
	std::filesystem::path p(std::u8string(reinterpret_cast<const char8_t*>(path.c_str())));
	if (!f) return {};
	std::vector<unsigned char> buf((std::istreambuf_iterator<char>(f)), {});
	Image img = RAYLIB_FUNCTIONAL::LoadImageFromMemory(".png", buf.data(), (int)buf.size());
	if (!IsImageValid(img)) return {};

	if (img.data == nullptr) {
		return {};
	}

	if (img.width > 1920) {
		int targetWidth = 1920;
		int targetHeight = (img.height * 1920) / img.width;
		ImageResize(&img, targetWidth, targetHeight);
	}

	Image background = GenImageColor(img.width, img.height, WHITE);

	ImageDraw(&background, img,
		Rectangle{ 0, 0, (float)img.width, (float)img.height },
		Rectangle{ 0, 0, (float)img.width, (float)img.height },
		WHITE);

	ImageFormat(&background, PIXELFORMAT_UNCOMPRESSED_R8G8B8);

	int channels = 3;
	if (background.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8A8) {
		channels = 4;
	} else if (background.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8) {
		channels = 3;
	} else {
		ImageFormat(&background, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
		channels = 4;
	}

	std::vector<unsigned char> outBytes;

	stbi_write_jpg_to_func(
		[](void* context, void* data, int size) {
		auto* vec = static_cast<std::vector<unsigned char>*>(context);
		auto* bytes = static_cast<unsigned char*>(data);
		vec->insert(vec->end(), bytes, bytes + size);
	},
		&outBytes,
		background.width,
		background.height,
		channels,
		background.data,
		quality
	);

	UnloadImage(img);
	UnloadImage(background);

	return outBytes;
}

inline void DrawFrame(Instance* StartInstance) {
	BeginDrawing();
	ClearBackground({ 255,255,255,255 });
	StartInstance->Update(SIMPLEUI_GLOBAL::windowSizeChanged);
	FlushRectanglesBatch();
	EndDrawing();
}

inline void toggleFPS(Instance* s) {
	static TextLabel* labelFPS = nullptr;

	auto upd = []() {
		if (!labelFPS) return;

		labelFPS->Text = "  " + std::to_string(SIMPLEUI_GLOBAL::accurateFPS) + " FPS  ";
		Color c =
			(SIMPLEUI_GLOBAL::accurateFPS > 200) ? Color{ 153, 255, 204, 255 } :
			(SIMPLEUI_GLOBAL::accurateFPS > 120) ? Color{ 0, 255, 0, 255 } :
			(SIMPLEUI_GLOBAL::accurateFPS > 60) ? Color{ 255, 255, 102, 255 } :
			(SIMPLEUI_GLOBAL::accurateFPS > 30) ? Color{ 255, 178, 102, 255 } :
			(SIMPLEUI_GLOBAL::accurateFPS > 15) ? Color{ 255, 102, 102, 255 } :
			Color{ 255, 0, 0, 255 };
		labelFPS->TextColor = c;
	};

	if (!labelFPS) {
		labelFPS = TextLabel::New(s);
		labelFPS->BackgroundTransparency = 0.4;
		labelFPS->BackgroundColor = { 0, 0, 0, 255 };
		labelFPS->TextSize = -1;
		labelFPS->Name = "FPS_LABEL";
		labelFPS->Active = false;
		labelFPS->SizeOFFSET = SpecialVector2{ 180, 30 };
		labelFPS->Position = SpecialVector2{ 1, 0 };
		labelFPS->PositionOFFSET = SpecialVector2{ -180, 0 };
		labelFPS->ZIndex = 10000000;
		labelFPS->Visible = false;
		labelFPS->Roundness = 0.5;

		new ChangedSignal(SIMPLEUI_GLOBAL::accurateFPS, [upd]() {
			static int last = 0;
			if (last != SIMPLEUI_GLOBAL::accurateFPS or last == 0) {
				upd();
			}
		});
	}

	upd();

	labelFPS->Visible = !labelFPS->Visible;
}

inline namespace debug {
	inline int typeFPS[4]{
		60,
		144,
		-1,
		0
	};
	inline Color DefaultDebugColor = { 153, 204, 255, 255 };
	inline Color typeColor[9] = {
		DefaultDebugColor,
		{255,255,255,255},
		{255,102,102,255},
		{204,102,0,255},
		{255,255,204,255},
		{153,255,153,255},
		{51,0,102,255},
		{153,153,255,255},
		{0,51,102,255}
	};
	inline int currentColor = 0;

	inline ScrollFrame* console = nullptr;
	inline std::vector<std::string> textQueue;

	inline void print(const std::string& text) {
		if (!console) { textQueue.push_back(text); return; }
		TextLabel* sas = TextLabel::New(console);
		sas->BackgroundTransparency = 1;
		sas->TextColor = typeColor[currentColor]; sas->TextSize = -1;
		sas->FontFace = SIMPLEUI_GLOBAL::BASIC_FONT_NAME;
		sas->TextAnchor = TextAnchorEnum::W;
		int n = console->Children.size();
		sas->Name = std::to_string(n);
		sas->Text = text;
		sas->Size = SpecialVector2{ 1, 0.05 };
		sas->Position = SpecialVector2{ 0, 0.05f * (n - 1) };
		console->CanvasSize.y += 0.05 - (n > 20 ? 0 : 0.05);
		console->CanvasPosition.y = console->CanvasSize.y - 1;
	}

	inline Object2D* debugMenu = nullptr;
	inline bool Animations = true; // SOON
	inline int currentFPSindex = 3;
	inline bool lowGraphicsMode = false; // SOON

	inline int getCurrentMaxFPS() {
		return typeFPS[currentFPSindex] == 0 ? GetMonitorRefreshRate(GetCurrentMonitor()) : typeFPS[currentFPSindex];
	}

	inline Object2D* treeFrame = nullptr;
	inline Instance* currentInstance = nullptr;

	inline void initDebug(Instance* s) {
		if (debugMenu) return;
		debugMenu = Object2D::New(s);
		debugMenu->Size = SpecialVector2{ 1,1 };
		debugMenu->BackgroundTransparency = 0.9;
		debugMenu->BackgroundColor = DefaultDebugColor;
		debugMenu->Visible = false;
		debugMenu->ZIndex = 100000;
		debugMenu->Name = "debugMenu";

		TextLabel* lowerName = TextLabel::New(debugMenu);
		lowerName->Name = "debugName";
		lowerName->SetText("(F2) Debug Menu");
		lowerName->BackgroundColor = { 0,0,0,255 };
		lowerName->TextSize = -1;
		lowerName->TextColor = DefaultDebugColor;
		lowerName->Position = SpecialVector2{ 0.03f, 0.9f };
		lowerName->Size = SpecialVector2{ 0.24, 0.1 };
		lowerName->TextAnchor = TextAnchorEnum::SE;
		lowerName->BackgroundTransparency = 1;
		lowerName->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);

		/************************
		*       Settings        *
		************************/

		Object2D* SettingsFrame = Object2D::New(debugMenu);
		SettingsFrame->Size = SpecialVector2{ 0.4, 0.25 };
		SettingsFrame->Position = SpecialVector2{ 0.04, 0.03 };
		SettingsFrame->BackgroundTransparency = 0.2;
		SettingsFrame->BorderColor = DefaultDebugColor;
		SettingsFrame->BackgroundColor = { 0,0,0,255 };
		SettingsFrame->BorderThickness = 3;
		SettingsFrame->Name = "SettingsFrame";

		TextLabel* SettingsName = TextLabel::New(SettingsFrame);
		SettingsName->Name = "SettingsName";
		SettingsName->SetText("Settings");
		SettingsName->TextSize = -1;
		SettingsName->TextColor = DefaultDebugColor;
		SettingsName->Position = SpecialVector2{ 0.5, 0 };
		SettingsName->AnchorPosition = SpecialVector2{ 0.5, 0 };
		SettingsName->Size = SpecialVector2{ 0.8, 0.1 };
		SettingsName->TextAnchor = TextAnchorEnum::CENTER;
		SettingsName->BackgroundTransparency = 1;
		SettingsName->BackgroundColor = { 0,0,0,255 };
		SettingsName->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);

		TextLabel* AnimLabel = TextLabel::New(SettingsFrame);
		AnimLabel->Size = SpecialVector2{ 0.7, 0.2 };
		AnimLabel->BackgroundTransparency = 1;
		AnimLabel->BackgroundColor = { 0,0,0,255 };
		AnimLabel->Position = SpecialVector2{ 0, 0.1 };
		AnimLabel->SetText(" Animations");
		AnimLabel->TextAnchor = TextAnchorEnum::W;
		AnimLabel->TextSize = -1;
		AnimLabel->TextColor = DefaultDebugColor;
		AnimLabel->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		AnimLabel->Name = "animLabel";

		TextLabel* AnimButton = TextLabel::New(SettingsFrame);
		AnimButton->Size = SpecialVector2{ 0.19, 0.15 };
		AnimButton->BackgroundColor = Animations ? Color{ 204, 255, 204, 255 } : Color{ 255, 204, 204, 255 };
		AnimButton->Position = SpecialVector2{ 0.8, 0.125 };
		AnimButton->SetText(Animations ? " On " : " Off ");
		AnimButton->TextAnchor = TextAnchorEnum::W;
		AnimButton->TextSize = -1;
		AnimButton->TextColor = { 0,0,0,255 };
		AnimButton->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		AnimButton->Name = "animButton";
		AnimButton->Active = true;
		AnimButton->AddEvent(MOUSE_CLICK, [](Instance* t) {Animations = !Animations; }, MOUSE_LEFT);
		AnimButton->Roundness = 0.3;

		TextLabel* LGMlabel = TextLabel::New(SettingsFrame);
		LGMlabel->Size = SpecialVector2{ 0.7, 0.2 };
		LGMlabel->BackgroundTransparency = 1;
		LGMlabel->BackgroundColor = { 0,0,0,255 };
		LGMlabel->Position = SpecialVector2{ 0, 0.3 };
		LGMlabel->SetText(" Low Graphics Mode");
		LGMlabel->TextAnchor = TextAnchorEnum::W;
		LGMlabel->TextSize = -1;
		LGMlabel->TextColor = DefaultDebugColor;
		LGMlabel->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		LGMlabel->Name = "LGMlabel";

		TextLabel* LGMbutton = TextLabel::New(SettingsFrame);
		LGMbutton->Size = SpecialVector2{ 0.19, 0.15 };
		LGMbutton->BackgroundColor = lowGraphicsMode ? Color{ 204, 255, 204, 255 } : Color{ 255, 204, 204, 255 };
		LGMbutton->Position = SpecialVector2{ 0.8, 0.325 };
		LGMbutton->SetText(lowGraphicsMode ? " On " : " Off ");
		LGMbutton->TextAnchor = TextAnchorEnum::W;
		LGMbutton->TextSize = -1;
		LGMbutton->TextColor = { 0,0,0,255 };
		LGMbutton->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		LGMbutton->Name = "LGMbutton";
		LGMbutton->Active = true;
		LGMbutton->AddEvent(MOUSE_CLICK, [](Instance* t) {lowGraphicsMode = !lowGraphicsMode; }, MOUSE_LEFT);
		LGMbutton->Roundness = 0.3;

		TextLabel* FPSlabel = TextLabel::New(SettingsFrame);
		FPSlabel->Size = SpecialVector2{ 0.65, 0.2 };
		FPSlabel->BackgroundTransparency = 1;
		FPSlabel->BackgroundColor = { 0,0,0,255 };
		FPSlabel->Position = SpecialVector2{ 0, 0.5 };
		FPSlabel->SetText(" FPS mode");
		FPSlabel->TextAnchor = TextAnchorEnum::W;
		FPSlabel->TextSize = -1;
		FPSlabel->TextColor = DefaultDebugColor;
		FPSlabel->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		FPSlabel->Name = "FPSlabel";

		Object2D* FPSframe = TextLabel::New(SettingsFrame);
		FPSframe->Size = SpecialVector2{ 0.3, 0.2 };
		FPSframe->BackgroundTransparency = 1;
		FPSframe->BackgroundColor = { 0,0,0,255 };
		FPSframe->Roundness = 0.3;
		FPSframe->Position = SpecialVector2{ 0.7, 0.5 };
		FPSframe->Name = "FPSlabel";

		TextLabel* FPSleft = TextLabel::New(FPSframe);
		FPSleft->Size = SpecialVector2{ 0.25, 0.6 };
		FPSleft->BackgroundTransparency = 1;
		FPSleft->BackgroundColor = { 0,0,0,255 };
		FPSleft->Position = SpecialVector2{ 0.0, 0.2 };
		FPSleft->SetText("<");
		FPSleft->TextAnchor = TextAnchorEnum::CENTER;
		FPSleft->TextSize = -1;
		FPSleft->TextColor = DefaultDebugColor;
		FPSleft->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		FPSleft->Name = "FPSleft";
		FPSleft->Active = true;
		FPSleft->AddEvent(MOUSE_CLICK, [](Instance* t) { currentFPSindex--; currentFPSindex += 4; currentFPSindex = currentFPSindex % 4; }, MOUSE_LEFT);

		TextLabel* FPSquantity = TextLabel::New(FPSframe);
		FPSquantity->Size = SpecialVector2{ 0.5, 1 };
		FPSquantity->BackgroundTransparency = 1;
		FPSquantity->BackgroundColor = { 0,0,0,255 };
		FPSquantity->Position = SpecialVector2{ 0.25, 0 };
		std::ostringstream st; st << " " << typeFPS[currentFPSindex] << " ";
		FPSquantity->SetText(currentFPSindex == 2 ? "FULL" : ((currentFPSindex == 3) ? "V-SYNC" : st.str()));
		FPSquantity->TextSize = -1;
		FPSquantity->TextColor = DefaultDebugColor;
		FPSquantity->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		FPSquantity->Name = "FPSquantity";

		TextLabel* FPSright = TextLabel::New(FPSframe);
		FPSright->Size = SpecialVector2{ 0.25, 0.6 };
		FPSright->BackgroundTransparency = 1;
		FPSright->BackgroundColor = { 0,0,0,255 };
		FPSright->Position = SpecialVector2{ 0.75, 0.2 };
		FPSright->SetText(">");
		FPSright->TextAnchor = TextAnchorEnum::CENTER;
		FPSright->TextSize = -1;
		FPSright->TextColor = DefaultDebugColor;
		FPSright->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		FPSright->Name = "FPSright";
		FPSright->Active = true;
		FPSright->AddEvent(MOUSE_CLICK, [](Instance* t) { currentFPSindex++; currentFPSindex += 4; currentFPSindex = currentFPSindex % 4; }, MOUSE_LEFT);

		TextLabel* Colorlabel = TextLabel::New(SettingsFrame);
		Colorlabel->Size = SpecialVector2{ 0.65, 0.2 };
		Colorlabel->BackgroundTransparency = 1;
		Colorlabel->BackgroundColor = { 0,0,0,255 };
		Colorlabel->Position = SpecialVector2{ 0, 0.7 };
		Colorlabel->SetText(" Menu color");
		Colorlabel->TextAnchor = TextAnchorEnum::W;
		Colorlabel->TextSize = -1;
		Colorlabel->TextColor = DefaultDebugColor;
		Colorlabel->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		Colorlabel->Name = "Colorlabel";

		Object2D* Colorframe = TextLabel::New(SettingsFrame);
		Colorframe->Size = SpecialVector2{ 0.3, 0.2 };
		Colorframe->BackgroundTransparency = 1;
		Colorframe->BackgroundColor = { 0,0,0,255 };
		Colorframe->Roundness = 0.3;
		Colorframe->Position = SpecialVector2{ 0.7, 0.7 };
		Colorframe->Name = "Colorframe";

		TextLabel* Colorleft = TextLabel::New(Colorframe);
		Colorleft->Size = SpecialVector2{ 0.25, 0.6 };
		Colorleft->BackgroundTransparency = 1;
		Colorleft->BackgroundColor = { 0,0,0,255 };
		Colorleft->Position = SpecialVector2{ 0.0, 0.2 };
		Colorleft->SetText("<");
		Colorleft->TextAnchor = TextAnchorEnum::CENTER;
		Colorleft->TextSize = -1;
		Colorleft->TextColor = DefaultDebugColor;
		Colorleft->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		Colorleft->Name = "Colorleft";
		Colorleft->Active = true;
		Colorleft->AddEvent(MOUSE_CLICK, [](Instance* t) { currentColor--; currentColor += 9; currentColor = currentColor % 9; }, MOUSE_LEFT);

		Object2D* ColorBlock = TextLabel::New(Colorframe);
		ColorBlock->Size = SpecialVector2{ 0.5, 0.8 };
		ColorBlock->BackgroundColor = DefaultDebugColor;
		ColorBlock->Position = SpecialVector2{ 0.25, 0.1 };
		ColorBlock->Roundness = 0.3;
		ColorBlock->Name = "ColorBlock";

		TextLabel* Colorright = TextLabel::New(Colorframe);
		Colorright->Size = SpecialVector2{ 0.25, 0.6 };
		Colorright->BackgroundTransparency = 1;
		Colorright->BackgroundColor = { 0,0,0,255 };
		Colorright->Position = SpecialVector2{ 0.75, 0.2 };
		Colorright->SetText(">");
		Colorright->TextAnchor = TextAnchorEnum::CENTER;
		Colorright->TextSize = -1;
		Colorright->TextColor = DefaultDebugColor;
		Colorright->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);
		Colorright->Name = "Colorright";
		Colorright->Active = true;
		Colorright->AddEvent(MOUSE_CLICK, [](Instance* t) { currentColor++; currentColor += 9; currentColor = currentColor % 9; }, MOUSE_LEFT);

		/******************
		*       logs      *
		******************/

		Object2D* LogsFrame = Object2D::New(debugMenu);
		LogsFrame->Size = SpecialVector2{ 0.4, 0.6 };
		LogsFrame->Position = SpecialVector2{ 0.04, 0.3 };
		LogsFrame->BackgroundTransparency = 0.2;
		LogsFrame->BackgroundColor = { 0,0,0,255 };
		LogsFrame->BorderColor = DefaultDebugColor;
		LogsFrame->BorderThickness = 3;
		LogsFrame->Name = "LogsFrame";

		TextLabel* LogsName = TextLabel::New(LogsFrame);
		LogsName->Name = "LogsName";
		LogsName->SetText("Logs");
		LogsName->TextSize = -1;
		LogsName->TextColor = DefaultDebugColor;
		LogsName->Position = SpecialVector2{ 0.5, 0 };
		LogsName->AnchorPosition = SpecialVector2{ 0.5, 0 };
		LogsName->Size = SpecialVector2{ 0.8, 0.055 };
		LogsName->TextAnchor = TextAnchorEnum::CENTER;
		LogsName->BackgroundTransparency = 1;
		LogsName->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);

		console = ScrollFrame::New(LogsFrame);
		console->BackgroundColor = { 0,0,0,255 };
		console->BackgroundTransparency = 0.1;
		console->BorderThickness = 3;
		console->BorderColor = DefaultDebugColor;
		console->Size = SpecialVector2{ 1, 0.93 };
		console->Position = SpecialVector2{ 0, 0.07 };
		console->SliderColor = { 255,255,255,255 };
		console->Name = "consoleLogs";
		console->Active = true;
		print("Debug inited");
		for (int i = 0; i < textQueue.size(); i++) {
			print(textQueue[i]);
		}
		textQueue.clear();

		/********************
		* Objects hierarchy *
		********************/

		treeFrame = Object2D::New(debugMenu);
		treeFrame->Size = SpecialVector2{ 0.49, 0.87 };
		treeFrame->Position = SpecialVector2{ 0.47, 0.03 };
		treeFrame->BackgroundTransparency = 0.2;
		treeFrame->BackgroundColor = { 0,0,0,255 };
		treeFrame->BorderColor = DefaultDebugColor;
		treeFrame->BorderThickness = 3;
		treeFrame->Name = "treeFrame";
		treeFrame->Active = true;

		TextLabel* treeName = TextLabel::New(treeFrame);
		treeName->Name = "treeName";
		treeName->SetText("Objects hierarchy");
		treeName->TextSize = -1;
		treeName->TextColor = DefaultDebugColor;
		treeName->Position = SpecialVector2{ 0.5, 0 };
		treeName->AnchorPosition = SpecialVector2{ 0.5, 0 };
		treeName->Size = SpecialVector2{ 0.8, 0.055 };
		treeName->TextAnchor = TextAnchorEnum::CENTER;
		treeName->BackgroundTransparency = 1;
		treeName->SetFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME);

		Object2D* manageMenu = Object2D::New(treeFrame);
		manageMenu->Name = "manageMenu";
		manageMenu->Position = SpecialVector2{ 0, 0.06 };
		manageMenu->Size = SpecialVector2{ 1, 0.05 };
		manageMenu->BorderThickness = 3;
		manageMenu->BackgroundTransparency = 1;
		manageMenu->BorderColor = DefaultDebugColor;

		ScrollFrame* way = ScrollFrame::New(manageMenu);
		way->Name = "directory";
		way->BackgroundTransparency = 1;
		way->Position = SpecialVector2{ 0, 0 };
		way->Size = SpecialVector2{ 1, 1 };
		way->Direction = 'X';
		way->SliderColor = { 255,255,255,255 };

		ScrollFrame* treeScroll = ScrollFrame::New(treeFrame);
		treeScroll->Name = "treeScroll";
		treeScroll->Position = SpecialVector2{ 0, 0.12 };
		treeScroll->Size = SpecialVector2{ 0.5, 0.88 };
		treeScroll->BackgroundTransparency = 1;
		treeScroll->SliderColor = { 255,255,255,255 };
		treeScroll->ScrollSpeed = 0.2;

		/********************
		*  Events Handler   *
		********************/

		new ChangedSignal<int>(currentColor, [treeScroll, way, manageMenu, treeName, LogsName, LogsFrame, lowerName, Colorright, ColorBlock, Colorleft, Colorlabel, FPSright, FPSquantity, FPSleft, FPSlabel, LGMlabel, AnimLabel, SettingsName, SettingsFrame]() {
			Colorright->TextColor = typeColor[currentColor];
			ColorBlock->BackgroundColor = typeColor[currentColor];
			Colorleft->TextColor = typeColor[currentColor];
			Colorlabel->TextColor = typeColor[currentColor];
			FPSright->TextColor = typeColor[currentColor];
			FPSquantity->TextColor = typeColor[currentColor];
			FPSleft->TextColor = typeColor[currentColor];
			FPSlabel->TextColor = typeColor[currentColor];
			LGMlabel->TextColor = typeColor[currentColor];
			AnimLabel->TextColor = typeColor[currentColor];
			SettingsName->TextColor = typeColor[currentColor];
			SettingsFrame->BorderColor = typeColor[currentColor];
			lowerName->TextColor = typeColor[currentColor];
			debugMenu->BackgroundColor = typeColor[currentColor];
			console->BorderColor = typeColor[currentColor];
			LogsFrame->BorderColor = typeColor[currentColor];
			LogsName->TextColor = typeColor[currentColor];
			treeFrame->BorderColor = typeColor[currentColor];
			treeName->TextColor = typeColor[currentColor];
			manageMenu->BorderColor = typeColor[currentColor];
			for (Instance* obj : console->Children) {
				if (obj->Class == TEXTLABEL) {
					TextLabel* t = static_cast<TextLabel*>(obj);
					if (t) {
						t->TextColor = typeColor[currentColor];
					}
				}
			}
			for (Instance* obj : way->Children) {
				if (obj->Class == TEXTLABEL) {
					TextLabel* t = static_cast<TextLabel*>(obj);
					if (t) {
						t->TextColor = typeColor[currentColor];
					}
				}
			}
			for (Instance* obj : treeScroll->Children) {
				if (obj->Class == TEXTLABEL) {
					TextLabel* t = static_cast<TextLabel*>(obj);
					if (t) {
						t->TextColor = typeColor[currentColor];
					}
				}
			}
		});

		new ChangedSignal<int>(currentFPSindex, [FPSquantity]() { SetTargetFPS(getCurrentMaxFPS()); std::ostringstream s; s << " " << typeFPS[currentFPSindex] << " "; FPSquantity->SetText(currentFPSindex == 2 ? "FULL" : ((currentFPSindex == 3) ? "V-SYNC" : s.str())); });
		new ChangedSignal<bool>(Animations, [AnimButton]() { AnimButton->BackgroundColor = Animations ? Color{ 204, 255, 204, 255 } : Color{ 255, 204, 204, 255 }; AnimButton->SetText(Animations ? " On " : " Off ");});
		new ChangedSignal<bool>(lowGraphicsMode, [LGMbutton]() { LGMbutton->BackgroundColor = lowGraphicsMode ? Color{ 204, 255, 204, 255 } : Color{ 255, 204, 204, 255 }; LGMbutton->SetText(lowGraphicsMode ? " On " : " Off "); });

		new ChangedSignal<Instance*>(currentInstance, [way, treeScroll]() {
			way->deleteAllChildren();
			treeScroll->deleteAllChildren();

			if (currentInstance) {
				Instance* obj = currentInstance;
				static std::vector<Instance*> objects;
				objects.clear();
				while (obj != nullptr) {
					objects.push_back(obj);

					obj = obj->Parent;
				}

				for (int i = objects.size() - 1; i >= 0; i--) {
					TextLabel* element = TextLabel::New(way);
					element->Name = objects[i]->Name;
					element->BackgroundTransparency = 1;
					element->TextColor = typeColor[currentColor];
					element->Position = SpecialVector2{ (objects.size() - i - 1) * 0.25f, 0 };
					element->Size = SpecialVector2{ 0.2, 0.9 };
					element->SetText(objects[i]->Name);
					element->Active = true;

					if (i != 0) {
						TextLabel* element2 = TextLabel::New(way);
						element2->Name = ">";
						element2->BackgroundTransparency = 1;
						element2->TextColor = typeColor[currentColor];
						element2->Position = SpecialVector2{ (objects.size() - i - 1) * 0.25f + 0.2f , 0 };
						element2->Size = SpecialVector2{ 0.05, 0.9 };
						element2->SetText(">");
					}

					element->AddEvent(MOUSE_CLICK, [i](Instance* t) { currentInstance = objects[i]; }, MOUSE_LEFT);
				}

				way->CanvasSize.x = objects.size() * 0.25 - 0.05;
				way->CanvasPosition.x = way->CanvasSize.x;

				static std::vector<Instance*> objects2;
				objects2.clear();

				bool dec = false;

				for (int i = 0; i < currentInstance->Children.size(); i++) {
					if (currentInstance->Children[i]->Name == "debugMenu") { dec = true; continue; }
					objects2.push_back(currentInstance->Children[i]);
					TextLabel* element = TextLabel::New(treeScroll);
					element->Name = currentInstance->Children[i]->Name;
					element->BackgroundTransparency = 1;
					element->TextColor = typeColor[currentColor];
					element->Position = { 0, (i - dec) * 0.05f };
					element->Size = { 1, 0.05 };
					std::ostringstream pupupupu; pupupupu << " > " << currentInstance->Children[i]->Name;
					element->SetText(pupupupu.str());
					element->Active = true;
					element->TextAnchor = TextAnchorEnum::W;
					element->AddEvent(MOUSE_CLICK, [i, dec](Instance* t) { currentInstance = objects2[i - dec]; }, MOUSE_LEFT);
				}

				treeScroll->CanvasSize.y = (currentInstance->Children.size() - dec) * 0.05;
				treeScroll->CanvasPosition.y = 0;
			}
		});
		currentInstance = s;
	}

	inline void toggleDebug(Instance* s) {
		if (!debugMenu) {
			initDebug(s);
		}

		debugMenu->Visible = !debugMenu->Visible;
	}
};

inline void updateSignals() {
	for (auto obj : ActiveSignals) {
		if (!obj) continue;
		obj->Update();
	}
}

inline void SUI_SetWindowSize(int newW, int newH) {
	SIMPLEUI_GLOBAL::changeWindowSize = SpecialVector2{ (float)newW, (float)newH };
	SIMPLEUI_GLOBAL::changeWindowSizeB = true;
}

inline void SUI_SetWindowPosition(int newX, int newY) {
	SetWindowPosition(newX, newY);
}

inline SpecialVector2 windowMinimalSize = { 0,0 };

inline void SUI_SetMinimalWindowSize(int newX, int newY) {
	windowMinimalSize = SpecialVector2{ (float)newX, (float)newY };
}

inline bool ALLOW_DEBUG = false;
inline bool ALLOW_FPS = false;

inline void UpdateHigher(Instance* StartInstance) {
	Object2D* best = nullptr;
	int maxDepth = -1;

	std::function<bool(Instance*, int)> getTop = [&getTop, &best, &maxDepth](Instance* parent, int localDepth) -> bool {
		bool foundInThisBranch = false;

		if (parent->Class == SCROLLFRAME) {
			ScrollFrame* scroll = static_cast<ScrollFrame*>(parent);

			for (auto sector : scroll->sectorsOnView) {
				for (auto& [id, child] : sector->Objects) {
					if (child == parent) continue;
					int nextDepth = localDepth;
					bool isTarget = false;

					if (scroll->childsRemovedInFrame.contains(id)) continue;

					if (!Is2DInheritor(child)) {
						if (getTop(child, nextDepth)) {
							foundInThisBranch = true;
						}

						if (foundInThisBranch) {
							return true;
						}
					} else {
						auto obj = static_cast<Object2D*>(child);

						if (!obj->Visible) continue;
						nextDepth = localDepth + 1;
						if (obj->Active and obj->pointInObject(SIMPLEUI_GLOBAL::mousePosition)) {
							isTarget = true;
						}

						if (getTop(child, nextDepth)) {
							foundInThisBranch = true;
						}

						if (isTarget) {
							if (nextDepth > maxDepth or (nextDepth == maxDepth and (!best or obj->ZIndex > best->ZIndex))) {
								best = obj;
								maxDepth = nextDepth;
								foundInThisBranch = true;
							}
						}

						if (foundInThisBranch) {
							return true;
						}
					}
				}
			}
		} else {
			for (auto it = parent->Children.rbegin(); it != parent->Children.rend(); it++) {
				Instance* child = *it;

				int nextDepth = localDepth;
				bool isTarget = false;

				if (!Is2DInheritor(child)) {
					if (getTop(child, nextDepth)) {
						foundInThisBranch = true;
					}

					if (foundInThisBranch) {
						return true;
					}
				} else {
					auto obj = static_cast<Object2D*>(child);

					if (!obj->Visible) continue;
					nextDepth = localDepth + 1;
					if (obj->Active and obj->pointInObject(SIMPLEUI_GLOBAL::mousePosition)) {
						isTarget = true;
					}

					if (getTop(child, nextDepth)) {
						foundInThisBranch = true;
					}

					if (isTarget) {
						if (nextDepth > maxDepth or (nextDepth == maxDepth and (!best or obj->ZIndex > best->ZIndex))) {
							best = obj;
							maxDepth = nextDepth;
							foundInThisBranch = true;
						}
					}

					if (foundInThisBranch) {
						return true;
					}
				}
			}
		}

		return foundInThisBranch;
	};

	getTop(StartInstance, 0);
	SIMPLEUI_GLOBAL::PreviousHigherObject = SIMPLEUI_GLOBAL::higherObject;
	SIMPLEUI_GLOBAL::higherObject = best;
}

inline void start(Instance* StartInstance=nullptr, Vector3 inf={1280, 720, 0}, const char* name = "simpleUI", const char* iconName = "", unsigned int flags = FLAG_WINDOW_RESIZABLE + FLAG_MSAA_4X_HINT) {
	if (!StartInstance) {
		std::cout << RED_ANSI << "start() requires root object. GetRoot() to get root object" << DEFAULT_ANSI << std::endl;
		return;
	}
	SetConsoleUTF8();
	SetConfigFlags(flags);

	SIMPLEUI_GLOBAL::winWidth = inf.x;
	SIMPLEUI_GLOBAL::winHeight = inf.y;

	InitWindow(inf.x, inf.y, name);

	if (windowMinimalSize.x != 0 and windowMinimalSize.y != 0) {
		SetWindowMinSize(windowMinimalSize.x, windowMinimalSize.y);
	}

	int targetFPS = (inf.z <= 0) ? GetMonitorRefreshRate(GetCurrentMonitor()) : inf.z;
	SetTargetFPS(targetFPS);

	Image ic = RAYLIB_FUNCTIONAL::LoadImage(iconName);
	if (!std::string(iconName).empty()) RAYLIB_FUNCTIONAL::SetWindowIcon(ic);

	SetExitKey(KEY_NULL);

	createFont(SIMPLEUI_GLOBAL::BASIC_FONT_NAME, "Fonts/arial.ttf", 60); // Basic font 1
	createFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME, "Fonts/rogFont.otf", 35); // Basic font 2
	SIMPLEUI_GLOBAL::RectangleRoundnessShader = loadNewShader("simpleUI Shaders/rectangle_roundness.vert", "simpleUI Shaders/rectangle_roundness.frag"); // Basic shader 2

	for (auto& tup : queuedFonts) {
		createFont(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup));
	}
	queuedFonts.clear();

	for (auto& pair : SIMPLEUI_GLOBAL::pendingImages) {
		AtlasTexture tex = LoadTextureOnAtlas(pair.second);
		SIMPLEUI_GLOBAL::loadedImages.insert({ pair.first, {pair.second, tex} });
	}

	SIMPLEUI_GLOBAL::pendingImages.clear();

	debug::print("Hello from Ishakao!");

	while (SIMPLEUI_GLOBAL::programRunning and !WindowShouldClose()) {
		if (IsWindowFullscreen()) ToggleFullscreen();
		if (SIMPLEUI_GLOBAL::changeWindowSizeB) {
			SetWindowSize(SIMPLEUI_GLOBAL::changeWindowSize.x, SIMPLEUI_GLOBAL::changeWindowSize.y);
			SIMPLEUI_GLOBAL::changeWindowSizeB = false;
		}

		static Vector2 previousMousePosition = {};
		SIMPLEUI_GLOBAL::mousePosition = GetMousePosition();
		SIMPLEUI_GLOBAL::mouseScreenPosition = GetMouseScreenPosition();
		SIMPLEUI_GLOBAL::windowPosition = GetWindowPosition();

		static Vector2 previousWinSize = { -10, -10 };
		SIMPLEUI_GLOBAL::winWidth = GetScreenWidth(); SIMPLEUI_GLOBAL::winHeight = GetScreenHeight();

		if (previousWinSize.x != SIMPLEUI_GLOBAL::winWidth or previousWinSize.y != SIMPLEUI_GLOBAL::winHeight) {
			SIMPLEUI_GLOBAL::windowSizeChanged = true;
			previousWinSize = { (float)SIMPLEUI_GLOBAL::winWidth, (float)SIMPLEUI_GLOBAL::winHeight };
		}

		static long middleFPS = 0;
		middleFPS += 1 / SIMPLEUI_GLOBAL::dt;
		static double cd = 0;
		cd += SIMPLEUI_GLOBAL::dt;
		static int frames = 0;
		frames++;

		if (cd >= 0.1) {
			cd = 0;
			SIMPLEUI_GLOBAL::accurateFPS = middleFPS / frames;
			middleFPS = 0;
			frames = 0;
		}

		updateSignals();
		SIMPLEUI_GLOBAL::dt = GetFrameTime();
		Animate::UpdateAnimations(SIMPLEUI_GLOBAL::dt);
		Tasks::UpdateTasks(SIMPLEUI_GLOBAL::dt);

		if ((previousMousePosition.x != SIMPLEUI_GLOBAL::mousePosition.x or previousMousePosition.y != SIMPLEUI_GLOBAL::mousePosition.y or SIMPLEUI_GLOBAL::sceneDirty)) {
			previousMousePosition = SIMPLEUI_GLOBAL::mousePosition;
			UpdateHigher(StartInstance);
		}

		if (IsKeyPressed(KEY_F1) and ALLOW_FPS) { toggleFPS(StartInstance); }
		if (IsKeyPressed(KEY_F2) and ALLOW_DEBUG) { debug::toggleDebug(StartInstance); }
		if (IsKeyPressed(KEY_F3)) { std::cout << BLUE_ANSI << SIMPLEUI_GLOBAL::accurateFPS << DEFAULT_ANSI << std::endl; }

		SIMPLEUI_GLOBAL::framesSinceStart += 1;

		DrawFrame(StartInstance);

		SIMPLEUI_GLOBAL::sceneDirty = false;
		SIMPLEUI_GLOBAL::windowSizeChanged = false;
	}

	if (GetRoot()) {
		GetRoot()->deleteAllChildren();
	}

	UnloadImage(ic);

	for (auto pair : SIMPLEUI_GLOBAL::loadedImages) {
		RAYLIB_FUNCTIONAL::UnloadImage(pair.second.first);
		UnloadTextureFromAtlas(pair.second.second);
	}

	for (auto it : Fonts) {
		UnloadFont(it.second);
	}

	for (auto atlas : SIMPLEUI_GLOBAL::AtlasArray) {
		delete atlas;
	}

	Fonts.clear();

	SIMPLEUI_GLOBAL::deletedObjectsByID.clear();
	SIMPLEUI_GLOBAL::AtlasTextureId = 1;
	SIMPLEUI_GLOBAL::currentUniqueObjectID = 1;
	SIMPLEUI_GLOBAL::framesSinceStart = 0;

	CloseWindow();
}

#ifndef EXCLUDE_SIMPLEUI_EXTENSION
#include "../include/SUIextension.h"
#endif
