#pragma once
#include <glad/gl.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <string>
#include <stb_image.h>

namespace SIMPLEUI_CORE {

#ifndef PI
    #define PI 3.14159265358979323846f
#endif

#ifndef DEG2RAD
    #define DEG2RAD (PI/180.0f)
#endif

#ifndef RAD2DEG
    #define RAD2DEG (180.0f/PI)
#endif

enum MouseButton : int {
    MOUSE_NONE = -1,
    MOUSE_BUTTON_LEFT = 0,
    MOUSE_BUTTON_RIGHT = 1,
    MOUSE_BUTTON_MIDDLE = 2,
    MOUSE_BUTTON_COUNT = 3
};

enum ConfigFlags : unsigned int {
	FLAG_VSYNC_HINT          = 1u << 0,
	FLAG_FULLSCREEN_MODE     = 1u << 1,
	FLAG_WINDOW_RESIZABLE    = 1u << 2,
	FLAG_WINDOW_UNDECORATED  = 1u << 3,
	FLAG_WINDOW_HIDDEN       = 1u << 4,
	FLAG_WINDOW_MINIMIZED    = 1u << 5,
	FLAG_WINDOW_MAXIMIZED    = 1u << 6,
	FLAG_WINDOW_TOPMOST      = 1u << 7,
	FLAG_WINDOW_TRANSPARENT  = 1u << 8,
	FLAG_WINDOW_HIGHDPI      = 1u << 9,
	FLAG_MSAA_4X_HINT        = 1u << 10
};

enum KeyboardKey : int {
	KEY_NULL = SDL_SCANCODE_UNKNOWN,

	KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE,
	KEY_COMMA = SDL_SCANCODE_COMMA,
	KEY_MINUS = SDL_SCANCODE_MINUS,
	KEY_PERIOD = SDL_SCANCODE_PERIOD,
	KEY_SLASH = SDL_SCANCODE_SLASH,

	KEY_ZERO = SDL_SCANCODE_0,
	KEY_ONE = SDL_SCANCODE_1,
	KEY_TWO = SDL_SCANCODE_2,
	KEY_THREE = SDL_SCANCODE_3,
	KEY_FOUR = SDL_SCANCODE_4,
	KEY_FIVE = SDL_SCANCODE_5,
	KEY_SIX = SDL_SCANCODE_6,
	KEY_SEVEN = SDL_SCANCODE_7,
	KEY_EIGHT = SDL_SCANCODE_8,
	KEY_NINE = SDL_SCANCODE_9,

	KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON,
	KEY_EQUAL = SDL_SCANCODE_EQUALS,

	KEY_A = SDL_SCANCODE_A,
	KEY_B = SDL_SCANCODE_B,
	KEY_C = SDL_SCANCODE_C,
	KEY_D = SDL_SCANCODE_D,
	KEY_E = SDL_SCANCODE_E,
	KEY_F = SDL_SCANCODE_F,
	KEY_G = SDL_SCANCODE_G,
	KEY_H = SDL_SCANCODE_H,
	KEY_I = SDL_SCANCODE_I,
	KEY_J = SDL_SCANCODE_J,
	KEY_K = SDL_SCANCODE_K,
	KEY_L = SDL_SCANCODE_L,
	KEY_M = SDL_SCANCODE_M,
	KEY_N = SDL_SCANCODE_N,
	KEY_O = SDL_SCANCODE_O,
	KEY_P = SDL_SCANCODE_P,
	KEY_Q = SDL_SCANCODE_Q,
	KEY_R = SDL_SCANCODE_R,
	KEY_S = SDL_SCANCODE_S,
	KEY_T = SDL_SCANCODE_T,
	KEY_U = SDL_SCANCODE_U,
	KEY_V = SDL_SCANCODE_V,
	KEY_W = SDL_SCANCODE_W,
	KEY_X = SDL_SCANCODE_X,
	KEY_Y = SDL_SCANCODE_Y,
	KEY_Z = SDL_SCANCODE_Z,

	KEY_LEFT_BRACKET = SDL_SCANCODE_LEFTBRACKET,
	KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH,
	KEY_RIGHT_BRACKET = SDL_SCANCODE_RIGHTBRACKET,
	KEY_GRAVE = SDL_SCANCODE_GRAVE,

	KEY_ESCAPE = SDL_SCANCODE_ESCAPE,
	KEY_ENTER = SDL_SCANCODE_RETURN,
	KEY_TAB = SDL_SCANCODE_TAB,
	KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,
	KEY_INSERT = SDL_SCANCODE_INSERT,
	KEY_DELETE = SDL_SCANCODE_DELETE,

	KEY_RIGHT = SDL_SCANCODE_RIGHT,
	KEY_LEFT = SDL_SCANCODE_LEFT,
	KEY_DOWN = SDL_SCANCODE_DOWN,
	KEY_UP = SDL_SCANCODE_UP,

	KEY_PAGE_UP = SDL_SCANCODE_PAGEUP,
	KEY_PAGE_DOWN = SDL_SCANCODE_PAGEDOWN,
	KEY_HOME = SDL_SCANCODE_HOME,
	KEY_END = SDL_SCANCODE_END,

	KEY_CAPS_LOCK = SDL_SCANCODE_CAPSLOCK,
	KEY_SCROLL_LOCK = SDL_SCANCODE_SCROLLLOCK,
	KEY_NUM_LOCK = SDL_SCANCODE_NUMLOCKCLEAR,
	KEY_PRINT_SCREEN = SDL_SCANCODE_PRINTSCREEN,
	KEY_PAUSE = SDL_SCANCODE_PAUSE,

	KEY_F1 = SDL_SCANCODE_F1,
	KEY_F2 = SDL_SCANCODE_F2,
	KEY_F3 = SDL_SCANCODE_F3,
	KEY_F4 = SDL_SCANCODE_F4,
	KEY_F5 = SDL_SCANCODE_F5,
	KEY_F6 = SDL_SCANCODE_F6,
	KEY_F7 = SDL_SCANCODE_F7,
	KEY_F8 = SDL_SCANCODE_F8,
	KEY_F9 = SDL_SCANCODE_F9,
	KEY_F10 = SDL_SCANCODE_F10,
	KEY_F11 = SDL_SCANCODE_F11,
	KEY_F12 = SDL_SCANCODE_F12,
	KEY_F13 = SDL_SCANCODE_F13,
	KEY_F14 = SDL_SCANCODE_F14,
	KEY_F15 = SDL_SCANCODE_F15,
	KEY_F16 = SDL_SCANCODE_F16,
	KEY_F17 = SDL_SCANCODE_F17,
	KEY_F18 = SDL_SCANCODE_F18,
	KEY_F19 = SDL_SCANCODE_F19,
	KEY_F20 = SDL_SCANCODE_F20,
	KEY_F21 = SDL_SCANCODE_F21,
	KEY_F22 = SDL_SCANCODE_F22,
	KEY_F23 = SDL_SCANCODE_F23,
	KEY_F24 = SDL_SCANCODE_F24,

	KEY_KP_0 = SDL_SCANCODE_KP_0,
	KEY_KP_1 = SDL_SCANCODE_KP_1,
	KEY_KP_2 = SDL_SCANCODE_KP_2,
	KEY_KP_3 = SDL_SCANCODE_KP_3,
	KEY_KP_4 = SDL_SCANCODE_KP_4,
	KEY_KP_5 = SDL_SCANCODE_KP_5,
	KEY_KP_6 = SDL_SCANCODE_KP_6,
	KEY_KP_7 = SDL_SCANCODE_KP_7,
	KEY_KP_8 = SDL_SCANCODE_KP_8,
	KEY_KP_9 = SDL_SCANCODE_KP_9,

	KEY_KP_PERIOD = SDL_SCANCODE_KP_PERIOD,
	KEY_KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE,
	KEY_KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY,
	KEY_KP_MINUS = SDL_SCANCODE_KP_MINUS,
	KEY_KP_PLUS = SDL_SCANCODE_KP_PLUS,
	KEY_KP_ENTER = SDL_SCANCODE_KP_ENTER,
	KEY_KP_EQUALS = SDL_SCANCODE_KP_EQUALS,

	KEY_LEFT_CONTROL = SDL_SCANCODE_LCTRL,
	KEY_LEFT_SHIFT = SDL_SCANCODE_LSHIFT,
	KEY_LEFT_ALT = SDL_SCANCODE_LALT,
	KEY_LEFT_GUI = SDL_SCANCODE_LGUI,

    KEY_SPACE = SDL_SCANCODE_SPACE,

	KEY_RIGHT_CONTROL = SDL_SCANCODE_RCTRL,
	KEY_RIGHT_SHIFT = SDL_SCANCODE_RSHIFT,
	KEY_RIGHT_ALT = SDL_SCANCODE_RALT,
	KEY_RIGHT_GUI = SDL_SCANCODE_RGUI,

	KEY_APPLICATION = SDL_SCANCODE_APPLICATION,
	KEY_MENU = SDL_SCANCODE_MENU,
	KEY_POWER = SDL_SCANCODE_POWER,

	KEY_MUTE = SDL_SCANCODE_MUTE,
	KEY_VOLUME_UP = SDL_SCANCODE_VOLUMEUP,
	KEY_VOLUME_DOWN = SDL_SCANCODE_VOLUMEDOWN,

	KEY_AUDIO_NEXT = SDL_SCANCODE_MEDIA_NEXT_TRACK,
	KEY_AUDIO_PREV = SDL_SCANCODE_MEDIA_PREVIOUS_TRACK,
	KEY_AUDIO_STOP = SDL_SCANCODE_MEDIA_STOP,
	KEY_AUDIO_PLAY = SDL_SCANCODE_MEDIA_PLAY,

	KEY_MEDIA_SELECT = SDL_SCANCODE_MEDIA_SELECT,

	KEY_AC_SEARCH = SDL_SCANCODE_AC_SEARCH,
	KEY_AC_HOME = SDL_SCANCODE_AC_HOME,
	KEY_AC_BACK = SDL_SCANCODE_AC_BACK,
	KEY_AC_FORWARD = SDL_SCANCODE_AC_FORWARD,
	KEY_AC_STOP = SDL_SCANCODE_AC_STOP,
	KEY_AC_REFRESH = SDL_SCANCODE_AC_REFRESH,
	KEY_AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS
};

struct Vector2 { 
    float x;
    float y;
};

struct Vector3 { 
    float x;
    float y;
    float z;
};

struct Vector4 { 
    float x;
    float y;
    float z;
    float w;
};

typedef struct Matrix {
    float m0, m4, m8, m12;
    float m1, m5, m9, m13;
    float m2, m6, m10, m14;
    float m3, m7, m11, m15;
} Matrix;

struct Rectangle { 
    float x;
    float y;
    float width;
    float height;
};

struct Color { 
    uint8_t r, g, b, a; 
};

constexpr Color WHITE = { 255, 255, 255, 255 };
constexpr Color BLANK = { 0, 0, 0, 0 };

struct Image { 
    void* data; 
    int width, height; 
};

struct Texture { 
    GLuint id;
    int width, height;
    int mipmaps = 1;
};

struct RenderTexture { 
    GLuint id; 
    Texture texture; 
};

struct Shader { 
    GLuint id; 
};

enum TextureFilter { 
    FILTER_POINT,
    FILTER_BILINEAR 
};
enum TextureWrap { WRAP_REPEAT, WRAP_CLAMP };
enum BlendMode { BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED, BLEND_REPLACE, BLEND_CUSTOM_SEPARATE };
enum UniformType { UNIFORM_FLOAT, UNIFORM_VEC2, UNIFORM_VEC3, UNIFORM_VEC4, UNIFORM_INT, UNIFORM_MAT4 };

struct BlendState {
	GLenum srcRGB, dstRGB, srcA, dstA, eqRGB, eqA;
	bool enabled;
};

struct GLStateBackup {
	GLint program;
	GLint vao;
	GLint arrayBuffer;
	GLint fbo;
	GLint activeTexture;
	GLint texture2D;
	GLint viewport[4];
	GLint scissorBox[4];
	GLint blendSrcRGB;
	GLint blendDstRGB;
	GLint blendSrcAlpha;
	GLint blendDstAlpha;
	GLint blendEqRGB;
	GLint blendEqAlpha;
	GLboolean blend;
	GLboolean depthTest;
	GLboolean cullFace;
	GLboolean scissorTest;
};

struct Context {
    GLStateBackup stateBackup;
	int winW = 0, winH = 0;
	int fbW = 0, fbH = 0;
	float mvp[16] = {};
	BlendMode blend = BLEND_ALPHA;
	BlendState custom = { GL_ONE, GL_ZERO, GL_ONE, GL_ZERO, GL_FUNC_ADD, GL_FUNC_ADD, true };
	GLuint userProgram = 0;
	GLuint defaultProgram = 0;
	GLuint vao = 0, vbo = 0;
	Texture white = {};
	std::function<void()> flush = [] {};

	SDL_Window* window = nullptr;
	SDL_GLContext glContext = nullptr;
	SDL_Cursor* activeCursor = nullptr;
	int currentCursorId = -1;

	unsigned int configFlags = 0;
	bool windowReady = false;
	bool shouldClose = false;
	bool cursorOnWindow = false;

	bool mouseDown[MOUSE_BUTTON_COUNT] = {};
	bool mousePressed[MOUSE_BUTTON_COUNT] = {};
	bool mouseReleased[MOUSE_BUTTON_COUNT] = {};
	float mouseWheel = 0.0f;

	bool keyDown[SDL_SCANCODE_COUNT] = {};
	bool keyPressed[SDL_SCANCODE_COUNT] = {};
	std::deque<int> charQueue;

	std::string clipboard;
	uint64_t lastFrameTimeNS = 0;
	float frameTime = 0.0f;
	int targetFPS = 0;

    bool ownsWindow = false;
};

inline Context g;

inline void OrthoYDown(float* m, float w, float h) {
	std::memset(m, 0, 16 * sizeof(float));
	m[0] = 2.0f / w;
	m[5] = -2.0f / h;
	m[10] = -1.0f;
	m[12] = -1.0f;
	m[13] = 1.0f;
	m[15] = 1.0f;
}

inline void OrthoYUp(float* m, float w, float h) {
	std::memset(m, 0, 16 * sizeof(float));
	m[0] = 2.0f / w;
	m[5] = 2.0f / h;
	m[10] = -1.0f;
	m[12] = -1.0f;
	m[13] = -1.0f;
	m[15] = 1.0f;
}

inline Image GenImageFromBytes(const void* bytes, int w, int h, int channels) {
	Image img = { nullptr, w, h };
	size_t n = (size_t)w * h;
	uint8_t* out = (uint8_t*)std::malloc(n * 4);
	const uint8_t* in = (const uint8_t*)bytes;

	for (size_t i = 0; i < n; i++) {
		if (channels == 4) {
			std::memcpy(out + i * 4, in + i * 4, 4);
		} else if (channels == 3) {
			out[i * 4 + 0] = in[i * 3 + 0];
			out[i * 4 + 1] = in[i * 3 + 1];
			out[i * 4 + 2] = in[i * 3 + 2];
			out[i * 4 + 3] = 255;
		} else {
			out[i * 4 + 0] = out[i * 4 + 1] = out[i * 4 + 2] = in[i];
			out[i * 4 + 3] = 255;
		}
	}

	img.data = out;
	return img;
}

inline Image GenImageColor(int w, int h, Color c) {
	Image img = { std::malloc((size_t)w * h * 4), w, h };
	uint32_t px;
	std::memcpy(&px, &c, 4);
	uint32_t* p = (uint32_t*)img.data;
	for (size_t i = 0; i < (size_t)w * h; i++) p[i] = px;
	return img;
}

inline bool ImageTypeSupported(const char* t) {
	if (!t) return true;
	if (*t == '.') t++;
	char buf[8] = {};
	size_t n = std::strlen(t);
	if (n == 0 or n >= sizeof(buf)) return false;
	for (size_t i = 0; i < n; i++) buf[i] = (char)std::tolower((unsigned char)t[i]);
	static const char* ok[] = { "png", "jpg", "jpeg", "bmp", "tga", "gif", "psd", "hdr", "pic", "ppm", "pgm", "pnm" };
	for (const char* e : ok) if (std::strcmp(buf, e) == 0) return true;
	return false;
}

inline Image LoadImageFromMemory(const char* fileType, const unsigned char* fileData, int dataSize) {
	Image img = { nullptr, 0, 0 };
	if (!fileData or dataSize <= 0) return img;
	if (!ImageTypeSupported(fileType)) {
		std::fprintf(stderr, "unsupported image type: %s\n", fileType);
		return img;
	}
	int comp = 0;
	img.data = stbi_load_from_memory(fileData, dataSize, &img.width, &img.height, &comp, 4);
	if (!img.data) {
		std::fprintf(stderr, "image decode failed: %s\n", stbi_failure_reason());
		img.width = img.height = 0;
	}
	return img;
}

inline Image LoadImage(const char* fileName) {
	Image img = { nullptr, 0, 0 };
	int comp = 0;
	img.data = stbi_load(fileName, &img.width, &img.height, &comp, 4);
	if (!img.data) {
		std::fprintf(stderr, "image load failed: %s (%s)\n", fileName, stbi_failure_reason());
		img.width = img.height = 0;
	}
	return img;
}

inline Image ImageCopy(const Image& img) {
	Image ret = { nullptr, 0, 0 };
	if (!img.data or img.width <= 0 or img.height <= 0) return ret;
	size_t s = (size_t)img.width * img.height * 4;
	void* p = std::malloc(s);
	if (!p) return ret;
	std::memcpy(p, img.data, s);
	ret = { p, img.width, img.height };
	return ret;
}

inline void UnloadImage(Image& img) {
	if (img.data) stbi_image_free(img.data);
	img = { nullptr, 0, 0 };
}

inline void SetTextureFilter(const Texture& t, TextureFilter f) {
	bool mip = t.mipmaps > 1;
	GLint mn = f == FILTER_POINT ? (mip ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST) : (mip ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
	GLint mg = f == FILTER_POINT ? GL_NEAREST : GL_LINEAR;
	glTextureParameteri(t.id, GL_TEXTURE_MIN_FILTER, mn);
	glTextureParameteri(t.id, GL_TEXTURE_MAG_FILTER, mg);
}

inline int MipLevelCount(int w, int h) {
	int m = w > h ? w : h;
	int n = 1;
	while (m > 1) {
		m >>= 1;
		n++;
	}
	return n;
}

inline void GenTextureMipmaps(Texture& t) {
	if (!t.id) return;
	if (t.mipmaps > 1) {
		glGenerateTextureMipmap(t.id);
		return;
	}
	int levels = MipLevelCount(t.width, t.height);
	if (levels <= 1) return;

	GLint minF = 0, wrapS = 0, wrapT = 0;
	glGetTextureParameteriv(t.id, GL_TEXTURE_MIN_FILTER, &minF);
	glGetTextureParameteriv(t.id, GL_TEXTURE_WRAP_S, &wrapS);
	glGetTextureParameteriv(t.id, GL_TEXTURE_WRAP_T, &wrapT);
	bool point = minF == GL_NEAREST or minF == GL_NEAREST_MIPMAP_NEAREST or minF == GL_NEAREST_MIPMAP_LINEAR;

	GLuint id = 0;
	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glTextureStorage2D(id, levels, GL_RGBA8, t.width, t.height);
	glCopyImageSubData(t.id, GL_TEXTURE_2D, 0, 0, 0, 0, id, GL_TEXTURE_2D, 0, 0, 0, 0, t.width, t.height, 1);
	glDeleteTextures(1, &t.id);

	t.id = id;
	t.mipmaps = levels;
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, wrapS);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, wrapT);
	SetTextureFilter(t, point ? FILTER_POINT : FILTER_BILINEAR);
	glGenerateTextureMipmap(id);
}

inline void GenTextureMipmaps(RenderTexture& rt) {
	GenTextureMipmaps(rt.texture);
	glNamedFramebufferTexture(rt.id, GL_COLOR_ATTACHMENT0, rt.texture.id, 0);
}

inline void SetTextureWrap(const Texture& t, TextureWrap w) {
	GLint v = w == WRAP_REPEAT ? GL_REPEAT : GL_CLAMP_TO_EDGE;
	glTextureParameteri(t.id, GL_TEXTURE_WRAP_S, v);
	glTextureParameteri(t.id, GL_TEXTURE_WRAP_T, v);
}

inline Texture LoadTextureFromImage(const Image& img) {
	Texture t = { 0, img.width, img.height };
	if (!img.data or img.width <= 0 or img.height <= 0) return t;
	glCreateTextures(GL_TEXTURE_2D, 1, &t.id);
	glTextureStorage2D(t.id, 1, GL_RGBA8, img.width, img.height);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTextureSubImage2D(t.id, 0, 0, 0, img.width, img.height, GL_RGBA, GL_UNSIGNED_BYTE, img.data);
	SetTextureFilter(t, FILTER_BILINEAR);
	SetTextureWrap(t, WRAP_CLAMP);
	return t;
}

inline void UnloadTexture(Texture& t) {
	if (t.id) glDeleteTextures(1, &t.id);
	t = {};
}

inline Image LoadImageFromTexture(const Texture& t) {
	Image img = { std::malloc((size_t)t.width * t.height * 4), t.width, t.height };
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glGetTextureImage(t.id, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLsizei)((size_t)t.width * t.height * 4), img.data);
	return img;
}

inline RenderTexture LoadRenderTexture(int w, int h) {
	RenderTexture rt = {};
	rt.texture = { 0, w, h };
	glCreateTextures(GL_TEXTURE_2D, 1, &rt.texture.id);
	glTextureStorage2D(rt.texture.id, 1, GL_RGBA8, w, h);
	SetTextureFilter(rt.texture, FILTER_BILINEAR);
	SetTextureWrap(rt.texture, WRAP_CLAMP);

	glCreateFramebuffers(1, &rt.id);
	glNamedFramebufferTexture(rt.id, GL_COLOR_ATTACHMENT0, rt.texture.id, 0);

	GLenum status = glCheckNamedFramebufferStatus(rt.id, GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::fprintf(stderr, "framebuffer incomplete: 0x%x\n", status);
		glDeleteFramebuffers(1, &rt.id);
		glDeleteTextures(1, &rt.texture.id);
		return {};
	}

	GLboolean scissorWasEnabled = glIsEnabled(GL_SCISSOR_TEST);
	if (scissorWasEnabled) glDisable(GL_SCISSOR_TEST);
	const float zero[4] = { 0, 0, 0, 0 };
	glClearNamedFramebufferfv(rt.id, GL_COLOR, 0, zero);
	if (scissorWasEnabled) glEnable(GL_SCISSOR_TEST);
	return rt;
}

inline void UnloadRenderTexture(RenderTexture& rt) {
	if (rt.id) glDeleteFramebuffers(1, &rt.id);
	if (rt.texture.id) glDeleteTextures(1, &rt.texture.id);
	rt = {};
}

inline void ClearRegion(const RenderTexture& rt, Rectangle r) {
	glEnable(GL_SCISSOR_TEST);
	glScissor((GLint)r.x, (GLint)r.y, (GLsizei)r.width, (GLsizei)r.height);
	const float zero[4] = { 0, 0, 0, 0 };
	glClearNamedFramebufferfv(rt.id, GL_COLOR, 0, zero);
	glDisable(GL_SCISSOR_TEST);
}

inline BlendState BlendStateFor(BlendMode m) {
	switch (m) {
	case BLEND_ALPHA:      return { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD, GL_FUNC_ADD, true };
	case BLEND_ADDITIVE:   return { GL_SRC_ALPHA, GL_ONE, GL_ONE, GL_ONE, GL_FUNC_ADD, GL_FUNC_ADD, true };
	case BLEND_MULTIPLIED: return { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD, GL_FUNC_ADD, true };
	case BLEND_REPLACE:    return { GL_ONE, GL_ZERO, GL_ONE, GL_ZERO, GL_FUNC_ADD, GL_FUNC_ADD, false };
	case BLEND_CUSTOM_SEPARATE: return g.custom;
	}
	return g.custom;
}

inline void ApplyBlend() {
	BlendState s = BlendStateFor(g.blend);
	if (!s.enabled) {
		glDisable(GL_BLEND);
		return;
	}
	glEnable(GL_BLEND);
	glBlendFuncSeparate(s.srcRGB, s.dstRGB, s.srcA, s.dstA);
	glBlendEquationSeparate(s.eqRGB, s.eqA);
}

inline void SetBlendFactorsSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcA, GLenum dstA, GLenum eqRGB, GLenum eqA) {
	g.custom = { srcRGB, dstRGB, srcA, dstA, eqRGB, eqA, true };
}

inline void BeginBlendMode(BlendMode m) {
	g.flush();
	g.blend = m;
	ApplyBlend();
}

inline void EndBlendMode() {
	g.flush();
	g.blend = BLEND_ALPHA;
	ApplyBlend();
}

inline void BeginTextureMode(const RenderTexture& rt) {
	g.flush();
	glBindFramebuffer(GL_FRAMEBUFFER, rt.id);
	glViewport(0, 0, rt.texture.width, rt.texture.height);
	OrthoYUp(g.mvp, (float)rt.texture.width, (float)rt.texture.height);
}

inline void EndTextureMode() {
	g.flush();
	glBindFramebuffer(GL_FRAMEBUFFER, g.ownsWindow ? 0 : g.stateBackup.fbo);
	glViewport(0, 0, g.fbW, g.fbH);
	OrthoYDown(g.mvp, (float)g.winW, (float)g.winH);
}

inline void BeginShaderMode(Shader s) {
	g.flush();
	g.userProgram = s.id;
}

inline void EndShaderMode() {
	g.flush();
	g.userProgram = 0;
}

inline GLuint CompileStage(GLenum type, const char* src) {
	GLuint sh = glCreateShader(type);
	glShaderSource(sh, 1, &src, nullptr);
	glCompileShader(sh);
	GLint ok = 0;
	glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		char log[2048];
		glGetShaderInfoLog(sh, sizeof(log), nullptr, log);
		std::fprintf(stderr, "shader compile error:\n%s\n", log);
		glDeleteShader(sh);
		return 0;
	}
	return sh;
}

inline Shader LoadShaderFromMemory(const char* vs, const char* fs) {
	GLuint v = CompileStage(GL_VERTEX_SHADER, vs);
	GLuint f = CompileStage(GL_FRAGMENT_SHADER, fs);
	if (!v or !f) {
		if (v) glDeleteShader(v);
		if (f) glDeleteShader(f);
		return { 0 };
	}
	GLuint p = glCreateProgram();
	glAttachShader(p, v);
	glAttachShader(p, f);
	glLinkProgram(p);
	glDetachShader(p, v);
	glDetachShader(p, f);
	glDeleteShader(v);
	glDeleteShader(f);
	GLint ok = 0;
	glGetProgramiv(p, GL_LINK_STATUS, &ok);
	if (!ok) {
		char log[2048];
		glGetProgramInfoLog(p, sizeof(log), nullptr, log);
		std::fprintf(stderr, "program link error:\n%s\n", log);
		glDeleteProgram(p);
		return { 0 };
	}
	return { p };
}

inline void UnloadShader(Shader& s) {
	if (s.id) glDeleteProgram(s.id);
	s.id = 0;
}

inline int GetShaderLocation(Shader s, const char* name) {
	return glGetUniformLocation(s.id, name);
}

inline void SetShaderValue(Shader s, int loc, const void* v, UniformType t) {
	if (loc < 0) return;
	switch (t) {
	case UNIFORM_FLOAT: glProgramUniform1fv(s.id, loc, 1, (const float*)v); break;
	case UNIFORM_VEC2:  glProgramUniform2fv(s.id, loc, 1, (const float*)v); break;
	case UNIFORM_VEC3:  glProgramUniform3fv(s.id, loc, 1, (const float*)v); break;
	case UNIFORM_VEC4:  glProgramUniform4fv(s.id, loc, 1, (const float*)v); break;
	case UNIFORM_INT:   glProgramUniform1iv(s.id, loc, 1, (const int*)v); break;
	case UNIFORM_MAT4:  glProgramUniformMatrix4fv(s.id, loc, 1, GL_FALSE, (const float*)v); break;
	}
}

inline const char* DefaultVS = R"(
#version 460 core
layout(location = 0) in vec2 inPos;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec4 inColor;
layout(location = 0) uniform mat4 mvp;
out vec2 uv;
out vec4 color;
void main() {
	uv = inUV;
	color = inColor;
	gl_Position = mvp * vec4(inPos, 0.0, 1.0);
}
)";

inline const char* DefaultFS = R"(
#version 460 core
in vec2 uv;
in vec4 color;
layout(location = 1) uniform sampler2D tex;
out vec4 outColor;
void main() {
	outColor = texture(tex, uv) * color;
}
)";

struct Vertex { float x, y, u, v; uint8_t r, g, b, a; };

inline bool InitCore(int w, int h) {
	g.winW = w;
	g.winH = h;
	OrthoYDown(g.mvp, (float)w, (float)h);

	g.defaultProgram = LoadShaderFromMemory(DefaultVS, DefaultFS).id;
	if (!g.defaultProgram) return false;

	glCreateVertexArrays(1, &g.vao);
	glCreateBuffers(1, &g.vbo);
	glNamedBufferStorage(g.vbo, sizeof(Vertex) * 6, nullptr, GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayVertexBuffer(g.vao, 0, g.vbo, 0, sizeof(Vertex));
	glEnableVertexArrayAttrib(g.vao, 0);
	glEnableVertexArrayAttrib(g.vao, 1);
	glEnableVertexArrayAttrib(g.vao, 2);
	glVertexArrayAttribFormat(g.vao, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, x));
	glVertexArrayAttribFormat(g.vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, u));
	glVertexArrayAttribFormat(g.vao, 2, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex, r));
	glVertexArrayAttribBinding(g.vao, 0, 0);
	glVertexArrayAttribBinding(g.vao, 1, 0);
	glVertexArrayAttribBinding(g.vao, 2, 0);

	uint8_t px[4] = { 255, 255, 255, 255 };
	Image one = { px, 1, 1 };
	g.white = LoadTextureFromImage(one);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	g.blend = BLEND_ALPHA;
	ApplyBlend();
	return true;
}

inline MouseButton MapSDLMouseButton(uint8_t btn) {
	switch (btn) {
	case SDL_BUTTON_LEFT:   return MOUSE_BUTTON_LEFT;
	case SDL_BUTTON_RIGHT:  return MOUSE_BUTTON_RIGHT;
	case SDL_BUTTON_MIDDLE: return MOUSE_BUTTON_MIDDLE;
	default:                return MOUSE_NONE;
	}
}

inline void CoreResize(int w, int h) {
	g.winW = w;
	g.winH = h;
	if (g.window) {
		SDL_GetWindowSizeInPixels(g.window, &g.fbW, &g.fbH);
	} else {
		g.fbW = w;
		g.fbH = h;
	}
}

inline int GetCodepoint(const char* text, int* codepointSize) {
	const unsigned char* s = (const unsigned char*)text;
	if (!s or !*s) {
		if (codepointSize) *codepointSize = 1;
		return 0x3f;
	}
	int size = 1;
	int cp = 0x3f;
	unsigned char c = s[0];
 
	if (c < 0x80) {
		cp = c;
	} else if (c >= 0xc2 and c <= 0xdf) {
		if ((s[1] & 0xc0) == 0x80) {
			cp = ((c & 0x1f) << 6) | (s[1] & 0x3f);
			size = 2;
		}
	} else if (c >= 0xe0 and c <= 0xef) {
		if ((s[1] & 0xc0) == 0x80 and (s[2] & 0xc0) == 0x80) {
			int v = ((c & 0x0f) << 12) | ((s[1] & 0x3f) << 6) | (s[2] & 0x3f);
			if (v >= 0x800 and (v < 0xd800 or v > 0xdfff)) {
				cp = v;
				size = 3;
			}
		}
	} else if (c >= 0xf0 and c <= 0xf4) {
		if ((s[1] & 0xc0) == 0x80 and (s[2] & 0xc0) == 0x80 and (s[3] & 0xc0) == 0x80) {
			int v = ((c & 0x07) << 18) | ((s[1] & 0x3f) << 12) | ((s[2] & 0x3f) << 6) | (s[3] & 0x3f);
			if (v >= 0x10000 and v <= 0x10ffff) {
				cp = v;
				size = 4;
			}
		}
	}
 
	if (codepointSize) *codepointSize = size;
	return cp;
}

inline void ResetFrameInput() {
	std::memset(g.mousePressed, 0, sizeof(g.mousePressed));
	std::memset(g.mouseReleased, 0, sizeof(g.mouseReleased));
	std::memset(g.keyPressed, 0, sizeof(g.keyPressed));
	g.mouseWheel = 0.0f;
	g.charQueue.clear();
}

inline void ProcessEvent(const SDL_Event& e) {
	switch (e.type) {
	case SDL_EVENT_QUIT:
	case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
		g.shouldClose = true;
		break;
	case SDL_EVENT_WINDOW_RESIZED:
		CoreResize(e.window.data1, e.window.data2);
		break;
	case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
		g.fbW = e.window.data1;
		g.fbH = e.window.data2;
		break;
	case SDL_EVENT_WINDOW_MOUSE_ENTER:
		g.cursorOnWindow = true;
		break;
	case SDL_EVENT_WINDOW_MOUSE_LEAVE:
		g.cursorOnWindow = false;
		break;
	case SDL_EVENT_WINDOW_FOCUS_LOST:
		std::memset(g.keyDown, 0, sizeof(g.keyDown));
		std::memset(g.mouseDown, 0, sizeof(g.mouseDown));
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN: {
		MouseButton b = MapSDLMouseButton(e.button.button);
		if (b != MOUSE_NONE) {
			if (!g.mouseDown[b]) g.mousePressed[b] = true;
			g.mouseDown[b] = true;
		}
		break;
	}
	case SDL_EVENT_MOUSE_BUTTON_UP: {
		MouseButton b = MapSDLMouseButton(e.button.button);
		if (b != MOUSE_NONE) {
			g.mouseDown[b] = false;
			g.mouseReleased[b] = true;
		}
		break;
	}
	case SDL_EVENT_MOUSE_WHEEL:
		g.mouseWheel += e.wheel.y;
		break;
	case SDL_EVENT_KEY_DOWN: {
		SDL_Scancode sc = e.key.scancode;
		if (sc >= 0 and sc < SDL_SCANCODE_COUNT) {
			if (!e.key.repeat and !g.keyDown[sc]) g.keyPressed[sc] = true;
			g.keyDown[sc] = true;
		}
		break;
	}
	case SDL_EVENT_KEY_UP: {
		SDL_Scancode sc = e.key.scancode;
		if (sc >= 0 and sc < SDL_SCANCODE_COUNT) {
			g.keyDown[sc] = false;
		}
		break;
	}
	case SDL_EVENT_TEXT_INPUT: {
		const char* text = e.text.text;
		while (text and *text) {
			int sz = 0;
			int cp = GetCodepoint(text, &sz);
			if (sz <= 0) break;
			g.charQueue.push_back(cp);
			text += sz;
		}
		break;
	}
	default:
		break;
	}
}

inline void PollEvents() {
	ResetFrameInput();
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ProcessEvent(e);
	}
}

inline GLStateBackup SaveGLState() {
	GLStateBackup s{};
	glGetIntegerv(GL_CURRENT_PROGRAM, &s.program);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &s.vao);
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &s.arrayBuffer);
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &s.fbo);
	glGetIntegerv(GL_ACTIVE_TEXTURE, &s.activeTexture);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &s.texture2D);
	glGetIntegerv(GL_VIEWPORT, s.viewport);
	glGetIntegerv(GL_SCISSOR_BOX, s.scissorBox);
	glGetIntegerv(GL_BLEND_SRC_RGB, &s.blendSrcRGB);
	glGetIntegerv(GL_BLEND_DST_RGB, &s.blendDstRGB);
	glGetIntegerv(GL_BLEND_SRC_ALPHA, &s.blendSrcAlpha);
	glGetIntegerv(GL_BLEND_DST_ALPHA, &s.blendDstAlpha);
	glGetIntegerv(GL_BLEND_EQUATION_RGB, &s.blendEqRGB);
	glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &s.blendEqAlpha);
	s.blend = glIsEnabled(GL_BLEND);
	s.depthTest = glIsEnabled(GL_DEPTH_TEST);
	s.cullFace = glIsEnabled(GL_CULL_FACE);
	s.scissorTest = glIsEnabled(GL_SCISSOR_TEST);
	return s;
}

inline void RestoreGLState(const GLStateBackup& s) {
	glUseProgram(s.program);
	glBindVertexArray(s.vao);
	glBindBuffer(GL_ARRAY_BUFFER, s.arrayBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, s.fbo);
	glActiveTexture(s.activeTexture);
	glBindTexture(GL_TEXTURE_2D, s.texture2D);
	glViewport(s.viewport[0], s.viewport[1], s.viewport[2], s.viewport[3]);
	glScissor(s.scissorBox[0], s.scissorBox[1], s.scissorBox[2], s.scissorBox[3]);
	glBlendEquationSeparate(s.blendEqRGB, s.blendEqAlpha);
	glBlendFuncSeparate(s.blendSrcRGB, s.blendDstRGB, s.blendSrcAlpha, s.blendDstAlpha);
	if (s.blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
	if (s.depthTest) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
	if (s.cullFace) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
	if (s.scissorTest) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
}

inline void BeginOverlay(int winW, int winH, int fbW, int fbH, float dt) {
	g.stateBackup = SaveGLState();
	g.winW = winW;
	g.winH = winH;
	g.fbW = fbW;
	g.fbH = fbH;
	g.frameTime = dt;

	glViewport(0, 0, fbW, fbH);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	OrthoYDown(g.mvp, (float)winW, (float)winH);
}

inline void EndOverlay() {
	g.flush();
	RestoreGLState(g.stateBackup);
	ResetFrameInput();
}

inline void BeginDrawing() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, g.fbW, g.fbH);
	OrthoYDown(g.mvp, (float)g.winW, (float)g.winH);
}

inline void EndDrawing() {
	g.flush();
	if (g.window) SDL_GL_SwapWindow(g.window);

	uint64_t now = SDL_GetTicksNS();
	uint64_t elapsed = now - g.lastFrameTimeNS;
	if (g.targetFPS > 0) {
		uint64_t targetNS = 1000000000ULL / (uint64_t)g.targetFPS;
		if (elapsed < targetNS) {
			SDL_DelayPrecise(targetNS - elapsed);
			now = SDL_GetTicksNS();
			elapsed = now - g.lastFrameTimeNS;
		}
	}
	g.frameTime = (float)elapsed / 1e9f;
	g.lastFrameTimeNS = now;

	PollEvents();
}

inline void ClearBackground(Color c) {
	glClearColor(c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

inline void DrawTexturePro(const Texture& t, Rectangle src, Rectangle dst, Vector2 origin, float rotation, Color tint) {
	float u0 = src.x / t.width, u1 = (src.x + src.width) / t.width;
	float v0 = src.y / t.height, v1 = (src.y + src.height) / t.height;

	float lx0 = -origin.x, lx1 = dst.width - origin.x;
	float ly0 = -origin.y, ly1 = dst.height - origin.y;

	float c = 1.0f, s = 0.0f;
	if (rotation != 0.0f) {
		float rad = rotation * DEG2RAD;
		c = std::cos(rad);
		s = std::sin(rad);
	}

	float ax = dst.x + lx0 * c - ly0 * s, ay = dst.y + lx0 * s + ly0 * c;
	float bx = dst.x + lx1 * c - ly0 * s, by = dst.y + lx1 * s + ly0 * c;
	float cx = dst.x + lx1 * c - ly1 * s, cy = dst.y + lx1 * s + ly1 * c;
	float dx = dst.x + lx0 * c - ly1 * s, dy = dst.y + lx0 * s + ly1 * c;

	Vertex q[6] = {
		{ ax, ay, u0, v0, tint.r, tint.g, tint.b, tint.a },
		{ bx, by, u1, v0, tint.r, tint.g, tint.b, tint.a },
		{ cx, cy, u1, v1, tint.r, tint.g, tint.b, tint.a },
		{ ax, ay, u0, v0, tint.r, tint.g, tint.b, tint.a },
		{ cx, cy, u1, v1, tint.r, tint.g, tint.b, tint.a },
		{ dx, dy, u0, v1, tint.r, tint.g, tint.b, tint.a },
	};
	glNamedBufferSubData(g.vbo, 0, sizeof(q), q);

	GLuint prog = g.userProgram ? g.userProgram : g.defaultProgram;
	glUseProgram(prog);
	glProgramUniformMatrix4fv(prog, 0, 1, GL_FALSE, g.mvp);
	glProgramUniform1i(prog, 1, 0);
	glBindTextureUnit(0, t.id);
	glBindVertexArray(g.vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

inline void UpdateTextureRec(const Texture& t, Rectangle r, const void* rgba) {
	if (!t.id or !rgba) return;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTextureSubImage2D(t.id, 0, (GLint)r.x, (GLint)r.y, (GLsizei)r.width, (GLsizei)r.height, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
	if (t.mipmaps > 1) glGenerateTextureMipmap(t.id);
}

inline void UpdateTexture(const Texture& t, const void* rgba) {
	UpdateTextureRec(t, { 0, 0, (float)t.width, (float)t.height }, rgba);
}

inline void DrawTexturePro(const Texture& t, Rectangle src, Rectangle dst, Color tint) {
	DrawTexturePro(t, src, dst, { 0, 0 }, 0.0f, tint);
}

inline void DrawRectangle(Rectangle r, Color c) {
	DrawTexturePro(g.white, { 0, 0, 1, 1 }, r, c);
}
 
inline int* LoadCodepoints(const char* text, int* count) {
	int len = (int)std::strlen(text);
	int* out = (int*)std::malloc(sizeof(int) * (len > 0 ? len : 1));
	int n = 0;
	for (int i = 0; i < len;) {
		int sz = 1;
		out[n++] = GetCodepoint(text + i, &sz);
		i += sz;
	}
	if (n < len) {
		int* shrunk = (int*)std::realloc(out, sizeof(int) * (n > 0 ? n : 1));
		if (shrunk) out = shrunk;
	}
	if (count) *count = n;
	return out;
}
 
inline void UnloadCodepoints(int* codepoints) {
	std::free(codepoints);
}
 
inline const char* CodepointToUTF8(int codepoint, int* utf8Size) {
	static thread_local char utf8[8];
	std::memset(utf8, 0, sizeof(utf8));
	int size = 0;
 
	if (codepoint >= 0xd800 and codepoint <= 0xdfff) codepoint = 0xfffd;
 
	if (codepoint < 0) {
		utf8[0] = (char)0xef; utf8[1] = (char)0xbf; utf8[2] = (char)0xbd;
		size = 3;
	} else if (codepoint <= 0x7f) {
		utf8[0] = (char)codepoint;
		size = 1;
	} else if (codepoint <= 0x7ff) {
		utf8[0] = (char)(0xc0 | (codepoint >> 6));
		utf8[1] = (char)(0x80 | (codepoint & 0x3f));
		size = 2;
	} else if (codepoint <= 0xffff) {
		utf8[0] = (char)(0xe0 | (codepoint >> 12));
		utf8[1] = (char)(0x80 | ((codepoint >> 6) & 0x3f));
		utf8[2] = (char)(0x80 | (codepoint & 0x3f));
		size = 3;
	} else if (codepoint <= 0x10ffff) {
		utf8[0] = (char)(0xf0 | (codepoint >> 18));
		utf8[1] = (char)(0x80 | ((codepoint >> 12) & 0x3f));
		utf8[2] = (char)(0x80 | ((codepoint >> 6) & 0x3f));
		utf8[3] = (char)(0x80 | (codepoint & 0x3f));
		size = 4;
	} else {
		utf8[0] = (char)0xef; utf8[1] = (char)0xbf; utf8[2] = (char)0xbd;
		size = 3;
	}
 
	if (utf8Size) *utf8Size = size;
	return utf8;
}

inline Color ColorLerp(Color a, Color b, float t) {
    Color color{};

    t = std::clamp(t, 0.0f, 1.0f);

    color.r = (uint8_t)((1.0f - t)*a.r + t*b.r);
    color.g = (uint8_t)((1.0f - t)*a.g + t*b.g);
    color.b = (uint8_t)((1.0f - t)*a.b + t*b.b);
    color.a = (uint8_t)((1.0f - t)*a.a + t*b.a);

    return color;
}

inline Color ColorFromHSV(float hue, float saturation, float value) {
    float h = std::fmod(hue, 360.0f);
    if (h < 0.0f) h += 360.0f;

    float c = value * saturation;
    float x = c * (1.0f - std::fabs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = value - c;

    float r = 0.0f, g = 0.0f, b = 0.0f;

    if (h < 60.0f) {
        r = c; g = x; b = 0.0f;
    } else if (h < 120.0f) {
        r = x; g = c; b = 0.0f;
    } else if (h < 180.0f) {
        r = 0.0f; g = c; b = x;
    } else if (h < 240.0f) {
        r = 0.0f; g = x; b = c;
    } else if (h < 300.0f) {
        r = x; g = 0.0f; b = c;
    } else {
        r = c; g = 0.0f; b = x;
    }

    return {
        static_cast<uint8_t>(std::round((r + m) * 255.0f)),
        static_cast<uint8_t>(std::round((g + m) * 255.0f)),
        static_cast<uint8_t>(std::round((b + m) * 255.0f)),
        255
    };
}

inline bool IsMouseButtonPressed(MouseButton t) {
	if (t < 0 or t >= MOUSE_BUTTON_COUNT) return false;
	return g.mousePressed[t];
}

inline bool IsMouseButtonDown(MouseButton t) {
	if (t < 0 or t >= MOUSE_BUTTON_COUNT) return false;
	return g.mouseDown[t];
}

inline bool IsMouseButtonUp(MouseButton t) {
	if (t < 0 or t >= MOUSE_BUTTON_COUNT) return false;
	return !g.mouseDown[t];
}

inline bool IsMouseButtonReleased(MouseButton t) {
	if (t < 0 or t >= MOUSE_BUTTON_COUNT) return false;
	return g.mouseReleased[t];
}

inline bool IsKeyPressed(int key) {
	if (key < 0 or key >= SDL_SCANCODE_COUNT) return false;
	return g.keyPressed[key];
}

inline bool IsKeyDown(int key) {
	if (key < 0 or key >= SDL_SCANCODE_COUNT) return false;
	return g.keyDown[key];
}

inline int GetCharPressed() {
	if (g.charQueue.empty()) return 0;
	int cp = g.charQueue.front();
	g.charQueue.pop_front();
	return cp;
}

inline float GetMouseWheelMove() {
	return g.mouseWheel;
}

inline bool IsWindowReady() {
	return g.windowReady;
}

inline bool IsWindowMaximized() {
	return g.window and (SDL_GetWindowFlags(g.window) & SDL_WINDOW_MAXIMIZED) != 0;
}

inline void MaximizeWindow() {
	if (g.window) SDL_MaximizeWindow(g.window);
}

inline void MinimizeWindow() {
	if (g.window) SDL_MinimizeWindow(g.window);
}

inline void RestoreWindow() {
	if (g.window) SDL_RestoreWindow(g.window);
}

inline bool IsWindowFullscreen() {
	return g.window and (SDL_GetWindowFlags(g.window) & SDL_WINDOW_FULLSCREEN) != 0;
}

inline void ToggleFullscreen() {
	if (g.window) SDL_SetWindowFullscreen(g.window, !IsWindowFullscreen());
}

inline void SetMouseCursor(int cursor) {
	if (cursor == g.currentCursorId) return;
	SDL_Cursor* next = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor));
	if (!next) return;
	SDL_SetCursor(next);
	if (g.activeCursor) SDL_DestroyCursor(g.activeCursor);
	g.activeCursor = next;
	g.currentCursorId = cursor;
}

inline bool IsCursorOnWindow() {
	return g.window and g.cursorOnWindow;
}

inline Vector2 GetMousePosition() {
	float x = 0.0f, y = 0.0f;
	SDL_GetMouseState(&x, &y);
	return { x, y };
}

inline int GetWindowWidth() {
	int w = 0, h = 0;
	if (g.window) SDL_GetWindowSize(g.window, &w, &h);
	else { w = g.winW; h = g.winH; }
	return w;
}

inline int GetWindowHeight() {
	int w = 0, h = 0;
	if (g.window) SDL_GetWindowSize(g.window, &w, &h);
    else { w = g.winW; h = g.winH; }
	return h;
}

inline void SetWindowPosition(int x, int y) {
	if (g.window) SDL_SetWindowPosition(g.window, x, y);
}

inline Vector2 GetWindowPosition() {
	int x = 0, y = 0;
	if (g.window) SDL_GetWindowPosition(g.window, &x, &y);
	return { (float)x, (float)y };
}

inline void SetWindowSize(int width, int height) {
	if (!g.window) return;
	SDL_SetWindowSize(g.window, width, height);
	CoreResize(width, height);
}

inline void SetWindowMinSize(int width, int height) {
	if (g.window) SDL_SetWindowMinimumSize(g.window, width, height);
}

inline void SetWindowIcon(const Image& icon) {
	if (!g.window or !icon.data or icon.width <= 0 or icon.height <= 0) return;
	SDL_Surface* surf = SDL_CreateSurfaceFrom(
		icon.width,
		icon.height,
		SDL_PIXELFORMAT_RGBA32,
		icon.data,
		icon.width * 4
	);
	if (!surf) return;
	SDL_SetWindowIcon(g.window, surf);
	SDL_DestroySurface(surf);
}

inline void SetConfigFlags(unsigned int flags) {
	g.configFlags = flags;
}

inline void DestroyGLResources() {
	SIMPLEUI_CORE::Context& ctx = SIMPLEUI_CORE::g;

	SIMPLEUI_CORE::UnloadTexture(ctx.white);
	if (ctx.vao) {
		glDeleteVertexArrays(1, &ctx.vao);
		ctx.vao = 0;
	}
	if (ctx.vbo) {
		glDeleteBuffers(1, &ctx.vbo);
		ctx.vbo = 0;
	}
	if (ctx.defaultProgram) {
		glDeleteProgram(ctx.defaultProgram);
		ctx.defaultProgram = 0;
	}
}

inline void CloseWindow() {
	if (g.activeCursor) {
		SDL_DestroyCursor(g.activeCursor);
		g.activeCursor = nullptr;
		g.currentCursorId = -1;
	}

	DestroyGLResources();

	if (g.ownsWindow) {
		if (g.glContext) {
			SDL_GL_DestroyContext(g.glContext);
			g.glContext = nullptr;
		}
		if (g.window) {
			SDL_StopTextInput(g.window);
			SDL_DestroyWindow(g.window);
			g.window = nullptr;
		}
		SDL_Quit();
	} else {
		g.window = nullptr;
		g.glContext = nullptr;
	}

	g.windowReady = false;
	g.shouldClose = false;
}

inline void InitWindow(int width, int height, const std::string& name) {
    g.ownsWindow = true;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (g.configFlags & FLAG_MSAA_4X_HINT) {
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	}

	SDL_WindowFlags winFlags = SDL_WINDOW_OPENGL;
	if (g.configFlags & FLAG_FULLSCREEN_MODE)    winFlags |= SDL_WINDOW_FULLSCREEN;
	if (g.configFlags & FLAG_WINDOW_RESIZABLE)   winFlags |= SDL_WINDOW_RESIZABLE;
	if (g.configFlags & FLAG_WINDOW_UNDECORATED) winFlags |= SDL_WINDOW_BORDERLESS;
	if (g.configFlags & FLAG_WINDOW_HIDDEN)      winFlags |= SDL_WINDOW_HIDDEN;
	if (g.configFlags & FLAG_WINDOW_MINIMIZED)   winFlags |= SDL_WINDOW_MINIMIZED;
	if (g.configFlags & FLAG_WINDOW_MAXIMIZED)   winFlags |= SDL_WINDOW_MAXIMIZED;
	if (g.configFlags & FLAG_WINDOW_TOPMOST)     winFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
	if (g.configFlags & FLAG_WINDOW_TRANSPARENT) winFlags |= SDL_WINDOW_TRANSPARENT;
	if (g.configFlags & FLAG_WINDOW_HIGHDPI)     winFlags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;

	g.window = SDL_CreateWindow(name.c_str(), width, height, winFlags);
	if (!g.window) {
		std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}

	g.glContext = SDL_GL_CreateContext(g.window);
	if (!g.glContext) {
		std::fprintf(stderr, "SDL_GL_CreateContext failed: %s\n", SDL_GetError());
		SDL_DestroyWindow(g.window);
		g.window = nullptr;
		SDL_Quit();
		return;
	}

	SDL_GL_MakeCurrent(g.window, g.glContext);
	SDL_GL_SetSwapInterval((g.configFlags & FLAG_VSYNC_HINT) ? 1 : 0);

	if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
		std::fprintf(stderr, "gladLoadGL failed\n");
		CloseWindow();
		return;
	}

	if (g.configFlags & FLAG_MSAA_4X_HINT) {
		glEnable(GL_MULTISAMPLE);
	}

	if (!InitCore(width, height)) {
		CloseWindow();
		return;
	}
	CoreResize(width, height);

	SDL_StartTextInput(g.window);
	g.cursorOnWindow = (SDL_GetWindowFlags(g.window) & SDL_WINDOW_MOUSE_FOCUS) != 0;
	g.lastFrameTimeNS = SDL_GetTicksNS();
	g.frameTime = 0.0f;
	g.shouldClose = false;
	g.windowReady = true;
}

inline bool WindowShouldClose() {
	return g.shouldClose or !g.window;
}

inline float GetFrameTime() {
	return g.frameTime;
}

inline void SetTargetFPS(int q) {
	g.targetFPS = q > 0 ? q : 0;
}

inline int GetCurrentMonitor() {
	if (g.window) return (int)SDL_GetDisplayForWindow(g.window);
	return (int)SDL_GetPrimaryDisplay();
}

inline int GetMonitorRefreshRate(int monitor) {
	SDL_DisplayID id = monitor > 0 ? (SDL_DisplayID)monitor : SDL_GetPrimaryDisplay();
	const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(id);
	return mode ? (int)std::lround(mode->refresh_rate) : 0;
}

inline const char* GetClipboardText() {
	char* raw = SDL_GetClipboardText();
	if (!raw) {
		g.clipboard.clear();
		return "";
	}
	g.clipboard = raw;
	SDL_free(raw);
	return g.clipboard.c_str();
}

}