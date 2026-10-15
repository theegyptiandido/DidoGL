#pragma once

namespace diyqme {
bool Init(const wchar_t* title, int width, int height);
void Run(void (*update)(float dt), void (*render)());
void Shutdown();
}
