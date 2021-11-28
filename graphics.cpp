
#include"graphics.h"
#include<windows.h>
#include<d3d11.h>
#include"ant_exception.h"
#include<wrl.h>
#include<d3dcompiler.h>
#include"shapes.h"
#include<dxgidebug.h>

using namespace Microsoft::WRL;
using namespace utility;

graphics::graphics(HWND& hwnd) {
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferCount = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	
	sd.Windowed = true;
	sd.Flags = 0;
	sd.OutputWindow = hwnd;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = true;

	HRESULT hr;

	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&(this->pSwap),
		&(this->pDevice),
		nullptr,
		&(this->pContext)
	);
	throw_ant_if(hr);


	this->setup_pipeline(hwnd);
}

void graphics::render_cube(cube& C) {
	C.before_render();
	const vertex* dat = C.get_vertex_list_data();
	this->setup_IA_data(dat, C.get_vertex_list_count(), D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->pContext->Draw(C.get_vertex_list_count(), 0u);
}

void graphics::render_triangle(tri& T) {
	T.before_render();
	const vertex* dat = T.get_vertex_list_data();
	this->setup_IA_data(dat, T.get_vertex_list_count(), D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->pContext->Draw(T.get_vertex_list_count(), 0u);
}

void graphics::setup_pipeline(HWND hwnd) {
	this->setup_shader_pipeline();
	this->setup_render_target();
	this->setup_viewport(hwnd);
}

void graphics::setup_viewport(HWND hwnd) {
	RECT wnd_rect = {0};
	GetClientRect(hwnd, &wnd_rect);

	D3D11_VIEWPORT vp;
	vp.Width = float(wnd_rect.right - wnd_rect.left);
	vp.Height = float(wnd_rect.bottom - wnd_rect.top);
	vp.MaxDepth = 1;
	vp.MinDepth = 0;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	this->pContext->RSSetViewports(1, &vp);
}

void graphics::setup_IA_data(const vertex* pData, int count, D3D11_PRIMITIVE_TOPOLOGY type) {
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(vertex)*count;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = sizeof(vertex);

	D3D11_SUBRESOURCE_DATA rd;
	rd.pSysMem = reinterpret_cast<const void*>(pData);
	rd.SysMemPitch = 0u;
	rd.SysMemSlicePitch = 0u;

	ComPtr<ID3D11Buffer> pBuffer = nullptr;
	hr = this->pDevice->CreateBuffer(&bd, &rd, &pBuffer);
	throw_ant_if(hr);

	UINT Stride = sizeof(vertex);
	UINT StrideOffset = 0;
	this->pContext->IASetVertexBuffers(0u, 1, pBuffer.GetAddressOf(), &Stride, &StrideOffset);

	D3D11_INPUT_ELEMENT_DESC iec[] = {
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 8u, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	hr = this->pDevice->CreateInputLayout(iec, 2, this->pVertexShaderBlob->GetBufferPointer(), this->pVertexShaderBlob->GetBufferSize(), &(this->pInputLayout));
	throw_ant_if(hr);
	
	this->pContext->IASetPrimitiveTopology(type);
	this->pContext->IASetInputLayout(this->pInputLayout);
}

void graphics::setup_rastarizer() {
	ComPtr<ID3D11RasterizerState> pRast = nullptr;
	D3D11_RASTERIZER_DESC rDesc = {};
	rDesc.FillMode = D3D11_FILL_SOLID;
	rDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	rDesc.FrontCounterClockwise = true;
	rDesc.DepthBias = 0;
	rDesc.DepthBiasClamp = 0.0f;
}

void graphics::setup_render_target() {
	HRESULT hr;
	ID3D11Resource* p = nullptr;
	hr = this->pSwap->GetBuffer(0, __uuidof(p), reinterpret_cast<void**>(&p)); //Getting the swapchain backbuffer
	throw_ant_if(hr);

	hr = this->pDevice->CreateRenderTargetView(p, nullptr, &(this->pRTV)); //Creating renderTargetView for that backbuffer
	throw_ant_if(hr);
	
	this->pContext->OMSetRenderTargets(1, &(this->pRTV), nullptr);
	p->Release();
}

void graphics::setup_shader_pipeline() {
	HRESULT hr;
	
	hr = D3DReadFileToBlob(L"PixelShader.cso", &(this->pVertexShaderBlob));
	throw_ant_if(hr);

	ID3D11PixelShader* pPixelShader = nullptr;
	hr = this->pDevice->CreatePixelShader(this->pVertexShaderBlob->GetBufferPointer(), this->pVertexShaderBlob->GetBufferSize(), nullptr, &pPixelShader);
	throw_ant_if(hr);
	this->pContext->PSSetShader(pPixelShader, nullptr, 0);
	this->pPixelShader = pPixelShader;

	this->pVertexShaderBlob->Release();

	hr = D3DReadFileToBlob(L"VertexShader.cso", &(this->pVertexShaderBlob));
	throw_ant_if(hr);

	ID3D11VertexShader* VS = nullptr;
	hr = this->pDevice->CreateVertexShader(this->pVertexShaderBlob->GetBufferPointer(), this->pVertexShaderBlob->GetBufferSize(), nullptr, &VS);
	throw_ant_if(hr);

	this->pVertexShader = VS;
	this->pContext->VSSetShader(VS, nullptr, 0);
}

void graphics::clear_buffer(float red, float green, float blue) {
	float colors[4] = { red, green, blue, 1.0f};
	this->pContext->ClearRenderTargetView(this->pRTV, colors);
}

graphics::~graphics() {
	if (this->pContext != nullptr) {
		this->pContext->Release();
	}
	if (this->pSwap != nullptr) {
		this->pSwap->Release();
	}
	if (this->pDevice != nullptr) {
		this->pDevice->Release();
	}
	if (this->pRTV != nullptr) {
		this->pRTV->Release();
	}
	if (this->pVertexShader != nullptr) {
		this->pVertexShader->Release();
	}
	if (this->pPixelShader != nullptr) {
		this->pPixelShader->Release();
	}
	if (this->pInputLayout != nullptr) {
		this->pInputLayout->Release();
	}
	if (this->pVertexShaderBlob != nullptr) {
		this->pVertexShaderBlob->Release();
	}
}

void graphics::end_frame() {
	this->pSwap->Present(1u, 0u);
	this->clear_buffer(0.0f, 0.0f, 0.0f);
}
