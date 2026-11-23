#define SIMPLEUI_IMPLEMENTATION
#include "simpleUI.h"

static GLuint compileHostShader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    return s;
}

static GLuint createHostProgram() {
    const char* vs = R"(
        #version 460 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec3 aCol;
        uniform float uAngle;
        uniform float uAspect;
        out vec3 vCol;
        void main() {
            float c = cos(uAngle);
            float s = sin(uAngle);
            vec2 p = vec2(aPos.x * c - aPos.y * s, aPos.x * s + aPos.y * c);
            p.x /= uAspect;
            vCol = aCol;
            gl_Position = vec4(p, 0.0, 1.0);
        }
    )";
    const char* fs = R"(
        #version 460 core
        in vec3 vCol;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(vCol, 1.0);
        }
    )";
    GLuint v = compileHostShader(GL_VERTEX_SHADER, vs);
    GLuint f = compileHostShader(GL_FRAGMENT_SHADER, fs);
    GLuint p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);
    glDeleteShader(v);
    glDeleteShader(f);
    return p;
}

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) return 1;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int winW = 1100;
    int winH = 680;
    SDL_Window* window = SDL_CreateWindow("Host OpenGL + simpleUI Embedded", winW, winH, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_GLContext glCtx = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glCtx);
    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
        SDL_GL_DestroyContext(glCtx);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_StartTextInput(window);

    float verts[] = {
         0.0f,   0.55f,  1.0f, 0.35f, 0.45f,
        -0.52f, -0.40f,  0.30f, 0.85f, 0.65f,
         0.52f, -0.40f,  0.35f, 0.55f, 1.0f
    };

    GLuint vao = 0;
    GLuint vbo = 0;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(verts), verts, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 5 * sizeof(float));
    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, 1);
    glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribBinding(vao, 1, 0);

    GLuint prog = createHostProgram();
    GLint angleLoc = glGetUniformLocation(prog, "uAngle");
    GLint aspectLoc = glGetUniformLocation(prog, "uAspect");

    if (!SUI_InitEmbedded(window, winW, winH)) {
        glDeleteProgram(prog);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
        SDL_GL_DestroyContext(glCtx);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SIMPLEUI_CONTEXT::ALLOW_FPS = true;
    Instance* root = GetRoot();

    bool spinning = true;
    bool reversed = false;
    float speed = 1.2f;
    float angle = 0.0f;
    int bgIndex = 0;

    float bgColors[3][3] = {
        { 0.07f, 0.08f, 0.11f },
        { 0.06f, 0.11f, 0.10f },
        { 0.12f, 0.07f, 0.10f }
    };

    Object2D* hud = Object2D::New(root);
    hud->Name = "OverlayHUD";
    hud->PositionOffset = Vector2{ 20.0f, 20.0f };
    hud->SizeOffset = Vector2{ 280.0f, 236.0f };
    hud->BackgroundColor = Color{ 18, 21, 28, 255 };
    hud->BackgroundTransparency = 0.18f;
    hud->BorderThickness = 1;
    hud->BorderColor = Color{ 70, 82, 110, 255 };
    hud->Roundness = 0.08f;
    hud->Active = true;

    TextLabel* title = TextLabel::New(hud);
    title->PositionOffset = Vector2{ 16.0f, 14.0f };
    title->SizeOffset = Vector2{ 248.0f, 28.0f };
    title->BackgroundTransparency = 1.0f;
    title->TextAnchor = TextAnchorEnum::W;
    title->TextColor = Color{ 230, 235, 245, 255 };
    title->TextSize = 20;
    title->Text = "Embedded HUD";

    auto makeRowLabel = [hud](const std::string& text, float y) {
        TextLabel* l = TextLabel::New(hud);
        l->PositionOffset = Vector2{ 16.0f, y };
        l->SizeOffset = Vector2{ 150.0f, 26.0f };
        l->BackgroundTransparency = 1.0f;
        l->TextAnchor = TextAnchorEnum::W;
        l->TextColor = Color{ 175, 185, 205, 255 };
        l->TextSize = 18;
        l->Text = text;
        return l;
    };

    makeRowLabel("Rotate", 58.0f);
    ToggleSwitcher* spinToggle = ToggleSwitcher::New(hud);
    spinToggle->PositionOffset = Vector2{ 204.0f, 58.0f };
    spinToggle->SizeOffset = Vector2{ 58.0f, 26.0f };
    spinToggle->BackgroundColor = Color{ 42, 48, 64, 255 };
    spinToggle->SliderColor = Color{ 85, 195, 145, 255 };
    spinToggle->AnimationSpeed = 0.16f;
    spinToggle->SetValue(true);
    spinToggle->OnToggle([&spinning](Instance*, bool v) {
        spinning = v;
    });

    makeRowLabel("Reverse", 100.0f);
    ToggleSwitcher* revToggle = ToggleSwitcher::New(hud);
    revToggle->PositionOffset = Vector2{ 204.0f, 100.0f };
    revToggle->SizeOffset = Vector2{ 58.0f, 26.0f };
    revToggle->BackgroundColor = Color{ 42, 48, 64, 255 };
    revToggle->SliderColor = Color{ 95, 145, 255, 255 };
    revToggle->AnimationSpeed = 0.16f;
    revToggle->OnToggle([&reversed](Instance*, bool v) {
        reversed = v;
    });

    TextLabel* speedLabel = makeRowLabel("Speed: 1.2", 146.0f);

    auto makeStepBtn = [hud](const std::string& txt, float x) {
        TextLabel* b = TextLabel::New(hud);
        b->PositionOffset = Vector2{ x, 142.0f };
        b->SizeOffset = Vector2{ 34.0f, 32.0f };
        b->BackgroundColor = Color{ 46, 54, 74, 255 };
        b->TextColor = Color{ 235, 240, 250, 255 };
        b->Roundness = 0.3f;
        b->TextSize = 20;
        b->Text = txt;
        b->Active = true;
        return b;
    };

    auto updateSpeedText = [speedLabel, &speed]() {
        char buf[32];
        std::snprintf(buf, sizeof(buf), "Speed: %.1f", speed);
        speedLabel->Text = buf;
    };

    TextLabel* btnMinus = makeStepBtn("-", 186.0f);
    btnMinus->AddEvent(MOUSE_CLICK, [&speed, updateSpeedText](Instance*) {
        speed = std::max(0.2f, speed - 0.3f);
        updateSpeedText();
    }, MOUSE_LEFT);

    TextLabel* btnPlus = makeStepBtn("+", 228.0f);
    btnPlus->AddEvent(MOUSE_CLICK, [&speed, updateSpeedText](Instance*) {
        speed = std::min(6.0f, speed + 0.3f);
        updateSpeedText();
    }, MOUSE_LEFT);

    TextLabel* hint = TextLabel::New(hud);
    hint->PositionOffset = Vector2{ 16.0f, 194.0f };
    hint->SizeOffset = Vector2{ 248.0f, 24.0f };
    hint->BackgroundTransparency = 1.0f;
    hint->TextAnchor = TextAnchorEnum::W;
    hint->TextColor = Color{ 125, 135, 155, 255 };
    hint->TextSize = 15;
    hint->Text = "Click scene to cycle bg | F1 FPS";

    bool running = true;
    uint64_t lastTicks = SDL_GetTicksNS();

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && e.button.button == SDL_BUTTON_LEFT) {
                if (SIMPLEUI_CONTEXT::higherObject == nullptr) {
                    bgIndex = (bgIndex + 1) % 3;
                }
            }
            SIMPLEUI_CORE::ProcessEvent(e);
        }

        uint64_t now = SDL_GetTicksNS();
        float dt = static_cast<float>(now - lastTicks) / 1e9f;
        lastTicks = now;

        if (spinning) {
            angle += dt * speed * (reversed ? -1.0f : 1.0f);
        }

        int fbW = 0;
        int fbH = 0;
        SDL_GetWindowSize(window, &winW, &winH);
        SDL_GetWindowSizeInPixels(window, &fbW, &fbH);

        glViewport(0, 0, fbW, fbH);
        glEnable(GL_DEPTH_TEST);
        glClearColor(bgColors[bgIndex][0], bgColors[bgIndex][1], bgColors[bgIndex][2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(prog);
        glUniform1f(angleLoc, angle);
        glUniform1f(aspectLoc, winH > 0 ? static_cast<float>(winW) / static_cast<float>(winH) : 1.0f);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        SIMPLEUI_CORE::BeginOverlay(winW, winH, fbW, fbH, dt);
        SUI_RenderFrame(root);
        SIMPLEUI_CORE::EndOverlay();

        SDL_GL_SwapWindow(window);
    }

    SUI_ShutdownEmbedded();
    glDeleteProgram(prog);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    SDL_StopTextInput(window);
    SDL_GL_DestroyContext(glCtx);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}