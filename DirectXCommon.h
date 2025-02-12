#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
#include "array"

class DirectXCommon
{
public: // メンバ
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


		
private:
	// DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;
	
	
	//コマンドアロケータを生成する
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;

	//コマンドリストを生成する
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;

	//コマンドキューを生成する
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;

	//スワップチェーンを生成する
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;

	// WindowsAPI
	WinApp* winApp = nullptr;
	
	

	//DepthStencilTextureをウインドウのサイズで作成
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilResource;

	// RTV用のヒープでディスクリプタの数は2。RTVはShader内で触るものではないので、ShaderVisibleはfalse
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	// SRV用のヒープでディスクリプタの数は128。SRVはShader内で触るものなので、Shadervisibleはtrue
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;
	//DSV用のヒープでデイスクリプタの数は1。DSVはShader内で触るものではないので、Shade Visibleはfalse
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap;

	// デスクリプタヒープを生成する
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	// 指定番号のCPUデスクリプタハンドルを取得する
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);
	// 指定番号のGPUデスクリプタハンドルを取得する
	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);
	
	//SwapChainからResoureceを引っ張ってくる
	//スワップチェーンリソース
	// //Microsoft::WRL::ComPtr<ID3D12Resource>  swapChainResources[2];
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;

	//RTVを2つ作るのでディスクリプタを2つ用意
	//D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	std::array<Microsoft::WRL::ComPtr<D3D12_CPU_DESCRIPTOR_HANDLE>, 2> rtvHandles;

	//初期値0でFenceを作る
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;

	//ビューポート
	Microsoft::WRL::ComPtr<D3D12_VIEWPORT> viewport{};

	//シザー矩形
	Microsoft::WRL::ComPtr<D3D12_RECT> scissorRect{};

	//dxCompilerを初期化
	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils;
	Microsoft::WRL::ComPtr<IDxcCompiler3> dxcCompiler;
	//現時点でincludeはしないが、includeに対応するための設定を行っておく
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHandler;
};

