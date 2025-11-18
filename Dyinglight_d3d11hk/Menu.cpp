#include"Menu.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Menu::RenderMenu() 
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		Show_Menu = !Show_Menu;
	}
	if (Show_Menu)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowSize(ImVec2(600, 450));
		ImGui::Begin("A", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		ImGui::Checkbox("Boxes", &Menu::MenuVars::Boxes);
		ImGui::Checkbox("BoneEsp", &Menu::MenuVars::BoneEsp);
		ImGui::Checkbox("Lines", &Menu::MenuVars::Lines);
		ImGui::Checkbox("NameEsp", &Menu::MenuVars::NameEsp);
		ImGui::Checkbox("Godmode", &Menu::MenuVars::Godmode);
		ImGui::Checkbox("Unlimited Ammo", &Menu::MenuVars::UnlimitedAmmo);
		ImGui::Checkbox("Infinite Stamina", &Menu::MenuVars::InfiniteStamina);
		ImGui::Checkbox("Infinite Weapon Durability", &Menu::MenuVars::InfiniteDurability);

		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		
		
		//Menu::Devcon->OMSetRenderTargets(1, &RenderTarget, nullptr);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}

LRESULT CALLBACK Menu::WndProc(const HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{	
	if (Menu::Show_Menu)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDrawCursor = true;
		io.WantCaptureMouse = true;
		ClipCursor(nullptr);
		SetForegroundWindow(hwnd);
		if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wparam, lparam))
		{
			return true;
		}
		return true;
	}

	return CallWindowProc(oWndProc, hwnd, uMsg, wparam, lparam);
}


bool Menu::initMenu(ID3D11Device* Device, ID3D11DeviceContext* context, ID3D11RenderTargetView* renderTarget, HWND hwnd)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	if (!ImGui_ImplWin32_Init(hwnd))
	{
		return false;
	}
	if (!ImGui_ImplDX11_Init(Device, context))
	{
		return false;
	}
	imgui_init = true;
	ImGuiStyle& style = ImGui::GetStyle();

	Menu::hwnd = hwnd;
	Menu::Devcon = context;
	Menu::RenderTarget = renderTarget;

	style.Colors[ImGuiCol_TitleBg] = ImColor(255, 160, 0);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(255, 160, 0);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(255, 140, 0);
	style.Colors[ImGuiCol_MenuBarBg] = ImColor(255, 157, 0);
	style.Colors[ImGuiCol_Border] = ImColor(255, 160, 0);
	style.Colors[ImGuiCol_CheckMark] = ImColor(255, 160, 0);
	style.Colors[ImGuiCol_FrameBg] = ImColor(54, 52, 47);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(54, 52, 47);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(255, 135, 0);
	style.Colors[ImGuiCol_Button] = ImColor(255, 160, 0);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(255, 175, 0);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(255, 190, 0);
	style.Colors[ImGuiCol_ScrollbarBg] = ImColor(54, 52, 47);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(255, 160, 0);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(255, 210, 0);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(255, 190, 0);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(255, 160, 0);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 190, 0);
	style.Colors[ImGuiCol_Tab] = ImColor(255, 160, 0);
	style.Colors[ImGuiCol_TabHovered] = ImColor(255, 175, 0);
	style.Colors[ImGuiCol_TabActive] = ImColor(255, 190, 0);
	style.Colors[ImGuiCol_Header] = ImColor(255, 160, 0);
	style.Colors[ImGuiCol_HeaderActive] = ImColor(255, 190, 0);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(255, 175, 0);
	style.Colors[ImGuiCol_TextDisabled] = ImColor(255, 150, 0);
	style.Colors[ImGuiCol_TextSelectedBg] = ImColor(255, 180, 0);
	style.Colors[ImGuiCol_ChildBg] = ImColor(82, 76, 61);
	style.Colors[ImGuiCol_PopupBg] = ImColor(54, 52, 47);
	style.Colors[ImGuiCol_Separator] = ImColor(255, 140, 0);
	style.Colors[ImGuiCol_SeparatorActive] = ImColor(255, 190, 0);
	style.Colors[ImGuiCol_SeparatorHovered] = ImColor(255, 165, 0);


	style.WindowRounding = 9.0f;
	style.GrabMinSize = 4.0f;
	style.GrabRounding = 20.0f;
	style.GrabMinSize = 9.0f;
	style.ScrollbarRounding = 6.0f;
	style.TabRounding = 7.0f;
	style.FrameRounding = 6.0f;
	style.ChildRounding = 7.0f;
	style.PopupRounding = 6.0f;
}
