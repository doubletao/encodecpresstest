#pragma once
#ifdef VA_PLAYER_API
#define VA_PLAYER_API_EXPORT __declspec(dllexport)
#else
#define VA_PLAYER_API_EXPORT __declspec(dllimport)
#ifdef _USE_VA_PLAYER_LIB
#ifdef _DEBUG
#	pragma comment(lib, "VAPlayerD.lib")
#else
#	pragma comment(lib, "VAPlayerU.lib")
#endif
#endif
#endif // VA_PLAYER_API

#include "IVAPlayer.h"
enum EM_VAPLayer_Type
{
	EM_VAPLayer_SDL,
	EM_VAPLayer_DDraw,
};

VA_PLAYER_API_EXPORT IVAPlayer * CreateVAPlayer(EM_VAPLayer_Type emPlayerType = EM_VAPLayer_SDL);
VA_PLAYER_API_EXPORT bool ReleasePlayer(IVAPlayer *& pPlayer);