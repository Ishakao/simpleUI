#define SIMPLEUI_IMPLEMENTATION
#include "simpleUI.h"

int main() {
    SIMPLEUI_CONTEXT::ChangeWindowColor(Color{ 16, 18, 22, 255 });
    SIMPLEUI_CONTEXT::SetMinimalWindowSize(900, 540);
    SIMPLEUI_CONTEXT::ALLOW_FPS = true;
    SIMPLEUI_CONTEXT::ALLOW_DEBUG = true;

    Instance* root = GetRoot();

    TextLabel* header = TextLabel::New(root);
    header->Position = Vector2{ 0.0f, 0.0f };
    header->PositionOffset = Vector2{ 20.0f, 16.0f };
    header->Size = Vector2{ 1.0f, 0.0f };
    header->SizeOffset = Vector2{ -40.0f, 32.0f };
    header->BackgroundTransparency = 1.0f;
    header->TextAnchor = TextAnchorEnum::W;
    header->TextColor = Color{ 210, 220, 235, 255 };
    header->TextSize = 22;
    header->Text = "ScrollFrame (20000 items) & Live GraphBuilder  |  Press F1 for FPS";

    ScrollFrame* list = ScrollFrame::New(root);
    list->Name = "BigList";
    list->Position = Vector2{ 0.0f, 0.0f };
    list->PositionOffset = Vector2{ 20.0f, 60.0f };
    list->Size = Vector2{ 0.42f, 1.0f };
    list->SizeOffset = Vector2{ -28.0f, -80.0f };
    list->BackgroundColor = Color{ 24, 27, 35, 255 };
    list->BorderThickness = 1;
    list->BorderColor = Color{ 55, 62, 82, 255 };
    list->Roundness = 0.04f;
    list->SliderColor = Color{ 120, 140, 190, 255 };
    list->SliderSize = 6;
    list->ScrollSpeed = 0.0f;
    list->ScrollSpeedOffset = 500.0f;
    list->Animated = true;

    constexpr int itemCount = 20000;
    constexpr float itemHeight = 36.0f;
    constexpr float itemGap = 6.0f;
    list->CanvasSize = Vector2{ 0.0f, 0.0f };
    list->CanvasSizeOffset = Vector2{ 0.0f, itemCount * (itemHeight + itemGap) + 12.0f };

    TextLabel* selectedItem = nullptr;

    for (int i = 0; i < itemCount; i++) {
        TextLabel* row = TextLabel::New(list);
        row->Position = Vector2{ 0.0f, 0.0f };
        row->PositionOffset = Vector2{ 10.0f, 8.0f + i * (itemHeight + itemGap) };
        row->Size = Vector2{ 1.0f, 0.0f };
        row->SizeOffset = Vector2{ -28.0f, itemHeight };
        row->BackgroundColor = Color{ 34, 38, 50, 255 };
        row->Roundness = 0.25f;
        row->TextAnchor = TextAnchorEnum::W;
        row->TextColor = Color{ 215, 222, 235, 255 };
        row->TextSize = 18;
        row->Text = "  Item #" + std::to_string(i + 1);
        row->Active = true;

        row->AddEvent(MOUSE_CLICK, [&selectedItem, header, i](Instance* self) {
            if (selectedItem) {
                selectedItem->BackgroundColor = Color{ 34, 38, 50, 255 };
            }
            TextLabel* cur = static_cast<TextLabel*>(self);
            cur->BackgroundColor = Color{ 62, 118, 245, 255 };
            selectedItem = cur;
            header->Text = "Selected Item #" + std::to_string(i + 1) + "  |  Press F1 for FPS";
        }, MOUSE_LEFT);
    }

    Object2D* rightPanel = Object2D::New(root);
    rightPanel->Name = "GraphPanel";
    rightPanel->Position = Vector2{ 0.42f, 0.0f };
    rightPanel->PositionOffset = Vector2{ 8.0f, 60.0f };
    rightPanel->Size = Vector2{ 0.58f, 1.0f };
    rightPanel->SizeOffset = Vector2{ -28.0f, -80.0f };
    rightPanel->BackgroundColor = Color{ 24, 27, 35, 255 };
    rightPanel->BorderThickness = 1;
    rightPanel->BorderColor = Color{ 55, 62, 82, 255 };
    rightPanel->Roundness = 0.04f;

    TextLabel* modeLabel = TextLabel::New(rightPanel);
    modeLabel->PositionOffset = Vector2{ 18.0f, 16.0f };
    modeLabel->SizeOffset = Vector2{ 260.0f, 28.0f };
    modeLabel->BackgroundTransparency = 1.0f;
    modeLabel->TextAnchor = TextAnchorEnum::W;
    modeLabel->TextColor = Color{ 200, 210, 230, 255 };
    modeLabel->TextSize = 20;
    modeLabel->Text = "Mode: Linear";

    ToggleSwitcher* modeToggle = ToggleSwitcher::New(rightPanel);
    modeToggle->Position = Vector2{ 1.0f, 0.0f };
    modeToggle->PositionOffset = Vector2{ -84.0f, 16.0f };
    modeToggle->SizeOffset = Vector2{ 66.0f, 28.0f };
    modeToggle->BackgroundColor = Color{ 44, 50, 66, 255 };
    modeToggle->SliderColor = Color{ 85, 195, 145, 255 };
    modeToggle->AnimationSpeed = 0.18f;
    modeToggle->AnimationFunction = Animate::Quad;
    modeToggle->AnimationEase = Animate::Out;

    GraphBuilder* graph = GraphBuilder::New(rightPanel);
    graph->Name = "LiveGraph";
    graph->Position = Vector2{ 0.0f, 0.0f };
    graph->PositionOffset = Vector2{ 16.0f, 60.0f };
    graph->Size = Vector2{ 1.0f, 1.0f };
    graph->SizeOffset = Vector2{ -32.0f, -76.0f };
    graph->BackgroundColor = Color{ 16, 18, 24, 255 };
    graph->BorderThickness = 1;
    graph->BorderColor = Color{ 45, 52, 68, 255 };
    graph->Roundness = 0.01f;
    graph->Spacing = 4;
    graph->ColumnsRoundness = 0.35f;
    graph->SizeOfLeftInfo = OffsetScale{ 64, 0.0f };
    graph->TextColor = Color{ 170, 180, 200, 255 };

    auto fmtVal = [](long double v) {
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%.1Lf ", v);
        return std::string(buf);
    };
    graph->MinimalValueToTextFunction(fmtVal);
    graph->MaximalValueToTextFunction(fmtVal);

    size_t seqA = graph->CreateSequence("WaveA");
    graph->SetSequenceColor(seqA, Color{ 85, 195, 145, 255 });
    graph->SetSequenceThickness(seqA, 3);

    size_t seqB = graph->CreateSequence("WaveB");
    graph->SetSequenceColor(seqB, Color{ 95, 145, 255, 255 });
    graph->SetSequenceThickness(seqB, 2);

    graph->ColumnarDisplayID = seqA;

    modeToggle->OnToggle([graph, modeLabel](Instance*, bool columnar) {
        graph->GraphType = columnar ? GRAPH_COLUMNAR : GRAPH_LINEAR;
        modeLabel->Text = columnar ? "Mode: Columnar" : "Mode: Linear";
    });

    float phase = 0.0f;
    float accum = 0.0f;
    constexpr size_t maxPoints = 48;

    graph->AddEvent(TICK, [&phase, &accum, seqA, seqB](Instance* self) {
        accum += SIMPLEUI_CONTEXT::DeltaTime;
        if (accum < 0.05f) return;
        accum = 0.0f;
        phase += 0.22f;

        GraphBuilder* g = static_cast<GraphBuilder*>(self);
        long double a = 50.0 + std::sin(phase) * 32.0 + std::sin(phase * 2.7f) * 10.0;
        long double b = 50.0 + std::cos(phase * 0.8f) * 26.0;

        g->AddValueToSequence(seqA, a);
        g->AddValueToSequence(seqB, b);

        if (g->GetSequenceValues(seqA).size() > maxPoints) {
            g->RemoveIndexFromSequence(seqA, 0);
        }
        if (g->GetSequenceValues(seqB).size() > maxPoints) {
            g->RemoveIndexFromSequence(seqB, 0);
        }
    });

    StartNewWindow(root, WindowData{ 1180, 680, 0 }, "simpleUI - ScrollFrame & GraphBuilder");
    return 0;
}