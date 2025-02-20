#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
#include "array"
#include <dxcapi.h>
#include <string>
#include "externals/DirectXTex/DirectXTex.h"
#include<chrono>


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

	//GE3_04_03
	// 描画前処理
	void PreDraw();
	// 描画後処理
	void PostDraw();

	//終了
	void Finalize();

	// SRVの指定番号のCPUデスクリプタハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);
	// SRVの指定番号のGPUデスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	/*D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);*/

	

	// getter
	ID3D12Device* GetDevice() const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }
	
	Microsoft::WRL::ComPtr<IDxcBlob> CompileShader(
		//CompilerするShederファイルへのパス
		const std::wstring& filePath,
		//Compilerに使用するProfile
		const wchar_t* profile
		);


	//CG2_02_00 P42lll
	//リソース生成関数
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);

	//テクスチャリソースの生成
	////2.DirectX12のTextureResourceを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);

	//テクスチャデータの転送
	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	// テクスチャファイルの読み込み
	static DirectX::ScratchImage LoadTexture(const std::string& filePath);

private:
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	

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
	WinApp* winApp;
	
	

	//DepthStencilTextureをウインドウのサイズで作成
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilResource;

	// RTV用のヒープでディスクリプタの数は2。RTVはShader内で触るものではないので、ShaderVisibleはfalse
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	// SRV用のヒープでディスクリプタの数は128。SRVはShader内で触るものなので、Shadervisibleはtrue
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;
	//ID3D12DescriptorHeap* srvDescriptorHeap;
	//DSV用のヒープでデイスクリプタの数は1。DSVはShader内で触るものではないので、Shade Visibleはfalse
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeaps;

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
	Microsoft::WRL::ComPtr<IDxcUtils> dxcUtils;
	Microsoft::WRL::ComPtr<IDxcCompiler3> dxcCompiler;
	//現時点でincludeはしないが、includeに対応するための設定を行っておく
	Microsoft::WRL::ComPtr<IDxcIncludeHandler> includeHandler;

	//TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier{};
	// フェンス値
	UINT64 fenceValue = 0;
	//FenceのSignalを待つためのイベントを作成する
	HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter;
	
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D12Debug1> debugController;
#endif // DEBUG

	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue;

	Microsoft::WRL::ComPtr<ID3D12Resource> resource;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap;

	Microsoft::WRL::ComPtr<IDxcBlobEncoding> shaderSource;

	Microsoft::WRL::ComPtr<IDxcResult> shaderResult;

	Microsoft::WRL::ComPtr<IDxcBlobUtf8> shaderError;

	Microsoft::WRL::ComPtr <IDxcBlob> shaderBlob;

	Microsoft::WRL::ComPtr<ID3D12CommandList> commandLists;

	// GE3_04_05
	// FPS固定初期化
	void InitializeFixFPS();
	// FPS固定更新
	void UpdateFixFPS();
	// 記録時間（FPS固定用）
	std::chrono::steady_clock::time_point reference_;
};

