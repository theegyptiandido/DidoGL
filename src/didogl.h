#pragma once

namespace dg {

enum MatrixTarget { DG_PROJECTION = 1, DG_MODELVIEW = 2 };
enum Primitive { DG_TRIANGLES = 3, DG_QUADS = 4 };

void Init(int width, int height);

void Clear(float r, float g, float b);
void MatrixMode(int mode);
void LoadIdentity();
void Perspective(float fovDeg, float aspect, float znear, float zfar);
void LookAt(float ex, float ey, float ez, float cx, float cy, float cz, float ux, float uy, float uz);
void PushMatrix();
void PopMatrix();
void Translate(float x, float y, float z);
void Rotate(float angleDeg, float x, float y, float z);

void Begin(int mode);
void End();
void Color3f(float r, float g, float b);
void TexCoord2f(float u, float v);
void Vertex3f(float x, float y, float z);

void EnableDepthTest(bool on);
void EnableTexture(bool on);
int  CreateCheckerTexture(int size, int cells);
int  CreateTexture(int w, int h, const unsigned char* rgb, bool nearest);
void BindTexture(int id);

void SwapBuffers();
}
