#pragma once
#include <d3d11.h>
#include "std.h"
#include "macro.h"

class Material
{
public:
	~Material();

public:
	bool LoadShader(const T_Char* vsfile, const T_Char* psfile);
	void Unload();

	// �V�F�[�_���Z�b�g����
	void SetShader();

private:
	ID3D11VertexShader* m_pVertexShader = nullptr;		// ���_�V�F�[�_�[���ꕨ
	ID3D11PixelShader* m_pPixelShader = nullptr;		// �s�N�Z���V�F�[�_�[���ꕨ
	ID3D11InputLayout* m_pVertexLayout = nullptr;		// ���_�t�H�[�}�b�g��`
};

