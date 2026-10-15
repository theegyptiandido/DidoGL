#include "engine.h"
#include "game.h"

int main() {
    if (!diyqme::Init(L"DidYouCallForAMinimalEngine? - DidoGL", 800, 600))
        return 1;

    GameInit();
    diyqme::Run(GameUpdate, GameRender);
    diyqme::Shutdown();
    return 0;
}
