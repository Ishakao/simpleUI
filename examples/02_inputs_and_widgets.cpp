#define SIMPLEUI_IMPLEMENTATION
#include "simpleUI.h"

int main() {
    SIMPLEUI_CONTEXT::ChangeWindowColor(Color{ 16, 18, 22, 255 });
    SIMPLEUI_CONTEXT::SetMinimalWindowSize(820, 560);

    Instance* root = GetRoot();

    Object2D* panel = Object2D::New(root);
    panel->Name = "FormPanel";
    panel->Position = Vector2{ 0.5f, 0.5f };
    panel->AnchorPosition = Vector2{ 0.5f, 0.5f };
    panel->Size = Vector2{ 0.0f, 0.0f };
    panel->SizeOffset = Vector2{ 740.0f, 500.0f };
    panel->BackgroundColor = Color{ 25, 28, 36, 255 };
    panel->Roundness = 0.06f;
    panel->BorderThickness = 2;
    panel->BorderColor = Color{ 70, 130, 255, 255 };

    auto makeLabel = [](Instance* parent, const std::string& text, float x, float y, float w) {
        TextLabel* l = TextLabel::New(parent);
        l->PositionOffset = Vector2{ x, y };
        l->SizeOffset = Vector2{ w, 24.0f };
        l->BackgroundTransparency = 1.0f;
        l->TextAnchor = TextAnchorEnum::W;
        l->TextColor = Color{ 170, 180, 200, 255 };
        l->TextSize = 18;
        l->Text = text;
        return l;
    };

    makeLabel(panel, "Username (max 20 chars)", 28.0f, 24.0f, 260.0f);
    TextLabel* charCount = makeLabel(panel, "0 / 20", 290.0f, 24.0f, 70.0f);
    charCount->TextAnchor = TextAnchorEnum::E;

    TextBox* userBox = TextBox::New(panel);
    userBox->Name = "UsernameBox";
    userBox->PositionOffset = Vector2{ 28.0f, 54.0f };
    userBox->SizeOffset = Vector2{ 332.0f, 40.0f };
    userBox->BackgroundColor = Color{ 18, 20, 27, 255 };
    userBox->BorderThickness = 1;
    userBox->BorderColor = Color{ 60, 68, 88, 255 };
    userBox->Roundness = 0.25f;
    userBox->TextColor = Color{ 235, 240, 250, 255 };
    userBox->PlaceholderText = "Enter name...";
    userBox->PlaceholderTextColor = Color{ 95, 105, 125, 255 };
    userBox->CursorColor = Color{ 235, 240, 250, 255 };
    userBox->TextAnchor = TextAnchorEnum::W;
    userBox->TextSize = 20;
    userBox->MaxSymbols = 20;
    userBox->EnterInputCondition = TEXTBOX_NEXTLINE_NOT_ALLOWED;
    userBox->AddEvent(TEXT_CHANGED, [charCount](Instance* self) {
        TextBox* tb = static_cast<TextBox*>(self);
        size_t len = tb->size() > 0 ? tb->size() - 1 : 0;
        charCount->Text = std::to_string(len) + " / 20";
    });

    makeLabel(panel, "Password", 28.0f, 114.0f, 200.0f);
    TextBox* passBox = TextBox::New(panel);
    passBox->Name = "PasswordBox";
    passBox->PositionOffset = Vector2{ 28.0f, 144.0f };
    passBox->SizeOffset = Vector2{ 252.0f, 40.0f };
    passBox->BackgroundColor = Color{ 18, 20, 27, 255 };
    passBox->BorderThickness = 1;
    passBox->BorderColor = Color{ 60, 68, 88, 255 };
    passBox->Roundness = 0.25f;
    passBox->TextColor = Color{ 235, 240, 250, 255 };
    passBox->PlaceholderText = "Secret...";
    passBox->PlaceholderTextColor = Color{ 95, 105, 125, 255 };
    passBox->CursorColor = Color{ 235, 240, 250, 255 };
    passBox->TextAnchor = TextAnchorEnum::W;
    passBox->TextSize = 20;
    passBox->HideText = '*';
    passBox->EnterInputCondition = TEXTBOX_NEXTLINE_NOT_ALLOWED;

    ToggleSwitcher* showPass = ToggleSwitcher::New(panel);
    showPass->Name = "ShowPasswordToggle";
    showPass->PositionOffset = Vector2{ 294.0f, 150.0f };
    showPass->SizeOffset = Vector2{ 66.0f, 28.0f };
    showPass->BackgroundColor = Color{ 42, 48, 64, 255 };
    showPass->SliderColor = Color{ 70, 130, 255, 255 };
    showPass->AnimationSpeed = 0.18f;
    showPass->AnimationFunction = Animate::Quad;
    showPass->AnimationEase = Animate::Out;
    showPass->OnToggle([passBox](Instance*, bool visible) {
        passBox->HideText = visible ? '\0' : '*';
    });

    makeLabel(panel, "Multiline notes (Enter + scroll)", 28.0f, 208.0f, 332.0f);
    TextBox* notes = TextBox::New(panel);
    notes->Name = "NotesBox";
    notes->PositionOffset = Vector2{ 28.0f, 238.0f };
    notes->SizeOffset = Vector2{ 332.0f, 230.0f };
    notes->BackgroundColor = Color{ 18, 20, 27, 255 };
    notes->BorderThickness = 1;
    notes->BorderColor = Color{ 60, 68, 88, 255 };
    notes->Roundness = 0.08f;
    notes->Type = TEXTBOX_VIEWPORTED_XY;
    notes->VPScrollSpeed = 72;
    notes->VPScrollEnabled = true;
    notes->VPAnimated = true;
    notes->TextColor = Color{ 225, 230, 240, 255 };
    notes->PlaceholderText = "Type multiline text...\nCtrl+V works too.";
    notes->PlaceholderTextColor = Color{ 95, 105, 125, 255 };
    notes->CursorColor = Color{ 235, 240, 250, 255 };
    notes->TextAnchor = TextAnchorEnum::NW;
    notes->TextSize = 19;
    notes->EnterInputCondition = TEXTBOX_NEXTLINE_ENTER;

    makeLabel(panel, "Accent color (Radio)", 400.0f, 24.0f, 300.0f);

    Color accents[3] = {
        Color{ 70, 130, 255, 255 },
        Color{ 65, 200, 130, 255 },
        Color{ 235, 100, 130, 255 }
    };
    int accentIndex = 0;

    CheckBox* radio = CheckBox::New(panel);
    radio->Name = "AccentRadio";
    radio->PositionOffset = Vector2{ 400.0f, 58.0f };
    radio->SizeOffset = Vector2{ 300.0f, 130.0f };
    radio->BackgroundTransparency = 1.0f;
    radio->MultiChoice = false;
    radio->AnimationSpeed = 0.18f;
    radio->AnimationFunction = Animate::Quad;
    radio->AnimationEase = Animate::Out;

    CheckBoxItemVisual radioVis;
    radioVis.FalseButtonBorderColor = Color{ 110, 120, 145, 255 };
    radioVis.TrueButtonBorderColor = Color{ 230, 235, 245, 255 };

    radioVis.TrueButtonColor = accents[0];
    int idBlue = radio->AddItem("Blue", radioVis);
    radioVis.TrueButtonColor = accents[1];
    int idGreen = radio->AddItem("Green", radioVis);
    radioVis.TrueButtonColor = accents[2];
    int idRose = radio->AddItem("Rose", radioVis);
    radio->SetValue(idBlue, true);

    radio->OnToggle([&accentIndex, idBlue, idGreen, idRose](Instance*, int id, bool val) {
        if (!val) return;
        if (id == idBlue) accentIndex = 0;
        else if (id == idGreen) accentIndex = 1;
        else if (id == idRose) accentIndex = 2;
    });

    SafeChangedSignal<int>::New(panel, accentIndex, [&accentIndex, &accents, panel, showPass]() {
        Color c = accents[accentIndex];
        Animate::SafeAnimation::Create(panel, &panel->BorderColor, 0.2f, c, Animate::Quad, Animate::Out);
        Animate::SafeAnimation::Create(showPass, &showPass->SliderColor, 0.2f, c, Animate::Quad, Animate::Out);
    });

    makeLabel(panel, "Options (MultiChoice)", 400.0f, 208.0f, 300.0f);

    CheckBox* checks = CheckBox::New(panel);
    checks->Name = "OptionsCheckBox";
    checks->PositionOffset = Vector2{ 400.0f, 242.0f };
    checks->SizeOffset = Vector2{ 300.0f, 150.0f };
    checks->BackgroundTransparency = 1.0f;
    checks->MultiChoice = true;
    checks->MultiChoiceRoundness = 0.35f;
    checks->AnimationSpeed = 0.15f;

    CheckBoxItemVisual checkVis;
    checkVis.TrueButtonColor = Color{ 90, 175, 255, 255 };
    checkVis.TrueButtonBorderColor = Color{ 90, 175, 255, 255 };
    checkVis.FalseButtonBorderColor = Color{ 100, 110, 130, 255 };

    int optA = checks->AddItem("Enable VSync", checkVis);
    int optB = checks->AddItem("Show FPS (F1)", checkVis);
    int optC = checks->AddItem("Debug Menu (F2)", checkVis);

    TextLabel* summary = makeLabel(panel, "Active flags: 0", 400.0f, 430.0f, 300.0f);

    checks->OnToggle([checks, optA, optB, optC, summary](Instance*, int id, bool val) {
        if (id == optB) SIMPLEUI_CONTEXT::ALLOW_FPS = val;
        if (id == optC) SIMPLEUI_CONTEXT::ALLOW_DEBUG = val;
        int count = (checks->GetValue(optA) ? 1 : 0) + (checks->GetValue(optB) ? 1 : 0) + (checks->GetValue(optC) ? 1 : 0);
        summary->Text = "Active flags: " + std::to_string(count);
    });

    StartNewWindow(root, WindowData{ 960, 620, 0 }, "simpleUI - Inputs & Widgets");
    return 0;
}