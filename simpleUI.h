#pragma once
#include <raylib.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include "getLayout.h"

int winWidth = 0;
int winHeight = 0;

Font ArialFont;
int defaultSpacing = 5;

float dt = 0;

std::vector<void*> ActiveSignals;

#define _CRT_SECURE_NO_WARNINGS

template <typename T>
struct ChangedSignal { // not working with strings (any dynamic memory)
public:
	std::string SignalClass = "~";

	void Update() {
		if (Getter) {
			std::cout << LastValue << std::endl;
			if (LastValue != Getter()) {
				LastValue = Getter();
				Callback();
			}
		}
		else {
			if (*SignalPTR != LastValue) {
				LastValue = *SignalPTR;
				Callback();
			}
		}
	}
private:
	T* SignalPTR = nullptr;
	T LastValue{};
	std::function<void(void)> Callback;
	std::function<T(void)> Getter;
public:
	void Disconnect() {
		auto z = find(ActiveSignals.begin(), ActiveSignals.end(), this);
		if (z != ActiveSignals.end()) ActiveSignals.erase(z);
		delete this;
	}
	ChangedSignal() = delete;
	ChangedSignal(T* p, std::function<void(void)> func) : SignalPTR(p), Callback(func), LastValue(*p), SignalClass(typeid(T).name()) { ActiveSignals.push_back(this); }
	ChangedSignal(std::function<T(void)> get, std::function<void(void)> func) : Getter(get), Callback(func), SignalClass(typeid(T).name()) {
		ActiveSignals.push_back(this);
		LastValue = string(Getter());
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

Vector2 getTextOffset(TextAnchorEnum anchor) {
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

Vector3 getTextCFrame(const char* text, Font font, Rectangle rec, TextAnchorEnum anchor, int maxTextSize) {
	if (maxTextSize < 0 or maxTextSize > rec.height) maxTextSize = rec.height;

	int endX{};
	int endY{};
	float endSize = 1;
	float sizeMax = maxTextSize;
	Vector2 textSize{};

	while (endSize < sizeMax) {
		float middle = (endSize + sizeMax + 1) / 2;
		textSize = MeasureTextEx(font, text, middle, defaultSpacing);
		if (textSize.x <= rec.width and textSize.y <= rec.height) endSize = middle;
		else sizeMax = middle - 1;
	}

	if (endSize > maxTextSize) endSize = maxTextSize;
	Vector2 ofst = getTextOffset(anchor);
	float offsetX = ofst.x;
	float offsetY = ofst.y;

	endX = offsetX * (rec.width - textSize.x); if (endX < 0) endX = 0;
	endY = offsetY * (rec.height - textSize.y);  if (endX < 0) endX = 0;

	return { (float)endX, (float)endY, (float)endSize };
}

class TextLabel;
class Instance;
class Object2D;
class TextBox;
class ImageLabel;
class ScrollFrame;

TextBox* FocusedTextBox = nullptr;
Object2D* PreviousHigherObject = nullptr;
Object2D* higherObject = nullptr;

template<typename Z>
void Delete(Z*& ptr) {
	if (!ptr) return;

	if (ptr->Class == "ImageLabel") {
		dynamic_cast<ImageLabel*>(ptr)->setImage("");
	}
	std::vector<Instance*> z = ptr->Children;
	for (auto child : z) {
		Delete(child);
	}

	ptr->setParent(nullptr);
	ptr->Children.clear();
	z.clear();

	delete ptr;
	ptr = nullptr;
}

template <typename T>
T* Clone(T* th) {
	T* ptr = new T(*th);

	ptr->Children.clear();

	if (th->Parent) {
		th->Parent->updateChildrenZIndex = true;
	}

	return ptr;
}

void updateChildren(Instance*);

class Instance {
	std::function<void(Instance*)> callbackChildAdded = [](Instance*) {};
	std::function<void(Instance*)> callbackChildRemoved = [](Instance*) {};
public:
	std::function<void()> functionForTick;
	void SetForTick(std::function<void()> f) { functionForTick = f; }

	bool updateChildrenZIndex = true;

	void CloneChildrenTo(Instance* ptr, const Instance* from) const {
		for (auto& child : from->Children) {
			Instance* newChild = Clone(child);
			newChild->Parent = ptr;
			ptr->Children.push_back(newChild);
			ptr->callbackChildAdded(newChild);
		}

		ptr->updateChildrenZIndex = true;
	}

	Instance* Parent = nullptr;
	std::vector<Instance*> Children;

	std::string Name = "Instance";
	std::string Class = "Instance";

	bool __ParentObject{};

	Instance(bool a) : __ParentObject(a) {};
	Instance(Instance* p) : Parent(p) { if (p) { p->Children.push_back(this); p->callbackChildAdded(this); p->updateChildrenZIndex = true; } }
	Instance() = delete;

	virtual ~Instance() {

	}

	void setParent(Instance* ptr) {
		if (ptr == this) return;

		if (Parent != nullptr) {
			std::vector<Instance*> arr;
			for (Instance*& obj : static_cast<Instance*>(Parent)->Children) {
				arr.push_back(static_cast<Instance*>(obj));
			}
			for (int i = 0; i < arr.size(); i++) {
				if (arr[i] == this) {
					this->Parent->Children.erase(Parent->Children.begin() + i);
					break;
				}
			}

			Parent->callbackChildRemoved(this);
		}

		Parent = ptr;
		if (ptr) {
			ptr->Children.push_back(this);
			ptr->updateChildrenZIndex = true;
			ptr->callbackChildAdded(this);
		}
	}

	void OnChildAdded(std::function<void(Instance*)> callback) {
		callbackChildAdded = callback;
	}

	void OnChildRemoved(std::function<void(Instance*)> callback) {
		callbackChildRemoved = callback;
	}

	Instance* findChild(std::string name) {
		for (auto obj : Children) {
			if (obj->Name == name) {
				return obj;
			}
		}

		return nullptr;
	}

	Instance* findChildOfClass(std::string cls) {
		for (Instance*& obj : Children) {
			if (obj->Class == cls) {
				return obj;
			}
		}

		return nullptr;
	}

	bool isAncestorOf(Instance* other) const {
		Instance* ptr = other;

		while (ptr->Parent != nullptr) {
			if (ptr->Parent == this) return true;
			ptr = ptr->Parent;
		}

		return false;
	}

	bool isDescendantOf(Instance* maybeAncestor) const {
		const Instance* ptr = this;

		while (ptr->Parent != nullptr) {
			if (ptr->Parent == maybeAncestor) return true;
			ptr = ptr->Parent;
		}

		return false;
	}

	virtual void Update() {
		if (updateChildrenZIndex) {
			updateChildren(this);
		}

		if (functionForTick) functionForTick();

		for (Instance* child : Children) {
			child->Update();
		}
	}
};

class StringValue : virtual public Instance {
	constexpr static const char* DefaultName = "StringValue";
	constexpr static const char* DefaultClass = "StringValue";
public:
	std::string Value = "";

	StringValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	StringValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	StringValue() = delete;
};

class ObjectValue : virtual public Instance {
	constexpr static const char* DefaultName = "ObjectValue";
	constexpr static const char* DefaultClass = "ObjectValue";
public:
	Instance* Value = nullptr;

	ObjectValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	ObjectValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	ObjectValue() = delete;
};

class BoolValue : virtual public Instance {
	constexpr static const char* DefaultName = "BoolValue";
	constexpr static const char* DefaultClass = "BoolValue";
public:
	bool Value = 0;

	BoolValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	BoolValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	BoolValue() = delete;
};

class IntValue : virtual public Instance {
	constexpr static const char* DefaultName = "IntValue";
	constexpr static const char* DefaultClass = "IntValue";
public:
	int Value = 0;

	IntValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	IntValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	IntValue() = delete;
};

class FloatValue : virtual public Instance {
	constexpr static const char* DefaultName = "FloatValue";
	constexpr static const char* DefaultClass = "FloatValue";
public:
	float Value = 0.0f;

	FloatValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	FloatValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	FloatValue() = delete;
};

class Vector2Value : virtual public Instance {
	constexpr static const char* DefaultName = "Vector2Value";
	constexpr static const char* DefaultClass = "Vector2Value";
public:
	Vector2 Value = { 0,0 };

	Vector2Value(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	Vector2Value(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	Vector2Value() = delete;
};

class ColorValue : virtual public Instance {
	constexpr static const char* DefaultName = "ColorValue";
	constexpr static const char* DefaultClass = "ColorValue";
public:
	Color Value = { 255,255,255,255 };

	ColorValue(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	ColorValue(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	ColorValue() = delete;
};

class Folder : virtual public Instance {
	constexpr static const char* DefaultName = "Folder";
	constexpr static const char* DefaultClass = "Folder";
public:

	Folder(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	Folder(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	Folder() = delete;
};

Vector2 getCanvasPosition(Object2D*);

class Object2D : virtual public Instance {
	constexpr static const char* DefaultName = "Object2D";
	constexpr static const char* DefaultClass = "Object2D";

	std::function<void()> functionForMouseEnter;
	std::function<void()> functionForMouseLeave;
	std::function<void()> functionForClick1;
	std::function<void()> functionForClick2;

public:
	virtual void eventHandler() {
		Vector2 mousePosition = GetMousePosition();
		bool mouseOnObject = pointInObject(mousePosition);

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) or !Visible or higherObject != this) { isMouseButton1Down = false; }
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) or !Visible or higherObject != this) { isMouseButton2Down = false; }

		if (mouseOnObject) {
			if (startedOnObject1 and IsMouseButtonDown(MOUSE_BUTTON_LEFT) and Visible and higherObject == this) { isMouseButton1Down = true; }
			if (startedOnObject2 and IsMouseButtonDown(MOUSE_BUTTON_RIGHT) and Visible and higherObject == this) { isMouseButton2Down = true; }

			if (!MouseEntered) {
				MouseEntered = true;
				if (functionForMouseEnter and Visible and higherObject == this) functionForMouseEnter();
			}
		}
		else {
			if (MouseEntered) {
				MouseEntered = false;
				if (functionForMouseLeave) functionForMouseLeave();
			}

			isMouseButton1Down = false;
			isMouseButton2Down = false;
		}

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) and mouseOnObject and higherObject == this) {
			startedOnObject1 = true;
		}

		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) and mouseOnObject and higherObject == this) {
			startedOnObject2 = true;
		}

		if (startedOnObject1 and IsMouseButtonReleased(MOUSE_LEFT_BUTTON) and mouseOnObject and higherObject == this) {
			if (functionForClick1 and Visible) functionForClick1(); startedOnObject1 = false;
		}

		if (startedOnObject2 and IsMouseButtonReleased(MOUSE_RIGHT_BUTTON) and mouseOnObject and higherObject == this) {
			if (functionForClick2 and Visible) functionForClick2(); startedOnObject2 = false;
		}

		if (functionForTick) functionForTick();
	}

	Vector2 Position{};
	Vector2 Size{};
	Vector2 AnchorPosition{};

	float BackgroundTransparency{};
	Color BackgroundColor = { 0,0,0,255 };
	bool Visible = true;

	float Roundness = 0.0f;
	short Segments = 5;

	short BorderThickness{};
	float BorderTransparency{};
	Color BorderColor{};

	int ZIndex = 0;
	bool Active = false;

	Vector2 getRealObject2Dsize() {
		Vector2 size = Size;
		Instance* current = Parent;

		while (current) {
			Object2D* obj = dynamic_cast<Object2D*>(current);
			if (!obj) {

				if (current->Parent) {
					current = current->Parent;
					continue;
				}
				break;
			};

			if (obj->__ParentObject) break;

			size.x *= obj->Size.x;
			size.y *= obj->Size.y;

			current = obj->Parent;
		}

		return { size.x * winWidth, size.y * winHeight };
	}

	Vector2 getRealObject2Dposition() {
		Vector2 pos = { Position.x - AnchorPosition.x * Size.x, Position.y - AnchorPosition.y * Size.y };
		Instance* current = Parent;

		while (current) {
			Object2D* obj = dynamic_cast<Object2D*>(current);
			if (!obj) {

				if (current->Parent) {
					current = current->Parent;
					continue;
				}
				break;
			};

			if (obj->__ParentObject) break;

			Vector2 parentPos = { obj->Position.x - obj->AnchorPosition.x * obj->Size.x, obj->Position.y - obj->AnchorPosition.y * obj->Size.y };

			if (obj->Class == "ScrollFrame") {
				Vector2 CanvasPosition = getCanvasPosition(obj);
				pos.x += parentPos.x * obj->Size.x - CanvasPosition.x;
				pos.y += parentPos.y * obj->Size.y - CanvasPosition.y;

			}
			else {
				pos.x = parentPos.x + pos.x * obj->Size.x;
				pos.y = parentPos.y + pos.y * obj->Size.y;
			}

			current = obj->Parent;
		}

		return { pos.x * winWidth, pos.y * winHeight };
	}

	virtual void Draw(Vector2 RealPos = { -1,-1 }, Vector2 RealSize = { -1,-1 }) {
		if (Visible) {
			if (RealPos.x == -1 and RealPos.y == -1 and RealSize.x == -1 and RealSize.y == -1) {
				RealPos = this->getRealObject2Dposition();
				RealSize = this->getRealObject2Dsize();
			}

			if (RealPos.x + RealSize.x + BorderThickness < 0
				or RealPos.x - RealSize.x - BorderThickness > winWidth
				or RealPos.y + RealSize.y + BorderThickness < 0
				or RealPos.y - RealSize.y - BorderThickness > winHeight) {
				return;
			}

			DrawRectangleRounded({ RealPos.x, RealPos.y, RealSize.x, RealSize.y }, Roundness, Segments, { BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, (unsigned char)(BackgroundColor.a * (1 - BackgroundTransparency)) });

			if (BorderThickness > 0) {
				DrawRectangleRoundedLinesEx({ RealPos.x, RealPos.y, RealSize.x, RealSize.y }, Roundness, Segments, BorderThickness, { BorderColor.r, BorderColor.g, BorderColor.b, (unsigned char)(BorderColor.a * (1 - BorderTransparency)) });
			}
		}
	}

	bool pointInObject(Vector2 pos) {
		Vector2 RealPos = this->getRealObject2Dposition();
		Vector2 RealSize = this->getRealObject2Dsize();

		if (pos.x >= RealPos.x and pos.x <= RealPos.x + RealSize.x and pos.y >= RealPos.y and pos.y <= RealPos.y + RealSize.y) return true;

		return false;
	}

	void SetMouseEnter(std::function<void()> f) { functionForMouseEnter = f; }
	void SetMouseLeave(std::function<void()> f) { functionForMouseLeave = f; }
	void SetMouseClick1(std::function<void()> f) { functionForClick1 = f; }
	void SetMouseClick2(std::function<void()> f) { functionForClick2 = f; }

	bool MouseEntered = false;
	bool isMouseButton1Down = false;
	bool isMouseButton2Down = false;

	bool startedOnObject1 = false;
	bool startedOnObject2 = false;

	void Update() override {
		if (!Visible) return;

		if (updateChildrenZIndex) {
			updateChildren(this);
		}

		eventHandler();
		Draw();

		for (Instance* child : Children) {
			child->Update();
		}
	}

	Object2D(bool a) : Instance(a) { Name = DefaultName; Class = DefaultClass; };
	Object2D(Instance* p) : Instance(p) { Name = DefaultName; Class = DefaultClass; }

	Object2D() = delete;
};

void updateChildren(Instance* parent) {
	if (!parent) return;

	parent->updateChildrenZIndex = false;
	for (int i = 0; i < parent->Children.size(); i++)
		for (int j = i + 1; j < parent->Children.size(); j++) {
			if (i == j) continue;

			auto az = dynamic_cast<Object2D*>(parent->Children[i]);
			auto bz = dynamic_cast<Object2D*>(parent->Children[j]);

			if (az and bz and az->ZIndex > bz->ZIndex)
				std::swap(parent->Children[i], parent->Children[j]);
		}
}

class TextLabel : virtual public Object2D {
	constexpr static const char* DefaultName = "TextLabel";
	constexpr static const char* DefaultClass = "TextLabel";
public:
	std::string Text = "";
	float TextTransparency = 0.0f;
	TextAnchorEnum TextAnchor = TextAnchorEnum::CENTER;
	Color TextColor = { 0,0,0,255 };
	int TextSize = 10;

	void Draw(Vector2 RealPos = { -1,-1 }, Vector2 RealSize = { -1,-1 }) override {
		if (Visible) {
			if (RealPos.x == -1 and RealPos.y == -1 and RealSize.x == -1 and RealSize.y == -1) {
				RealPos = this->getRealObject2Dposition();
				RealSize = this->getRealObject2Dsize();
			}

			if (RealPos.x + RealSize.x + BorderThickness < 0
				or RealPos.x - RealSize.x - BorderThickness > winWidth
				or RealPos.y + RealSize.y + BorderThickness < 0
				or RealPos.y - RealSize.y - BorderThickness > winHeight) {
				return;
			}

			DrawRectangleRounded({ RealPos.x, RealPos.y, RealSize.x, RealSize.y }, Roundness, Segments, { BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, (unsigned char)(BackgroundColor.a * (1 - BackgroundTransparency)) });

			if (BorderThickness > 0) {
				DrawRectangleRoundedLinesEx({ RealPos.x, RealPos.y, RealSize.x, RealSize.y }, Roundness, Segments, BorderThickness, { BorderColor.r, BorderColor.g, BorderColor.b, (unsigned char)(BorderColor.a * (1 - BorderTransparency)) });
			}

			Vector3 textParams = getTextCFrame(Text.c_str(), ArialFont, { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize);
			if (textParams.z > 1) {
				DrawTextEx(ArialFont, Text.c_str(), { RealPos.x + textParams.x, RealPos.y + textParams.y }, textParams.z, defaultSpacing, { TextColor.r, TextColor.g, TextColor.b, (unsigned char)(TextColor.a * (1 - TextTransparency)) });
			}
		}
	}

	TextLabel(bool a) : Instance(a), Object2D(a) { Name = DefaultName; Class = DefaultClass; };
	TextLabel(Instance* p) : Instance(p), Object2D(p) { Name = DefaultName; Class = DefaultClass; }

	TextLabel() = delete;
};

struct KeyMapping {
	KeyboardKey key;
	const char* defaultEN;
	const char* shiftEN;
	const char* defaultRU;
	const char* shiftRU;
};

KeyMapping KeysMapping[49] = {
	{ KEY_ONE,   "1", "!", "1", "!" },
	{ KEY_TWO,   "2", "@", "2", "\"" },
	{ KEY_THREE, "3", "#", "3", "¹" },
	{ KEY_FOUR,  "4", "$", "4", ";" },
	{ KEY_FIVE,  "5", "%", "5", ":" },
	{ KEY_SIX,   "6", "^", "6", "?" },
	{ KEY_SEVEN, "7", "&", "7", "?" },
	{ KEY_EIGHT, "8", "*", "8", "*" },
	{ KEY_NINE,  "9", "(", "9", "(" },
	{ KEY_ZERO,  "0", ")", "0", ")" },

	{ KEY_Q, "q", "Q", "é", "É" },
	{ KEY_W, "w", "W", "ö", "Ö" },
	{ KEY_E, "e", "E", "ó", "Ó" },
	{ KEY_R, "r", "R", "ê", "Ê" },
	{ KEY_T, "t", "T", "å", "Å" },
	{ KEY_Y, "y", "Y", "í", "Í" },
	{ KEY_U, "u", "U", "ã", "Ã" },
	{ KEY_I, "i", "I", "ø", "Ø" },
	{ KEY_O, "o", "O", "ù", "Ù" },
	{ KEY_P, "p", "P", "ç", "Ç" },

	{ KEY_A, "a", "A", "ô", "Ô" },
	{ KEY_S, "s", "S", "û", "Û" },
	{ KEY_D, "d", "D", "â", "Â" },
	{ KEY_F, "f", "F", "à", "À" },
	{ KEY_G, "g", "G", "ï", "Ï" },
	{ KEY_H, "h", "H", "ð", "Ð" },
	{ KEY_J, "j", "J", "î", "Î" },
	{ KEY_K, "k", "K", "ë", "Ë" },
	{ KEY_L, "l", "L", "ä", "Ä" },
	{ KEY_SEMICOLON, ";", ":", "æ", "Æ" },
	{ KEY_APOSTROPHE, "'", "\"", "ý", "Ý" },

	{ KEY_Z, "z", "Z", "ÿ", "ß" },
	{ KEY_X, "x", "X", "÷", "×" },
	{ KEY_C, "c", "C", "ñ", "Ñ" },
	{ KEY_V, "v", "V", "ì", "Ì" },
	{ KEY_B, "b", "B", "è", "È" },
	{ KEY_N, "n", "N", "ò", "Ò" },
	{ KEY_M, "m", "M", "ü", "Ü" },
	{ KEY_COMMA, ",", "<", "á", "Á" },
	{ KEY_PERIOD, ".", ">", "þ", "Þ" },
	{ KEY_SLASH, "/", "?", ".", "," },

	{ KEY_SPACE, " ", " ", " ", " " },
	{ KEY_MINUS, "-", "_", "-", "_" },
	{ KEY_EQUAL, "=", "+", "=", "+" },
	{ KEY_LEFT_BRACKET, "[", "{", "õ", "Õ" },
	{ KEY_RIGHT_BRACKET, "]", "}", "ú", "Ú" },
	{ KEY_BACKSLASH, "\\", "|", "\\", "/" },
	{ KEY_GRAVE, "`", "~", "¸", "¨" },
	// { KEY_ENTER, "", "\n", "", "\n"} // WIP
};

class TextBox : virtual public Object2D {
	constexpr static const char* DefaultName = "TextBox";
	constexpr static const char* DefaultClass = "TextBox";

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
public:
	std::vector<int> charOffsets;

	Color CursorColor = { 0,0,0,255 };

	std::string PlaceholderText = "PlaceholderText";
	Color PlaceholderTextColor = { 150, 150, 150, 255 };
	std::string Text = "";
	Color TextColor = { 0,0,0,255 };
	TextAnchorEnum TextAnchor = TextAnchorEnum::CENTER;
	int TextSize = 10;
	int maxSymbols = 20;

	RenderTexture2D cachedText{};
	bool textCached = false;
	std::string lastText;

	void Draw(Vector3 textParams, Vector2 RealPos, Vector2 RealSize) {
		if (!Visible) return;
		if (RealPos.x == -1 and RealPos.y == -1 and RealSize.x == -1 and RealSize.y == -1) {
			RealPos = this->getRealObject2Dposition();
			RealSize = this->getRealObject2Dsize();
		}

		if (RealPos.x + RealSize.x + BorderThickness < 0
			or RealPos.x - RealSize.x - BorderThickness > winWidth
			or RealPos.y + RealSize.y + BorderThickness < 0
			or RealPos.y - RealSize.y - BorderThickness > winHeight) {
			return;
		}

		DrawRectangleRounded({ RealPos.x, RealPos.y, RealSize.x, RealSize.y }, Roundness, Segments, { BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, (unsigned char)(BackgroundColor.a * (1 - BackgroundTransparency)) });

		if (BorderThickness > 0)
			DrawRectangleRoundedLinesEx({ RealPos.x, RealPos.y, RealSize.x, RealSize.y }, Roundness, Segments, BorderThickness, { BorderColor.r, BorderColor.g, BorderColor.b, (unsigned char)(BorderColor.a * (1 - BorderTransparency)) });

		if (Text != "") {

			if (!textCached or Text != lastText) {
				if (textCached) UnloadRenderTexture(cachedText);

				Vector2 size = MeasureTextEx(ArialFont, Text.c_str(), textParams.z, defaultSpacing);
				cachedText = LoadRenderTexture(size.x + 10, size.y + 10);

				BeginTextureMode(cachedText);

				ClearBackground(BLANK);
				DrawTextEx(ArialFont, Text.c_str(), { 0, 0 }, textParams.z, defaultSpacing, TextColor);

				EndTextureMode();

				lastText = Text;
				textCached = true;
			}

			DrawTextureRec(cachedText.texture, { 0, 0, (float)cachedText.texture.width, -(float)cachedText.texture.height }, { RealPos.x + textParams.x, RealPos.y + textParams.y }, WHITE);
		}
		else {
			if (CursorVisible and FocusedTextBox == this) {
				if (textParams.z > 3) {
					float sizeY = MeasureTextEx(ArialFont, "a", textParams.z, defaultSpacing).y;
					DrawLineEx({ RealPos.x + getTextOffset(TextAnchor).x * RealSize.x, RealPos.y + textParams.y + 2 }, { RealPos.x + getTextOffset(TextAnchor).x * RealSize.x, RealPos.y + textParams.y + sizeY - 4 }, 3, CursorColor);
				}
			}
			else if (CursorIndex == -1 or FocusedTextBox != this) {
				DrawTextEx(ArialFont, PlaceholderText.c_str(), { RealPos.x + textParams.x, RealPos.y + textParams.y }, textParams.z, defaultSpacing, PlaceholderTextColor);
			}
		}

		if (CursorIndex >= 0 and CursorVisible and Text != "" and textParams.z > 3) {

			int bytePos = (CursorIndex < (int)charOffsets.size()) ? charOffsets[CursorIndex] : Text.size();
			std::string textBeforeCursor = Text.substr(0, bytePos);
			Vector2 size = MeasureTextEx(ArialFont, textBeforeCursor.c_str(), textParams.z, defaultSpacing);

			if (size.x == 0 and size.y == 0) {
				size.y = MeasureTextEx(ArialFont, "a", textParams.z, defaultSpacing).y;
			}

			DrawLineEx({ RealPos.x + textParams.x + size.x + 2, RealPos.y + textParams.y + 2 }, { RealPos.x + textParams.x + size.x + 2, RealPos.y + textParams.y + size.y - 4 }, 3, CursorColor);
		}
	}

	void Update() override {
		if (!Visible) { CursorIndex = -1; CursorVisible = false; Text = ""; return; }
		if (!(FocusedTextBox == this)) { CursorIndex = -1; CursorVisible = false; deleteText = true; }

		if (updateChildrenZIndex) {
			updateChildren(this);
		}

		eventHandler();

		if (FocusedTextBox == this and deleteText) {
			Text = "";
			CursorIndex = 0;
			deleteText = false;
			updateCharOffsets();
		}

		// CURSOR

		CursorTime += dt;
		if (CursorTime >= CursorCooldown) { CursorVisible = !CursorVisible; CursorTime = 0.0f; }

		Vector2 RealPos = this->getRealObject2Dposition();
		Vector2 RealSize = this->getRealObject2Dsize();

		Vector2 mousePosition = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (pointInObject(mousePosition) and FocusedTextBox != this and higherObject == this) {
				Text = "";
			}

			if (!pointInObject(mousePosition)) {
				CursorIndex = -1;
				CursorVisible = false;

				if (higherObject and higherObject->Class == "TextBox") {
					FocusedTextBox = dynamic_cast<TextBox*>(higherObject);
				}
				else {
					FocusedTextBox = nullptr;
				}
			}

			if (pointInObject(mousePosition) and higherObject == this) {
				CursorTime = 0.0f;
				CursorVisible = true;
				FocusedTextBox = this;

				Vector2 RealPos = this->getRealObject2Dposition();
				Vector2 RealSize = this->getRealObject2Dsize();
				Vector3 textParams = getTextCFrame(Text != "" ? Text.c_str() : PlaceholderText.c_str(), ArialFont, { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize);

				float textStartX = RealPos.x + textParams.x;
				float clickX = mousePosition.x - textStartX;

				CursorIndex = 0;
				if (!Text.empty()) {
					for (int i = 1; i < charOffsets.size(); i++) {
						float widthPrev = MeasureTextEx(ArialFont, Text.substr(0, charOffsets[i - 1]).c_str(), textParams.z, defaultSpacing).x;
						float widthCurr = MeasureTextEx(ArialFont, Text.substr(0, charOffsets[i]).c_str(), textParams.z, defaultSpacing).x;
						if (clickX < (widthPrev + widthCurr) / 2.0f) {
							CursorIndex = (int)(i - 1);
							break;
						}
						CursorIndex = (int)i;
					}
				}
				else {
					CursorIndex = 0;
				}
			}
		}

		// KEYBOARD INPUT

		if (FocusedTextBox == this and Visible) {
			if (maxSymbols >= charOffsets.size()) {
				std::string layout = getLayout();
				int index = (layout == "RU") ? 2 : 0;
				if (IsKeyDown(KEY_LEFT_SHIFT) or capsLock()) index += 1;

				for (auto& key : KeysMapping) {
					if (IsKeyPressed(key.key)) {
						const char* keyValue = nullptr;
						switch (index) {
						case 0: keyValue = key.defaultEN; break;
						case 1: keyValue = key.shiftEN; break;
						case 2: keyValue = key.defaultRU; break;
						case 3: keyValue = key.shiftRU; break;
						default: keyValue = key.defaultEN;
						}

						int bytePos = (CursorIndex < (int)charOffsets.size()) ? charOffsets[CursorIndex] : Text.size();
						Text = Text.substr(0, bytePos) + std::string(keyValue) + Text.substr(bytePos);
						CursorIndex += 1;
						updateCharOffsets();
						CursorVisible = true; CursorTime = 0.0f;
					}
				}
			}
		}

		// UTILS (BACKSPACE | DEL | CTRL BACKSPACE | ARROWS
		if (FocusedTextBox == this and Visible) {
			if (IsKeyPressed(KEY_BACKSPACE) or IsKeyPressed(KEY_DELETE)) {
				if (IsKeyDown(KEY_LEFT_CONTROL)) {
					if (CursorIndex == 0) return;

					int lower = CursorIndex;
					bool Space = false;
					bool first = true;

					for (int i = charOffsets.size() - 2; i >= 0; i--) {
						if (charOffsets[i] > CursorIndex) continue;
						int index = charOffsets[i];
						unsigned char c = Text[index];

						if (c == '.' or c == ',' or c == ':' or c == ';' or c == '?' or c == '!' or c == '/' or c == '\\' or c == '\'' or c == '\"' or c == '`' or c == '~') {
							lower = index;
							break;
						}
						else if ((c == ' ' and first)) {
							Space = true;
							continue;
						}
						else if (c == ' ' and not Space) {
							break;
						}
						else if (c != ' ' and Space) {
							Space = false;
						}

						first = false;

						lower = index;
						CursorVisible = true; CursorTime = 0.0f;
					}

					Text = Text.substr(0, lower);
					updateCharOffsets();
				}
				else {
					if (charOffsets.size() > 1) {
						int sz = charOffsets[charOffsets.size() - 1] - charOffsets[charOffsets.size() - 2];

						int z = Text.size() - sz; if (z < 0) z = 0;
						Text = Text.substr(0, z);
						CursorIndex = z;
						CursorVisible = true; CursorTime = 0.0f;
					}
					else {
						CursorIndex = 0;
						Text = "";
					}

					updateCharOffsets();
				}
			}

			if (IsKeyPressed(KEY_LEFT)) {
				int z = CursorIndex - 1; if (z < 0) z = 0;
				CursorIndex = z;
				CursorVisible = true; CursorTime = 0.0f;
			}

			if (IsKeyPressed(KEY_RIGHT)) {
				int z = CursorIndex + 1; if (z > charOffsets.size() - 1) z = charOffsets.size() - 1;
				CursorIndex = z;
				CursorVisible = true; CursorTime = 0.0f;
			}
		}

		static Vector3 textParams{};
		static std::string lastText = Text;
		static std::string lastPlaceholder = PlaceholderText;
		static Vector2 lastWin = { winWidth, winHeight };

		if (
			(textParams.x == 0 and textParams.y == 0 and textParams.z == 0)
			or lastText != Text
			or lastPlaceholder != PlaceholderText
			or (lastWin.x != winWidth or lastWin.y != winHeight)
			) {

			lastText = Text;
			lastPlaceholder = PlaceholderText;
			lastWin = { winWidth * 1.0f, winHeight * 1.0f };

			if (Text != "")
				textParams = getTextCFrame(Text.c_str(), ArialFont, { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize);
			else
				textParams = getTextCFrame(PlaceholderText.c_str(), ArialFont, { RealPos.x, RealPos.y, RealSize.x, RealSize.y }, TextAnchor, TextSize);
		}

		Draw(textParams, RealPos, RealSize);

		for (Instance* child : Children) {
			child->Update();
		}
	};

	TextBox(bool a) : Instance(a), Object2D(a) { Name = DefaultName; Class = DefaultClass; Active = true; }
	TextBox(Instance* p) : Instance(p), Object2D(p) { Name = DefaultName; Class = DefaultClass; Active = true; }

	TextBox() = delete;
};

enum ImageOverlayFormat {
	STRETCH = 0, // STRETCH ON FULL OBJECT
	FIT = 1, // FIT BY RESOLUTION
	CROP = 2, // CUT EXCESS
};

class ImageLabel : virtual public Object2D {
	constexpr static const char* DefaultName = "ImageLabel";
	constexpr static const char* DefaultClass = "ImageLabel";

	Texture2D tex{};
	int lastImageWidth = 0;
	int lastImageHeight = 0;
	Vector2 lastRealSize = { 0,0 };

	void updateTexture(Vector2 realSize) {
		if (tex.id == 0 or image.width != lastImageWidth or image.height != lastImageHeight or realSize.x != lastRealSize.x or realSize.y != lastRealSize.y) {
			if (tex.id != 0) UnloadTexture(tex);
			tex = LoadTextureFromImage(image);
			SetTextureFilter(tex, TEXTURE_FILTER_TRILINEAR);
			lastImageWidth = image.width;
			lastImageHeight = image.height;
			lastRealSize = realSize;
		}
	}

public:
	Image image = LoadImage("Images/DefaultImage.png");
	ImageOverlayFormat Overlay = FIT;
	float ImageTransparency = 0.0f;
	Color ImageColor = { 255,255,255,255 };

	void setImage(std::string way = "Images/DefaultImage.png") {
		UnloadImage(image);
		image = LoadImage(way.c_str());
		if (tex.id != 0) {
			UnloadTexture(tex);
			tex.id = 0;
		}
	}

	void Draw(Vector2 RealPos = { -1,-1 }, Vector2 RealSize = { -1,-1 }) override {
		if (!Visible) return;
		if (RealPos.x == -1 and RealPos.y == -1 and RealSize.x == -1 and RealSize.y == -1) {
			RealPos = this->getRealObject2Dposition();
			RealSize = this->getRealObject2Dsize();
		}

		if (RealPos.x + RealSize.x + BorderThickness < 0
			or RealPos.x - RealSize.x - BorderThickness > winWidth
			or RealPos.y + RealSize.y + BorderThickness < 0
			or RealPos.y - RealSize.y - BorderThickness > winHeight) {
			return;
		}

		updateTexture(RealSize);

		Rectangle destRec = { RealPos.x, RealPos.y, RealSize.x, RealSize.y };
		Rectangle srcRec = { 0, 0, static_cast<float>(image.width), static_cast<float>(image.height) };

		if (Overlay == FIT) {
			float imageAspect = static_cast<float>(image.width) / image.height;
			float rectAspect = RealSize.x / RealSize.y;

			if (imageAspect > rectAspect) {
				float scaledHeight = RealSize.x / imageAspect;
				destRec.y += (RealSize.y - scaledHeight) / 2.0f;
				destRec.height = scaledHeight;
			}
			else {
				float scaledWidth = RealSize.y * imageAspect;
				destRec.x += (RealSize.x - scaledWidth) / 2.0f;
				destRec.width = scaledWidth;
			}
		}
		else if (Overlay == CROP) {
			float imageAspect = static_cast<float>(image.width) / image.height;
			float rectAspect = RealSize.x / RealSize.y;

			if (imageAspect > rectAspect) {
				float cropWidth = image.height * rectAspect;
				srcRec.x = (image.width - cropWidth) / 2.0f;
				srcRec.width = cropWidth;
			}
			else {
				float cropHeight = image.width / rectAspect;
				srcRec.y = (image.height - cropHeight) / 2.0f;
				srcRec.height = cropHeight;
			}
		}

		DrawRectangleRounded({ RealPos.x, RealPos.y, RealSize.x, RealSize.y }, Roundness, Segments, { BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, (unsigned char)(BackgroundColor.a * (1 - BackgroundTransparency)) });
		DrawTexturePro(tex, srcRec, destRec, { 0,0 }, 0.0f, { ImageColor.r, ImageColor.g, ImageColor.b, (unsigned char)(ImageColor.a * (1 - ImageTransparency)) });

		if (BorderThickness > 0) {
			DrawRectangleRoundedLinesEx({ RealPos.x, RealPos.y, RealSize.x, RealSize.y }, Roundness, Segments, BorderThickness, { BorderColor.r, BorderColor.g, BorderColor.b, (unsigned char)(BorderColor.a * (1 - BorderTransparency)) });
		}
	}

	ImageLabel(bool a) : Instance(a), Object2D(a) { Name = DefaultName; Class = DefaultClass; };
	ImageLabel(Instance* p) : Instance(p), Object2D(p) { Name = DefaultName; Class = DefaultClass; }

	ImageLabel() = delete;

	~ImageLabel() {
		UnloadImage(image);
		if (tex.id != 0) UnloadTexture(tex);
	}
};

class ScrollFrame : public Object2D {
	constexpr static const char* DefaultName = "ScrollFrame";
	constexpr static const char* DefaultClass = "ScrollFrame";
public:
	Vector2 CanvasSize = { 1,1 };
	Vector2 CanvasPosition = { 0,0 };
	float ScrollSpeed = 0.5;
	bool CropDescendants = true;
	Color SliderColor = { 15,15,15,255 };
	float SliderTransparency = 0.5;
	unsigned int SliderSize = 5;
	char Direction = 'Y';

	void Draw(Vector2 RealPosition, Vector2 RealSize) {
		Object2D::Draw(RealPosition, RealSize);

		if (CropDescendants) {
			BeginScissorMode(RealPosition.x, RealPosition.y, RealSize.x, RealSize.y);
		}

		for (Instance* child : Children) {
			child->Update();
		}

		if (CropDescendants) {
			EndScissorMode();
		}

		if (SliderTransparency != 1 and SliderSize != 0) {

			if (CanvasSize.y > 1) {
				if (Direction == 'Y' or Direction == 'B') {
					float sliderHeight = RealSize.y * (1.0f / CanvasSize.y);
					float sliderY = RealPosition.y + (RealSize.y - sliderHeight) * (CanvasPosition.y / (CanvasSize.y - 1));
					Vector2 firstPoint = { RealPosition.x + RealSize.x - SliderSize * 0.6f, sliderY };
					Vector2 secondPoint = { firstPoint.x, sliderY + sliderHeight };
					DrawLineEx(firstPoint, secondPoint, SliderSize, { SliderColor.r, SliderColor.g, SliderColor.b, (unsigned char)(SliderColor.a * (1 - SliderTransparency)) });
				}
			}

			if (CanvasSize.x > 1) {
				if (Direction == 'X' or Direction == 'B') {
					float sliderWidth = RealSize.x * (1.0f / CanvasSize.x);
					float sliderX = RealPosition.x + (RealSize.x - sliderWidth) * (CanvasPosition.x / (CanvasSize.x - 1));
					Vector2 firstPoint = { sliderX, RealPosition.y + RealSize.y - SliderSize * 0.6f };
					Vector2 secondPoint = { sliderX + sliderWidth, firstPoint.y };
					DrawLineEx(firstPoint, secondPoint, SliderSize, { SliderColor.r, SliderColor.g, SliderColor.b, (unsigned char)(SliderColor.a * (1 - SliderTransparency)) });
				}
			}
		}
	}

	void Update() override {
		if (!Visible) return;
		if (CanvasSize.x < 1) CanvasSize.x = 1; if (CanvasSize.y < 1) CanvasSize.y = 1;
		if (Direction != 'X' and Direction != 'Y' and Direction != 'B') {
			Direction = 'Y';
		}

		if (updateChildrenZIndex) {
			updateChildren(this);
		}

		Vector2 RealSize = getRealObject2Dsize();
		Vector2 RealPosition = getRealObject2Dposition();

		if (pointInObject(GetMousePosition())) {
			float WheelMove = GetMouseWheelMove();
			if (WheelMove > 0) {
				if (Direction == 'Y' or (!IsKeyDown(KEY_LEFT_SHIFT) and Direction == 'B')) {
					CanvasPosition.y -= ScrollSpeed;
					if (CanvasPosition.y < 0) {
						CanvasPosition.y = 0;
					}
				}
				else if (Direction == 'X' or (IsKeyDown(KEY_LEFT_SHIFT) and Direction == 'B')) {
					CanvasPosition.x -= ScrollSpeed;
					if (CanvasPosition.x < 0) {
						CanvasPosition.x = 0;
					}
				}
			}
			else if (WheelMove < 0) {
				if (Direction == 'Y' or (!IsKeyDown(KEY_LEFT_SHIFT) and Direction == 'B')) {
					CanvasPosition.y += ScrollSpeed;
					if (CanvasPosition.y > CanvasSize.y - 1) {
						CanvasPosition.y = CanvasSize.y - 1;
					}
				}
				else if (Direction == 'X' or (IsKeyDown(KEY_LEFT_SHIFT) and Direction == 'B')) {
					CanvasPosition.x += ScrollSpeed;
					if (CanvasPosition.x > CanvasSize.x - 1) {
						CanvasPosition.x = CanvasSize.x - 1;
					}
				}
			}
		}

		Draw(RealPosition, RealSize);
	}

	ScrollFrame(bool a) : Instance(a), Object2D(a) { Name = DefaultName; Class = DefaultClass; };
	ScrollFrame(Instance* p) : Instance(p), Object2D(p) { Name = DefaultName; Class = DefaultClass; }

	ScrollFrame() = delete;
};
Vector2 getCanvasPosition(Object2D* obj) {
	ScrollFrame* scra = dynamic_cast<ScrollFrame*>(obj);
	if (scra) return scra->CanvasPosition;
	return { 0,0 };
}

void DrawFrame(Instance* StartInstance) {
	BeginDrawing();

	ClearBackground({ 255,255,255,255 });

	StartInstance->Update();

	EndDrawing();
}

TextLabel* labelFPS = nullptr;

void toggleFPS(Instance* s, Color textColor = { 0,0,0,255 }) {
	if (!labelFPS) {
		labelFPS = new TextLabel(s);
		labelFPS->BackgroundTransparency = 1;
		labelFPS->TextSize = -1;
		labelFPS->SetForTick([&]() { std::ostringstream s; s << GetFPS() << " FPS"; labelFPS->Text = s.str(); });
		labelFPS->Name = "FPS_LABEL";
		labelFPS->Active = false;
		labelFPS->Size = { 0.15, 0.1 };
		labelFPS->Position = { 0.85, 0 };
		labelFPS->TextAnchor = TextAnchorEnum::NE;
		labelFPS->ZIndex = 100000;
		labelFPS->TextColor = { 0,0,0,255 };
		labelFPS->Visible = false;
		labelFPS->TextColor = textColor;
	}

	labelFPS->Visible = !labelFPS->Visible;
}

void updateSignals() {
	for (auto obj : ActiveSignals) {
		if (!obj) continue;
		auto signal = static_cast<ChangedSignal<int>*>(obj);
		signal->Update();
	}
}

void start(Instance& StartInstance, Vector3 inf, std::function<void()> f, std::function<void(float)> f2, const char* name) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	SetTraceLogLevel(LOG_NONE);
	SetTargetFPS(0);

	winWidth = inf.x;
	winHeight = inf.y;

	InitWindow(winWidth / 2, winHeight / 2, name);
	MaximizeWindow();

	SetExitKey(KEY_NULL);
	int codepointsCount = 0;
	int* codepoints = LoadCodepoints(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¨ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß¸àáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ", &codepointsCount);
	ArialFont = LoadFontEx("Fonts/ariblk.ttf", 200, codepoints, codepointsCount);
	SetTextureFilter(ArialFont.texture, TEXTURE_FILTER_TRILINEAR);
	delete(codepoints);

	while (!WindowShouldClose()) {
		winWidth = GetScreenWidth(); winHeight = GetScreenHeight();
		updateSignals();
		dt = GetFrameTime();
		Vector2 mousePosition = GetMousePosition();

		std::function<Instance* (Instance*)> mostHigherActive = [&](Instance* obj) -> Instance* {
			Object2D* mostChild = nullptr;
			for (auto child : obj->Children) {
				if (child->Class == "TextLabel" or child->Class == "ImageLabel" or child->Class == "Object2D" or child->Class == "TextBox") {
					Object2D* z = dynamic_cast<Object2D*>(child);
					if (!z or !z->Active or !z->Visible) continue;
					if (!z->pointInObject(mousePosition)) continue;
					if (!mostChild or z->ZIndex >= mostChild->ZIndex) {
						mostChild = z;
					}
				}
			}

			if (!mostChild) return obj;
			return mostHigherActive(mostChild);

			};

		PreviousHigherObject = higherObject;
		higherObject = dynamic_cast<Object2D*>(mostHigherActive(&StartInstance));

		f();
		f2(dt);

		DrawFrame(&StartInstance);
	}

	for (int i = 0; i < StartInstance.Children.size();) {
		Instance* child = StartInstance.Children[i];
		Delete(child);
	}

	UnloadFont(ArialFont);

	CloseWindow();
}