#include"Includes.h"
#include"ErrorLogger.h"

bool DirectX::init(void** Vtable, int size) 
{
	ZeroMemory(&swap_desc,sizeof(swap_desc));
	swap_desc.BufferCount = 1;
	swap_desc.OutputWindow = GetForegroundWindow();
	swap_desc.Windowed = TRUE;
	swap_desc.SampleDesc.Count = 1;
	swap_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_desc.BufferUsage = DXGI_SWAP_EFFECT_DISCARD;

	if (D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr, NULL,
		nullptr, NULL, D3D11_SDK_VERSION,
		&swap_desc, &swapChain,
		&device, NULL, nullptr) != S_OK)
	{
		return false;
	}
	memcpy(Vtable, *(void**)swapChain, size);

	return true;
}

bool Drawing::InitDraw(ID3D11Device* Device, ID3D11DeviceContext* Context)
{
	Drawing::Device = Device;
	Drawing::Context = Context;
	HRESULT hr = D3DCompileFromFile(L"C:\\Users\\alib1\\source\\repos\\Dyinglight_d3d11hk\\Dyinglight_d3d11hk\\VertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, &Vertex_ShaderBlob, 0);
	if (FAILED(hr))
	{		
		MessageBoxA(NULL, "Couldnt compile vertex shader!", "Error!", MB_OKCANCEL);
		return false;
	}

	hr = D3DCompileFromFile(L"C:\\Users\\alib1\\source\\repos\\Dyinglight_d3d11hk\\Dyinglight_d3d11hk\\PixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, &Pixel_ShaderBlob, 0);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Couldnt compile Pixel Shader!", "Error!", MB_OKCANCEL);
		return false;
	}

	hr = Device->CreateVertexShader(Vertex_ShaderBlob->GetBufferPointer(), Vertex_ShaderBlob->GetBufferSize(), 0, &VertexShader);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Couldnt Create Vertex Object Shader!", "Error!", MB_OKCANCEL);
		return false;
	}
	hr = Device->CreatePixelShader(Pixel_ShaderBlob->GetBufferPointer(), Pixel_ShaderBlob->GetBufferSize(), 0, &PixelShader);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Couldnt Create Pixel Object Shader!", "Error!", MB_OKCANCEL);
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC input_layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0} ,
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,12, D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	hr = Device->CreateInputLayout(input_layout, 2, Vertex_ShaderBlob->GetBufferPointer(), Vertex_ShaderBlob->GetBufferSize(), &InputLayout);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Couldnt Create input layout!", "Error!", MB_OKCANCEL);
		return false;
	}
	
	if (!InitIndexBuffers())
	{
		LogError("Failed to initilize index buffers!");
		return false;
	}

	Drawing::Initialized = true;
	return true;
}

bool Drawing::InitIndexBuffers()
{
	DWORD LineIndicies[] = {
		2, 4, 3,
		5, 0, 1
	};
	D3D11_BUFFER_DESC LineDsc = { };
	LineDsc.ByteWidth = sizeof(DWORD) * 6;
	LineDsc.Usage = D3D11_USAGE_DEFAULT;
	LineDsc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA LineData = { };
	LineData.pSysMem = LineIndicies;

	DWORD RectIndicies[] = {
		1, 6, 2, 7,
		8, 18, 9, 19,
		16, 11, 17, 12,
		13, 3, 14, 4,

		0, 5, 5, 15,
		15, 10, 10, 0
	};
	D3D11_BUFFER_DESC RectDsc = { };
	RectDsc.ByteWidth = sizeof(DWORD) * 24;
	RectDsc.Usage = D3D11_USAGE_DEFAULT;
	RectDsc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA RectData = { };
	RectData.pSysMem = RectIndicies;

	HRESULT hr = Device->CreateBuffer(&LineDsc, &LineData, &LineIndexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	hr = Device->CreateBuffer(&RectDsc, &RectData, &RectIndexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

void Drawing::BeginFrame()
{
	Context->IASetInputLayout(InputLayout);
	Context->VSSetShader(VertexShader, NULL, NULL);
	Context->PSSetShader(PixelShader, NULL, NULL);
}

void Drawing::DrawLine(Vector2 Src, Vector2 Dst, Vector3 Color)
{
	Vertex verticies[] = {
		{Vector3(Src.x,Src.y,1.0f),Color},
		{Vector3(Dst.x,Dst.y,1.0f),Color}
	};
	UINT stride = sizeof(Vertex);
	ID3D11Buffer* Buffer;
	D3D11_BUFFER_DESC buff_dsc;
	ZeroMemory(&buff_dsc,sizeof(buff_dsc));
	buff_dsc.ByteWidth = stride * 2;
	buff_dsc.Usage = D3D11_USAGE_DEFAULT;
	buff_dsc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data;
	data.SysMemPitch = NULL;
	data.SysMemSlicePitch = NULL;
	data.pSysMem = verticies;

	UINT Offset = 0;
	HRESULT hr = Drawing::Device->CreateBuffer(&buff_dsc, &data, &Buffer);
	if (FAILED(hr))
	{
		MessageBox(NULL,"Couldnt create vertex buffer","ERROR",MB_OK);
	}
	Drawing::Context->IASetVertexBuffers(0, 1, &Buffer, &stride, &Offset);
	Drawing::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	Drawing::Context->Draw(2, 0);
	Buffer->Release();
}

void Drawing::DrawOutLinedLine(Vector2 Src, Vector2 Dst, Vector3 Color)
{

	Vertex verticies[] = {
		{Vector3(Src.x, Src.y, 0.0f), Color}, //Line Src
		{Vector3(Dst.x, Dst.y, 0.0f), Color}, //Line Dst
		{Vector3(Src.x - 1, Src.y - 1, 0.0f), Colors::Black}, //OutLine Src Left
		{Vector3(Src.x + 1, Src.y + 1, 0.0f), Colors::Black}, //OutLine Src Right
		{Vector3(Dst.x - 1, Dst.y - 1, 0.0f), Colors::Black}, //OutLine Dst left
		{Vector3(Dst.x + 1, Dst.y + 1, 0.0f), Colors::Black}  //OutLine Dst Right
	};

	ID3D11Buffer* Buffer;
	D3D11_BUFFER_DESC buff_dsc;
	UINT stride = sizeof(Vertex);
	buff_dsc.ByteWidth = stride * 6;
	buff_dsc.Usage = D3D11_USAGE_DEFAULT;
	buff_dsc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_dsc.CPUAccessFlags = NULL;
	buff_dsc.MiscFlags = NULL;
	buff_dsc.StructureByteStride = NULL;
	D3D11_SUBRESOURCE_DATA buffer_data;
	buffer_data.pSysMem = verticies;
	buffer_data.SysMemPitch = NULL;
	buffer_data.SysMemSlicePitch = NULL;
	
	UINT Offset = 0;
	Device->CreateBuffer(&buff_dsc, &buffer_data, &Buffer);

	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	Context->IASetIndexBuffer(LineIndexBuffer, DXGI_FORMAT_R32_UINT, Offset);
	Context->IASetVertexBuffers(0, 1, &Buffer, &stride, &Offset);
	Context->DrawIndexed(6, 0, 0);
	Buffer->Release();
}

void Drawing::DrawText(Vector2 Point, const char* Text , int StringSize , float Scale , Vector3 Color)
{
	if (!InitFont)
	{
		Spritebatch = std::make_unique<DirectX::SpriteBatch>(Context);
		Spritefont = std::make_unique<DirectX::SpriteFont>(Device, L"C:\\Users\\alib1\\source\\repos\\Dyinglight_d3d11hk\\Dep\\Fonts\\TimesNewRoman.spritefont");
		InitFont = true;
	}
	wchar_t wstr[100];
	DirectX::XMVECTORF32 color = { Color.x, Color.y, Color.z, 1.0f };
	MultiByteToWideChar(437, MB_PRECOMPOSED, Text, StringSize, wstr, 100);
	

	Spritebatch->Begin();
	Spritefont->DrawString(Spritebatch.get(), wstr, DirectX::XMFLOAT2(Point.x, Point.y), color, 0, DirectX::XMFLOAT2(0, 0), Scale);

	Spritebatch->End();
	Context->IASetInputLayout(InputLayout);
	Context->PSSetShader(PixelShader, 0, 0);
	Context->VSSetShader(VertexShader, 0, 0);
}

void Drawing::DrawOutlinedText(Vector2 Point, const char* text, int size, float scale, Vector3 Color)
{
	if (!InitFont)
	{
		Spritebatch = std::make_unique<DirectX::SpriteBatch>(Context);
		Spritefont = std::make_unique<DirectX::SpriteFont>(Device, L"C:\\Users\\alib1\\source\\repos\\Dyinglight_d3d11hk\\Dep\\Fonts\\TimesNewRoman.spritefont");
		InitFont = true;
	}
	wchar_t wstr[100];
	DirectX::XMVECTORF32 color = { Color.x, Color.y, Color.z, 1.0f };
	MultiByteToWideChar(437, MB_PRECOMPOSED, text, size, wstr, 100);

	DirectX::XMVECTOR result = Spritefont->MeasureString(wstr);
	float XWidth = DirectX::XMVectorGetX(result) * scale;
	Point.x -= XWidth / 2;

	Spritebatch->Begin();
	Spritefont->DrawString(Spritebatch.get(), wstr, DirectX::XMFLOAT2(Point.x + 1, Point.y), DirectX::Colors::Black, 0, DirectX::XMFLOAT2(0, 0), scale);
	Spritefont->DrawString(Spritebatch.get(), wstr, DirectX::XMFLOAT2(Point.x - 1, Point.y), DirectX::Colors::Black, 0, DirectX::XMFLOAT2(0, 0), scale);
	Spritefont->DrawString(Spritebatch.get(), wstr, DirectX::XMFLOAT2(Point.x, Point.y + 1), DirectX::Colors::Black, 0, DirectX::XMFLOAT2(0, 0), scale);
	Spritefont->DrawString(Spritebatch.get(), wstr, DirectX::XMFLOAT2(Point.x, Point.y - 1), DirectX::Colors::Black, 0, DirectX::XMFLOAT2(0, 0), scale);


	Spritefont->DrawString(Spritebatch.get(), wstr, DirectX::XMFLOAT2(Point.x, Point.y), color, 0, DirectX::XMFLOAT2(0, 0), scale);

	Spritebatch->End();
	Context->IASetInputLayout(InputLayout);
	Context->PSSetShader(PixelShader, 0, 0);
	Context->VSSetShader(VertexShader, 0, 0);
}

void Drawing::DrawFilledRect(Vector2 Point, int Width, int Height, Vector3 Color)
{
	Vertex Verticies[] =
	{
		{Vector3(Point.x,Point.y,1.0f) , Color}, // TopLeft
		{Vector3(Point.x + Width, Point.y, 1.0f), Color}, // TopRight
		{Vector3(Point.x, Point.y - Height,1.0f), Color}, // BottomLeft
		{Vector3(Point.x + Width, Point.y - Height, 1.0f), Color} // BottomRight
	};

	DWORD Indicies[] = {
		2, 0, 1,
		2, 1, 3
	};

	UINT Stride = sizeof(Vertex) * 4;

	ID3D11Buffer* Buffer;
	D3D11_SUBRESOURCE_DATA dataptr;
	D3D11_BUFFER_DESC dsc;
	dsc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	dsc.ByteWidth = Stride;
	dsc.CPUAccessFlags = NULL;
	dsc.Usage = D3D11_USAGE_DEFAULT;
	dsc.StructureByteStride = NULL;
	dsc.MiscFlags = NULL;
	dataptr.pSysMem = Verticies;
	dataptr.SysMemPitch = NULL;
	dataptr.SysMemSlicePitch = NULL;
	Device->CreateBuffer(&dsc, &dataptr, &Buffer);

	ID3D11Buffer* Indicies_Buffer;
	D3D11_BUFFER_DESC dsc1;
	dsc1.ByteWidth = sizeof(DWORD) * 6;
	dsc1.StructureByteStride = NULL;
	dsc1.Usage = D3D11_USAGE_DEFAULT;
	dsc1.BindFlags = D3D11_BIND_INDEX_BUFFER;
	dsc1.CPUAccessFlags = NULL;
	dsc1.MiscFlags = NULL;
	D3D11_SUBRESOURCE_DATA dataptr1;
	dataptr1.pSysMem = Indicies;
	dataptr1.SysMemPitch = NULL;
	dataptr1.SysMemSlicePitch = NULL;
	Device->CreateBuffer(&dsc1, &dataptr1, &Indicies_Buffer);

	UINT Offset = 0;
	Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	Context->IASetIndexBuffer(Indicies_Buffer, DXGI_FORMAT_R32_UINT, NULL);
	Context->IASetVertexBuffers(0, 1, &Buffer, &Stride, &Offset);
	Context->DrawIndexed(6, 0, 0);
}

void Drawing::DrawOutlinedRect(Vector2 Point, int Width, int height, Vector3 color)
{
	float XWidth = Point.x + Width;
	float YHeight = Point.y - height;
	Vertex verticies[] = {
		{Vector3(Point.x, YHeight, 1.0f), color}, // Bottom Left 0
		{Vector3(Point.x - 1, YHeight, 1.0f), Colors::Black}, // left
		{Vector3(Point.x + 1, YHeight, 1.0f), Colors::Black}, // right
		{Vector3(Point.x, YHeight + 1, 1.0f), Colors::Black}, // up
		{Vector3(Point.x, YHeight - 1, 1.0f), Colors::Black}, // down

		{Vector3(Point.x, Point.y, 1.0f), color}, // TopLeft 5
		{Vector3(Point.x - 1, Point.y, 1.0f), Colors::Black}, // left
		{Vector3(Point.x + 1, Point.y, 1.0f), Colors::Black}, // right
		{Vector3(Point.x, Point.y + 1, 1.0f), Colors::Black}, // up
		{Vector3(Point.x, Point.y - 1, 1.0f), Colors::Black}, // down

		{Vector3(XWidth, YHeight, 1.0f), color}, // Bottom Right 10
		{Vector3(XWidth - 1, YHeight, 1.0f), Colors::Black}, // left
		{Vector3(XWidth + 1, YHeight, 1.0f), Colors::Black}, // right
		{Vector3(XWidth, YHeight + 1, 1.0f), Colors::Black}, // up
		{Vector3(XWidth, YHeight - 1, 1.0f), Colors::Black}, // down

		{Vector3(XWidth, Point.y, 1.0f), color}, // TopRight 15
		{Vector3(XWidth - 1, Point.y, 1.0f), Colors::Black}, // left
		{Vector3(XWidth + 1, Point.y, 1.0f), Colors::Black}, // right
		{Vector3(XWidth, Point.y + 1, 1.0f), Colors::Black}, // up
		{Vector3(XWidth, Point.y - 1, 1.0f), Colors::Black}  // down

	};

	ID3D11Buffer* Verticies;
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = verticies;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;
	
	UINT Offset = 0;
	UINT Stride = sizeof(Vertex);
	D3D11_BUFFER_DESC dsc;
	dsc.ByteWidth = Stride * 20;
	dsc.Usage = D3D11_USAGE_DEFAULT;
	dsc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	dsc.CPUAccessFlags = NULL;
	dsc.MiscFlags = NULL;
	dsc.StructureByteStride = NULL;

	Device->CreateBuffer(&dsc, &data, &Verticies);

	Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	Context->IASetIndexBuffer(RectIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	Context->IASetVertexBuffers(0, 1, &Verticies, &Stride, &Offset);
	Context->DrawIndexed(24, 0, 0);

	Verticies->Release();
}
