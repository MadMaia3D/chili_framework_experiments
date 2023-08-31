/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.cpp																		  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Graphics.h"
#include "DXErr.h"
#include "ChiliException.h"
#include <assert.h>
#include <string>
#include <array>
#include "MathUtilities.h"

// Ignore the intellisense error "cannot open source file" for .shh files.
// They will be created during the build sequence before the preprocessor runs.
namespace FramebufferShaders {
#include "FramebufferPS.shh"
#include "FramebufferVS.shh"
}

#pragma comment( lib,"d3d11.lib" )

#define CHILI_GFX_EXCEPTION( hr,note ) Graphics::Exception( hr,note,_CRT_WIDE(__FILE__),__LINE__ )

using Microsoft::WRL::ComPtr;

Graphics::Graphics(HWNDKey& key) {
	assert(key.hWnd != nullptr);

	//////////////////////////////////////////////////////
	// create device and swap chain/get render target view
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 1;
	sd.BufferDesc.Width = Graphics::ScreenWidth;
	sd.BufferDesc.Height = Graphics::ScreenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.RefreshRate.Denominator = 60;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = key.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	HRESULT				hr;
	UINT				createFlags = 0u;
#ifdef CHILI_USE_D3D_DEBUG_LAYER
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
#endif

	// create device and front/back buffers
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pImmediateContext))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Creating device and swap chain");
	}

	// get handle to backbuffer
	ComPtr<ID3D11Resource> pBackBuffer;
	if (FAILED(hr = pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBuffer))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Getting back buffer");
	}

	// create a view on backbuffer that we can render to
	if (FAILED(hr = pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&pRenderTargetView))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Creating render target view on backbuffer");
	}


	// set backbuffer as the render target using created view
	pImmediateContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), nullptr);


	// set viewport dimensions
	D3D11_VIEWPORT vp;
	vp.Width = float(Graphics::ScreenWidth);
	vp.Height = float(Graphics::ScreenHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pImmediateContext->RSSetViewports(1, &vp);


	///////////////////////////////////////
	// create texture for cpu render target
	D3D11_TEXTURE2D_DESC sysTexDesc;
	sysTexDesc.Width = Graphics::ScreenWidth;
	sysTexDesc.Height = Graphics::ScreenHeight;
	sysTexDesc.MipLevels = 1;
	sysTexDesc.ArraySize = 1;
	sysTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sysTexDesc.SampleDesc.Count = 1;
	sysTexDesc.SampleDesc.Quality = 0;
	sysTexDesc.Usage = D3D11_USAGE_DYNAMIC;
	sysTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	sysTexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	sysTexDesc.MiscFlags = 0;
	// create the texture
	if (FAILED(hr = pDevice->CreateTexture2D(&sysTexDesc, nullptr, &pSysBufferTexture))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Creating sysbuffer texture");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = sysTexDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	// create the resource view on the texture
	if (FAILED(hr = pDevice->CreateShaderResourceView(pSysBufferTexture.Get(),
		&srvDesc, &pSysBufferTextureView))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Creating view on sysBuffer texture");
	}


	////////////////////////////////////////////////
	// create pixel shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof(FramebufferShaders::FramebufferPSBytecode),
		nullptr,
		&pPixelShader))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Creating pixel shader");
	}


	/////////////////////////////////////////////////
	// create vertex shader for framebuffer
	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		nullptr,
		&pVertexShader))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Creating vertex shader");
	}


	//////////////////////////////////////////////////////////////
	// create and fill vertex buffer with quad for rendering frame
	const FSQVertex vertices[] =
	{
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,1.0f,0.5f,1.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,-1.0f,0.5f,0.0f,1.0f },
	};
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FSQVertex) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if (FAILED(hr = pDevice->CreateBuffer(&bd, &initData, &pVertexBuffer))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Creating vertex buffer");
	}


	//////////////////////////////////////////
	// create input layout for fullscreen quad
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	// Ignore the intellisense error "namespace has no member"
	if (FAILED(hr = pDevice->CreateInputLayout(ied, 2,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		&pInputLayout))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Creating input layout");
	}


	////////////////////////////////////////////////////
	// Create sampler state for fullscreen textured quad
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(hr = pDevice->CreateSamplerState(&sampDesc, &pSamplerState))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Creating sampler state");
	}

	// allocate memory for sysbuffer (16-byte aligned for faster access)
	pSysBuffer = reinterpret_cast<Color*>(
		_aligned_malloc(sizeof(Color) * Graphics::ScreenWidth * Graphics::ScreenHeight, 16u));
}

Graphics::~Graphics() {
	// free sysbuffer memory (aligned free)
	if (pSysBuffer) {
		_aligned_free(pSysBuffer);
		pSysBuffer = nullptr;
	}
	// clear the state of the device context before destruction
	if (pImmediateContext) pImmediateContext->ClearState();
}

void Graphics::EndFrame() {
	HRESULT hr;

	// lock and map the adapter memory for copying over the sysbuffer
	if (FAILED(hr = pImmediateContext->Map(pSysBufferTexture.Get(), 0u,
		D3D11_MAP_WRITE_DISCARD, 0u, &mappedSysBufferTexture))) {
		throw CHILI_GFX_EXCEPTION(hr, L"Mapping sysbuffer");
	}
	// setup parameters for copy operation
	Color* pDst = reinterpret_cast<Color*>(mappedSysBufferTexture.pData);
	const size_t dstPitch = mappedSysBufferTexture.RowPitch / sizeof(Color);
	const size_t srcPitch = Graphics::ScreenWidth;
	const size_t rowBytes = srcPitch * sizeof(Color);
	// perform the copy line-by-line
	for (size_t y = 0u; y < Graphics::ScreenHeight; y++) {
		memcpy(&pDst[y * dstPitch], &pSysBuffer[y * srcPitch], rowBytes);
	}
	// release the adapter memory
	pImmediateContext->Unmap(pSysBufferTexture.Get(), 0u);

	// render offscreen scene texture to back buffer
	pImmediateContext->IASetInputLayout(pInputLayout.Get());
	pImmediateContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	pImmediateContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	const UINT stride = sizeof(FSQVertex);
	const UINT offset = 0u;
	pImmediateContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	pImmediateContext->PSSetShaderResources(0u, 1u, pSysBufferTextureView.GetAddressOf());
	pImmediateContext->PSSetSamplers(0u, 1u, pSamplerState.GetAddressOf());
	pImmediateContext->Draw(6u, 0u);

	// flip back/front buffers
	if (FAILED(hr = pSwapChain->Present(1u, 0u))) {
		if (hr == DXGI_ERROR_DEVICE_REMOVED) {
			throw CHILI_GFX_EXCEPTION(pDevice->GetDeviceRemovedReason(), L"Presenting back buffer [device removed]");
		}
		else {
			throw CHILI_GFX_EXCEPTION(hr, L"Presenting back buffer");
		}
	}
}

void Graphics::BeginFrame() {
	// clear the sysbuffer
	memset(pSysBuffer, 0u, sizeof(Color) * Graphics::ScreenHeight * Graphics::ScreenWidth);
}

void Graphics::PutPixel(int x, int y, Color c) {
	assert(x >= 0);
	assert(x < int(Graphics::ScreenWidth));
	assert(y >= 0);
	assert(y < int(Graphics::ScreenHeight));
	pSysBuffer[Graphics::ScreenWidth * y + x] = c;
}

void Graphics::PutPixel(int x, int y, int r, int g, int b) {
	PutPixel(x, y, { unsigned char(r),unsigned char(g),unsigned char(b) });
}

void Graphics::PutPixel(Vector2<int> position, Color c) {
	PutPixel(position.x, position.y, c);
}

void Graphics::PutPixel(int x, int y, Color c, float alpha) {
	Color oldColor = GetPixel(x, y);

	int newR = MathUtilities::LerpInt(oldColor.GetR(), c.GetR(), alpha);
	int newG = MathUtilities::LerpInt(oldColor.GetG(), c.GetG(), alpha);
	int newB = MathUtilities::LerpInt(oldColor.GetB(), c.GetB(), alpha);

	PutPixel(x, y, newR, newG, newB);
}

Color Graphics::GetPixel(int x, int y) {
	return pSysBuffer[Graphics::ScreenWidth * y + x];
}

void Graphics::DrawLine(Vector2<int> start, Vector2<int> end, Color color) {
	RectI screenRect = GetScreenRect();

	int deltaX = end.x - start.x;
	int deltaY = end.y - start.y;

	if (deltaX == 0 && deltaY == 0) {
		return;
	}
	bool isSlopeLow = abs(deltaX) > abs(deltaY);

	if (isSlopeLow) {		
		const float slope = float(deltaY) / deltaX;
		if (deltaX < 0) {
			std::swap(start, end);
			deltaX *= -1;
		}
		for (int i = 0; i <= abs(deltaX); i++) {
			const int currentX = start.x + i;
			const int currentY = int(start.y + slope * i);
			Vector2<int> point(currentX, currentY);
			if (screenRect.ContainsPoint(point)) {
				PutPixel(currentX, currentY, color);
			}
		}
	} else {
		const float slope = float(deltaX) / deltaY;
		if (deltaY < 0) {
			std::swap(start, end);
			deltaY *= -1;
		}
		for (int i = 0; i <= abs(deltaY); i++) {
			const int currentX = int(start.x + slope * i);
			const int currentY = start.y + i;
			Vector2<int> point(currentX, currentY);
			if (screenRect.ContainsPoint(point)) {
				PutPixel(currentX, currentY, color);
			}
		}
	}
}

void Graphics::DrawRect(int x, int y, int width, int height, Color c) {
	for (int py = 0; py < height; py++) {
		for (int px = 0; px < width; px++) {
			PutPixel(x + px, y + py, c);
		}
	}
}

void Graphics::DrawRect(Vector2<int> position, int width, int height, Color c) {
	DrawRect(position.x, position.y, width, height, c);
}

void Graphics::DrawRect(RectI rect, Color c) {
	DrawRect(rect.GetPosition(), rect.GetWidth(), rect.GetHeight(), c);
}

void Graphics::DrawRect(int x, int y, int width, int height, Color c, float alpha) {
	for (int py = 0; py < height; py++) {
		for (int px = 0; px < width; px++) {
			PutPixel(x + px, y + py, c, alpha);
		}
	}
}

void Graphics::DrawRect(Vector2<int> position, int width, int height, Color c, float alpha) {
	DrawRect(position.x, position.y, width, height, c, alpha);
}

void Graphics::DrawRect(RectI rect, Color c, float alpha) {
	DrawRect(rect.GetPosition(), rect.GetWidth(), rect.GetHeight(), c, alpha);
}

void Graphics::DrawCircle(Vector2<int> position, int radius, Color c) {
	RectI boundingBox = RectI::GetRectFromCenter(position, radius, radius);
	RectI screenRect = GetScreenRect();
	for (int y = boundingBox.top; y < boundingBox.bottom; y++) {
		for (int x = boundingBox.left; x < boundingBox.right; x++) {
			 const Vector2<int> point(x, y);

			bool isInsideCircle = position.GetDistanceSquared(point) <= (radius * radius);
			if (isInsideCircle && screenRect.ContainsPoint(point)) {
				PutPixel(point, c);
			}
		}
	}
}

void Graphics::DrawSprite(int x, int y, const Surface & surf) {
	const int surfWidth = surf.GetWidth();
	const int surfHeight = surf.GetHeight();
	for (int sy = 0; sy < surfHeight; sy++) {
		for (int sx = 0; sx < surfWidth; sx++) {
			PutPixel(x + sx, y + sy, surf.GetPixel(sx,sy));
		}
	}
}

void Graphics::DrawSprite(int x, int y, const RectI& subregion, const Surface& surf) {
	assert(0 <= subregion.left);
	assert(subregion.right <= surf.GetWidth());
	assert(0 <= subregion.top);
	assert(subregion.bottom <= surf.GetHeight());
	for (int sy = subregion.top; sy < subregion.bottom; sy++) {
		for (int sx = subregion.left; sx < subregion.right; sx++) {
			PutPixel(x + sx - subregion.left, y + sy - subregion.top, surf.GetPixel(sx, sy));
		}
	}
}

void Graphics::DrawSprite(int x, int y, RectI subregion, const RectI& clipRect, const Surface& surf) {
	assert(0 <= subregion.left);
	assert(subregion.right <= surf.GetWidth());
	assert(0 <= subregion.top);
	assert(subregion.bottom <= surf.GetHeight());

	if (x < clipRect.left) {
		const int leftClipSize = clipRect.left - x;
		subregion.left += leftClipSize;
		x += leftClipSize;
	}
	if ( (x + subregion.right) > clipRect.right) {
		const int rightClipSize = (x + subregion.right) - clipRect.right;
		subregion.right -= rightClipSize;
	}
	if (y < clipRect.top) {
		const int topClipSize = clipRect.top - y;
		subregion.top += topClipSize;
		y += topClipSize;
	}
	if ( (y + subregion.bottom) > clipRect.bottom) {
		const int bottomClipSize = (y + subregion.bottom) - clipRect.bottom;
		subregion.bottom -= bottomClipSize;
	}

	for (int sy = subregion.top; sy < subregion.bottom; sy++) {
		for (int sx = subregion.left; sx < subregion.right; sx++) {
			PutPixel(x + sx - subregion.left, y + sy - subregion.top, surf.GetPixel(sx, sy));
		}
	}
}

RectI Graphics::GetScreenRect() {
	return RectI(0, 0, ScreenWidth - 1, ScreenHeight - 1);
}

//////////////////////////////////////////////////
//           Graphics Exception
Graphics::Exception::Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line)
	:
	ChiliException(file, line, note),
	hr(hr) {
}

std::wstring Graphics::Exception::GetFullMessage() const {
	const std::wstring empty = L"";
	const std::wstring errorName = GetErrorName();
	const std::wstring errorDesc = GetErrorDescription();
	const std::wstring& note = GetNote();
	const std::wstring location = GetLocation();
	return    (!errorName.empty() ? std::wstring(L"Error: ") + errorName + L"\n"
		: empty)
		+ (!errorDesc.empty() ? std::wstring(L"Description: ") + errorDesc + L"\n"
			: empty)
		+ (!note.empty() ? std::wstring(L"Note: ") + note + L"\n"
			: empty)
		+ (!location.empty() ? std::wstring(L"Location: ") + location
			: empty);
}

std::wstring Graphics::Exception::GetErrorName() const {
	return DXGetErrorString(hr);
}

std::wstring Graphics::Exception::GetErrorDescription() const {
	std::array<wchar_t, 512> wideDescription;
	DXGetErrorDescription(hr, wideDescription.data(), wideDescription.size());
	return wideDescription.data();
}

std::wstring Graphics::Exception::GetExceptionType() const {
	return L"Chili Graphics Exception";
}