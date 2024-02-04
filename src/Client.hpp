#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <vector>
// #include <SDL2> also image and mixer
#include "Game.hpp"

namespace GO{
	class Client{
		
		public:
		
		Client();
		~Client();
		
		void loop();
		
		private:
		
		void _new_game();
		
	};
};

#include "Client.cpp"

#endif
