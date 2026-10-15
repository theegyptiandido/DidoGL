#include "platform.h"
#include "didogl.h"
#include <GL/gl.h>
#include <cmath>
#include <vector>
#include <cstdlib>

namespace dg {

static int g_w = 0, g_h = 0;

static float Len3(float x, float y, float z) { return sqrtf(x * x + y * y + z * z); }

void Init(int width, int height) {
    g_w = width;
    g_h = height;
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.05f, 0.06f, 0.09f, 1.0f);
}

void Clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MatrixMode(int mode) { glMatrixMode(mode == DG_PROJECTION ? GL_PROJECTION : GL_MODELVIEW); }
void LoadIdentity() { glLoadIdentity(); }
void PushMatrix() { glPushMatrix(); }
void PopMatrix() { glPopMatrix(); }
void Translate(float x, float y, float z) { glTranslatef(x, y, z); }
void Rotate(float angleDeg, float x, float y, float z) { glRotatef(angleDeg, x, y, z); }

void Perspective(float fovDeg, float aspect, float znear, float zfar) {
    float f = 1.0f / tanf((fovDeg * 3.14159265f / 180.0f) * 0.5f);
    float m[16] = { 0 };
    m[0] = f / aspect;
    m[5] = f;
    m[10] = (zfar + znear) / (znear - zfar);
    m[11] = -1.0f;
    m[14] = (2.0f * zfar * znear) / (znear - zfar);
    glLoadMatrixf(m);
}

void LookAt(float ex, float ey, float ez, float cx, float cy, float cz, float ux, float uy, float uz) {
    float fx = cx - ex, fy = cy - ey, fz = cz - ez;
    float fl = Len3(fx, fy, fz); fx /= fl; fy /= fl; fz /= fl;

    float sx = fy * uz - fz * uy, sy = fz * ux - fx * uz, sz = fx * uy - fy * ux;
    float sl = Len3(sx, sy, sz); sx /= sl; sy /= sl; sz /= sl;

    float tx = sy * fz - sz * fy, ty = sz * fx - sx * fz, tz = sx * fy - sy * fx;

    float m[16] = {
        sx, tx, -fx, 0.0f,
        sy, ty, -fy, 0.0f,
        sz, tz, -fz, 0.0f,
        -(sx * ex + sy * ey + sz * ez),
        -(tx * ex + ty * ey + tz * ez),
         (fx * ex + fy * ey + fz * ez),
        1.0f
    };
    glLoadMatrixf(m);
}

void Begin(int mode) { glBegin(mode == DG_TRIANGLES ? GL_TRIANGLES : GL_QUADS); }
void End() { glEnd(); }
void Color3f(float r, float g, float b) { glColor3f(r, g, b); }
void TexCoord2f(float u, float v) { glTexCoord2f(u, v); }
void Vertex3f(float x, float y, float z) { glVertex3f(x, y, z); }

void EnableDepthTest(bool on) { if (on) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST); }
void EnableTexture(bool on) { if (on) glEnable(GL_TEXTURE_2D); else glDisable(GL_TEXTURE_2D); }

int CreateCheckerTexture(int size, int cells) {
    std::vector<unsigned char> px(size * size * 3);
    int cell = size / cells;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            bool on = ((x / cell) + (y / cell)) % 2 == 0;
            unsigned char c0 = on ? 210 : 60;
            unsigned char c1 = on ? 220 : 70;
            unsigned char c2 = on ? 180 : 55;
            int i = (y * size + x) * 3;
            px[i + 0] = c0;
            px[i + 1] = c1;
            px[i + 2] = c2;
        }
    }
    GLuint id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, px.data());
    return (int)id;
}

int CreateTexture(int w, int h, const unsigned char* rgb, bool nearest) {
    GLuint id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    GLint filter = nearest ? GL_NEAREST : GL_LINEAR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb);
    return (int)id;
}

void BindTexture(int id) { glBindTexture(GL_TEXTURE_2D, (GLuint)id); }

void SwapBuffers() { platform::SwapBuffers(); }

}
