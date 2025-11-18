#include<windows.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")


#include<d3d11.h>
#include<d3dcompiler.h>
#include"Vectors.h"

#include"SpriteFont.h"
#include"SpriteBatch.h"
#include<iostream>
#include<memory>
#include"DirectX11.h"

typedef void(__fastcall* tPointToScreen)(void* thisptr, Vector2* Returned, Vector3* Point);
typedef void(__fastcall* tGetBonePos)(void* Entity, Vector3* Returned, unsigned char index);
static const uintptr_t GameModule = (uintptr_t)GetModuleHandleA("gamedll_x64_rwdi.dll");
static const uintptr_t EngineModule = (uintptr_t)GetModuleHandleA("engine_x64_rwdi.dll");
static const tPointToScreen oPointToScreen = (tPointToScreen)(EngineModule + 0x12e8b0);
static const tGetBonePos oGetBonePose = (tGetBonePos)(EngineModule + 0x143c40);

#include"BoneIDs.h"
#include"ErrorLogger.h"
#include"MinHook.h"
#include"Offsets.h"

#include"Player.h"
#include<vector>
#include"Entity.h"
#include"geom.h"

#include<string>
#include<sstream>
#include"Esp.h"
