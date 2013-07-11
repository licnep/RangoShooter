#include "loader.h"
#include <stdlib.h>
#include <time.h>

struct position
{
	struct aiVector3D traslazione, rotazione, scalamento;
	int livello,movimento,check;
};

struct level{
	struct position posizione[18];
};

struct motion{
	int stato,count,continua,temp_rel,dt,timer;
	float angle;
};

struct m_time{
	float v,tempof;
	int offset,tempoi;
};

struct personaggio {
	int id,punteggio,life;
};

struct indice_personaggi{
	struct personaggio character[10];
};

level InitPos(void);

indice_personaggi InitPers(void);

position def_pos (int liv, int mov, aiVector3D t, aiVector3D r, aiVector3D s);

level def_liv (position p0, position p1,position p2,position p3,position p4,position p5,
			   position p6, position p7,position p8,position p9,position p10,position p11,
			   position p12, position p13,position p14,position p15,position p16,position p17);

personaggio def_pers (int pers_id, int life, int points);

indice_personaggi def_indice(personaggio p0,personaggio p1,personaggio p2,personaggio p3,personaggio p4,
							 personaggio p5,personaggio p6,personaggio p7,personaggio p8,personaggio p9);

void renderLevel (const struct aiScene *sc, const struct aiScene *sc1, const struct aiScene *sc2, int level);

void lista_target(GLuint scene_list, const struct aiScene *sc);

int scegli_pos(int livello, level livelli);

void def_mov(int pos, float angle, int vel);

int render_target(GLuint scene_list,int pos, level l, motion m, int ch, int vel);

void render_case(int livello,GLuint scene_list);

motion scegli_mov(motion m,level l, int pos, int tempoi, float vel, indice_personaggi index, int ch);

motion do_motion1 (motion m,int tempoi,int wait);

motion do_motion2 (motion m,int tempoi);

motion reset_motion(motion m);

m_time count_time (m_time t);

m_time reset_time(m_time t);