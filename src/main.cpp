#define SIMPLEUI_IMPLEMENTATION
#include <simpleUI.h>

int main() {
	Instance* Root = GetRoot();

    CreateFont("segoe", "Fonts/segoeui.ttf", 64);
	LoadImage("bg_image", "textures/test.jpg"); // add your image path cuz textures was not in simpleUI repo

	ImageLabel* Background = ImageLabel::New(Root);
	Background->Size = { 1,1 };
	Background->BackgroundColor = { 15, 24, 36, 255 };
	Background->SetImage("bg_image");
	Background->Overlay = IMAGE_STRETCH;
	Background->ImageTransparency = 0.9;

	TextLabel* Tryf1f2 = TextLabel::New(Background);
	Tryf1f2->AnchorPosition = { 0.5, 0 };
	Tryf1f2->Position = { 0.5, 0 };
	Tryf1f2->SizeOFFSET = { 500, 0 };
	Tryf1f2->Size.y = 0.07;
	Tryf1f2->FontFace = "segoe";
	Tryf1f2->Text = " Try F1 and F2 binds "; 
	Tryf1f2->TextColor = { 224, 244, 244, 255 };
	Tryf1f2->TextTransparency = 0.7;
	Tryf1f2->BackgroundTransparency = 1;

	TextLabel* Hello = TextLabel::New(Background);
	Hello->AnchorPosition = { 0.5, 0.5 };
	Hello->Position = { 0.5, 0.5 };
	Hello->PositionOFFSET = { -200, 0 };
	Hello->SizeOFFSET = { 340, 80 };
	Hello->FontFace = "segoe";
	Hello->Text = " Hello "; 
	Hello->Roundness = 0.2;
	Hello->Active = true;
	Hello->BorderThickness = 3;
	Hello->TextColor = { 224, 244, 244, 255 };
	Hello->BorderColor = { 0, 51, 25, 255 };
	Hello->BackgroundColor = { 0, 204, 0, 255 };
	Hello->AddEvent(MOUSE_ENTER, [Hello](Instance* th) {
		Animate::Animation::Create(&Hello->SizeOFFSET, 0.4, SpecialVector2{ 400, 100 }, Animate::Bounce, Animate::Out);
		Animate::Animation::Create(&Hello->Roundness, 0.4, 1, Animate::Bounce, Animate::Out);
		Animate::Animation::Create(&Hello->Rotation, 0.4, 10, Animate::Bounce, Animate::Out);
	});
	Hello->AddEvent(MOUSE_LEAVE, [Hello](Instance* th) {
		Animate::Animation::Create(&Hello->SizeOFFSET, 0.4, SpecialVector2{ 340, 80 }, Animate::Bounce, Animate::Out);
		Animate::Animation::Create(&Hello->Roundness, 0.4, 0.2, Animate::Bounce, Animate::Out);
		Animate::Animation::Create(&Hello->Rotation, 0.4, 0, Animate::Bounce, Animate::Out);
	});
	Hello->AddEvent(MOUSE_CLICK, [Hello](Instance* th) { 
		for (int i = 0; i < 5; i++) {
			// Tasks::Task, task which will call lambda function on timer end. Can be canceled while timer > 0
			Tasks::Task::Create(0.1 * i, [Hello, i]() {
				Hello->Text += std::to_string(i+1);
			});
		}
	}, MOUSE_LEFT);
	Hello->AddEvent(TEXT_CHANGED, [Hello](Instance* th) { std::cout << Hello->Text.c_str() << std::endl; });

	TextBox* World = TextBox::New(Background);
	World->AnchorPosition = { 0.5, 0.5 };
	World->Position = { 0.5, 0.5 };
	World->PositionOFFSET = { 200, 0 };
	World->SizeOFFSET = { 340, 80 };
	World->FontFace = "segoe";
	World->Text = "";
	World->PlaceholderText = " World ";
	World->MaxSymbols = 10;
	World->CursorColor = { 0, 102, 102, 255 };
	World->Roundness = 0.2;
	World->Active = true;
	World->BorderThickness = 3;
	World->TextColor = { 224, 244, 244, 255 };
	World->BackgroundColor = { 0, 102, 204, 255 };
	World->BorderColor = { 0, 102, 102, 255 };
	World->AddEvent(MOUSE_ENTER, [World](Instance* th) {
		// SafeAnimation linked to object World. This animation will be deleted when World deletes
		Animate::SafeAnimation::Create(World, &World->SizeOFFSET, 0.4, SpecialVector2{ 400, 100 }, Animate::Bounce, Animate::Out); 
		Animate::Animation::Create(&World->Rotation, 0.4, -10, Animate::Bounce, Animate::Out);
	});
	World->AddEvent(MOUSE_LEAVE, [World](Instance* th) {
		Animate::SafeAnimation::Create(World, &World->SizeOFFSET, 0.4, SpecialVector2{ 340, 80 }, Animate::Bounce, Animate::Out);
		Animate::Animation::Create(&World->Rotation, 0.4, 0, Animate::Bounce, Animate::Out);
	});
	World->AddEvent(CHILD_ADDED, [](Instance* th, Instance* child) {
		std::cout << "Child added " << child->Name << std::endl;
	});
	World->AddEvent(TEXT_CHANGED, [World](Instance* th) { std::cout << !World->Text << std::endl; });

	SIMPLEUI_GLOBAL::ALLOW_FPS = true; // Allows to show FPS label on F1
	SIMPLEUI_GLOBAL::ALLOW_DEBUG = true; // Allows to show debug menu on F2

	SUI_SetMinimalWindowSize(600, 400);
	StartNewWindow(Root, { 1200, 800, -1 }, "Test program", "textures/test.jpg", FLAG_WINDOW_RESIZABLE);
}
