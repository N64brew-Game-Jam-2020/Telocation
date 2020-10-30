#include <ultra64.h>

Gfx _alienWorldTexAlign[] = {gsSPEndDisplayList()};

#include "tex_floor.inc.c"

u8 _alienWallLum_i4[] = {
	0xDD, 0xCD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDC, 0xDD, 0xDC, 
	0xCD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDC, 0xDD, 0xCC, 
	0xDD, 0xDD, 0xDD, 0xDD, 0xDC, 0xD9, 0xDD, 0xCC, 0xCD, 
	0xDD, 0xDD, 0xDD, 0x9D, 0xDC, 0xDD, 0xDC, 0xCD, 0xDD, 
	0xCD, 0x9D, 0x9C, 0xDD, 0xDD, 0xCC, 0xCD, 0xDD, 0xD9, 
	0xFD, 0xDD, 0xCD, 0xDD, 0xFD, 0xC9, 0xDD, 0xCC, 0xDD, 
	0xCC, 0xDD, 0xDD, 0xD9, 0xCC, 0xCD, 0xDD, 0xFD, 0xDD, 
	0xCD, 0xDD, 0xFD, 0xCD, 0xDF, 0xFC, 0xCD, 0xCC, 0xDD, 
	0xFF, 0xD9, 0xCC, 0xCD, 0xDD, 0xFD, 0xDC, 0xCD, 0xDD, 
	0xFD, 0xCD, 0xDF, 0xDC, 0xCC, 0xCD, 0xCD, 0xFF, 0xD9, 
	0x9C, 0xCD, 0xDD, 0xFD, 0xDC, 0xCC, 0xDF, 0xD9, 0xCC, 
	0xDF, 0xD9, 0xCD, 0x59, 0xCD, 0x9F, 0xD5, 0x99, 0xCD, 
	0x9F, 0xDD, 0xC9, 0xCC, 0xDF, 0xD9, 0xCC, 0xDF, 0xD9, 
	0x9D, 0x59, 0xCC, 0xFF, 0xD5, 0x59, 0xCD, 0xDF, 0xDC, 
	0x55, 0x9C, 0xDF, 0xD5, 0x9C, 0xDD, 0xD5, 0x9D, 0x55, 
	0x9C, 0xFF, 0xD5, 0x59, 0xCD, 0xDF, 0xDC, 0x55, 0x9C, 
	0xDF, 0xD5, 0x9C, 0xDD, 0x55, 0x9D, 0x55, 0x9C, 0xFD, 
	0xD5, 0x59, 0xCC, 0xDF, 0xDC, 0x65, 0x9C, 0xDF, 0x65, 
	0x9C, 0xDD, 0x65, 0x9D, 0x65, 0x9C, 0xFD, 0x66, 0x59, 
	0xCC, 0xDF, 0xC6, 0x65, 0x9C, 0xDF, 0x66, 0x59, 0xDD, 
	0x66, 0x9D, 0x65, 0x9C, 0xFD, 0x66, 0x59, 0xCC, 0xDF, 
	0xD6, 0x65, 0x9C, 0xDF, 0x66, 0x69, 0xDD, 0x66, 0x9D, 
	0x65, 0x9C, 0xFD, 0x66, 0x59, 0xC9, 0xDF, 0xD6, 0x55, 
	0x9C, 0xDD, 0x66, 0x69, 0xDD, 0x66, 0x9D, 0x66, 0x9C, 
	0xDD, 0x66, 0x59, 0xCC, 0xDD, 0xD6, 0x66, 0x99, 0xDD, 
	0x66, 0x69, 0x9D, 0x56, 0x9D, 0x65, 0x9C, 0xDD, 0x66, 
	0x69, 0xCC, 0xDD, 0xD6, 0x66, 0x59, 0xDD, 0x66, 0x69, 
	0xDD, 0x66, 0x9D, 0x66, 0x9C, 0x9D, 0x66, 0x69, 0x9C, 
	0xFD, 0xD6, 0x66, 0x59, 0xDD, 0x65, 0x69, 0xDD, 0x66, 
	0x9D, 0x66, 0x9C, 0xDD, 0x66, 0x65, 0x9C, 0xFD, 0x66, 
	0x66, 0x59, 0xDD, 0x66, 0x69, 0xDD, 0x66, 0x9D, 0x66, 
	0x99, 0xD6, 0x65, 0x65, 0x9C, 0xFD, 0x65, 0x66, 0x69, 
	0xD9, 0x66, 0x69, 0xDD, 0x66, 0x6D, 0x66, 0x9C, 0xD6, 
	0x66, 0x66, 0x9C, 0xFD, 0x66, 0x66, 0x69, 0xDD, 0x66, 
	0x69, 0xDD, 0x66, 0x6D, 0x66, 0x9C, 0xD6, 0x66, 0x66, 
	0x9C, 0xFD, 0x66, 0x65, 0x69, 0xDD, 0x66, 0x69, 0xDD, 
	0x66, 0x6D, 0x66, 0x9C, 0xD6, 0x66, 0x66, 0x9C, 0xDD, 
	0x66, 0x66, 0x69, 0xDD, 0x66, 0x69, 0x96, 0x66, 0x6D, 
	0x66, 0x9C, 0xD6, 0x66, 0x66, 0x9C, 0x9D, 0x66, 0x66, 
	0x69, 0xDD, 0x66, 0x69, 0x96, 0x56, 0x6D, 0x66, 0x9D, 
	0xD6, 0x66, 0x66, 0x9C, 0xDD, 0x66, 0x66, 0x69, 0xDD, 
	0x56, 0x69, 0x96, 0x66, 0x66, 0x66, 0x6D, 0xD6, 0x65, 
	0x66, 0x9C, 0xDD, 0x65, 0x66, 0x69, 0xDD, 0x66, 0x66, 
	0x96, 0x65, 0x65, 0x66, 0x6D, 0x66, 0x66, 0x66, 0x9C, 
	0x99, 0x66, 0x66, 0x69, 0xDD, 0x65, 0x66, 0x96, 0x66, 
	0x66, 0x65, 0x6D, 0x66, 0x66, 0x65, 0x9C, 0xDD, 0x66, 
	0x66, 0x69, 0xDD, 0x66, 0x66, 0x96, 0x66, 0xC6, 0x66, 
	0x6D, 0x56, 0x66, 0x65, 0x9C, 0xD6, 0x66, 0x65, 0x69, 
	0xDD, 0x66, 0x65, 0x95, 0x66, 0xC6, 0x66, 0x6D, 0x66, 
	0xC6, 0x65, 0x9C, 0xD6, 0xC6, 0x66, 0x59, 0xD6, 0x66, 
	0xC6, 0x96, 0x65, 0xCC, 0x66, 0x6D, 0x66, 0xC6, 0x56, 
	0x5D, 0x95, 0xC6, 0x66, 0x9D, 0xD6, 0x65, 0xC6, 0x96, 
	0x59, 0xCC, 0x65, 0x66, 0x65, 0xCC, 0x66, 0x5D, 0x95, 
	0x96, 0x66, 0x9C, 0xD6, 0x59, 0xC6, 0x66, 0x59, 0xCC, 
	0x66, 0x66, 0x59, 0xCC, 0x66, 0x5D, 0x99, 0xCC, 0x66, 
	0xCC, 0xD5, 0x59, 0xCC, 0x65, 0x99, 0xCC, 0xC6, 0x65, 
	0x99, 0xCC, 0xC6, 0x59, 0x99, 0xCC, 0xCC, 0xCC, 
};

u8 _alienUnderhang_ci4[] = {
	0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 
	0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x11, 
	0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x11, 0x10, 
	0x0, 0x0, 0x0, 0x20, 0x1, 0x0, 0x1, 0x10, 0x0, 
	0x10, 0x20, 0x21, 0x0, 0x0, 0x11, 0x10, 0x0, 0x2, 
	0x30, 0x0, 0x10, 0x0, 0x30, 0x12, 0x0, 0x11, 0x0, 
	0x11, 0x0, 0x0, 0x2, 0x11, 0x10, 0x0, 0x30, 0x0, 
	0x10, 0x0, 0x30, 0x10, 0x3, 0x31, 0x10, 0x11, 0x0, 
	0x33, 0x2, 0x11, 0x10, 0x0, 0x30, 0x1, 0x10, 0x0, 
	0x30, 0x10, 0x3, 0x1, 0x11, 0x10, 0x10, 0x33, 0x2, 
	0x21, 0x10, 0x0, 0x30, 0x1, 0x11, 0x3, 0x2, 0x11, 
	0x3, 0x2, 0x10, 0x42, 0x10, 0x23, 0x4, 0x22, 0x10, 
	0x23, 0x0, 0x12, 0x11, 0x3, 0x2, 0x11, 0x3, 0x2, 
	0x20, 0x42, 0x11, 0x33, 0x4, 0x42, 0x10, 0x3, 0x1, 
	0x44, 0x21, 0x3, 0x4, 0x21, 0x0, 0x4, 0x20, 0x44, 
	0x21, 0x33, 0x4, 0x42, 0x10, 0x3, 0x1, 0x44, 0x21, 
	0x3, 0x4, 0x21, 0x0, 0x44, 0x20, 0x44, 0x21, 0x30, 
	0x4, 0x42, 0x11, 0x3, 0x1, 0x44, 0x21, 0x3, 0x44, 
	0x21, 0x0, 0x44, 0x20, 0x44, 0x21, 0x30, 0x44, 0x42, 
	0x11, 0x3, 0x14, 0x44, 0x21, 0x3, 0x44, 0x42, 0x0, 
	0x44, 0x20, 0x44, 0x21, 0x30, 0x44, 0x42, 0x11, 0x3, 
	0x4, 0x44, 0x21, 0x3, 0x44, 0x42, 0x0, 0x44, 0x20, 
	0x44, 0x21, 0x30, 0x44, 0x42, 0x12, 0x3, 0x4, 0x44, 
	0x21, 0x0, 0x44, 0x42, 0x0, 0x44, 0x20, 0x44, 0x21, 
	0x0, 0x44, 0x42, 0x11, 0x0, 0x4, 0x44, 0x22, 0x0, 
	0x44, 0x42, 0x20, 0x44, 0x20, 0x44, 0x21, 0x0, 0x44, 
	0x42, 0x11, 0x0, 0x4, 0x44, 0x42, 0x0, 0x44, 0x42, 
	0x0, 0x44, 0x20, 0x44, 0x21, 0x20, 0x44, 0x42, 0x21, 
	0x30, 0x4, 0x44, 0x42, 0x0, 0x44, 0x42, 0x0, 0x44, 
	0x20, 0x44, 0x21, 0x0, 0x44, 0x44, 0x21, 0x30, 0x44, 
	0x44, 0x42, 0x0, 0x44, 0x42, 0x0, 0x44, 0x20, 0x44, 
	0x22, 0x4, 0x44, 0x44, 0x21, 0x30, 0x44, 0x44, 0x42, 
	0x2, 0x44, 0x42, 0x0, 0x44, 0x40, 0x44, 0x21, 0x4, 
	0x44, 0x44, 0x21, 0x30, 0x44, 0x44, 0x42, 0x0, 0x44, 
	0x42, 0x0, 0x44, 0x40, 0x44, 0x21, 0x4, 0x44, 0x44, 
	0x21, 0x30, 0x44, 0x44, 0x42, 0x0, 0x44, 0x42, 0x0, 
	0x44, 0x40, 0x44, 0x21, 0x4, 0x44, 0x44, 0x21, 0x0, 
	0x44, 0x44, 0x42, 0x0, 0x44, 0x42, 0x24, 0x44, 0x40, 
	0x44, 0x21, 0x4, 0x44, 0x44, 0x21, 0x20, 0x44, 0x44, 
	0x42, 0x0, 0x44, 0x42, 0x24, 0x44, 0x40, 0x44, 0x20, 
	0x4, 0x44, 0x44, 0x21, 0x0, 0x44, 0x44, 0x42, 0x0, 
	0x44, 0x42, 0x24, 0x44, 0x44, 0x44, 0x40, 0x4, 0x44, 
	0x44, 0x21, 0x0, 0x44, 0x44, 0x42, 0x0, 0x44, 0x44, 
	0x24, 0x44, 0x44, 0x44, 0x40, 0x44, 0x44, 0x44, 0x21, 
	0x22, 0x44, 0x44, 0x42, 0x0, 0x44, 0x44, 0x24, 0x44, 
	0x44, 0x44, 0x40, 0x44, 0x44, 0x44, 0x21, 0x0, 0x44, 
	0x44, 0x42, 0x0, 0x44, 0x44, 0x24, 0x44, 0x44, 0x44, 
	0x40, 0x44, 0x44, 0x44, 0x21, 0x4, 0x44, 0x44, 0x42, 
	0x0, 0x44, 0x44, 0x24, 0x44, 0x44, 0x44, 0x40, 0x44, 
	0x44, 0x44, 0x21, 0x4, 0x44, 0x44, 0x42, 0x4, 0x44, 
	0x44, 0x24, 0x44, 0x44, 0x44, 0x40, 0x44, 0x44, 0x44, 
	0x40, 0x44, 0x44, 0x44, 0x44, 0x4, 0x44, 0x44, 0x24, 
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x40, 0x44, 
	0x44, 0x44, 0x44, 0x4, 0x44, 0x44, 0x44, 0x44, 0x44, 
	0x44, 0x44, 0x44, 0x44, 0x44, 0x40, 0x44, 0x44, 0x44, 
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 
	0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 
};

u8 _alienUnderhang_ci4_pal_rgba16[] = {
	0x61, 0xDB, 0x59, 0xD9, 0x41, 0x11, 0x6A, 0x1D, 0x0, 
	0x0, 
};

Gfx _alienFloor_material[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, TEXEL0, 0, SHADE, 0, 0, 0, 0, 1),
	gsDPPipeSync(),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 32, _alienFloorLum_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 126, 252),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 252),
	gsSPEndDisplayList(),
};

Gfx _alienWall_material[] = {
	gsDPPipeSync(),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 16, _alienWallLum_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 62, 124),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx _alienUnderhang_material[] = {
	gsDPPipeSync(),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, _alienUnderhang_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 4),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 16, _alienUnderhang_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 2, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 62, 124),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsDPSetPrimColor(0, 0, 187, 187, 187, 255),
	gsSPEndDisplayList(),
};