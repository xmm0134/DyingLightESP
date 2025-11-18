#include"Includes.h"
#include"Menu.h"
typedef HRESULT(__stdcall* tpresent)(IDXGISwapChain* , UINT , UINT );
void* vtable[18];
tpresent opresent;

ID3D11Device* Device;
ID3D11DeviceContext* Devcon;

template<int size>
void NOP(BYTE* src, BYTE* originalBytes) 
{
    DWORD oprotection;
    VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &oprotection);
    for (int i = 0; i < size; i++)
    {
        if (originalBytes)
        {
            originalBytes[i] = src[i];
        }
        src[i] = 0x90;
    }
    VirtualProtect(src, size, oprotection, &oprotection);
}
HRESULT WINAPI hkpresent(IDXGISwapChain* swapchain, UINT syncinterval, UINT Flag) 
{
    if (Menu::imgui_init == false)
    {
        swapchain->GetDevice(__uuidof(Device), (void**)&Device);
        
        Device->GetImmediateContext(&Devcon);

        DXGI_SWAP_CHAIN_DESC dsc;
        swapchain->GetDesc(&dsc);
        HWND hwnd = dsc.OutputWindow;

        ID3D11Texture2D* Backbuffer;

        HRESULT hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&Backbuffer);
        if (FAILED(hr))
        {
            LogError("Get Buffer Failed in imgui init!");
        }
        hr = Device->CreateRenderTargetView(Backbuffer, nullptr, &DirectX::RenderTarget);
        if (FAILED(hr))
        {
            LogError("Create Render TargetView Failed in imgui init");
        }

        if (!Menu::initMenu(Device, Devcon, DirectX::RenderTarget, hwnd))
        {
            LogError("Couldnt initialize imgui!");
        }
        
    }
    Menu::RenderMenu();
    RunEsp(Device, Devcon);

  return opresent(swapchain,syncinterval,Flag);
}

BOOL WINAPI hackthread(DWORD hmodule)
{
    bool AmmoBytes_Patched = false;
    BYTE OriginalAmmoBytes[2];
    MH_Initialize();
    DirectX::init(vtable, sizeof(vtable));
    MH_CreateHook(vtable[8], &hkpresent, (LPVOID*)&opresent);
    MH_EnableHook(vtable[8]);
    Menu::oWndProc = (WNDPROC)SetWindowLongPtr(Menu::hwnd, GWLP_WNDPROC, (LONG_PTR)Menu::WndProc);

    while (true)
    {
        Player Localplayer;
        if (Localplayer.IsHackAbleState())
        {
            if (Menu::MenuVars::Godmode)
            {
                Localplayer.SetHealth(275);
            }
            if (Menu::MenuVars::UnlimitedAmmo)
            {
                if (!AmmoBytes_Patched)
                {
                    NOP<2>((BYTE*)GameModule + Offsets::Writabels::decrease_ammo, OriginalAmmoBytes);
                    AmmoBytes_Patched = true;
                }
                Localplayer.SetAmmo(99);
            }
            if (Menu::MenuVars::InfiniteStamina)
            {
                Localplayer.SetStamina(1.75f);
            }
            if (Menu::MenuVars::InfiniteDurability)
            {
                Localplayer.SetDurability(120);
            }
        }
        Sleep(10);
    }
    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)hackthread, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

