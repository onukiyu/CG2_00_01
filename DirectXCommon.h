#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
#include "array"
#include <dxcapi.h>
#include "externals/DirectXTex/DirectXTex.h"


class DirectXCommon
{
public: // メンバ
	//DirectX::ScratchImage LoadTexture(const std::string& filePath);

	// 初期化
	void Initialize(WinApp* winApp);
	// デバイスの初期化
	void DeviceInitialize();
	// コマンド関連の初期化
	void CommandInitialize();
	// スワップチェーンの生成
	void SwapChainInitialize();
	// 深度バッファの生成
	void DepthBufferInitialize();
	// 各種デスクリプタヒープの生成
	void DescriptorHeapInitialize();
	// レンダーターゲットビューの初期化
	void RenderTargetViewInitialize();
	// 深度ステンシルビューの初期化
	void DepthStencilViewInitialize();
	// フェンスの生成
	void FenceInitialize();
	// ビューポート矩形の初期化
	void ViewportInitialize();
	// シザリング矩形の初期化
	void ScissorRectInitialize();
	// DXCコンパイラの生成
	void DxCompilerInitialize();
	// ImGuiの初期化
	void ImGuiInitialize();


	// SRVの指定番号のCPUデスクリプタハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);
	// SRVの指定番号のGPUデスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	//IDxcBlob* CompileShader(
	//	//CompilerするShederファイルへのパス
	//	const std::wstring& filePath,
	//	//Compilerに使用するProfile
	//	const wchar_t* profile,
	//	//初期化で生成したものを3つ
	//	IDxcUtils* dxcUtils,
	//	IDxcCompiler3* dxcCompiler,
	//	IDxcIncludeHandler* includeHandler);

		
private:
	IDXGIFactory7* dxgiFactory = nullptr;

	

	// DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	
	// DescriptorSizeを取得しておく
	uint32_t desriptorSizeSRV;
	uint32_t desriptorSizeRTV;
	uint32_t desriptorSizeDSV;

	//DXGIファクトリ
	//Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;
	

	//コマンドキューを生成する
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;

	//コマンドアロケータを生成する
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;

	//コマンドリストを生成する
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	//スワップチェーンを生成する
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	// WindowsAPI
	WinApp* winApp = nullptr;
	
	

	//DepthStencilTextureをウインドウのサイズで作成
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilResource;

	// RTV用のヒープでディスクリプタの数は2。RTVはShader内で触るものではないので、ShaderVisibleはfalse
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	// SRV用のヒープでディスクリプタの数は128。SRVはShader内で触るものなので、Shadervisibleはtrue
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;
	//ID3D12DescriptorHeap* srvDescriptorHeap;
	//DSV用のヒープでデイスクリプタの数は1。DSVはShader内で触るものではないので、Shade Visibleはfalse
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap;

	// デスクリプタヒープを生成する
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateDepthStencilTextureResource();

	// 指定番号のCPUデスクリプタハンドルを取得する
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	// 指定番号のGPUデスクリプタハンドルを取得する
	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap, uint32_t descriptorSize, uint32_t index);
	
	//SwapChainからResoureceを引っ張ってくる
	//スワップチェーンリソース
	// //Microsoft::WRL::ComPtr<ID3D12Resource>  swapChainResources[2];
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;

	//RTVを2つ作るのでディスクリプタを2つ用意
	//D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	std::array<D3D12_CPU_DESCRIPTOR_HANDLE, 2> rtvHandles;

	//初期値0でFenceを作る
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	//ビューポート
	D3D12_VIEWPORT viewport{};

	//シザー矩形
	D3D12_RECT scissorRect{};

	//dxCompilerを初期化
	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils = nullptr;
	Microsoft::WRL::ComPtr<IDxcCompiler3> dxcCompiler = nullptr;
	//現時点でincludeはしないが、includeに対応するための設定を行っておく
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHandler = nullptr;
};

