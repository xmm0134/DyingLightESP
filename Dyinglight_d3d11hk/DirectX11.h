#undef DrawText

struct Vertex
{
	Vector3 Position;
	Vector3 Color;
};

namespace Drawing 
{
	namespace Colors
	{
		inline Vector3 Red(1.0f, 0.0f, 0.0f);
		inline Vector3 Green(0.0f, 1.0f, 0.0f);
		inline Vector3 Blue(0.0f, 0.0f, 1.0f);
		inline Vector3 Black(0.0f, 0.0f, 0.0f);
		inline Vector3 White(1.0f, 1.0f, 1.0f);
		inline Vector3 Yellow(1.0f, 1.0f, 0.0f);
	};
	inline bool Initialized = false;
	inline bool InitFont = false;
	inline ID3D11Device* Device;
	inline ID3D11DeviceContext* Context;
	inline ID3D10Blob* Vertex_ShaderBlob;
	inline ID3D10Blob* Pixel_ShaderBlob;
	inline ID3D11VertexShader* VertexShader;
	inline ID3D11PixelShader* PixelShader;
	inline ID3D11InputLayout* InputLayout;
	inline std::unique_ptr<DirectX::SpriteBatch> Spritebatch;
	inline std::unique_ptr<DirectX::SpriteFont>  Spritefont;
	inline ID3D11Buffer* LineIndexBuffer;
	inline ID3D11Buffer* RectIndexBuffer;
	extern bool InitDraw(ID3D11Device* Device, ID3D11DeviceContext* Context);
	extern bool InitIndexBuffers();
	extern void BeginFrame();
	extern void DrawLine(Vector2 Src, Vector2 Dst, Vector3 Color);
	extern void DrawOutLinedLine(Vector2 Src, Vector2 Dst, Vector3 Color);
	extern void DrawText(Vector2 Point, const char* text, int size, float scale, Vector3 Color);
	extern void DrawOutlinedText(Vector2 Point, const char* text, int size, float scale, Vector3 Color);
	extern void DrawFilledRect(Vector2 Point, int Width, int Height, Vector3 Color);
	extern void DrawOutlinedRect(Vector2 Point, int Width, int height, Vector3 color);
}

namespace DirectX
{
	inline ID3D11VertexShader* Vertex_shader;
	inline ID3D11PixelShader* Pixel_shader;
	inline ID3D10Blob* Vertex_shader_Blob;
	inline ID3D10Blob* Pixel_shader_Blob;
	inline ID3D11InputLayout* InputLayout;
	inline ID3D11RenderTargetView* RenderTarget;
	inline ID3D11Device* device;
	inline ID3D11DeviceContext* context;
	inline IDXGISwapChain* swapChain;
	inline DXGI_SWAP_CHAIN_DESC swap_desc;
	inline bool Init_Draw = false;
	extern bool init(void** Vtable, int size);
}