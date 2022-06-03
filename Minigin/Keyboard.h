#pragma once

class Command;

namespace dae
{
	class GameObject;

	enum class KeyboardButton
	{
		A = SDL_SCANCODE_A,
		Z = SDL_SCANCODE_Z,
		E = SDL_SCANCODE_E,
		R = SDL_SCANCODE_R,
		T = SDL_SCANCODE_T,
		Y = SDL_SCANCODE_Y,
		U = SDL_SCANCODE_U,
		I = SDL_SCANCODE_I,
		O = SDL_SCANCODE_O,
		P = SDL_SCANCODE_P,
		Q = SDL_SCANCODE_Q,
		S = SDL_SCANCODE_S,
		D = SDL_SCANCODE_D,
		F = SDL_SCANCODE_F,
		G = SDL_SCANCODE_G,
		H = SDL_SCANCODE_H,
		J = SDL_SCANCODE_J,
		K = SDL_SCANCODE_K,
		L = SDL_SCANCODE_L,
		M = SDL_SCANCODE_M,
		W = SDL_SCANCODE_W,
		X = SDL_SCANCODE_X,
		C = SDL_SCANCODE_C,
		V = SDL_SCANCODE_V,
		B = SDL_SCANCODE_B,
		N = SDL_SCANCODE_N,
		SPACE = SDL_SCANCODE_SPACE,
		LEFTCONTROL = SDL_SCANCODE_LCTRL,
		RIGHTCONTROL = SDL_SCANCODE_RCTRL,
		LEFTSHIFT = SDL_SCANCODE_LSHIFT,
		RIGHTSHIFT = SDL_SCANCODE_RSHIFT,
		ESCAPE = SDL_SCANCODE_ESCAPE,
		DEL = SDL_SCANCODE_DELETE,
		NUMP0 = SDL_SCANCODE_0,
		NUMP1 = SDL_SCANCODE_1,
		NUMP2 = SDL_SCANCODE_2,
		NUMP3 = SDL_SCANCODE_3,
		NUMP4 = SDL_SCANCODE_4,
		NUMP5 = SDL_SCANCODE_5,
		NUMP6 = SDL_SCANCODE_6,
		NUMP7 = SDL_SCANCODE_7,
		NUMP8 = SDL_SCANCODE_8,
		NUMP9 = SDL_SCANCODE_9,
		F1 = SDL_SCANCODE_F1,
		F2 = SDL_SCANCODE_F2,
		F3 = SDL_SCANCODE_F3,
		F4 = SDL_SCANCODE_F4,
		F5 = SDL_SCANCODE_F5,
		F6 = SDL_SCANCODE_F6,
		F7 = SDL_SCANCODE_F7,
		F8 = SDL_SCANCODE_F8,
		F9 = SDL_SCANCODE_F9,
		F10 = SDL_SCANCODE_F10,
		F11 = SDL_SCANCODE_F11,
		F12 = SDL_SCANCODE_F12,
		LEFTARROW = SDL_SCANCODE_LEFT,
		RIGHTARROW = SDL_SCANCODE_RIGHT,
		UPARROW = SDL_SCANCODE_UP,
		DOWNARROW = SDL_SCANCODE_DOWN



	};
	class Keyboard final
	{
	public:
		Keyboard();
		~Keyboard();
		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) = delete;

		void Update();

		bool IsPressed(unsigned int key);
		bool IsDowThisFrame(unsigned int key);
		bool IsUpThisFrame(unsigned int key);

	private:
		int* m_pNumberOfKeys{};
		const Uint8* m_pCurrentState{};
		Uint8* m_pPreviousState{};
	};
}


