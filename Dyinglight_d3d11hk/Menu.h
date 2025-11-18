#pragma once
#include<d3d11.h>
#include<windows.h>
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"

namespace Menu 
{
	namespace MenuVars 
	{
		inline bool BoneEsp = false;
		inline bool Boxes = false;
		inline bool Lines = true;
		inline bool NameEsp = true;
		inline bool Godmode = false;
		inline bool InfiniteStamina = false;
		inline bool InfiniteDurability = false;
		inline bool UnlimitedAmmo = false;
	}
	inline bool imgui_init = false;
	inline bool Show_Menu = true;
	inline ID3D11DeviceContext* Devcon;
	inline ID3D11RenderTargetView* RenderTarget;
	inline HWND hwnd;
	bool initMenu(ID3D11Device* Device, ID3D11DeviceContext* context, ID3D11RenderTargetView* RenderTarget,HWND hwnd);
	void RenderMenu();
	LRESULT WINAPI WndProc(const HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
	inline WNDPROC oWndProc = nullptr;
}