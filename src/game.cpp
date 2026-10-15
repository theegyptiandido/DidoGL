#include "game.h"
#include "didogl.h"
#include "platform.h"

static float g_angle = 0.0f;
static int g_tex = 0;

static void Face(float a0, float a1, float a2, float b0, float b1, float b2,
                 float c0, float c1, float c2, float d0, float d1, float d2) {
    dg::Color3f(1, 1, 1);
    dg::TexCoord2f(0, 0); dg::Vertex3f(a0, a1, a2);
    dg::TexCoord2f(1, 0); dg::Vertex3f(b0, b1, b2);
    dg::TexCoord2f(1, 1); dg::Vertex3f(c0, c1, c2);
    dg::TexCoord2f(0, 1); dg::Vertex3f(d0, d1, d2);
}

void GameInit() {
    g_tex = dg::CreateCheckerTexture(64, 8);
}

void GameUpdate(float dt) {
    g_angle += dt * 45.0f;
}

void GameRender() {
    float aspect = (float)platform::Width() / (float)platform::Height();

    dg::MatrixMode(dg::DG_PROJECTION);
    dg::LoadIdentity();
    dg::Perspective(60.0f, aspect, 0.1f, 100.0f);

    dg::MatrixMode(dg::DG_MODELVIEW);
    dg::LoadIdentity();
    dg::LookAt(3, 3, 4, 0, 0, 0, 0, 1, 0);

    dg::PushMatrix();
    dg::Rotate(g_angle, 1.0f, 1.0f, 0.3f);

    dg::EnableTexture(true);
    dg::BindTexture(g_tex);
    dg::Begin(dg::DG_QUADS);
    Face(-1, -1,  1,  1, -1,  1,  1,  1,  1, -1,  1,  1);
    Face( 1, -1, -1, -1, -1, -1, -1,  1, -1,  1,  1, -1);
    Face(-1, -1, -1, -1, -1,  1, -1,  1,  1, -1,  1, -1);
    Face( 1, -1,  1,  1, -1, -1,  1,  1, -1,  1,  1,  1);
    Face(-1,  1,  1,  1,  1,  1,  1,  1, -1, -1,  1, -1);
    Face(-1, -1, -1,  1, -1, -1,  1, -1,  1, -1, -1,  1);
    dg::End();
    dg::EnableTexture(false);

    dg::PopMatrix();
}
