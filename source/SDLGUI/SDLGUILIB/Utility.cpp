#include "stdafx.h"

#include "Utility.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <codecvt>				// this is used in ws2s
#include <objbase.h>			// provides CoTaskMemFree
#include <Shlobj.h>				// provides SHGetKnownFolderPath
#include <Knownfolders.h>		// provides FOLDERID_Fonts

namespace sgl
{
	void renderTextAtPos(SDL_Renderer* renderer, std::string textMessage, int posX, int posY, SDL_Color textColor, SDL_Color backgroundColor, int fontSize)
	{
		int width_, height_;

		wchar_t* folderPath;
		SHGetKnownFolderPath(FOLDERID_Fonts, 0, NULL, &folderPath);								// This stores the Windows folder path in folderPath
		auto textFont = TTF_OpenFont( (ws2s(folderPath) + "\\Arial.ttf").c_str() , fontSize);	// We have to convert folderPath to string
		CoTaskMemFree(static_cast<void*>(folderPath));											// Manually free folderPath

		if (textFont == NULL)
		{
			std::cerr << "Unable to open font! Error: " << TTF_GetError() << std::endl;
		} 
		else
		{
			auto surfaceMessage = TTF_RenderText_Solid(textFont, textMessage.c_str(), textColor);
			if (surfaceMessage == NULL)
			{
				std::cerr << "Unable to create surface from message! Error: " << SDL_GetError() << std::endl;
			}
			else
			{
				// Get width and height from surface so we don't have to use SDL_QueryTexture
				width_ = surfaceMessage->w;
				height_ = surfaceMessage->h;

				auto textureMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
				if (textureMessage == NULL)
				{
					std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
				}
				else
				{
					// Copy texture to renderer
					SDL_Rect destRect = { posX, posY, width_, height_ };
					SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
					SDL_RenderFillRect(renderer, &destRect);
					SDL_RenderCopy(renderer, textureMessage, NULL, &destRect);

					// Free resources
					SDL_DestroyTexture(textureMessage);
				}
				SDL_FreeSurface(surfaceMessage);
			}
			TTF_CloseFont(textFont);
		}
	}

	std::string ws2s(const std::wstring& wstr)
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}
}
