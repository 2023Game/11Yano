#include "CXPlayer.h"
#include "CActionCamera.h"

void CXPlayer::Update() {
    switch (AnimationIndex())
    {
    case 3:
        if (IsAnimationFinished())
        {
            ChangeAnimation(4, false, 30);
        }
        break;
    case 4:
        if (IsAnimationFinished())
        {
            ChangeAnimation(0, true, 60);
        }
        break;
    default:
        //カメラの前方
        CVector cameraZ = CActionCamera::Instance()->VectorZ();
        //カメラの左方向
        CVector cameraX = CActionCamera::Instance()->VectorX();
        //キャラクタの前方
        CVector charZ = mMatrixRotate.VectorZ();
        //XZ平面にして正規化
        cameraZ.Y(0.0f); cameraZ = cameraZ.Normalize();
        cameraX.Y(0.0f); cameraX = cameraX.Normalize();
        charZ.Y(0.0f); charZ = charZ.Normalize();
        //移動方向の設定
        CVector move;
        if (mInput.Key('A')) {
            move = move + cameraX;
        }
        if (mInput.Key('D')) {
            move = move - cameraX;
        }
        if (mInput.Key('W')) {
            move = move + cameraZ;
        }
        if (mInput.Key('S')) {
            move = move - cameraZ;
        }
        //移動あり
        if (move.Length() > 0.0f)
        {
            //遊び
            const float MARGIN = 0.06f;
            //正規化
            move = move.Normalize();
            //自分の向きと向かせたい向きで外積
            float cross = charZ.Cross(move).Y();
            //自分の向きと向かせたい向きで内積
            float dot = charZ.Dot(move);
            //外積がプラスは左回転
            if (cross > MARGIN) {
                mRotation.Y(mRotation.Y() + 5.0f);
            }
            //外積がマイナスは右回転
            else if (cross < -MARGIN) {
                mRotation.Y(mRotation.Y() - 5.0f);
            }
            //前後の向きが同じとき内積は1.0
            else if (dot < 1.0f - MARGIN) {
                mRotation.Y(mRotation.Y() - 5.0f);
            }
            //移動方向へ移動
            mPosition = mPosition + move * 0.1f;
            ChangeAnimation(1, true, 60);
        }
        else
        {
            ChangeAnimation(0, true, 60);
        }
        if (mInput.Key(VK_SPACE))
        {
            ChangeAnimation(3, false, 30);
        }
    }
    CXCharacter::Update();
    mColBody.Update();
}

CXPlayer::CXPlayer() 
    :mColBody(this, nullptr, CVector(0.0f, 25.0f, 0.0f), CVector(0.0f, 150.0f, 0.0f), 0.5f)
    ,mColSphereBody(this,nullptr,CVector(),0.5f,CCollider::ETag::EBODY)
    ,mColSphereHead(this, nullptr, CVector(0.0f,5.0f,-3.0f), 0.5f)
    ,mColSphereSword(this, nullptr, CVector(-10.0f,10.0f,50.0f), 0.3f,CCollider::ETag::ESWORD)
{

}

void CXPlayer::Init(CModelX* model) {
    CXCharacter::Init(model);
    //合成行列の設定
    mColBody.Matrix(&mpCombinedMatrix[1]);
    mColSphereBody.Matrix(&mpCombinedMatrix[9]);
    mColSphereHead.Matrix(&mpCombinedMatrix[12]);
    mColSphereSword.Matrix(&mpCombinedMatrix[22]);
}

void CXPlayer::Collision(CCollider* m, CCollider* o)
{
    switch (m->Type())
    {
    case CCollider::EType::ECAPSULE:
        if (o->Type() == CCollider::EType::ECAPSULE)
        {
            CVector adjust;
            if (CCollider::CollisionCapsuleCapsule(m, o, &adjust))
            {
                mPosition = mPosition + adjust;
                CTransform::Update();
            }
        }
        break;
    }
}