#include "Rnd/shaderoptions.hpp"
#include "utl/Symbol.h"

Symbol sShaderTypes[26];

void InitShaderOptions(){
    sShaderTypes[0] = "bloom";
    sShaderTypes[25] = "bloom_glare";
    sShaderTypes[1] = "blur";
    sShaderTypes[2] = "depthvolume";
    sShaderTypes[5] = "downsample_depth";
    sShaderTypes[3] = "downsample";
    sShaderTypes[4] = "downsample_4x";
    sShaderTypes[6] = "drawrect";
    sShaderTypes[7] = "error";
    sShaderTypes[8] = "fur";
    sShaderTypes[9] = "line_noz";
    sShaderTypes[10] = "line";
    sShaderTypes[11] = "movie";
    sShaderTypes[13] = "multimesh_bb";
    sShaderTypes[12] = "multimesh";
    sShaderTypes[14] = "particles";
    sShaderTypes[15] = "postproc_error";
    sShaderTypes[16] = "postprocess";
    sShaderTypes[17] = "shadowmap";
    sShaderTypes[18] = "standard";
    sShaderTypes[20] = "unwrapuv";
    sShaderTypes[21] = "velocity_camera";
    sShaderTypes[22] = "velocity_object";
    sShaderTypes[23] = "playerdepth_vis";
    sShaderTypes[24] = "playerdepth_shell";
}

static const char* const unusedShaderStrings[] = {
    "pulse",
    " /D%s=%s",
    " -D%s=%s",
    "shaders/%s.fx",
    "shaders",
    "ps",
    "vs",
    "%s/gen/%s_%llx_%s.%s_%s",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
    "PIXEL_SHADER",
    "HX_XBOX",
    "HX_WIN32",
    "SHOW_SHADER_COST",
    "HX_PS3",
    "HX_PC",
    "ENABLE_DIFFUSE_MAP",
    "ENABLE_NORMAL_MAP",
    "NORM_DETAIL",
    "ENABLE_SPECULAR",
    "ENABLE_SPECULAR_MAP",
    "ENABLE_RIMLIGHT",
    "ENABLE_RIMLIGHT_UNDER",
    "ENABLE_RIMLIGHT_MAP",
    "ENABLE_ENVIRON_MAP",
    "ENABLE_ENVIRON_MAP_FALLOFF",
    "ENABLE_ENVIRON_MAP_SPECMASK",
    "ENABLE_GLOW_MAP",
    "PER_PIXEL_LIGHTING",
    "PRELIT",
    "TEX_GEN",
    "HAS_REAL_LIGHTS",
    "HAS_APPROX_LIGHTS",
    "NUM_PROJ",
    "PROJ_LIGHT_MULTIPLY",
    "NUM_POINT",
    "RESAMP",
    "SKINNED",
    "FOG",
    "SPOTLIGHT",
    "FADE_OUT",
    "SHADOW_BUFFER",
    "ANISOTROPIC",
    "PSEUDO_HDR",
    "POSTERIZE",
    "BILLBOARD",
    "NUM_TAPS",
    "LUMMAP",
    "PARTICLES",
    "SCREEN_ALIGNED",
    "COLORXFM",
    "NOISE",
    "NOISE_MIDTONE",
    "DOF",
    "BLENDPREVIOUS",
    "COPYPREVIOUS",
    "BLOOM",
    "GLARE",
    "KALEIDOSCOPE",
    "HALLOFTIME",
    "MOTIONBLUR",
    "VELOCITY",
    "GRADIENTMAP",
    "REFRACT",
    "REFRACT_WORLD",
    "EXTRUDE",
    "SHAPE",
    "CUSTOM_VARIATION",
    "CHROMATIC_ABERRATION",
    "CHROMATIC_SHARPEN",
    "COLOR_MOD",
    "FUR_DETAIL",
    "DISPLAY_ERROR",
    "VIGNETTE",
    "ENABLE_AO",
    "TONE_MAPPING",
    "SOFT_DEPTH_BLEND",
    "ENABLE_POINT_CUBE_TEX",
    "HI_RES_SCREEN",
    "INTENSIFY",
    "vector"
};
