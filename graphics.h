#pragma once

#include<Windows.h>
#include<vector>
#include<d3d11.h>
#include"shapes.h"

class graphics {
public:
	graphics(HWND& hwnd);
	graphics(graphics&) = delete;
	graphics& operator=(const graphics&) = delete;
	~graphics();
	void end_frame();
	void clear_buffer(float red, float green, float blue);
	void setup_shader_pipeline();
	void setup_render_target();

	void render_cube(cube& C);

	void setup_IA_data(const vertex* pData, int count);
	void setup_viewport(HWND hwnd);
	void setup_pipeline(HWND hwnd);

private:
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11RenderTargetView* pRTV = nullptr;
	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11InputLayout* pInputLayout = nullptr;
	ID3DBlob* pVertexShaderBlob = nullptr;

};
