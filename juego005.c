#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/file.h>
#include <allegro5/allegro_font.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#define ANCHO 15
#define LARGO 20
#define PIXEL 40
#define cantidad 10
#define KEY_SEEN     1
#define KEY_RELEASED 2
#define vision 2
struct JUG{
   int bitmap_x;
   int bitmap_y;
   int vida;
   int nivel;
   int keys;
   int activo;
};
struct enemigo{
    int e_x;
    int e_y;
    int indicacion;
    int vida;
    int activo;
    int posx;
    int posy;
};
struct trampa{
  int t_x;
  int t_y;
  int flecha_x;
  int flecha_y;
  int activo;
};
struct ranking{
  int puntaje;
  char nombre[20];
  char numero_jug[5];
};
int num_de_puntaje=1;
void posenemigo(struct enemigo en [cantidad],char mapaenv[ANCHO][LARGO]);
void cargamapa(char map[ANCHO][LARGO],char map2[ANCHO][LARGO],char map3[ANCHO][LARGO],char map4[ANCHO][LARGO],char map5[ANCHO][LARGO],char map6[ANCHO][LARGO],char map7[ANCHO][LARGO],char map8[ANCHO][LARGO],char map9[ANCHO][LARGO],char map10[ANCHO][LARGO],char map11[ANCHO][LARGO],char map12[ANCHO][LARGO],struct JUG jugador);
void cargamapa2(char map[ANCHO][LARGO],char map2[ANCHO][LARGO],char map3[ANCHO][LARGO],char map4[ANCHO][LARGO],char map5[ANCHO][LARGO],char map6[ANCHO][LARGO],char map7[ANCHO][LARGO],char map8[ANCHO][LARGO],char map9[ANCHO][LARGO],char map10[ANCHO][LARGO],char map11[ANCHO][LARGO],char map12[ANCHO][LARGO],struct JUG jugador);
void vaciar(char map[ANCHO][LARGO],char map2[ANCHO][LARGO],char map3[ANCHO][LARGO],char map4[ANCHO][LARGO],char map5[ANCHO][LARGO],char map6[ANCHO][LARGO],char map7[ANCHO][LARGO],char map8[ANCHO][LARGO],char map9[ANCHO][LARGO],char map10[ANCHO][LARGO],char map11[ANCHO][LARGO],char map12[ANCHO][LARGO],struct JUG jugador);
void posjugador(char mapaenv[ANCHO][LARGO],struct JUG* jugador,int ubicacion);
void postrampa (struct trampa tira[cantidad],char mapaenv[ANCHO][LARGO]);
void Trampas(char mapaenv[ANCHO][LARGO],struct trampa lanza[cantidad],int mapa,int velocidad, int posf,int posfx,struct JUG jugador);
void movenemigos(int velocidad, struct enemigo en[cantidad], struct JUG jugador, char mapaenv[ANCHO][LARGO], int ay, int ax, int by, int bx, int cy, int cx, int dy, int dx, int eny, int enx);
void dibujarmapa(ALLEGRO_BITMAP* jug, ALLEGRO_BITMAP* eneb, ALLEGRO_BITMAP* flecha, ALLEGRO_BITMAP* ene, ALLEGRO_BITMAP* muro, ALLEGRO_BITMAP* lim, ALLEGRO_BITMAP* fal, ALLEGRO_BITMAP* suelo, ALLEGRO_BITMAP* tirar, ALLEGRO_BITMAP* llave, ALLEGRO_BITMAP* corazon, ALLEGRO_BITMAP* puerta, int mapa, struct JUG jugador, struct enemigo en[cantidad], struct trampa lanza[cantidad], int x, int y,char mapaenv[ANCHO][LARGO],ALLEGRO_BITMAP* moneda,ALLEGRO_BITMAP* sig_niv);
void contarvida(char mapaenv[ANCHO][LARGO], struct JUG* jugador, struct enemigo en[cantidad], struct trampa lanza[cantidad], int mapa,int ubicacion);
void movjugador(unsigned char key[], struct JUG* jugador, char mapaenv[ANCHO][LARGO]);
void asignar(char mapaenv[ANCHO][LARGO], char mapausado[ANCHO][LARGO]);
void escritura(char mapaenv[ANCHO][LARGO], char mapaoriginal[ANCHO][LARGO]);
void puntaje(char mapaenv[ANCHO][LARGO],struct ranking* puntos,struct JUG jugador);
void leerranking(ALLEGRO_FONT* font,struct ranking lectura[num_de_puntaje]);
void ordenar_ranking( struct ranking lectura[num_de_puntaje]);
void registrar_ranking(struct ranking puntos,ALLEGRO_FONT* font);
void mostrar_ranking(ALLEGRO_FONT* font,struct ranking lectura[num_de_puntaje]);
void cargamapa3(char map[ANCHO][LARGO],char map2[ANCHO][LARGO],char map3[ANCHO][LARGO],char map4[ANCHO][LARGO],char map5[ANCHO][LARGO],char map6[ANCHO][LARGO],char map7[ANCHO][LARGO],char map8[ANCHO][LARGO],char map9[ANCHO][LARGO],char map10[ANCHO][LARGO],char map11[ANCHO][LARGO],char map12[ANCHO][LARGO],struct JUG jugador);
int main(){
  srand(time(NULL));
    typedef struct JUG PERSONA;
   PERSONA jugador;
   typedef struct enemigo ENE;
   ENE en [cantidad];
   typedef struct trampa FLECHAS;
   FLECHAS lanza[cantidad];
   struct ranking puntos;
   struct ranking lectura[num_de_puntaje];
   int x, y, i,velocidad=0,mapa,ubicacion=6,eny,enx,ay,ax,by,bx,cy,cx,dy,dx,a,posf,posfx,opcion,seleccion,velocidad2,velocidad3;
   char mapaenv[ANCHO][LARGO];
   char map[ANCHO][LARGO];
   char map2[ANCHO][LARGO];
   char map3[ANCHO][LARGO];
   char map4[ANCHO][LARGO];
   char map5[ANCHO][LARGO];
   char map6[ANCHO][LARGO];
   char map7[ANCHO][LARGO];
   char map8[ANCHO][LARGO];
   char map9[ANCHO][LARGO];
   char map10[ANCHO][LARGO];
   char map11[ANCHO][LARGO];
   char map12[ANCHO][LARGO];
    al_init();
   al_install_keyboard();
   ALLEGRO_TIMER* timer = al_create_timer(1.5 / 30.0);
   ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
   ALLEGRO_DISPLAY* disp = al_create_display(800, 600); 
   al_init_image_addon();
   mapa=1;
   al_start_timer(timer);
   ALLEGRO_FONT* font = al_create_builtin_font();
   ALLEGRO_BITMAP* lim = al_load_bitmap("pinch.png");
   ALLEGRO_BITMAP* muro = al_load_bitmap("muro2.png");
   ALLEGRO_BITMAP* jug = al_load_bitmap("jugador.png");
   ALLEGRO_BITMAP* fal = al_load_bitmap("falso.png");
   ALLEGRO_BITMAP* ene = al_load_bitmap("ene.png");
   ALLEGRO_BITMAP* eneb = al_load_bitmap("enemigo_0.png");
   ALLEGRO_BITMAP* suelo = al_load_bitmap("falso_s.png");
   ALLEGRO_BITMAP* flecha = al_load_bitmap("flecha.png");
   ALLEGRO_BITMAP* tirar = al_load_bitmap("tiraflechas.png");
   ALLEGRO_BITMAP* llave = al_load_bitmap("llave.png");
   ALLEGRO_BITMAP* corazon = al_load_bitmap("corazon2.png");
   ALLEGRO_BITMAP* puerta = al_load_bitmap("Spriteb.png");
   ALLEGRO_BITMAP* moneda= al_load_bitmap("moneda.png");
   ALLEGRO_BITMAP* menu1= al_load_bitmap("MAPA_01.png");
   ALLEGRO_BITMAP* menu2= al_load_bitmap("menu02.png");
   ALLEGRO_BITMAP* menu3= al_load_bitmap("MENU03.png");
   ALLEGRO_BITMAP* sig_niv= al_load_bitmap("sig_niv.png");
   al_register_event_source(queue, al_get_keyboard_event_source());
   al_register_event_source(queue, al_get_display_event_source(disp));
   al_register_event_source(queue, al_get_timer_event_source(timer));
   bool done = false;
   bool redraw = true;
   ALLEGRO_EVENT event;
   jugador.nivel =1;
   cargamapa(map,map2,map3,map4,map5,map6,map7,map8,map9,map10,map11,map12,jugador);
   asignar(mapaenv, map);
   posjugador(map,&jugador,ubicacion); 
   unsigned char key[ALLEGRO_KEY_MAX];
   memset(key, 0, sizeof(key));
   jugador.vida = 10;
   jugador.keys =0;
   jugador.activo= 0;
   opcion=0;
   seleccion=0;
   puntos.puntaje=0;
   while(1){
    al_wait_for_event(queue, &event);
      switch(event.type){
       case ALLEGRO_EVENT_TIMER:
        if(jugador.activo==1&&seleccion==1&&opcion==0){
        movjugador(key,&jugador,mapaenv);
        velocidad=(velocidad+1)%14;
        movenemigos(velocidad,en,jugador,mapaenv, ay, ax, by, bx, cy, cx, dy, dx, eny, enx);
        if(mapa==4&&jugador.nivel==1){
          velocidad2=(velocidad2+1)%10;
          Trampas(mapaenv,lanza,mapa,velocidad2,posf,posfx,jugador);
        }
       if(mapa==8&&jugador.nivel==1){
          velocidad2=(velocidad2+1)%12;
          Trampas(mapaenv,lanza,mapa,velocidad2,posf,posfx,jugador);
        }
        if(mapa==3&&jugador.nivel==2){
          velocidad3=(velocidad3+1)%12;
          Trampas(mapaenv,lanza,mapa,velocidad3,posf,posfx,jugador);
        }
        if(mapa==4&&jugador.nivel==3){
          velocidad3=(velocidad3+1)%10;
          Trampas(mapaenv,lanza,mapa,velocidad3,posf,posfx,jugador);
        }
        if(mapa==7&&jugador.nivel==3)
        {
          velocidad3=(velocidad3+1)%8;
          Trampas(mapaenv,lanza,mapa,velocidad,posf,posfx,jugador);
        }
        }
        if(key[ALLEGRO_KEY_ESCAPE])
            done = true;

        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= KEY_SEEN;
       
        redraw = true;
        break;

       case ALLEGRO_EVENT_KEY_DOWN:
       if(seleccion==0)
       {
       if (event.keyboard.keycode== ALLEGRO_KEY_DOWN&&(opcion >= 0 && opcion <2))
        {
          opcion++;
        }
        if (event.keyboard.keycode== ALLEGRO_KEY_UP&&(opcion > 0 && opcion <=2))
        {
          opcion--;
        }
       if(event.keyboard.keycode== ALLEGRO_KEY_ENTER)
       {
        seleccion=1;
        if(opcion==0)
        {
          jugador.activo=1;
        }
       }
       }
        key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        break;

       case ALLEGRO_EVENT_KEY_UP:
        key[event.keyboard.keycode] &= KEY_RELEASED;
        break;
       case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;
      }
      if (done)
         break;
  if (redraw && al_is_event_queue_empty(queue)) {
   if(seleccion==0)
   {   
    if(opcion==0)
    {
      al_draw_bitmap(menu1,0,0,0);
    }
    if(opcion==1)
    {
      al_draw_bitmap(menu2,0,0,0);
    }
    if(opcion==2)
    {
      al_draw_bitmap(menu3,0,0,0);
    }
   }
   if(seleccion==1&&opcion==1)
   {
    al_clear_to_color(al_map_rgb(255, 255, 0));
    leerranking(font,lectura);
    ordenar_ranking(lectura);
    mostrar_ranking(font,lectura);
    //sleep(3);
   }
    if(seleccion==1&&opcion==2)
   {
    done = true;
    break;
   }
    if(jugador.activo==1&&seleccion==1&&opcion==0){
        al_clear_to_color(al_map_rgb(143, 86, 59));
        x=jugador.bitmap_x/PIXEL;
        y=jugador.bitmap_y/PIXEL;
        dibujarmapa(jug, eneb, flecha, ene, muro, lim, fal, suelo, tirar, llave, corazon, puerta, mapa, jugador, en, lanza, x,y, mapaenv,moneda,sig_niv);
          if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='n'&&jugador.nivel==2&&mapa==10){
            vaciar(map,map2,map3,map4,map5,map6,map7,map8,map9,map10,map11,map12,jugador);
            jugador.nivel=3;
            ubicacion =6;
            cargamapa3(map,map2,map3,map4,map5,map6,map7,map8,map9,map10,map11,map12,jugador);
            asignar(mapaenv, map5);
            posjugador(map5,&jugador,ubicacion);
            mapa=5; 
          }
        if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='n'&&jugador.nivel==1&&mapa==11){
        vaciar(map,map2,map3,map4,map5,map6,map7,map8,map9,map10,map11,map12,jugador);
         jugador.nivel=2;
        ubicacion =6;
        cargamapa2(map,map2,map3,map4,map5,map6,map7,map8,map9,map10,map11,map12,jugador);
        asignar(mapaenv, map2);
        posjugador(map2,&jugador,ubicacion);
        mapa=2; 
        }
        if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='n'&&jugador.nivel==3&&mapa==11)
        {
        jugador.activo=0;
         al_clear_to_color(al_map_rgb(255,255,255));
         al_draw_textf(font, al_map_rgb(0, 0, 0), 100, 50, ALLEGRO_ALIGN_LEFT, "USTED HA TERMINADO EL JUEGO" );
         sleep(2);
         registrar_ranking(puntos,font);
        }
   if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&& mapa==1)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'N'&& mapa==3)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&& mapa==5))
   {
    
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&& mapa==1)
    {
      escritura(mapaenv,map);
      ubicacion=2;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'N'&& mapa==3){
      escritura(mapaenv,map3);
      ubicacion=0;
    }
    else if (mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&& mapa==5)
    {
      escritura(mapaenv,map5);
      ubicacion=1;
    }
    asignar(mapaenv,map2);
    mapa=2;
    posjugador(mapaenv,&jugador,ubicacion);
    posenemigo(en,mapaenv);
    postrampa(lanza,mapaenv);
    if(jugador.nivel==1)
    {
    en[0].activo=1;
    for(i=0;i<cantidad;i++)
    {
      lanza[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
   }
   if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==2)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==6))
   {
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==2){
      escritura(mapaenv,map2);
    ubicacion=2;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==6)
    {
      escritura(mapaenv,map6);
    ubicacion=1;
    }
    asignar(mapaenv, map3);
    mapa=3;
    posjugador(mapaenv,&jugador,ubicacion);
    posenemigo(en,mapaenv);
    postrampa(lanza,mapaenv);
    if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      en[i].activo=0;
      lanza[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      
      }
      lanza[0].activo=1;
      lanza[1].activo=1;
      posfx=lanza[0].flecha_x;
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=1;
        if(i!=0){
         en[i].indicacion=0;
      }
      lanza[i].activo=0;
       }
    }
  }
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==3)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==5)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==9))
   {
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==5)
   {
    escritura(mapaenv,map5);
    ubicacion=2;
   }
   else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==3){
    escritura(mapaenv,map3);
    ubicacion=3;
   }
  else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==9)
   {
    escritura(mapaenv,map9);
   ubicacion=1;
   }
   asignar(mapaenv, map6);
    mapa=6;
    posjugador(mapaenv,&jugador,ubicacion);
    posenemigo(en,mapaenv);
    postrampa(lanza,mapaenv);
    if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      en[i].activo=1;
      if(i!=0){
    en[i].indicacion=0;
      }
     lanza[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
   }
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'x'&&mapa==8)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'N'&&mapa==6)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==8)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'e'&&mapa==2)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'S'&&mapa==4))
   {
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'N'&&mapa==6){
      escritura(mapaenv,map6);
      ubicacion=0;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==8)
   {
    escritura(mapaenv,map8);
    ubicacion=1;
   }
   else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'e'&&mapa==2)
   {
    escritura(mapaenv,map2);
    ubicacion=3;
   }
   else if (mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'S'&&mapa==4)
   {
    escritura(mapaenv,map4);
    ubicacion=2;
   }
   else if (mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'x'&&mapa==8)
   {
    escritura(mapaenv,map8);
    ubicacion=4;
   } 
   asignar(mapaenv, map5);
    mapa=5;
    posenemigo(en,mapaenv);
    postrampa(lanza,mapaenv);
    posjugador(mapaenv,&jugador,ubicacion);
    if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      en[i].activo=0;
      lanza[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      en[0].activo=1;
      for(i=0;i<cantidad;i++)
      {
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
   }
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 's'&&mapa==5)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'x'&&mapa==7)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==5)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'S'&&mapa==7)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'N'&&mapa==9)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==11)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'x'&&mapa==7))
   {
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'e'&&mapa==5)
    {
      escritura(mapaenv,map5);
      ubicacion=3;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'N'&&mapa==9)
    {
      escritura(mapaenv,map9);
      ubicacion=0;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'o'&&mapa==11)
   {
    escritura(mapaenv,map11);
    ubicacion=1;
   }
   else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'x'&&mapa==7)
   {
    escritura(mapaenv,map7);
    ubicacion=4;
   }
   else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'S'&&mapa==7)
   {
    escritura(mapaenv,map7);
    ubicacion=2;
   }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 's'&&mapa==5)
   {
    escritura(mapaenv,map5);
    ubicacion=5;
   }
  
    asignar(mapaenv, map8);
    mapa=8;
    posjugador(mapaenv,&jugador,ubicacion); 
    posenemigo(en,mapaenv);
    postrampa(lanza,mapaenv);
     if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      lanza[i].activo=1;
      en[i].activo=0;
    }
    for(a=0;a<cantidad;a++)
    {
      lanza[a].flecha_y=lanza[a].t_y+PIXEL;
      lanza[a].flecha_x=lanza[a].t_x+PIXEL;
    }
    posf=lanza[0].flecha_y;
    posfx=lanza[5].flecha_x;
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    
   } 
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==8)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'N'&&mapa==12)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==10))
   {
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==8)
    {
    escritura(mapaenv,map8);
    ubicacion=3;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==10)
    {
    escritura(mapaenv,map10);
    ubicacion=2;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'N'&&mapa==12)
    {
     escritura(mapaenv,map12);
     ubicacion=0;
    }
    asignar(mapaenv, map11);
    mapa=11;
    posjugador(mapaenv,&jugador,ubicacion);
    posenemigo(en,mapaenv);
    postrampa(lanza,mapaenv);
     if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      lanza[i].activo=0;
      en[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
   }
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==9)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==11))
   {
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==9)
    {
    escritura(mapaenv,map9);
    ubicacion=3;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==11)
    {
      escritura(mapaenv,map11);
      ubicacion= 2;
    }
    if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      lanza[i].activo=0;
      en[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    asignar(mapaenv, map12);
    mapa=12;
    posjugador(mapaenv,&jugador,ubicacion); 
   }
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==1)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==7)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 's'&&mapa==1)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'N'&&mapa==5))
   {
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'o'&&mapa==7)
   {
    escritura(mapaenv,map7);
    ubicacion=1;
   }
   else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==1)
   {
    escritura(mapaenv,map);
    ubicacion=3;
   }
   else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'N'&&mapa==5)
   {
    escritura(mapaenv,map5);
    ubicacion=0;
   }
   else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 's'&&mapa==1)
   {
    escritura(mapaenv,map);
    ubicacion=5;
   }
    asignar(mapaenv, map4);
    mapa=4;
    posjugador(mapaenv,&jugador,ubicacion); 
    postrampa(lanza,mapaenv);
    posenemigo(en,mapaenv);
    if(jugador.nivel==1)
    {
     for(i=0;i<cantidad;i++)
      {
       lanza[i].activo=1;
       en[i].activo=0;
      }
     for(a=0;a<cantidad;a++)
      {
       lanza[a].flecha_y=lanza[a].t_y-PIXEL;
      }
     posf=lanza[0].flecha_y;
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
       {
        lanza[i].activo=0;
       }
       for(a=0;a<3;a++)
       {
        en[a].activo=1;
        if(a!=0)
        {
         en[a].indicacion=0;
        }
       }
    
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=1;
       }
       for(a=0;a<cantidad;a++)
    {
      lanza[a].flecha_y=lanza[a].t_y+PIXEL;
    }
    posf=lanza[0].flecha_y;
    }
    }
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='e'&&mapa==4)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'N'&&mapa==8)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==10)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 's'&&mapa==8))
    {
      if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==10)
      {
        escritura(mapaenv,map10);
       ubicacion=1;
      }
      else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='e'&&mapa==4)
      {
        escritura(mapaenv,map4);
      ubicacion=3;
      }
      else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 's'&&mapa==8)
      {
        escritura(mapaenv,map8);
      ubicacion=5;
      }
      else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'N'&&mapa==8)
      {
        escritura(mapaenv,map8);
      ubicacion=0;
      }
      asignar(mapaenv, map7);
      mapa=7;
      posjugador(mapaenv,&jugador,ubicacion);
      postrampa(lanza,mapaenv);
    posenemigo(en,mapaenv);
      if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      lanza[i].activo=0;
      en[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=1;
       }
       for(a=0;a<cantidad;a++)
    {
      lanza[a].flecha_x=lanza[a].t_x+PIXEL;
    }
    posfx=lanza[0].flecha_x;
    } 
    }
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='e'&&mapa==7)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='N'&&mapa==11)){
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='e'&&mapa==7){
    escritura(mapaenv,map7);
    ubicacion=3;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='N'&&mapa==11)
    {
      escritura(mapaenv,map11);
    ubicacion=0;
    }
    asignar(mapaenv, map10);
      mapa=10;
      posjugador(mapaenv,&jugador,ubicacion); 
      posenemigo(en,mapaenv);
    postrampa(lanza,mapaenv);  
    if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      lanza[i].activo=0;
      en[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
   }
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'N'&&mapa==2)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'o'&&mapa==4)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'x'&&mapa==4)){
   if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'N'&&mapa==2){
    escritura(mapaenv,map2);
    ubicacion=0;
   }
   else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==4)
   {
    escritura(mapaenv,map4);
     ubicacion=1;
   }
   else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'x'&&mapa==4)
   {
    escritura(mapaenv,map4);
    ubicacion=4;
   }
   asignar(mapaenv, map);
    mapa=1;
    posjugador(mapaenv,&jugador,ubicacion);
    posenemigo(en,mapaenv);
    postrampa(lanza,mapaenv);
   if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      lanza[i].activo=0;
      en[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
   }
  if((mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==8)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==12)||(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'e'&&mapa==6))
   {
    if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'S'&&mapa==8)
    {
      escritura(mapaenv,map8);
    ubicacion=2;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40] == 'o'&&mapa==12)
    {
    escritura(mapaenv,map12);
    ubicacion=1;
    }
    else if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]== 'e'&&mapa==6)
   {
    escritura(mapaenv,map6);
    ubicacion=3;
   }
   asignar(mapaenv, map9);
    mapa=9;
    posjugador(mapaenv,&jugador,ubicacion);
    posenemigo(en,mapaenv);
    postrampa(lanza,mapaenv); 
    if(jugador.nivel==1)
    {
    for(i=0;i<cantidad;i++)
    {
      lanza[i].activo=0;
      en[i].activo=0;
    }
    }
    else if(jugador.nivel==2)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=0;
      lanza[i].activo=0;
       }
    }
    else if(jugador.nivel==3)
    {
      for(i=0;i<cantidad;i++)
      {
        en[i].activo=1;
        if(i!=0){
         en[i].indicacion=0;
        }
      lanza[i].activo=0;
       }
    }
  }
   if(mapa==2&&jugador.nivel==1){
   ax=en[0].e_x/PIXEL;
   ay=en[0].e_y/PIXEL;
   }
  if(mapa==6&&jugador.nivel==1){
   ax=en[0].e_x/PIXEL;
   ay=en[0].e_y/PIXEL;
   enx=en[1].e_x/PIXEL;
   eny=en[1].e_y/PIXEL;
   by=en[2].e_y/PIXEL;
   bx=en[2].e_x/PIXEL;
   cy=en[3].e_y/PIXEL;
   cx=en[3].e_x/PIXEL;
   dy=en[4].e_y/PIXEL;
   dx=en[4].e_x/PIXEL;
  }
  if(mapa==4&&jugador.nivel==2){
   ax=en[0].e_x/PIXEL;
   ay=en[0].e_y/PIXEL;
   enx=en[1].e_x/PIXEL;
   eny=en[1].e_y/PIXEL;
   by=en[2].e_y/PIXEL;
   bx=en[2].e_x/PIXEL;
  }
  if(mapa==5&&jugador.nivel==2){
   ax=en[0].e_x/PIXEL;
   ay=en[0].e_y/PIXEL;
  }
  if(mapa==4&&jugador.nivel==2){
   ax=en[0].e_x/PIXEL;
   ay=en[0].e_y/PIXEL;
   enx=en[1].e_x/PIXEL;
   eny=en[1].e_y/PIXEL;
   by=en[2].e_y/PIXEL;
   bx=en[2].e_x/PIXEL;
  }
  if(mapa==3&&jugador.nivel==3){
   ax=en[0].e_x/PIXEL;
   ay=en[0].e_y/PIXEL;
   enx=en[1].e_x/PIXEL;
   eny=en[1].e_y/PIXEL;
   by=en[2].e_y/PIXEL;
   bx=en[2].e_x/PIXEL;
  }
  if(mapa==9&&jugador.nivel==2){
   ax=en[0].e_x/PIXEL;
   ay=en[0].e_y/PIXEL;
   enx=en[1].e_x/PIXEL;
   eny=en[1].e_y/PIXEL;
   by=en[2].e_y/PIXEL;
   bx=en[2].e_x/PIXEL;
  }
  contarvida(mapaenv, &jugador, en, lanza, mapa,ubicacion);
  puntaje(mapaenv,&puntos,jugador);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Llaves: %d",jugador.keys);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 20, 0, "Vidas: %d ",jugador.vida);
  al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 40, 0, "Puntaje: %d ",puntos.puntaje);
  if(jugador.vida==0){
    jugador.activo=0;
    al_clear_to_color(al_map_rgb(255,255,255));
    registrar_ranking(puntos,font);
  }
        }
  
   al_flip_display();
      redraw = false;
      }
   }
   al_destroy_display(disp);
   al_destroy_timer(timer);
   al_destroy_event_queue(queue);
   al_destroy_bitmap(lim);
   return 0;
}
void cargamapa(char map[ANCHO][LARGO],char map2[ANCHO][LARGO],char map3[ANCHO][LARGO],char map4[ANCHO][LARGO],char map5[ANCHO][LARGO],char map6[ANCHO][LARGO],char map7[ANCHO][LARGO],char map8[ANCHO][LARGO],char map9[ANCHO][LARGO],char map10[ANCHO][LARGO],char map11[ANCHO][LARGO],char map12[ANCHO][LARGO],struct JUG jugador){
   int y,x,aux;
   ALLEGRO_FILE* file = al_fopen("file1.txt", "r"); 
   ALLEGRO_FILE* file2 = al_fopen("file2.txt", "r");
   ALLEGRO_FILE* file3 = al_fopen("m1_03.txt", "r");
   ALLEGRO_FILE* file4 = al_fopen("file4.txt", "r");
   ALLEGRO_FILE* file5 = al_fopen("file5.txt", "r");
   ALLEGRO_FILE* file6 = al_fopen("file6.txt", "r");
   ALLEGRO_FILE* file7 = al_fopen("file7.txt", "r");
   ALLEGRO_FILE* file8 = al_fopen("file8.txt", "r");
   ALLEGRO_FILE* file9 = al_fopen("file9.txt", "r");
   ALLEGRO_FILE* file10 = al_fopen("file10.txt", "r");
   ALLEGRO_FILE* file11 = al_fopen("file11.txt", "r");
   ALLEGRO_FILE* file12 = al_fopen("file12.txt", "r");
   for (y = 0; y < ANCHO; y++) {
      for (x = 0; x < LARGO; x++) {
        map[y][x] = al_fgetc(file);
        map2[y][x] = al_fgetc(file2);
        map3[y][x] = al_fgetc(file3);
        map4[y][x] = al_fgetc(file4);
        map5[y][x] = al_fgetc(file5);
        map6[y][x] = al_fgetc(file6);
        map7[y][x] = al_fgetc(file7);
        map8[y][x] = al_fgetc(file8);
        map9[y][x] = al_fgetc(file9);
        map10[y][x] = al_fgetc(file10);
        map11[y][x] = al_fgetc(file11);
        map12[y][x] = al_fgetc(file12);
         if(x==(LARGO-1)){
            aux=al_fgetc(file);
            aux=al_fgetc(file2);
            aux=al_fgetc(file3);
            aux=al_fgetc(file4);
            aux=al_fgetc(file5);
            aux=al_fgetc(file6);
            aux=al_fgetc(file7);
            aux=al_fgetc(file8);
            aux=al_fgetc(file9);
            aux=al_fgetc(file10);
            aux=al_fgetc(file11);
            aux=al_fgetc(file12);
         }
         
      }
   }
   al_fclose(file);
   al_fclose(file2);
   al_fclose(file3);
   al_fclose(file4);
   al_fclose(file5);
   al_fclose(file6);
   al_fclose(file7);
   al_fclose(file8);
   al_fclose(file9);
   al_fclose(file10);
   al_fclose(file11);
   al_fclose(file12);
}
void cargamapa2(char map[ANCHO][LARGO],char map2[ANCHO][LARGO],char map3[ANCHO][LARGO],char map4[ANCHO][LARGO],char map5[ANCHO][LARGO],char map6[ANCHO][LARGO],char map7[ANCHO][LARGO],char map8[ANCHO][LARGO],char map9[ANCHO][LARGO],char map10[ANCHO][LARGO],char map11[ANCHO][LARGO],char map12[ANCHO][LARGO],struct JUG jugador){
   int y,x,aux;
    ALLEGRO_FILE* file = al_fopen("m2_1.txt", "r"); 
   ALLEGRO_FILE* file2 = al_fopen("m2_2.txt", "r");
   ALLEGRO_FILE* file3 = al_fopen("m2_3.txt", "r");
   ALLEGRO_FILE* file4 = al_fopen("m2_4.txt", "r");
   ALLEGRO_FILE* file5 = al_fopen("m2_5.txt", "r");
   ALLEGRO_FILE* file6 = al_fopen("m2_6.txt", "r");
   ALLEGRO_FILE* file7 = al_fopen("m2_7.txt", "r");
   ALLEGRO_FILE* file8 = al_fopen("m2_8.txt", "r");
   ALLEGRO_FILE* file9 = al_fopen("m2_9.txt", "r");
   ALLEGRO_FILE* file10 = al_fopen("m2_10.txt", "r");
   ALLEGRO_FILE* file11 = al_fopen("m2_11.txt", "r");
   ALLEGRO_FILE* file12 = al_fopen("m2_12.txt", "r");
   for (y = 0; y < ANCHO; y++) {
      for (x = 0; x < LARGO; x++) {
        map[y][x] = al_fgetc(file);
        map2[y][x] = al_fgetc(file2);
        map3[y][x] = al_fgetc(file3);
        map4[y][x] = al_fgetc(file4);
        map5[y][x] = al_fgetc(file5);
        map6[y][x] = al_fgetc(file6);
        map7[y][x] = al_fgetc(file7);
        map8[y][x] = al_fgetc(file8);
        map9[y][x] = al_fgetc(file9);
        map10[y][x] = al_fgetc(file10);
        map11[y][x] = al_fgetc(file11);
        map12[y][x] = al_fgetc(file12);
         if(x==(LARGO-1)){
            aux=al_fgetc(file);
            aux=al_fgetc(file2);
            aux=al_fgetc(file3);
            aux=al_fgetc(file4);
            aux=al_fgetc(file5);
            aux=al_fgetc(file6);
            aux=al_fgetc(file7);
            aux=al_fgetc(file8);
            aux=al_fgetc(file9);
            aux=al_fgetc(file10);
            aux=al_fgetc(file11);
            aux=al_fgetc(file12);
         }
         
      }
   }
   al_fclose(file);
   al_fclose(file2);
   al_fclose(file3);
   al_fclose(file4);
   al_fclose(file5);
   al_fclose(file6);
   al_fclose(file7);
   al_fclose(file8);
   al_fclose(file9);
   al_fclose(file10);
   al_fclose(file11);
   al_fclose(file12);
}
void cargamapa3(char map[ANCHO][LARGO],char map2[ANCHO][LARGO],char map3[ANCHO][LARGO],char map4[ANCHO][LARGO],char map5[ANCHO][LARGO],char map6[ANCHO][LARGO],char map7[ANCHO][LARGO],char map8[ANCHO][LARGO],char map9[ANCHO][LARGO],char map10[ANCHO][LARGO],char map11[ANCHO][LARGO],char map12[ANCHO][LARGO],struct JUG jugador){
   int y,x,aux;
   ALLEGRO_FILE* file = al_fopen("m3_01.txt", "r"); 
   ALLEGRO_FILE* file2 = al_fopen("m3_02.txt", "r");
   ALLEGRO_FILE* file3 = al_fopen("m3_03.txt", "r");
   ALLEGRO_FILE* file4 = al_fopen("m3_04.txt", "r");
   ALLEGRO_FILE* file5 = al_fopen("m3_05.txt", "r");
   ALLEGRO_FILE* file6 = al_fopen("m3_06.txt", "r");
   ALLEGRO_FILE* file7 = al_fopen("m3_07.txt", "r");
   ALLEGRO_FILE* file8 = al_fopen("m3_08.txt", "r");
   ALLEGRO_FILE* file9 = al_fopen("m3_09.txt", "r");
   ALLEGRO_FILE* file10 = al_fopen("m3_10.txt", "r");
   ALLEGRO_FILE* file11 = al_fopen("m3_11.txt", "r");
   ALLEGRO_FILE* file12 = al_fopen("m3_12.txt", "r");
   for (y = 0; y < ANCHO; y++) {
      for (x = 0; x < LARGO; x++) {
        map[y][x] = al_fgetc(file);
        map2[y][x] = al_fgetc(file2);
        map3[y][x] = al_fgetc(file3);
        map4[y][x] = al_fgetc(file4);
        map5[y][x] = al_fgetc(file5);
        map6[y][x] = al_fgetc(file6);
        map7[y][x] = al_fgetc(file7);
        map8[y][x] = al_fgetc(file8);
        map9[y][x] = al_fgetc(file9);
        map10[y][x] = al_fgetc(file10);
        map11[y][x] = al_fgetc(file11);
        map12[y][x] = al_fgetc(file12);
         if(x==(LARGO-1)){
            aux=al_fgetc(file);
            aux=al_fgetc(file2);
            aux=al_fgetc(file3);
            aux=al_fgetc(file4);
            aux=al_fgetc(file5);
            aux=al_fgetc(file6);
            aux=al_fgetc(file7);
            aux=al_fgetc(file8);
            aux=al_fgetc(file9);
            aux=al_fgetc(file10);
            aux=al_fgetc(file11);
            aux=al_fgetc(file12);
         }
         
      }
   }
   al_fclose(file);
   al_fclose(file2);
   al_fclose(file3);
   al_fclose(file4);
   al_fclose(file5);
   al_fclose(file6);
   al_fclose(file7);
   al_fclose(file8);
   al_fclose(file9);
   al_fclose(file10);
   al_fclose(file11);
   al_fclose(file12);
}
void posjugador(char mapaenv[ANCHO][LARGO],struct JUG* jugador,int ubicacion){
  int y,x;
   for (y = 0; y < ANCHO; y++){
     for (x = 0; x < LARGO; x++) {
        if(ubicacion==0){
          if (mapaenv[y][x] == 'j'){
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
          }
        }
        if(ubicacion==1){
         if (mapaenv[y][x] == 'J'){
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
          }  
        }
        if(ubicacion==2){
          if (mapaenv[y][x] == 'P'){
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
         } 
        }
        if(ubicacion==3){
          if (mapaenv[y][x] == '1'){
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
          } 
        }
        if(ubicacion==4){
          if (mapaenv[y][x] == '2') {
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
          } 
        }
        if(ubicacion==5){
          if (mapaenv[y][x] == '3') {
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
          } 
        }
        if(ubicacion==6){
          if (mapaenv[y][x] == 'I'){
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
         } 
        }
      }
   }
}
void posenemigo(struct enemigo en [cantidad],char mapaenv[ANCHO][LARGO])
{
  int y,x,i=0;
   for (y = 0; y < ANCHO; y++){
     for (x = 0; x < LARGO; x++) {
       if (mapaenv[y][x] == 'E') {
        en [i].e_x=x;
        en [i].e_y=y;
        en[i].posx=x;
        en[i].posy=y;
        en [i].e_x= en [i].e_x*PIXEL;
        en [i].e_y= en [i].e_y*PIXEL;
        i++;
       }
      }
    }
}
void postrampa (struct trampa tira[cantidad],char mapaenv[ANCHO][LARGO])
{
  int y,x,i=0;
   for (y = 0; y < ANCHO; y++) {
     for (x = 0; x < LARGO; x++){
        if (mapaenv[y][x] == 'L') {
          tira[i].t_x=x;
          tira[i].t_y=y;
          tira[i].t_x=tira[i].t_x*PIXEL;
          tira[i].t_y= tira[i].t_y*PIXEL;
          i++;
        }
      }
   }
}
void Trampas(char mapaenv[ANCHO][LARGO],struct trampa lanza[cantidad],int mapa,int velocidad, int posf,int posfx,struct JUG jugador){
  int a;
  if(mapa==4&&velocidad==0&&jugador.nivel==1){
    for(a=0;a<cantidad;a++){
      lanza[a].flecha_y-=PIXEL;
      lanza[a].flecha_x=lanza[a].t_x;
    }
    if(mapaenv[(lanza[1].flecha_y/40)][lanza[1].t_x/40]=='m'){
      lanza[1].flecha_y=posf;
    }
    if(mapaenv[(lanza[0].flecha_y/40)][lanza[0].t_x/40]=='m'){
      lanza[0].flecha_y=posf;
    }
    if(mapaenv[(lanza[2].flecha_y/40)][lanza[2].t_x/40]=='m'){
      lanza[2].flecha_y=posf;
    }
    if(mapaenv[(lanza[3].flecha_y/40)][lanza[3].t_x/40]=='m'){
      lanza[3].flecha_y=posf;
    }
    if(mapaenv[(lanza[4].flecha_y/40)][lanza[4].t_x/40]=='m'){
      lanza[4].flecha_y=posf;
    }
  }
  if(mapa==8&&velocidad==0&&jugador.nivel==1){
    for(a=0;a<cantidad;a++){
      if(a>-1&&a<4){
        lanza[a].flecha_y+=PIXEL;
        lanza[a].flecha_x=lanza[a].t_x;
      }
      if(a>3&&a<8){
        lanza[a].flecha_x+=PIXEL;
        lanza[a].flecha_y=lanza[a].t_y;
      }
    }
    if(mapaenv[(lanza[1].flecha_y/40)][lanza[1].t_x/40]=='S'){
      lanza[1].flecha_y=posf;
    }
    if(mapaenv[(lanza[0].flecha_y/40)][lanza[0].t_x/40]=='S'){
      lanza[0].flecha_y=posf;
    }
    if(mapaenv[(lanza[2].flecha_y/40)][lanza[2].t_x/40]=='m'){
      lanza[2].flecha_y=posf;
    }
    if(mapaenv[(lanza[3].flecha_y/40)][lanza[3].t_x/40]=='m'){
      lanza[3].flecha_y=posf;
    }
    if(mapaenv[(lanza[4].t_y/40)][lanza[4].flecha_x/40]=='m'){
      lanza[4].flecha_x=posfx;
    }
    if(mapaenv[(lanza[5].t_y/40)][lanza[5].flecha_x/40]=='m'){
      lanza[5].flecha_x=posfx;
    }
    if(mapaenv[(lanza[6].t_y/40)][lanza[6].flecha_x/40]=='m'){
      lanza[6].flecha_x=posfx;
    }
    if(mapaenv[(lanza[7].t_y/40)][lanza[7].flecha_x/40]=='m'){
      lanza[7].flecha_x=posfx;
    }
  }
  if(mapa==3&&velocidad==0&&jugador.nivel==2){
    for(a=0;a<cantidad;a++){
      lanza[a].flecha_x+=PIXEL;
      lanza[a].flecha_y=lanza[a].t_y;
    }
    if(mapaenv[(lanza[0].t_y/40)][lanza[0].flecha_x/40]=='m'){
      lanza[0].flecha_x=posfx;
    }
    if(mapaenv[(lanza[1].t_y/40)][lanza[1].flecha_x/40]=='m'){
      lanza[1].flecha_x=posfx;
    }
  }
  if(mapa==4&&velocidad==0&&jugador.nivel==3){
     for(a=0;a<cantidad;a++){
        lanza[a].flecha_y+=PIXEL;
        lanza[a].flecha_x=lanza[a].t_x;
      }
      if(mapaenv[(lanza[0].flecha_y/40)][lanza[0].t_x/40]=='m'){
        lanza[0].flecha_y=posf;
      }
      if(mapaenv[(lanza[1].flecha_y/40)][lanza[1].t_x/40]=='m'){
        lanza[1].flecha_y=posf;
      }
      if(mapaenv[(lanza[2].flecha_y/40)][lanza[2].t_x/40]=='m'){
        lanza[2].flecha_y=posf;
      }
      if(mapaenv[(lanza[3].flecha_y/40)][lanza[3].t_x/40]=='m'){
        lanza[3].flecha_y=posf;
      }
   }
  if(mapa==7&&velocidad==0&&jugador.nivel==3){
    for(a=0;a<cantidad;a++){
      lanza[a].flecha_x+=PIXEL;
      lanza[a].flecha_y=lanza[a].t_y;
    }
    if(mapaenv[(lanza[0].t_y/40)][lanza[0].flecha_x/40]=='m'){
      lanza[0].flecha_x=posfx;
    }
    if(mapaenv[(lanza[1].t_y/40)][lanza[1].flecha_x/40]=='m'){
      lanza[1].flecha_x=posfx;
    }
    if(mapaenv[(lanza[2].t_y/40)][lanza[2].flecha_x/40]=='m'){
      lanza[2].flecha_x=posfx;
    }
    if(mapaenv[(lanza[3].t_y/40)][lanza[3].flecha_x/40]=='m'){
      lanza[3].flecha_x=posfx;
    }  
  }
}
void movenemigos(int velocidad, struct enemigo en[cantidad], struct JUG jugador, char mapaenv[ANCHO][LARGO], int ay, int ax, int by, int bx, int cy, int cx, int dy, int dx, int eny, int enx){
  if(velocidad==0){
    if(en[0].e_x<jugador.bitmap_x&&en[0].activo==1){
        en[0].e_x+=PIXEL;
          if(mapaenv[ay][ax+1] == 'm'){
            en[0].e_x-=PIXEL;
          }
    }      
    if(en[0].e_x>jugador.bitmap_x&&en[0].activo==1){
      en[0].e_x-=PIXEL;
        if(mapaenv[ay][ax-1] == 'm'){
          en[0].e_x+=PIXEL;
        }
    }
    if(en[0].e_y<jugador.bitmap_y&&en[0].activo==1){
      en[0].e_y+=PIXEL;
        if(mapaenv[ay+1][ax] == 'm'){
          en[0].e_y-=PIXEL;
        }
    }
    if(en[0].e_y>jugador.bitmap_y&&en[0].activo==1){
      en[0].e_y-=PIXEL;
        if(mapaenv[ay-1][ay] == 'm'){
          en[0].e_y+=PIXEL;
        }
    }
  }
  if(velocidad==1){
    if(en[1].indicacion==0&&en[1].activo==1){
      en[1].e_y+=PIXEL;
        if(mapaenv[eny+1][enx]=='m'){
          en[1].indicacion=1;
        }
    }
    if(en[1].indicacion==1&&en[1].activo==1){
      en[1].e_y-=PIXEL;
      if(mapaenv[eny-1][enx]=='m'){
        en[1].indicacion=0;
      }
    }
  }
  if(velocidad==1){
    if(en[2].indicacion==0&&en[2].activo==1){
      en[2].e_x+=PIXEL;
        if(mapaenv[by][bx+1]=='m'){
          en[2].indicacion=1;
        }
    }
    if(en[2].indicacion==1&&en[2].activo==1){
      en[2].e_x-=PIXEL;
        if(mapaenv[by][bx-1]=='m'){
          en[2].indicacion=0;
        }
    }
  }
  if(velocidad==2){
    if(en[3].indicacion==0&&en[3].activo==1){
      en[3].e_x+=PIXEL;
        if(mapaenv[cy][cx+1]=='m'){
          en[3].indicacion=1;
        }
    }
    if(en[3].indicacion==1&&en[3].activo==1){
      en[3].e_x-=PIXEL;
        if(mapaenv[cy][cx-1]=='m'){
          en[3].indicacion=0;
        }
    }
  }
  if(velocidad==3){
    if(en[4].indicacion==0&&en[4].activo==1){
      en[4].e_x+=PIXEL;
        if(mapaenv[dy][dx+1]=='m'){
          en[4].indicacion=1;
        }
    }
    if(en[4].indicacion==1&&en[4].activo==1){
      en[4].e_y+=PIXEL;
        if(mapaenv[dy+1][dx]=='m'){
          en[4].indicacion=2;
        }
    }
    if(en[4].indicacion==2&&en[4].activo==1){
      en[4].e_x-=PIXEL;
        if(mapaenv[dy][dx-1]=='m'){
          en[4].indicacion=3;
        }
    }
    if(en[4].indicacion==3&&en[4].activo==1){
      en[4].e_y-=PIXEL;
        if(mapaenv[dy-1][dx]=='m'||mapaenv[dy-1][dx]=='N'){
          en[4].indicacion=0;
        }
    }
    if((mapaenv[dy-1][dx]==(mapaenv[cy][cx]||mapaenv[by][bx]||mapaenv[ay][ax]||mapaenv[eny][enx]))||(mapaenv[dy][dx+1]==(mapaenv[cy][cx]||mapaenv[by][bx]||mapaenv[ay][ax]||mapaenv[eny][enx]))||(mapaenv[dy][dx-1]==(mapaenv[cy][cx]||mapaenv[by][bx]||mapaenv[ay][ax]||mapaenv[eny][enx]))||(mapaenv[dy+1][dx]==(mapaenv[cy][cx]||mapaenv[by][bx]||mapaenv[ay][ax]||mapaenv[eny][enx]))){
      en[4].indicacion=rand()%5;
    }
  }
}
void dibujarmapa(ALLEGRO_BITMAP* jug, ALLEGRO_BITMAP* eneb, ALLEGRO_BITMAP* flecha, ALLEGRO_BITMAP* ene, ALLEGRO_BITMAP* muro, ALLEGRO_BITMAP* lim, ALLEGRO_BITMAP* fal, ALLEGRO_BITMAP* suelo, ALLEGRO_BITMAP* tirar,ALLEGRO_BITMAP* llave, ALLEGRO_BITMAP* corazon, ALLEGRO_BITMAP* puerta, int mapa, struct JUG jugador, struct enemigo en[cantidad], struct trampa lanza[cantidad], int x, int y,char mapaenv[ANCHO][LARGO],ALLEGRO_BITMAP* moneda,ALLEGRO_BITMAP* sig_niv)
{
  int a=0;
  al_clear_to_color(al_map_rgb(0,0,0));
    for(y=-vision;y>=-vision&&y<=vision;y++){
      for(x=-vision;x>=-vision&&x<=vision;x++){
        al_draw_bitmap(suelo, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        al_draw_bitmap(jug, jugador.bitmap_x, jugador.bitmap_y, 0);
        if(mapaenv[(jugador.bitmap_y/40)+y][(jugador.bitmap_x/40)+x] == 'p') {
          al_draw_bitmap(lim, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        }
        if(mapaenv[(jugador.bitmap_y/40)+y][(jugador.bitmap_x/40)+x] == 't') {
          al_draw_bitmap(fal, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        }
        if(mapaenv[(jugador.bitmap_y/40)+y][(jugador.bitmap_x/40)+x] == 'L') {
          al_draw_bitmap(tirar, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        }
        if(mapaenv[(jugador.bitmap_y/40)+y][(jugador.bitmap_x/40)+x] == 'V') {
          al_draw_bitmap(corazon, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        }
        if(mapaenv[(jugador.bitmap_y/40)+y][(jugador.bitmap_x/40)+x] == 'M') {
          al_draw_bitmap(moneda, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        }
        if(mapaenv[(jugador.bitmap_y/40)+y][(jugador.bitmap_x/40)+x] == 'K') {
          al_draw_bitmap(llave, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        }
        if(mapaenv[(jugador.bitmap_y/40)+y][(jugador.bitmap_x/40)+x] == 'B') {
          al_draw_bitmap(puerta, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        }
        if(mapaenv[(jugador.bitmap_y/40)+y][(jugador.bitmap_x/40)+x] == 'n') {
          al_draw_bitmap(sig_niv, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        }
        for(a=0;a<cantidad;a++){
          if((jugador.bitmap_y+(40*y)== en[a].e_y)&&(jugador.bitmap_x+(40*x)== en[a].e_x)&&en[a].activo==1) {
              if(a!=0)
               al_draw_bitmap(ene, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
              else
               al_draw_bitmap(eneb, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
          }
          if((jugador.bitmap_y+(40*y)== lanza[a].flecha_y)&&(jugador.bitmap_x+(40*x)== lanza[a].flecha_x)&&lanza[a].activo==1) {
             al_draw_bitmap(flecha, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
          }
        }
        if(mapaenv[(jugador.bitmap_y/40)+y][(jugador.bitmap_x/40)+x] == 'm'){
          al_draw_bitmap(muro, (x*PIXEL)+jugador.bitmap_x, (y*PIXEL)+jugador.bitmap_y, 0);
        }
      }
    }   
}
void contarvida(char mapaenv[ANCHO][LARGO], struct JUG *jugador, struct enemigo en[cantidad], struct trampa lanza[cantidad], int mapa, int ubicacion){
  int x, y, i, a;
  if (mapaenv[(jugador->bitmap_y) / 40][(jugador->bitmap_x) / 40] == 'V'){
    jugador->vida += 1;
    mapaenv[(jugador->bitmap_y) / 40][(jugador->bitmap_x) / 40] = '-';
  }
  if (mapaenv[(jugador->bitmap_y) / 40][(jugador->bitmap_x) / 40] == 'K'){
    jugador->keys += 1;
    mapaenv[(jugador->bitmap_y) / 40][(jugador->bitmap_x) / 40] = '-';
  }
  if (mapaenv[(jugador->bitmap_y) / 40][(jugador->bitmap_x) / 40] == 'p'){
    jugador->vida -= 1;
    posjugador(mapaenv, jugador, ubicacion);
  }
  if (mapaenv[(jugador->bitmap_y) / 40][(jugador->bitmap_x) / 40] == 'B'&&jugador->keys>0){
    jugador->keys -= 1;
    mapaenv[(jugador->bitmap_y) / 40][(jugador->bitmap_x) / 40] = '-';
  }
  if (mapaenv[(jugador->bitmap_y) / 40][(jugador->bitmap_x) / 40] == 't'){
    mapaenv[(jugador->bitmap_y) / 40][(jugador->bitmap_x) / 40] = '-';
  }
  for (a = 0; a < cantidad; a++){
    if (((jugador->bitmap_x == en[a].e_x) && (jugador->bitmap_y == en[a].e_y))&&en[a].activo==1){
      jugador->vida -= 1;
      posjugador(mapaenv, jugador, ubicacion);
      en[a].activo=0;
      en[a].e_x=-1000;
      en[a].e_y=-1000;
        for(y = 0; y < ANCHO; y++){
          for (x = 0; x < LARGO; x++){
            if(mapaenv[y][x] == 'E') 
              mapaenv[y][x] ='-';
          }
        }
    }
  }
  for (i = 0; i < cantidad; i++){
    if (((((jugador->bitmap_y == lanza[i].flecha_y) && (lanza[i].flecha_x == jugador->bitmap_x))))&&lanza[i].activo==1){
      jugador->vida -= 1;
      posjugador(mapaenv, jugador, ubicacion);
    }
  }
}
void movjugador(unsigned char key[], struct JUG* jugador, char mapaenv[ANCHO][LARGO]){
  int x,y;
  x=jugador->bitmap_x / PIXEL;
  y=jugador->bitmap_y / PIXEL;
    if(key[ALLEGRO_KEY_UP]){
      jugador->bitmap_y-=PIXEL;
        if ((mapaenv[y-1][x] == 'm')||(mapaenv[y-1][x] == 'L')){
           jugador->bitmap_y+=PIXEL;
         }
        if(mapaenv[y-1][x]=='B'&&jugador->keys<1){
            jugador->bitmap_y+=PIXEL;
         }
    }
    if(key[ALLEGRO_KEY_DOWN]){
      jugador->bitmap_y+=PIXEL;
        if ((mapaenv[y+1][x] == 'm')||(mapaenv[y+1][x] == 'L')){
          jugador->bitmap_y-=PIXEL;
         }
        if(mapaenv[y+1][x]=='B'&&jugador->keys<1){
           jugador->bitmap_y-=PIXEL;
          }
    }
    if(key[ALLEGRO_KEY_LEFT]){
      jugador->bitmap_x-=PIXEL;
        if ((mapaenv[y][x-1] == 'm')||(mapaenv[y][x-1] == 'L')){
          jugador->bitmap_x+=PIXEL;
         }
        if(mapaenv[y][x-1]=='B'&&jugador->keys<1){
           jugador->bitmap_x+=PIXEL;
         }
    }
    if(key[ALLEGRO_KEY_RIGHT]){
      jugador->bitmap_x+=PIXEL;
        if ((mapaenv[y][x+1] == 'm')||(mapaenv[y][x+1] == 'L')){
          jugador->bitmap_x-=PIXEL;
         }
        if(mapaenv[y][x+1]=='B'&&jugador->keys<1){
          jugador->bitmap_x-=PIXEL;
         }
    }
}
void asignar(char mapaenv[ANCHO][LARGO], char mapausado[ANCHO][LARGO]){
  int y, x;
   for(y=0;y<ANCHO;y++){
     for(x=0;x<LARGO;x++){
      mapaenv[y][x]= mapausado[y][x];
     }
    }
}
void escritura(char mapaenv[ANCHO][LARGO], char mapaoriginal[ANCHO][LARGO]){
  int y, x;
   for(y=0;y<ANCHO;y++){
     for(x=0;x<LARGO;x++){
      mapaoriginal[y][x]=mapaenv[y][x];
     }
   }
}
void vaciar(char map[ANCHO][LARGO],char map2[ANCHO][LARGO],char map3[ANCHO][LARGO],char map4[ANCHO][LARGO],char map5[ANCHO][LARGO],char map6[ANCHO][LARGO],char map7[ANCHO][LARGO],char map8[ANCHO][LARGO],char map9[ANCHO][LARGO],char map10[ANCHO][LARGO],char map11[ANCHO][LARGO],char map12[ANCHO][LARGO],struct JUG jugador)
{
  int y,x;
  for (y = 0; y < ANCHO; y++) {
      for (x = 0; x < LARGO; x++) {
        map[y][x] = ' ';
        map2[y][x] = ' ';
        map3[y][x] = ' ';
        map4[y][x] = ' ';
        map5[y][x] = ' ';
        map6[y][x] = ' ';
        map7[y][x] = ' ';
        map8[y][x] = ' ';
        map9[y][x] = ' ';
        map10[y][x] = ' ';
        map11[y][x] = ' ';
        map12[y][x] = ' ';
      }
  }
}
void puntaje(char mapaenv[ANCHO][LARGO],struct ranking* puntos,struct JUG jugador){
  if(mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]=='M'){
    mapaenv[jugador.bitmap_y/40][jugador.bitmap_x/40]='-';
    puntos->puntaje +=50;
  }
}
void leerranking(ALLEGRO_FONT* font,struct ranking lectura[num_de_puntaje])
{
  int i;
  FILE* archivo = fopen("ranking.txt", "r+");
  i=0;
  while(!feof(archivo)){
    fscanf(archivo, "%s %s %d", lectura[i].nombre, lectura[i].numero_jug, &lectura[i].puntaje);
    num_de_puntaje++;
    i++;
    printf("a");
  }
fclose(archivo);
}
void ordenar_ranking(struct ranking lectura[num_de_puntaje]){
  struct ranking temp;
  int i,j;
  for (i = 0; i < num_de_puntaje - 1; i++) {
        for (j = 0; j < num_de_puntaje - i - 1; j++) {
            if (lectura[j].puntaje < lectura[j + 1].puntaje) {
                temp = lectura[j];
                lectura[j] = lectura[j + 1];
                lectura[j + 1] = temp;
                printf("e");
            }
        }
    }
  FILE* arch_orden = fopen ("nuevo_ranking.txt", "w");
  for (i = 0; i < num_de_puntaje; i++) {
        fprintf(arch_orden, "%s %s %d\n", lectura[i].nombre, lectura[i].numero_jug, lectura[i].puntaje);
    }
  fclose(arch_orden);
}
void mostrar_ranking(ALLEGRO_FONT* font,struct ranking lectura[num_de_puntaje]){
  int posY = 100,i,mostrar;
  mostrar=10;
  al_clear_to_color(al_map_rgb(255,255,255));
  printf("c");
    for (i = 0; i < mostrar; i++){
        al_draw_textf(font, al_map_rgb(0, 0, 0), 200, posY, 0, "%s  %s %d", lectura[i].nombre,lectura[i].numero_jug,lectura[i].puntaje);
        posY += 50;
    }
  printf("f");
  sleep(4);
}
void registrar_ranking(struct ranking puntos,ALLEGRO_FONT* font){
  int numero;
  char num[5];
  numero=rand()%1000+1;
  sprintf(num, "%d", numero);
  sprintf(puntos.nombre, "jugador ");
  strcat(puntos.nombre, num);
  al_draw_textf(font, al_map_rgb(0, 0, 0), 200, 100, ALLEGRO_ALIGN_LEFT, "USTED ES EL %s SU PUNTAJE FUE:  %d",puntos.nombre,puntos.puntaje);
  FILE * archivo = fopen("ranking.txt", "a");
  fprintf(archivo, "%s %d\n", puntos.nombre, puntos.puntaje);
  fclose(archivo);
}
