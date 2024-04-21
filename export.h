#pragma once

#if defined(WIN32) && defined(RLIMGUI_SHARED_LIB)
#if defined(rlimgui_EXPORTS)
#define RLIMGUI_EXPORT __declspec(dllexport)
#else
#define RLIMGUI_EXPORT __declspec(dllimport)
#endif
#else
#define RLIMGUI_EXPORT
#endif