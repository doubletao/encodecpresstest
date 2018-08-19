#include "stdafx.h"
#include "VAPlayerExport.h"
#include "SDL_VAPlayer.h"

VA_PLAYER_API_EXPORT IVAPlayer * CreateVAPlayer(EM_VAPLayer_Type emPlayerType)
{
	IVAPlayer * pPlayer = nullptr;
	switch (emPlayerType)
	{
	case EM_VAPLayer_SDL:
		pPlayer = new SDL_VAPlayer;
		break;
	case EM_VAPLayer_DDraw:
		break;
	default:
		break;
	}
	return pPlayer;
}

VA_PLAYER_API_EXPORT bool ReleasePlayer(IVAPlayer *& pPlayer)
{
	if (pPlayer)
	{
		pPlayer->ReleasePlayer();
		delete pPlayer;
		pPlayer = nullptr;
	}
	return true;
}
