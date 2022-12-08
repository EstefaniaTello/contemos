#include <iostream>
#include<allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>
#include<string>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include <Windows.h>

using namespace std;

void salir();
void jugar();
void menu();
int ancho = 1280;
int alto = 838;


ALLEGRO_DISPLAY* ventana;
ALLEGRO_FONT* Golden_Age_Shad;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_COLOR blanco;
ALLEGRO_COLOR naranja;
ALLEGRO_COLOR negro;

int main()
{

	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR:404", "No se pudo cargar correctamente", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_init_image_addon();

	ventana = al_create_display(ancho, alto);
	Golden_Age_Shad = al_load_font("fuentes/Golden_Age_Shad.otf", 70, 0);

	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);
	al_set_window_title(ventana, "CONTEMOS");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);

	//segundoTimer = al_create_timer(1.0);
	queue = al_create_event_queue();

	blanco = al_map_rgb(255, 255, 255);
	naranja = al_map_rgb(239, 186, 36);
	negro = al_map_rgb(0, 0, 0);

	
	//al_register_event_source(queue, al_get_timer_event_source(segundoTimer));
	//al_start_timer(segundoTimer);
	al_register_event_source(queue, al_get_mouse_event_source());

	menu();

	
}
void menu()
{
	ALLEGRO_BITMAP* menu_null = al_load_bitmap("imagenes/menu_null.jpeg");
	ALLEGRO_BITMAP* menu_iniciar = al_load_bitmap("imagenes/menu_iniciar.jpeg");
	ALLEGRO_BITMAP* menu_salir = al_load_bitmap("imagenes/menu_salir.jpeg");

	int x = -1, y = -1;
	int segundo = 0;
	while (true)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		/*if (evento.type == ALLEGRO_EVENT_TIMER)
		{
			if (evento.timer.source == segundoTimer)
			{
				segundo++;
			}
		}*/
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(menu_null, 0, 0, 0);


		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			cout << "x: " << x << "y : " << y << endl;
			x = evento.mouse.x;
			y = evento.mouse.y;
			if (x >= 801 && x <= 1077 && y >= 458 && y <= 546)
			{
				al_draw_bitmap(menu_iniciar, 0, 0, 0);
				if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					jugar();
				}
			}
			if (x >= 802 && x <= 1077 && y >= 609 && y <= 694)
			{
				al_draw_bitmap(menu_salir, 0, 0, 0);
				if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					salir();
				}

			}
		}
		if (x >= 200 && x <= 400 && y >= 280 && y <= 350)
		{
			al_draw_filled_rectangle(200, 280, 400, 350, naranja);
		}
		else
		{
			al_draw_filled_rectangle(200, 280, 400, 350, blanco);
		}
		al_draw_text(Golden_Age_Shad, al_map_rgb(255, 255, 255), 200, 200, NULL, "CONTEMOS ");
		al_flip_display();
	}

}

void salir()
{
	while (true)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		al_clear_to_color(negro);
		al_flip_display();

	}
	cout << "diste click en salir";
}

void jugar()
{

	while (true)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		al_clear_to_color(negro);
		al_draw_filled_circle(200, 200, 100, al_map_rgb(255, 255, 255));
		al_flip_display();

	}
	cout << "diste click en jugar";

}


