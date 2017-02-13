#include "GameObject.h"

GameObject::GameObject(string type, Geometry geometry, Material material, Transform* transform) : _geometry(geometry), _type(type), _material(material)
{
	_parent = nullptr;
	
	_transform = transform;
	_textureRV = nullptr;

}

GameObject::~GameObject()
{
}

void GameObject::Update(float t)
{
	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
	}

	XMMATRIX scale = XMMatrixScaling(_transform->GetScale().X, _transform->GetScale().Y, _transform->GetScale().Z);
	XMMATRIX rotation = XMMatrixRotationX(_transform->GetRotation().X) * XMMatrixRotationY(_transform->GetRotation().Y) * XMMatrixRotationZ(_transform->GetRotation().Z);
	XMMATRIX translation = XMMatrixTranslation(_transform->GetPosition().X, _transform->GetPosition().Y, _transform->GetPosition().Z);

	XMStoreFloat4x4(&_world, scale * rotation * translation);
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
