#pragma once

#include "include/webgpu.h"

// >NOTE: tag for custom utilitary functions that were added to WGPU objects structs
#if !defined(WGPU_XIN_EXTRA)
#define WGPU_XIN_EXTRA
#endif

namespace wgpu
{
	WGPUInstance createInstance(WGPU_NULLABLE WGPUInstanceDescriptor const* descriptor);

	struct Device            ;
	struct Adapter           ;
	struct Instance          ;
	struct Surface           ;
	struct Texture           ;
	struct ShaderModule      ;
	struct Queue             ;
	struct CommandEncoder    ;
	struct RenderPassEncoder ;
	struct RenderPipeline    ;
	struct Buffer            ;
	struct BindGroupLayout   ;
	struct PipelineLayout    ;
	struct BindGroup         ;
	struct TextureView       ;
	struct CommandBuffer     ;

	namespace helper
	{
		wgpu::Instance        createInstance           ();
		wgpu::Adapter         createAdapter            (wgpu::Instance instance);
		wgpu::Device          createDevice             (wgpu::Adapter adapter, flog* logger);
		wgpu::Surface         createSurface            (void* wndHandle, void* hInstance, wgpu::Instance instance);
		wgpu::ShaderModule    createShaderModule       (wgpu::Device device, WGPUStringView shaderData, const char* label);
		wgpu::BindGroupLayout createBindGroupLayout    (wgpu::Device device, uint64_t minBindingSize, const char* label);
		wgpu::PipelineLayout  createPipelineLayout     (wgpu::Device device, wgpu::BindGroupLayout bindGroupLayout);
		wgpu::RenderPipeline  createGameRenderPipeline (wgpu::Device, wgpu::ShaderModule, WGPUTextureFormat, wgpu::PipelineLayout, const char* label);
		wgpu::RenderPipeline  createUIRenderPipeline   (wgpu::Device, wgpu::ShaderModule, WGPUTextureFormat, wgpu::PipelineLayout, const char* label);

		WGPUAdapter requestAdapterAsync (wgpu::Instance instance, WGPURequestAdapterOptions const* options);
		WGPUDevice  requestDeviceAsync  (wgpu::Adapter adapter, const WGPUDeviceDescriptor* descriptor);

		void setDefault(WGPUBindGroupLayoutEntry& bindingLayout);
		void setDefault(WGPUStencilFaceState& stencilFaceState);
		void setDefault(WGPUDepthStencilState& depthStencilState);
	}

	namespace callback
	{
		WGPUDeviceLostCallbackInfo      onDeviceLost(flog* log);
		WGPUUncapturedErrorCallbackInfo onUncapturedError(flog* log);
	}

	namespace stringifier
	{
		const char* deviceLostReason(WGPUDeviceLostReason e);
		const char* errorType(WGPUErrorType e);
	}





	enum class LoadOp : uint32
	{
		Undefined            = WGPULoadOp_Undefined            ,
		Load                 = WGPULoadOp_Load                 ,
		Clear                = WGPULoadOp_Clear                ,
		ExpandResolveTexture = WGPULoadOp_ExpandResolveTexture ,
	};
	inline WGPULoadOp toWGPU(LoadOp e) { return (WGPULoadOp)e; }

	enum class TextureViewDimension : uint32
	{
		Undefined = WGPUTextureViewDimension_Undefined ,
		_1D       = WGPUTextureViewDimension_1D        ,
		_2D       = WGPUTextureViewDimension_2D        ,
		_2DArray  = WGPUTextureViewDimension_2DArray   ,
		Cube      = WGPUTextureViewDimension_Cube      ,
		CubeArray = WGPUTextureViewDimension_CubeArray ,
		_3D       = WGPUTextureViewDimension_3D        ,
	};
	inline WGPUTextureViewDimension toWGPU(TextureViewDimension e) { return (WGPUTextureViewDimension)e; }

	enum class PrimitiveTopology : uint32
	{
		Undefined     = WGPUPrimitiveTopology_Undefined     ,
		PointList     = WGPUPrimitiveTopology_PointList     ,
		LineList      = WGPUPrimitiveTopology_LineList      ,
		LineStrip     = WGPUPrimitiveTopology_LineStrip     ,
		TriangleList  = WGPUPrimitiveTopology_TriangleList  ,
		TriangleStrip = WGPUPrimitiveTopology_TriangleStrip ,
	};
	inline WGPUPrimitiveTopology toWGPU(PrimitiveTopology e) { return (WGPUPrimitiveTopology)e; }

	enum class IndexFormat : uint32
	{
		Undefined = WGPUIndexFormat_Undefined ,
		Uint16    = WGPUIndexFormat_Uint16    ,
		Uint32    = WGPUIndexFormat_Uint32    ,
	};
	inline WGPUIndexFormat toWGPU(IndexFormat e) { return (WGPUIndexFormat)e; }

	enum class FrontFace : uint32
	{
		Undefined = WGPUFrontFace_Undefined ,
		CCW       = WGPUFrontFace_CCW       ,
		CW        = WGPUFrontFace_CW        ,
	};
	inline WGPUFrontFace toWGPU(FrontFace e) { return (WGPUFrontFace)e; }

	enum class VertexStepMode : uint32
	{
		Undefined = WGPUVertexStepMode_Undefined ,
		Vertex    = WGPUVertexStepMode_Vertex    ,
		Instance  = WGPUVertexStepMode_Instance  ,
	};
	inline WGPUVertexStepMode toWGPU(VertexStepMode e) { return (WGPUVertexStepMode)e; }

	enum class BlendFactor : uint32
	{
		Undefined         = WGPUBlendFactor_Undefined         ,
		Zero              = WGPUBlendFactor_Zero              ,
		One               = WGPUBlendFactor_One               ,
		Src               = WGPUBlendFactor_Src               ,
		OneMinusSrc       = WGPUBlendFactor_OneMinusSrc       ,
		SrcAlpha          = WGPUBlendFactor_SrcAlpha          ,
		OneMinusSrcAlpha  = WGPUBlendFactor_OneMinusSrcAlpha  ,
		Dst               = WGPUBlendFactor_Dst               ,
		OneMinusDst       = WGPUBlendFactor_OneMinusDst       ,
		DstAlpha          = WGPUBlendFactor_DstAlpha          ,
		OneMinusDstAlpha  = WGPUBlendFactor_OneMinusDstAlpha  ,
		SrcAlphaSaturated = WGPUBlendFactor_SrcAlphaSaturated ,
		Constant          = WGPUBlendFactor_Constant          ,
		OneMinusConstant  = WGPUBlendFactor_OneMinusConstant  ,
		Src1              = WGPUBlendFactor_Src1              ,
		OneMinusSrc1      = WGPUBlendFactor_OneMinusSrc1      ,
		Src1Alpha         = WGPUBlendFactor_Src1Alpha         ,
		OneMinusSrc1Alpha = WGPUBlendFactor_OneMinusSrc1Alpha ,
	};
	inline WGPUBlendFactor toWGPU(BlendFactor e) { return (WGPUBlendFactor)e; }

	enum class BlendOperation : uint32
	{
		Undefined       = WGPUBlendOperation_Undefined       ,
		Add             = WGPUBlendOperation_Add             ,
		Subtract        = WGPUBlendOperation_Subtract        ,
		ReverseSubtract = WGPUBlendOperation_ReverseSubtract ,
		Min             = WGPUBlendOperation_Min             ,
		Max             = WGPUBlendOperation_Max             ,
	};
	inline WGPUBlendOperation toWGPU(BlendOperation e) { return (WGPUBlendOperation)e; }

	enum class CullMode : uint32
	{
		Undefined = WGPUCullMode_Undefined ,
		None      = WGPUCullMode_None      ,
		Front     = WGPUCullMode_Front     ,
		Back      = WGPUCullMode_Back      ,
	};
	inline WGPUCullMode toWGPU(CullMode e) { return (WGPUCullMode)e; }

	enum class VertexFormat : uint32
	{
		Uint8           = WGPUVertexFormat_Uint8           ,
		Uint8x2         = WGPUVertexFormat_Uint8x2         ,
		Uint8x4         = WGPUVertexFormat_Uint8x4         ,
		Sint8           = WGPUVertexFormat_Sint8           ,
		Sint8x2         = WGPUVertexFormat_Sint8x2         ,
		Sint8x4         = WGPUVertexFormat_Sint8x4         ,
		Unorm8          = WGPUVertexFormat_Unorm8          ,
		Unorm8x2        = WGPUVertexFormat_Unorm8x2        ,
		Unorm8x4        = WGPUVertexFormat_Unorm8x4        ,
		Snorm8          = WGPUVertexFormat_Snorm8          ,
		Snorm8x2        = WGPUVertexFormat_Snorm8x2        ,
		Snorm8x4        = WGPUVertexFormat_Snorm8x4        ,
		Uint16          = WGPUVertexFormat_Uint16          ,
		Uint16x2        = WGPUVertexFormat_Uint16x2        ,
		Uint16x4        = WGPUVertexFormat_Uint16x4        ,
		Sint16          = WGPUVertexFormat_Sint16          ,
		Sint16x2        = WGPUVertexFormat_Sint16x2        ,
		Sint16x4        = WGPUVertexFormat_Sint16x4        ,
		Unorm16         = WGPUVertexFormat_Unorm16         ,
		Unorm16x2       = WGPUVertexFormat_Unorm16x2       ,
		Unorm16x4       = WGPUVertexFormat_Unorm16x4       ,
		Snorm16         = WGPUVertexFormat_Snorm16         ,
		Snorm16x2       = WGPUVertexFormat_Snorm16x2       ,
		Snorm16x4       = WGPUVertexFormat_Snorm16x4       ,
		Float16         = WGPUVertexFormat_Float16         ,
		Float16x2       = WGPUVertexFormat_Float16x2       ,
		Float16x4       = WGPUVertexFormat_Float16x4       ,
		Float32         = WGPUVertexFormat_Float32         ,
		Float32x2       = WGPUVertexFormat_Float32x2       ,
		Float32x3       = WGPUVertexFormat_Float32x3       ,
		Float32x4       = WGPUVertexFormat_Float32x4       ,
		Uint32          = WGPUVertexFormat_Uint32          ,
		Uint32x2        = WGPUVertexFormat_Uint32x2        ,
		Uint32x3        = WGPUVertexFormat_Uint32x3        ,
		Uint32x4        = WGPUVertexFormat_Uint32x4        ,
		Sint32          = WGPUVertexFormat_Sint32          ,
		Sint32x2        = WGPUVertexFormat_Sint32x2        ,
		Sint32x3        = WGPUVertexFormat_Sint32x3        ,
		Sint32x4        = WGPUVertexFormat_Sint32x4        ,
		Unorm10_10_10_2 = WGPUVertexFormat_Unorm10_10_10_2 ,
		Unorm8x4BGRA    = WGPUVertexFormat_Unorm8x4BGRA    ,
	};
	inline WGPUVertexFormat toWGPU(VertexFormat e) { return (WGPUVertexFormat)e; }

	enum class CompareFunction : uint32
	{
		Undefined    = WGPUCompareFunction_Undefined    ,
		Never        = WGPUCompareFunction_Never        ,
		Less         = WGPUCompareFunction_Less         ,
		Equal        = WGPUCompareFunction_Equal        ,
		LessEqual    = WGPUCompareFunction_LessEqual    ,
		Greater      = WGPUCompareFunction_Greater      ,
		NotEqual     = WGPUCompareFunction_NotEqual     ,
		GreaterEqual = WGPUCompareFunction_GreaterEqual ,
		Always       = WGPUCompareFunction_Always       ,
	};
	inline WGPUCompareFunction toWGPU(CompareFunction e) { return (WGPUCompareFunction)e; }

	enum class OptionalBool : uint32
	{
		False     = WGPUOptionalBool_False     ,
		True      = WGPUOptionalBool_True      ,
		Undefined = WGPUOptionalBool_Undefined ,
	};
	inline WGPUOptionalBool toWGPU(OptionalBool e) { return (WGPUOptionalBool)e; }

	enum class TextureFormat : uint32
	{
		Undefined                   = WGPUTextureFormat_Undefined                   ,
		R8Unorm                     = WGPUTextureFormat_R8Unorm                     ,
		R8Snorm                     = WGPUTextureFormat_R8Snorm                     ,
		R8Uint                      = WGPUTextureFormat_R8Uint                      ,
		R8Sint                      = WGPUTextureFormat_R8Sint                      ,
		R16Unorm                    = WGPUTextureFormat_R16Unorm                    ,
		R16Snorm                    = WGPUTextureFormat_R16Snorm                    ,
		R16Uint                     = WGPUTextureFormat_R16Uint                     ,
		R16Sint                     = WGPUTextureFormat_R16Sint                     ,
		R16Float                    = WGPUTextureFormat_R16Float                    ,
		RG8Unorm                    = WGPUTextureFormat_RG8Unorm                    ,
		RG8Snorm                    = WGPUTextureFormat_RG8Snorm                    ,
		RG8Uint                     = WGPUTextureFormat_RG8Uint                     ,
		RG8Sint                     = WGPUTextureFormat_RG8Sint                     ,
		R32Float                    = WGPUTextureFormat_R32Float                    ,
		R32Uint                     = WGPUTextureFormat_R32Uint                     ,
		R32Sint                     = WGPUTextureFormat_R32Sint                     ,
		RG16Unorm                   = WGPUTextureFormat_RG16Unorm                   ,
		RG16Snorm                   = WGPUTextureFormat_RG16Snorm                   ,
		RG16Uint                    = WGPUTextureFormat_RG16Uint                    ,
		RG16Sint                    = WGPUTextureFormat_RG16Sint                    ,
		RG16Float                   = WGPUTextureFormat_RG16Float                   ,
		RGBA8Unorm                  = WGPUTextureFormat_RGBA8Unorm                  ,
		RGBA8UnormSrgb              = WGPUTextureFormat_RGBA8UnormSrgb              ,
		RGBA8Snorm                  = WGPUTextureFormat_RGBA8Snorm                  ,
		RGBA8Uint                   = WGPUTextureFormat_RGBA8Uint                   ,
		RGBA8Sint                   = WGPUTextureFormat_RGBA8Sint                   ,
		BGRA8Unorm                  = WGPUTextureFormat_BGRA8Unorm                  ,
		BGRA8UnormSrgb              = WGPUTextureFormat_BGRA8UnormSrgb              ,
		RGB10A2Uint                 = WGPUTextureFormat_RGB10A2Uint                 ,
		RGB10A2Unorm                = WGPUTextureFormat_RGB10A2Unorm                ,
		RG11B10Ufloat               = WGPUTextureFormat_RG11B10Ufloat               ,
		RGB9E5Ufloat                = WGPUTextureFormat_RGB9E5Ufloat                ,
		RG32Float                   = WGPUTextureFormat_RG32Float                   ,
		RG32Uint                    = WGPUTextureFormat_RG32Uint                    ,
		RG32Sint                    = WGPUTextureFormat_RG32Sint                    ,
		RGBA16Unorm                 = WGPUTextureFormat_RGBA16Unorm                 ,
		RGBA16Snorm                 = WGPUTextureFormat_RGBA16Snorm                 ,
		RGBA16Uint                  = WGPUTextureFormat_RGBA16Uint                  ,
		RGBA16Sint                  = WGPUTextureFormat_RGBA16Sint                  ,
		RGBA16Float                 = WGPUTextureFormat_RGBA16Float                 ,
		RGBA32Float                 = WGPUTextureFormat_RGBA32Float                 ,
		RGBA32Uint                  = WGPUTextureFormat_RGBA32Uint                  ,
		RGBA32Sint                  = WGPUTextureFormat_RGBA32Sint                  ,
		Stencil8                    = WGPUTextureFormat_Stencil8                    ,
		Depth16Unorm                = WGPUTextureFormat_Depth16Unorm                ,
		Depth24Plus                 = WGPUTextureFormat_Depth24Plus                 ,
		Depth24PlusStencil8         = WGPUTextureFormat_Depth24PlusStencil8         ,
		Depth32Float                = WGPUTextureFormat_Depth32Float                ,
		Depth32FloatStencil8        = WGPUTextureFormat_Depth32FloatStencil8        ,
		BC1RGBAUnorm                = WGPUTextureFormat_BC1RGBAUnorm                ,
		BC1RGBAUnormSrgb            = WGPUTextureFormat_BC1RGBAUnormSrgb            ,
		BC2RGBAUnorm                = WGPUTextureFormat_BC2RGBAUnorm                ,
		BC2RGBAUnormSrgb            = WGPUTextureFormat_BC2RGBAUnormSrgb            ,
		BC3RGBAUnorm                = WGPUTextureFormat_BC3RGBAUnorm                ,
		BC3RGBAUnormSrgb            = WGPUTextureFormat_BC3RGBAUnormSrgb            ,
		BC4RUnorm                   = WGPUTextureFormat_BC4RUnorm                   ,
		BC4RSnorm                   = WGPUTextureFormat_BC4RSnorm                   ,
		BC5RGUnorm                  = WGPUTextureFormat_BC5RGUnorm                  ,
		BC5RGSnorm                  = WGPUTextureFormat_BC5RGSnorm                  ,
		BC6HRGBUfloat               = WGPUTextureFormat_BC6HRGBUfloat               ,
		BC6HRGBFloat                = WGPUTextureFormat_BC6HRGBFloat                ,
		BC7RGBAUnorm                = WGPUTextureFormat_BC7RGBAUnorm                ,
		BC7RGBAUnormSrgb            = WGPUTextureFormat_BC7RGBAUnormSrgb            ,
		ETC2RGB8Unorm               = WGPUTextureFormat_ETC2RGB8Unorm               ,
		ETC2RGB8UnormSrgb           = WGPUTextureFormat_ETC2RGB8UnormSrgb           ,
		ETC2RGB8A1Unorm             = WGPUTextureFormat_ETC2RGB8A1Unorm             ,
		ETC2RGB8A1UnormSrgb         = WGPUTextureFormat_ETC2RGB8A1UnormSrgb         ,
		ETC2RGBA8Unorm              = WGPUTextureFormat_ETC2RGBA8Unorm              ,
		ETC2RGBA8UnormSrgb          = WGPUTextureFormat_ETC2RGBA8UnormSrgb          ,
		EACR11Unorm                 = WGPUTextureFormat_EACR11Unorm                 ,
		EACR11Snorm                 = WGPUTextureFormat_EACR11Snorm                 ,
		EACRG11Unorm                = WGPUTextureFormat_EACRG11Unorm                ,
		EACRG11Snorm                = WGPUTextureFormat_EACRG11Snorm                ,
		ASTC4x4Unorm                = WGPUTextureFormat_ASTC4x4Unorm                ,
		ASTC4x4UnormSrgb            = WGPUTextureFormat_ASTC4x4UnormSrgb            ,
		ASTC5x4Unorm                = WGPUTextureFormat_ASTC5x4Unorm                ,
		ASTC5x4UnormSrgb            = WGPUTextureFormat_ASTC5x4UnormSrgb            ,
		ASTC5x5Unorm                = WGPUTextureFormat_ASTC5x5Unorm                ,
		ASTC5x5UnormSrgb            = WGPUTextureFormat_ASTC5x5UnormSrgb            ,
		ASTC6x5Unorm                = WGPUTextureFormat_ASTC6x5Unorm                ,
		ASTC6x5UnormSrgb            = WGPUTextureFormat_ASTC6x5UnormSrgb            ,
		ASTC6x6Unorm                = WGPUTextureFormat_ASTC6x6Unorm                ,
		ASTC6x6UnormSrgb            = WGPUTextureFormat_ASTC6x6UnormSrgb            ,
		ASTC8x5Unorm                = WGPUTextureFormat_ASTC8x5Unorm                ,
		ASTC8x5UnormSrgb            = WGPUTextureFormat_ASTC8x5UnormSrgb            ,
		ASTC8x6Unorm                = WGPUTextureFormat_ASTC8x6Unorm                ,
		ASTC8x6UnormSrgb            = WGPUTextureFormat_ASTC8x6UnormSrgb            ,
		ASTC8x8Unorm                = WGPUTextureFormat_ASTC8x8Unorm                ,
		ASTC8x8UnormSrgb            = WGPUTextureFormat_ASTC8x8UnormSrgb            ,
		ASTC10x5Unorm               = WGPUTextureFormat_ASTC10x5Unorm               ,
		ASTC10x5UnormSrgb           = WGPUTextureFormat_ASTC10x5UnormSrgb           ,
		ASTC10x6Unorm               = WGPUTextureFormat_ASTC10x6Unorm               ,
		ASTC10x6UnormSrgb           = WGPUTextureFormat_ASTC10x6UnormSrgb           ,
		ASTC10x8Unorm               = WGPUTextureFormat_ASTC10x8Unorm               ,
		ASTC10x8UnormSrgb           = WGPUTextureFormat_ASTC10x8UnormSrgb           ,
		ASTC10x10Unorm              = WGPUTextureFormat_ASTC10x10Unorm              ,
		ASTC10x10UnormSrgb          = WGPUTextureFormat_ASTC10x10UnormSrgb          ,
		ASTC12x10Unorm              = WGPUTextureFormat_ASTC12x10Unorm              ,
		ASTC12x10UnormSrgb          = WGPUTextureFormat_ASTC12x10UnormSrgb          ,
		ASTC12x12Unorm              = WGPUTextureFormat_ASTC12x12Unorm              ,
		ASTC12x12UnormSrgb          = WGPUTextureFormat_ASTC12x12UnormSrgb          ,
		R8BG8Biplanar420Unorm       = WGPUTextureFormat_R8BG8Biplanar420Unorm       ,
		R10X6BG10X6Biplanar420Unorm = WGPUTextureFormat_R10X6BG10X6Biplanar420Unorm ,
		R8BG8A8Triplanar420Unorm    = WGPUTextureFormat_R8BG8A8Triplanar420Unorm    ,
		R8BG8Biplanar422Unorm       = WGPUTextureFormat_R8BG8Biplanar422Unorm       ,
		R8BG8Biplanar444Unorm       = WGPUTextureFormat_R8BG8Biplanar444Unorm       ,
		R10X6BG10X6Biplanar422Unorm = WGPUTextureFormat_R10X6BG10X6Biplanar422Unorm ,
		R10X6BG10X6Biplanar444Unorm = WGPUTextureFormat_R10X6BG10X6Biplanar444Unorm ,
		External                    = WGPUTextureFormat_External                    ,
	};
	inline WGPUTextureFormat toWGPU(TextureFormat e) { return (WGPUTextureFormat)e; }

	enum class BufferBindingType
	{
		BindingNotUsed   = WGPUBufferBindingType_BindingNotUsed  ,
		Undefined        = WGPUBufferBindingType_Undefined       ,
		Uniform          = WGPUBufferBindingType_Uniform         ,
		Storage          = WGPUBufferBindingType_Storage         ,
		ReadOnlyStorage  = WGPUBufferBindingType_ReadOnlyStorage ,
	};
	inline WGPUBufferBindingType toWGPU(BufferBindingType e) { return (WGPUBufferBindingType)e; }



	// >NOTE: All of these structs are referred to as "helpers"
	//        Example: Device::getQueueHelper will return wgpu::Queue while Device::getQueue will return WGPUQueue
	struct Device
	{
		WGPUBindGroup           createBindGroup              (WGPUBindGroupDescriptor const* descriptor);
		wgpu::BindGroup         createBindGroupHelper        (WGPUBindGroupDescriptor const* descriptor, const char* label) WGPU_XIN_EXTRA;
		WGPUBindGroupLayout     createBindGroupLayout        (WGPUBindGroupLayoutDescriptor const* descriptor);
		WGPUBuffer              createBuffer                 (WGPUBufferDescriptor const* descriptor);
		wgpu::Buffer            createBufferHelper           (WGPUBufferDescriptor const* descriptor, const char* label) WGPU_XIN_EXTRA;
		WGPUCommandEncoder      createCommandEncoder         (WGPU_NULLABLE WGPUCommandEncoderDescriptor const* descriptor);
		wgpu::CommandEncoder    createCommandEncoderHelper   (WGPU_NULLABLE WGPUCommandEncoderDescriptor const* descriptor, const char* label) WGPU_XIN_EXTRA;
		WGPUComputePipeline     createComputePipeline        (WGPUComputePipelineDescriptor const* descriptor);
		WGPUFuture              createComputePipelineAsync   (WGPUComputePipelineDescriptor const* descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo);
		WGPUBuffer              createErrorBuffer            (WGPUBufferDescriptor const* descriptor);
		WGPUExternalTexture     createErrorExternalTexture   ();
		WGPUShaderModule        createErrorShaderModule      (WGPUShaderModuleDescriptor const* descriptor, WGPUStringView errorMessage);
		WGPUTexture             createErrorTexture           (WGPUTextureDescriptor const* descriptor);
		WGPUExternalTexture     createExternalTexture        (WGPUExternalTextureDescriptor const* externalTextureDescriptor);
		WGPUPipelineLayout      createPipelineLayout         (WGPUPipelineLayoutDescriptor const* descriptor);
		WGPUQuerySet            createQuerySet               (WGPUQuerySetDescriptor const* descriptor);
		WGPURenderBundleEncoder createRenderBundleEncoder    (WGPURenderBundleEncoderDescriptor const* descriptor);
		WGPURenderPipeline      createRenderPipeline         (WGPURenderPipelineDescriptor const* descriptor);
		WGPUFuture              createRenderPipelineAsync    (WGPURenderPipelineDescriptor const* descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo);
		WGPUResourceTable       createResourceTable          (WGPUResourceTableDescriptor const* descriptor);
		WGPUSampler             createSampler                (WGPU_NULLABLE WGPUSamplerDescriptor const* descriptor);
		WGPUShaderModule        createShaderModule           (WGPUShaderModuleDescriptor const* descriptor);
		WGPUTexture             createTexture                (WGPUTextureDescriptor const* descriptor);
		wgpu::Texture           createTextureHelper          (WGPUTextureDescriptor const* descriptor) WGPU_XIN_EXTRA;
		void                    destroy                      ();
		void                    forceLoss                    (WGPUDeviceLostReason type, WGPUStringView message);
		WGPUAdapter             getAdapter                   ();
		WGPUStatus              getAdapterInfo               (WGPUAdapterInfo* adapterInfo);
		WGPUStatus              getAHardwareBufferProperties (void* handle, WGPUAHardwareBufferProperties* properties);
		void                    getFeatures                  (WGPUSupportedFeatures* features);
		WGPUStatus              getLimits                    (WGPULimits* limits);
		WGPUFuture              getLostFuture                ();
		WGPUQueue               getQueue                     ();
		wgpu::Queue             getQueueHelper               () WGPU_XIN_EXTRA;
		WGPUBool                hasFeature                   (WGPUFeatureName feature);
		WGPUSharedBufferMemory  importShaderBufferMemory     (WGPUSharedBufferMemoryDescriptor const* descriptor);
		WGPUSharedFence         importSharedFence            (WGPUSharedFenceDescriptor const* descriptor);
		WGPUSharedTextureMemory importSharedTextureMemory    (WGPUSharedTextureMemoryDescriptor const* descriptor);
		void                    injectError                  (WGPUErrorType type, WGPUStringView message);
		WGPUFuture              popErrorScope                (WGPUPopErrorScopeCallbackInfo callbackInfo);
		void                    pushErrorScope               (WGPUErrorFilter filter);
		void                    setLabel                     (WGPUStringView label);
		void                    setLabel                     (const char* label) WGPU_XIN_EXTRA;
		void                    setLoggingCallback           (WGPULoggingCallbackInfo callbackInfo);
		void                    tick                         ();
		void                    validateTextureDescriptor    (WGPUTextureDescriptor const* descriptor);
		void                    addRef                       ();
		void                    release                      ();

		WGPUDevice object;
	};

	struct Adapter
	{
		WGPUDevice   createDevice          (WGPU_NULLABLE WGPUDeviceDescriptor const* descriptor);
		void         getFeatures           (WGPUSupportedFeatures* features);
		WGPUStatus   getFormatCapabilities (WGPUTextureFormat format, WGPUDawnFormatCapabilities* capabilities);
		WGPUStatus   getInfo               (WGPUAdapterInfo* info);
		WGPUInstance getInstance           ();
		WGPUStatus   getLimits             (WGPULimits* limits);
		WGPULimits   getDefaultLimits      () WGPU_XIN_EXTRA;
		WGPUBool     hasFeature            (WGPUFeatureName feature);
		WGPUFuture   requestDevice         (WGPU_NULLABLE WGPUDeviceDescriptor const* descriptor, WGPURequestDeviceCallbackInfo callbackInfo);
		void         addRef                ();
		void         release               ();

		WGPUAdapter object;
	};

	struct Instance
	{
		WGPUSurface    createSurface           (WGPUSurfaceDescriptor const* descriptor);
		void           getWGSLLanguageFeatures (WGPUSupportedWGSLLanguageFeatures* features);
		WGPUBool       hasWGSLLanguageFeature  (WGPUWGSLLanguageFeatureName feature);
		void           processEvents           ();
		WGPUFuture     requestAdapter          (WGPU_NULLABLE WGPURequestAdapterOptions const* options, WGPURequestAdapterCallbackInfo callbackInfo);
		WGPUWaitStatus waitAny                 (size_t futureCount, WGPU_NULLABLE WGPUFutureWaitInfo* futures, uint64_t timeoutNS);
		void           addRef                  ();
		void           release                 ();

		WGPUInstance object;
	};

	struct Surface
	{
		void              configure             (WGPUSurfaceConfiguration const* config);
		WGPUStatus        getCapabilities       (WGPUAdapter adapter, WGPUSurfaceCapabilities* capabilities);
		WGPUStatus        getCapabilities       (wgpu::Adapter adapter, WGPUSurfaceCapabilities* capabilities) WGPU_XIN_EXTRA;
		void              getCurrentTexture     (WGPUSurfaceTexture* surfaceTexture);
		wgpu::TextureView getCurrentTextureView () WGPU_XIN_EXTRA;
		WGPUTextureFormat getFormat             (WGPUAdapter adapter, uint32 index = 0) WGPU_XIN_EXTRA;
		WGPUTextureFormat getFormat             (wgpu::Adapter adapter, uint32 index = 0) WGPU_XIN_EXTRA;
		WGPUStatus        present               ();
		void              setLabel              (WGPUStringView label);
		void              setLabel              (const char* label) WGPU_XIN_EXTRA;
		void              unconfigure           ();
		void              addRef                ();
		void              release               ();

		WGPUSurface object;
	};

	struct Texture
	{
		WGPUTextureView          createErrorView                (WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor);
		WGPUTextureView          createView                     (WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor);
		wgpu::TextureView        createViewHelper               (WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor) WGPU_XIN_EXTRA;
		void                     destroy                        ();
		uint32                   getDepthOrArrayLayers          ();
		WGPUTextureDimension     getDimension                   ();
		WGPUTextureFormat        getFormat                      ();
		uint32                   getHeight                      ();
		uint32                   getMipLevelCount               ();
		uint32                   getSampleCount                 ();
		WGPUTextureViewDimension getTextureBindingViewDimension ();
		WGPUTextureUsage         getUsage                       ();
		uint32                   getWidth                       ();
		void                     pin                            (WGPUTextureUsage usage);
		void                     setLabel                       (WGPUStringView label);
		void                     setLabel                       (const char* label) WGPU_XIN_EXTRA;
		void                     setOwnershipForMemoryDump      (uint64 ownerGuid);
		void                     unpin                          ();
		void                     addRef                         ();
		void                     release                        ();

		WGPUTexture object;
	};

	struct ShaderModule
	{
		WGPUFuture getCompilationInfo (WGPUCompilationInfoCallbackInfo callbackInfo);
		void       setLabel           (WGPUStringView label);
		void       setLabel           (const char* label) WGPU_XIN_EXTRA;
		void       addRef             ();
		void       release            ();

		WGPUShaderModule object;
	};

	struct Queue
	{
		void       copyExternalTextureForBrowser (WGPUImageCopyExternalTexture const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize, WGPUCopyTextureForBrowserOptions const* options);
		void       copyTextureForBrowser         (WGPUTexelCopyTextureInfo const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize, WGPUCopyTextureForBrowserOptions const* options);
		WGPUFuture onSubmittedWorkDone           (WGPUQueueWorkDoneCallbackInfo callbackInfo);
		void       setLabel                      (WGPUStringView label);
		void       setLabel                      (const char* label) WGPU_XIN_EXTRA;
		void       submit                        (size_t commandCount, WGPUCommandBuffer const* commands);
		void       writeBuffer                   (WGPUBuffer buffer, uint64_t bufferOffset, void const* data, size_t size);
		void       writeBuffer                   (wgpu::Buffer buffer, uint64_t bufferOffset, void const* data, size_t size) WGPU_XIN_EXTRA;
		void       writeTexture                  (WGPUTexelCopyTextureInfo const* destination, void const* data, size_t dataSize, WGPUTexelCopyBufferLayout const* dataLayout, WGPUExtent3D const* writeSize);
		void       addRef                        ();
		void       release                       ();

		WGPUQueue object;
	};

	struct CommandEncoder
	{
		WGPUComputePassEncoder   beginComputePass      (WGPU_NULLABLE WGPUComputePassDescriptor const* descriptor);
		WGPURenderPassEncoder    beginRenderPass       (WGPURenderPassDescriptor const* descriptor);
		wgpu::RenderPassEncoder  beginRenderPassHelper (WGPURenderPassDescriptor const* descriptor, const char* label) WGPU_XIN_EXTRA;
		void                     clearBuffer           (WGPUBuffer buffer, uint64_t offset, uint64_t size);
		void                     copyBufferToBuffer    (WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
		void                     copyBufferToTexture   (WGPUTexelCopyBufferInfo const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize);
		void                     copyTextureToBuffer   (WGPUTexelCopyTextureInfo const* source, WGPUTexelCopyBufferInfo const* destination, WGPUExtent3D const* copySize);
		void                     copyTextureToTexture  (WGPUTexelCopyTextureInfo const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize);
		WGPUCommandBuffer        finish                (WGPU_NULLABLE WGPUCommandBufferDescriptor const* descriptor);
		wgpu::CommandBuffer      finishHelper          (WGPU_NULLABLE WGPUCommandBufferDescriptor const* descriptor, const char* label);
		void                     injectValidationError (WGPUStringView message);
		void                     injectDebugMarker     (WGPUStringView markerLabel);
		void                     popDebugGroup         ();
		void                     pushDebugGroup        (WGPUStringView groupLabel);
		void                     resolveQuerySet       (WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset);
		void                     setLabel              (WGPUStringView label);
		void                     setLabel              (const char* label) WGPU_XIN_EXTRA;
		void                     setResourceTable      (WGPU_NULLABLE WGPUResourceTable table);
		void                     writeBuffer           (WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const* data, uint64_t size);
		void                     writeTimestamp        (WGPUQuerySet querySet, uint32_t queryIndex);
		void                     addRef                ();
		void                     release               ();

		WGPUCommandEncoder object;
	};

	struct RenderPassEncoder
	{
		void beginOcclusionQuery      (uint32_t queryIndex);
		void draw                     (uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
		void drawIndexed              (uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
		void drawIndexedIndirect      (WGPUBuffer indirectBuffer, uint64_t indirectOffset);
		void end                      ();
		void endOcclusionQuery        ();
		void executeBundles           (size_t bundleCount, WGPURenderBundle const* bundles);
		void insertDebugMarker        (WGPUStringView markerLabel);
		void multiDrawIndexedIndirect (WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset);
		void multiDrawIndirect        (WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset);
		void pixelLocalStorageBarrier ();
		void popDebugGroup            ();
		void pushDebugGroup           (WGPUStringView groupLabel);
		void setBindGroup             (uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets);
		void setBindGroup             (uint32_t groupIndex, wgpu::BindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets) WGPU_XIN_EXTRA;
		void setBlendConstant         (WGPUColor const* color);
		void setImmediates            (uint32_t offset, void const* data, size_t size);
		void setIndexBuffer           (WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
		void setIndexBuffer           (wgpu::Buffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_XIN_EXTRA;
		void setLabel                 (WGPUStringView label);
		void setLabel                 (const char* label) WGPU_XIN_EXTRA;
		void setPipeline              (WGPURenderPipeline pipeline);
		void setPipeline              (wgpu::RenderPipeline pipeline) WGPU_XIN_EXTRA;
		void setScissorRect           (uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		void setStencilReference      (uint32_t reference);
		void setVertexBuffer          (uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size);
		void setVertexBuffer          (uint32_t slot, wgpu::Buffer buffer, uint64_t offset, uint64_t size) WGPU_XIN_EXTRA;
		void setViewport              (float x, float y, float width, float height, float minDepth, float maxDepth);
		void writeTimestamp           (WGPUQuerySet querySet, uint32_t queryIndex);
		void addRef                   ();
		void release                  ();

		WGPURenderPassEncoder object;
	};

	struct RenderPipeline
	{
		WGPUBindGroupLayout getBindGroupLayout (uint32_t groupIndex);
		void                setLabel           (WGPUStringView label);
		void                setLabel           (const char* label) WGPU_XIN_EXTRA;
		void                addRef             ();
		void                release            ();

		WGPURenderPipeline object;
	};

	struct Buffer
	{
		WGPUTexelBufferView createTexelView     (WGPUTexelBufferViewDescriptor const* descriptor);
		void                destroy             ();
		void const*         getConstMappedRange (size_t offset, size_t size);
		void*               getMappedRange      (size_t offset, size_t size);
		WGPUBufferMapState  getMapState         ();
		uint64              getSize             ();
		WGPUBufferUsage     getUsage            ();
		WGPUFuture          mapAsync            (WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo);
		WGPUStatus          readMappedRange     (size_t offset, void* data, size_t size);
		void                setLabel            (WGPUStringView label);
		void                setLabel            (const char* label) WGPU_XIN_EXTRA;
		void                unmap               ();
		WGPUStatus          writeMappedRange    (size_t offset, void const* data, size_t size);
		void                addRef              ();
		void                release             ();

		WGPUBuffer object;
	};

	struct BindGroupLayout
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUBindGroupLayout object;
	};

	struct PipelineLayout
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUPipelineLayout object;
	};

	struct BindGroup
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUBindGroup object;
	};

	struct TextureView
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUTextureView object;
	};

	struct CommandBuffer
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUCommandBuffer object;
	};
}