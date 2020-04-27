#pragma once
#include "ConstantBuffers.h"
#include "Drawable.h"
#include <DirectXMath.h>

class TransformCbuf: public Bindable
{
private:
	struct Transforms
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX modelViewProj;
	};
public:
	TransformCbuf( Graphics& gfx, const Drawable& parent, UINT slot = 0u );
	void Bind( Graphics& gfx ) noexcept override;
private:
	static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
	const Drawable& parent;
};