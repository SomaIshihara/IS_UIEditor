//======================================================
//
//GUI�I�u�W�F�N�g[gui.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "object.h"
#include "objectX.h"
#include "texture.h"
#include "gui.h"
#include "debugproc.h"
#include "input.h"
#include "player.h"
#include "xmodel.h"

//************************************************
//�I�u�W�F�ǉ�
//************************************************
//=================================
//�R���X�g���N�^
//=================================
CGUIAddObj::CGUIAddObj() : CObject(PRIORITY_UI)
{
	m_SelectObj = nullptr;
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_bDragged = false;
}

//=================================
//�f�X�g���N�^
//=================================
CGUIAddObj::~CGUIAddObj()
{
}

//========================
//����������
//========================
HRESULT CGUIAddObj::Init(void)
{
	return S_OK;
}

//========================
//�I������
//========================
void CGUIAddObj::Uninit(void)
{
}

//========================
//�X�V����
//========================
void CGUIAddObj::Update(void)
{
	//ImGUI
	ImGuiIO& io = ImGui::GetIO();

	//���b�V���t�B�[���h
	static int width = 1;
	static int height = 1;
	static float length = 100.0f;

	// Demonstrate the various window flags. Typically you would just use the default!
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool unsaved_document = false;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;

	ImGui::SetNextWindowPos(ImVec2(900, 50));
	ImGui::SetNextWindowSize(ImVec2(335, 260), ImGuiCond_Once);	// �T�C�Y
	ImGui::Begin(u8"Main Window", nullptr, window_flags);			// ���O

	//Menu Bar
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Open Model"))
			{
				static OPENFILENAME     ofn;
				static TCHAR            szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = FindWindow(nullptr, TEXT(WINDOW_NAME));
					ofn.lpstrInitialDir = szPath;       // �����t�H���_�ʒu
					ofn.lpstrFile = szFile;       // �I���t�@�C���i�[
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFilter = TEXT("X�t�@�C��(*.x)\0*.x\0");
					ofn.lpstrTitle = TEXT("���f���t�@�C����I��");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
				}
				if (GetOpenFileName(&ofn)) {
					//���΃p�X��
					char aRelat[256];
					int nPathLen = strlen(_strdup(szPath));
					nPathLen++;	//�X���b�V��2��������
					strcpy(&aRelat[0], (_strdup(szFile) + nPathLen));

  					CXModel::Load(&aRelat[0]);
				}
			}
			else if (ImGui::MenuItem("Load ModelList"))
			{
				static OPENFILENAME     ofn;
				static TCHAR            szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = FindWindow(nullptr, TEXT(WINDOW_NAME));
					ofn.lpstrInitialDir = szPath;       // �����t�H���_�ʒu
					ofn.lpstrFile = szFile;       // �I���t�@�C���i�[
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFilter = TEXT("���f�����X�g�t�@�C��(*.isml)\0*.isml\0");
					ofn.lpstrTitle = TEXT("���f�����X�g�t�@�C����ǂݍ���");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
				}
				if (GetOpenFileName(&ofn)) {
					//���΃p�X��
					char aRelat[256];
					int nPathLen = strlen(_strdup(szPath));
					nPathLen++;	//�X���b�V��2��������
					strcpy(&aRelat[0], (_strdup(szFile) + nPathLen));

					CXModel::LoadList(&aRelat[0]);
				}
			}
			else if (ImGui::MenuItem("Save ModelList"))
			{
				static OPENFILENAME     ofn;
				static TCHAR            szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = FindWindow(nullptr, TEXT(WINDOW_NAME));
					ofn.lpstrInitialDir = szPath;       // �����t�H���_�ʒu
					ofn.lpstrFile = szFile;       // �I���t�@�C���i�[
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFilter = TEXT("���f�����X�g�t�@�C��(*.isml)\0*.isml\0");
					ofn.lpstrTitle = TEXT("���f�����X�g�t�@�C����ۑ�");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					//���΃p�X��
					char aRelat[256];
					int nPathLen = strlen(_strdup(szPath));
					nPathLen++;	//�X���b�V��2��������
					strcpy(&aRelat[0], (_strdup(szFile) + nPathLen));
					//�t�@�C���p�X�Ɋg���q���Ȃ���Εt������
					char* pSearch = strstr(&aRelat[0], ".isml");
					if (pSearch == nullptr)
					{
						strcat(&aRelat[0], ".isml");
					}

					CXModel::SaveList(&aRelat[0]);
				}
			}
			else if (ImGui::MenuItem("Load MapData"))
			{
				static OPENFILENAME     ofn;
				static TCHAR            szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = FindWindow(nullptr, TEXT(WINDOW_NAME));
					ofn.lpstrInitialDir = szPath;       // �����t�H���_�ʒu
					ofn.lpstrFile = szFile;       // �I���t�@�C���i�[
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFilter = TEXT("�}�b�v�f�[�^�t�@�C��(*.ismd)\0*.ismd\0");
					ofn.lpstrTitle = TEXT("�}�b�v�f�[�^�t�@�C����ǂݍ���");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
				}
				if (GetOpenFileName(&ofn)) {
					//���΃p�X��
					char aRelat[256];
					int nPathLen = strlen(_strdup(szPath));
					nPathLen++;	//�X���b�V��2��������
					strcpy(&aRelat[0], (_strdup(szFile) + nPathLen));

					CObjectX::LoadData(&aRelat[0]);
				}
			}
			else if (ImGui::MenuItem("Save MapData"))
			{
				static OPENFILENAME     ofn;
				static TCHAR            szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = FindWindow(nullptr, TEXT(WINDOW_NAME));
					ofn.lpstrInitialDir = szPath;       // �����t�H���_�ʒu
					ofn.lpstrFile = szFile;       // �I���t�@�C���i�[
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFilter = TEXT("�}�b�v�f�[�^�t�@�C��(*.ismd)\0*.ismd\0");
					ofn.lpstrTitle = TEXT("�}�b�v�f�[�^�t�@�C����ۑ�");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					//���΃p�X��
					char aRelat[256];
					int nPathLen = strlen(_strdup(szPath));
					nPathLen++;	//�X���b�V��2��������
					strcpy(&aRelat[0], (_strdup(szFile) + nPathLen));
					//�t�@�C���p�X�Ɋg���q���Ȃ���Εt������
					char* pSearch = strstr(&aRelat[0], ".ismd");
					if (pSearch == nullptr)
					{
						strcat(&aRelat[0], ".ismd");
					}

					CObjectX::SaveData(&aRelat[0]);
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("Select Model");

	if (ImGui::BeginListBox("ModelList", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
	{
		CXModel* pModel = CXModel::GetTop();

		while (pModel != nullptr)
		{
			CXModel* pNextModel = pModel->GetNext();

			const bool is_selected = (m_SelectObj == pModel);
			if (ImGui::Selectable(pModel->GetPath(), is_selected))
				m_SelectObj = pModel;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();

			pModel = pNextModel;
		}

		ImGui::EndListBox();
	}

	//�z�u
	if (m_SelectObj != nullptr)
	{
		ImGui::Text("-->Drag and drop placement<--");
		ImGui::ImageButton(CManager::GetTexture()->GetAddress(0), ImVec2(48.0f, 48.0f));
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{//�h���b�O�J�n
			ImGui::SetDragDropPayload("Place", nullptr, 0);
			ImGui::Text("Drop Place");
			ImGui::EndDragDropSource();
			m_bDragged = true;
		}
		else if (m_bDragged == true)
		{//�h���b�O�I��
			m_bDragged = false;

			if (io.WantCaptureMouse == false)
			{
				CInputMouse* mouse = CManager::GetInputMouse();	//�}�E�X�擾

				//�I�u�W�F�N�g�I���i0.0�`1.0�j
				D3DXVECTOR3 posNear = mouse->ConvertClickPosToWorld(0.0f);
				D3DXVECTOR3 posFar = mouse->ConvertClickPosToWorld(1.0f);

				D3DXPLANE plane;
				D3DXPlaneFromPointNormal(&plane, &CManager::VEC3_ZERO, &(D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
				D3DXVECTOR3 posCloss;
				D3DXPlaneIntersectLine(&posCloss, &plane, &posNear, &posFar);
				posCloss.x = ceilf(posCloss.x);
				posCloss.y = ceilf(posCloss.y);
				posCloss.z = ceilf(posCloss.z);
				CObjectX::Create(posCloss, CManager::VEC3_ZERO, m_SelectObj);
			}
		}
	}

	//���f���폜
	if (ImGui::Button("Unload Model") == true && m_SelectObj != nullptr)
	{
		ImGui::OpenPopup("Unload Model?");
	}
	if (ImGui::BeginPopupModal("Unload Model?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Read Model Unload?");
		ImGui::Separator();

		if (ImGui::Button("OK", ImVec2(120, 0))) 
		{ 
			CManager::GetPlayer()->UnsetSelObj();
			CObjectX::Delete(m_SelectObj);
			m_SelectObj->Unload();
			m_SelectObj = nullptr;
			ImGui::CloseCurrentPopup(); 
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) 
		{ 
			ImGui::CloseCurrentPopup(); 
		}
		ImGui::EndPopup();
	}

	ImGui::End();
}

//========================
//�`�揈��
//========================
void CGUIAddObj::Draw(void)
{
}

//========================
//��������
//========================
CGUIAddObj* CGUIAddObj::Create(void)
{
	CGUIAddObj* pObj = nullptr;

	if (pObj == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		pObj = new CGUIAddObj;

		//������
		pObj->Init();

		return pObj;
	}
	else
	{
		return nullptr;
	}
}

//************************************************
//�I�u�W�F�ύX
//************************************************
//=================================
//�R���X�g���N�^
//=================================
CGUIChangeObj::CGUIChangeObj() : CObject(PRIORITY_UI)
{
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_bDragged = false;
}

//=================================
//�f�X�g���N�^
//=================================
CGUIChangeObj::~CGUIChangeObj()
{
}

//========================
//����������
//========================
HRESULT CGUIChangeObj::Init(void)
{
	return S_OK;
}

//========================
//�I������
//========================
void CGUIChangeObj::Uninit(void)
{
}

//========================
//�X�V����
//========================
void CGUIChangeObj::Update(void)
{
	//ImGUI
	ImGuiIO& io = ImGui::GetIO();

	//���b�V���t�B�[���h
	static int width = 1;
	static int height = 1;
	static float length = 100.0f;

	// Demonstrate the various window flags. Typically you would just use the default!
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool unsaved_document = false;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;

	ImGui::SetNextWindowPos(ImVec2(900, 350));
	ImGui::SetNextWindowSize(ImVec2(335, 350), ImGuiCond_Once);	// �T�C�Y
	ImGui::Begin(u8"Change Model", nullptr, window_flags);			// ���O

	CObjectX* pObject = CManager::GetPlayer()->GetSelObj();

	//�I�u�W�F�N�g�I�����Ă�H
	if (pObject != nullptr)
	{//���Ă��
		float fPos[3], fRot[3];
		D3DXVECTOR3 dxPos = pObject->GetPos();
		D3DXVECTOR3 dxRot = pObject->GetRot();
		//float�z��ɓ����iImGUI�p�j
		fPos[0] = dxPos.x;
		fPos[1] = dxPos.y;
		fPos[2] = dxPos.z;
		fRot[0] = dxRot.x;
		fRot[1] = dxRot.y;
		fRot[2] = dxRot.z;

		//UI�\��
		ImGui::Text("[Selected]");
		ImGui::DragFloat3("Pos", fPos, 1.0f);
		ImGui::DragFloat3("Rot", fRot, 0.01f, -D3DX_PI, D3DX_PI);

		//Vec3�^�ɓ����
		dxPos.x = fPos[0];
		dxPos.y = fPos[1];
		dxPos.z = fPos[2];
		dxRot.x = fRot[0];
		dxRot.y = fRot[1];
		dxRot.z = fRot[2];

		//�I�u�W�F�N�g�ɓ����
		pObject->SetPos(dxPos);
		pObject->SetRot(dxRot);

		//�Ռ`���Ȃ���������{�^��
		if (ImGui::Button("Delete"))
		{//�ۂ����Ƃ�
			CManager::GetPlayer()->UnsetSelObj();
			pObject->Uninit();
		}
	}
	else
	{//���ĂȂ���
		ImGui::Text("[No Selected]");
	}

	ImGui::End();
}

//========================
//�`�揈��
//========================
void CGUIChangeObj::Draw(void)
{
}

//========================
//��������
//========================
CGUIChangeObj* CGUIChangeObj::Create(void)
{
	CGUIChangeObj* pObj = nullptr;

	if (pObj == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		pObj = new CGUIChangeObj;

		//������
		pObj->Init();

		return pObj;
	}
	else
	{
		return nullptr;
	}
}