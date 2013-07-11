#include "trgt_crct.h"

level InitPos(void)
{
    
	struct level lev;
	struct aiVector3D trasl,rot,scal;
	struct position destra_11,sinistra_11,centro_11,destra_12,sinistra_12,centro_12;
	struct position destra_21,sinistra_21,centro_21,destra_22,sinistra_22,centro_22;
	struct position destra_31,sinistra_31,centro_31,destra_32,sinistra_32,centro_32;
    
	//livello 1
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=-10,trasl.y=-8.45,trasl.z=3.5;
	destra_11=def_pos(1,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=2.5,trasl.y=9.776,trasl.z=0.4;
	centro_11=def_pos(1,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=11,trasl.y=-8.45,trasl.z=3.5;
	sinistra_11=def_pos(1,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=19.795,trasl.y=-7.183,trasl.z=-8;
	destra_12=def_pos(1,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=32.8,trasl.y=12.644,trasl.z=-5.026;
	centro_12=def_pos(1,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=36.892,trasl.y=1.789,trasl.z=0.0807;
	sinistra_12=def_pos(1,1,trasl,rot,scal);
	//---------------------
	
	//livello 2
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=-2,trasl.y=12.33,trasl.z=-3.8;
	destra_21=def_pos(2,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=3.017,trasl.y=1.181,trasl.z=-2.280;
	centro_21=def_pos(2,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=11,trasl.y=-8.88,trasl.z=3.5;
	sinistra_21=def_pos(2,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=17.9,trasl.y=-7.5,trasl.z=-1.6;
	destra_22=def_pos(2,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=-10;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=23.8,trasl.y=6.05,trasl.z=-0.9;
	centro_22=def_pos(2,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=-20,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=33,trasl.y=-9,trasl.z=0.08;
	sinistra_22=def_pos(2,1,trasl,rot,scal);
	//---------------------
	
	//livello 3
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=-11.14,trasl.y=-0.45,trasl.z=32.519;
	destra_31=def_pos(3,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=-10;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=7.553,trasl.y=0.253,trasl.z=40;
	centro_31=def_pos(3,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=13.0,trasl.y=-6.57,trasl.z=32.168;
	sinistra_31=def_pos(3,2,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=12.093,trasl.y=16.055,trasl.z=32.276;
	destra_32=def_pos(3,1,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=38,trasl.y=-7.149,trasl.z=45.58;
	centro_32=def_pos(3,2,trasl,rot,scal);
	//---------------------
	rot.x=0,rot.y=0,rot.z=0;
	scal.x=1,scal.y=1,scal.z=1;
	trasl.x=55.46,trasl.y=16.7,trasl.z=36.645;
	sinistra_32=def_pos(3,2,trasl,rot,scal);
	//---------------------
	
	lev=def_liv(destra_11,centro_11,sinistra_11,destra_12,centro_12,sinistra_12,
				destra_21,centro_21,sinistra_21,destra_22,centro_22,sinistra_22,
				destra_31,centro_31,sinistra_31,destra_32,centro_32,sinistra_32);
	
	return lev;
    
}


// ----------------------------------------------------------------------------

indice_personaggi InitPers(void)
{
    
	struct indice_personaggi index;
	struct personaggio ragazza,bambina,uccello,rospo,coniglio,cane,tasso,geko,tartarugha,serpente;
    
	int norm=70,bonus=35;
    int point_friend = - 10;
    int point_enemy = 10;
    
    // the bad guys
	tartarugha=def_pers(1,bonus, point_enemy * 3);
	serpente=def_pers(3,bonus, point_enemy * 3);
	coniglio=def_pers(4,norm, point_enemy);
	tasso=def_pers(5,norm, point_enemy);
	cane=def_pers(6,norm, point_enemy);
	geko=def_pers(7,norm, point_enemy);
    
    // the good guys
    uccello=def_pers(0,norm, point_friend);
	bambina=def_pers(8,norm,point_friend);
	rospo=def_pers(9,norm, point_friend);
    ragazza=def_pers(2,norm, point_friend);
    
	index=def_indice(uccello,tartarugha,ragazza,serpente,coniglio,tasso,cane,geko,bambina,rospo);
	
	return index;
    
}


// ----------------------------------------------------------------------------

position def_pos (int liv, int mov, aiVector3D t, aiVector3D r, aiVector3D s)
{
    
	position p;
    
	p.livello=liv;
	p.movimento=mov;
	p.rotazione=r;
	p.scalamento=s;
	p.traslazione=t;
	p.check=0;
    
	return p;
    
}


// ----------------------------------------------------------------------------

level def_liv (position p0, position p1,position p2,position p3,position p4,position p5,
			   position p6, position p7,position p8,position p9,position p10,position p11,
			   position p12, position p13,position p14,position p15,position p16,position p17)
{
    
	struct level liv;
    
	liv.posizione[0]=p0;
	liv.posizione[1]=p1;
	liv.posizione[2]=p2;
	liv.posizione[3]=p3;
	liv.posizione[4]=p4;
	liv.posizione[5]=p5;
	liv.posizione[6]=p6;
	liv.posizione[7]=p7;
	liv.posizione[8]=p8;
	liv.posizione[9]=p9;
	liv.posizione[10]=p10;
	liv.posizione[11]=p11;
	liv.posizione[12]=p12;
	liv.posizione[13]=p13;
	liv.posizione[14]=p14;
	liv.posizione[15]=p15;
	liv.posizione[16]=p16;
	liv.posizione[17]=p17;
    
	return liv;
    
}


// ----------------------------------------------------------------------------

personaggio def_pers (int pers_id, int life, int points)
{
    
	personaggio p;
    
	p.id=pers_id;
	p.life=life;
	p.punteggio=points;
    
	return p;
    
}


// ----------------------------------------------------------------------------

indice_personaggi def_indice(personaggio p0,personaggio p1,personaggio p2,personaggio p3,personaggio p4,
							 personaggio p5,personaggio p6,personaggio p7,personaggio p8,personaggio p9)
{
    
    indice_personaggi i;
    
    i.character[0]=p0;
    i.character[1]=p1;
    i.character[2]=p2;
    i.character[3]=p3;
    i.character[4]=p4;
    i.character[5]=p5;
    i.character[6]=p6;
    i.character[7]=p7;
    i.character[8]=p8;
    i.character[9]=p9;
    
    return i;
    
}

// ----------------------------------------------------------------------------

void renderLevel (const struct aiScene *sc, const struct aiScene *sc1, const struct aiScene *sc2, int level){

	/*glPushMatrix();
    glTranslatef(0,-2,0);
	recursive_render(sc,sc->mRootNode,1.0);
	glPopMatrix();
	//recursive_render(sc,sc->mRootNode->mChildren[55],1.0);
	return;*/
    switch (level) {
        case 1:
            recursive_render(sc,sc->mRootNode, 1.0);
            break;
        case 2:
            recursive_render(sc1,sc->mRootNode, 1.0);
            break;
        case 3:
            recursive_render(sc2,sc->mRootNode, 1.0);
            break;
    }
}


// ----------------------------------------------------------------------------

void lista_case(GLuint scene_list, const struct aiScene *sc,const struct aiScene *sc1,const struct aiScene *sc2)
{
	glNewList(scene_list, GL_COMPILE);
	//recursive_render(sc,sc->mRootNode->mChildren[0], 1.0);//Terreno
	recursive_render(sc,sc->mRootNode, 1.0);
	glEndList();
    
	glNewList(scene_list, GL_COMPILE);
	//recursive_render(sc,sc->mRootNode->mChildren[0], 1.0);//Terreno
	recursive_render(sc1,sc1->mRootNode, 1.0);
	glEndList();
	
	glNewList(scene_list, GL_COMPILE);
	//recursive_render(sc,sc->mRootNode->mChildren[0], 1.0);//Terreno
	recursive_render(sc2,sc2->mRootNode, 1.0);
	glEndList();
}


// ----------------------------------------------------------------------------

void lista_target(GLuint scene_list, const struct aiScene *sc)
{
	
	for(int i=0; i<10;i++){
		glNewList(scene_list+i, GL_COMPILE);
		recursive_render(sc,sc->mRootNode->mChildren[i], 1.0);
		glEndList();
	}
    
}


// ----------------------------------------------------------------------------

int scegli_pos(int livello, level livelli)
{
    
	int pos = 0;
	
    srand((int)time(NULL));
    
    if(livello==1){
        pos = rand() %6;
    } else if(livello==2) {
        pos = rand() %6 +6;
    } else if(livello==3) {
        pos = rand() %6 +12;
    }
    
	return pos;
}


// ----------------------------------------------------------------------------

void def_mov(int pos, float angle, int vel)
{
    
	if((pos>-1&&pos<3)||(pos>4&&pos<7)|| pos==8 || (pos>9&&pos<12) || pos==13 || pos==15){
		glRotatef(-90.f,1.f,0.f,0.f);
		glRotatef(angle,1.f,0.f,0.f);
		glTranslatef(0.f,1.5f,0.f);
	}
    
	if(pos==4){
        glRotatef(-angle,1.f,0.f,0.f);
        glRotatef(90,1.f,0.f,0.f);
        glTranslatef(0.f,-1.5f,0.f);
    }
    
	if(pos==3 || pos==9){
		glRotatef(angle,0.f,1.f,0.f);
		glTranslatef(0.5f,0.f,0.f);
		glRotatef(-90.f,0.f,1.f,0.f);
	}
    
	if(pos==7){
		glRotatef(angle,0.f,0.f,1.f);
		glRotatef(-90.f,0.f,0.f,1.f);
		glTranslatef(0.f,1.5f,0.f);
	}
    
	if(pos==12){
		glRotatef(-angle,0.f,1.f,0.f);
		glTranslatef(0.5f,0.f,0.f);
		glRotatef(90.f,0.f,1.f,0.f);
	}
    
	if(pos==14)glTranslatef(0.f,angle/9,0.f);
	if(pos==16)glTranslatef(0.f,0.f,-angle/20);
	if(pos==17)glTranslatef(-angle/9,0.f,0.f);
    
}


// ----------------------------------------------------------------------------

int render_target(GLuint scene_list,int pos, level l, motion m, int ch, int vel)
{
    
	if(m.angle==0 && m.count==0)ch=rand() %10;
    
	glPushMatrix();
    glLoadName(100+pos);
    glTranslatef(l.posizione[pos].traslazione.x,l.posizione[pos].traslazione.y,l.posizione[pos].traslazione.z);
	glRotatef(l.posizione[pos].rotazione.x,1.f,0.f,0.f);
	glRotatef(l.posizione[pos].rotazione.y,0.f,1.f,0.f);
	glRotatef(l.posizione[pos].rotazione.z,0.f,0.f,1.f);
	def_mov(pos,m.angle,vel);
	if(m.stato!=2)glCallList(scene_list+ch);
	glPopMatrix();
    
	return ch;
}


// ----------------------------------------------------------------------------

void render_case(int livello,GLuint scene_list)
{
    
	if(livello==1)glCallList(scene_list);
	if(livello==2)glCallList(scene_list+1);
	if(livello==3)glCallList(scene_list+2);
    
}


// ----------------------------------------------------------------------------

motion scegli_mov(motion m,level l, int pos, int tempoi, float vel, indice_personaggi index, int ch)
{
    
	int mov;
	int wait;
    
	wait=index.character[ch].life*(100*vel);
	mov=l.posizione[pos].movimento;
    
	if(mov==1) m=do_motion1(m,tempoi, wait);
	if(mov==2) m=do_motion2(m,tempoi);
    
	return m;
    
}


// ----------------------------------------------------------------------------

motion do_motion1 (motion m,int tempoi,int wait)
{
    
	if(m.stato!=2){
        
		if(m.angle==0 && m.count==0) m.temp_rel=tempoi-1;
        
		if(m.stato==1) {
			
			m.dt=tempoi-m.temp_rel;
            
			m.angle = m.dt;
            
		}
        
		if(m.angle >= 90.0 && m.count==0) {
			m.stato = 0;
			m.count=1;
			m.angle=90;
		}
        
		if(m.angle>=90 && m.count==1){
            
			if(m.continua==0){
				m.timer=tempoi;
				m.continua=1;
			}
			if(tempoi>=(m.timer+wait)){
				
				m.count=2;
                
				m.temp_rel=tempoi-1;
                
			}
		}
        
		if(m.stato==0 && m.count==2){
            
			m.dt=tempoi-m.temp_rel;
            
			m.angle = m.angle - m.dt;
            
		}
        
		if(m.angle<=0 && m.count==2) m.count=3;
        
	}
    
	if(m.count==3) {
		m.stato=2;
		m.count=0;
		m.angle=0.0;
	}
    
	return m;
}


// ----------------------------------------------------------------------------

motion do_motion2 (motion m,int tempoi)
{
    
	if(m.angle >= 90.0) {
		m.stato = 0;
		m.count+=1;
		m.temp_rel=tempoi-1;
	}
    
	if(m.angle <= 0.0) {
		m.stato = 1;
		m.count+=1;
		m.temp_rel=tempoi-1;
	}
	
	if(m.stato==1){
		m.dt=tempoi-m.temp_rel;
		m.angle = m.dt;
		if(m.angle > 90.0) m.angle=90;
	}
	if(m.stato==0){
		m.dt=tempoi-m.temp_rel;
		m.angle = 90 - m.dt;
		if(m.angle < 0.0) m.angle=0;
	}
	
	if(m.count==4)m.stato=2;
    
	return m;
}


// ----------------------------------------------------------------------------

motion reset_motion(motion m)
{
    
	m.angle=0.0;
	m.continua=0;
	m.count=0;
	m.dt=0;
	m.stato=1;
	m.temp_rel=0;
	m.timer=0;
    
	return m;
}


// ----------------------------------------------------------------------------

m_time count_time (m_time t)
{
	static GLint prev_time = 0;
    
	int time = glutGet(GLUT_ELAPSED_TIME);
	t.tempof += (time-prev_time)*t.v;
	t.tempoi=((int)t.tempof-t.offset);
	prev_time = time;
    
	return t;
}


// ----------------------------------------------------------------------------

m_time reset_time(m_time t){
	t.tempof=0.0;
	t.tempoi=0.0;
	t.v=0.1;
	t.offset=30000*t.v;
    
	return t;
}