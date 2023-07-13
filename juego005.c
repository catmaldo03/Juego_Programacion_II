#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/file.h>
#include <allegro5/allegro_font.h>
#include<stdio.h>
#define ANCHO 30
#define LARGO 41
#define PIXEL 20
#define MOV 20
#define MAX 6
#define cantidad 2
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
    int flech_x[MAX];
    //poner aqui la variable indicacion y contador

};

void  cargamapa(char map[ANCHO][LARGO], ALLEGRO_FILE* file);
void posjugador(char map[ANCHO][LARGO],struct JUG* jugador);
void posenemigo(struct enemigo en [cantidad],char map[ANCHO][LARGO]);
int main(){
   typedef struct enemigo ENE;
   typedef struct JUG PERSONA;
   PERSONA jugador;
   ENE en [cantidad];
   int x, y, posxj, posyj,enx,eny,cont,efx,i,velocidad=0,velocidad_2=0;
   int flech_pos, flech_y;
   char map[ANCHO][LARGO];
   //variable contador que regule la velocidad del enemigo
//----------Inicializaciones---------------------------------
   al_init();
   al_install_keyboard();
   ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
   ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
   ALLEGRO_DISPLAY* disp = al_create_display(800, 600); 
   al_init_image_addon();
   ALLEGRO_FILE* file = al_fopen("mapa1.txt", "r");
   al_start_timer(timer);
   ALLEGRO_FONT* font = al_create_builtin_font();
   // ----Inicializaciones DE bitmap------
   ALLEGRO_BITMAP* lim = al_load_bitmap("pinch.png");
   ALLEGRO_BITMAP* muro = al_load_bitmap("roca1.png");
   ALLEGRO_BITMAP* jug = al_load_bitmap("jug.png");
   ALLEGRO_BITMAP* fal = al_load_bitmap("falso.png");
   ALLEGRO_BITMAP* ene = al_load_bitmap("ene.png");
   ALLEGRO_BITMAP* flecha = al_load_bitmap("flecha.png");
   //---eventos-------
   al_register_event_source(queue, al_get_keyboard_event_source());
   al_register_event_source(queue, al_get_display_event_source(disp));
   al_register_event_source(queue, al_get_timer_event_source(timer));
   bool done = false;
   bool redraw = true;
   ALLEGRO_EVENT event;

   al_start_timer(timer);

   cargamapa(map,file);
 posjugador(map,&jugador); 
 posxj =jugador.bitmap_x;
 posyj=jugador.bitmap_y; 
//posiciona al enemigo
 posenemigo(en,map);


   unsigned char key[ALLEGRO_KEY_MAX];
   memset(key, 0, sizeof(key));
   jugador.vida = 3;
   en [1].indicacion=0;
   cont=0;
   en [1].vida=3;
   en [1].activo=1;
   for(i=0;i<MAX;i++)
   {
   en [0].flech_x[i]= en[0].e_x;
   en [0].flech_x[i]= en [0].flech_x[i]-20;
   }
   i=0;
   while (1){
      al_wait_for_event(queue, &event);
      switch(event.type)
      {
       case ALLEGRO_EVENT_TIMER:
       //enemigo en[1]-----------------------------------------------------------------------------------
       printf("%d",velocidad);
       if(velocidad==0)
        {
      
        if(en [1].indicacion==0&&cont<2&&en [1].activo==1)
        {
            en [1].e_x+=MOV;
        }
        if(map[eny][enx+2] == 'm'&& en [1].indicacion==0&&en [1].activo==1)
        {
            en [1].e_x-=MOV;
            en [1].indicacion =1;
            cont++;
        }
            
        if(en [1].indicacion==1&&en [1].activo==1)
        {
             en [1].e_y+=MOV;
        }
        if(map[eny+2][enx] == 'm'&& en [1].indicacion==1&&en [1].activo==1)
        {
            en [1].e_y-=MOV;
            en [1].indicacion =0;
        }
        if(cont==2 && en [1].indicacion==0&&en [1].activo==1)
        {
         en [1].e_x-=MOV;
        }
        if(cont==2 && map[eny][enx-2]== 'm'&&en [1].indicacion==0&&en [1].activo==1)
        {
            en [1].e_x+=MOV;
            cont--;
        }
        
        }
        velocidad=(velocidad+1)%4;
        //jugador-------------------------------------------------------------------------------------------------------
        if(key[ALLEGRO_KEY_UP]){
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
        }
        //en [0]----------------------------------------------------------------------------------
        velocidad_2=(velocidad_2+1)%80;
       if(velocidad==0)
        {
            en[0].flech_x[i]-=MOV;
            flech_pos=en[0].flech_x[i]/20;
            if (map[en[0].e_y][flech_pos-1] == 'm')
            {
              en[0].flech_x[i]+=MOV;
            }
            
        } 
        if(velocidad_2==0)
            {
                i++;
            }
        printf("%d", velocidad_2);
        if(key[ALLEGRO_KEY_ESCAPE])
            done = true;

        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= KEY_SEEN;
       
        redraw = true;
        break;

       case ALLEGRO_EVENT_KEY_DOWN:
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
          if(jugador.bitmap_x+MOV==en [1].e_x)
          {
            en [1].vida--;
          }
          if(en [1].vida==0)
          {
            for(y = 0; y < ANCHO; y++){
              for (x = 0; x < LARGO; x++) 
            {
               if(map[y][x] == 'E') 
                 map[y][x] ='-';
            }
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
         al_clear_to_color(al_map_rgb(255, 255, 255));
         al_draw_bitmap(jug, jugador.bitmap_x, jugador.bitmap_y, 0);//el jugador
         al_draw_bitmap(ene, en [0].e_x, en [0].e_y,0);
         al_draw_bitmap(ene, en [1].e_x, en [1].e_y,0);
          al_draw_bitmap(flecha,en[0].flech_x[i], en [0].e_y,0);
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
         
         
//-------calculos del mapa--------------
   x=jugador.bitmap_x/PIXEL;
   y=jugador.bitmap_y/PIXEL;
   enx=en [1].e_x/PIXEL;
   eny= en [1].e_y/PIXEL;
   al_draw_textf(font, al_map_rgb(0, 0, 0), 0, 0, 0, "bitx: %d, bity: %d, x: %d, y: %d,vida %d, %d,%d, eny:%d,enx%d,env:%d, flecha: %d,i:%d",jugador.bitmap_x, jugador.bitmap_y,x,y,jugador.vida,en [1].e_x,en [1].e_y,eny,enx,en [1].vida, flech_pos,i);
//------otras cosas--------
   
   if(map[y][x] == 'p')
   {
      jugador.vida-= 1;
      jugador.bitmap_x = posxj;
      jugador.bitmap_y = posyj;
   }
   if((x == enx)&&(y == eny))
   {
      jugador.vida-= 1;
      jugador.bitmap_x = posxj;
      jugador.bitmap_y = posyj;
   } 
   if(jugador.vida==0)
   {
      done = true;
      break;
   }
   if(en [1].vida==0)
   {
     en [1].activo=0;
     en [1].e_x=0;
     en [1].e_y=0;
   }
   if(i==(MAX-1))
   {
    i=0;
    en [0].flech_x[i]= en[0].e_x;
   en [0].flech_x[i]= en [0].flech_x[i]-20;
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
   int y,x;
   for (y = 0; y < ANCHO; y++) {
      for (x = 0; x < LARGO; x++) {
         map[y][x] = al_fgetc(file);
      }
   }
   al_fclose(file);
}
void posjugador(char map[ANCHO][LARGO],struct JUG* jugador){
   int y,x;
   for (y = 0; y < ANCHO; y++) 
   {
     for (x = 0; x < LARGO; x++) 
     {
        if (map[y][x] == 'J') 
        {
           jugador->bitmap_x=x;
           jugador->bitmap_y=y;
           jugador->bitmap_x=jugador->bitmap_x*PIXEL;
           jugador->bitmap_y=jugador->bitmap_y*PIXEL;
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
