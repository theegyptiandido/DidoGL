#include "engine.h"
#include "platform.h"
#include "didogl.h"

namespace diyqme {

static LARGE_INTEGER s_freq, s_prev;

static float DeltaSeconds() {
    LARGE_INTEGER n;
    QueryPerformanceCounter(&n);
    double dt = (double)(n.QuadPart - s_prev.QuadPart) / (double)s_freq.QuadPart;
    s_prev = n;
    if (dt > 0.1) dt = 0.1;
    return (float)dt;
}

bool Init(const wchar_t* title, int width, int height) {
    if (!platform::CreateGameWindow(title, width, height)) return false;
    dg::Init(width, height);
    QueryPerformanceFrequency(&s_freq);
    QueryPerformanceCounter(&s_prev);
    return true;
}

void Run(void (*update)(float dt), void (*render)()) {
    while (platform::PumpMessages()) {
        update(DeltaSeconds());
        dg::Clear(0.05f, 0.06f, 0.09f);
        render();
        dg::SwapBuffers();
        platform::ClearPressed();
    }
}

void Shutdown() {
}

}
