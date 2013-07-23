// OGLESRenderEngine.hpp
// KlayGE OpenGL ES渲染引擎类 头文件
// Ver 3.12.0
// 版权所有(C) 龚敏敏, 2010
// Homepage: http://www.klayge.org
//
// 3.11.0
// Remove TexelToPixelOffset (2010.9.26)
//
// 3.10.0
// 初次建立 (2010.1.22)
//
// 修改记录
//////////////////////////////////////////////////////////////////////////////////

#ifndef _OGLESRENDERENGINE_HPP
#define _OGLESRENDERENGINE_HPP

#pragma once

#include <KFL/Vector.hpp>

#include <vector>
#include <map>
#include <set>

#include <glloader/glloader.h>

#include <KlayGE/RenderEngine.hpp>
#include <KlayGE/ShaderObject.hpp>

namespace KlayGE
{
	class OGLESRenderEngine : public RenderEngine
	{
	public:
		OGLESRenderEngine();
		~OGLESRenderEngine();

		std::wstring const & Name() const;

		bool RequiresFlipping() const
		{
			return false;
		}

		void BeginFrame();
		void EndFrame();
		void BeginPass();
		void EndPass();

		void ForceFlush();

		void ScissorRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		void GetCustomAttrib(std::string const & name, void* value);

		bool FullScreen() const;
		void FullScreen(bool fs);

		void AdjustProjectionMatrix(float4x4& proj_mat);

		void ActiveTexture(GLenum tex_unit);
		
		void BindBuffer(GLenum target, GLuint buffer, bool force = false);
		void DeleteBuffers(GLsizei n, GLuint const * buffers);

		void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
		void ClearDepth(GLfloat depth);
		void ClearStencil(GLuint stencil);

		void BindFramebuffer(GLuint fbo, bool force = false);
		GLuint BindFramebuffer() const
		{
			return cur_fbo_;
		}
		void DeleteFramebuffers(GLsizei n, GLuint const * framebuffers);

		bool HackForPVR() const
		{
			return hack_for_pvr_;
		}
		bool HackForMali() const
		{
			return hack_for_mali_;
		}

	private:
		void DoCreateRenderWindow(std::string const & name, RenderSettings const & settings);
		void DoBindFrameBuffer(FrameBufferPtr const & fb);
		void DoBindSOBuffers(RenderLayoutPtr const & rl);
		void DoRender(RenderTechnique const & tech, RenderLayout const & rl);
		void DoDispatch(RenderTechnique const & tech, uint32_t tgx, uint32_t tgy, uint32_t tgz);
		void DoResize(uint32_t width, uint32_t height);

		void FillRenderDeviceCaps();
		void InitRenderStates();

		bool VertexFormatSupport(ElementFormat elem_fmt);
		bool TextureFormatSupport(ElementFormat elem_fmt);
		bool RenderTargetFormatSupport(ElementFormat elem_fmt, uint32_t sample_count, uint32_t sample_quality);

		virtual void CheckConfig(RenderSettings& settings) KLAYGE_OVERRIDE;

	private:
		array<GLfloat, 4> clear_clr_;
		GLfloat clear_depth_;
		GLuint clear_stencil_;

		GLint vp_x_, vp_y_;
		GLsizei vp_width_, vp_height_;

		GLuint cur_fbo_;

		RenderLayoutPtr so_rl_;
		GLenum so_primitive_mode_;
		std::vector<std::string> so_vars_;
		std::vector<char const *> so_vars_ptrs_;
		std::vector<GLuint> so_buffs_;

		GLenum active_tex_unit_;
		std::map<GLenum, GLuint> binded_buffer_;

		std::set<ElementFormat> vertex_format_;
		std::set<ElementFormat> texture_format_;
		std::set<ElementFormat> rendertarget_format_;

		bool hack_for_pvr_;
		bool hack_for_mali_;
	};

	typedef shared_ptr<OGLESRenderEngine> OGLESRenderEnginePtr;
}

#endif			// _OGLESRENDERENGINE_HPP
