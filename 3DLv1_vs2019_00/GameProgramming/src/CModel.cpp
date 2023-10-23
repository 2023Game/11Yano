#include "CModel.h"
#include <stdio.h>
#include "CVector.h"
#include "CMaterial.h"

int strcmp(const char* s1, const char* s2) //������s1��s2�̔�r
{
	int i = 0;
	//�����������ꍇ�͌J��Ԃ��A�ǂ������̕������I���ƃ��[�v�I��
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return s1[i] - s2[i]; //�����Ȃ�����ĂO
}

void CModel::Load(char* obj, char* mtl) {
	std::vector<CVector> vertex; //���_�f�[�^�̕ۑ�
	std::vector<CVector> normal; //�@���f�[�^�̕ۑ�
	std::vector<CVector> uv; //�e�N�X�`���}�b�s���O�̕ۑ�

	FILE* fp; //�t�@�C���|�C���^�ϐ��̍쐬
	char buf[256]; //�t�@�C������f�[�^���́A���̓G���A�쐬

	fp = fopen(mtl, "r"); //�t�@�C���I�[�v��

	//NULL�̎��̓G���[
	if (fp == NULL) {
		printf("%s file open error\n", mtl); //�R���\�[���ɃG���[�o�͂��Ė߂�
		return;
	}

	int idx = 0; //�}�e���A���C���f�b�N�X
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		char str[4][64] = { "","","","" };
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]); //�����񂩂�f�[�^��4�ϐ��֑��
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			pm->Name(str[1]); //�}�e���A�����̐ݒ�
			mpMaterials.push_back(pm); //�}�e���A���̉ϒ��z��ɒǉ�
			idx = mpMaterials.size() - 1; //�z��̒������擾
		}
		else if (strcmp(str[0], "Kd") == 0) {
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}
		else if (strcmp(str[0], "d") == 0) {
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}
		else if (strcmp(str[0], "map_Kd") == 0) {
			mpMaterials[idx]->Texture()->Load(str[1]);
		}
	}

	fclose(fp); //�t�@�C���̃N���[�Y

	fp = fopen(obj, "r");

	if (fp == NULL) {
		printf("%s file open error\n", obj);
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		char str[4][64] = { "","","","" }; //�f�[�^�𕪊�
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]); //�����񂩂�f�[�^��4�ϐ��֑��
		if (strcmp(str[0], "v") == 0) //�������r
		{
			//�ϒ��z��vertex�ɒǉ�
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}

		else if (strcmp(str[0], "f") == 0) {
			int v[3], n[3]; //���_�Ɩ@���̔ԍ��쐬
			if (strstr(str[1], "//")) {
				sscanf(str[1], "%d//%d", &v[0], &n[0]); //���_�Ɩ@���̔ԍ��擾
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);
				CTriangle t; //�O�p�`�쐬
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				t.MaterialIdx(idx); //�}�e���A���ԍ��̐ݒ�
				mTriangles.push_back(t); //mTriangles�ɎO�p�`��ǉ�
			}
			else {
				int u[3]; //�e�N�X�`���}�b�s���O�̔ԍ�
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]); //���_�Ɩ@���ƃ}�b�s���O�̔ԍ��擾
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				CTriangle t; //�O�p�`�쐬
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				t.UV(uv[u[0] - 1], uv[u[1] - 1], uv[u[2] - 1]);
				t.MaterialIdx(idx);
				mTriangles.push_back(t);
			}
		}
		else if (strcmp(str[0], "vn") == 0) {
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		else if (strcmp(str[0], "usemtl") == 0) {
			//�ϒ��z����ォ���r
			for (idx = mpMaterials.size() - 1; idx > 0; idx--) {
				//�������O�̃}�e���A��������΃��[�v�I��
				if (strcmp(mpMaterials[idx]->Name(), str[1]) == 0) {
					break; //���[�v����o��
				}
			}
		}
		else if (strcmp(str[0], "vt") == 0) {
			//�ϒ��z��uv�ɒǉ�
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}
	}

	fclose(fp);
}

void CModel::Render() {
	for (int i = 0; i < mTriangles.size(); i++) {
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled(); //�}�e���A���̓K�p
		mTriangles[i].Render();
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}

CModel::~CModel()
{
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		delete mpMaterials[i];
	}
}

void CModel::Render(const CMatrix& m) {
	for (int i = 0; i < mTriangles.size(); i++) {
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled();
		mTriangles[i].Render(m);
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}