#pragma once

namespace Engine
{
	/*
	* @brief Represent the window the game can run on
	*/
	class IWindow
	{
		public:
			virtual ~IWindow() = default;

			/*
			* @brief Updtaes the window
			*/
			virtual void Update() = 0;

			/*
			* @brief return true for one time after the user request to close the window
			* @return True when close was requested
			*/
			virtual bool CloseRequsted() = 0;

			/*
			* @brief Retreive the client width of the window
			* @return width in pixel
			*/
			virtual size_t GetWidth() = 0;

			/*
			* @brief Retreive the client height of the window
			* @return height in pixel
			*/
			virtual size_t GetHeight() = 0;



	};
}
