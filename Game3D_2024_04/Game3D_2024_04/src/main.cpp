#include <Windows.h>
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    Application* application = new Application();
    //�A�v��������
    application->Initialize(hInst);
    //���[�v�F�A�v�����C���̎����������Ƃ���
    application->Loop();
    //�A�v���I������
    application->Terminate();
    delete(application);
    return 0;
}