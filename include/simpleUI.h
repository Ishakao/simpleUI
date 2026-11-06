//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																												//
// simpleUI by Ishakao | https://github.com/Ishakao/simpleUI													//
// Current Version 1.0.1																						//
//																												//
// Description:																									//
// simpleUI is a library for simple creating a beautiful and fast retained user interfaces.						//
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
// A lot of CPU performance improvement																			//
// Spacial Grid optimization for ScrollFrame (millions of objects with thousands of FPS)					    //
// TextBox input can be on any language (any UTF-8 character)													//
// FreeType support (CJK, emoji, UTF-8)																			//
// TextBox now supports clipboard and Y viewport																//
// Optimizated position and size calculate functions															//
// Self rectangles batcher and shaders. Now rounded rectangles are so optimized (minimal CPU overload)			//
// Textures atlassing (excluding TextureLabel)																	//
// Improved performance on big quantity of rectangles															//
// Several architecture changes. ODR fix, ::New(), ::Destroy(), GetRoot() to get singleton root Instance		//
// Textures draw optimization. Batching for textures and rectangles												//
// Local Rotation and Origin support																			//
// Added SafeChangedSignal which works like SafeAnimation (destroys when linked object deletes)					//
// Added roundness clipping and ClipDescendants for every 2D object												//
// Added user-made shapes for 2D objects background																//
// Per-Symbol coloring (UsePerSymbolColor, SetPerSymbolColor, ClearPerSymbolColor) for TextLabel and TextBox	//
//																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <cstdarg>
#include <cstring>


#define INCLUDE_SIMPLEUI_EXTENSION // Extension for simpleUI. Contains additional unnecesary 2D objects (GraphBuilder, ToggleSwitcher, CheckBox, !ProgressBar, !DropdownBox)
// IF YOU DON'T NEED SIMPLEUI EXTENSION THEN USE "#define EXCLUDE_SIMPLEUI_EXTENSION" BEFORE INCLUDING simpleUI.h


#define INCLUDE_SIMPLEUI_FREETYPE // Flag to use FreeType in text drawing. UTF-8 and emoji support.
// IF YOU DON'T NEED FREETYPE IN YOUR UI THEN USE "#define EXCLUDE_SIMPLEUI_FREETYPE" BEFORE INCLUDING simpleUI.h

#ifndef EXCLUDE_SIMPLEUI_FREETYPE
	#include <freetype2/ft2build.h>
	#include FT_FREETYPE_H
	#define BASIC_FREETYPE_FONT_SIZE 512
	#include <harfbuzz/hb.h>
	#include <harfbuzz/hb-ft.h>
#endif

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
using RAYLIB_FUNCTIONAL::IsCursorOnScreen;
using RAYLIB_FUNCTIONAL::WindowShouldClose;
using RAYLIB_FUNCTIONAL::ToggleFullscreen;
using RAYLIB_FUNCTIONAL::MaximizeWindow;
using RAYLIB_FUNCTIONAL::MinimizeWindow;
using RAYLIB_FUNCTIONAL::RestoreWindow;

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
#define SCROLLFRAME_GRID_SIZE 512
#define MAX_TEXTURE_LIMIT 16384
#define DEFAULT_ATLAS_SIZE 2048
#define FLT_MAX          3.402823466e+38F        // max value  (from float.h)

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
	throw;
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

enum SUI_EEC {
	EEC_DEFAULT = 0,			 // Entered if current object is highest by ZIndex on mouse
	EEC_EVERY_ENTER,			 // Entered if current object on mouse
	EEC_IF_DESCENDANT_HIGHER	 // Entered if current object is ancestor of highest ZIndex object on mouse
};

enum BorderPlacement {
	BORDER_INNER = 0,		// Border will be in rectangle area
	BORDER_MIDDLE,			// Half of border will be on area and other half will be out of area
	BORDER_OUTER			// Border will be out of area
};

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

	BorderPlacement borderType;
	int BackgroundShape{};
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

struct IChangedSignal {
	friend inline void Delete(Instance*);
	virtual ~IChangedSignal() = default;
	virtual void Update() = 0;
};

namespace SIMPLEUI_GLOBAL {
	inline int winWidth = 0;
	inline int winHeight = 0;
	inline int defaultSpacing = 0;
	inline float dt = 0;
	inline Vector2 changeWindowSize = { 0,0 };
	inline bool changeWindowSizeB = false;
	inline bool windowSizeChanged = false;
	inline long accurateFPS = 0;
	inline bool programRunning = true;
	inline Vector2 mousePosition;
	inline bool mouseOnWindow;
	inline constexpr const char* BASIC_FONT_NAME = "Arial";
	inline constexpr const char* DEBUG_MENU_FONT_NAME = "rog";
	inline std::unordered_map<int, Shader> Shaders;
	inline long currentUniqueObjectID = 0;
	inline bool sceneDirty = false; // true in frame where any object hierarchy, size or position changed

	inline Vector2 windowMinimalSize = { 0,0 };
	inline bool ALLOW_DEBUG = false;
	inline bool ALLOW_FPS = false;

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

	inline std::vector<TextBox*> TextBoxesToUpdateTexture;
	inline std::vector<TextLabel*> TextLabelsToUpdateTexture;

	inline Color WindowColor = { 255,255,255,255 };

	inline std::vector<Font> Fonts;
	inline std::unordered_map<std::string, int> FontsIndexes;
	inline std::vector<std::tuple<std::string, std::string, int>> queuedFonts;
	inline std::vector<std::tuple<std::string, std::vector<std::string>, int>> queuedFontsV;

	inline std::vector<IChangedSignal*> ActiveSignals;
	inline std::unordered_map<Instance*, std::vector<IChangedSignal*>> SafeActiveSignals;

	inline std::vector<Instance*> WillDelete;
	inline void CollectDeadObjects() {
		for (int i = 0; i < WillDelete.size(); i++) {
			delete WillDelete[i];
		}

		WillDelete.clear();
	}

	struct ClipData {
		float x, y, w, h;
		float roundness, rotation;
		Vector2 origin;
	};

	struct ClipDesc {
		float cx, cy, hw, hh;
		float cosA, sinA, radius, parent;
	};

	inline constexpr int MAX_CLIP_STACK_SIZE = 128; // DEFAULT MAXIMUM OF CLIPS - 128. IF YOU NEED MORE THAN SET BIGGER VALUE HERE AND IN rectangle_roundness.frag (uniform vec4 clips[256]) SIZE OF ARRAY MUST BE x2 FROM MAX_CLIP_STACK_SIZE
	inline bool clipping = true;
	inline std::vector<int> clipStack;
	inline std::vector<ClipDesc> clips;

	inline void PushClip(const ClipData& c) {
		if (clips.size() >= MAX_CLIP_STACK_SIZE) {
			clipStack.push_back(clipStack.empty() ? -1 : clipStack.back());
			return;
		}

		float a = c.rotation * DEG2RAD;
		float ca = cosf(a), sa = sinf(a);

		float lx = c.w * 0.5f - c.origin.x;
		float ly = c.h * 0.5f - c.origin.y;

		ClipDesc d;
		d.cx = c.x + c.origin.x + lx * ca - ly * sa;
		d.cy = c.y + c.origin.y + lx * sa + ly * ca;
		d.hw = c.w * 0.5f;
		d.hh = c.h * 0.5f;
		d.cosA = ca;
		d.sinA = sa;
		d.radius = c.roundness * std::min(c.w, c.h) * 0.5f;
		d.parent = clipStack.empty() ? -1.0f : (float)clipStack.back();

		clips.push_back(d);
		clipStack.push_back((int)clips.size() - 1);
	}

	inline void PopClip() { clipStack.pop_back(); }
}

inline void ChangeWindowColor(Color c) {
	SIMPLEUI_GLOBAL::WindowColor = c;
}

inline void DrawRoundRectBatch(const RoundRectData&);

namespace SIMPLEUI_GRAPHICS_WRAPS {
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

	inline void StopClipping() {
		SIMPLEUI_GLOBAL::clipping = false;
	}

	inline void ResumeClipping() {
		SIMPLEUI_GLOBAL::clipping = true;
	}

	inline void DrawLineEx(Vector2 s, Vector2 e, float t, Color c, Vector2 Pos, Vector2 Origin, float Rotation, float Roundness) {
		float rad = Rotation * DEG2RAD;
		float cs = cosf(rad);
		float sn = sinf(rad);
		float ox = Pos.x + Origin.x;
		float oy = Pos.y + Origin.y;

		auto rot = [&](Vector2 p) {
			float dx = p.x - ox;
			float dy = p.y - oy;
			return Vector2{ ox + dx * cs - dy * sn, oy + dx * sn + dy * cs };
		};

		Vector2 a = rot(s);
		Vector2 b = rot(e);

		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float len = sqrtf(dx * dx + dy * dy);
		if (len <= 0.0f or t <= 0.0f or !c.a) return;

		RoundRectData rec = {
			{ a.x, a.y - t * 0.5f }, { len, t },
			c, c,
			0.0f, Roundness, 0.0f,
			0,
			atan2f(dy, dx) * RAD2DEG,
			{ 0.0f, t * 0.5f }
		};

		DrawRoundRectBatch(rec);
	}

	inline void DrawTexturePro(Texture2D texture, Vector2 position, Vector2 size, Rectangle source, Rectangle destination, Vector2 origin, float rotation, Color color, float roundness) {
		const RoundRectData rec = {
			position,
			size,
			color, {255,255,255,255},
			0.0f, roundness, 1.0f,
			0,
			rotation,
			origin,
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

struct TexturedTextLabelData {
	Vector2 RealPos{};
	Vector2 RealSize{};
	Vector2 Origin{};
	float Rotation{};
	float Roundness{};
};

#ifndef EXCLUDE_SIMPLEUI_FREETYPE
    namespace FT_TextManagement {
        struct Glyph {
            Rectangle src{};
            float xoff = 0;
            float yoff = 0;
            float advance = 0;
            float scale = 1;
            bool color = false;
        };

        struct Shaped {
            int face;
            FT_UInt gid;
            float x, y, adv;
        };

        struct Quad {
            Rectangle src;
            float ox, oy, w, h;
            int col;
            bool color;
        };

        struct LineSpan {
            float baseW;
            int count;
        };

        struct Layout {
            std::string text;
            std::vector<Quad> quads;
            std::vector<LineSpan> lines;
            float baseLineH = 0;
        };

        class FT_Font {
            struct Atlas {
                Texture2D tex{};
                std::vector<unsigned char> pixels;
                std::unordered_map<uint64_t, Glyph> map;
                float baseline = 0;
                float lineH = 0;
                int height = 0;
                int x = 0, y = 0, rowH = 0;
            };

            FT_Library lib_ = nullptr;
            hb_buffer_t* buf_ = nullptr;
            std::vector<hb_font_t*> hb_;
            std::vector<FT_Face> faces_{};
            std::vector<int> activeSizes_{};
            std::vector<float> activeScales_{};
            Atlas atlas_{};
            std::vector<unsigned char> scratchRgba_{};
            int width_{};
            int maxSide_{};
            int baseSize_ = 64;

            float ApplySize(int faceIdx, int size) {
                if (activeSizes_[faceIdx] == size) {
                    return activeScales_[faceIdx];
                }

                FT_Face face = faces_[faceIdx];
                float scale = 1.0f;

                if (FT_IS_SCALABLE(face)) {
                    FT_Set_Pixel_Sizes(face, 0, (FT_UInt)size);
                } else if (face->num_fixed_sizes > 0) {
                    int best = 0;
                    float bestDiff = 1e9f;
                    for (int i = 0; i < face->num_fixed_sizes; i++) {
                        float d = std::fabs(face->available_sizes[i].y_ppem / 64.0f - size);
                        if (d < bestDiff) { bestDiff = d; best = i; }
                    }
                    FT_Select_Size(face, best);
                    float ppem = (float)face->size->metrics.y_ppem;
                    scale = ppem > 0 ? size / ppem : 1.0f;
                }

                hb_ft_font_changed(hb_[faceIdx]);
                activeSizes_[faceIdx] = size;
                activeScales_[faceIdx] = scale;
                return scale;
            }

            static uint64_t Key(int face, FT_UInt gid) {
                return ((uint64_t)face << 32) | gid;
            }

            static bool Joins(int cp) {
                return (cp >= 0x1F3FB and cp <= 0x1F3FF) or cp == 0x200D or cp == 0xFE0F or cp == 0xFE0E or cp == 0x20E3 or (cp >= 0xE0020 and cp <= 0xE007F);
            }

            static bool IsRI(int cp) { return cp >= 0x1F1E6 and cp <= 0x1F1FF; }

            int PickFace(int cp) {
                for (size_t i = 0; i < faces_.size(); i++)
                    if (FT_Get_Char_Index(faces_[i], (FT_ULong)cp)) return (int)i;
                return 0;
            }

            int NextCluster(const int* cps, int count, int i, int& faceOut) {
                faceOut = PickFace(cps[i]);
                int j = i + 1;
                while (j < count and (Joins(cps[j]) or cps[j - 1] == 0x200D or (IsRI(cps[i]) and j == i + 1 and IsRI(cps[j])))) j++;
                return j;
            }

            void Upload(Atlas& a) {
                Image img = { a.pixels.data(), width_, a.height, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
                Texture2D t = RAYLIB_FUNCTIONAL::LoadTextureFromImage(img);
                RAYLIB_FUNCTIONAL::SetTextureFilter(t, TEXTURE_FILTER_BILINEAR);
                if (a.tex.id) RAYLIB_FUNCTIONAL::UnloadTexture(a.tex);
                a.tex = t;
            }

            bool Grow(Atlas& a) {
                if (a.height >= maxSide_) return false;
                int nh = std::min(a.height * 2, maxSide_);
                FlushRectanglesBatch();
                a.pixels.resize((size_t)width_ * nh * 4, 0);
                a.height = nh;
                Upload(a);
                return true;
            }

            void InitAtlas() {
                if (atlas_.tex.id != 0 or faces_.empty()) return;
                atlas_.height = width_;
                atlas_.pixels.assign((size_t)width_ * atlas_.height * 4, 0);
                Upload(atlas_);
                float s = ApplySize(0, baseSize_);
                atlas_.baseline = (faces_[0]->size->metrics.ascender / 64.0f) * s;
                atlas_.lineH = (faces_[0]->size->metrics.height / 64.0f) * s;
            }

            Glyph Rasterize(Atlas& a, int f, FT_UInt gid) {
                FT_Face face = faces_[f];
                float scale = ApplySize(f, baseSize_);
                int flags = FT_LOAD_RENDER;
                if (FT_HAS_COLOR(face)) flags |= FT_LOAD_COLOR;
                if (FT_Load_Glyph(face, gid, flags)) return {};

                FT_GlyphSlot slot = face->glyph;
                FT_Bitmap& bm = slot->bitmap;

                Glyph g;
                g.scale = scale;
                g.advance = (slot->advance.x / 64.0f) * scale;
                g.xoff = slot->bitmap_left * scale;
                g.yoff = -slot->bitmap_top * scale;

                int w = (int)bm.width;
                int h = (int)bm.rows;
                if (w == 0 or h == 0) return g;

                bool bgra = bm.pixel_mode == FT_PIXEL_MODE_BGRA;
                if (!bgra and bm.pixel_mode != FT_PIXEL_MODE_GRAY) return g;
                g.color = bgra;

                if (w + 2 > width_) return g;

                if (a.x + w + 2 > width_) { a.x = 0; a.y += a.rowH + 2; a.rowH = 0; }
                while (a.y + h + 2 > a.height) {
                    if (!Grow(a)) return g;
                }

                size_t needed = (size_t)w * h * 4;
                if (scratchRgba_.size() < needed) scratchRgba_.resize(needed);

                int pitch = std::abs(bm.pitch);
                for (int y = 0; y < h; y++) {
                    const unsigned char* row = bm.buffer + (size_t)y * pitch;
                    unsigned char* out = scratchRgba_.data() + (size_t)y * w * 4;
                    for (int x = 0; x < w; x++) {
                        if (bgra) {
                            unsigned char alpha = row[x * 4 + 3];
                            out[x * 4 + 0] = alpha ? (unsigned char)std::min(255, row[x * 4 + 2] * 255 / alpha) : 0;
                            out[x * 4 + 1] = alpha ? (unsigned char)std::min(255, row[x * 4 + 1] * 255 / alpha) : 0;
                            out[x * 4 + 2] = alpha ? (unsigned char)std::min(255, row[x * 4 + 0] * 255 / alpha) : 0;
                            out[x * 4 + 3] = alpha;
                        } else {
                            out[x * 4 + 0] = 255;
                            out[x * 4 + 1] = 255;
                            out[x * 4 + 2] = 255;
                            out[x * 4 + 3] = row[x];
                        }
                    }
                    std::memcpy(&a.pixels[((size_t)(a.y + y) * width_ + a.x) * 4], out, (size_t)w * 4);
                }

                UpdateTextureRec(a.tex, { (float)a.x, (float)a.y, (float)w, (float)h }, scratchRgba_.data());
                g.src = { (float)a.x, (float)a.y, (float)w, (float)h };
                a.x += w + 2;
                if (h > a.rowH) a.rowH = h;
                return g;
            }

        public:
            std::unordered_map<uint64_t, Layout> layouts;
            std::vector<Shaped> shScratch;

            FT_Font(const std::vector<std::string>& paths, int size = 64, int startSide = 1024, int maxSide = 16384) : baseSize_(size), width_(startSide < 512 ? 512 : startSide), maxSide_(maxSide) {
                FT_Init_FreeType(&lib_);
                buf_ = hb_buffer_create();
                layouts.reserve(4096);
                for (const std::string& p : paths) AddFace(p.c_str());
                InitAtlas();
            }

            FT_Font(FT_Font&& o) noexcept : lib_(o.lib_), buf_(o.buf_), hb_(std::move(o.hb_)), faces_(std::move(o.faces_)),
                  activeSizes_(std::move(o.activeSizes_)), activeScales_(std::move(o.activeScales_)),
                  atlas_(std::move(o.atlas_)), scratchRgba_(std::move(o.scratchRgba_)),
                  width_(o.width_), maxSide_(o.maxSide_), baseSize_(o.baseSize_),
                  layouts(std::move(o.layouts)), shScratch(std::move(o.shScratch)) {
                o.lib_ = nullptr;
                o.buf_ = nullptr;
                o.atlas_.tex.id = 0;
                o.faces_.clear();
                o.hb_.clear();
            }

            ~FT_Font() {
                if (atlas_.tex.id) RAYLIB_FUNCTIONAL::UnloadTexture(atlas_.tex);
                for (auto f : hb_) hb_font_destroy(f);
                if (buf_) hb_buffer_destroy(buf_);
                for (FT_Face f : faces_) FT_Done_Face(f);
                if (lib_) FT_Done_FreeType(lib_);
            }

            FT_Font(const FT_Font&) = delete;
            FT_Font& operator=(const FT_Font&) = delete;

            bool AddFace(const char* path) {
                FT_Face face;
                if (FT_New_Face(lib_, path, 0, &face)) return false;
                faces_.push_back(face);
                activeSizes_.push_back(-1);
                activeScales_.push_back(1.0f);
                hb_font_t* h = hb_ft_font_create_referenced(face);
                hb_ft_font_set_load_flags(h, FT_LOAD_DEFAULT | FT_LOAD_COLOR);
                hb_.push_back(h);
                return true;
            }

            void ShapeBase(const int* cps, int count, std::vector<Shaped>& out) {
                if (count <= 0) return;
                int i = 0;
                while (i < count) {
                    int face = 0;
                    int j = NextCluster(cps, count, i, face);
                    while (j < count) {
                        int nextFace = 0;
                        int nextJ = NextCluster(cps, count, j, nextFace);
                        if (nextFace != face) break;
                        j = nextJ;
                    }

                    float scale = ApplySize(face, baseSize_);

                    hb_buffer_clear_contents(buf_);
                    hb_buffer_add_codepoints(buf_, (const uint32_t*)cps, count, i, j - i);
                    hb_buffer_guess_segment_properties(buf_);
                    hb_shape(hb_[face], buf_, nullptr, 0);

                    unsigned n;
                    hb_glyph_info_t* inf = hb_buffer_get_glyph_infos(buf_, &n);
                    hb_glyph_position_t* ps = hb_buffer_get_glyph_positions(buf_, &n);
                    for (unsigned k = 0; k < n; k++) {
                        out.push_back({
                            face,
                            inf[k].codepoint,
                            (ps[k].x_offset / 64.0f) * scale,
                            -(ps[k].y_offset / 64.0f) * scale,
                            (ps[k].x_advance / 64.0f) * scale
                        });
                    }
                    i = j;
                }
            }

            bool Valid() const { return !faces_.empty(); }

            const Glyph& GetBase(int face, FT_UInt gid) {
                InitAtlas();
                uint64_t k = Key(face, gid);
                auto it = atlas_.map.find(k);
                if (it != atlas_.map.end()) return it->second;
                return atlas_.map.emplace(k, Rasterize(atlas_, face, gid)).first->second;
            }

            Texture2D BaseTexture() { InitAtlas(); return atlas_.tex; }
            float BaseBaseline() { InitAtlas(); return atlas_.baseline; }
            float BaseLineHeight() { InitAtlas(); return atlas_.lineH; }
            int BaseSize() const { return baseSize_; }
        };

        inline std::vector<FT_Font> Fonts;
        inline std::unordered_map<std::string, int> FontsIndexes;

        inline bool CreateFont(const std::string& name, const std::vector<std::string>& paths, int size = 64, int startSide = 1024, int maxSide = 16384) {
            auto it = FontsIndexes.find(name);
			if (it == FontsIndexes.end()) {
            	Fonts.emplace_back(paths, size, startSide, maxSide);
				FontsIndexes.insert({name, Fonts.size()-1});
				return true;
			}

			return false;
        }

        inline void UnloadFonts() { Fonts.clear(); }

        inline const Layout& GetLayout(FT_Font& font, const char* text) {
            std::string_view sv(text ? text : "");
            uint64_t h = std::hash<std::string_view>{}(sv);

            auto& m = font.layouts;
            auto it = m.find(h);
            if (it != m.end() and it->second.text == sv)
                return it->second;

            if (m.size() > 32768) m.clear();

            Layout& L = m[h];
            L.text.assign(sv.data(), sv.size());
            L.quads.clear();
            L.lines.clear();
            L.baseLineH = font.BaseLineHeight();

            int count = 0;
            int* cps = RAYLIB_FUNCTIONAL::LoadCodepoints(text ? text : "", &count);
            float base = font.BaseBaseline();
            std::vector<Shaped>& sh = font.shScratch;

            L.quads.reserve(count);

            float y = 0;
            int start = 0;
            while (start <= count) {
                int end = start;
                while (end < count and cps[end] != '\n') end++;

                sh.clear();
                if (end > start) {
                    font.ShapeBase(cps + start, end - start, sh);
                }

                float x = 0;
                int col = 0;
                for (const Shaped& s : sh) {
                    const Glyph& g = font.GetBase(s.face, s.gid);
                    if (g.src.width > 0) {
                        L.quads.push_back({
                            g.src,
                            x + s.x + g.xoff,
                            y + base + s.y + g.yoff,
                            g.src.width * g.scale,
                            g.src.height * g.scale,
                            col,
                            g.color
                        });
                    }
                    x += s.adv;
                    col++;
                }

                L.lines.push_back({ x, (int)sh.size() });
                y += L.baseLineH;
                start = end + 1;
            }

            RAYLIB_FUNCTIONAL::UnloadCodepoints(cps);
            return L;
        }

        inline Vector2 MeasureTextEx(FT_Font& font, const char* text, int size, int spacing) {
            const Layout& L = GetLayout(font, text);
            float s = (float)size / (float)font.BaseSize();
            float maxW = 0.0f;
            for (const LineSpan& line : L.lines) {
                float w = line.count > 0 ? (line.baseW * s + (float)(line.count - 1) * spacing) : 0.0f;
                if (w > maxW) maxW = w;
            }
            return { maxW, (float)L.lines.size() * L.baseLineH * s };
        }

        inline void DrawTextEx(FT_Font& font, const char* text, Vector2 pos, int fontSize, int spacing, Color tint, std::vector<Color>* c=nullptr, TexturedTextLabelData* textlabeldata=nullptr) {
            const Layout& L = GetLayout(font, text);
            Texture2D tex = font.BaseTexture();
            Color colorTint = { 255, 255, 255, tint.a };
            float s = (float)fontSize / (float)font.BaseSize();

			int i = 0;

            for (const Quad& q : L.quads) {
                Rectangle dst = {
                    pos.x + q.ox * s + (float)q.col * spacing,
                    pos.y + q.oy * s,
                    q.w * s,
                    q.h * s
                };

				Color symbolColor = tint;

				if (c) {
					if (i < c->size()) {
						symbolColor = (*c)[i];
						i++;
					} else if (q.color) symbolColor = colorTint;
				} else if (q.color) symbolColor = colorTint;

				if (textlabeldata) {
                	SIMPLEUI_GRAPHICS_WRAPS::DrawTexturePro(tex, textlabeldata->RealPos, textlabeldata->RealSize, q.src, dst, textlabeldata->Origin, textlabeldata->Rotation, symbolColor, textlabeldata->Roundness);
				} else {
					RAYLIB_FUNCTIONAL::DrawTexturePro(tex, q.src, dst, { 0, 0 }, 0, symbolColor);
				}
            }
        }
    }
#endif

namespace SIMPLEUI_GRAPHICS_WRAPS {
	inline void DrawTextEx(
		#ifdef EXCLUDE_SIMPLEUI_FREETYPE 
			Font 
		#else
			FT_TextManagement::FT_Font&
		#endif
		font, const char* text, Vector2 pos, int fontSize, int spacing, Color tint, std::vector<Color>* c=nullptr, TexturedTextLabelData* data=nullptr) {

		#ifdef EXCLUDE_SIMPLEUI_FREETYPE
			RAYLIB_FUNCTIONAL::DrawTextEx(font, text, pos, fontSize, spacing, tint);
		#else
			FT_TextManagement::DrawTextEx(font, text, pos, fontSize, spacing, tint, c, data);
		#endif
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
	bool loaded = false;

	Texture2D texture() {
		if (pleaseGenerateMipmaps) {
			RAYLIB_FUNCTIONAL::GenTextureMipmaps(&tex.texture);
			pleaseGenerateMipmaps = false;
		}
		return tex.texture;
	}
	RenderTexture2D renderTexture() {
		if (pleaseGenerateMipmaps) {
			RAYLIB_FUNCTIONAL::GenTextureMipmaps(&tex.texture);
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

		Texture2D src = RAYLIB_FUNCTIONAL::LoadTextureFromImage(img);

		SIMPLEUI_GRAPHICS_WRAPS::BeginTextureMode(tex);
		RAYLIB_FUNCTIONAL::rlSetBlendFactorsSeparate(RL_ONE, RL_ZERO, RL_ONE, RL_ZERO, RL_FUNC_ADD, RL_FUNC_ADD);
		SIMPLEUI_GRAPHICS_WRAPS::BeginBlendMode(RAYLIB_FUNCTIONAL::BLEND_CUSTOM_SEPARATE);
		SIMPLEUI_GRAPHICS_WRAPS::DrawTexture(src, x, y, WHITE);
		SIMPLEUI_GRAPHICS_WRAPS::EndBlendMode();
		SIMPLEUI_GRAPHICS_WRAPS::EndTextureMode();

		pleaseGenerateMipmaps = true;

		RAYLIB_FUNCTIONAL::UnloadTexture(src);

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

		SIMPLEUI_GRAPHICS_WRAPS::BeginTextureMode(tex);
		RAYLIB_FUNCTIONAL::rlSetBlendFactorsSeparate(RL_ONE, RL_ZERO, RL_ONE, RL_ZERO, RL_FUNC_ADD, RL_FUNC_ADD);
		SIMPLEUI_GRAPHICS_WRAPS::BeginBlendMode(RAYLIB_FUNCTIONAL::BLEND_CUSTOM_SEPARATE);
		RAYLIB_FUNCTIONAL::DrawRectangle(x, y, width, height, BLANK);
		SIMPLEUI_GRAPHICS_WRAPS::EndBlendMode();
		SIMPLEUI_GRAPHICS_WRAPS::EndTextureMode();

		pleaseGenerateMipmaps = true;

		AtlasTexture att{ SIMPLEUI_GLOBAL::AtlasTextureId++, {(float)x, (float)y} , {(float)width, (float)height}, this };

		textures.push_back(att);

		return att;
	}

	void blankArea(AtlasTexture t) {
		if (t.currentAtlas != this) return;
		RAYLIB_FUNCTIONAL::rlSetBlendFactorsSeparate(RL_ONE, RL_ZERO, RL_ONE, RL_ZERO, RL_FUNC_ADD, RL_FUNC_ADD);
		SIMPLEUI_GRAPHICS_WRAPS::BeginBlendMode(RAYLIB_FUNCTIONAL::BLEND_CUSTOM_SEPARATE);
		RAYLIB_FUNCTIONAL::DrawRectangle(t.position.x-1, t.position.y-1, t.size.x + padding * 2, t.size.y + padding * 2, BLANK);
		SIMPLEUI_GRAPHICS_WRAPS::EndBlendMode();
	}

	Atlas(int size = DEFAULT_ATLAS_SIZE, int pad = 2) : padding(pad) {
		tex = RAYLIB_FUNCTIONAL::LoadRenderTexture(size, size);
		if (tex.id) {
			loaded = true;
			nodes.resize(size);
			RAYLIB_FUNCTIONAL::SetTextureFilter(tex.texture, TEXTURE_FILTER_BILINEAR);
			RAYLIB_FUNCTIONAL::SetTextureWrap(tex.texture, TEXTURE_WRAP_CLAMP);
			std::cout << BLUE_ANSI << "Loaded new render texture for atlas (" << size << "x" << size << ")" << DEFAULT_ANSI << std::endl;
			stbrp_init_target(&ctx, size, size, nodes.data(), (int)nodes.size());
			SIMPLEUI_GRAPHICS_WRAPS::BeginTextureMode(tex);
			ClearBackground(BLANK);
			SIMPLEUI_GRAPHICS_WRAPS::EndTextureMode();

			SIMPLEUI_GLOBAL::AtlasArray.push_back(this);
		} else {
			std::cout << RED_ANSI << "Cannot load atlas with size " << size << "x" << size << DEFAULT_ANSI << std::endl;
		}
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

namespace SIMPLEUI_GRAPHICS_WRAPS {
	inline void DrawTexturePro(AtlasTexture t, Vector2 pos, Vector2 size, Rectangle s, Rectangle d, Vector2 o, float r, Color c, float rou) {
		if (!t.currentAtlas) return;

		Texture2D tex = t.currentAtlas->texture();

		Rectangle src = { t.position.x + s.x, t.position.y + s.y, s.width, s.height };

		src.y = tex.height - src.y - src.height;
		src.height = -src.height;

		SIMPLEUI_GRAPHICS_WRAPS::DrawTexturePro(tex, pos, size, src, d, o, r, c, rou);
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
	if (sizeOfAtlas > MAX_TEXTURE_LIMIT) return {};

	for (Atlas* atlas : SIMPLEUI_GLOBAL::AtlasArray) {
		AtlasTexture t = atlas->add(width, height);
		if (t.id) return t;
	}

	for (int size = sizeOfAtlas; size <= MAX_TEXTURE_LIMIT; size *= 2) {
		Atlas* atlas = new Atlas(size);
		if (!atlas->loaded) {
			std::cout << RED_ANSI << "Atlas cannot be created with size " << sizeOfAtlas << "x" << sizeOfAtlas << "." << DEFAULT_ANSI << std::endl;
			delete atlas;
			return {};
		}

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

inline void LoadImage(const std::string& name, const std::string& path) {
	SIMPLEUI_GLOBAL::ImagesLoadingMtx.lock();

	if (IsWindowReady()) {
		Image img = RAYLIB_FUNCTIONAL::LoadImage(path.c_str());
		AtlasTexture tex = LoadTextureOnAtlas(img);
		SIMPLEUI_GLOBAL::loadedImages.insert({ name, {img, tex} });
	} else {
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
	}

	SIMPLEUI_GLOBAL::ImagesLoadingMtx.unlock();
}

inline void UnloadImage(const std::string& name) {
	SIMPLEUI_GLOBAL::ImagesLoadingMtx.lock();

	auto it = SIMPLEUI_GLOBAL::loadedImages.find(name);
	if (it != SIMPLEUI_GLOBAL::loadedImages.end()) {
		RAYLIB_FUNCTIONAL::UnloadImage(it->second.first);
		UnloadTextureFromAtlas(it->second.second);
		SIMPLEUI_GLOBAL::loadedImages.erase(it);
	}

	auto it1 = SIMPLEUI_GLOBAL::pendingImages.find(name);
	if (it1 != SIMPLEUI_GLOBAL::pendingImages.end()) {
		RAYLIB_FUNCTIONAL::UnloadImage(it1->second);
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
		abort();
	}
	return it->second;
}

inline void unloadShader(int id) {
	RAYLIB_FUNCTIONAL::UnloadShader(getShader(id));
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

inline void addFontToQueqe(const char* name, std::string path, int size) {
	SIMPLEUI_GLOBAL::queuedFonts.emplace_back(name, path, size);
}

inline void CreateFont(const std::string& name, const std::string& path, int size=64) {
	if (IsWindowReady()) {
		#ifdef EXCLUDE_SIMPLEUI_FREETYPE
			static int codepointsCount = 0;
			static int* codepoints = RAYLIB_FUNCTIONAL::LoadCodepoints(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ЁАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯёабвгдежзийклмнопрстуфхцчшщъыьэюя", &codepointsCount);
			Font ft = RAYLIB_FUNCTIONAL::LoadFontEx(path.c_str(), (size > 0 ? size : 64), codepoints, codepointsCount);
			if (ft.texture.id) {
				RAYLIB_FUNCTIONAL::GenTextureMipmaps(&ft.texture);
				RAYLIB_FUNCTIONAL::SetTextureFilter(ft.texture, TEXTURE_FILTER_BILINEAR);
				SIMPLEUI_GLOBAL::Fonts.push_back(ft);
				SIMPLEUI_GLOBAL::FontsIndexes.emplace(name, SIMPLEUI_GLOBAL::Fonts.size() - 1);
			} else {
				UnloadFont(ft);
			}
		#else
			FT_TextManagement::CreateFont(name, {path}, size);
		#endif
	} else {
		SIMPLEUI_GLOBAL::queuedFonts.emplace_back(name, path, size);
	}
}

inline void CreateFont(const std::string& name, const std::vector<std::string>& paths, int size=64) {
	if (paths.empty()) return;

	if (IsWindowReady()) {
		#ifdef EXCLUDE_SIMPLEUI_FREETYPE
			static int codepointsCount = 0;
			static int* codepoints = RAYLIB_FUNCTIONAL::LoadCodepoints(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ЁАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯёабвгдежзийклмнопрстуфхцчшщъыьэюя", &codepointsCount);
			Font ft = RAYLIB_FUNCTIONAL::LoadFontEx(paths[0].c_str(), (size > 0 ? size : 64), codepoints, codepointsCount);
			if (ft.texture.id) {
				RAYLIB_FUNCTIONAL::GenTextureMipmaps(&ft.texture);
				RAYLIB_FUNCTIONAL::SetTextureFilter(ft.texture, TEXTURE_FILTER_BILINEAR);
				SIMPLEUI_GLOBAL::Fonts.push_back(ft);
				SIMPLEUI_GLOBAL::FontsIndexes.emplace(name, SIMPLEUI_GLOBAL::Fonts.size() - 1);
			} else {
				UnloadFont(ft);
			}
		#else
			FT_TextManagement::CreateFont(name, paths, size);
		#endif
	} else {
		SIMPLEUI_GLOBAL::queuedFontsV.emplace_back(name, paths, size);
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
		if (text != other) {
			text = other;
			changed = true;
		}
		return *this;
	}

	const SUI_Text& operator=(const char* other) {
		std::string st = other;

		if (text.size() != st.size()) {
			changed = true;
		} else {
			changed = text != st;
		}

		text = st;
		return *this;
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
	inline std::vector<Task*> ActiveTasks;

	class Task {
		Task(float TimeInSeconds, std::function<void(void)> f) : TimeLeft(TimeInSeconds), Callback(f) {
			ActiveTasks.push_back(this);
		}

		Task() = delete;
		Task(const Task& o) = delete;
		void operator=(const Task& o) = delete;
	public:
		float TimeLeft{};
		std::function<void(void)> Callback{};

		void Cancel() {
			auto obj = find(ActiveTasks.begin(), ActiveTasks.end(), this);
			if (obj != ActiveTasks.end()) {
				ActiveTasks.erase(obj);
			}
			delete this;
		}

		~Task() {}

		static Task* Create(float TimeInSeconds, std::function<void(void)> f) {
			Task* t = new Task(TimeInSeconds, f);

			return t;
		}
	};

	inline void UpdateTasks(float dt) {
		for (int i = 0; i < ActiveTasks.size();) {
			if (ActiveTasks[i]->TimeLeft <= 0) {
				Task* t = ActiveTasks[i];
				ActiveTasks.erase(ActiveTasks.begin() + i);

				t->Callback();
				delete t;
			} else {
				ActiveTasks[i]->TimeLeft -= dt;
				i++;
			}
		}
	}
}

template <typename T>
class ChangedSignal : public IChangedSignal {
public:
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

	ChangedSignal() = delete;
	ChangedSignal(T& p, std::function<void(void)> func) : SignalPTR(&p), Callback(func) {
		SIMPLEUI_GLOBAL::ActiveSignals.push_back(this);
		LastValue = new T(p);
	}
	~ChangedSignal() {
		if (!LastValue) return;
		delete LastValue;
	}
public:
	void Disconnect() {
		auto z = find(SIMPLEUI_GLOBAL::ActiveSignals.begin(), SIMPLEUI_GLOBAL::ActiveSignals.end(), this);
		if (z != SIMPLEUI_GLOBAL::ActiveSignals.end()) SIMPLEUI_GLOBAL::ActiveSignals.erase(z);
		delete this;
	}

	static ChangedSignal* New(T& p, std::function<void(void)> func) {
		return new ChangedSignal(std::forward<T&>(p), func);
	}
};

template <typename T>
class SafeChangedSignal : public IChangedSignal {
public:
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
	Instance* LinkedTo = nullptr;
	std::function<void(void)> Callback;

	SafeChangedSignal() = delete;
	SafeChangedSignal(Instance* linked, T& p, std::function<void(void)> func) : SignalPTR(&p), Callback(func), LinkedTo(linked) {
		auto it = SIMPLEUI_GLOBAL::SafeActiveSignals.find(linked);
		if (it != SIMPLEUI_GLOBAL::SafeActiveSignals.end()) {
			it->second.push_back(this);
		} else {
			SIMPLEUI_GLOBAL::SafeActiveSignals.insert({linked, {this}});
		}

		LastValue = new T(p);
	}
	~SafeChangedSignal() {
		if (!LastValue) return;
		delete LastValue;
	}
public:
	void Disconnect() {
		auto it = SIMPLEUI_GLOBAL::SafeActiveSignals.find(LinkedTo);
		if (it != SIMPLEUI_GLOBAL::SafeActiveSignals.end()) {
			auto z = find(it->second.begin(), it->second.end(), this);
			if (z != it->second.end()) it->second.erase(z);

			if (it->second.empty()) {
				SIMPLEUI_GLOBAL::SafeActiveSignals.erase(it);
			}
		}
		delete this;
	}

	static SafeChangedSignal* New(Instance* linked, T& p, std::function<void(void)> func) {
		return new SafeChangedSignal(linked, std::forward<T&>(p), func);
	}
};

template <typename T>
class AtomicChangedSignal : public IChangedSignal {
public:
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

	AtomicChangedSignal() = delete;
	AtomicChangedSignal(std::atomic<T>& p, std::function<void(void)> func) : SignalPTR(p), Callback(func) {
		SIMPLEUI_GLOBAL::ActiveSignals.push_back(this);
		LastValue.store(new T(p.load()));
	}
	~AtomicChangedSignal() {
		if (!LastValue.load()) return;
		delete LastValue.load();
	}
public:
	void Disconnect() {
		auto z = find(SIMPLEUI_GLOBAL::ActiveSignals.begin(), SIMPLEUI_GLOBAL::ActiveSignals.end(), this);
		if (z != SIMPLEUI_GLOBAL::ActiveSignals.end()) SIMPLEUI_GLOBAL::ActiveSignals.erase(z);
		delete this;
	}

	static AtomicChangedSignal* New(T& p, std::function<void(void)> func) {
		return new AtomicChangedSignal(std::forward<T&>(p), func);
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
	template <typename T, typename Y, typename = void>
	struct is_castable : std::false_type {};

	template <typename T, typename Y>
	struct is_castable<T, Y, std::void_t<decltype(static_cast<T>(std::declval<Y>()))>> : std::true_type {};

	template <typename T, typename Y>
	constexpr bool is_castable_v = is_castable<T, Y>::value;

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

	class SafeAnimation;
	inline std::unordered_map<void*, SafeAnimation*> ActiveSafeAnimations;
	inline std::unordered_map<Instance*, std::vector<void*>> ActiveSafeAnimationsLinks;

	inline void deleteCurrent(void* ptr);

	enum class AnimationType {
		INT = 0,
		FLOAT,
		COLOR,
		VECTOR2,
		NUMX,
		NUMY,
		NONE
	};

	template<typename T>
	AnimationType ConvertAnimationType() {
		if (std::is_same_v<T, int>) return AnimationType::INT;
		if (std::is_same_v<T, float>) return AnimationType::FLOAT;
		if (std::is_same_v<T, Color>) return AnimationType::COLOR;
		if (std::is_same_v<T, SpecialVector2>) return AnimationType::VECTOR2;
		if (std::is_same_v<T, SpecialVector2::num_x>) return AnimationType::NUMX;
		if (std::is_same_v<T, SpecialVector2::num_y>) return AnimationType::NUMY;
		return AnimationType::NONE;
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

		AnimationType type = AnimationType::INT;

		void operator=(const Animation& o) = delete;
		Animation(const Animation& o) = delete;
		Animation() = delete;
		Animation(int* ptr, float time, int endValue, AnimationType type, Function func = Linear, Ease ease = In) : type(type), startValueI(*ptr), endValueI(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(float* ptr, float time, float endValue, AnimationType type, Function func = Linear, Ease ease = In) : type(type), startValueF(*ptr), endValueF(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(Color* ptr, float time, Color endValue, AnimationType type, Function func = Linear, Ease ease = In) : type(type), startValueC(*ptr), endValueC(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(SpecialVector2* ptr, float time, SpecialVector2 endValue, AnimationType type, Function func = Linear, Ease ease = In) : type(type), startValueV(*ptr), endValueV(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(SpecialVector2::num_x* ptr, float time, float endValue, AnimationType type, Function func = Linear, Ease ease = In) : type(type), startValueNX(*ptr), endValueNX(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		Animation(SpecialVector2::num_y* ptr, float time, float endValue, AnimationType type, Function func = Linear, Ease ease = In) : type(type), startValueNY(*ptr), endValueNY(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
	public:
		std::function<void(void)> Completed = []() {};
		bool Update() {
			currentTime += SIMPLEUI_GLOBAL::dt;
			if (currentTime >= endTime) {
				if (type == AnimationType::INT) { *(int*)ptr = endValueI; }
				else if (type == AnimationType::FLOAT) { *(float*)ptr = endValueF; }
				else if (type == AnimationType::COLOR) { *(Color*)ptr = endValueC; }
				else if (type == AnimationType::VECTOR2) { *(SpecialVector2*)ptr = endValueV; }
				else if (type == AnimationType::NUMX) { *(SpecialVector2::num_x*)ptr = endValueNX; }
				else if (type == AnimationType::NUMY) { *(SpecialVector2::num_y*)ptr = endValueNY; }
				return true;
			}
			if (type == AnimationType::INT) { *(int*)ptr = sui_lerp(startValueI, endValueI, getTime(func, ease, currentTime / endTime)); }
			else if (type == AnimationType::FLOAT) { *(float*)ptr = sui_lerp(startValueF, endValueF, getTime(func, ease, currentTime / endTime)); }
			else if (type == AnimationType::COLOR) { *(Color*)ptr = ColorLerp(startValueC, endValueC, getTime(func, ease, currentTime / endTime)); }
			else if (type == AnimationType::VECTOR2) { *(SpecialVector2*)ptr = SpecialVector2{ sui_lerp(startValueV.x, endValueV.x, getTime(func, ease, currentTime / endTime)), sui_lerp(startValueV.y, endValueV.y, getTime(func, ease, currentTime / endTime)) }; }
			else if (type == AnimationType::NUMX) { *(SpecialVector2::num_x*)ptr = sui_lerp(startValueNX, endValueNX, getTime(func, ease, currentTime / endTime)); }
			else if (type == AnimationType::NUMY) { *(SpecialVector2::num_y*)ptr = sui_lerp(startValueNY, endValueNY, getTime(func, ease, currentTime / endTime)); }
			return false;
		}

		template<typename T, typename Y>
		static Animation* Create(T* ptr, float time, Y endValue, Function func = Linear, Ease ease = In) {
			if (!is_castable_v<Y, T>) {
				std::cout << RED_ANSI << "Animate, unacceptable types" << DEFAULT_ANSI << std::endl;
				return nullptr;
			}

			deleteCurrent((void*)ptr);
			AnimationType type = ConvertAnimationType<T>();
			Animation* s = new Animation(ptr, time, endValue, type, func, ease);
			ActiveAnimations.insert({ ptr, s });
			return s;
		}
	};

	// Same as Animation but stops when object which data animating deleted
	class SafeAnimation {
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
		SpecialVector2::num_y startValueNY{};
		SpecialVector2::num_x endValueNX{};
		SpecialVector2::num_y endValueNY{};
		SpecialVector2 startValueV{};
		SpecialVector2 endValueV{};

		AnimationType type = AnimationType::INT;

		void operator=(const SafeAnimation& o) = delete;
		SafeAnimation(const SafeAnimation& o) = delete;
		SafeAnimation() = delete;
		SafeAnimation(Instance* link, int* ptr, float time, int endValue, AnimationType type, Function func = Linear, Ease ease = In) : LinkedTo(link), type(type), startValueI(*ptr), endValueI(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		SafeAnimation(Instance* link, float* ptr, float time, float endValue, AnimationType type, Function func = Linear, Ease ease = In) : LinkedTo(link), type(type), startValueF(*ptr), endValueF(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		SafeAnimation(Instance* link, Color* ptr, float time, Color endValue, AnimationType type, Function func = Linear, Ease ease = In) : LinkedTo(link), type(type), startValueC(*ptr), endValueC(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		SafeAnimation(Instance* link, SpecialVector2* ptr, float time, SpecialVector2 endValue, AnimationType type, Function func = Linear, Ease ease = In) : LinkedTo(link), type(type), startValueV(*ptr), endValueV(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		SafeAnimation(Instance* link, SpecialVector2::num_x* ptr, float time, float endValue, AnimationType type, Function func = Linear, Ease ease = In) : LinkedTo(link), type(type), startValueNX(*ptr), endValueNX(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
		SafeAnimation(Instance* link, SpecialVector2::num_y* ptr, float time, float endValue, AnimationType type, Function func = Linear, Ease ease = In) : LinkedTo(link), type(type), startValueNY(*ptr), endValueNY(endValue), ptr(ptr), func(func), ease(ease), endTime(time) {}
	public:
		std::function<void(void)> Completed = []() {};
		const Instance* LinkedTo = nullptr;

		bool Update() {
			currentTime += SIMPLEUI_GLOBAL::dt;
			if (currentTime >= endTime) {
				if (type == AnimationType::INT) { *(int*)ptr = endValueI; }
				else if (type == AnimationType::FLOAT) { *(float*)ptr = endValueF; }
				else if (type == AnimationType::COLOR) { *(Color*)ptr = endValueC; }
				else if (type == AnimationType::VECTOR2) { *(SpecialVector2*)ptr = endValueV; }
				else if (type == AnimationType::NUMX) { *(SpecialVector2::num_x*)ptr = endValueNX; }
				else if (type == AnimationType::NUMY) { *(SpecialVector2::num_y*)ptr = endValueNY; }
				return true;
			}
			if (type == AnimationType::INT) { *(int*)ptr = sui_lerp(startValueI, endValueI, getTime(func, ease, currentTime / endTime)); }
			else if (type == AnimationType::FLOAT) { *(float*)ptr = sui_lerp(startValueF, endValueF, getTime(func, ease, currentTime / endTime)); }
			else if (type == AnimationType::COLOR) { *(Color*)ptr = ColorLerp(startValueC, endValueC, getTime(func, ease, currentTime / endTime)); }
			else if (type == AnimationType::VECTOR2) { *(SpecialVector2*)ptr = SpecialVector2{ sui_lerp(startValueV.x, endValueV.x, getTime(func, ease, currentTime / endTime)), sui_lerp(startValueV.y, endValueV.y, getTime(func, ease, currentTime / endTime)) }; }
			else if (type == AnimationType::NUMX) { *(SpecialVector2::num_x*)ptr = sui_lerp(startValueNX, endValueNX, getTime(func, ease, currentTime / endTime)); }
			else if (type == AnimationType::NUMY) { *(SpecialVector2::num_y*)ptr = sui_lerp(startValueNY, endValueNY, getTime(func, ease, currentTime / endTime)); }
			return false;
		}

		template<typename T, typename Y>
		static SafeAnimation* Create(Instance* Link, T* ptr, float time, Y endValue, Function func = Linear, Ease ease = In) {
			if (!Link) {
				std::cout << YELLOW_ANSI << "Animate, SafeAnimation requires Instance" << DEFAULT_ANSI << std::endl;
				return nullptr;
			}

			if (!is_castable_v<Y, T>) {
				std::cout << RED_ANSI << "Animate, unacceptable types" << DEFAULT_ANSI << std::endl;
				return nullptr;
			}

			deleteCurrent((void*)ptr);
			AnimationType type = ConvertAnimationType<T>();
			SafeAnimation* s = new SafeAnimation(Link, ptr, time, endValue, type, func, ease);

			ActiveSafeAnimations.insert({ ptr, s });

			auto an2 = ActiveSafeAnimationsLinks.find(Link);
			if (an2 != ActiveSafeAnimationsLinks.end()) {
				an2->second.push_back(ptr);
			} else {
				ActiveSafeAnimationsLinks.insert({ Link, { ptr } });
			}
			return s;
		}
	};

	inline void UpdateAnimations(float t) {
		std::vector<Animation*> doneA;
		for (auto it = ActiveAnimations.begin(); it != ActiveAnimations.end();) {
			if (it->second->Update()) {
				doneA.push_back(it->second);
				it = ActiveAnimations.erase(it);
			} else {
				it++;
			}
		}

		std::vector<std::pair<void*, SafeAnimation*>> doneS;
		for (auto it = ActiveSafeAnimations.begin(); it != ActiveSafeAnimations.end();) {
			if (it->second->Update()) {
				doneS.emplace_back(it->first, it->second);
				it = ActiveSafeAnimations.erase(it);
			} else {
				it++;
			}
		}

		for (auto& [key, sa] : doneS) {
			auto link = ActiveSafeAnimationsLinks.find(const_cast<Instance*>(sa->LinkedTo));
			if (link != ActiveSafeAnimationsLinks.end()) {
				auto& v = link->second;
				v.erase(std::remove(v.begin(), v.end(), key), v.end());
			}
		}

		for (Animation* a : doneA) {
			a->Completed();
			delete a;
		}
		for (auto& [key, sa] : doneS) {
			sa->Completed();
			delete sa;
		}
	}

	inline void deleteCurrent(void* ptr) {
		auto an = ActiveAnimations.find(ptr);
		if (an != ActiveAnimations.end()) {
			delete an->second;
			ActiveAnimations.erase(an);
		}

		auto an2 = ActiveSafeAnimations.find(ptr);
		if (an2 != ActiveSafeAnimations.end()) {

			SafeAnimation* animation = an2->second;

			auto it = ActiveSafeAnimationsLinks.find(const_cast<Instance*>(animation->LinkedTo));
			if (it != ActiveSafeAnimationsLinks.end()) {
				for (int i = 0; i < it->second.size(); i++) {
					if (it->second[i] == ptr) {
						it->second.erase(it->second.begin() + i);
						break;
					}
				}
			}

			delete animation;
			ActiveSafeAnimations.erase(an2);
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

inline Vector2 getTextOffset(TextAnchorEnum anchor) {
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

inline Vector3 getTextCFrame(const char* text, 
	#ifdef EXCLUDE_SIMPLEUI_FREETYPE
	Font 
	#else
	FT_TextManagement::FT_Font&
	#endif
	font, Rectangle rec, TextAnchorEnum anchor, int maxTextSize, int Spacing) {
	if (maxTextSize < 0 or maxTextSize > rec.height) maxTextSize = rec.height;

	int endX{};
	int endY{};
	float endSize = 1;
	float sizeMax = maxTextSize;
	SpecialVector2 textSize{};

	while (endSize < sizeMax) {
		float middle = (endSize + sizeMax + 1) / 2;
		textSize = 
		#ifdef EXCLUDE_SIMPLEUI_FREETYPE
		RAYLIB_FUNCTIONAL::MeasureTextEx
		#else
		MeasureTextEx
		#endif
		(font, text, middle, Spacing);
		if (textSize.x <= rec.width and textSize.y <= rec.height) endSize = middle;
		else sizeMax = middle - 1;
	}

	if (endSize > maxTextSize) endSize = maxTextSize;
	Vector2 ofst = getTextOffset(anchor);
	float offsetX = ofst.x;
	float offsetY = ofst.y;

	endX = offsetX * (rec.width - textSize.x); if (endX < 0) endX = 0;
	endY = offsetY * (rec.height - textSize.y);  if (endY < 0) endY = 0;

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

	FOLDER = 50,

	// Additional classes from SUIextension.h
	GRAPHBUILDER = 100,
	TOGGLESWITCHER,
	CHECKBOX,
	DROPBOX,
	PROGRESSBAR
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
	friend void SIMPLEUI_GLOBAL::CollectDeadObjects();
protected:
	size_t lastUpdateFrame = 0;
	bool DontSeekParent = false;
public:
	Instance* Parent = nullptr;
	std::vector<Instance*> Children;
	long uniqueID = -1;
	InstanceType Class = InstanceType::INSTANCE;
	bool updateChildrenZIndex = true;
protected:
	bool updateWhenWillBeVisible = true;
	bool __ParentObject{};
	std::vector<std::tuple<EventType, InstanceCallback, MouseButtonType>> events;
public:
	std::string Name = "Instance";
protected:
	std::vector<std::pair<long, Instance*>> childsAddedInFrame;
	std::vector<std::pair<long, Instance*>> childsRemovedInFrame;

	virtual void basicCloneOperation(Instance* copyfrom) {
		this->Parent = nullptr;
		this->Children.clear();
		updateWhenWillBeVisible = true;
		SIMPLEUI_GLOBAL::sceneDirty = true;

		this->uniqueID = SIMPLEUI_GLOBAL::currentUniqueObjectID++;
		SIMPLEUI_GLOBAL::deletedObjectsByID.push_back(0);

		if (!copyfrom) return;

		for (Instance* c : copyfrom->Children) {
			c->Clone()->setParent(this);
		}
	}

	Instance(bool a) : uniqueID(SIMPLEUI_GLOBAL::currentUniqueObjectID++), __ParentObject(true) {
		SIMPLEUI_GLOBAL::deletedObjectsByID.push_back(0);
	}

	Instance(Instance* p);
	Instance() = delete;
	virtual ~Instance() {}

public:
	void AddEvent(EventType t, InstanceCallback f, MouseButtonType m);

	virtual bool hasEvent(EventType t) const {
		for (auto& [type, _, __] : events) {
			if (type == t) {
				return true;
			}
		}
		return false;
	}

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
		std::function<Instance* (Instance*)> l = [&](Instance* ptr) -> Instance* {
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
		std::function<Instance* (Instance*)> l = [&](Instance* ptr) -> Instance* {
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

	void deleteAllChildren();

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

		for (const auto& [type, func, _] : events) {
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
	Vector2 Value = { 0,0 };

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

inline Vector2 getCanvasRealPos(Object2D*);
inline Vector2 getObject2DRS(Instance*);
inline Vector2 getObject2DRP(Instance*);

inline void FlushRectanglesBatch();

struct RectInstance {
	float x, y, w, h;
	float ox, oy, rot, z;
	float dx, dy, dw, dh;
	float u0, v0, u1, v1;
	unsigned char r, g, b, a;
	unsigned char br, bg, bb, ba;
	float inset;
	float clip;
	float shape;
};

namespace RectGPU {
	constexpr int MaxQuads = 65536;
	inline unsigned int vao = 0;
	inline unsigned int vbo = 0;
	inline std::vector<RectInstance> insts;

	inline void Init() {
		float corners[8] = { 0, 0, 0, 1, 1, 1, 1, 0 };
		unsigned short idx[6] = { 0, 1, 3, 1, 2, 3 };

		vao = RAYLIB_FUNCTIONAL::rlLoadVertexArray();
		RAYLIB_FUNCTIONAL::rlEnableVertexArray(vao);

		RAYLIB_FUNCTIONAL::rlLoadVertexBuffer(corners, sizeof(corners), false);
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(0, 2, RL_FLOAT, false, 2 * sizeof(float), 0);
		RAYLIB_FUNCTIONAL::rlEnableVertexAttribute(0);

		vbo = RAYLIB_FUNCTIONAL::rlLoadVertexBuffer(nullptr, MaxQuads * (int)sizeof(RectInstance), true);
		int stride = (int)sizeof(RectInstance);
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(6, 4, RL_FLOAT, false, stride, offsetof(RectInstance, x));
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(7, 4, RL_FLOAT, false, stride, offsetof(RectInstance, ox));
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(8, 4, RL_FLOAT, false, stride, offsetof(RectInstance, dx));
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(9, 4, RL_FLOAT, false, stride, offsetof(RectInstance, u0));
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(10, 4, RL_UNSIGNED_BYTE, true, stride, offsetof(RectInstance, r));
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(11, 4, RL_UNSIGNED_BYTE, true, stride, offsetof(RectInstance, br));
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(12, 1, RL_FLOAT, false, stride, offsetof(RectInstance, inset));
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(13, 1, RL_FLOAT, false, stride, offsetof(RectInstance, clip));
		RAYLIB_FUNCTIONAL::rlSetVertexAttribute(14, 1, RL_FLOAT, false, stride, offsetof(RectInstance, shape));

		for (int i = 6; i <= 14; i++) {
			RAYLIB_FUNCTIONAL::rlEnableVertexAttribute(i);
			RAYLIB_FUNCTIONAL::rlSetVertexAttributeDivisor(i, 1);
		}

		RAYLIB_FUNCTIONAL::rlLoadVertexBufferElement(idx, sizeof(idx), false);
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

	inline void PushInstance(Vector2 pos, Vector2 size, float roundness, float thickness, float inset, Color fill, Color border, float rotation, Vector2 origin, const QuadTex& t, float clip, float shape=0) {
		float z = floorf(thickness) + std::clamp(roundness, 0.0f, 1.0f) * 0.99f;
		float dw = t.use > 0.5f ? t.dest.width : 0.0f;
		insts.emplace_back(
			pos.x, pos.y, size.x, size.y,
			origin.x, origin.y, rotation * DEG2RAD, z,
			t.dest.x, t.dest.y, dw, t.dest.height,
			t.u0, t.v0, t.u1, t.v1,
			fill.r, fill.g, fill.b, fill.a,
			border.r, border.g, border.b, border.a,
			inset,
			clip,
			shape
		);
	}
}

inline void DrawRoundRectBatch(const RoundRectData& r) {
	SIMPLEUI_GLOBAL::CurrentCustomShader = SIMPLEUI_GLOBAL::RectangleRoundnessShader;
	if (r.Texture.id) {
		auto& cur = SIMPLEUI_GLOBAL::CurrentBatchTexture;
		if (cur and cur != r.Texture.id) FlushRectanglesBatch();
		cur = r.Texture.id;
	}

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
	unsigned char borderA = (unsigned char)(r.BorderColor.a * (1 - r.BorderTransparency));
	bool hasBorder = r.BorderThickness > 0 and borderA;
	if (!fillA and !hasBorder) return;

	float off = 0.0f;
	if (hasBorder) {
		float k = (r.borderType == BorderPlacement::BORDER_INNER) ? 0.0f : ((r.borderType == BorderPlacement::BORDER_MIDDLE) ? 0.5f : 1.0f);
		off = std::roundf(r.BorderThickness * k);
	}

	RectGPU::PushInstance(
		{ r.Pos.x - off, r.Pos.y - off },
		{ r.Size.x + off * 2, r.Size.y + off * 2 },
		r.Roundness, hasBorder ? (float)r.BorderThickness : 0.0f, off,
		{ r.Color.r, r.Color.g, r.Color.b, fillA },
		{ r.BorderColor.r, r.BorderColor.g, r.BorderColor.b, borderA },
		r.Rotation, { r.Origin.x + off, r.Origin.y + off }, qt, 
		((SIMPLEUI_GLOBAL::clipping and !SIMPLEUI_GLOBAL::clipStack.empty()) ? SIMPLEUI_GLOBAL::clipStack.back() : -1),
		r.BackgroundShape
	);
}

inline void FlushRectanglesBatch() {
	auto& v = RectGPU::insts;
	if (v.empty()) return;

	static Shader shader = getShader(SIMPLEUI_GLOBAL::RectangleRoundnessShader);
	if (!RectGPU::vao) RectGPU::Init();

	RAYLIB_FUNCTIONAL::rlDrawRenderBatchActive();
	RAYLIB_FUNCTIONAL::rlEnableShader(shader.id);

	static int clipLoc = RAYLIB_FUNCTIONAL::rlGetLocationUniform(shader.id, "clips");
	if (!SIMPLEUI_GLOBAL::clips.empty()) {
		int n = (int)std::min<size_t>(SIMPLEUI_GLOBAL::clips.size(), SIMPLEUI_GLOBAL::MAX_CLIP_STACK_SIZE);
		RAYLIB_FUNCTIONAL::rlSetUniform(clipLoc, SIMPLEUI_GLOBAL::clips.data(), RAYLIB_FUNCTIONAL::RL_SHADER_UNIFORM_VEC4, n * 2);
	}

	RAYLIB_FUNCTIONAL::rlSetUniformMatrix(shader.locs[RAYLIB_FUNCTIONAL::SHADER_LOC_MATRIX_MVP], RectGPU::Mul(RAYLIB_FUNCTIONAL::rlGetMatrixModelview(), RAYLIB_FUNCTIONAL::rlGetMatrixProjection()));

	int diffuseLoc = shader.locs[RAYLIB_FUNCTIONAL::SHADER_LOC_COLOR_DIFFUSE];
	if (diffuseLoc >= 0) {
		float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		RAYLIB_FUNCTIONAL::rlSetUniform(diffuseLoc, white, RAYLIB_FUNCTIONAL::RL_SHADER_UNIFORM_VEC4, 1);
	}

	unsigned int texId = SIMPLEUI_GLOBAL::CurrentBatchTexture ? SIMPLEUI_GLOBAL::CurrentBatchTexture : RAYLIB_FUNCTIONAL::rlGetTextureIdDefault();
	RAYLIB_FUNCTIONAL::rlActiveTextureSlot(0);
	RAYLIB_FUNCTIONAL::rlEnableTexture(texId);

	size_t done = 0;
	while (done < RectGPU::insts.size()) {
		int n = (int)std::min<size_t>(RectGPU::MaxQuads, RectGPU::insts.size() - done);
		RAYLIB_FUNCTIONAL::rlUpdateVertexBuffer(RectGPU::vbo, RectGPU::insts.data() + done, n * (int)sizeof(RectInstance), 0);
		RAYLIB_FUNCTIONAL::rlEnableVertexArray(RectGPU::vao);
		RAYLIB_FUNCTIONAL::rlDrawVertexArrayElementsInstanced(0, 6, nullptr, n);
		done += n;
	}

	RAYLIB_FUNCTIONAL::rlDisableVertexArray();
	RAYLIB_FUNCTIONAL::rlDisableTexture();

	v.clear();
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
	bool lastVisible = false;
	bool posOrSizeChangedResult = false;

	void SameUpdate() {
		if (Active != lastActive or lastZIndex != ZIndex) {
			lastActive = Active;
			lastZIndex = ZIndex;

			if (Parent) {
				Parent->updateChildrenZIndex = true;
			}
		}

		childsAddedInFrame.clear();
		childsRemovedInFrame.clear();
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

	bool hasEvent(EventType t) const override {
		for (auto& [type, _, __] : events) {
			if (type == t) {
				return true;
			}
		}

		return false;
	}

	Vector2 RealSize{}; // Absolute size in pixels (not for changing from somewhere)
	Vector2 RealPos{}; // Absolute position in pixels (not for changing from somewhere)
	SUI_EEC EnterEventCondition = SUI_EEC::EEC_DEFAULT;

	SpecialVector2 PositionOFFSET{ 0, 0, this };
	SpecialVector2 AnchorPositionOFFSET{ 0, 0, this };
	SpecialVector2 Position{ 0, 0, this };
	SpecialVector2 AnchorPosition{ 0, 0, this };

	SpecialVector2 Size{ 0, 0, this };
	SpecialVector2 SizeOFFSET{ 0, 0, this };

	float Rotation = 0; // Local object rotation
	Vector2 Origin = { 0.5,0.5 }; // Local object origin
	Vector2 OriginOFFSET = { 0, 0 }; // Local object origin in pixels

	float BackgroundTransparency{};
	Color BackgroundColor = { 255,255,255,255 };
	bool Visible = true;

	float Roundness = 0.0f;
	short Segments = 5; // Deprecated value, now simpleUI using SDF for corners

	short BorderThickness{};
	float BorderTransparency{};
	Color BorderColor{};
	BorderPlacement BorderType = BorderPlacement::BORDER_INNER;

	bool ClipDescendants = false;

	int ZIndex = 0;
	bool Active = false;

	int BackgroundShape = 0; // 0 default builtin shape. change it to use your shapes (describe shape in rectangle_roundness.frag)

	void getRealObject2Dsize() {
		Vector2 sizePx = {};
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

		Vector2 parentSizePx = parent2D ? parent2D->RealSize : Vector2{ static_cast<float>(SIMPLEUI_GLOBAL::winWidth), static_cast<float>(SIMPLEUI_GLOBAL::winHeight) };

		sizePx.x = std::roundf(parentSizePx.x * self->Size.x + self->SizeOFFSET.x);
		sizePx.y = std::roundf(parentSizePx.y * self->Size.y + self->SizeOFFSET.y);

		RealSize = sizePx;
	}

	void getRealObject2Dposition() {
		Vector2 posPx = { 0.0f, 0.0f };
		Vector2 sizePx = RealSize;

		Vector2 anchorPx = {
			std::roundf(sizePx.x * AnchorPosition.x + AnchorPositionOFFSET.x),
			std::roundf(sizePx.y * AnchorPosition.y + AnchorPositionOFFSET.y)
		};

		Instance* current = Parent;
		while (current) {
			if (!Is2DInheritor(current)) { current = current->Parent; continue; }

			Object2D* obj = static_cast<Object2D*>(current);

			Vector2 parentSizePx = obj->RealSize;
			Vector2 parentPosPx = obj->RealPos;

			Vector2 myLocalPx = {
				std::roundf(parentSizePx.x * Position.x + PositionOFFSET.x - anchorPx.x),
				std::roundf(parentSizePx.y * Position.y + PositionOFFSET.y - anchorPx.y)
			};

			if (obj->Class == SCROLLFRAME) {
				Vector2 canvasPx = getCanvasRealPos(obj);
				posPx.x = std::roundf(parentPosPx.x + myLocalPx.x - canvasPx.x);
				posPx.y = std::roundf(parentPosPx.y + myLocalPx.y - canvasPx.y);
			} else {
				posPx.x = std::roundf(parentPosPx.x + myLocalPx.x);
				posPx.y = std::roundf(parentPosPx.y + myLocalPx.y);
			}

			RealPos = posPx;
			return;
		}

		Vector2 rootSizePx = { static_cast<float>(SIMPLEUI_GLOBAL::winWidth), static_cast<float>(SIMPLEUI_GLOBAL::winHeight) };
		Vector2 rootLocalPx = {
			std::roundf(rootSizePx.x * Position.x + PositionOFFSET.x - anchorPx.x),
			std::roundf(rootSizePx.y * Position.y + PositionOFFSET.y - anchorPx.y)
		};

		RealPos = rootLocalPx;
	}

	Vector2 getMousePosition() {
		Vector2 mousePos = SIMPLEUI_GLOBAL::mousePosition;
		return { (mousePos.x - RealPos.x) / RealSize.x, (mousePos.y - RealPos.y) / RealSize.y };
	}

	// Get bounds of background (Requires calculated size and position)
	Rectangle GetRotatedBounds() {
		Vector2 pos = RealPos;
		Vector2 size = RealSize;
		if (Rotation == 0.0f) return { pos.x, pos.y, size.x, size.y };

		float sn = sinf(Rotation * DEG2RAD);
		float cs = cosf(Rotation * DEG2RAD);
		float ox = pos.x + Origin.x * size.x + OriginOFFSET.x;
		float oy = pos.y + Origin.y * size.y + OriginOFFSET.y;

		float xs[4] = { pos.x, pos.x + size.x, pos.x + size.x, pos.x };
		float ys[4] = { pos.y, pos.y, pos.y + size.y, pos.y + size.y };

		float minX = FLT_MAX, minY = FLT_MAX, maxX = -FLT_MAX, maxY = -FLT_MAX;

		for (int i = 0; i < 4; i++) {
			float dx = xs[i] - ox;
			float dy = ys[i] - oy;
			float rx = ox + dx * cs - dy * sn;
			float ry = oy + dx * sn + dy * cs;
			minX = std::min(minX, rx);
			maxX = std::max(maxX, rx);
			minY = std::min(minY, ry);
			maxY = std::max(maxY, ry);
		}

		return { minX, minY, maxX - minX, maxY - minY };
	}

	virtual void Draw() {
		if (!Visible) return;
		if (BackgroundTransparency >= 1.0f and (BorderThickness == 0 or BorderTransparency >= 1.0f)) return;

		float bt = (float)BorderThickness;
		if (Rotation == 0.0f) {
			if (RealPos.x + RealSize.x + bt < 0 or RealPos.x - bt > SIMPLEUI_GLOBAL::winWidth or RealPos.y + RealSize.y + bt < 0 or RealPos.y - bt > SIMPLEUI_GLOBAL::winHeight) return;
		} else {
			Rectangle b = GetRotatedBounds();
			if (b.x + b.width + bt < 0 or b.x - bt > SIMPLEUI_GLOBAL::winWidth or b.y + b.height + bt < 0 or b.y - bt > SIMPLEUI_GLOBAL::winHeight) return;
		}

		RoundRectData rec = {
			RealPos, RealSize,
			BackgroundColor, BorderColor,
			BackgroundTransparency, Roundness, BorderTransparency,
			BorderThickness,
			Rotation,
			{Origin.x * RealSize.x + OriginOFFSET.x, Origin.y * RealSize.y + OriginOFFSET.y}
		};

		rec.borderType = BorderType;
		rec.BackgroundShape = BackgroundShape;

		DrawRoundRectBatch(rec);
	}

	bool pointInObject(Vector2 pos) {
		if (!SIMPLEUI_GLOBAL::mouseOnWindow) return false;

		if (Parent and Is2DInheritor(Parent) and static_cast<Object2D*>(Parent)->ClipDescendants) {
			Vector2 scrRS = getObject2DRS(Parent);
			Vector2 scrRP = getObject2DRP(Parent);
			if (scrRP.x > pos.x or scrRP.x + scrRS.x < pos.x or
				scrRP.y > pos.y or scrRP.y + scrRS.y < pos.y) {
				return false;
			}
		}

		float px = pos.x;
		float py = pos.y;

		if (Rotation != 0.0f) {
			float ox = RealPos.x + Origin.x * RealSize.x + OriginOFFSET.x;
			float oy = RealPos.y + Origin.y * RealSize.y + OriginOFFSET.y;
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

	bool MouseEntered = false; // works with MOUSE_ENTER MOUSE_LEAVE events only

	void Update(bool posOrSizeChanged) override {
		if (lastUpdateFrame == SIMPLEUI_GLOBAL::framesSinceStart) return;
		lastUpdateFrame = SIMPLEUI_GLOBAL::framesSinceStart;

		eventHandler();
		if (SIMPLEUI_GLOBAL::deletedObjectsByID[uniqueID]) return;

		if (lastVisible != Visible) {
			SIMPLEUI_GLOBAL::sceneDirty = true;
			lastVisible = Visible;
		}

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

		bool c = ClipDescendants;

		if (c) {
			SIMPLEUI_GLOBAL::ClipData clip = {
				RealPos.x, RealPos.y, RealSize.x, RealSize.y, 
				Roundness, Rotation, 
				{Origin.x * RealSize.x + OriginOFFSET.x, Origin.y * RealSize.y + OriginOFFSET.y}
			};

			SIMPLEUI_GLOBAL::PushClip(clip);
		}

		for (int i = 0; i < Children.size(); i++) {
			Instance* child = Children[i];
			child->Update(tempRes);
		}

		if (c) SIMPLEUI_GLOBAL::PopClip();
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

	std::pair<Vector2, Vector2> getRealObject2Dposition() {
		Vector2 pos1 = { Position1.x, Position1.y };
		Vector2 pos2 = { Position2.x, Position2.y };
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

			Vector2 parentPos = {
				obj->Position.x - obj->AnchorPosition.x * obj->Size.x,
				obj->Position.y - obj->AnchorPosition.y * obj->Size.y
			};

			if (obj->Class == SCROLLFRAME) {
				Vector2 CanvasPosition = getCanvasRealPos(obj);

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
	Vector2 Position1{};
	Vector2 Position2{};
	Color LineColor{};
	int Thickness = 5;
	int ZIndex = 0;
	bool Visible = true;

	void Draw() {
		if (Visible and Thickness) {
			auto [pos1, pos2] = getRealObject2Dposition();
			SIMPLEUI_GRAPHICS_WRAPS::DrawLineEx(pos1, pos2, Thickness, LineColor, { 0,0 }, { 0, 0 }, 0, 0);
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

#ifdef EXCLUDE_SIMPLEUI_FREETYPE
	inline Font getFont(int index) {
		if (index < 0 or index >= SIMPLEUI_GLOBAL::Fonts.size()) index = 0;
		return SIMPLEUI_GLOBAL::Fonts[index];
	}
#else
	inline FT_TextManagement::FT_Font& getFont(int index) {
		if (index < 0 or index >= FT_TextManagement::Fonts.size()) index = 0;
		return FT_TextManagement::Fonts[index];
	}
#endif

#ifdef EXCLUDE_SIMPLEUI_FREETYPE
	inline int getFontIndex(const std::string& name) {
		auto it = SIMPLEUI_GLOBAL::FontsIndexes.find(name);
		if (it != SIMPLEUI_GLOBAL::FontsIndexes.end())
			return it->second;

		return SIMPLEUI_GLOBAL::FontsIndexes.find(SIMPLEUI_GLOBAL::BASIC_FONT_NAME)->second;
	}
#else
	inline int getFontIndex(const std::string& name) {
		auto it = FT_TextManagement::FontsIndexes.find(name);
		if (it != FT_TextManagement::FontsIndexes.end())
			return it->second;

		return FT_TextManagement::FontsIndexes.find(SIMPLEUI_GLOBAL::BASIC_FONT_NAME)->second;
	}
#endif

class ScrollFrame : public Object2D {
	friend inline void Instance::deleteAllChildren();
	constexpr static const char* DefaultName = "ScrollFrame";
	constexpr static InstanceType DefaultClass = SCROLLFRAME;
	constexpr static unsigned int GridSectorSize = SCROLLFRAME_GRID_SIZE;

	struct ScrollSector {
		int X = 0;
		int Y = 0;
		std::vector<std::pair<long, Instance*>> Objects;
	};

	std::unordered_map<int, std::unordered_map<int, ScrollSector*>> Grid;
	std::unordered_map<long, std::vector<ScrollSector*>> SectorsOnObject;
	std::unordered_map<long, std::array<int, 4>> SectorRectOnObject;

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

		auto upit = toUpdateSectorsC.find(childID);
		if (upit != toUpdateSectorsC.end()) {
			toUpdateSectorsC.erase(upit);
			for (int i = 0; i < toUpdateSectors.size(); i++) {
				if (toUpdateSectors[i].first == childID) {
					toUpdateSectors.erase(toUpdateSectors.begin() + i);
					break;
				}
			}
		}

		auto it = SectorsOnObject.find(childID);
		if (it != SectorsOnObject.end()) {
			for (ScrollSector* sector : it->second) {
				for (int i = 0; i < sector->Objects.size(); i++) {
					if (sector->Objects[i].first == childID) {
						sector->Objects.erase(sector->Objects.begin() + i);
						break;
					}
				}
			}
			SectorsOnObject.erase(it);
			SectorRectOnObject.erase(childID);
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

	static void accumulateBounds(Instance* obj, float px, float py, float pw, float ph, float& minX, float& minY, float& maxX, float& maxY) {
		float cx = px;
		float cy = py;
		float cw = pw;
		float ch = ph;

		if (Is2DInheritor(obj)) {
			Object2D* o = static_cast<Object2D*>(obj);

			float w = std::roundf(pw * o->Size.x + o->SizeOFFSET.x);
			float h = std::roundf(ph * o->Size.y + o->SizeOFFSET.y);

			float ax = std::roundf(w * o->AnchorPosition.x + o->AnchorPositionOFFSET.x);
			float ay = std::roundf(h * o->AnchorPosition.y + o->AnchorPositionOFFSET.y);

			float x = px + std::roundf(pw * o->Position.x + o->PositionOFFSET.x - ax);
			float y = py + std::roundf(ph * o->Position.y + o->PositionOFFSET.y - ay);

			minX = std::min(minX, x);
			minY = std::min(minY, y);
			maxX = std::max(maxX, x + w);
			maxY = std::max(maxY, y + h);

			cx = x;
			cy = y;
			cw = w;
			ch = h;
		}

		for (Instance* child : obj->Children) {
			accumulateBounds(child, cx, cy, cw, ch, minX, minY, maxX, maxY);
		}
	}

	bool getSectorRect(Instance* generalObj, std::array<int, 4>& out) const {
		float minX = FLT_MAX;
		float minY = FLT_MAX;
		float maxX = -FLT_MAX;
		float maxY = -FLT_MAX;

		accumulateBounds(generalObj, 0, 0, RealSize.x, RealSize.y, minX, minY, maxX, maxY);

		if (minX > maxX or minY > maxY) return false;

		out[0] = (int)std::floor(minX / GridSectorSize);
		out[1] = (int)std::floor(maxX / GridSectorSize);
		out[2] = (int)std::floor(minY / GridSectorSize);
		out[3] = (int)std::floor(maxY / GridSectorSize);
		return true;
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
			sectorsDirty = true;
		}

		sector->Objects.push_back({ obj->uniqueID, obj });

		auto it3 = SectorsOnObject.find(obj->uniqueID);

		if (it3 == SectorsOnObject.end()) {
			SectorsOnObject[obj->uniqueID] = { sector };
		} else {
			SectorsOnObject[obj->uniqueID].push_back(sector);
		}
	}
private:
	Vector2 lastFullSize{};
	Vector2 lastCanvasFullPosition{};
	Vector2 lastCanvasPos{};
	bool lastVisible = false;
	bool sectorsDirty = false;

	void checkAndUpdateCurrentSectors(bool force = false) {
		Vector2 fullSize = RealSize;
		Vector2 fullPos = { CanvasPosition.x * RealSize.x + CanvasPositionOFFSET.x, CanvasPosition.y * RealSize.y + CanvasPositionOFFSET.y };

		if (force or lastVisible != Visible or SIMPLEUI_GLOBAL::windowSizeChanged or lastFullSize.x != fullSize.x or lastFullSize.y != fullSize.y or
			lastCanvasFullPosition.x != fullPos.x or lastCanvasFullPosition.y != fullPos.y or sectorsDirty) {
			lastFullSize = fullSize;
			lastCanvasFullPosition = fullPos;
			lastVisible = Visible;
			sectorsDirty = false;
			sectorsOnView.clear();
			Vector2 pos = fullPos;
			Vector2 lastpos = { fullPos.x + fullSize.x, fullPos.y + fullSize.y };

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

	std::unordered_map<long, Instance*> toUpdateSectorsC;
	std::vector<std::pair<long, Instance*>> toUpdateSectors;

	void secUpd(Instance* child) {
		if (!child) return;

		std::array<int, 4> rect;
		bool hasRect = getSectorRect(child, rect);

		auto checkIt = SectorsOnObject.find(child->uniqueID);
		if (checkIt == SectorsOnObject.end()) {
			checkIt = SectorsOnObject.insert({ child->uniqueID, {} }).first;
		} else {
			auto rc = SectorRectOnObject.find(child->uniqueID);
			if (hasRect and rc != SectorRectOnObject.end() and rc->second == rect) return;

			for (ScrollSector* sector : checkIt->second) {
				for (int i = 0; i < sector->Objects.size(); i++) {
					if (sector->Objects[i].first == child->uniqueID) {
						sector->Objects.erase(sector->Objects.begin() + i);
						break;
					}
				}
			}

			checkIt->second.clear();
		}

		if (!hasRect) {
			SectorRectOnObject.erase(child->uniqueID);
			return;
		}

		SectorRectOnObject[child->uniqueID] = rect;

		for (int i = rect[0]; i <= rect[1]; i++) {
			for (int j = rect[2]; j <= rect[3]; j++) {
				addObjToSector(child, i, j);
			}
		}
	}
protected:
	ScrollFrame(bool a) : Object2D(a) { Name = DefaultName; Class = DefaultClass; EnterEventCondition = EEC_IF_DESCENDANT_HIGHER; Active = true; ClipDescendants = true; };
	ScrollFrame(Instance* p) : Object2D(p) { Name = DefaultName; Class = DefaultClass; EnterEventCondition = EEC_IF_DESCENDANT_HIGHER; Active = true; ClipDescendants = true; }

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
		auto it = toUpdateSectorsC.find(child->uniqueID);
		if (it != toUpdateSectorsC.end()) return;

		toUpdateSectors.push_back({ child->uniqueID, child });
		toUpdateSectorsC.insert({ child->uniqueID, child });
	}

	void UpdateObjectTickState(Instance* child) {
		auto it = isTick.find(child->uniqueID);
		bool hasTick = child->hasEvent(TICK);

		if (hasTick and it == isTick.end()) {
			isTick.insert({ child->uniqueID, child });
			Tick.push_back(child);
		} else if (!hasTick and it != isTick.end()) {
			isTick.erase(it);
			for (int i = 0; i < Tick.size(); i++) {
				if (Tick[i] == child) {
					Tick.erase(Tick.begin() + i);
					break;
				}
			}
		}
	}

	Vector2 CanvasSize = { 0,0 };
	Vector2 CanvasPosition = { 0,0 };
	Vector2 CanvasSizeOFFSET = { 0,0 };
	Vector2 CanvasPositionOFFSET = { 0,0 };
	float ScrollSpeed = 0.25;
	float ScrollSpeedOFFSET = 0;
	Color SliderColor = { 15,15,15,255 };
	float SliderTransparency = 0.5;
	float SliderRoundness = 1;
	unsigned int SliderSize = 5;
	char Direction = 'Y';
	bool ScrollEnabled = true;
	bool Animated = false;

	void Draw(bool posOrSizeChanged) {
		Object2D::Draw();

		bool tempRes = posOrSizeChanged or posOrSizeChangedResult or updateWhenWillBeVisible;
		posOrSizeChangedResult = false;
		updateWhenWillBeVisible = false;

		if (ClipDescendants) {
			SIMPLEUI_GLOBAL::ClipData clip = {
				RealPos.x, RealPos.y, RealSize.x, RealSize.y, 
				Roundness, Rotation, 
				{Origin.x * RealSize.x + OriginOFFSET.x, Origin.y * RealSize.y + OriginOFFSET.y}
			};
			
			SIMPLEUI_GLOBAL::PushClip(clip);

			for (auto& [id, ptr] : toUpdateSectors) {
				if (SIMPLEUI_GLOBAL::deletedObjectsByID[id]) continue;
				secUpd(ptr);
			}

			toUpdateSectors.clear();
			toUpdateSectorsC.clear();

			checkAndUpdateCurrentSectors();

			for (ScrollSector* s : sectorsOnView) {
				for (auto& [id, ptr] : s->Objects) {
					if (SIMPLEUI_GLOBAL::deletedObjectsByID[id]) continue;
					ptr->Update(tempRes);
				}
			}

			for (Instance* s : Tick) {
				s->Update(tempRes);
			}

			SIMPLEUI_GLOBAL::PopClip();
		} else {
			for (Instance* child : Children) {
				child->Update(tempRes);
			}
		}

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

					Vector2 firstPoint = { RealPos.x + RealSize.x - SliderSize * 0.6f, sliderY };
					Vector2 secondPoint = { firstPoint.x, sliderY + sliderHeight };
					Vector2 o = {
						Origin.x * RealSize.x + OriginOFFSET.x,
						Origin.y * RealSize.y + OriginOFFSET.y
					};
					SIMPLEUI_GRAPHICS_WRAPS::DrawLineEx(firstPoint, secondPoint, SliderSize, { SliderColor.r, SliderColor.g, SliderColor.b, (unsigned char)(SliderColor.a * (1 - SliderTransparency)) }, RealPos, o, Rotation, SliderRoundness);
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

					Vector2 o = {
						  Origin.x * RealSize.x + OriginOFFSET.x,
						  Origin.y * RealSize.y + OriginOFFSET.y
					};

					Vector2 firstPoint = { sliderX, RealPos.y + RealSize.y - SliderSize * 0.6f };
					Vector2 secondPoint = { sliderX + sliderWidth, firstPoint.y };
					SIMPLEUI_GRAPHICS_WRAPS::DrawLineEx(firstPoint, secondPoint, SliderSize, { SliderColor.r, SliderColor.g, SliderColor.b, (unsigned char)(SliderColor.a * (1 - SliderTransparency)) }, RealPos, o, Rotation, SliderRoundness);
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

		if (lastVisible != Visible) {
			SIMPLEUI_GLOBAL::sceneDirty = true;
			lastVisible = Visible;
		}

		if (!Visible) {
			if (posOrSizeChanged or posOrSizeChangedResult) updateWhenWillBeVisible = true;
			return;
		}

		if (posOrSizeChanged or posOrSizeChangedResult or updateWhenWillBeVisible) {
			getRealObject2Dsize();
			getRealObject2Dposition();

			for (Instance* obj : Children) {
				obj->SetSizePosUpdateFlag();
				UpdateSectors(obj);
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
							Animate::Animation::Create(&CanvasPositionOFFSET.y, 0.125f, newY);
							Animate::Animation::Create(&CanvasPosition.y, 0.125f, newY1);
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
							Animate::Animation::Create(&CanvasPositionOFFSET.x, 0.125f, newX);
							Animate::Animation::Create(&CanvasPosition.x, 0.125f, newX1);
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
		i->toUpdateSectors.clear();
		i->toUpdateSectorsC.clear();
		i->SectorRectOnObject.clear();
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

inline Vector2 getCanvasRealPos(Object2D* obj) {
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

inline Vector2 getObject2DRS(Instance* sc) {
	if (Is2DInheritor(sc)) {
		Object2D* obj = static_cast<ScrollFrame*>(sc);
		return obj->RealSize;
	}

	return { 0,0 };
}
inline Vector2 getObject2DRP(Instance* sc) {
	if (Is2DInheritor(sc)) {
		Object2D* obj = static_cast<ScrollFrame*>(sc);
		return obj->RealPos;
	}

	return { 0,0 };
}
inline bool isScrollFrameClips(Instance* sc) {
	if (sc->Class == SCROLLFRAME) {
		ScrollFrame* scra = static_cast<ScrollFrame*>(sc);
		return scra->ClipDescendants;
	}

	return false;
}

class TextLabel : public Object2D {
	friend inline void SUI_RenderFrame(Instance*);
	constexpr static float TextTextureUpdateAspect = 1.1f;
	constexpr static float MinRasterFont = 8.0f;
	constexpr static float MaxRasterFont = 128.0f;
	constexpr static float MeasureRefFont = 32.0f;
	constexpr static const char* DefaultName = "TextLabel";
	constexpr static InstanceType DefaultClass = TEXTLABEL;

	std::string visibleText = "";
	int lastMaxVisible = -1;
	bool lastMaxVisibleRight = false;
	bool rebuildVisible = true;
	bool allocFailed = false;
	bool queued = false;
	AtlasTexture cachedText{};
	std::vector<int> charOffsets;

	Vector2 textSizeOnTexture{};
	Vector2 maxTextureSize{};
	Rectangle whereDrawText{};
	float rasterFont = 0.0f;
	float currentScale = 1.0f;
	Vector2 refSize{};
	int lastSpacing = 0;
	int lastTextured = false;

	int FontFaceIndex = 0;

	TexturedTextLabelData data{};

	std::vector<Color> GlyphsColor;
	bool lastPerSymbol = false;


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

	void rebuildVisibleText() {
		updateCharOffsets();

		if (MaxVisibleSymbols > 0 and MaxVisibleSymbols < (int)charOffsets.size()) {
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
			visibleText = Text;
		}

		lastPerSymbol = UsePerSymbolColor;
		lastMaxVisible = MaxVisibleSymbols;
		lastMaxVisibleRight = MaxVisibleRight;
		rebuildVisible = false;
		refSize = MeasureTextEx(getFont(FontFaceIndex), visibleText.c_str(), MeasureRefFont, Spacing);
		lastSpacing = Spacing;
	}

	float rasterTarget() const {
		if (visibleText.empty() or RealSize.x <= 0.0f or RealSize.y <= 0.0f) return 0.0f;
		if (refSize.x <= 0.0f or refSize.y <= 0.0f) return 0.0f;
		float fit = MeasureRefFont * std::min(RealSize.x / refSize.x, RealSize.y / refSize.y);
		if (TextSize > 0) fit = std::min(fit, (float)TextSize);
		return std::clamp(std::floor(fit), (Textured ? MinRasterFont : 1), (Textured ? MaxRasterFont : 1024));
	}

	void updateLayout() {
		if (rasterFont <= 0.0f or textSizeOnTexture.x <= 0.0f or textSizeOnTexture.y <= 0.0f) {
			whereDrawText = {};
			currentScale = 1.0f;
			return;
		}

		float scale = std::min(RealSize.x / textSizeOnTexture.x, RealSize.y / textSizeOnTexture.y);
		if (TextSize > 0) scale = std::min(scale, TextSize / rasterFont);
		currentScale = scale;

		Vector2 f = getTextOffset(TextAnchor);
		float w = textSizeOnTexture.x * scale;
		float h = textSizeOnTexture.y * scale;
		whereDrawText = { (RealSize.x - w) * f.x, (RealSize.y - h) * f.y, w, h };
	}

	void updateTexture() {
		queued = false;
		rasterFont = rasterTarget();
		if (rasterFont <= 0.0f) {
			textSizeOnTexture = {};
			return;
		}
		textSizeOnTexture = MeasureTextEx(getFont(FontFaceIndex), visibleText.c_str(), rasterFont, Spacing);

		bool noTexture = cachedText.id == 0 or !cachedText.currentAtlas;
		bool tooSmall = textSizeOnTexture.x > maxTextureSize.x or textSizeOnTexture.y > maxTextureSize.y;
		bool tooBig = textSizeOnTexture.x * TextTextureUpdateAspect * 2.0f < maxTextureSize.x and textSizeOnTexture.y * TextTextureUpdateAspect * 2.0f < maxTextureSize.y;

		if (noTexture or tooSmall or tooBig) {
			if (cachedText.id != 0) {
				UnloadTextureFromAtlas(cachedText);
				cachedText = {};
			}
			maxTextureSize = {};

			if (Text.size()) {
				float w = std::ceil(textSizeOnTexture.x * TextTextureUpdateAspect);
				float h = std::ceil(textSizeOnTexture.y * TextTextureUpdateAspect);
				cachedText = LoadRenderTextureOnAtlas(w, h);
				if (cachedText.id == 0 or !cachedText.currentAtlas) {
					allocFailed = true;
				} else {
					maxTextureSize = { w, h };
				}
			}
		}

		if (cachedText.id and cachedText.currentAtlas) {
			SIMPLEUI_GRAPHICS_WRAPS::StopClipping();

			SIMPLEUI_GRAPHICS_WRAPS::BeginTextureMode(cachedText.currentAtlas->renderTexture());
			cachedText.currentAtlas->blankArea(cachedText);
			SIMPLEUI_GRAPHICS_WRAPS::DrawTextEx(getFont(FontFaceIndex), visibleText.c_str(), { cachedText.position.x, cachedText.position.y }, rasterFont, Spacing, { 255,255,255,255 }, ((GlyphsColor.empty() or !UsePerSymbolColor ? nullptr : &GlyphsColor)));
			SIMPLEUI_GRAPHICS_WRAPS::EndTextureMode();

			SIMPLEUI_GRAPHICS_WRAPS::ResumeClipping();
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
	bool RoundText = true; // Cropping text which pixels placed out of rounded border
	bool Textured = false; // Text will bake into texture and texture will be drawn on FB. Textured better in static scenes (uses more VRAM). Always true if EXCLUDE_SIMPLEUI_FREETYPE defined
	bool UsePerSymbolColor = false;

	void SetPerSymbolColor(const std::vector<Color>& c) { // Set different color for every symbol. Requires FreeType
		GlyphsColor = c;
		if (Textured) {
			rebuildVisible = true;
		}
	}

	void ClearPerSymbolColor() {
		GlyphsColor.clear();
		if (Textured) {
			rebuildVisible = true;
		}
	}

	void Draw() override {
		if (Visible) {
			Object2D::Draw();

			Rectangle b = GetRotatedBounds();
			if (b.x + b.width + BorderThickness < 0
				or b.x - BorderThickness > SIMPLEUI_GLOBAL::winWidth
				or b.y + b.height + BorderThickness < 0
				or b.y - BorderThickness > SIMPLEUI_GLOBAL::winHeight) {
				return;
			}

			#ifdef EXCLUDE_SIMPLEUI_FREETYPE
				Textured = true;
			#endif

			if (!Textured) {
				textSizeOnTexture = refSize;
			}

			Vector2 o = {
				Origin.x * RealSize.x + OriginOFFSET.x,
				Origin.y * RealSize.y + OriginOFFSET.y
			};

			bool dirty = Text.isChanged() or FontFace.isChanged();

			if (FontFace.isChanged()) {
				FontFaceIndex = getFontIndex(FontFace);
			}

			Text.restate();
			FontFace.restate();

			updateLayout();

			if (dirty) {
				rebuildVisible = true;
				allocFailed = false;
			}

			if (lastMaxVisible != MaxVisibleSymbols or lastMaxVisibleRight != MaxVisibleRight or lastSpacing != Spacing or (Textured and lastTextured != Textured) or lastPerSymbol != UsePerSymbolColor) {
				rebuildVisible = true;
			}

			if (Textured) {
				if (allocFailed and rasterTarget() != rasterFont) allocFailed = false;

				bool hasTexture = cachedText.id != 0 and cachedText.currentAtlas;
				bool needRaster = rebuildVisible;
				if (!needRaster and !hasTexture and !allocFailed and Text.size() and rasterTarget() > 0.0f) needRaster = true;
				if (!needRaster and hasTexture and rasterFont > 0.0f and (currentScale > TextTextureUpdateAspect or currentScale < 0.5f) and rasterTarget() != rasterFont) needRaster = true;

				if (needRaster and !queued) {
					if (rebuildVisible) rebuildVisibleText();
					queued = true;
					SIMPLEUI_GLOBAL::TextLabelsToUpdateTexture.push_back(this);
				}

				if (rasterFont > 1 and cachedText.id != 0) {
					Rectangle sourceRec = { 0.0f, 0.0f, textSizeOnTexture.x, textSizeOnTexture.y };
					Rectangle destRec = { std::floorf(RealPos.x + whereDrawText.x), std::floorf(RealPos.y + whereDrawText.y), whereDrawText.width, whereDrawText.height };

					SIMPLEUI_GRAPHICS_WRAPS::DrawTexturePro(cachedText, RealPos, RealSize, sourceRec, destRec, o, Rotation, { TextColor.r, TextColor.g, TextColor.b, (unsigned char)(TextColor.a * (1 - TextTransparency)) }, (RoundText ? Roundness : 0));
				} else {
					rebuildVisible = true;
				}
			} else {
				if (rebuildVisible or rasterFont < 1) rebuildVisibleText();
				rasterFont = rasterTarget();
				data.Origin = o;
				data.Rotation = Rotation;
				data.RealPos = RealPos;
				data.RealSize = RealSize;
				data.Roundness = Roundness;

				Rectangle destRec = { std::floorf(RealPos.x + whereDrawText.x), std::floorf(RealPos.y + whereDrawText.y), whereDrawText.width, whereDrawText.height };
				if (rasterFont > 1) {
					SIMPLEUI_GRAPHICS_WRAPS::DrawTextEx(getFont(FontFaceIndex), visibleText.c_str(), { destRec.x, destRec.y }, rasterFont, Spacing, TextColor, (GlyphsColor.empty() or !UsePerSymbolColor ? nullptr : &GlyphsColor), &data);
				}
			}

			lastTextured = Textured;
		}
	}

	TextLabel* Clone() const override {
		TextLabel* i = new TextLabel(*this);
		i->UpdateAllVectorPointers();
		i->posOrSizeChangedResult = true;

		i->basicCloneOperation(const_cast<TextLabel*>(this));

		i->cachedText = {};
		i->maxTextureSize = {};
		i->rebuildVisible = true;
		i->allocFailed = false;
		i->textSizeOnTexture={0,0};
		SIMPLEUI_GLOBAL::TextLabelsToUpdateTexture.push_back(i);
		i->queued = true;

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
	friend inline void SUI_RenderFrame(Instance*);
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
	Vector2 newSize{};
	Vector2 lastRealSize{};
	Vector3 lastParams = Vector3{};
	char lastHideText = '\0';
	Vector2 lastNewSize{};
	TextBoxType lastType = TextBoxType::TEXTBOX_RESIZING;
	int lastCursorIndex = -1;
	int FontFaceIndex = 0;

	std::vector<Color> GlyphsColor;
	bool lastPerSymbol = false;
	bool changedGlyphs = false;

	std::string visibleText = "";

	void updateTextParams() {
		if (Type != TextBoxType::TEXTBOX_RESIZING) {
			textParams.y = 0;
			textParams.x = 0;
			textParams.z = getTextCFrame("A", getFont(FontFaceIndex), { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize, Spacing).z;
		} else {
			if (Text != "") {
				textParams = getTextCFrame(Text.c_str(), getFont(FontFaceIndex), { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize, Spacing);
			} else {
				textParams = getTextCFrame(PlaceholderText.c_str(), getFont(FontFaceIndex), { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize, Spacing);
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
		changedGlyphs = false;
		lastPerSymbol = UsePerSymbolColor;

		if (Text != "") {
			newSize = MeasureTextEx(getFont(FontFaceIndex), Text.c_str(), textParams.z, Spacing);
		} else {
			if (CursorIndex == -1 or SIMPLEUI_GLOBAL::FocusedTextBox != this) {
				newSize = MeasureTextEx(getFont(FontFaceIndex), PlaceholderText.c_str(), textParams.z, Spacing);
			}
		}

		float reqX = (Type != TextBoxType::TEXTBOX_RESIZING) ? std::max(newSize.x, RealSize.x) : newSize.x;
		float reqY = (Type != TextBoxType::TEXTBOX_RESIZING) ? std::max(newSize.y, RealSize.y) : newSize.y;

		if (lastNewSize.x < reqX or lastNewSize.y < reqY or !cachedText.currentAtlas) {
			if (cachedText.id != 0) {
				UnloadTextureFromAtlas(cachedText);
			}
			cachedText = LoadRenderTextureOnAtlas(reqX * TextTextureUpdateAspect, reqY * TextTextureUpdateAspect);
			lastNewSize = Vector2{ reqX * TextTextureUpdateAspect, reqY * TextTextureUpdateAspect };
		}

		if (!cachedText.currentAtlas) {
			std::cout << RED_ANSI << "Atlas was nullptr" << DEFAULT_ANSI << std::endl;
			return;
		}

		SIMPLEUI_GRAPHICS_WRAPS::StopClipping();

		SIMPLEUI_GRAPHICS_WRAPS::BeginTextureMode(cachedText.currentAtlas->renderTexture());
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

			SIMPLEUI_GRAPHICS_WRAPS::DrawTextEx(getFont(FontFaceIndex), t.c_str(), { cachedText.position.x,cachedText.position.y }, textParams.z, Spacing, { 255,255,255,255 }, (UsePerSymbolColor and !GlyphsColor.empty() ? &GlyphsColor : nullptr));
		} else {
			lines = 0;
			if (CursorIndex == -1 or SIMPLEUI_GLOBAL::FocusedTextBox != this) {
				SIMPLEUI_GRAPHICS_WRAPS::DrawTextEx(getFont(FontFaceIndex), PlaceholderText.c_str(), { cachedText.position.x,cachedText.position.y }, textParams.z, Spacing, { 255,255,255,255 }, (UsePerSymbolColor and !GlyphsColor.empty() ? &GlyphsColor : nullptr));
			}
		}

		SIMPLEUI_GRAPHICS_WRAPS::EndTextureMode();
		SIMPLEUI_GRAPHICS_WRAPS::ResumeClipping();
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
	float CursorRoundness = 0;
	SUI_Text Text = "";
	SUI_Text FontFace = SIMPLEUI_GLOBAL::BASIC_FONT_NAME;
	SUI_Text PlaceholderText = "PlaceholderText";
	Color PlaceholderTextColor = { 150, 150, 150, 255 };
	Color TextColor = { 0,0,0,255 };
	TextAnchorEnum TextAnchor = TextAnchorEnum::CENTER;
	int TextSize = -1;
	int MaxSymbols = -1;
	float TextTransparency = 0;
	std::string AllowedSymbols = "";
	std::string DisallowedSymbols = "";
	int Spacing = SIMPLEUI_GLOBAL::defaultSpacing;
	char HideText = '\0';
	bool ClearOnClick = false;
	TextBoxNextLine EnterInputCondition = TextBoxNextLine::TEXTBOX_NEXTLINE_ENTER;
	bool ClipboardPasteAllowed = true;
	bool ClipboardCopyAllowed = true;
	std::function<bool(const std::string&)> ClipboardPasteCondition;
	bool TextHighlightAllowed = true;
	Vector2 viewportPosition{};
	bool CanType = true;
	bool CanClick = true;
	bool UsePerSymbolColor = false;

	void SetPerSymbolColor(const std::vector<Color>& c) { // Set different color for every symbol. Requires FreeType
		GlyphsColor = c;
		changedGlyphs = true;
	}

	void ClearPerSymbolColor() {
		GlyphsColor.clear();
		changedGlyphs = true;
	}

	int CursorSize = 3;
	TextBoxType Type = TextBoxType::TEXTBOX_RESIZING;

	void Draw() override {
		if (!Visible) return;

		Object2D::Draw();

		Rectangle b = GetRotatedBounds();
		if (b.x + b.width + BorderThickness < 0
			or b.x - BorderThickness > SIMPLEUI_GLOBAL::winWidth
			or b.y + b.height + BorderThickness < 0
			or b.y - BorderThickness > SIMPLEUI_GLOBAL::winHeight) {
			return;
		}

		bool updateCondition1 = PlaceholderText.isChanged() or FontFace.isChanged() or Text.isChanged();
		bool updateCondition2 = lastType != Type or cachedText.id == 0 or lastHideText != HideText or lastParams.z != textParams.z or ((SIMPLEUI_GLOBAL::FocusedTextBox == this and lastFocused != this) or (lastFocused == this and SIMPLEUI_GLOBAL::FocusedTextBox != this));

		if (FontFace.isChanged()) {
			FontFaceIndex = getFontIndex(FontFace);
		}

		Text.restate();
		FontFace.restate();
		PlaceholderText.restate();

		if (updateCondition1 or updateCondition2 or lastPerSymbol != UsePerSymbolColor or changedGlyphs) {
			SIMPLEUI_GLOBAL::TextBoxesToUpdateTexture.push_back(this);
		} else {
			if (lastRealSize.x != RealSize.x or lastRealSize.y != RealSize.y) {
				updateTextParams();
				if (Text == "") {
					newSize = MeasureTextEx(getFont(FontFaceIndex), PlaceholderText.c_str(), textParams.z, Spacing);
				} else {
					newSize = MeasureTextEx(getFont(FontFaceIndex), Text.c_str(), textParams.z, Spacing);
				}
			}
		}

		float viewX = (Type == TextBoxType::TEXTBOX_VIEWPORTED_X or Type == TextBoxType::TEXTBOX_VIEWPORTED_XY) ? viewportPosition.x : 0.0f;
		float viewY = (Type == TextBoxType::TEXTBOX_VIEWPORTED_Y or Type == TextBoxType::TEXTBOX_VIEWPORTED_XY) ? viewportPosition.y : 0.0f;

		if (textParams.z > 1) {
			if (cachedText.id != 0) {
				Vector2 sizeToDraw = (Type != TextBoxType::TEXTBOX_RESIZING) ? RealSize : newSize;

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

				Vector2 o = {
						Origin.x * RealSize.x + OriginOFFSET.x,
						Origin.y * RealSize.y + OriginOFFSET.y
				};

				SIMPLEUI_GRAPHICS_WRAPS::DrawTexturePro(cachedText, RealPos, RealSize, sourceRec, destRec, o, Rotation, clr, 0);
			}
		}

		if (Text.empty()) {
			if (CursorVisible and SIMPLEUI_GLOBAL::FocusedTextBox == this) {
				if (textParams.z > 1) {
					float sizeY = RealSize.y;

					Vector2 o = {
						Origin.x * RealSize.x + OriginOFFSET.x,
						Origin.y * RealSize.y + OriginOFFSET.y
					};

					SIMPLEUI_GRAPHICS_WRAPS::DrawLineEx(
						{ RealPos.x + getTextOffset(TextAnchor).x * RealSize.x - viewX, RealPos.y + textParams.y - viewY },
						{ RealPos.x + getTextOffset(TextAnchor).x * RealSize.x - viewX, RealPos.y + textParams.y + sizeY - viewY },
						CursorSize, CursorColor, RealPos, o, Rotation, CursorRoundness
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

			Vector2 size = MeasureTextEx(getFont(FontFaceIndex), textBeforeCursorOnThisLine.c_str(), textParams.z, Spacing);

			if (size.x == 0 or size.y == 0) {
				size.y = MeasureTextEx(getFont(FontFaceIndex), "A", textParams.z, Spacing).y;
				if (size.y == 0) size.y = textParams.z;
			}

			float yOffset = 0.0f;
			if (currentLine > 0) {
				std::string newlinesStr(currentLine, '\n');
				float totalH = MeasureTextEx(getFont(FontFaceIndex), newlinesStr.c_str(), textParams.z, Spacing).y;
				float singleH = MeasureTextEx(getFont(FontFaceIndex), "A", textParams.z, Spacing).y;
				yOffset = totalH - singleH;
			}

			Vector2 o = {
				Origin.x * RealSize.x + OriginOFFSET.x,
				Origin.y * RealSize.y + OriginOFFSET.y
			};

			SIMPLEUI_GRAPHICS_WRAPS::DrawLineEx(
				{ RealPos.x + textParams.x + size.x - viewX, RealPos.y + textParams.y + yOffset - viewY },
				{ RealPos.x + textParams.x + size.x - viewX, RealPos.y + textParams.y + yOffset + size.y - viewY },
				CursorSize, CursorColor, RealPos, o, Rotation, CursorRoundness
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

				//updateTextParams();
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

				Vector2 o = {
					Origin.x * RealSize.x + OriginOFFSET.x,
					Origin.y * RealSize.y + OriginOFFSET.y
				};

				float rad = -Rotation * DEG2RAD;
				float cs = cosf(rad);
				float sn = sinf(rad);
				float px = RealPos.x + o.x;
				float py = RealPos.y + o.y;
				float mdx = SIMPLEUI_GLOBAL::mousePosition.x - px;
				float mdy = SIMPLEUI_GLOBAL::mousePosition.y - py;
				Vector2 localMouse = { px + mdx * cs - mdy * sn, py + mdx * sn + mdy * cs };

				float textStartX = RealPos.x + textParams.x;
				float textStartY = RealPos.y + textParams.y;
				float clickX = localMouse.x - textStartX + viewX;
				float clickY = localMouse.y - textStartY + viewY;

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
							float widthCurr = MeasureTextEx(getFont(FontFaceIndex), Text.substr(byteStart, currentByte - byteStart).c_str(), textParams.z, Spacing).x;

							int prevByte = (i > startIdx) ? charOffsets[i - 1] : byteStart;
							float widthPrev = (i > startIdx) ? MeasureTextEx(getFont(FontFaceIndex), Text.substr(byteStart, prevByte - byteStart).c_str(), textParams.z, Spacing).x : 0.0f;

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
			if (MaxSymbols >= charOffsets.size() or MaxSymbols < 0) {
				int symbolsLeft = MaxSymbols - static_cast<int>(charOffsets.size());
				int addedSymbols = 0;
				std::string buf;

				int key = GetCharPressed();
				while (key > 0) {
					if (symbolsLeft > 0 or MaxSymbols < 0) {
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
				int symbolsLeft = MaxSymbols - static_cast<int>(charOffsets.size());

				if (symbolsLeft > 0 or MaxSymbols < 0) {
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

			if (EnterInputCondition != TextBoxNextLine::TEXTBOX_NEXTLINE_NOT_ALLOWED and (MaxSymbols < charOffsets.size() or MaxSymbols < 0)) {
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

				float currentX = MeasureTextEx(getFont(FontFaceIndex), textBeforeCursorOnLine.c_str(), textParams.z, Spacing).x;

				int left = charI1;
				int right = (charI > 0) ? charI - 1 : charI1;
				int targetCharI = left;

				while (left <= right) {
					int mid = left + (right - left) / 2;
					std::string prefix = Text.substr(s1, charOffsets[mid] - s1);
					float midX = MeasureTextEx(getFont(FontFaceIndex), prefix.c_str(), textParams.z, Spacing).x;

					if (midX <= currentX) {
						targetCharI = mid;
						left = mid + 1;
					} else {
						right = mid - 1;
					}
				}

				if (targetCharI < ((charI > 0) ? charI - 1 : charI1)) {
					std::string prefix1 = Text.substr(s1, charOffsets[targetCharI] - s1);
					float x1 = MeasureTextEx(getFont(FontFaceIndex), prefix1.c_str(), textParams.z, Spacing).x;

					std::string prefix2 = Text.substr(s1, charOffsets[targetCharI + 1] - s1);
					float x2 = MeasureTextEx(getFont(FontFaceIndex), prefix2.c_str(), textParams.z, Spacing).x;

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
				float currentX = MeasureTextEx(getFont(FontFaceIndex), textBeforeCursorOnLine.c_str(), textParams.z, Spacing).x;

				int left = charI1;
				int right = charI2;
				int targetCharI = left;

				while (left <= right) {
					int mid = left + (right - left) / 2;
					std::string prefix = Text.substr(s1, charOffsets[mid] - s1);
					float midX = MeasureTextEx(getFont(FontFaceIndex), prefix.c_str(), textParams.z, Spacing).x;

					if (midX <= currentX) {
						targetCharI = mid;
						left = mid + 1;
					} else {
						right = mid - 1;
					}
				}

				if (targetCharI < charI2) {
					std::string prefix1 = Text.substr(s1, charOffsets[targetCharI] - s1);
					float x1 = MeasureTextEx(getFont(FontFaceIndex), prefix1.c_str(), textParams.z, Spacing).x;

					std::string prefix2 = Text.substr(s1, charOffsets[targetCharI + 1] - s1);
					float x2 = MeasureTextEx(getFont(FontFaceIndex), prefix2.c_str(), textParams.z, Spacing).x;

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

		if (SIMPLEUI_GLOBAL::FocusedTextBox != this) { CursorIndex = -1; CursorVisible = false; deleteText = true; }

		eventHandler();
		if (SIMPLEUI_GLOBAL::deletedObjectsByID[uniqueID]) return;

		if (lastVisible != Visible) {
			SIMPLEUI_GLOBAL::sceneDirty = true;
			lastVisible = Visible;
		}

		if (!Visible) { CursorIndex = -1; CursorVisible = false; deleteText = true; if (posOrSizeChanged or posOrSizeChangedResult) updateWhenWillBeVisible = true; return; }

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
					Vector2 textSizeY = MeasureTextEx(getFont(FontFaceIndex), textBeforeCursor.c_str(), textParams.z, Spacing);
					Vector2 textSizeX = MeasureTextEx(getFont(FontFaceIndex), textBeforeCursorOnLine.c_str(), textParams.z, Spacing);

					Vector2 textSize = { textSizeX.x, textSizeY.y };

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

		bool c = ClipDescendants;

		if (c) {
			SIMPLEUI_GLOBAL::ClipData clip = {
				RealPos.x, RealPos.y, RealSize.x, RealSize.y, 
				Roundness, Rotation, 
				{Origin.x * RealSize.x + OriginOFFSET.x, Origin.y * RealSize.y + OriginOFFSET.y}
			};
			
			SIMPLEUI_GLOBAL::PushClip(clip);
		}

		for (int i = 0; i < Children.size(); i++) {
			Instance* child = Children[i];
			child->Update(tempRes);
		}

		if (c) SIMPLEUI_GLOBAL::PopClip();
	};

	size_t size() {
		updateCharOffsets();
		return charOffsets.size();
	}

	TextBox* Clone() const override {
		TextBox* i = new TextBox(*this);
		i->UpdateAllVectorPointers();
		i->posOrSizeChangedResult = true;

		i->basicCloneOperation(const_cast<TextBox*>(this));

		i->cachedText.id = 0;
		i->cachedText.currentAtlas = nullptr;
		SIMPLEUI_GLOBAL::TextBoxesToUpdateTexture.push_back(i);

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
		if (imageIfMemory.data) RAYLIB_FUNCTIONAL::UnloadImage(imageIfMemory);
	}
public:
	ImageOverlayFormat Overlay = ImageOverlayFormat::IMAGE_FIT;
	float ImageTransparency = 0.0f;
	Color ImageColor = { 255,255,255,255 };
	bool RoundImage = false;

	void setImage(const std::string& name = "") {
		if (imageIfMemory.data) {
			RAYLIB_FUNCTIONAL::UnloadImage(imageIfMemory);
			imageIfMemory = Image{};
			UnloadTextureFromAtlas(tex);
		}

		auto pair = getImage(name);
		tex = pair.second;
		currentPair = name;
	}

	void Draw() override {
		if (!Visible) return;

		Object2D::Draw();

		Rectangle b = GetRotatedBounds();
		if (b.x + b.width + BorderThickness < 0
			or b.x - BorderThickness > SIMPLEUI_GLOBAL::winWidth
			or b.y + b.height + BorderThickness < 0
			or b.y - BorderThickness > SIMPLEUI_GLOBAL::winHeight) {
			return;
		}

		updateTexture();

		if (tex.id) {
			Rectangle destRec = { RealPos.x, RealPos.y, RealSize.x, RealSize.y };
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

			SIMPLEUI_GRAPHICS_WRAPS::DrawTexturePro(tex, RealPos, RealSize, srcRec, destRec, { OriginOFFSET.x + Origin.x * RealSize.x, OriginOFFSET.y + Origin.y * RealSize.y }, Rotation, { ImageColor.r, ImageColor.g, ImageColor.b, (unsigned char)(ImageColor.a * (1 - ImageTransparency)) }, (RoundImage ? Roundness : 0));
		} else {
			if (currentPair == "" or imageIfMemory.data) return;
			setImage(currentPair);
		}
	}

	void UpdateImageFromMemory(const std::string& type, const std::vector<unsigned char>& data) {
		if (imageIfMemory.data) {
			RAYLIB_FUNCTIONAL::UnloadImage(imageIfMemory);
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
			if (texture.id != 0) RAYLIB_FUNCTIONAL::UnloadTexture(texture);

			Image img = RAYLIB_FUNCTIONAL::GenImageColor(w, h, BLANK);
			texture = RAYLIB_FUNCTIONAL::LoadTextureFromImage(img);
			RAYLIB_FUNCTIONAL::UnloadImage(img);
		}
	}
protected:
	TextureLabel(bool a) : Object2D(a) { Name = DefaultName; Class = DefaultClass; };
	TextureLabel(Instance* p) : Object2D(p) { Name = DefaultName; Class = DefaultClass; }

	TextureLabel() = delete;

	~TextureLabel() override {
		if (texture.id != 0 and owner) RAYLIB_FUNCTIONAL::UnloadTexture(texture);
	}
public:
	Color TextureColor = { 255,255,255,255 };
	bool RoundTexture = false;

	void Draw() override {
		if (Visible) {
			Object2D::Draw();

			if (imageLoadedWhileNotReady) {
				imageLoadedWhileNotReady = false;

				if (img.data != nullptr) {
					if (texture.id != 0 and owner) RAYLIB_FUNCTIONAL::UnloadTexture(texture);

					owner = true;
					texture = RAYLIB_FUNCTIONAL::LoadTextureFromImage(img);
					RAYLIB_FUNCTIONAL::SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
					RAYLIB_FUNCTIONAL::UnloadImage(img);
				}
			}

			Rectangle b = GetRotatedBounds();
			if (b.x + b.width + BorderThickness < 0
				or b.x - BorderThickness > SIMPLEUI_GLOBAL::winWidth
				or b.y + b.height + BorderThickness < 0
				or b.y - BorderThickness > SIMPLEUI_GLOBAL::winHeight) {
				return;
			}

			if (texture.id == 0) {
				return;
			}

			SIMPLEUI_GRAPHICS_WRAPS::DrawTexturePro(texture, RealPos, RealSize, { 0,0,(float)texture.width,(float)texture.height }, { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, { Origin.x * RealSize.x + OriginOFFSET.x, Origin.y * RealSize.y + OriginOFFSET.y }, Rotation, TextureColor, {RoundTexture ? Roundness : 0});
		}
	}

	void UpdateWithType(const std::string& type, std::vector<unsigned char>& data) {
		if (!IsWindowReady()) {
			if (imageLoadedWhileNotReady) {
				RAYLIB_FUNCTIONAL::UnloadImage(img);
			}
		}

		img = RAYLIB_FUNCTIONAL::LoadImageFromMemory(type.c_str(), data.data(), data.size());

		if (img.data == nullptr) return;
		if (texture.id != 0 and owner) RAYLIB_FUNCTIONAL::UnloadTexture(texture);

		if (IsWindowReady()) {
			imageLoadedWhileNotReady = false;

			owner = true;
			texture = RAYLIB_FUNCTIONAL::LoadTextureFromImage(img);
			RAYLIB_FUNCTIONAL::GenTextureMipmaps(&texture);
			RAYLIB_FUNCTIONAL::SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
			RAYLIB_FUNCTIONAL::UnloadImage(img);
		} else {
			imageLoadedWhileNotReady = true;
		}
	}

	void UpdateData(std::vector<char>& data, int w, int h) {
		SetSize(w, h);
		RAYLIB_FUNCTIONAL::UpdateTexture(texture, data.data());
		owner = true;
	}

	TextureLabel* Clone() const override {
		TextureLabel* i = new TextureLabel(*this);
		i->UpdateAllVectorPointers();
		i->posOrSizeChangedResult = true;

		i->basicCloneOperation(const_cast<TextureLabel*>(this));

		i->owner = false;
		i->texture = Texture{};

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

inline void Instance::AddEvent(EventType t, InstanceCallback f, MouseButtonType m = MouseButtonType::MOUSE_NONE) {
	events.push_back({ t, f, m });

	Instance* asc = findFirstAncestorOfClass(SCROLLFRAME);

	if (asc) {
		static_cast<ScrollFrame*>(asc)->UpdateObjectTickState(this);
	}
}

inline void Instance::setParent(Instance* ptr) {
	if (ptr == this) return;

	SIMPLEUI_GLOBAL::sceneDirty = true;

	if (Parent and !DontSeekParent) {
		for (int i = 0; i < Parent->Children.size(); i++) {
			if (Parent->Children[i] == this) {
				Parent->Children.erase(Parent->Children.begin() + i);
				break;
			}
		}

		Parent->childsRemovedInFrame.push_back({uniqueID, this});
	}

	Parent = ptr;
	if (ptr) {
		ptr->Children.push_back(this);
		ptr->childsAddedInFrame.push_back({uniqueID, this});
		ptr->updateChildrenZIndex = true;

		Instance* asc = findFirstAncestorOfClass(SCROLLFRAME);

		if (asc) {
			static_cast<ScrollFrame*>(asc)->UpdateSectors(this);
		}
	}
}

inline void Delete(Instance* ptr) {
	if (!ptr) return;
	if (ptr == GetRoot()) {
		std::cout << YELLOW_ANSI << "Root object has resistance from deleting" << DEFAULT_ANSI << std::endl;
		return;
	}

	SIMPLEUI_GLOBAL::sceneDirty = true;

	auto it = Animate::ActiveSafeAnimationsLinks.find(ptr);
	if (it != Animate::ActiveSafeAnimationsLinks.end()) {
		while (it->second.size()) {
			Animate::deleteCurrent(it->second[0]);
		}

		Animate::ActiveSafeAnimationsLinks.erase(ptr);
	}

	auto it2 = SIMPLEUI_GLOBAL::SafeActiveSignals.find(ptr);
	if (it2 != SIMPLEUI_GLOBAL::SafeActiveSignals.end()) {
		for (auto sig : it2->second) {
			delete sig;
		}

		SIMPLEUI_GLOBAL::SafeActiveSignals.erase(ptr);
	}

	SIMPLEUI_GLOBAL::deletedObjectsByID[ptr->uniqueID] = 1;

	if (ptr->Parent and !ptr->DontSeekParent) {
		ptr->Parent->childsRemovedInFrame.push_back({ptr->uniqueID, ptr});

		Instance* scrollChild = (ptr->Parent->Class == SCROLLFRAME ? ptr : getAncestorWhichParentIsScrollFrame(ptr));

		if (scrollChild) {
			static_cast<ScrollFrame*>(scrollChild->Parent)->UpdateSectors(scrollChild);
		}

		for (int i = 0; i < ptr->Parent->Children.size(); i++) {
			if (ptr->Parent->Children[i] == ptr) {
				ptr->Parent->Children.erase(ptr->Parent->Children.begin() + i);
				break;
			}
		}
	}

	ptr->setParent(nullptr);
	ptr->deleteAllChildren();

	if (ptr == SIMPLEUI_GLOBAL::FocusedTextBox) SIMPLEUI_GLOBAL::FocusedTextBox = nullptr;
	if (ptr == SIMPLEUI_GLOBAL::higherObject) SIMPLEUI_GLOBAL::higherObject = nullptr;

	SIMPLEUI_GLOBAL::WillDelete.push_back(ptr);
}

inline void Instance::deleteAllChildren() {
	if (!DontSeekParent and Parent) {
		Instance* scrollChild = (this->Parent->Class == SCROLLFRAME ? this : getAncestorWhichParentIsScrollFrame(this));

		if (scrollChild) {
			static_cast<ScrollFrame*>(scrollChild->Parent)->UpdateSectors(scrollChild);
		}
	}

	for (int i = 0; i < Children.size(); i++) {
		Children[i]->DontSeekParent = true;
		childsRemovedInFrame.push_back({ Children[i]->uniqueID, Children[i] });
		Delete(Children[i]);
	}

	Children.clear();

	if (Class == SCROLLFRAME) {
		for (auto& [c1, layer] : static_cast<ScrollFrame*>(this)->Grid) {
			for (auto& [c2, sec] : layer) {
				delete sec;
			}
		}

		static_cast<ScrollFrame*>(this)->Grid.clear();
		static_cast<ScrollFrame*>(this)->SectorsOnObject.clear();
		static_cast<ScrollFrame*>(this)->Tick.clear();
		static_cast<ScrollFrame*>(this)->isTick.clear();
		static_cast<ScrollFrame*>(this)->sectorsOnView.clear();
		static_cast<ScrollFrame*>(this)->toUpdateSectors.clear();
		static_cast<ScrollFrame*>(this)->toUpdateSectorsC.clear();
	}
}

inline Instance::Instance(Instance* p) : Parent(p), uniqueID(SIMPLEUI_GLOBAL::currentUniqueObjectID++) {
	SIMPLEUI_GLOBAL::sceneDirty = true;
	SIMPLEUI_GLOBAL::deletedObjectsByID.push_back(0);

	if (p) {
		p->Children.push_back(this);
		p->childsAddedInFrame.push_back({uniqueID, this});
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

	Image background = RAYLIB_FUNCTIONAL::GenImageColor(img.width, img.height, WHITE);

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

	RAYLIB_FUNCTIONAL::UnloadImage(img);
	RAYLIB_FUNCTIONAL::UnloadImage(background);

	return outBytes;
}

inline void DrawFrame(Instance* StartInstance) {
	SIMPLEUI_GLOBAL::sceneDirty = false;

	RAYLIB_FUNCTIONAL::BeginDrawing();
	RAYLIB_FUNCTIONAL::ClearBackground(SIMPLEUI_GLOBAL::WindowColor);
	StartInstance->Update(SIMPLEUI_GLOBAL::windowSizeChanged);
	FlushRectanglesBatch();
	RAYLIB_FUNCTIONAL::EndDrawing();
}

#ifndef EXCLUDE_SIMPLEUI_EXTENSION
#include <SUIextension.h>
#endif

inline namespace SIMPLEUI_DEBUG {
	inline bool fpsVisible = false;
	inline TextLabel* labelFPS = nullptr;
	inline Object2D* background = nullptr;

#ifndef EXCLUDE_SIMPLEUI_EXTENSION
	inline GraphBuilder* msGRAPH = nullptr;
	inline size_t msSEQ = -1;
#endif

	inline void toggleFPS() {
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

		if (!background) {
			background = Object2D::New(GetRoot());
			background->BackgroundTransparency = 0.3;
			background->BackgroundColor = { 30, 30, 30, 255 };
			background->BorderColor = { 40, 40, 40, 255 };
			background->BorderTransparency = 0.5;
			background->BorderThickness = 2;
			background->Name = "Frametime debug";
			background->Active = false;

			float Y = 0.3;
#ifdef EXCLUDE_SIMPLEUI_EXTENSION
			Y = 0.05;
#endif

			background->Size = { 0.2, Y };
			background->Position = { 0.8, 0 };
			background->PositionOFFSET = { -3, 3 };
			background->ZIndex = 10000000;
			background->Visible = false;
			background->Roundness = 0.075;
		}

		if (!labelFPS and background) {
			labelFPS = TextLabel::New(background);
			labelFPS->BackgroundTransparency = 0.9;
			labelFPS->BackgroundColor = { 0, 0, 0, 255 };
			labelFPS->TextSize = -1;
			labelFPS->Name = "FPS label";
			labelFPS->Active = false;

			float Y = 0.15;
#ifdef EXCLUDE_SIMPLEUI_EXTENSION
			Y = 1;
#endif

			labelFPS->Size = { 1, Y };
			labelFPS->Roundness = 0.3;

			ChangedSignal<long>::New(SIMPLEUI_GLOBAL::accurateFPS, [upd]() {
				static int last = 0;
				if (last != SIMPLEUI_GLOBAL::accurateFPS or last == 0) {
					upd();
				}
			});
		}

#ifndef EXCLUDE_SIMPLEUI_EXTENSION
		if (!msGRAPH and background) {
			msGRAPH = GraphBuilder::New(background);
			msGRAPH->Size = { 0.9, 0.78 };
			msGRAPH->Position = { 0.05, 0.2 };
			msGRAPH->BackgroundTransparency = 0.9;
			msGRAPH->BackgroundColor = { 0, 0, 0, 255 };
			msGRAPH->Roundness = 0.1;
			msGRAPH->Name = "Frametime graph";
			msGRAPH->IndependentValuesX = true;
			msSEQ = msGRAPH->createSequence("s");
			msGRAPH->setSequenceThickness(msSEQ, 2);
			msGRAPH->setSequenceColor(msSEQ, {190, 190, 190, 255});
			msGRAPH->minimalValueToTextFunction([](long double value) {
				char buf[32];
				std::snprintf(buf, sizeof(buf), "%.2Lf", value * 1000);
				std::string s = buf;
				return s + " ms ";
			});
			msGRAPH->maximalValueToTextFunction([](long double value) { 
				char buf[32];
				std::snprintf(buf, sizeof(buf), "%.2Lf", value * 1000);
				std::string s = buf;
				return s + " ms ";
			});
			msGRAPH->SizeOfLeftInfo = { 0, 0.3 };
			msGRAPH->TextColor = { 190, 190, 190, 255 };

			size_t seq = msGRAPH->createSequence("s");
			msGRAPH->setSequenceThickness(seq, 2);
			msGRAPH->setSequenceColor(seq, { 170, 0, 0, 255 });
			msGRAPH->addValueToSequence(seq, 0.017);
			msGRAPH->addValueToSequence(seq, 0.017);
		}
#endif

		upd();

		if (background) {
			background->Visible = !background->Visible;
			fpsVisible = background->Visible;
		}
	}


	inline std::vector<double> msBuffer;
	inline double msAccum = 0.0;
	inline constexpr double msFlushInterval = 0.1;
	inline constexpr size_t msMaxPoints = 1000;

	inline void updateGraph() {
#ifndef EXCLUDE_SIMPLEUI_EXTENSION
		if (!msGRAPH or !msGRAPH->Visible) {
			msBuffer.clear();
			msAccum = 0.0;
			return;
		}

		msBuffer.push_back(SIMPLEUI_GLOBAL::dt);
		msAccum += SIMPLEUI_GLOBAL::dt;

		if (msAccum < msFlushInterval) return;

		size_t current = msGRAPH->getSequenceValues(msSEQ).size();
		size_t incoming = std::min(msBuffer.size(), msMaxPoints);
		size_t skip = msBuffer.size() - incoming;

		size_t overflow = (current + incoming > msMaxPoints) ? current + incoming - msMaxPoints : 0;
		for (size_t i = 0; i < overflow; i++) {
			msGRAPH->removeIndexFromSequence(msSEQ, 0);
		}

		for (size_t i = skip; i < msBuffer.size(); i++) {
			msGRAPH->addValueToSequence(msSEQ, msBuffer[i]);
		}

		msBuffer.clear();
		msAccum = 0.0;
#endif
	}

	inline void toggleFrameTimeGraph() {
		if (!SIMPLEUI_GLOBAL::ALLOW_DEBUG) return;
#ifndef EXCLUDE_SIMPLEUI_EXTENSION
		toggleFPS();
		if (msGRAPH) {
			msGRAPH->Visible = !msGRAPH->Visible;

			if (labelFPS) {
				labelFPS->Size.y = msGRAPH->Visible ? 0.15 : 1;
			}

			if (background) {
				background->Size.y = msGRAPH->Visible ? 0.3 : 0.05;
			}
		}
		toggleFPS();
#endif
	}

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
		sas->Size = Vector2{ 1, 0.05 };
		sas->Position = Vector2{ 0, 0.05f * (n - 1) };
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

	inline void initDebug() {
		if (debugMenu) return;
		debugMenu = Object2D::New(GetRoot());
		debugMenu->Size = Vector2{ 1,1 };
		debugMenu->BackgroundTransparency = 0.9;
		debugMenu->BackgroundColor = DefaultDebugColor;
		debugMenu->Visible = false;
		debugMenu->ZIndex = 100000;
		debugMenu->Name = "debugMenu";

		TextLabel* lowerName = TextLabel::New(debugMenu);
		lowerName->Name = "debugName";
		lowerName->Text = "(F2) Debug Menu";
		lowerName->BackgroundColor = { 0,0,0,255 };
		lowerName->TextSize = -1;
		lowerName->TextColor = DefaultDebugColor;
		lowerName->Position = Vector2{ 0.03f, 0.9f };
		lowerName->Size = Vector2{ 0.24, 0.1 };
		lowerName->TextAnchor = TextAnchorEnum::SE;
		lowerName->BackgroundTransparency = 1;
		lowerName->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;

		/************************
		*       Settings        *
		************************/

		Object2D* SettingsFrame = Object2D::New(debugMenu);
		SettingsFrame->Size = Vector2{ 0.4, 0.25 };
		SettingsFrame->Position = Vector2{ 0.04, 0.03 };
		SettingsFrame->BackgroundTransparency = 0.2;
		SettingsFrame->BorderColor = DefaultDebugColor;
		SettingsFrame->BackgroundColor = { 0,0,0,255 };
		SettingsFrame->BorderThickness = 3;
		SettingsFrame->Name = "SettingsFrame";

		TextLabel* SettingsName = TextLabel::New(SettingsFrame);
		SettingsName->Name = "SettingsName";
		SettingsName->Text = "Settings";
		SettingsName->TextSize = -1;
		SettingsName->TextColor = DefaultDebugColor;
		SettingsName->Position = Vector2{ 0.5, 0 };
		SettingsName->AnchorPosition = Vector2{ 0.5, 0 };
		SettingsName->Size = Vector2{ 0.8, 0.1 };
		SettingsName->TextAnchor = TextAnchorEnum::CENTER;
		SettingsName->BackgroundTransparency = 1;
		SettingsName->BackgroundColor = { 0,0,0,255 };
		SettingsName->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;

		TextLabel* AnimLabel = TextLabel::New(SettingsFrame);
		AnimLabel->Size = Vector2{ 0.7, 0.2 };
		AnimLabel->BackgroundTransparency = 1;
		AnimLabel->BackgroundColor = { 0,0,0,255 };
		AnimLabel->Position = Vector2{ 0, 0.1 };
		AnimLabel->Text = " Animations";
		AnimLabel->TextAnchor = TextAnchorEnum::W;
		AnimLabel->TextSize = -1;
		AnimLabel->TextColor = DefaultDebugColor;
		AnimLabel->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		AnimLabel->Name = "animLabel";

		TextLabel* AnimButton = TextLabel::New(SettingsFrame);
		AnimButton->Size = Vector2{ 0.19, 0.15 };
		AnimButton->BackgroundColor = Animations ? Color{ 204, 255, 204, 255 } : Color{ 255, 204, 204, 255 };
		AnimButton->Position = Vector2{ 0.8, 0.125 };
		AnimButton->Text = Animations ? " On " : " Off ";
		AnimButton->TextAnchor = TextAnchorEnum::W;
		AnimButton->TextSize = -1;
		AnimButton->TextColor = { 0,0,0,255 };
		AnimButton->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		AnimButton->Name = "animButton";
		AnimButton->Active = true;
		AnimButton->AddEvent(MOUSE_CLICK, [](Instance* t) {Animations = !Animations; }, MOUSE_LEFT);
		AnimButton->Roundness = 0.3;

		TextLabel* LGMlabel = TextLabel::New(SettingsFrame);
		LGMlabel->Size = Vector2{ 0.7, 0.2 };
		LGMlabel->BackgroundTransparency = 1;
		LGMlabel->BackgroundColor = { 0,0,0,255 };
		LGMlabel->Position = Vector2{ 0, 0.3 };
		LGMlabel->Text = " Low Graphics Mode";
		LGMlabel->TextAnchor = TextAnchorEnum::W;
		LGMlabel->TextSize = -1;
		LGMlabel->TextColor = DefaultDebugColor;
		LGMlabel->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		LGMlabel->Name = "LGMlabel";

		TextLabel* LGMbutton = TextLabel::New(SettingsFrame);
		LGMbutton->Size = Vector2{ 0.19, 0.15 };
		LGMbutton->BackgroundColor = lowGraphicsMode ? Color{ 204, 255, 204, 255 } : Color{ 255, 204, 204, 255 };
		LGMbutton->Position = Vector2{ 0.8, 0.325 };
		LGMbutton->Text = lowGraphicsMode ? " On " : " Off ";
		LGMbutton->TextAnchor = TextAnchorEnum::W;
		LGMbutton->TextSize = -1;
		LGMbutton->TextColor = { 0,0,0,255 };
		LGMbutton->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		LGMbutton->Name = "LGMbutton";
		LGMbutton->Active = true;
		LGMbutton->AddEvent(MOUSE_CLICK, [](Instance* t) {lowGraphicsMode = !lowGraphicsMode; }, MOUSE_LEFT);
		LGMbutton->Roundness = 0.3;

		TextLabel* FPSlabel = TextLabel::New(SettingsFrame);
		FPSlabel->Size = Vector2{ 0.65, 0.2 };
		FPSlabel->BackgroundTransparency = 1;
		FPSlabel->BackgroundColor = { 0,0,0,255 };
		FPSlabel->Position = Vector2{ 0, 0.5 };
		FPSlabel->Text = " FPS mode";
		FPSlabel->TextAnchor = TextAnchorEnum::W;
		FPSlabel->TextSize = -1;
		FPSlabel->TextColor = DefaultDebugColor;
		FPSlabel->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		FPSlabel->Name = "FPSlabel";

		Object2D* FPSframe = TextLabel::New(SettingsFrame);
		FPSframe->Size = Vector2{ 0.3, 0.2 };
		FPSframe->BackgroundTransparency = 1;
		FPSframe->BackgroundColor = { 0,0,0,255 };
		FPSframe->Roundness = 0.3;
		FPSframe->Position = Vector2{ 0.7, 0.5 };
		FPSframe->Name = "FPSlabel";

		TextLabel* FPSleft = TextLabel::New(FPSframe);
		FPSleft->Size = Vector2{ 0.25, 0.6 };
		FPSleft->BackgroundTransparency = 1;
		FPSleft->BackgroundColor = { 0,0,0,255 };
		FPSleft->Position = Vector2{ 0.0, 0.2 };
		FPSleft->Text = "<";
		FPSleft->TextAnchor = TextAnchorEnum::CENTER;
		FPSleft->TextSize = -1;
		FPSleft->TextColor = DefaultDebugColor;
		FPSleft->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		FPSleft->Name = "FPSleft";
		FPSleft->Active = true;
		FPSleft->AddEvent(MOUSE_CLICK, [](Instance* t) { currentFPSindex--; currentFPSindex += 4; currentFPSindex = currentFPSindex % 4; }, MOUSE_LEFT);

		TextLabel* FPSquantity = TextLabel::New(FPSframe);
		FPSquantity->Size = Vector2{ 0.5, 1 };
		FPSquantity->BackgroundTransparency = 1;
		FPSquantity->BackgroundColor = { 0,0,0,255 };
		FPSquantity->Position = Vector2{ 0.25, 0 };
		std::ostringstream st; st << " " << typeFPS[currentFPSindex] << " ";
		FPSquantity->Text = currentFPSindex == 2 ? "FULL" : ((currentFPSindex == 3) ? "V-SYNC" : st.str());
		FPSquantity->TextSize = -1;
		FPSquantity->TextColor = DefaultDebugColor;
		FPSquantity->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		FPSquantity->Name = "FPSquantity";

		TextLabel* FPSright = TextLabel::New(FPSframe);
		FPSright->Size = Vector2{ 0.25, 0.6 };
		FPSright->BackgroundTransparency = 1;
		FPSright->BackgroundColor = { 0,0,0,255 };
		FPSright->Position = Vector2{ 0.75, 0.2 };
		FPSright->Text = ">";
		FPSright->TextAnchor = TextAnchorEnum::CENTER;
		FPSright->TextSize = -1;
		FPSright->TextColor = DefaultDebugColor;
		FPSright->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		FPSright->Name = "FPSright";
		FPSright->Active = true;
		FPSright->AddEvent(MOUSE_CLICK, [](Instance* t) { currentFPSindex++; currentFPSindex += 4; currentFPSindex = currentFPSindex % 4; }, MOUSE_LEFT);

		TextLabel* Colorlabel = TextLabel::New(SettingsFrame);
		Colorlabel->Size = Vector2{ 0.65, 0.2 };
		Colorlabel->BackgroundTransparency = 1;
		Colorlabel->BackgroundColor = { 0,0,0,255 };
		Colorlabel->Position = Vector2{ 0, 0.7 };
		Colorlabel->Text = " Menu color";
		Colorlabel->TextAnchor = TextAnchorEnum::W;
		Colorlabel->TextSize = -1;
		Colorlabel->TextColor = DefaultDebugColor;
		Colorlabel->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		Colorlabel->Name = "Colorlabel";

		Object2D* Colorframe = TextLabel::New(SettingsFrame);
		Colorframe->Size = Vector2{ 0.3, 0.2 };
		Colorframe->BackgroundTransparency = 1;
		Colorframe->BackgroundColor = { 0,0,0,255 };
		Colorframe->Roundness = 0.3;
		Colorframe->Position = Vector2{ 0.7, 0.7 };
		Colorframe->Name = "Colorframe";

		TextLabel* Colorleft = TextLabel::New(Colorframe);
		Colorleft->Size = Vector2{ 0.25, 0.6 };
		Colorleft->BackgroundTransparency = 1;
		Colorleft->BackgroundColor = { 0,0,0,255 };
		Colorleft->Position = Vector2{ 0.0, 0.2 };
		Colorleft->Text = "<";
		Colorleft->TextAnchor = TextAnchorEnum::CENTER;
		Colorleft->TextSize = -1;
		Colorleft->TextColor = DefaultDebugColor;
		Colorleft->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		Colorleft->Name = "Colorleft";
		Colorleft->Active = true;
		Colorleft->AddEvent(MOUSE_CLICK, [](Instance* t) { currentColor--; currentColor += 9; currentColor = currentColor % 9; }, MOUSE_LEFT);

		Object2D* ColorBlock = TextLabel::New(Colorframe);
		ColorBlock->Size = Vector2{ 0.5, 0.8 };
		ColorBlock->BackgroundColor = DefaultDebugColor;
		ColorBlock->Position = Vector2{ 0.25, 0.1 };
		ColorBlock->Roundness = 0.3;
		ColorBlock->Name = "ColorBlock";

		TextLabel* Colorright = TextLabel::New(Colorframe);
		Colorright->Size = Vector2{ 0.25, 0.6 };
		Colorright->BackgroundTransparency = 1;
		Colorright->BackgroundColor = { 0,0,0,255 };
		Colorright->Position = Vector2{ 0.75, 0.2 };
		Colorright->Text = ">";
		Colorright->TextAnchor = TextAnchorEnum::CENTER;
		Colorright->TextSize = -1;
		Colorright->TextColor = DefaultDebugColor;
		Colorright->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;
		Colorright->Name = "Colorright";
		Colorright->Active = true;
		Colorright->AddEvent(MOUSE_CLICK, [](Instance* t) { currentColor++; currentColor += 9; currentColor = currentColor % 9; }, MOUSE_LEFT);

		/******************
		*       logs      *
		******************/

		Object2D* LogsFrame = Object2D::New(debugMenu);
		LogsFrame->Size = Vector2{ 0.4, 0.6 };
		LogsFrame->Position = Vector2{ 0.04, 0.3 };
		LogsFrame->BackgroundTransparency = 0.2;
		LogsFrame->BackgroundColor = { 0,0,0,255 };
		LogsFrame->BorderColor = DefaultDebugColor;
		LogsFrame->BorderThickness = 3;
		LogsFrame->Name = "LogsFrame";

		TextLabel* LogsName = TextLabel::New(LogsFrame);
		LogsName->Name = "LogsName";
		LogsName->Text = "Logs";
		LogsName->TextSize = -1;
		LogsName->TextColor = DefaultDebugColor;
		LogsName->Position = Vector2{ 0.5, 0 };
		LogsName->AnchorPosition = Vector2{ 0.5, 0 };
		LogsName->Size = Vector2{ 0.8, 0.055 };
		LogsName->TextAnchor = TextAnchorEnum::CENTER;
		LogsName->BackgroundTransparency = 1;
		LogsName->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;

		console = ScrollFrame::New(LogsFrame);
		console->BackgroundColor = { 0,0,0,255 };
		console->BackgroundTransparency = 0.1;
		console->BorderThickness = 3;
		console->BorderColor = DefaultDebugColor;
		console->Size = Vector2{ 1, 0.93 };
		console->Position = Vector2{ 0, 0.07 };
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
		treeFrame->Size = Vector2{ 0.49, 0.87 };
		treeFrame->Position = Vector2{ 0.47, 0.03 };
		treeFrame->BackgroundTransparency = 0.2;
		treeFrame->BackgroundColor = { 0,0,0,255 };
		treeFrame->BorderColor = DefaultDebugColor;
		treeFrame->BorderThickness = 3;
		treeFrame->Name = "treeFrame";
		treeFrame->Active = true;

		TextLabel* treeName = TextLabel::New(treeFrame);
		treeName->Name = "treeName";
		treeName->Text = "Objects hierarchy";
		treeName->TextSize = -1;
		treeName->TextColor = DefaultDebugColor;
		treeName->Position = Vector2{ 0.5, 0 };
		treeName->AnchorPosition = Vector2{ 0.5, 0 };
		treeName->Size = Vector2{ 0.8, 0.055 };
		treeName->TextAnchor = TextAnchorEnum::CENTER;
		treeName->BackgroundTransparency = 1;
		treeName->FontFace = SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME;

		Object2D* manageMenu = Object2D::New(treeFrame);
		manageMenu->Name = "manageMenu";
		manageMenu->Position = Vector2{ 0, 0.06 };
		manageMenu->Size = Vector2{ 1, 0.05 };
		manageMenu->BorderThickness = 3;
		manageMenu->BackgroundTransparency = 1;
		manageMenu->BorderColor = DefaultDebugColor;

		ScrollFrame* way = ScrollFrame::New(manageMenu);
		way->Name = "directory";
		way->BackgroundTransparency = 1;
		way->Position = Vector2{ 0, 0 };
		way->Size = Vector2{ 1, 1 };
		way->Direction = 'X';
		way->SliderColor = { 255,255,255,255 };

		ScrollFrame* treeScroll = ScrollFrame::New(treeFrame);
		treeScroll->Name = "treeScroll";
		treeScroll->Position = Vector2{ 0, 0.12 };
		treeScroll->Size = Vector2{ 0.5, 0.88 };
		treeScroll->BackgroundTransparency = 1;
		treeScroll->SliderColor = { 255,255,255,255 };
		treeScroll->ScrollSpeed = 0.2;

		/********************
		*  Events Handler   *
		********************/

		ChangedSignal<int>::New(currentColor, [treeScroll, way, manageMenu, treeName, LogsName, LogsFrame, lowerName, Colorright, ColorBlock, Colorleft, Colorlabel, FPSright, FPSquantity, FPSleft, FPSlabel, LGMlabel, AnimLabel, SettingsName, SettingsFrame]() {
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

		ChangedSignal<int>::New(currentFPSindex, [FPSquantity]() { SetTargetFPS(getCurrentMaxFPS()); std::ostringstream s; s << " " << typeFPS[currentFPSindex] << " "; FPSquantity->Text = currentFPSindex == 2 ? "FULL" : ((currentFPSindex == 3) ? "V-SYNC" : s.str()); });
		ChangedSignal<bool>::New(Animations, [AnimButton]() { AnimButton->BackgroundColor = Animations ? Color{ 204, 255, 204, 255 } : Color{ 255, 204, 204, 255 }; AnimButton->Text = Animations ? " On " : " Off ";});
		ChangedSignal<bool>::New(lowGraphicsMode, [LGMbutton]() { LGMbutton->BackgroundColor = lowGraphicsMode ? Color{ 204, 255, 204, 255 } : Color{ 255, 204, 204, 255 }; LGMbutton->Text = lowGraphicsMode ? " On " : " Off "; });

		ChangedSignal<Instance*>::New(currentInstance, [way, treeScroll]() {
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
					element->Position = Vector2{ (objects.size() - i - 1) * 0.25f, 0 };
					element->Size = Vector2{ 0.2, 0.9 };
					element->Text = objects[i]->Name;
					element->Active = true;

					if (i != 0) {
						TextLabel* element2 = TextLabel::New(way);
						element2->Name = ">";
						element2->BackgroundTransparency = 1;
						element2->TextColor = typeColor[currentColor];
						element2->Position = Vector2{ (objects.size() - i - 1) * 0.25f + 0.2f , 0 };
						element2->Size = Vector2{ 0.05, 0.9 };
						element2->Text = ">";
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
					element->Text = pupupupu.str();
					element->Active = true;
					element->TextAnchor = TextAnchorEnum::W;
					element->AddEvent(MOUSE_CLICK, [i, dec](Instance* t) { currentInstance = objects2[i - dec]; }, MOUSE_LEFT);
				}

				treeScroll->CanvasSize.y = (currentInstance->Children.size() - dec) * 0.05;
				treeScroll->CanvasPosition.y = 0;
			}
		});
		currentInstance = GetRoot();
	}

	inline void toggleDebug() {
		if (!debugMenu) {
			initDebug();
		}

		debugMenu->Visible = !debugMenu->Visible;
	}
};

inline void updateSignals() {
	for (auto sig : SIMPLEUI_GLOBAL::ActiveSignals) {
		sig->Update();
	}

	for (auto& [link, signals] : SIMPLEUI_GLOBAL::SafeActiveSignals) {
		for (auto sig : signals) {
			sig->Update();
		}
	}
}

inline void SUI_SetWindowSize(int newW, int newH) {
	SIMPLEUI_GLOBAL::changeWindowSize = Vector2{ (float)newW, (float)newH };
	SIMPLEUI_GLOBAL::changeWindowSizeB = true;
}

inline void SUI_SetWindowPosition(int newX, int newY) {
	SetWindowPosition(newX, newY);
}

inline void SUI_SetMinimalWindowSize(int newX, int newY) {
	SIMPLEUI_GLOBAL::windowMinimalSize = Vector2{ (float)newX, (float)newY };
}

inline void UpdateHigher(Instance* StartInstance) {
	Object2D* best = nullptr;
	int maxDepth = -1;

	std::function<bool(Instance*, int)> getTop = [&getTop, &best, &maxDepth](Instance* parent, int localDepth) -> bool {
		bool foundInThisBranch = false;

		if (parent->Class == SCROLLFRAME and static_cast<ScrollFrame*>(parent)->ClipDescendants) {
			ScrollFrame* scroll = static_cast<ScrollFrame*>(parent);

			for (auto sector : scroll->sectorsOnView) {
				Vector2 mousePosOnScroll = { 
					SIMPLEUI_GLOBAL::mousePosition.x - scroll->RealPos.x + scroll->CanvasPosition.x * scroll->RealSize.x + scroll->CanvasPositionOFFSET.x, 
					SIMPLEUI_GLOBAL::mousePosition.y - scroll->RealPos.y + scroll->CanvasPosition.y * scroll->RealSize.y + scroll->CanvasPositionOFFSET.y 
				};
				if (!(sector->X * SCROLLFRAME_GRID_SIZE <= mousePosOnScroll.x and (sector->X + 1) * SCROLLFRAME_GRID_SIZE > mousePosOnScroll.x and
					sector->Y * SCROLLFRAME_GRID_SIZE <= mousePosOnScroll.y and (sector->Y + 1) * SCROLLFRAME_GRID_SIZE > mousePosOnScroll.y)) {
					continue;
				}

				for (auto& [id, child] : sector->Objects) {
					if (child == parent) continue;
					int nextDepth = localDepth;
					bool isTarget = false;

					if (SIMPLEUI_GLOBAL::deletedObjectsByID[id]) continue;

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

struct WindowData {
	int width = 1280;
	int height = 720;
	int FramerateCap = 0; // 0 - VSYNCED to current monitor
};

inline void SetWindowIcon(const std::string& name) {
	if (IsWindowReady()) {
		auto it1 = SIMPLEUI_GLOBAL::loadedImages.find(name);
		if (it1 != SIMPLEUI_GLOBAL::loadedImages.end()) {
			RAYLIB_FUNCTIONAL::SetWindowIcon(it1->second.first);
		}
	}
}

inline bool SUI_InitNewWindow(Instance* StartInstance = nullptr, WindowData windowData = {1280, 720, 0}, const char* name = "simpleUI window", const char* iconName = "", unsigned int flags = FLAG_WINDOW_RESIZABLE) {
	if (!StartInstance and !GetRoot()) {
		std::cout << RED_ANSI << "start() requires root object and creating scene from root (use GetRoot())" << DEFAULT_ANSI << std::endl;
		return false;
	}

	SetConfigFlags(flags);

	SIMPLEUI_GLOBAL::winWidth = windowData.width;
	SIMPLEUI_GLOBAL::winHeight = windowData.height;

	InitWindow(windowData.width, windowData.height, name);

	if (!IsWindowReady()) {
		std::cout << RED_ANSI << "InitWindow failed" << DEFAULT_ANSI << std::endl;
		return false;
	}

	if (SIMPLEUI_GLOBAL::windowMinimalSize.x != 0 and SIMPLEUI_GLOBAL::windowMinimalSize.y != 0) {
		SetWindowMinSize(SIMPLEUI_GLOBAL::windowMinimalSize.x, SIMPLEUI_GLOBAL::windowMinimalSize.y);
	}

	int targetFPS = (windowData.FramerateCap <= 0) ? GetMonitorRefreshRate(GetCurrentMonitor()) : windowData.FramerateCap;
	SetTargetFPS(targetFPS);

	if (iconName and *iconName) {
		Image z = RAYLIB_FUNCTIONAL::LoadImage(iconName);
		if (z.data) {
			RAYLIB_FUNCTIONAL::SetWindowIcon(z);
			RAYLIB_FUNCTIONAL::UnloadImage(z);
		}
	} 

	SetExitKey(KEY_NULL);

	return true;
}

inline void SUI_LoadPendings() {
	CreateFont(SIMPLEUI_GLOBAL::BASIC_FONT_NAME, "Fonts/arial.ttf", 60); // Basic font 1
	CreateFont(SIMPLEUI_GLOBAL::DEBUG_MENU_FONT_NAME, "Fonts/rogFont.otf", 35); // Basic font 2
	SIMPLEUI_GLOBAL::RectangleRoundnessShader = loadNewShader("simpleUI Shaders/rectangle_roundness.vert", "simpleUI Shaders/rectangle_roundness.frag"); // Basic shader 2

	for (auto& tup : SIMPLEUI_GLOBAL::queuedFonts) {
		CreateFont(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup));
	}
	SIMPLEUI_GLOBAL::queuedFonts.clear();
	
	for (auto& tup : SIMPLEUI_GLOBAL::queuedFontsV) {
		CreateFont(std::get<0>(tup), std::get<1>(tup), std::get<2>(tup));
	}
	SIMPLEUI_GLOBAL::queuedFontsV.clear();

	for (auto& pair : SIMPLEUI_GLOBAL::pendingImages) {
		AtlasTexture tex = LoadTextureOnAtlas(pair.second);
		SIMPLEUI_GLOBAL::loadedImages.insert({ pair.first, {pair.second, tex} });
	}
	SIMPLEUI_GLOBAL::pendingImages.clear();
}

inline void SUI_RenderFrame(Instance* StartInstance) {
	if (SIMPLEUI_GLOBAL::changeWindowSizeB) {
		SetWindowSize(SIMPLEUI_GLOBAL::changeWindowSize.x, SIMPLEUI_GLOBAL::changeWindowSize.y);
		SIMPLEUI_GLOBAL::changeWindowSizeB = false;
	}

	static Vector2 previousMousePosition = {};
	SIMPLEUI_GLOBAL::mousePosition = GetMousePosition();
	SIMPLEUI_GLOBAL::mouseOnWindow = IsCursorOnScreen();

	static Vector2 previousWinSize = { -1, -1 };
	SIMPLEUI_GLOBAL::winWidth = GetScreenWidth(); SIMPLEUI_GLOBAL::winHeight = GetScreenHeight();

	if (previousWinSize.x != SIMPLEUI_GLOBAL::winWidth or previousWinSize.y != SIMPLEUI_GLOBAL::winHeight) {
		SIMPLEUI_GLOBAL::windowSizeChanged = true;
		previousWinSize = { (float)SIMPLEUI_GLOBAL::winWidth, (float)SIMPLEUI_GLOBAL::winHeight };
	}

	updateSignals();
	SIMPLEUI_GLOBAL::dt = GetFrameTime();
	Animate::UpdateAnimations(SIMPLEUI_GLOBAL::dt);
	Tasks::UpdateTasks(SIMPLEUI_GLOBAL::dt);

	static double acc = 0;
	static int frames = 0;
	acc += SIMPLEUI_GLOBAL::dt;
	frames++;
	if (acc >= 0.1) {
		SIMPLEUI_GLOBAL::accurateFPS = (long)(frames / acc + 0.5);
		acc = 0;
		frames = 0;
	}

	if ((previousMousePosition.x != SIMPLEUI_GLOBAL::mousePosition.x or previousMousePosition.y != SIMPLEUI_GLOBAL::mousePosition.y or SIMPLEUI_GLOBAL::sceneDirty)) {
		previousMousePosition = SIMPLEUI_GLOBAL::mousePosition;
		UpdateHigher(StartInstance);
	}

	if (IsKeyPressed(KEY_F1) and SIMPLEUI_GLOBAL::ALLOW_FPS) { SIMPLEUI_DEBUG::toggleFPS(); }
	if (IsKeyPressed(KEY_F2) and SIMPLEUI_GLOBAL::ALLOW_DEBUG) { SIMPLEUI_DEBUG::toggleDebug(); }
	if (IsKeyPressed(KEY_F3) and SIMPLEUI_GLOBAL::ALLOW_FPS) { std::cout << BLUE_ANSI << SIMPLEUI_GLOBAL::accurateFPS << DEFAULT_ANSI << std::endl; }
	if (IsKeyPressed(RAYLIB_FUNCTIONAL::KEY_F4) and SIMPLEUI_GLOBAL::ALLOW_FPS) { SIMPLEUI_DEBUG::toggleFrameTimeGraph(); }

	SIMPLEUI_GLOBAL::framesSinceStart += 1;

	DrawFrame(StartInstance);

	SIMPLEUI_GLOBAL::clips.clear();

	if (SIMPLEUI_DEBUG::fpsVisible) {
		SIMPLEUI_DEBUG::updateGraph();
	}

	for (TextLabel* t : SIMPLEUI_GLOBAL::TextLabelsToUpdateTexture) {
		t->updateTexture();
	}
	SIMPLEUI_GLOBAL::TextLabelsToUpdateTexture.clear();

	for (TextBox* t : SIMPLEUI_GLOBAL::TextBoxesToUpdateTexture) {
		t->updateTexture();
	}
	SIMPLEUI_GLOBAL::TextBoxesToUpdateTexture.clear();

	SIMPLEUI_GLOBAL::CollectDeadObjects();

	SIMPLEUI_GLOBAL::windowSizeChanged = false;
}

inline void SUI_CleanUp() {
	if (GetRoot()) {
		GetRoot()->deleteAllChildren();
	}

	for (auto& pair : SIMPLEUI_GLOBAL::loadedImages) {
		RAYLIB_FUNCTIONAL::UnloadImage(pair.second.first);
		UnloadTextureFromAtlas(pair.second.second);
	}
	SIMPLEUI_GLOBAL::loadedImages.clear();

	for (auto atlas : SIMPLEUI_GLOBAL::AtlasArray) {
		delete atlas;
	}
	SIMPLEUI_GLOBAL::AtlasArray.clear();

	for (auto it : SIMPLEUI_GLOBAL::Fonts) {
		RAYLIB_FUNCTIONAL::UnloadFont(it);
	}
	SIMPLEUI_GLOBAL::Fonts.clear();

	#ifndef EXCLUDE_SIMPLEUI_FREETYPE
		FT_TextManagement::Fonts.clear();
	#endif

	unloadShader(SIMPLEUI_GLOBAL::RectangleRoundnessShader);

	SIMPLEUI_GLOBAL::deletedObjectsByID.clear();
	SIMPLEUI_GLOBAL::AtlasTextureId = 1;
	SIMPLEUI_GLOBAL::currentUniqueObjectID = 1;
	SIMPLEUI_GLOBAL::framesSinceStart = 0;
}

inline void StartNewWindow(Instance* StartInstance = nullptr, WindowData windowData = {1280, 720, 0}, const char* name = "simpleUI window", const char* iconName = "", unsigned int flags = FLAG_WINDOW_RESIZABLE) {
	SetConsoleUTF8();

	bool inited = SUI_InitNewWindow(StartInstance, windowData, name, iconName, flags);

	if (!inited) {
		return;
	}

	SUI_LoadPendings();

	while (SIMPLEUI_GLOBAL::programRunning and !WindowShouldClose()) {
		SUI_RenderFrame(StartInstance);
	}

	SUI_CleanUp();

	CloseWindow();
}

inline void StartInCurrentWindow(Instance* StartInstance = nullptr) {
	SetConsoleUTF8();

	if (!IsWindowReady()) {
		std::cout << RED_ANSI << "Window not inited. Start declined" << DEFAULT_ANSI << std::endl;
		return;
	}

	SUI_LoadPendings();

	while (SIMPLEUI_GLOBAL::programRunning and !WindowShouldClose()) {
		SUI_RenderFrame(StartInstance);
	}

	SUI_CleanUp();
}