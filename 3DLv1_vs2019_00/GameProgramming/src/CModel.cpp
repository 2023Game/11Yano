#include "CModel.h"
#include <stdio.h>
void CModel::Load(char* obj, char* mtl) {
	FILE* fp; //�t�@�C���|�C���^�ϐ��̍쐬
	FILE* fp2;
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
	fp2 = fopen(obj, "r");
	if (fp2 == NULL) {
		printf("%s file open error\n", obj); //�R���\�[���ɃG���[�o�͂��Ė߂�
		return;
	}
	while (fgets(buf, sizeof(buf), fp2) != NULL) {
		printf("%s", buf); //���͂����l���R���\�[���ɏo�͂���
	}

	fclose(fp); //�t�@�C���̃N���[�Y
	fclose(fp2);
}