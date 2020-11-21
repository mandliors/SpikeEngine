#pragma once

#include <string>

namespace Spike {

	enum MESSAGEBOX_TYPE
	{
		MESSAGEBOX_INFO = 0, MESSAGEBOX_WARNING, MESSAGEBOX_ERROR
	};

	enum MESSAGEBOX_RESULT
	{
		MESSAGEBOX_BUTTON_OK = 0, MESSAGEBOX_BUTTON_YES = 1, MESSAGEBOX_BUTTON_NO = 2, MESSAGEBOX_BUTTON_CANCEL = 3, MESSAGEBOX_FAILED = -1, MESSAGEBOX_CLOSED = -2
	};

	struct MessageBox
	{
		MessageBox() = delete;
		static MESSAGEBOX_RESULT Show(const std::string& title, const std::string& message, MESSAGEBOX_TYPE type = MESSAGEBOX_INFO)
		{
			const SDL_MessageBoxButtonData buttons[] = 
			{
				{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel" },
				{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "No"     },
				{										0, 2, "Yes"    }
			};
			const SDL_MessageBoxColorScheme colorScheme =
			{
				{
					{ 255, 0,  0  }, //background color
					{ 0,  255, 0  }, //text color
					{ 255, 255, 0 }, //button border color
					{ 0,  0,  255 }, //button background
					{ 0, 255, 255 }  //button selected
				}
			};
			const SDL_MessageBoxData mboxData =
			{
				type == MESSAGEBOX_INFO ? SDL_MESSAGEBOX_INFORMATION : type == MESSAGEBOX_WARNING ? SDL_MESSAGEBOX_WARNING : SDL_MESSAGEBOX_ERROR,
				nullptr,
				title.c_str(),
				message.c_str(),
				SDL_arraysize(buttons),
				buttons,
				&colorScheme
			};
			int buttonId;
			if (SDL_ShowMessageBox(&mboxData, &buttonId))
				return MESSAGEBOX_FAILED;
			switch (buttonId)
			{
			case -1:
				return MESSAGEBOX_CLOSED;
				break;
			case 0:
				return MESSAGEBOX_BUTTON_CANCEL;
				break;
			case 1:
				return MESSAGEBOX_BUTTON_NO;
				break;
			case 2:
				return MESSAGEBOX_BUTTON_YES;
				break;
			default:
				return MESSAGEBOX_FAILED;
			}
			//SDL_ShowSimpleMessageBox(NULL, title.c_str(), message.c_str(), nullptr);
		}
	};
}

