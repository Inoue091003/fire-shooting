#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)
// TODO: 砲台を青い壁に沿って上下に動かす。(C)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)
// TODO: スコアのサイズを大きくする。(E)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)
// TODO: PlaySound()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア

int     cannonDirection;//!< 砲台の向き　1:up / -1:down   (C)(実装:HW16A167 渕　崇洋)


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
//    cannonPos = Vector2(-80, -150);
    cannonPos = Vector2(-320, -150);        //砲台の位置(A)(実装:HW16A167 渕　崇洋)
//    targetRect = Rect(80, -140, 40, 40);
    targetRect = Rect(280, -140, 40, 40);   //ターゲットの位置(A)(実装:HW16A167 渕　崇洋)
    bulletPos.x = -999;
    score = 0;
<<<<<<< HEAD
    PlayBGM("bgm_maoudamashii_8bit07.mp3"); //ゲーム背景音(実装：HW16A154 西本　迅輝）
=======
    
    cannonDirection = 1;                    //砲台の向きの初期化 (C)(実装:HW16A167 渕　崇洋)
    
>>>>>>> e8303fff4bee329bc3f76c5f05fc2d2bbe8240bd
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        PlaySound("se_maoudamashii_system43.mp3");      //弾の発射音(実装：HW16A154 西本　迅輝）
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 10 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算//（実装：HW16A051 上手一貴）
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            PlaySound("se_maoudamashii_explosion03.mp3");   //ターゲットへの着弾音(実装：HW16A154 西本 迅輝)
        }
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }
    
    //砲台の移動(C)(実装:HW16A167 渕　崇洋)
    cannonPos.y += 100 * cannonDirection * Time::deltaTime;
    if (cannonPos.y < -150) {       //砲台の位置が青いRectの下
        cannonDirection = 1;
        cannonPos.y = -150;
    }
    if (cannonPos.y > -70) {        //砲台の位置が青いRectの上
        cannonDirection = -1;
        cannonPos.y = -70;
    }
    
    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 80.0f);//（実装：HW16A051 上手一貴）
    DrawText(FormatString("%05d", score), Vector2(-319, 149), Color::black);//（実装：HW16A051 上手一貴）
    DrawText(FormatString("%05d", score), Vector2(-320, 150), Color::white);//（実装：HW16A051 上手一貴）
}

