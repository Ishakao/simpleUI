<h1>simpleUI</h1>

<p>
    <a href="https://github.com/Ishakao/simpleUI"><img src="https://img.shields.io/badge/version-1.0.0-blue.svg" alt="Version"></a>
    <img src="https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey.svg" alt="Platform">
    <img src="https://img.shields.io/badge/license-MIT-green.svg" alt="License">
</p>

<p>A lightweight, high-performance, hardware-accelerated C++ user interface library built on top of Raylib for Windows and Linux systems. It features a complete hierarchical object tree, optimized text rendering, an advanced event system, and native shader integration.</p>

<h2>Features</h2>
<ul>
    <li><strong>Hierarchical Object Tree:</strong> Complete parent-child instance management structure (<code>Instance</code> and <code>Object2D</code>).</li>
    <li><strong>Z-Index &amp; Layer Management:</strong> Strict control over rendering order and input handling priority.</li>
    <li><strong>Optimization:</strong> This library contains a huge number of optimizations, and even a large project can produce thousands of FPS.</li>
    <li><strong>Efficient Event System:</strong> Optimized detection and spatial filtering for interactive elements under the cursor.</li>
</ul>

<h2>Dependencies</h2>
<ul>
    <li>C++20 compliant compiler or higher</li>
    <li>Raylib</li>
    <li>stb_image_write (included header implementation)</li>
</ul>

<h2>Quick Start</h2>
<p><code>simpleUI</code> is a header-only library. Include the header file in your project to start using it.</p>
<p>Example of Hello World with bounce animations and TextBox:</p>

```
#include <simpleUI.h>

int main() {
	Instance* Root = new Instance(true); // True in constructor means that the object is rooted and it has no parents.
	Root->Name = "Root";

	TextLabel* Hello = new TextLabel(Root);
	Hello->AnchorPosition = { 0.5, 0.5 };
	Hello->Position = { 0.5, 0.5 };
	Hello->PositionOFFSET = { -200, 0 };
	Hello->SizeOFFSET = { 340, 80 };
	Hello->SetFont("SegoeB");
	Hello->SetText(" Hello ");
	Hello->Roundness = 0.2;
	Hello->Active = true;
	Hello->BorderThickness = 3;
	Hello->TextColor = { 224, 244, 244, 255 };
	Hello->BorderColor = { 0, 51, 25, 255 };
	Hello->BackgroundColor = { 0, 204, 0, 255 };
	Hello->AddEvent(MOUSE_ENTER, [Hello](Object2D* th) {
		Animate::Create(&Hello->SizeOFFSET, 0.4, { 400, 100 }, Animate::Bounce, Animate::Out);
	});
	Hello->AddEvent(MOUSE_LEAVE, [Hello](Object2D* th) {
		Animate::Create(&Hello->SizeOFFSET, 0.4, { 340, 80 }, Animate::Bounce, Animate::Out);
	});

	TextBox* World = new TextBox(Root);
	World->AnchorPosition = { 0.5, 0.5 };
	World->Position = { 0.5, 0.5 };
	World->PositionOFFSET = { 200, 0 };
	World->SizeOFFSET = { 340, 80 };
	World->font = "SegoeB";
	World->SetText(" World ");
	World->PlaceholderText = " World ";
	World->maxSymbols = 10;
	World->CursorColor = { 0, 102, 102, 255 };
	World->Roundness = 0.2;
	World->Active = true;
	World->BorderThickness = 3;
	World->TextColor = { 224, 244, 244, 255 };
	World->BackgroundColor = { 0, 102, 204, 255 };
	World->BorderColor = { 0, 102, 102, 255 };
	World->AddEvent(MOUSE_ENTER, [World](Object2D* th) {
		Animate::Create(&World->SizeOFFSET, 0.4, { 400, 100 }, Animate::Bounce, Animate::Out);
	});
	World->AddEvent(MOUSE_LEAVE, [World](Object2D* th) {
		Animate::Create(&World->SizeOFFSET, 0.4, { 340, 80 }, Animate::Bounce, Animate::Out);
	});

	ALLOW_FPS = true; // Allows to show FPS label on F1
	ALLOW_DEBUG = true; // Allows to show debug menu on F2

	addFontToQueqe("SegoeB", "Fonts/segoeuib.ttf", 60); // Loading custom font
	SUI_SetMinimalWindowSize(600, 400);
	start(*Root, { 1200, 800, -1 }, "Test program", "Icon.ico", FLAG_WINDOW_RESIZABLE);
}
```

<h2>Architecture Overview</h2>

<h3>Primary Classes</h3>
<ul>
    <li><strong><code>Instance</code></strong>: The base class responsible for managing the hierarchical tree structure and node relationships.</li>
    <li><strong><code>Object2D</code></strong>: Inherits from <code>Instance</code>. Represents interactive UI elements containing spatial attributes, visibility toggles, and Z-index values.</li>
    <li><strong><code>TextLabel</code></strong>: Inherits from <code>Object2D</code>. Can show UTF-8 text with a lot of features.</li>
    <li><strong><code>TextBox</code></strong>: Inherits from <code>Object2D</code>. Can receive input from user. Also have a lot of features.</li>
    <li><strong><code>ScrollFrame</code></strong>: Inherits from <code>Object2D</code>. Represents canvas with different directions.</li>
    <li><strong><code>ImageLabel</code></strong>: Inherits from <code>Object2D</code>. Represents object that can show images.</li>
    <li><strong><code>TextureLabel</code></strong>: Inherits from <code>Object2D</code>. Represents object that can show textures</li>
</ul>
<h2>Every object has a huge amount of customization which allow you to make the interface interesting and individual</h2>
