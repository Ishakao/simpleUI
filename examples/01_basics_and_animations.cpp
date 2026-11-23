#define SIMPLEUI_IMPLEMENTATION
#include "simpleUI.h"

int main() {
    SIMPLEUI_CONTEXT::ChangeWindowColor(Color{ 18, 20, 26, 255 });
    SIMPLEUI_CONTEXT::SetMinimalWindowSize(720, 480);
    SIMPLEUI_CONTEXT::ALLOW_FPS = true;

    Instance* root = GetRoot();

    int cardGrad = CreateGradient(
        { { 0.0f, Color{ 38, 44, 62, 255 } }, { 1.0f, Color{ 24, 27, 38, 255 } } }
    );

    Object2D* card = Object2D::New(root);
    card->Name = "MainCard";
    card->Position = Vector2{ 0.5f, 0.5f };
    card->AnchorPosition = Vector2{ 0.5f, 0.5f };
    card->Size = Vector2{ 0.0f, 0.0f };
    card->SizeOffset = Vector2{ 520.0f, 380.0f };
    card->BackgroundColor = Color{ 255, 255, 255, 255 };
    card->BackgroundGradientIndex = cardGrad;
    card->BackgroundGradientRotation = 135;
    card->Roundness = 0.12f;
    card->BorderThickness = 2;
    card->BorderColor = Color{ 70, 82, 114, 255 };
    card->BorderType = BORDER_OUTER;

    TextLabel* title = TextLabel::New(card);
    title->Name = "Title";
    title->Position = Vector2{ 0.5f, 0.0f };
    title->PositionOffset = Vector2{ 0.0f, 24.0f };
    title->AnchorPosition = Vector2{ 0.5f, 0.0f };
    title->Size = Vector2{ 0.9f, 0.0f };
    title->SizeOffset = Vector2{ 0.0f, 44.0f };
    title->BackgroundTransparency = 1.0f;
    title->Text = "simpleUI showcase";
    title->TextSize = 36;
    title->UsePerSymbolColor = true;
    title->SetPerSymbolColor({
        { 120, 200, 255, 255 }, { 130, 190, 255, 255 }, { 145, 175, 255, 255 },
        { 165, 160, 255, 255 }, { 185, 145, 255, 255 }, { 205, 135, 255, 255 },
        { 255, 130, 195, 255 }, { 255, 150, 160, 255 }, { 255, 255, 255, 255 },
        { 220, 225, 235, 255 }, { 220, 225, 235, 255 }, { 220, 225, 235, 255 },
        { 220, 225, 235, 255 }, { 220, 225, 235, 255 }, { 220, 225, 235, 255 },
        { 220, 225, 235, 255 }, { 220, 225, 235, 255 }
    });

    Object2D* clipBox = Object2D::New(card);
    clipBox->Name = "ClipDemo";
    clipBox->Position = Vector2{ 0.5f, 0.0f };
    clipBox->PositionOffset = Vector2{ 0.0f, 90.0f };
    clipBox->AnchorPosition = Vector2{ 0.5f, 0.0f };
    clipBox->Size = Vector2{ 0.0f, 0.0f };
    clipBox->SizeOffset = Vector2{ 260.0f, 110.0f };
    clipBox->BackgroundColor = Color{ 18, 21, 30, 255 };
    clipBox->Roundness = 0.55f;
    clipBox->BorderThickness = 2;
    clipBox->BorderColor = Color{ 85, 100, 140, 255 };
    clipBox->ClipDescendants = true;

    int stripeGrad = CreateGradient(
        { { 0.0f, Color{ 70, 160, 255, 255 } }, { 1.0f, Color{ 210, 80, 255, 255 } } }
    );

    Object2D* spinner = Object2D::New(clipBox);
    spinner->Name = "Spinner";
    spinner->Position = Vector2{ 0.5f, 0.5f };
    spinner->AnchorPosition = Vector2{ 0.5f, 0.5f };
    spinner->Size = Vector2{ 0.0f, 0.0f };
    spinner->SizeOffset = Vector2{ 320.0f, 34.0f };
    spinner->BackgroundColor = Color{ 255, 255, 255, 255 };
    spinner->BackgroundGradientIndex = stripeGrad;
    spinner->Roundness = 0.4f;
    spinner->AddEvent(TICK, [](Instance* self) {
        Object2D* o = static_cast<Object2D*>(self);
        o->Rotation = std::fmod(o->Rotation + SIMPLEUI_CONTEXT::DeltaTime * 70.0f, 360.0f);
    });

    TextLabel* status = TextLabel::New(card);
    status->Name = "Status";
    status->Position = Vector2{ 0.5f, 1.0f };
    status->PositionOffset = Vector2{ 0.0f, -24.0f };
    status->AnchorPosition = Vector2{ 0.5f, 1.0f };
    status->Size = Vector2{ 0.9f, 0.0f };
    status->SizeOffset = Vector2{ 0.0f, 26.0f };
    status->BackgroundTransparency = 1.0f;
    status->TextColor = Color{ 150, 160, 185, 255 };
    status->TextSize = 18;
    status->Text = "Hover or click the button";

    TextLabel* btn = TextLabel::New(card);
    btn->Name = "ActionButton";
    btn->Position = Vector2{ 0.5f, 0.0f };
    btn->PositionOffset = Vector2{ 0.0f, 240.0f };
    btn->AnchorPosition = Vector2{ 0.5f, 0.0f };
    btn->Size = Vector2{ 0.0f, 0.0f };
    btn->SizeOffset = Vector2{ 200.0f, 52.0f };
    btn->BackgroundColor = Color{ 62, 118, 245, 255 };
    btn->TextColor = Color{ 255, 255, 255, 255 };
    btn->Roundness = 0.35f;
    btn->TextSize = 22;
    btn->Text = "Animate";
    btn->Active = true;

    int clicks = 0;

    btn->AddEvent(MOUSE_ENTER, [](Instance* self) {
        TextLabel* b = static_cast<TextLabel*>(self);
        Animate::SafeAnimation::Create(b, &b->BackgroundColor, 0.15f, Color{ 88, 142, 255, 255 }, Animate::Quad, Animate::Out);
        Animate::SafeAnimation::Create(b, &b->SizeOffset, 0.18f, SpecialVector2{ 218.0f, 56.0f }, Animate::Quad, Animate::Out);
    });

    btn->AddEvent(MOUSE_LEAVE, [](Instance* self) {
        TextLabel* b = static_cast<TextLabel*>(self);
        Animate::SafeAnimation::Create(b, &b->BackgroundColor, 0.15f, Color{ 62, 118, 245, 255 }, Animate::Quad, Animate::Out);
        Animate::SafeAnimation::Create(b, &b->SizeOffset, 0.18f, SpecialVector2{ 200.0f, 52.0f }, Animate::Quad, Animate::Out);
    });

    btn->AddEvent(MOUSE_CLICK, [&clicks, status](Instance* self) {
        TextLabel* b = static_cast<TextLabel*>(self);
        clicks++;
        status->Text = "Clicks: " + std::to_string(clicks);
        status->TextColor = Color{ 130, 235, 175, 255 };

        b->Rotation = 0.0f;
        Animate::SafeAnimation::Create(b, &b->Rotation, 0.45f, 360.0f, Animate::Bounce, Animate::Out);

        int snapshot = clicks;
        Tasks::Task::Create(1.0f, [&clicks, snapshot, status]() {
            if (clicks == snapshot) {
                status->TextColor = Color{ 150, 160, 185, 255 };
            }
        });
    }, MOUSE_LEFT);

    StartNewWindow(root, WindowData{ 960, 600, 0 }, "simpleUI - Basics & Animations");
    return 0;
}