#pragma once
#include "macro.h"
#include "std.h"
#include <DirectXMath.h>
#include <d3d11.h>

struct Vertex
{
	DirectX::XMFLOAT3 m_Pos;	// 位置
	DirectX::XMFLOAT3 m_Normal;	// 法線
	DirectX::XMFLOAT2 m_Tex;	// UV座標
	int32_t	m_BoneIndex[4];	//ボーンインデックス
	float	m_BoneWeight[4];// ウェイト値
	int32_t	m_BoneNum;		// ボーン数
};

struct Vertex_Cube
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
	DirectX::XMFLOAT3 Normal;
};


namespace GAME_SYSTEMS
{
	class Polygon
	{
	public:
		Polygon(Vector<Vertex> vertices, Vector<unsigned int> indices);
		Polygon(Vector<Vertex_Cube>vertices, Vector<uInt32> indices);
	
	public:
		void Uninit(); // 後処理
		void Draw(ID3D11DeviceContext* devcon);
	
	private:
		bool InitBuffers(); // バッファ初期化
		bool InitBuffersCube(); // バッファ初期化
	
	private:
		Vector<Vertex> m_vertices;			// 頂点データ
		Vector<Vertex_Cube> m_vx;			// 頂点データ
		
		Vector<unsigned int> m_indices;
	
	private:
		ID3D11Buffer* m_VertexBuffer;			// 頂点バッファ
		ID3D11Buffer* m_IndexBuffer;
	};
}