//======================================================
//
//�I�u�W�F�N�g�iX�j�����̃w�b�_[objectX.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_
#include "main.h"
#include "manager.h"
#include "object.h"

typedef unsigned char BINCODE;
//�o�C�i���̃R�[�h���e
//�V�X�e��(0b00xxxxxx)
#define BIN_CODE_SYSTEM				(0b00 << 6)
#define BIN_CODE_SCRIPT				(BIN_CODE_SYSTEM + 0b000000)
#define BIN_CODE_END_SCRIPT			(BIN_CODE_SYSTEM + 0b000001)
//���f���n(0b01xxxxxx)
#define BIN_CODE_MODEL				(0b01 << 6)
#define BIN_CODE_TEXTURE_FILENAME	(BIN_CODE_MODEL + 0b000000)
#define BIN_CODE_MODEL_FILENAME		(BIN_CODE_MODEL + 0b000001)
#define BIN_CODE_MODELSET			(BIN_CODE_MODEL + 0b000010)
#define BIN_CODE_TEXTURE_NUM		(BIN_CODE_MODEL + 0b000011)
#define BIN_CODE_MODEL_NUM			(BIN_CODE_MODEL + 0b000100)
//���[�V�����n(0b10xxxxxx)
#define BIN_CODE_MOTION				(0b10 << 6)

//�O���錾
class CXModel;

//�I�u�W�F�N�g�N���X
class CObjectX : public CObject
{
public:
	enum LOADRESULT
	{
		RES_OK = 0,
		RES_ERR_FILE_NOTFOUND,
		RES_MAX
	};

	//�ÓIconst
	static const int PATH_LENGTH;	//���u���ɕK�v�炵��

	//�R���X�g���N�^�E�f�X�g���N�^
	CObjectX(int nPriority = PRIORITY_DEFAULT);
	virtual ~CObjectX();

	//��{����
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//����
	static CObjectX* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return CManager::FLT_ZERO; }
	float GetHeight(void) { return CManager::FLT_ZERO; }
	float GetDepth(void) { return CManager::FLT_ZERO; }
	static CObjectX* GetTop(void) { return m_pTop; }
	CObjectX* GetNext(void) { return m_pNext; }
	CXModel* GetModel(void) { return m_pModel; }

	//�ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	//�g�p���f���P�ʂŏ���
	static void Delete(CXModel* pTarget);

	//�ǂݍ���
	static LOADRESULT LoadData(const char* pPath);
	static LOADRESULT SaveData(const char* pPath);

	//���S�t���O�������Ă���I�u�W�F���E��
	static void Exclusion(void);

private:
	//���f��
	D3DXMATRIX mtxWorld;	//���[���h�}�g��
	CXModel* m_pModel;		//���f��

	//�ʒu��
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����

	//���X�g
	static CObjectX* m_pTop;	//�擪�I�u�W�F�N�g
	static CObjectX* m_pCur;	//�Ō���I�u�W�F�N�g
	CObjectX* m_pNext;			//���̃I�u�W�F�N�g
	CObjectX* m_pPrev;			//�O�̃I�u�W�F�N�g
	bool m_bExclusion;			//���O�t���O
	static int m_nNumAll;		//����
};

#endif // !_OBJECT_H_