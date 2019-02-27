#include "iextreme.h"
#include "system\System.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Frame.h"
#include "Enemy.h"
#include "Effect.h"
#include "Number.h"

#include "stage_data.h"
#include "sceneMain.h"
#include "Sound.h"


enum {
	INIT,	//�����ݒ�
	BEGIN,	//
	APPEARANCE,	//
	BEGIN2,	//
	SLIDE_IN,  //�X���C�h�C��
	WARP_IN,   //���[�v�C��
	HOPPING_IN,//�z�b�s���O�C��
	HOPPING_IN2,//�z�b�s���O�C��
	HOPPING_IN3,//�z�b�s���O�C��
	MOVE,	//�ړ�����
	MOVE2,	//
	MOVE3,	//
	MOVE4,	//
	MOVE5,	//
	STOP,	//��~����
	STOP2,	//
	ROTATE,	//��]����
	FLASHING, //�_�ŏ���
	LOCK,	//���S����
	
	DEAD,	//���S����
	DEAD2,	//
	DEAD3,	//
	EFFECT, //�G�t�F�N�g
	CLEAR,	//������
};

//���Q�G�f�[�^
static SPR_DATA Enemy_data = SPR_DATA{ spr_data::Enemy1, 0, 0, 64, 64, -32, -32 };


//�ʏ�-----------------------------------------------------------------
static SPR_DATA Enemy_data_yellow[] = { //��
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 0,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 0,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 2, 64 * 0,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_green[] = { //��
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 1,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 1,	64,64,-32,-32,1 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,2 },
};
static SPR_DATA Enemy_data_pink[] = { //�s���N
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 2,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 2,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 2, 64 * 2,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_blue[] = { //��
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 3,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 3,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 2, 64 * 3,	64,64,-32,-32,2 },
	SPR_DATA{ spr_data::Enemy2, 64 * 3, 64 * 3,	64,64,-32,-32,3 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,4 },
};
static SPR_DATA Enemy_data_white[] = { //��
	SPR_DATA{ spr_data::Enemy2, 64 * 0, 64 * 4,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 1, 64 * 4,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 2, 64 * 4,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_kari[] = { //��
	SPR_DATA{ spr_data::Enemy1, 64 * 0, 0, 64, 64, -32, -32,0 },
	SPR_DATA{ spr_data::Enemy1, 64 * 0, 0, 64, 64, -32, -32,1 },
	SPR_DATA{ spr_data::Enemy1, 64 * 0, 0, 64, 64, -32, -32,2 },
	SPR_DATA{ spr_data::Enemy1, 64 * 0, 0, 64, 64, -32, -32,3 },
	SPR_DATA{ spr_data::Enemy1, 64 * 1, 0, 64, 64, -32, -32,4 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,5 },
};
//��-------------------------------------------------------------------
static SPR_DATA Enemy_data_yellow_damage[] = { //��
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 0,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 0,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 6, 64 * 0,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_green_damage[] = { //��
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 1,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 1,	64,64,-32,-32,1 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,2 },
};
static SPR_DATA Enemy_data_pink_damage[] = { //�s���N
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 2,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 2,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 6, 64 * 2,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_blue_damage[] = { //��
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 3,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 3,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 6, 64 * 3,	64,64,-32,-32,2 },
	SPR_DATA{ spr_data::Enemy2, 64 * 7, 64 * 3,	64,64,-32,-32,3 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,4 },
};
static SPR_DATA Enemy_data_white_damage[] = { //��
	SPR_DATA{ spr_data::Enemy2, 64 * 4, 64 * 4,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy2, 64 * 5, 64 * 4,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy2, 64 * 6, 64 * 4,	64,64,-32,-32,2 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,3 },
};
static SPR_DATA Enemy_data_kari_damage[] = { //��
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,0 },
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,1 },
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,2 },
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,3 },
	SPR_DATA{ spr_data::Enemy1, 64 * 2, 0,	64,64,-32,-32,4 },
	SPR_DATA{ -1,    0,     0,	 0, 0,  0,  0,5},
};
//�ʏ큕��-------------------------------------------------------------
static SPR_DATA* yellow_data[] = {
	{Enemy_data_yellow},
	{Enemy_data_yellow_damage},
};
static SPR_DATA* green_data[] = {
	{Enemy_data_green},
	{Enemy_data_green_damage},
};
static SPR_DATA* pink_data[] = {
	{Enemy_data_pink},
	{Enemy_data_pink_damage},
};
static SPR_DATA* blue_data[] = {
	{Enemy_data_blue},
	{Enemy_data_blue_damage},
};
static SPR_DATA* white_data[] = {
	{Enemy_data_white},
	{Enemy_data_white_damage},
};
static SPR_DATA* kari_data[] = {
	{Enemy_data_kari},
	{Enemy_data_kari_damage},
};

enum {
	normal = 0,
	Damage,
};




enum {	//�e�N�X�`���ԍ��ϊ�
	pinto_s = spr_data::UI1,
	pinto_a = spr_data::UI2,
	pinto_l = spr_data::UI4,
	flame_out = spr_data::UI3,
};

SPR_DATA spr_pinto_s = { pinto_s,0,0,128,128,-64,-64 };//�T�[�N��
SPR_DATA spr_pinto_a = { pinto_a,0,0,128,128,-64,-64 };//�Ԗ��
SPR_DATA spr_combo = { spr_data::UI6,0,125,120,40,0,0 }; //COMBO



//�����蔻��(obj1�̃T�C�Y����obj2�̃T�C�Y���S�ē����Ă��邩)
bool E_Judge(OBJ2D *obj1, OBJ2D *obj2)
{
	if (obj1->pos.x + obj1->size.x > obj2->pos.x + obj2->size.x) return false;
	if (obj2->pos.x - obj2->size.x > obj1->pos.x - obj1->size.x) return false;
	if (obj1->pos.y + obj1->size.y > obj2->pos.y + obj2->size.y) return false;
	if (obj2->pos.y - obj2->size.y > obj1->pos.y - obj1->size.y) return false;

	return true;
}

//��������(obj1��obj2�̋�����_lenge�ȓ�)
bool E_lenge(OBJ2D *obj1, OBJ2D *obj2, int _lenge)
{
	float lenge;
	float dx = obj1->pos.x - obj2->pos.x;
	float dy = obj1->pos.y - obj2->pos.y;
	lenge = sqrtf(dx*dx + dy*dy);
	if (lenge < _lenge) {
		return true;
	}
	return false;
}

//�v���C���[�܂ł̋����v�Z(obj1��obj2�̋���)
V2 E_P(OBJ2D *obj1, OBJ2D *obj2, V2 spd)
{
	float dx = obj1->pos.x - obj2->pos.x; //��Ԃ̋���
	float dy = obj1->pos.y - obj2->pos.y; //��Ԃ̋���
	float lenge = sqrtf(dx*dx + dy*dy);	//
	float ax = spd.x * dx / lenge;		//
	float ay = spd.y * dy / lenge;		//
	return V2(ax, ay);
}



//�G�_���[�W�_�Ŋ֐�
void Frash_white(Enemy* obj,int num) {
	obj->flash_timer++;
	pScore->add_ClearlyScore(1); //�X�R�A���Z

	if ( (obj->flash_timer%(num*2))<=4 ) { //01234
		obj->animeData = obj->Anime_Box[Damage];
		obj->alpha = 255*0.75f;
	}
	else if ( (obj->flash_timer%(num*2))<=9 ) { //56789
		obj->animeData = obj->Anime_Box[normal];
		obj->alpha = 255;
	}
	else if ( (obj->flash_timer%(num*2))<=14 ) { //1011121314
		obj->animeData = obj->Anime_Box[Damage];
		obj->alpha = 255*0.75f;
	}
	else {
		obj->animeData = obj->Anime_Box[normal];
		obj->alpha = 255;
	}
}

//�ȂɂŔ��f���邩,�Ԋu,�_�ł�������argb,�F�P,�F�Q
void Frash_Color(Enemy* obj,int num,D3DCOLOR argb1, D3DCOLOR argb2) {
	obj->flash_timer++;
	if ((obj->flash_timer % (num * 2)) <  num) obj->custom.argb = argb1;
	if ((obj->flash_timer % (num * 2)) >= num) obj->custom.argb = argb2;
}
//�_�Ŋ֐�(�F)
//�ȂɂŔ��f���邩,�Ԋu,�_�ł�������argb,�F�P,�F�Q
D3DCOLOR Frash_Color(int timer,int num,D3DCOLOR argb,D3DCOLOR argb1, D3DCOLOR argb2) {
	if ((timer % (num * 2)) <  num) argb = argb1;
	if ((timer % (num * 2)) >= num) argb = argb2;
	return argb;
}
//�_�Ŋ֐�(�����x)
//�ȂɂŔ��f���邩,�Ԋu,�_�ł�������alpha,�{���P,�{���Q,���܂�
int Frash_Alpha(int timer, int num, int alpha, float alpha1, float alpha2, int end) {
	if (timer<end) {
		if ((timer % (num * 2)) <  num) alpha = 255 * alpha1;
		if ((timer % (num * 2)) >= num) alpha = 255 * alpha2;
	}
	else alpha = 255;
	return alpha;
}



void Enemy_Manager::jast_dragIn(Enemy* obj) {
	if (obj->sz < JUSTPINTO_SIZE) { //�W���X�g�s���g�͈̔͂Ȃ�
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(0, 0), Just_pinto);
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (!enemy[i] || !enemy[i]->move)continue;
			if (E_lenge(obj, enemy[i], DRAGIN_SCALE)) { //�͈͓���
				enemy[i]->z = (pFrame->Get_f_z());		//����Z�l�ɂ���(��������)
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------
//
//	�G�^
//
//---------------------------------------------------------------------------------------------------------

//�����蔻��ɊY������Ȃ�_���[�W��ǉ�
void Enemy_Manager::damage_Calculation(Enemy* obj) {

	if (obj->zlock_flg == true) {
		obj->LockTimer--;
		if (obj->LockTimer < 0) {
			obj->zlock_flg = false;
			obj->LockTimer = 0;
			obj->z = ((rand() % (PINTO_MAX * 2)) - PINTO_MAX);
			obj->state = BEGIN;
		}
		if (KEY_Get(KEY_L1) == 3) {
			obj->damage += 9999 /*DAMAGE_MAX + 1*/;
		}
	}


	if (obj->sz < pFrame->getPintoSize())
	{


		if ( (pFrame->lockPinto_trg==true) && (obj->zlock_flg==false)) {
			pEffect_Manager->searchSet(obj->pos, V2(0, 0), pinto_lock); //�s���g���b�N�G�t�F�N�g
			pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y - 50), V2(0, 0), Lock); //Lock�G�t�F�N�g
			//pFrame->exorcise -= USE_PINTOLOCK;
			pFrame->lockPinto_exorcise(USE_PINTOLOCK);

			obj->zlock_flg = true;
			obj->LockTimer = obj->LockTime;
			obj->state = LOCK;
		
		}
		
		if ( obj->damage>(obj->damageMAX-obj->damageMAX/4) ) Frash_white(obj,11); //���_��(��)
		else Frash_white(obj, 35); //���_��(�x)
		//obj->damage += DAMAGE;
		//�@�@�{�^���@
		obj->damageflg = true;

		if (KEY_Get(KEY_L1) == 3) {
			obj->damage += 9999 /*DAMAGE_MAX + 1*/;
		}

	}

	else {
		if (obj->Anime_Box) {
			obj->damageflg = false;
			obj->animeData = obj->Anime_Box[normal];
			obj->data = &obj->animeData[0];
			obj->alpha = 255;
		}
	}
}




//Enemy_Manager::Enemy_Manager()
//{
//
//}
//
//Enemy_Manager::~Enemy_Manager()
//{
//
//}

//
void Enemy_Manager::searchSet(V2 pos, V2 spd, void(*move)(Enemy*), float _z, Enemy* parent) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		//���g������A�s�����s���Ă���Ȃ烋�[�v
		if (enemy[i] && enemy[i]->init_fg)continue;
		//���g�������Ȃ�쐬
		if (!enemy[i])enemy[i] = new Enemy();
		//�����ݒ�
		enemy[i]->clear();
		enemy[i]->pos = pos;
		enemy[i]->spd = spd;
		enemy[i]->move = move;
		(_z == rand_PINTO) ? enemy[i]->z = ((rand() % (PINTO_MAX * 2)) - PINTO_MAX) : enemy[i]->z = _z;
		enemy[i]->init_fg = true;
		if (parent)enemy[i]->parent = parent;
		break;
	}
}

STAGE_DATA* stageSetData_time[] = {
	tutorial_time,
	stage1_time,
};

STAGE_DATA* stageSetData_kill[] = {
	tutorial_time,
	stage1_kill,
};


void Enemy_Manager::Init(int stageNo) {

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!enemy[i])continue;
		enemy[i]->clear();
	}
	timer = 0;
	data = stageSetData_time[stageNo];
	data2 = stageSetData_kill[stageNo];
}
void Enemy_Manager::Update() {
	stageUpdate();
	
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i] && enemy[i]->move) 
		{
			enemy[i]->move(enemy[i]);
			enemy[i]->Update();
			enemy[i]->UIUpdate();

		}
	}
}

//static SPR_DATA line_data_e = SPR_DATA{ spr_data::Player_eff,128,60,4,4,-2,-2 }; //4�~4

//�G�Ǝ�l���̊Ԃ̐�
void Enemy::DotLine() {
	//if ( 20<Dot_timer ) {
	//	Dot_alpha -= 255/7;
	//	if ( Dot_alpha<0 ) Dot_alpha = 0;
	//}
	if ( /*0<Dot_alpha*/ Dot_timer<30 ) {
		V2 e_p;
		//float x = pos.x-size.x/2; //��
		//float x2 = pos.x+size.x/2; //�E
		//float y = pos.y-size.y/2; //��
		//float y2 = pos.y+size.y/2; //��
		float len = 20;
		for ( int i = 4; i<((int)len-2); i++ )
		{
			//if ( e_p.x<x && e_p.y<y || x2<e_p.x ) { //�G�̔��a�O�Ȃ�`��
				D3DXVec2Lerp(&e_p,&pos,&pPlayer->pos,i/len);
				pEffect_Manager->searchSet(e_p, V2(alpha, 0), line);
				//Dot_argb = (Dot_alpha << 24 | Dot_argb << 8 >> 8);
				//spr_data::Render(e_p, &line_data_e,Dot_argb,0);
			//}
		}
		//ID3DXLine::Draw
	}
	Dot_timer++;
}


void Enemy::UIUpdate() {
	if (sz < JUSTPINTO_SIZE) { //�W���X�g�s���g�Ȃ�
		u.argb = Frash_Color(count, 7, u.argb, 0x33D68D8D, 0xDDE2E268);	//�_��(��,��)
		//�g��--------------------------
		custom.scaleMode = CENTER;
		u.custom.scaleX = u.custom.scaleY = 1.2f;
//		if (count == 1)IEX_PlaySound(SE_JUSTPINTO, FALSE);	//�W���X�g�s���g���������Ƃ���SE
		count++;
	}
	else if (damageflg == true) { //�_���[�W���󂯂Ă���Ƃ�
		u.argb = Frash_Color(count, 15, u.argb, 0x22FFFFFF, 0xDDE26868);	//�_��(��,��)
		//�g��--------------------------
		custom.scaleMode = CENTER;
		u.custom.scaleX = u.custom.scaleY = 1.2f;
		if (count == 1)IEX_PlaySound(SE_PINTO, FALSE);	//�s���g���������Ƃ���SE
		count++;
	}
	else { //�_���[�W���󂯂Ă��Ȃ��Ƃ�
		u.argb = 0xDD5BE1FF; //�����F
		custom.scaleMode = CENTER;
		u.custom.scaleX = u.custom.scaleY = 1.0f;
		count = 0;
	}
}


void Enemy_Manager::stageUpdate()
{
	timer++;
	if (data) {
		//timer�ŊǗ�
		while (data->appearTime <= timer)
		{
			if (data->appearTime < 0) {
				break;
			}
			if (data->moveType == nullptr) break;
			pEnemy_Manager->searchSet(data->moveType, data->pos - V2(pMAP->getScrollX(), pMAP->getScrollY()), data->speed, data->speedAcc, data->speedMax, (float)data->z);
			data++;
		}
	}
	if (data2) {
		//���j���ŊǗ�
		while (data2->appearTime <= pScore->getKill_num()) {
			if (data2->appearTime == 0) {
				data2++;
				break;
			}
			if (data2->moveType == nullptr) break;
			pEnemy_Manager->searchSet(data2->moveType, data2->pos - V2(pMAP->getScrollX(), pMAP->getScrollY()), data2->speed, data2->speedAcc, data2->speedMax, (float)data2->z);
			data2++;
		}
	}
}

void Enemy_Manager::Render() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i] && enemy[i]->move)enemy[i]->Render();
	}
}
void Enemy_Manager::UIUpdate() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i] && enemy[i]->move) {
			enemy[i]->UIUpdate();
		}
	}
}
void Enemy_Manager::UIRender() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i] && enemy[i]->move) {
			enemy[i]->UIRender();
		}
	}
}




Enemy::Enemy()
{
	clear();
}

Enemy::~Enemy()
{

}
void Enemy::clear() {
	OBJ2DEX::clear();
	//delete_flg = false;
	move = nullptr;
	z = 0;
	damage = 0;
	damageMAX = 0;
	damageflg = false;
	rangeflg = false;
	alpha = 255;
	count = 0;
	u.argb = 0xFFFFFFFF;
	
	dx = 0;
	dy = 0;
	dist = 0;
	XCENTER = 0;
	YCENTER = 0;
	ANGLE = 0;
	ANGLEspd = 0;
	RADIUS = 0;
	LockTimer = 0;
	LockTime = 1;
	init_fg = false;
	z_flg = false;
	zlock_flg = false;
	flash_timer = 0;
	noHit_flg = 1;
	Anime_Box = nullptr;
	Dot_timer = 0;
	Dot_argb = 0xFFFFFFFF;

	for (int i = 0; i < 16; i++) {
		f_work[i] = 0;
	}
	custom.scaleMode = CENTER;
}
void Enemy::Init() {
	clear();
}
void Enemy::Update()
{
	animetion();
}



float Enemy_Manager::get_sz(float z) {
	float sz = 0;
	float ez = z;
	float fz = pFrame->Get_f_z();

	if (fz > ez) {
		sz = (fz) - (ez);
	}
	else {
		sz = (ez) - (fz);
	}
	//sz -= pFrame->getPintoSize();
	//if (sz < 0) {
	//	sz = 0;
	//}
	//	if (sz > 90)sz = 180 - sz;
	return sz;
}

//void Enemy::anime() {
//	
//}

//////////////////////////////////////////////////////////////////////////
//
//�����_�[
//
//////////////////////////////////////////////////////////////////////////
void Enemy::Render() {
	if (!data)return;
	custom.argb = (alpha << 24 | custom.argb << 8 >> 8);
	float fp = sz - pFrame->getPintoSize();
	if (fp < 0) {
		fp = 0;
	}

	shader2D->SetValue("FPower", fp > 90 ? (180 - fp) / 90 : fp / 90);
	spr_data::Render(pos, data, &custom, custom.argb, shader2D, "depth");
}

void Enemy::UIRender() {
	if (data) {
		if (E_lenge(this, pFrame, FRAME_SIZE / 2)) {
			if ( state!=APPEARANCE ) {
				spr_data::Render(pos, &spr_pinto_s, u.argb, 0);
				//spr_data::Render(pos, &spr_pinto_s, &u.custom, u.argb);
				spr_data::Render(pos, &spr_pinto_a, 0xFFFFFFFF, /*z + pFrame->Get_f_z()   */ u.angle);
				//iexPolygon::Rect((SCREEN_WIDTH / 2) + z - DAMAGE_SIZE, PINTO_POSY, DAMAGE_SIZE + DAMAGE_SIZE, 20, 0, 0xFF00FFFF);// Z
			}
		}
	}
	//auto a = pos.x-pPlayer->pos.x;
	//auto b = pos.y-pPlayer->pos.y;
	//auto c = sqrt(a*a+b*b);
	//iexPolygon::Rect(pPlayer->pos.x, pPlayer->pos.y, c, 2, 0, 0xFFFFFFFF);

	//iexPolygon::Rect(pPlayer->pos.x, pPlayer->pos.y, pos.x-pPlayer->pos.x, pos.y-pPlayer->pos.y, 0, 0xFFFFFFFF);
	//line_rect(pos, V2(size.x * custom.scaleX, size.y * custom.scaleY), 0xFFFFFFFF, custom.scaleMode);



	//iexPolygon::Rect(pos.x,pos.y + 50,damage/ DAMAGE_LINE,10,0,0xFFFF0000); //damage_line
	//
	//iexPolygon::Rect(pos.x, pos.y, 1, 1, 0, 0xFFFF0000);//center

	////��
	//iexPolygon::Rect((pos.x - size.x), (pos.y + size.y), (size.x * 2),1, 0, 0xFFFF0000);//{
	//iexPolygon::Rect((pos.x - size.x), (pos.y - size.y), (size.x * 2),1, 0, 0xFFFF0000);//�@judge_line

	//////�c
	//iexPolygon::Rect((pos.x + size.x), (pos.y - size.y),1, size.y * 2, 0, 0xFFFF0000);//
	//iexPolygon::Rect((pos.x - size.x), (pos.y - size.y),1, size.y * 2, 0, 0xFFFF0000);//}

}


//������
void Enemy_Init(Enemy* obj) {
	obj->damage = 0;
	obj->timer = 0;
	obj->alpha = 255;
	obj->rangeflg = false;
	obj->noHit_flg = true;
	obj->Anime_Box = yellow_data;
	obj->animeData = obj->Anime_Box[normal];
}

inline void Enemy_Update(Enemy* obj) {
	//�_���[�W����
	if (!obj->zlock_flg) {
		obj->sz = pEnemy_Manager->get_sz(obj->z);
		obj->u.angle = (obj->z > pFrame->Get_f_z() ? obj->sz : -obj->sz);
	}
	else {
		if (obj->sz > pFrame->getPintoSize()) {
			obj->zlock_flg = NULL;
		}
	}
	obj->rangeflg = E_lenge(obj, pFrame, FRAME_SIZE / 2);
	if (obj->rangeflg) {
		pEnemy_Manager->damage_Calculation(obj);
		//�j���`��
		if ( obj->sz<JUSTPINTO_SIZE ) obj->DotLine();	 //�W���X�g�s���g
		else if ( obj->damageflg==true ) obj->DotLine(); //�ʏ�_���[�W
	}
	else {
		obj->animeData = obj->Anime_Box[normal];
	}

	//���]�`�F�b�N
	if ((obj->pos.x - pPlayer->pos.x)<0) obj->custom.reflectX = true;
	else obj->custom.reflectX = false;
	//���S�`�F�b�N
	if (obj->damage > obj->damageMAX) obj->state = DEAD;
}

//�o�����㓖���蔻��Ȃ�(�_��)
void Enemy_appearance(Enemy* obj) {
	obj->alpha = Frash_Alpha(obj->timer, 2, obj->alpha, 0.3f, 0.6f, 80); //�_��(�����x)
	if (obj->timer++ >= 80) { //��莞�Ԍo������
		obj->state = BEGIN;
		obj->timer = 0;
	}
}

//���S���G�t�F�N�g
void Enemy_DeadEffect(Enemy*obj) {
	Effect_Manager* fm = pEffect_Manager;
	for (int i = 0; i<5; i++) fm->searchSet(V2(obj->pos.x, obj->pos.y), V2((float)(rand() % 20 - 10), (float)(rand() % 20 - 10)), ParticleExt_k);	//�p�[�e�B�N���G�t�F�N�g�L���L��
	fm->searchSet(V2(obj->pos.x, obj->pos.y), V2(0.0f, 1.5f), CircleExt_lightB);	//�ۃG�t�F�N�g
	if (obj->sz < JUSTPINTO_SIZE) { //�W���X�g�s���g�͈̔͂Ȃ�G�t�F�N�g�ǉ�
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(0.0f, 1.5f), CircleExt);		//�ۃG�t�F�N�g
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(4.0f, 2.5f), CircleExt);		//�ۃG�t�F�N�g
		for (int i = 0; i<5; i++) pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2((float)(rand() % 20 - 10), (float)(rand() % 20 - 10)), ParticleExt_c);	//�p�[�e�B�N���G�t�F�N�g��
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(0, 0), Ext);				//�G���ŃG�t�F�N�g
		pEffect_Manager->searchSet(V2(6, 2), V2(15, 4), Shake); //�W���X�g�s���g�U��
	}
}

//�R���{�֐�
void Combo(Enemy* obj) {
	int combo = pScore->getCombo(); //�R���{��
	if ( combo>=2 ) { //2�R���{����
		int _combo = combo;
		int count = 0;
		int n = 0;
		int pos_x = 0;

		//�����𒲂ׂ�-----------------------------------
		while ( _combo>=10 ) { //10�ȏ�Ȃ�
			_combo /= 10;		//10�Ŋ�����
			count++;		//x�ʒu���炵�J�E���g
		}
		//�`��-------------------------------------------
		do {
			_combo = combo % 10;	//1�̈ʒ��o
			combo /= 10;			//1�̈ʐ؎̂Ĕr��
			pos_x = obj->pos.x+50+(count-(count-n)*-32); //x�ʒu���炵
			pEffect_Manager->searchSet(V2(pos_x, obj->pos.y-40), V2((float)_combo, 0), Combo);		//�R���{
			//count--;
			n++;
		} while ( combo>0 );

		pEffect_Manager->searchSet(V2(pos_x+59+count*32, obj->pos.y-36), V2(0, 0), ComboText);		//�R���{�e�L�X�g
	}
}


//���S�O�G�g��
void Enemy_Dead_ready(Enemy* obj) {
	obj->animeData = obj->Anime_Box[normal];
	obj->custom.scaleX = obj->custom.scaleY += 0.7f;
	if ( obj->custom.scaleX>5.0f ) obj->custom.scaleX = obj->custom.scaleY = 5.0f;
	if ( 4.0f<=obj->custom.scaleX )obj->alpha -= 255/4;
	if ( obj->alpha<0 ) {
		obj->alpha = 0;
		obj->state = DEAD2;
	}
}

//���S�G�t�F�N�g����������
void Enemy_Dead(Enemy* obj) {
	pFrame->add_Exorcise(KILL_CURE);
	pEnemy_Manager->jast_dragIn(obj);
	Enemy_DeadEffect(obj);			//���S���G�t�F�N�g
	pScore->add_KillScore(obj->score);		//�X�R�A,�R���{,kill�����Z
	//if ( pFrame->exorciseDwon_timer==0 ) pScore->combo=0; //�Q�[�W�؂�Ă�����R���{���Z�b�g
	if ( obj->sz<JUSTPINTO_SIZE ) pScore->eval_justpinto++; //�R���{���U���g_�W���X�g�s���g��
	if ( pFrame->exorciseDwon_timer==0 ) Combo(obj);						//�R���{�\��
	if (obj->sz < JUSTPINTO_SIZE)	IEX_PlaySound(SE_JUSTPINTO, FALSE);	//���Ŏ���SE(�W���X�g�s���g)
	else IEX_PlaySound(SE_EXT, FALSE);	//���Ŏ���SE
	pPlayer->mltfcs.add_point(1);
	obj->clear();

}



////////////////////////////////////////////////////////////////////////////////////////////
//
//�@�G�֐�
//
////////////////////////////////////////////////////////////////////////////////////////////

//�����Ȃ��G
void Base(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:	//�����ݒ�
		obj->data = &Enemy_data;
		obj->damageMAX = DAMAGE_MAX;
		obj->custom.argb = 0x0000FFFF;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->LockTime = 1;
		Enemy_Init(obj);
		obj->state = BEGIN;
		//break;
	case BEGIN:
		//�_���[�W����
		Enemy_Update(obj);
		break;
	case DEAD: //���S����
		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}


//�߂Â�����p�������G
void Sudden(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //�����ݒ�
		obj->data = &Enemy_data;
		obj->damageMAX = DAMAGE_MAX;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		Enemy_Init(obj);
		obj->LockTime = 1;
		obj->state = BEGIN;
		//break;
	case BEGIN:
		Enemy_Update(obj);
		obj->rangeflg = E_lenge(obj, pPlayer, 300); //��������
		if (obj->rangeflg == true) {
			obj->alpha += (255 / 20);				//
			if (obj->alpha>255) obj->alpha = 255;	//
		}											//	
		else {										//	�_�o�S�v����
			obj->alpha -= (255 / 20);				//
			if (obj->alpha<0) obj->alpha = 0;		//
		}											//
		break;
	case DEAD: //���S����
		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}


//�e���|�[�g
void Teleport(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //�����ݒ�
		Enemy_Init(obj);
		obj->Anime_Box = blue_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];
		//HP
		obj->LockTime = ENEMY_LOCKTIME_C;
		obj->damageMAX = ENEMY_HP_C;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->score = 100;
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:
		obj->rangeflg = E_lenge(obj, pPlayer, 400); //��������
		if (obj->rangeflg == true) { //�͈͓��Ȃ�
			obj->state = STOP;
		}
		break;
	case STOP: //��~����
		Enemy_Update(obj);
		if (obj->timer++>100) {
			obj->timer = 0;
			obj->state = EFFECT;
		}
		break;
	case EFFECT: //�e���|�[�g�G�t�F�N�g
		pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y), V2(0, 0), TeleportExt);
		obj->alpha = 0;
		obj->state = BEGIN2;
		break;
	case BEGIN2: //���W�ړ�
		Enemy_Update(obj);
		//---------------------------------------------------------------------
		//obj->pos.x += ( (rand()%3-1)*200 );
		//obj->pos.y += ( (rand()%3-1)*200 );
		obj->pos.x += ( (float)(rand()%201-100)*0.01f*200.0f );
		obj->pos.y += ( (float)(rand()%201-100)*0.01f*200.0f );
		if ( obj->pos.x<100 ) obj->pos.x += 200;
		if ( (SCREEN_WIDTH-100)<obj->pos.x ) obj->pos.x -= 200;
		if ( obj->pos.y<100 ) obj->pos.y += 200;
		if ( (SCREEN_HEIGHT-100)<obj->pos.y ) obj->pos.y -= 200;
		//---------------------------------------------------------------------
		obj->state = FLASHING;
		break;
	case FLASHING: //�_�ŏ���
		Enemy_Update(obj);
		obj->timer++;
		if (obj->timer % 5<3) obj->alpha = (int)(255 * 0.3f); //0,1,2�̎�
		else				  obj->alpha = (int)(255 * 0.6f); //3,4,5�̎�
		if (obj->timer >= 50) {
			obj->alpha = 255;
			obj->state = BEGIN;
			obj->timer = 0;
		}
		break;
	case LOCK:
		Enemy_Update(obj);
		
		break;

	case DEAD:
		Enemy_Dead_ready(obj);
		break;

	case DEAD2:
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_blue++;
		break;

	default:
		break;
	}
}


//�P���Ă���G
void Normal(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //�����ݒ�
		Enemy_Init(obj);
		obj->Anime_Box = pink_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];
		//HP
		obj->damageMAX = ENEMY_HP_B;
		obj->LockTime = ENEMY_LOCKTIME_B;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->score = 100;
		obj->state = APPEARANCE;
		
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:	//�����͈͓��Ȃ�v���C���[�ɋ߂Â�
		Enemy_Update(obj);
		obj->rangeflg = E_lenge(obj, pPlayer, 300); //��������
		if (obj->rangeflg == true) {
			obj->pos -= E_P(obj, pPlayer, obj->spd); //�ړ�����
		}
		break;
	case LOCK:
		Enemy_Update(obj);

		break;

	case DEAD:
		Enemy_Dead_ready(obj);
		break;
	case DEAD2:
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_pink++;
		break;
	default:
		break;
	}
}


//�G(�ːi)
void Tombo(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:
		Enemy_Init(obj);
		obj->Anime_Box = green_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];
		//HP
		obj->damageMAX = ENEMY_HP_F;
		obj->LockTime = ENEMY_LOCKTIME_F;

		obj->pos.y -= 10;			//----------
		obj->ANGLE = INIT_ANGLE;	//�@��]�p
		obj->ANGLEspd = 0.5f;		//
		obj->RADIUS = 6.0f;			//----------
		obj->f_work[0] = 0;	//���W�ۑ��p
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->size = V2(20 / 2, 20 / 2);
		obj->score = 100;
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:
		Enemy_Update(obj);
		obj->rangeflg = E_lenge(obj, pPlayer, 1000); //��������
		if (obj->rangeflg == true) { //�͈͓��Ȃ�

			//obj->spd = E_P(obj, pPlayer, obj->spd); //�ړ����� 8.0f

			obj->dx = obj->pos.x - pPlayer->pos.x;				//
			obj->dy = obj->pos.y - pPlayer->pos.y;				//
			obj->dist = sqrtf(obj->dx*obj->dx + obj->dy*obj->dy);	//�ړ��ʌv�Z
			obj->spd.x = 8.0f * obj->dx / obj->dist;				//
			obj->spd.y = 8.0f * obj->dy / obj->dist;				//

			obj->state = MOVE;
		}
		break;
	case MOVE: //�ړ�����(�t)
		Enemy_Update(obj);
		if (obj->timer++<30) obj->pos += obj->spd*0.2f;
		else {
			obj->state = STOP;
			obj->timer = 0;
		}
		break;
	case STOP: //��~����
		Enemy_Update(obj);
		if (obj->timer++>10) {
			obj->timer = 0;
			obj->state = MOVE2;
		}
		break;
	case MOVE2: //�ړ�����(����)
		Enemy_Update(obj);
		if (obj->timer++>40) {
			obj->state = STOP2;
			obj->timer = 0;
		}
		else obj->pos -= obj->spd;

		break;
	case STOP2: //��~����
		Enemy_Update(obj);
		if (obj->timer++>100) {
			obj->timer = 0;
			obj->state = ROTATE;
			obj->f_work[0] = obj->pos.x; //���W��ۑ�
		}
		//�_���[�W����
		break;
	case ROTATE: //��]����
		Enemy_Update(obj);
		obj->XCENTER = obj->pos.x; //��]�̒��S
		obj->YCENTER = obj->pos.y; //��]�̒��S
		obj->ANGLE += obj->ANGLEspd;
		obj->pos.x = obj->XCENTER + obj->RADIUS*cosf(obj->ANGLE);
		obj->pos.y = obj->YCENTER + obj->RADIUS*sinf(obj->ANGLE);
		//if ( obj->f_work[0] < obj->pos.x &&  
		//	obj->pos.x < (obj->pos.x + (obj->XCENTER+obj->RADIUS*cosf(obj->ANGLE)) - 0.1f) ) { //�O�̍��W�ɖ߂�����
		//	obj->state = BEGIN;
		//}
		if (obj->timer++>15) {
			obj->state = BEGIN;
			obj->timer = 0;
		}
		break;
	case LOCK:
		Enemy_Update(obj);

		break;

	case DEAD:
		Enemy_Dead_ready(obj);
		break;
	case DEAD2:
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_green++;
		break;
	default:
		break;
	}
}


//�P���Ă���G
void zMove(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //�����ݒ�
		Enemy_Init(obj);
		obj->Anime_Box =white_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];

		obj->f_work[3] = obj->z;
		//HP
		obj->damageMAX = ENEMY_HP_D;
		obj->LockTime = ENEMY_LOCKTIME_D;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->size = V2(20 / 2, 20 / 2);
		obj->score = 100;
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:	//�����͈͓��Ȃ�v���C���[�ɋ߂Â�
		Enemy_Update(obj);
		obj->pos -= E_P(obj, pPlayer, obj->spd); //�ړ�����
		{
			float y = 100 * (sinf(obj->ANGLE * 0.01745f));
			obj->ANGLE += 0.5f;
			//obj->ANGLE++;
			if (obj->ANGLE > 360) {
				obj->ANGLE = 0;
			}
			obj->z = obj->f_work[3];
			obj->z += y;
			if (90 < obj->z) obj->z -= 180;
			if (-90 > obj->z) obj->z += 180;
		}
		//�_���[�W����
		break;
	case LOCK:
		Enemy_Update(obj);

		break;

	case DEAD:
		Enemy_Dead_ready(obj);
		break;
	case DEAD2:
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_white++;
		break;
	default:
		break;
	}
}


//�f�J�C(�������Ă���)
void Big(Enemy* obj) {
	switch (obj->state) {
	case INIT:
		Enemy_Init(obj);
		//obj->data = &Enemy_data;
		obj->Anime_Box =kari_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];
		//HP
		obj->damageMAX = ENEMY_HP_E;
		obj->LockTime = ENEMY_LOCKTIME_E;
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = B_scale;
		obj->size = V2(32, 32);
		obj->score = 200;
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:	//�����͈͓��Ȃ�v���C���[�ɋ߂Â�
		Enemy_Update(obj);

		obj->rangeflg = E_lenge(obj, pPlayer, 500); //��������
		if (obj->rangeflg == true) {
			obj->pos -= E_P(obj, pPlayer, obj->spd); //�ړ�����
		}
		break;
	case LOCK:
		Enemy_Update(obj);

		break;

	case DEAD:
		Enemy_Dead_ready(obj);
		break;
	case DEAD2:
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_kari++;
		break;
	default:
		break;
	}
}


/////////////////////////////////////////////////////////////
//
//��]���V
//
/////////////////////////////////////////////////////////////

enum
{
	posx = 0,
	posy = 1,
};




/////////////////////////////////////////////////////////////
//
//�W����
//
/////////////////////////////////////////////////////////////
enum Ag //Aggre
{
	//����

	//�e
	child_num = 0,
	//�q
	lenge = 0,
};

//�W���̐���
void Aggre(Enemy* obj) {

	switch (obj->state)
	{
	case INIT:
		//�����ݒ�
		Enemy_Init(obj);
		obj->data = NULL;
		obj->noHit_flg = false;
		//�e����
		pEnemy_Manager->searchSet(V2(0.0f, 0.0f), V2(0.0f, 0.0f), &Aggre_parent, (float)rand_PINTO, obj);
		{
			float angle = 360 * 0.16666f;
			//�q������				//
			pEnemy_Manager->searchSet(V2((float)(angle * 0), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 1), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 2), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 3), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 4), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
			pEnemy_Manager->searchSet(V2((float)(angle * 5), 0), V2(0.0f, 0.0f), &Aggre_child, (float)rand_PINTO, obj);
		}
		obj->f_work[child_num] = 0;
		obj->size = V2(20 / 2, 20 / 2);
		obj->state = MOVE;
		break;
	case MOVE: //�ړ�����
		obj->pos.x++;						//�� //todo�ӂ�ӂ�ړ�
		if (obj->f_work[child_num] <= 0) {	//�q���̗L�����m�F
			obj->state = DEAD;				//�����Ȃ玀�S
		}
		break;
	case DEAD: //���S����
		//Enemy_Dead(obj);
		obj->clear();
		break;
	default:
		break;
	}
}
//�W���́Q�e
void Aggre_parent(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:
		Enemy_Init(obj);
		obj->data = &Enemy_data;
		//�e�ݒ�(����Ɏ��g�̑��݂�n��)
		obj->damageMAX = DAMAGE_MAX;

		((Enemy*)(obj->parent))->f_work[child_num]++;
		obj->pos = V2(0, 0);
		obj->spd = V2(0, 0);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = B_scale;
		obj->state = MOVE;
		//break;
	case MOVE: //�ړ�����
		Enemy_Update(obj);
		//����ɍ��킹�ē���
		obj->pos = ((Enemy*)(obj->parent))->pos;
		//�_���[�W����
		break;
	case DEAD: //���S����
		((Enemy*)(obj->parent))->f_work[child_num]--;
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_kari++;

		break;
	default:
		break;
	}
}
//�W���́Q�q
void Aggre_child(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:
		Enemy_Init(obj);
		obj->data = &Enemy_data;
		//�e�ݒ�(����Ɏ��g�̑��݂�n��)
		((Enemy*)(obj->parent))->f_work[child_num]++;
		obj->ANGLE = obj->pos.x;
		obj->pos = V2(0, 0);
		obj->spd = V2(0, 0);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = C_scale;
		obj->damageMAX = DAMAGE_MAX;
		obj->size = V2(20 / 2, 20 / 2);
		obj->state = MOVE;
		//break;
	case MOVE:
		//����ɍ��킹�ē���(�e�̎��͂���])
		Enemy_Update(obj);
		{
			//��]�v�Z
			float y = sinf(obj->ANGLE * 0.01745f);
			float x = cosf(obj->ANGLE * 0.01745f);
			obj->pos = ((Enemy*)(obj->parent))->pos;
			obj->pos += V2(x * 100, y * 100);
			obj->ANGLE++;
			if (obj->ANGLE > 360) {
				obj->ANGLE = 0;
			}
		}
		break;
	case DEAD: //���S����
		((Enemy*)(obj->parent))->f_work[child_num]--;
		pEnemy_Kill->kill_num_kari++;

		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}


//�W���̐���(Rotetion)��
void Rotation_Aggre_4(Enemy* obj) {
	switch (obj->state)
	{
	case INIT: //�����ݒ�
		obj->data = NULL;
		pEnemy_Manager->searchSet(V2(0.0f, 0.0f), V2(0.0f, 0.0f), &Rotation, (float)rand_PINTO);
		pEnemy_Manager->searchSet(V2(50.0f, 80.0f), V2(0.0f, 0.0f), &Rotation, (float)rand_PINTO);
		pEnemy_Manager->searchSet(V2(50.0f, -80.0f), V2(0.0f, 0.0f), &Rotation, (float)rand_PINTO);
		pEnemy_Manager->searchSet(V2(100.0f, 0.0f), V2(0.0f, 0.0f), &Rotation, (float)rand_PINTO);
		obj->state = MOVE;
	case MOVE:
		//Enemy_Update(obj);
		obj->state = CLEAR;
		//�_���[�W����
		break;
	case DEAD: //���S����
		Enemy_Dead(obj);
		break;
	case CLEAR:
		obj->clear();
	default:
		break;
	}
}

void Rotation(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:
		Enemy_Init(obj);
		obj->Anime_Box = yellow_data;
		obj->animeData = obj->Anime_Box[normal];
		obj->data = &obj->animeData[0];

		//�e�ݒ�(����Ɏ��g�̑��݂�n��)
		obj->damageMAX = ENEMY_HP_A ;
		obj->LockTime = ENEMY_LOCKTIME_A;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->score = 100;
		obj->state = APPEARANCE;
		//break;
	case APPEARANCE:
		Enemy_appearance(obj);
		break;
	case BEGIN:
		//����ɍ��킹�ē���(�e�̎��͂���])
		Enemy_Update(obj);
		{
			//��]�v�Z
			obj->pos -= V2(obj->f_work[posx], obj->f_work[posy]);
			float y = 70 * (sinf(obj->ANGLE * 0.01745f));
			float x = 50 * (cosf(obj->ANGLE * 0.01745f));
			obj->f_work[posx] = x;
			obj->f_work[posy] = y;

			obj->pos += V2(x, y);
			obj->ANGLE += 0.5;
			if (obj->ANGLE > 360) {
				obj->ANGLE = 0;
			}
		}
		break;
	case LOCK:
		Enemy_Update(obj);

		break;

	case DEAD:
		Enemy_Dead_ready(obj);
		break;
	case DEAD2:
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_yellow++;
		break;
	default:
		break;
	}
}


void Tutorial(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:	//�����ݒ�
		Enemy_Init(obj);
		obj->data = &Enemy_data;
		obj->damageMAX = DAMAGE_MAX;
		obj->custom.argb = 0x0000FFFF;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->state = BEGIN;
		//break;
	case BEGIN:
		//�_���[�W����
		Enemy_Update(obj);
		break;
	case DEAD: //���S����
		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}



void tuto_Base(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:	//�����ݒ�
		Enemy_Init(obj);
		obj->damageMAX = DAMAGE_MAX;
		//obj->custom.argb = 0x0000FFFF;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->state = BEGIN;
		//break;
	case BEGIN:
		//�_���[�W����
		Enemy_Update(obj);
	
		break;
	case DEAD: //���S����
		Enemy_Dead(obj);

		break;
	default:
		break;
	}
}

void tuto_rock(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:	//�����ݒ�
		Enemy_Init(obj);
		obj->damageMAX = DAMAGE_MAX;
		//obj->custom.argb = 0x0000FFFF;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->state = BEGIN;
		//break;
	case BEGIN:
		//�_���[�W����
	
		Enemy_Update(obj);
		if (!obj->zlock_flg) {
			obj->damage = 0;
		}
		//���]�`�F�b�N
		if ((obj->pos.x - pPlayer->pos.x)<0) obj->custom.reflectX = true;
		else obj->custom.reflectX = false;
		//���S�`�F�b�N
		if (obj->damage > obj->damageMAX) obj->state = DEAD;
		break;
	case DEAD: //���S����
		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}

void tuto_justpinto(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:	//�����ݒ�
		Enemy_Init(obj);
		obj->damageMAX = DAMAGE_MAX;
		//obj->custom.argb = 0x0000FFFF;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->state = BEGIN;
		//break;
	case BEGIN:
		//�_���[�W����
		if (!obj->zlock_flg) {
			obj->sz = pEnemy_Manager->get_sz(obj->z);
		}

		if (obj->zlock_flg) {
			obj->rangeflg = E_lenge(obj, pFrame, FRAME_SIZE / 2);
			if (obj->rangeflg) {
				if (obj->sz < 2)
				{
					if (pFrame->lockPinto_trg == true) {
						pEffect_Manager->searchSet(obj->pos, V2(0, 0), pinto_lock); //�s���g���b�N�G�t�F�N�g
						pEffect_Manager->searchSet(V2(obj->pos.x, obj->pos.y - 50), V2(0, 0), Lock); //Lock�G�t�F�N�g
						obj->zlock_flg = true;
					}
					if (obj->damage>(obj->damageMAX - obj->damageMAX / 4)) Frash_white(obj, 11); //���_��(��)
					else Frash_white(obj, 35); //���_��(�x)
					obj->damage += DAMAGE;
					obj->damageflg = true;
				}
				else {
					if (obj->Anime_Box) {
						obj->damageflg = false;
						obj->animeData = obj->Anime_Box[normal];
						obj->alpha = 255;
					}
				}
			}
		}
		//���]�`�F�b�N
		if ((obj->pos.x - pPlayer->pos.x)<0) obj->custom.reflectX = true;
		else obj->custom.reflectX = false;
		//���S�`�F�b�N
		if (obj->damage > obj->damageMAX) obj->state = DEAD;
		break;
	case DEAD: //���S����
		Enemy_Dead(obj);
		break;
	default:
		break;
	}
}

void tuto_multifocus(Enemy* obj) {
	switch (obj->state)
	{
	case INIT:	//�����ݒ�
		Enemy_Init(obj);
		obj->damageMAX = DAMAGE_MAX;
		obj->size = V2(20 / 2, 20 / 2);
		obj->custom.scaleMode = CENTER;
		obj->custom.scaleX = obj->custom.scaleY = N_scale;
		obj->state = BEGIN;
		//break;
	case BEGIN:
		//�_���[�W����
		obj->sz = 45;

		obj->rangeflg = E_lenge(obj, pFrame, FRAME_SIZE / 2);
		if (obj->rangeflg) {
			pEnemy_Manager->damage_Calculation(obj);
		}
		//���]�`�F�b�N
		if ((obj->pos.x - pPlayer->pos.x)<0) obj->custom.reflectX = true;
		else obj->custom.reflectX = false;
		//���S�`�F�b�N
		if (obj->damage > obj->damageMAX) obj->state = DEAD;

		break;
	case DEAD:
		Enemy_Dead_ready(obj);
		break;
	case DEAD2:
		Enemy_Dead(obj);
		pEnemy_Kill->kill_num_pink++;
		break;
	default:
		break;
	}
}