// modified by 13yz


// Include

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include "imgui_internal.h"
#include "byte.h"
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// Include End

float dpi_scale = 1.f;

// ImFont Setup

ImFont* iconfont = nullptr;
ImFont* gilroy_big = nullptr;
ImFont* gilroy_mini = nullptr;
static bool theme = false;
ImVec2 pos;
ImDrawList* draw;

// ImFont Setup End

// Preview Menu Item Setups

IDirect3DTexture9* logggo = nullptr;
static bool checkboxfalse = false;
static bool checkboxtrue = true;
static int sliderint;
static int comboint;
static char inputtext[64] = { 0 };

// Preview Menu Item Setups End

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static int tabs = 0;
static int subtabs = 0;

// Main code, Tabs Setup

void LegitTab()
{
    ImGui::SetCursorPos(ImVec2(140, 40));
    ImGui::BeginChild("general", ImVec2(150, 200));
    {
        ImGui::BeginGroup();
        ImGui::Checkbox("Checkbox", &checkboxfalse);
        ImGui::SliderInt("SliderInt", &sliderint, 0, 100);
        ImGui::Combo("Combo", &comboint, ("Head\0\rBody\0\rLegs\0\0"));
        ImGui::Button("Button", ImVec2(97, 20));
        ImGui::EndGroup();
    }
    ImGui::EndChild();
}

void VisualsTab()
{

}

void PlayersTab()
{

}

void MiscellaneousTab()
{

}

void ConfigTab()
{

}

// Tabs Setup End

int main(int, char**)
{
    // Create application window
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("Main"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGuiStyle* style = &ImGui::GetStyle();

    ImGui::StyleColorsDark();

    style->Alpha = 1.f;
    style->WindowRounding = 5;
    style->FramePadding = ImVec2(4, 3);
    style->WindowPadding = ImVec2(0, 0);
    style->ItemInnerSpacing = ImVec2(4, 4);
    style->ItemSpacing = ImVec2(8, 10);
    style->FrameRounding = 12;
    style->ScrollbarSize = 2.f;
    style->ScrollbarRounding = 12.f;
    style->PopupRounding = 0.f;
    //style->Rounding = 11.f;


    ImVec4* colors = ImGui::GetStyle().Colors;



    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsClassic();

    ImFontConfig font_config;
    font_config.OversampleH = 1; //or 2 is the same
    font_config.OversampleV = 1;
    font_config.PixelSnapH = 1;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x044F, // Cyrillic
        0,
    };

    gilroy_mini = io.Fonts->AddFontFromMemoryTTF((void*)gilroyfont, sizeof(gilroyfont), 10, &font_config, ranges);
    gilroy_big = io.Fonts->AddFontFromMemoryTTF((void*)gilroyfont, sizeof(gilroyfont), 20, &font_config, ranges);
    iconfont = io.Fonts->AddFontFromMemoryTTF((void*)icon, sizeof(icon), 25, &font_config, ranges);
    
    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Our state
    bool show_demo_window = true, loader_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);
    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {

        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_HorizontalScrollbar);
            {
                // Main Menu Draw

                static int x = 545 * dpi_scale, y = 355 * dpi_scale;
                pos = ImGui::GetWindowPos();
                draw = ImGui::GetWindowDrawList();

                ImGui::SetWindowSize(ImVec2(ImFloor(x * dpi_scale), ImFloor(y * dpi_scale)));

                draw->AddRectFilled(pos, ImVec2(pos.x + 545, pos.y + 355), ImColor(17, 17, 17), 9);
                draw->AddRectFilled(pos, ImVec2(pos.x + 545, pos.y + 355), ImGui::GetColorU32(ImGuiCol_WindowBg), 9);
                draw->AddRectFilled(ImVec2(pos.x, pos.y + 30), ImVec2(pos.x + 130, pos.y + 355), ImGui::GetColorU32(ImGuiCol_TabBar), 9, 4);
                draw->AddLine(ImVec2(pos.x, pos.y + 30), ImVec2(pos.x + 545, pos.y + 30), ImColor(17, 17, 17));
                draw->AddRectFilledMultiColor(ImVec2(pos.x, pos.y + 29), ImVec2(pos.x + 545, pos.y + 30), ImColor(30, 163, 121), ImColor(30, 163, 121, 0), ImColor(30, 163, 121, 0), ImColor(30, 163, 121));

                // Main Menu Draw End

                // Logo

                if (logggo == nullptr)
                    D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &logo, sizeof(logo), 500, 500, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &logggo);

                ImGui::SetCursorPos(ImVec2(45, 280));
                ImGui::Image(logggo, ImVec2(40, 40));

                ImGui::SetCursorPos(ImVec2(10, 35));

                draw->AddCircleFilled(ImVec2(pos.x + 65, pos.y + 300), 26.f, ImColor(0, 0, 0, 50), 60.f);
                draw->AddCircle(ImVec2(pos.x + 65, pos.y + 300), 27.f, ImColor(255, 255, 255, 15), 60.f);

                // Logo End


                ImGui::BeginGroup();
                {
                // Tabs

                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 4));
                    if (ImGui::tab("legit", tabs == 0)) tabs = 0;
                    if (ImGui::tab("visuals", tabs == 1)) tabs = 1;
                    if (ImGui::tab("player", tabs == 2)) tabs = 2;
                    if (ImGui::tab("misc", tabs == 3)) tabs = 3;
                    if (ImGui::tab("config", tabs == 4)) tabs = 4;
                    ImGui::PopStyleVar();

                // Tabs End
                }
                ImGui::EndGroup();

                // Render Tabs

                switch (tabs)
                {
                case 0: LegitTab();   break;
                case 1: VisualsTab();   break;
                case 2: PlayersTab();   break;
                case 3: MiscellaneousTab();   break;
                case 4: ConfigTab();   break;
                }

                // Render Tabs End

            }
            ImGui::End();
        }

        // Rendering
        ImGui::EndFrame();
        
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

