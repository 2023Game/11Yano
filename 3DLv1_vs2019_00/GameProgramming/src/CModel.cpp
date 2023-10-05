#include "CModel.h"
#include <stdio.h>
#include "CVector.h"

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
	FILE* fp; //�t�@�C���|�C���^�ϐ��̍쐬
	char buf[256]; //�t�@�C������f�[�^���́A���̓G���A�쐬

	fp = fopen(mtl, "r"); //�t�@�C���I�[�v��

	//NULL�̎��̓G���[
	if (fp == NULL) {
		printf("%s file open error\n", mtl); //�R���\�[���ɃG���[�o�͂��Ė߂�
		return;
	}

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		printf("%s", buf); //���͂����l���R���\�[���ɏo�͂���
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
			sscanf(str[1], "%d//%d", &v[0], &n[0]); //���_�Ɩ@���̔ԍ��擾
			sscanf(str[2], "%d//%d", &v[1], &n[1]);
			sscanf(str[3], "%d//%d", &v[2], &n[2]);
			CTriangle t; //�O�p�`�쐬
			t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
			mTriangles.push_back(t); //mTriangles�ɎO�p�`��ǉ�
		}
	}

	fclose(fp);
}

void CModel::Render() {
	for (int i = 0; i < mTriangles.size(); i++) {
		mTriangles[i].Render();
	}
}