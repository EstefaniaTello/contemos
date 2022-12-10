#include <iostream>
#include<allegro5/allegro.h>
#include<stdlib.h>
#include <allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>
#include<string>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<Windows.h>
#include<sstream>


using namespace std;


void salir();
void jugar(ALLEGRO_COLOR negro, ALLEGRO_BITMAP* fondo_juego, ALLEGRO_EVENT_QUEUE* queue);
void menu();
void usarTeclado(ALLEGRO_DISPLAY* ventana);
int ancho = 1106;
int alto = 700;
ALLEGRO_DISPLAY* ventana;
ALLEGRO_BITMAP* buffer;
ALLEGRO_FONT* Golden_Age_Shad;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_COLOR blanco;
ALLEGRO_COLOR naranja;
ALLEGRO_COLOR negro;
ALLEGRO_KEYBOARD_STATE keyState;

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
	al_install_keyboard();



	ventana = al_create_display(ancho, alto);
	ALLEGRO_BITMAP* buffer = al_create_bitmap(ancho, alto);
	Golden_Age_Shad = al_load_font("fuentes/Golden_Age_Shad.otf", 70, 0);

	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);
	al_set_window_title(ventana, "CONTEMOS");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);

	queue = al_create_event_queue();

	blanco = al_map_rgb(255, 255, 255);
	naranja = al_map_rgb(239, 186, 36);
	negro = al_map_rgb(0, 0, 0);

	al_register_event_source(queue, al_get_mouse_event_source());

	menu();
	
}

void menu()
{
	ALLEGRO_BITMAP* menu_null = al_load_bitmap("imagenes/fondo/background.png");
	ALLEGRO_BITMAP* menu_start = al_load_bitmap("imagenes/fondo/background_jugar.png");
	ALLEGRO_BITMAP* menu_start_1 = al_load_bitmap("imagenes/fondo/background_jugar_1.png");
	ALLEGRO_BITMAP* menu_exit = al_load_bitmap("imagenes/fondo/background_salir.png");
	ALLEGRO_BITMAP* menu_exit_1 = al_load_bitmap("imagenes/fondo/background_salir_1.png");
	ALLEGRO_BITMAP* buffer = al_load_bitmap("fondo1.png");
	blanco = al_map_rgb(255, 255, 255);
	naranja = al_map_rgb(239, 186, 36);
	negro = al_map_rgb(0, 0, 0);

	bool end_program = false;

	int x = -1, y = -1;
	int segundo = 0;
	while (!end_program)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		al_clear_to_color(negro);



		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 704 && x <= 976 && y >= 398 && y <= 475)
			{
				al_draw_bitmap(menu_start_1, 0, 0, 0);
				if (evento.mouse.button & 1)
				{
					al_draw_bitmap(menu_start, 0, 0, 0);
					jugar(negro, buffer, queue);

				}
				else
				{
					al_draw_bitmap(menu_start_1, 0, 0, 0);
				}
			}
			else
			{
				if (x >= 704 && x <= 976 && y >= 529 && y <= 607)
				{
					al_draw_bitmap(menu_exit_1, 0, 0, 0);
					if (evento.mouse.button & 1)
					{
						al_draw_bitmap(menu_exit, 0, 0, 0);
						cout << "Presionaste SALIR\n";
						end_program = false;
					}
					else
					{
						al_draw_bitmap(menu_exit_1, 0, 0, 0);
					}
				}
				else
				{
					al_draw_bitmap(menu_null, 0, 0, 0);
				}
			}


		}
		else
		{
			al_draw_bitmap(menu_null, 0, 0, 0);
		}


		if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (evento.keyboard.keycode)
			{
			case ALLEGRO_KEY_DOWN:
				cout << "presionaste abajo\n";
				break;
			case ALLEGRO_KEY_UP:
				cout << "presionaste arriba\n";
				break;
			case ALLEGRO_KEY_ENTER:
			case ALLEGRO_KEY_PAD_ENTER:
				cout << "presionaste enter\n";
				break;

			default:
				break;
			}
		}

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

void jugar(ALLEGRO_COLOR negro, ALLEGRO_BITMAP* fondo_juego, ALLEGRO_EVENT_QUEUE* queue)
{
	cout << "Presionaste JUGAR\n";
	while (true)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		al_clear_to_color(negro);
		al_draw_bitmap(fondo_juego, 0, 0, 0);
		al_flip_display();
		usarTeclado(ventana);
	}
}

void usarTeclado(ALLEGRO_DISPLAY* ventana)
{

	ALLEGRO_BITMAP* buffer = al_load_bitmap("fondo1.png");
	//para que se ejecute a la misma velocidad en cualquier computadora 
	ALLEGRO_TIMER* tiempo = al_create_timer(1.0 / 5);
	ALLEGRO_EVENT_QUEUE* evento_queue = al_create_event_queue();
	ALLEGRO_BITMAP* caminando[8];
	ALLEGRO_KEYBOARD_STATE keyState;
	al_register_event_source(evento_queue, al_get_keyboard_event_source());
	al_register_event_source(evento_queue, al_get_timer_event_source(tiempo));
	al_get_keyboard_state(&keyState);
	//no declarar variables antes del tiempo
	al_start_timer(tiempo);


	bool terminado = false, dibujo = true, activo = false;
	int x = 60, y = 400;
	int velMovimiento = 70;
	int i, indice, dirPrevia;
	indice = 0, dirPrevia = 0;


	for (i = 0; i < 8; i++)
	{
		std::stringstream str;
		str << "sprites/" << i + 1 << ".jpg";
		caminando[i] = al_load_bitmap(str.str().c_str());
	}

	while (!terminado)
	{
		ALLEGRO_EVENT eventos;
		al_wait_for_event(evento_queue, &eventos);

		if (eventos.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (eventos.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT:
				x += velMovimiento;
				break;
			case ALLEGRO_KEY_LEFT:
				x -= velMovimiento;
				break;
			case ALLEGRO_KEY_ESCAPE:
				terminado = true;
				break;
			}
		}

		if (eventos.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			terminado = true;
		}
		else
		{
			if (eventos.type == ALLEGRO_EVENT_TIMER)
			{
				activo = true;
				if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
				{
					x += velMovimiento;
				}
				/*else
				{
					if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
					{
						x -= velMovimiento;
					}
				}*/
			}
			else
			{
				activo = false;
			}
			if (activo)
			{
				indice++;
				if (indice >= 8)
				{
					indice = 0;
				}
			}
			dibujo = true;
		}
		if (dibujo)
		{
			al_draw_bitmap(caminando[indice], x, y, NULL);
			al_flip_display();
			al_draw_bitmap(buffer, 0, 0, 0);
			//al_clear_to_color(negro);
		}
	}
	al_destroy_display(ventana);
	for (i = 0; i < 8; i++)
	{
		al_destroy_bitmap(caminando[i]);
	}
	al_destroy_event_queue(evento_queue);
}


