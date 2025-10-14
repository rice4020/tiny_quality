#pragma once

#include "tiny_quality/Renderer/Buffer.h"

namespace tiny_quality {

	class OpenGLVertexBuffer : public VertexBuffer {
	private:
		uint32_t m_RendererID;
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

		virtual uint32_t GetCount() const { return m_Count; }

	};
}