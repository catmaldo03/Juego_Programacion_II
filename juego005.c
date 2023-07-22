#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/file.h>
#include <allegro5/allegro_font.h>
#define ANCHO 15
#define LARGO 20
#define PIXEL 40
#define MOV 40
#define cantidad 10
#define KEY_SEEN     1
#define KEY_RELEASED 2
struct JUG{
   int bitmap_x;
   int bitmap_y;
   int vida;
// vidas,;
};
struct enemigo{
    int e_x;
    int e_y;
    int indicacion;
    int vida;
    int activo;
    //poner aqui la variable indicacion y contador

};
void posenemigo(struct enemigo en [cantidad],char map[ANCHO][LARGO]);
void  cargamapa(char map[ANCHO][LARGO], ALLEGRO_FILE* file);
void posjugador(char map[ANCHO][LARGO],struct JUG* jugador, int ubicacion);
int main(){
    typedef struct JUG PERSONA;
   PERSONA jugador;
   typedef struct enemigo ENE;
   ENE en [cantidad];
   int x, y, posxj, posyj,enx,eny,cont,efx,i,velocidad=0,velocidad_2=0,mapa,ubicacion=0,a;
   char map[ANCHO][LARGO];
    al_init();
   al_install_keyboard();
   ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
   ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
   ALLEGRO_DISPLAY* disp = al_create_display(800, 600); 
   al_init_image_addon();
   ALLEGRO_FILE* file = al_fopen("file1.txt", "r");
   mapa=1;
   al_start_timer(timer);
   ALLEGRO_FONT* font = al_create_builtin_font();
   ALLEGRO_BITMAP* lim = al_load_bitmap("pinch.png");
   ALLEGRO_BITMAP* muro = al_load_bitmap("muro2.png");
   ALLEGRO_BITMAP* jug = al_load_bitmap("X2.png");
   ALLEGRO_BITMAP* fal = al_load_bitmap("falso.png");
   ALLEGRO_BITMAP* ene = al_load_bitmap("ene.png");
   ALLEGRO_BITMAP* flecha = al_load_bitmap("flecha.png");
   al_register_event_source(queue, al_get_keyboard_event_source());
   al_register_event_source(queue, al_get_display_event_source(disp));
   al_register_event_source(queue, al_get_timer_event_source(timer));
   bool done = false;
   bool redraw = true;
   ALLEGRO_EVENT event;

   al_start_timer(timer);

   cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y; 
unsigned char key[ALLEGRO_KEY_MAX];
   memset(key, 0, sizeof(key));
   jugador.vida = 3;
   while(1)
   {
    al_wait_for_event(queue, &event);
      switch(event.type)
      {
       case ALLEGRO_EVENT_TIMER:
       if(mapa==2)

       {
         velocidad=(velocidad+1)%4;
        if(velocidad==0)
        {
          if(enx<x)
          {
            en [1].e_x+=MOV;

          }
        }
       }
       /*sif(key[ALLEGRO_KEY_UP]){
            jugador.bitmap_y-=MOV;
            if (map[y-1][x] == 'm')
            {
              jugador.bitmap_y+=MOV;
            }
        }
        if(key[ALLEGRO_KEY_DOWN]){
            jugador.bitmap_y+=MOV;
            if (map[y+1][x] == 'm')
            {
              jugador.bitmap_y-=MOV;
            }
        }
        if(key[ALLEGRO_KEY_LEFT]){
           jugador.bitmap_x-=MOV;
           if (map[y][x-1] == 'm')
            {
              jugador.bitmap_x+=MOV;
            }
            if(map[y][x-1] == 't')
            {
              jugador.bitmap_x+=MOV;
            }
        }
        if(key[ALLEGRO_KEY_RIGHT]){
            jugador.bitmap_x+=MOV;
            if (map[y][x+1] == 'm')
            {
              jugador.bitmap_x-=MOV;
            }
            if(map[y][x+1] == 't')
            {
              jugador.bitmap_x-=MOV;
            }
        }*/
        redraw = true;
        break;

        case ALLEGRO_EVENT_KEY_DOWN:
       //enemigo 1--------
        if(event.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            jugador.bitmap_y-=MOV;
            if (map[y-1][x] == 'm')
            {
              jugador.bitmap_y+=MOV;
            }
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            jugador.bitmap_y+=MOV;
            if (map[y+1][x] == 'm')
            {
              jugador.bitmap_y-=MOV;
            }
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
            jugador.bitmap_x-=MOV;
            if (map[y][x-1] == 'm')
            {
              jugador.bitmap_x+=MOV;
            }
            if(map[y][x-1] == 't')
            {
              jugador.bitmap_x+=MOV;
            } 
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
            jugador.bitmap_x+=MOV;
            if (map[y][x+1] == 'm')
            {
              jugador.bitmap_x-=MOV;
            }
            if(map[y][x+1] == 't')
            {
              jugador.bitmap_x-=MOV;
            } 
        }
        if (event.keyboard.keycode== ALLEGRO_KEY_Z)
        {
          if(map[y][x+1] == 't')
            {
              map[y][x+1] ='-';


            }
          if(map[y][x-1] == 't')
            {
              map[y][x-1] ='-';
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
         al_clear_to_color(al_map_rgb(255, 255, 255));
         for(i=0;i<cantidad && en[i].activo==1;i++)
         {
         al_draw_bitmap(ene, en [i].e_x, en [i].e_y,0);
         }
         al_draw_bitmap(jug, jugador.bitmap_x, jugador.bitmap_y, 0);//el jugador
         for (y = 0; y < ANCHO; y++) 
         {
            for (x = 0; x < LARGO; x++) 
            {
               if (map[y][x] == 'm') 
               {
                  al_draw_bitmap(muro, x * PIXEL, y * PIXEL, 0);  // muestra los muros
               }
               if (map[y][x] == 'p') 
               {
                  al_draw_bitmap(lim, x * PIXEL, y * PIXEL, 0);  //  Muestra las trampas
                  
               }
               if(map[y][x]=='t')
               {
                  al_draw_bitmap(fal, x * PIXEL, y * PIXEL, 0);
               }
            }
         }
    x=jugador.bitmap_x/PIXEL;
   y=jugador.bitmap_y/PIXEL;
   enx=en [1].e_x/PIXEL;
   eny= en [1].e_y/PIXEL;
   al_draw_textf(font, al_map_rgb(0, 0, 0), 0, 0, 0, "bitx: %d, bity: %d, x: %d, y: %d,mapa:%d,ubicacion:%d",jugador.bitmap_x, jugador.bitmap_y,x,y,mapa,ubicacion);
   if(map[y][x] == 'S'&&mapa==1)
   {
    mapa=2;
    ALLEGRO_FILE* file = al_fopen("file2.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   
   ubicacion=0;
   }
   if(map[y][x] == 'S'&&mapa==2)
   {
    mapa=3;
    ALLEGRO_FILE* file = al_fopen("file3.txt", "r");
    cargamapa(map,file);
    posjugador(map,&jugador,ubicacion); 
    posxj =jugador.bitmap_x;
    posyj=jugador.bitmap_y;
    ubicacion=1;

   }
   if(map[y][x] == 'e'&&mapa==3)
   {
    mapa=6;
    ALLEGRO_FILE* file = al_fopen("file6.txt", "r");
    cargamapa(map,file);
    posjugador(map,&jugador,ubicacion); 
    posxj =jugador.bitmap_x;
    posyj=jugador.bitmap_y;
    ubicacion=1;

   }
   if(map[y][x] == 'N'&&mapa==6)
   {
    mapa=5;
    ALLEGRO_FILE* file = al_fopen("file5.txt", "r");
    cargamapa(map,file);
    posjugador(map,&jugador,ubicacion); 
    posxj =jugador.bitmap_x;
    posyj=jugador.bitmap_y;
    ubicacion=0;

   }
   if(map[y][x] == 'e'&&mapa==6)
   {
    mapa=9;
    ALLEGRO_FILE* file = al_fopen("file9.txt", "r");
    cargamapa(map,file);
    posjugador(map,&jugador,ubicacion); 
    posxj =jugador.bitmap_x;
    posyj=jugador.bitmap_y;
    ubicacion=1;

   }
   if((map[y][x] == 'e'&&mapa==5)||(map[y][x] == 'N'&&mapa==9))
   {
    mapa=8;
    ALLEGRO_FILE* file = al_fopen("file8.txt", "r");
    cargamapa(map,file);
    posjugador(map,&jugador,ubicacion); 
    posxj =jugador.bitmap_x;
    posyj=jugador.bitmap_y;
    ubicacion=0;

   }
   if(map[y][x] == 'e'&&mapa==8)
   {
    mapa=11;
    ALLEGRO_FILE* file = al_fopen("file11.txt", "r");
    cargamapa(map,file);
    posjugador(map,&jugador,ubicacion); 
    posxj =jugador.bitmap_x;
    posyj=jugador.bitmap_y;
    ubicacion=1;

   }
   if(map[y][x] == 'e'&&mapa==9)
   {
    mapa=12;
    ALLEGRO_FILE* file = al_fopen("file12.txt", "r");
    cargamapa(map,file);
    posjugador(map,&jugador,ubicacion); 
    posxj =jugador.bitmap_x;
    posyj=jugador.bitmap_y;
    ubicacion=1;

   }
   if(map[y][x] == '1'&&mapa==1)
   {
    
    ALLEGRO_FILE* file = al_fopen("file4.txt", "r");
    cargamapa(map,file);
    posjugador(map,&jugador,ubicacion); 
    posxj =jugador.bitmap_x;
    posyj=jugador.bitmap_y;
    ubicacion=3;
    mapa=4;
   }
   if(map[jugador.bitmap_y/PIXEL][jugador.bitmap_x/PIXEL]=='e'&&mapa==4)
    {
      ALLEGRO_FILE* file = al_fopen("file7.txt", "r");
      cargamapa(map,file);
      posjugador(map,&jugador,ubicacion); 
      posxj =jugador.bitmap_x;
      posyj=jugador.bitmap_y;
      ubicacion=1;
      mapa=7;
    }
   if(map[jugador.bitmap_y/PIXEL][jugador.bitmap_x/PIXEL]=='1'&&mapa==7){
    ALLEGRO_FILE* file = al_fopen("file10.txt", "r");
      cargamapa(map,file);
      posjugador(map,&jugador,ubicacion); 
      posxj =jugador.bitmap_x;
      posyj=jugador.bitmap_y;
      ubicacion=0;
      mapa=10;
   }
   if(map[y][x] == 'N'&&mapa==2)
   {
    mapa=1;
    ALLEGRO_FILE* file = al_fopen("file1.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   
   ubicacion=0;
   }
   if(map[y][x] == 'o'&&mapa==4)
   {
    mapa=1;
    ALLEGRO_FILE* file = al_fopen("file1.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   
   ubicacion=0;
   }
   if(map[y][x] == 'o'&&mapa==7)
   {
    mapa=4;
    ALLEGRO_FILE* file = al_fopen("file4.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=3;
   }
    if(map[y][x] == 'o'&&mapa==10)
   {
    mapa=7;
    ALLEGRO_FILE* file = al_fopen("file7.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=1;
   }
   if(map[y][x] == 'N'&&mapa==3)
   {
    mapa=2;
    ALLEGRO_FILE* file = al_fopen("file2.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=0;
   }
   if(map[y][x] == 'o'&&mapa==6)
   {
    mapa=3;
    ALLEGRO_FILE* file = al_fopen("file3.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=1;
   }
   if(map[y][x] == 'S'&&mapa==5)
   {
    mapa=6;
    ALLEGRO_FILE* file = al_fopen("file6.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=1;
   }
   if(map[y][x] == 'o'&&mapa==8)
   {
    mapa=5;
    ALLEGRO_FILE* file = al_fopen("file5.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=0;
   }
   if(map[y][x] == 'S'&&mapa==8)
   {
    mapa=9;
    ALLEGRO_FILE* file = al_fopen("file9.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=1;
   }
    if(map[y][x] == 'o'&&mapa==9)
   {
    mapa=6;
    ubicacion=3;
    ALLEGRO_FILE* file = al_fopen("file6.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=1;
   }
    if(map[y][x] == 'o'&&mapa==12)
   {
    mapa=9;
    ubicacion=3;
    ALLEGRO_FILE* file = al_fopen("file9.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=1;
   }
    if(map[y][x] == 'o'&&mapa==11)
   {
    mapa=8;
    ubicacion=3;
    ALLEGRO_FILE* file = al_fopen("file8.txt", "r");
    cargamapa(map,file);
 posjugador(map,&jugador,ubicacion); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y;
   ubicacion=1;
   }
  if(mapa==2)
  {
    posenemigo(en,map);
    for(i=0;i<cantidad;i++)
    {
      en[i].activo=1;
      en[i].vida=3;
    }
  }
  else{
    for(i=0;i<cantidad;i++)
    {
      en[i].activo=0;
      en[i].vida=0;
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
void  cargamapa(char map[ANCHO][LARGO], ALLEGRO_FILE* file){
   // Leer el mapa del archivo
   int y,x,aux;
   for (y = 0; y < ANCHO; y++) {
      for (x = 0; x < LARGO; x++) {
         map[y][x] = al_fgetc(file);
         if(x==(LARGO-1))
         {
            aux=al_fgetc(file);
         }
      }
   }
   al_fclose(file);
}
void posjugador(char map[ANCHO][LARGO],struct JUG* jugador,int ubicacion){
   int y,x;
   for (y = 0; y < ANCHO; y++) 
   {
     for (x = 0; x < LARGO; x++) 
     {
        if(ubicacion==0){
        if (map[y][x] == 'J') 
        {
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
         }
        }
        if(ubicacion==1)
        {
          if (map[y][x] == 'j') 
        {
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
         }  
        }
        if(ubicacion==3){
            if (map[y][x] == 'P') 
        {
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
         } 
        }

      }
   }
}
void posenemigo(struct enemigo en [cantidad],char map[ANCHO][LARGO])
{
   int y,x,i=0;
   for (y = 0; y < ANCHO; y++) 
   {
     for (x = 0; x < LARGO; x++) 
     {
        if (map[y][x] == 'E') 
        {
           en [i].e_x=x;
            en [i].e_y=y;
           en [i].e_x= en [i].e_x*PIXEL;
            en [i].e_y= en [i].e_y*PIXEL;
            i++;
         }

      }
   }
   
}
