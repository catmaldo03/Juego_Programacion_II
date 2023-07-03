#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/file.h>
#include <allegro5/allegro_font.h>
#define ANCHO 30
#define LARGO 41
struct JUG{
   int bitmap_x;
   int bitmap_y;
   int vida;
// vidas,;
};
int main(){
   struct JUG jugador;
   int x, y, posxj, posyj;
   char map[ANCHO][LARGO];
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
   ALLEGRO_BITMAP* lim = al_load_bitmap("X.png");
   ALLEGRO_BITMAP* muro = al_load_bitmap("muro.png");
   ALLEGRO_BITMAP* jug = al_load_bitmap("jug.png");
    ALLEGRO_BITMAP* fal = al_load_bitmap("falso.png");
   //---eventos-------
   al_register_event_source(queue, al_get_keyboard_event_source());
   al_register_event_source(queue, al_get_display_event_source(disp));
   al_register_event_source(queue, al_get_timer_event_source(timer));
   bool done = false;
   bool redraw = true;
   ALLEGRO_EVENT event;

   al_start_timer(timer);

   // Leer el mapa del archivo
   for (y = 0; y < ANCHO; y++) {
      for (x = 0; x < LARGO; x++) {
         map[y][x] = al_fgetc(file);
      }
   }
   al_fclose(file);
// ----posiciona al jugador ---------
   for (y = 0; y < ANCHO; y++) 
   {
     for (x = 0; x < LARGO; x++) 
     {
        if (map[y][x] == 'J') 
        {
           jugador.bitmap_x=x;
           jugador.bitmap_y=y;
           jugador.bitmap_x=jugador.bitmap_x*20;
           jugador.bitmap_y=jugador.bitmap_y*20;
           posxj=jugador.bitmap_x;
           posyj=jugador.bitmap_y;
         }

      }
   }
   jugador.vida = 3;
   while (1){
      al_wait_for_event(queue, &event);
      switch(event.type)
      {
       case ALLEGRO_EVENT_TIMER:
        redraw = true;
        break;

       case ALLEGRO_EVENT_KEY_DOWN:
        if(event.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            jugador.bitmap_y-=20;
            if (map[y-1][x] == 'm')
            {
              jugador.bitmap_y+=20;
            }
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            jugador.bitmap_y+=20;
            if (map[y+1][x] == 'm')
            {
              jugador.bitmap_y-=20;
            }
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
            jugador.bitmap_x-=20;
            if (map[y][x-1] == 'm')
            {
              jugador.bitmap_x+=20;
            }
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
            jugador.bitmap_x+=20;
            if (map[y][x+1] == 'm')
            {
              jugador.bitmap_x-=20;
            }
            if(map[y][x+1] == 't')
            {
              jugador.bitmap_x-=20;
            } 
        }
        
        if(event.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
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
         for (y = 0; y < ANCHO; y++) 
         {
            for (x = 0; x < LARGO; x++) 
            {
               if (map[y][x] == 'm') 
               {
                  al_draw_bitmap(muro, x * 20, y * 20, 0);  // muestra los muros
               }
               if (map[y][x] == 'p') 
               {
                  al_draw_bitmap(lim, x * 20, y * 20, 0);  //  Muestra las trampas
               }
               if (map[y][x] == 't') 
               {
                  al_draw_bitmap(fal, x * 20, y * 20, 0);  // muestra los muros
               }
            }
         }
         
         
//-------calculos del mapa--------------
   x=jugador.bitmap_x/20;
   y=jugador.bitmap_y/20;
   al_draw_textf(font, al_map_rgb(0, 0, 0), 0, 0, 0, "bitx: %d, bity: %d, x: %d, y: %d,vida %d",jugador.bitmap_x, jugador.bitmap_y,x,y,jugador.vida);

   if(map[y][x] == 'p')
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