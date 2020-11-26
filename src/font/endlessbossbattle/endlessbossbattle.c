
#include "endlessbossbattle.h"
#include "tex.inc.c"

struct FontCharacter gEndlessBossBattleCharacters[] = {
    {'A',   3, 1, 7},
    {'B',   10, 1, 7},
    {'C',   17, 1, 7},
    {'D',   24, 1, 7},
    {'E',   31, 1, 7},
    {'F',   38, 1, 7},
    {'G',   45, 1, 7},
    {'H',   52, 1, 7},
    {'I',   59, 1, 3},

    {'J',   3, 12, 5},
    {'K',   8, 12, 7},
    {'L',   15, 12, 6},
    {'M',   21, 12, 8},
    {'N',   29, 12, 7},
    {'O',   36, 12, 7},
    {'P',   43, 12, 7},
    {'Q',   50, 12, 7},
    {'R',   57, 12, 7},

    {'S',   3, 23, 7},
    {'T',   10, 23, 7},
    {'U',   17, 23, 7},
    {'V',   24, 23, 7},
    {'W',   31, 23, 8},
    {'X',   39, 23, 7},
    {'Y',   46, 23, 7},
    {'Z',   53, 23, 7},

    {'a',   3, 34, 7},
    {'b',   10, 34, 7},
    {'c',   17, 34, 7},
    {'d',   24, 34, 7},
    {'e',   31, 34, 7},
    {'f',   38, 34, 7},
    {'g',   45, 34, 7},
    {'h',   52, 34, 7},
    {'i',   59, 34, 3},

    {'j',   1, 45, 5},
    {'k',   6, 45, 7},
    {'l',   13, 45, 3},
    {'m',   16, 45, 9},
    {'n',   25, 45, 7},
    {'o',   32, 45, 7},
    {'p',   39, 45, 7},
    {'q',   46, 45, 7},
    {'r',   53, 45, 5},

    {'s',   3, 56, 7},
    {'t',   10, 56, 7},
    {'u',   17, 56, 7},
    {'v',   24, 56, 7},
    {'w',   31, 56, 9},
    {'x',   40, 56, 7},
    {'y',   47, 56, 7},
    {'z',   54, 56, 7},

    {'.',   3, 67, 3},
    {'!',   6, 67, 5},
    {'?',   11, 67, 7},
    {'$',   18, 67, 7},
    {'#',   25, 67, 7},
    {'%',   32, 67, 7},
    {'-',   46, 67, 7},
    {'_',   53, 67, 7},

    {'0',   39, 67, 7},
    {'1',   3, 78, 4},
    {'2',   7, 78, 7},
    {'3',   14, 78, 7},
    {'4',   21, 78, 7},
    {'5',   28, 78, 7},
    {'6',   35, 78, 7},
    {'7',   42, 78, 7},
    {'8',   49, 78, 7},

    {'9',   3, 89, 7},
    {'"',   10, 89, 6},
    {'\'',  10, 89, 3},
    {',',   16, 89, 3},
    {'(',   19, 89, 4},
    {')',   23, 89, 4},
    {'/',   27, 89, 5},
    {'/',   32, 89, 5},
    {'<',   37, 89, 6},
    {'>',   43, 89, 6},
    {':',   49, 89, 3},
    {'=',   52, 89, 7},

    {'@',   3, 100, 7},
    {'^',   10, 100, 7},
    {' ',   17, 100, 2},

    {'\0',   0, 0, 0},
};

struct Font gEndlessBossBattle;

Gfx gEndlessBossBattleUse[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureLUT(G_TT_NONE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, 32, _endless_boss_battle_ia4),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 126, 508),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 508),
    gsSPEndDisplayList(),
};