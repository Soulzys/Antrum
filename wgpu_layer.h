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



	namespace LoadOp
	{
		constexpr auto Undefined            = WGPULoadOp_Undefined            ;
		constexpr auto Load                 = WGPULoadOp_Load                 ;
		constexpr auto Clear                = WGPULoadOp_Clear                ;
		constexpr auto ExpandResolveTexture = WGPULoadOp_ExpandResolveTexture ;
	}

	namespace TextureViewDimension
	{
		constexpr auto Undefined = WGPUTextureViewDimension_Undefined ;
		constexpr auto _1D       = WGPUTextureViewDimension_1D        ;
		constexpr auto _2D       = WGPUTextureViewDimension_2D        ;
		constexpr auto _2DArray  = WGPUTextureViewDimension_2DArray   ;
		constexpr auto Cube      = WGPUTextureViewDimension_Cube      ;
		constexpr auto CubeArray = WGPUTextureViewDimension_CubeArray ;
		constexpr auto _3D       = WGPUTextureViewDimension_3D        ;
	}

	namespace PrimitiveTopology
	{
		constexpr auto Undefined     = WGPUPrimitiveTopology_Undefined     ;
		constexpr auto PointList     = WGPUPrimitiveTopology_PointList     ;
		constexpr auto LineList      = WGPUPrimitiveTopology_LineList      ;
		constexpr auto LineStrip     = WGPUPrimitiveTopology_LineStrip     ;
		constexpr auto TriangleList  = WGPUPrimitiveTopology_TriangleList  ;
		constexpr auto TriangleStrip = WGPUPrimitiveTopology_TriangleStrip ;
	}

	namespace IndexFormat
	{
		constexpr auto Undefined = WGPUIndexFormat_Undefined ;
		constexpr auto Uint16    = WGPUIndexFormat_Uint16    ;
		constexpr auto Uint32    = WGPUIndexFormat_Uint32    ;
	}

	namespace FrontFace
	{
		constexpr auto Undefined = WGPUFrontFace_Undefined ;
		constexpr auto CCW       = WGPUFrontFace_CCW       ;
		constexpr auto CW        = WGPUFrontFace_CW        ;
	};

	namespace VertexStepMode
	{
		constexpr auto Undefined = WGPUVertexStepMode_Undefined ;
		constexpr auto Vertex    = WGPUVertexStepMode_Vertex    ;
		constexpr auto Instance  = WGPUVertexStepMode_Instance  ;
	};

	namespace BlendFactor
	{
		constexpr auto Undefined         = WGPUBlendFactor_Undefined         ;
		constexpr auto Zero              = WGPUBlendFactor_Zero              ;
		constexpr auto One               = WGPUBlendFactor_One               ;
		constexpr auto Src               = WGPUBlendFactor_Src               ;
		constexpr auto OneMinusSrc       = WGPUBlendFactor_OneMinusSrc       ;
		constexpr auto SrcAlpha          = WGPUBlendFactor_SrcAlpha          ;
		constexpr auto OneMinusSrcAlpha  = WGPUBlendFactor_OneMinusSrcAlpha  ;
		constexpr auto Dst               = WGPUBlendFactor_Dst               ;
		constexpr auto OneMinusDst       = WGPUBlendFactor_OneMinusDst       ;
		constexpr auto DstAlpha          = WGPUBlendFactor_DstAlpha          ;
		constexpr auto OneMinusDstAlpha  = WGPUBlendFactor_OneMinusDstAlpha  ;
		constexpr auto SrcAlphaSaturated = WGPUBlendFactor_SrcAlphaSaturated ;
		constexpr auto Constant          = WGPUBlendFactor_Constant          ;
		constexpr auto OneMinusConstant  = WGPUBlendFactor_OneMinusConstant  ;
		constexpr auto Src1              = WGPUBlendFactor_Src1              ;
		constexpr auto OneMinusSrc1      = WGPUBlendFactor_OneMinusSrc1      ;
		constexpr auto Src1Alpha         = WGPUBlendFactor_Src1Alpha         ;
		constexpr auto OneMinusSrc1Alpha = WGPUBlendFactor_OneMinusSrc1Alpha ;
	};

	namespace BlendOperation
	{
		constexpr auto Undefined       = WGPUBlendOperation_Undefined       ;
		constexpr auto Add             = WGPUBlendOperation_Add             ;
		constexpr auto Subtract        = WGPUBlendOperation_Subtract        ;
		constexpr auto ReverseSubtract = WGPUBlendOperation_ReverseSubtract ;
		constexpr auto Min             = WGPUBlendOperation_Min             ;
		constexpr auto Max             = WGPUBlendOperation_Max             ;
	};

	namespace CullMode
	{
		constexpr auto Undefined = WGPUCullMode_Undefined ;
		constexpr auto None      = WGPUCullMode_None      ;
		constexpr auto Front     = WGPUCullMode_Front     ;
		constexpr auto Back      = WGPUCullMode_Back      ;
	};

	namespace VertexFormat
	{
		constexpr auto Uint8           = WGPUVertexFormat_Uint8           ;
		constexpr auto Uint8x2         = WGPUVertexFormat_Uint8x2         ;
		constexpr auto Uint8x4         = WGPUVertexFormat_Uint8x4         ;
		constexpr auto Sint8           = WGPUVertexFormat_Sint8           ;
		constexpr auto Sint8x2         = WGPUVertexFormat_Sint8x2         ;
		constexpr auto Sint8x4         = WGPUVertexFormat_Sint8x4         ;
		constexpr auto Unorm8          = WGPUVertexFormat_Unorm8          ;
		constexpr auto Unorm8x2        = WGPUVertexFormat_Unorm8x2        ;
		constexpr auto Unorm8x4        = WGPUVertexFormat_Unorm8x4        ;
		constexpr auto Snorm8          = WGPUVertexFormat_Snorm8          ;
		constexpr auto Snorm8x2        = WGPUVertexFormat_Snorm8x2        ;
		constexpr auto Snorm8x4        = WGPUVertexFormat_Snorm8x4        ;
		constexpr auto Uint16          = WGPUVertexFormat_Uint16          ;
		constexpr auto Uint16x2        = WGPUVertexFormat_Uint16x2        ;
		constexpr auto Uint16x4        = WGPUVertexFormat_Uint16x4        ;
		constexpr auto Sint16          = WGPUVertexFormat_Sint16          ;
		constexpr auto Sint16x2        = WGPUVertexFormat_Sint16x2        ;
		constexpr auto Sint16x4        = WGPUVertexFormat_Sint16x4        ;
		constexpr auto Unorm16         = WGPUVertexFormat_Unorm16         ;
		constexpr auto Unorm16x2       = WGPUVertexFormat_Unorm16x2       ;
		constexpr auto Unorm16x4       = WGPUVertexFormat_Unorm16x4       ;
		constexpr auto Snorm16         = WGPUVertexFormat_Snorm16         ;
		constexpr auto Snorm16x2       = WGPUVertexFormat_Snorm16x2       ;
		constexpr auto Snorm16x4       = WGPUVertexFormat_Snorm16x4       ;
		constexpr auto Float16         = WGPUVertexFormat_Float16         ;
		constexpr auto Float16x2       = WGPUVertexFormat_Float16x2       ;
		constexpr auto Float16x4       = WGPUVertexFormat_Float16x4       ;
		constexpr auto Float32         = WGPUVertexFormat_Float32         ;
		constexpr auto Float32x2       = WGPUVertexFormat_Float32x2       ;
		constexpr auto Float32x3       = WGPUVertexFormat_Float32x3       ;
		constexpr auto Float32x4       = WGPUVertexFormat_Float32x4       ;
		constexpr auto Uint32          = WGPUVertexFormat_Uint32          ;
		constexpr auto Uint32x2        = WGPUVertexFormat_Uint32x2        ;
		constexpr auto Uint32x3        = WGPUVertexFormat_Uint32x3        ;
		constexpr auto Uint32x4        = WGPUVertexFormat_Uint32x4        ;
		constexpr auto Sint32          = WGPUVertexFormat_Sint32          ;
		constexpr auto Sint32x2        = WGPUVertexFormat_Sint32x2        ;
		constexpr auto Sint32x3        = WGPUVertexFormat_Sint32x3        ;
		constexpr auto Sint32x4        = WGPUVertexFormat_Sint32x4        ;
		constexpr auto Unorm10_10_10_2 = WGPUVertexFormat_Unorm10_10_10_2 ;
		constexpr auto Unorm8x4BGRA    = WGPUVertexFormat_Unorm8x4BGRA    ;
	};

	namespace CompareFunction
	{
		constexpr auto Undefined    = WGPUCompareFunction_Undefined    ;
		constexpr auto Never        = WGPUCompareFunction_Never        ;
		constexpr auto Less         = WGPUCompareFunction_Less         ;
		constexpr auto Equal        = WGPUCompareFunction_Equal        ;
		constexpr auto LessEqual    = WGPUCompareFunction_LessEqual    ;
		constexpr auto Greater      = WGPUCompareFunction_Greater      ;
		constexpr auto NotEqual     = WGPUCompareFunction_NotEqual     ;
		constexpr auto GreaterEqual = WGPUCompareFunction_GreaterEqual ;
		constexpr auto Always       = WGPUCompareFunction_Always       ;
	};

	namespace OptionalBool
	{
		constexpr auto False     = WGPUOptionalBool_False     ;
		constexpr auto True      = WGPUOptionalBool_True      ;
		constexpr auto Undefined = WGPUOptionalBool_Undefined ;
	};

	namespace TextureFormat
	{
		constexpr auto Undefined                   = WGPUTextureFormat_Undefined                   ;
		constexpr auto R8Unorm                     = WGPUTextureFormat_R8Unorm                     ;
		constexpr auto R8Snorm                     = WGPUTextureFormat_R8Snorm                     ;
		constexpr auto R8Uint                      = WGPUTextureFormat_R8Uint                      ;
		constexpr auto R8Sint                      = WGPUTextureFormat_R8Sint                      ;
		constexpr auto R16Unorm                    = WGPUTextureFormat_R16Unorm                    ;
		constexpr auto R16Snorm                    = WGPUTextureFormat_R16Snorm                    ;
		constexpr auto R16Uint                     = WGPUTextureFormat_R16Uint                     ;
		constexpr auto R16Sint                     = WGPUTextureFormat_R16Sint                     ;
		constexpr auto R16Float                    = WGPUTextureFormat_R16Float                    ;
		constexpr auto RG8Unorm                    = WGPUTextureFormat_RG8Unorm                    ;
		constexpr auto RG8Snorm                    = WGPUTextureFormat_RG8Snorm                    ;
		constexpr auto RG8Uint                     = WGPUTextureFormat_RG8Uint                     ;
		constexpr auto RG8Sint                     = WGPUTextureFormat_RG8Sint                     ;
		constexpr auto R32Float                    = WGPUTextureFormat_R32Float                    ;
		constexpr auto R32Uint                     = WGPUTextureFormat_R32Uint                     ;
		constexpr auto R32Sint                     = WGPUTextureFormat_R32Sint                     ;
		constexpr auto RG16Unorm                   = WGPUTextureFormat_RG16Unorm                   ;
		constexpr auto RG16Snorm                   = WGPUTextureFormat_RG16Snorm                   ;
		constexpr auto RG16Uint                    = WGPUTextureFormat_RG16Uint                    ;
		constexpr auto RG16Sint                    = WGPUTextureFormat_RG16Sint                    ;
		constexpr auto RG16Float                   = WGPUTextureFormat_RG16Float                   ;
		constexpr auto RGBA8Unorm                  = WGPUTextureFormat_RGBA8Unorm                  ;
		constexpr auto RGBA8UnormSrgb              = WGPUTextureFormat_RGBA8UnormSrgb              ;
		constexpr auto RGBA8Snorm                  = WGPUTextureFormat_RGBA8Snorm                  ;
		constexpr auto RGBA8Uint                   = WGPUTextureFormat_RGBA8Uint                   ;
		constexpr auto RGBA8Sint                   = WGPUTextureFormat_RGBA8Sint                   ;
		constexpr auto BGRA8Unorm                  = WGPUTextureFormat_BGRA8Unorm                  ;
		constexpr auto BGRA8UnormSrgb              = WGPUTextureFormat_BGRA8UnormSrgb              ;
		constexpr auto RGB10A2Uint                 = WGPUTextureFormat_RGB10A2Uint                 ;
		constexpr auto RGB10A2Unorm                = WGPUTextureFormat_RGB10A2Unorm                ;
		constexpr auto RG11B10Ufloat               = WGPUTextureFormat_RG11B10Ufloat               ;
		constexpr auto RGB9E5Ufloat                = WGPUTextureFormat_RGB9E5Ufloat                ;
		constexpr auto RG32Float                   = WGPUTextureFormat_RG32Float                   ;
		constexpr auto RG32Uint                    = WGPUTextureFormat_RG32Uint                    ;
		constexpr auto RG32Sint                    = WGPUTextureFormat_RG32Sint                    ;
		constexpr auto RGBA16Unorm                 = WGPUTextureFormat_RGBA16Unorm                 ;
		constexpr auto RGBA16Snorm                 = WGPUTextureFormat_RGBA16Snorm                 ;
		constexpr auto RGBA16Uint                  = WGPUTextureFormat_RGBA16Uint                  ;
		constexpr auto RGBA16Sint                  = WGPUTextureFormat_RGBA16Sint                  ;
		constexpr auto RGBA16Float                 = WGPUTextureFormat_RGBA16Float                 ;
		constexpr auto RGBA32Float                 = WGPUTextureFormat_RGBA32Float                 ;
		constexpr auto RGBA32Uint                  = WGPUTextureFormat_RGBA32Uint                  ;
		constexpr auto RGBA32Sint                  = WGPUTextureFormat_RGBA32Sint                  ;
		constexpr auto Stencil8                    = WGPUTextureFormat_Stencil8                    ;
		constexpr auto Depth16Unorm                = WGPUTextureFormat_Depth16Unorm                ;
		constexpr auto Depth24Plus                 = WGPUTextureFormat_Depth24Plus                 ;
		constexpr auto Depth24PlusStencil8         = WGPUTextureFormat_Depth24PlusStencil8         ;
		constexpr auto Depth32Float                = WGPUTextureFormat_Depth32Float                ;
		constexpr auto Depth32FloatStencil8        = WGPUTextureFormat_Depth32FloatStencil8        ;
		constexpr auto BC1RGBAUnorm                = WGPUTextureFormat_BC1RGBAUnorm                ;
		constexpr auto BC1RGBAUnormSrgb            = WGPUTextureFormat_BC1RGBAUnormSrgb            ;
		constexpr auto BC2RGBAUnorm                = WGPUTextureFormat_BC2RGBAUnorm                ;
		constexpr auto BC2RGBAUnormSrgb            = WGPUTextureFormat_BC2RGBAUnormSrgb            ;
		constexpr auto BC3RGBAUnorm                = WGPUTextureFormat_BC3RGBAUnorm                ;
		constexpr auto BC3RGBAUnormSrgb            = WGPUTextureFormat_BC3RGBAUnormSrgb            ;
		constexpr auto BC4RUnorm                   = WGPUTextureFormat_BC4RUnorm                   ;
		constexpr auto BC4RSnorm                   = WGPUTextureFormat_BC4RSnorm                   ;
		constexpr auto BC5RGUnorm                  = WGPUTextureFormat_BC5RGUnorm                  ;
		constexpr auto BC5RGSnorm                  = WGPUTextureFormat_BC5RGSnorm                  ;
		constexpr auto BC6HRGBUfloat               = WGPUTextureFormat_BC6HRGBUfloat               ;
		constexpr auto BC6HRGBFloat                = WGPUTextureFormat_BC6HRGBFloat                ;
		constexpr auto BC7RGBAUnorm                = WGPUTextureFormat_BC7RGBAUnorm                ;
		constexpr auto BC7RGBAUnormSrgb            = WGPUTextureFormat_BC7RGBAUnormSrgb            ;
		constexpr auto ETC2RGB8Unorm               = WGPUTextureFormat_ETC2RGB8Unorm               ;
		constexpr auto ETC2RGB8UnormSrgb           = WGPUTextureFormat_ETC2RGB8UnormSrgb           ;
		constexpr auto ETC2RGB8A1Unorm             = WGPUTextureFormat_ETC2RGB8A1Unorm             ;
		constexpr auto ETC2RGB8A1UnormSrgb         = WGPUTextureFormat_ETC2RGB8A1UnormSrgb         ;
		constexpr auto ETC2RGBA8Unorm              = WGPUTextureFormat_ETC2RGBA8Unorm              ;
		constexpr auto ETC2RGBA8UnormSrgb          = WGPUTextureFormat_ETC2RGBA8UnormSrgb          ;
		constexpr auto EACR11Unorm                 = WGPUTextureFormat_EACR11Unorm                 ;
		constexpr auto EACR11Snorm                 = WGPUTextureFormat_EACR11Snorm                 ;
		constexpr auto EACRG11Unorm                = WGPUTextureFormat_EACRG11Unorm                ;
		constexpr auto EACRG11Snorm                = WGPUTextureFormat_EACRG11Snorm                ;
		constexpr auto ASTC4x4Unorm                = WGPUTextureFormat_ASTC4x4Unorm                ;
		constexpr auto ASTC4x4UnormSrgb            = WGPUTextureFormat_ASTC4x4UnormSrgb            ;
		constexpr auto ASTC5x4Unorm                = WGPUTextureFormat_ASTC5x4Unorm                ;
		constexpr auto ASTC5x4UnormSrgb            = WGPUTextureFormat_ASTC5x4UnormSrgb            ;
		constexpr auto ASTC5x5Unorm                = WGPUTextureFormat_ASTC5x5Unorm                ;
		constexpr auto ASTC5x5UnormSrgb            = WGPUTextureFormat_ASTC5x5UnormSrgb            ;
		constexpr auto ASTC6x5Unorm                = WGPUTextureFormat_ASTC6x5Unorm                ;
		constexpr auto ASTC6x5UnormSrgb            = WGPUTextureFormat_ASTC6x5UnormSrgb            ;
		constexpr auto ASTC6x6Unorm                = WGPUTextureFormat_ASTC6x6Unorm                ;
		constexpr auto ASTC6x6UnormSrgb            = WGPUTextureFormat_ASTC6x6UnormSrgb            ;
		constexpr auto ASTC8x5Unorm                = WGPUTextureFormat_ASTC8x5Unorm                ;
		constexpr auto ASTC8x5UnormSrgb            = WGPUTextureFormat_ASTC8x5UnormSrgb            ;
		constexpr auto ASTC8x6Unorm                = WGPUTextureFormat_ASTC8x6Unorm                ;
		constexpr auto ASTC8x6UnormSrgb            = WGPUTextureFormat_ASTC8x6UnormSrgb            ;
		constexpr auto ASTC8x8Unorm                = WGPUTextureFormat_ASTC8x8Unorm                ;
		constexpr auto ASTC8x8UnormSrgb            = WGPUTextureFormat_ASTC8x8UnormSrgb            ;
		constexpr auto ASTC10x5Unorm               = WGPUTextureFormat_ASTC10x5Unorm               ;
		constexpr auto ASTC10x5UnormSrgb           = WGPUTextureFormat_ASTC10x5UnormSrgb           ;
		constexpr auto ASTC10x6Unorm               = WGPUTextureFormat_ASTC10x6Unorm               ;
		constexpr auto ASTC10x6UnormSrgb           = WGPUTextureFormat_ASTC10x6UnormSrgb           ;
		constexpr auto ASTC10x8Unorm               = WGPUTextureFormat_ASTC10x8Unorm               ;
		constexpr auto ASTC10x8UnormSrgb           = WGPUTextureFormat_ASTC10x8UnormSrgb           ;
		constexpr auto ASTC10x10Unorm              = WGPUTextureFormat_ASTC10x10Unorm              ;
		constexpr auto ASTC10x10UnormSrgb          = WGPUTextureFormat_ASTC10x10UnormSrgb          ;
		constexpr auto ASTC12x10Unorm              = WGPUTextureFormat_ASTC12x10Unorm              ;
		constexpr auto ASTC12x10UnormSrgb          = WGPUTextureFormat_ASTC12x10UnormSrgb          ;
		constexpr auto ASTC12x12Unorm              = WGPUTextureFormat_ASTC12x12Unorm              ;
		constexpr auto ASTC12x12UnormSrgb          = WGPUTextureFormat_ASTC12x12UnormSrgb          ;
		constexpr auto R8BG8Biplanar420Unorm       = WGPUTextureFormat_R8BG8Biplanar420Unorm       ;
		constexpr auto R10X6BG10X6Biplanar420Unorm = WGPUTextureFormat_R10X6BG10X6Biplanar420Unorm ;
		constexpr auto R8BG8A8Triplanar420Unorm    = WGPUTextureFormat_R8BG8A8Triplanar420Unorm    ;
		constexpr auto R8BG8Biplanar422Unorm       = WGPUTextureFormat_R8BG8Biplanar422Unorm       ;
		constexpr auto R8BG8Biplanar444Unorm       = WGPUTextureFormat_R8BG8Biplanar444Unorm       ;
		constexpr auto R10X6BG10X6Biplanar422Unorm = WGPUTextureFormat_R10X6BG10X6Biplanar422Unorm ;
		constexpr auto R10X6BG10X6Biplanar444Unorm = WGPUTextureFormat_R10X6BG10X6Biplanar444Unorm ;
		constexpr auto External                    = WGPUTextureFormat_External                    ;
	};

	namespace BufferBindingType
	{
		constexpr auto BindingNotUsed   = WGPUBufferBindingType_BindingNotUsed  ;
		constexpr auto Undefined        = WGPUBufferBindingType_Undefined       ;
		constexpr auto Uniform          = WGPUBufferBindingType_Uniform         ;
		constexpr auto Storage          = WGPUBufferBindingType_Storage         ;
		constexpr auto ReadOnlyStorage  = WGPUBufferBindingType_ReadOnlyStorage ;
	};

	namespace StoreOp
	{
		constexpr auto Undefined = WGPUStoreOp_Undefined ;
		constexpr auto Store     = WGPUStoreOp_Store     ;
		constexpr auto Discard   = WGPUStoreOp_Discard   ;
	};

	namespace TextureAspect
	{
		constexpr auto Undefined   = WGPUTextureAspect_Undefined   ;
		constexpr auto All         = WGPUTextureAspect_All         ;
		constexpr auto StencilOnly = WGPUTextureAspect_StencilOnly ;
		constexpr auto DepthOnly   = WGPUTextureAspect_DepthOnly   ;
		constexpr auto Plane0Only  = WGPUTextureAspect_Plane0Only  ;
		constexpr auto Plane1Only  = WGPUTextureAspect_Plane1Only  ;
		constexpr auto Plane2Only  = WGPUTextureAspect_Plane2Only  ;
	};

	namespace TextureDimension
	{
		constexpr auto Undefined = WGPUTextureDimension_Undefined ;
		constexpr auto _1D       = WGPUTextureDimension_1D        ;
		constexpr auto _2D       = WGPUTextureDimension_2D        ;
		constexpr auto _3D       = WGPUTextureDimension_3D        ;
	};

	namespace PresentMode
	{
		constexpr auto Undefined   = WGPUPresentMode_Undefined   ;
		constexpr auto Fifo        = WGPUPresentMode_Fifo        ;
		constexpr auto FifoRelaxed = WGPUPresentMode_FifoRelaxed ;
		constexpr auto Immediate   = WGPUPresentMode_Immediate   ;
		constexpr auto Mailbox     = WGPUPresentMode_Mailbox     ;
	};

	namespace CompositeAlphaMode
	{
		constexpr auto Auto           = WGPUCompositeAlphaMode_Auto            ;
		constexpr auto Opaque         = WGPUCompositeAlphaMode_Opaque          ;
		constexpr auto Premultipled   = WGPUCompositeAlphaMode_Premultiplied   ;
		constexpr auto Unpremultipled = WGPUCompositeAlphaMode_Unpremultiplied ;
		constexpr auto Inherit        = WGPUCompositeAlphaMode_Inherit         ;
	};



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