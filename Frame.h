#ifndef _FRAME_H_
#define _FRAME_H_
//�s���g���
#define FRAME_ACT (1.5f)		//�����x
#define FRAME_ACT_MAX (4.0f)	//�ő�����x
#define FRAME_ACT_R (2.5f)	//�����x��R
#define FRAME_SIZE (774)


#define MALTIFOCUS_TIME (180)

#define DAMAGE_SIZE (90)
//�t�H�[�J�X
//#define PINTO_ACT (0.55f)
//#define PINTO_ACT_MAX (4.0f)
//#define PINTO_ACT_R (0.4f)

#define PINTO_X_USE (false)//�v�Z��X�����g��
#define PINTO_Y_USE (true)//�v�Z��Y�����g��

#define MLTFCS_MAXLV (3)
//#define PINTO_ACT (5.0f)
#define PINTO_ACT (2.5 * (f_spd * f_spd))

#define PINTO_POSY (480)
#define PINTO_MAX (90)

//----------------------------------------------------------------------
//		���
//----------------------------------------------------------------------
#define EXORCISE_MAX (100) //��͍ő�l 
#define PINTO_COST_S (20.0f * 0.01666F) //�s���g��������/f
#define PINTO_DOWN_TIME (60*3) //UI�_�E���^�C��
#define KILL_CURE (5 + (10 * (obj->sz / PINTOMODE_DEFAULT)))	//�G�l�~�[���j���Q��͉񕜗�
#define EXORCISE_AUTOHEEL (5.5)	//���R��
#define EXORCISE_AUTOHEEL_TIME (90)//���R�񕜊J�n����
#define USE_PINTOLOCK (15) //�s���g���b�N�����
//----------------------------------------------------------------------



#define PINTO_SENSITIVE (100.0f) //���x 1000 ~ -1000

#define PINTOMODE_READY (-1)
#define PINTOMODE_DEFAULT (16)//�s���g��
#define PINTOMODE_MULTIFOCUSLV1 (24)
#define PINTOMODE_MULTIFOCUSLV2 (56)
#define PINTOMODE_MULTIFOCUSLV3 (180)


class Frame:public OBJ2D ,public Singleton<Frame>
{
public:
	//Frame();

	//~Frame();
	void Init();
	void Update();
	void Render();
	
	void SetMain();
	
	void R_Update();

	bool lock_flg;

	bool exorciseDwon_flg;
	bool multifocus_flg;
	TRG lockPinto_trg;
	TRG lockPinto_exorciseDwon;
	//-----------------------------------------------------
//
// �s���g�p�ϐ��A�֐�
//
//-----------------------------------------------------
	void f_move();
	void exorcise_Update();
	void Frame::clear();
	bool move_flg;//��]�ǂݎ��
	int exorciseDwon_timer;
	float Get_f_z();
	float getPintoSize();
	int multifocus_timer;
	void add_Exorcise(float);
	void use_Multifocus(int);
	void use_lockPinto();
	float get_sz(float z);
	void lockPinto_exorcise(int add) {
		if (lockPinto_exorciseDwon == false) {
			lockPinto_exorciseDwon = TRUE;
			exorcise -= add;
		}
	}
	D3DCOLOR Frash_Color_pinto(int timer,int num,D3DCOLOR argb,D3DCOLOR argb1,D3DCOLOR argb2,D3DCOLOR argb3);

	float exorcise;				//��͐��l�@1 �` 100
private:
	float act;
	float angle;
	float axisx;
	float axisy;
	float f_z;	//�s���g�l
	float f_spd;//�s���g�ύX���x
	int f_timer;
	float pintoSize;
	D3DCOLOR pinto_argb;
	bool multi_flg;

	D3DCOLOR argb;		//�F(��̓Q�[�W�_�ŗp)
	float old_exorcise; //��r�p��͐��l(��̓Q�[�W�_�ŗp)
	int flash_timer;	//�_��timer(��̓Q�[�W�_�ŗp)
	bool flash_flg;
	D3DCOLOR out_argb;
	int count;

	D3DCOLOR light_argb; //�����p

};


#endif // !_FRAME_H_

#define pFrame (Frame::getInstance())