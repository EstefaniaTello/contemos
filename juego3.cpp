#include <iostream>
#include<allegro5/allegro.h>
#include<stdlib.h>
#include<string.h>
#include <allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>
#include<string>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<Windows.h>
#include<sstream>
#include<ctime>
#include<stdio.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "FS_libreria.h"

#define M 50

using namespace std;
 
void jugar(ALLEGRO_DISPLAY* ventana);
void menu(ALLEGRO_DISPLAY* ventana);
int puntaje(int resultado, int avanceJugador, int puntos);
void usarTeclado(ALLEGRO_DISPLAY* ventana);
float ancho = 1106;
float alto = 700;

ALLEGRO_BITMAP* buffer;
ALLEGRO_FONT* Golden_Age_Shad = al_load_font("fuentes/Golden_Age_Shad.otf", 100, 0);
ALLEGRO_FONT* Golden_Age_Shad_pequeño;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_COLOR blanco;
ALLEGRO_COLOR naranja;
ALLEGRO_COLOR negro;
ALLEGRO_COLOR rojo;
ALLEGRO_COLOR azul;
ALLEGRO_KEYBOARD_STATE keyState;

int main()
{
	srand (time(NULL));
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

	// V E N T A N A
	ALLEGRO_DISPLAY* ventana = al_create_display(ancho, alto);
	ALLEGRO_BITMAP* buffer = al_create_bitmap(ancho, alto);
	Golden_Age_Shad = al_load_font("fuentes/Golden_Age_Shad.otf", 70, 0);
	Golden_Age_Shad_pequeño = al_load_font("fuentes/Golden_Age_Shad.otf", 30, 0);

	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);
	al_set_window_title(ventana, "CONTEMOS");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);

	//Q U E U E
	queue = al_create_event_queue();

	//C O L O R E S
	blanco = al_map_rgb(255, 255, 255);
	naranja = al_map_rgb(239, 186, 36);
	negro = al_map_rgb(0, 0, 0);

	al_register_event_source(queue, al_get_mouse_event_source());

	menu(ventana);
	
}

void menu(ALLEGRO_DISPLAY*ventana)
{
	ALLEGRO_BITMAP* menu_null = al_load_bitmap("imagenes/fondo/background.png");
	ALLEGRO_BITMAP* menu_start = al_load_bitmap("imagenes/fondo/background_jugar.png");
	ALLEGRO_BITMAP* menu_start_1 = al_load_bitmap("imagenes/fondo/background_jugar_1.png");
	ALLEGRO_BITMAP* menu_exit = al_load_bitmap("imagenes/fondo/background_salir.png");
	ALLEGRO_BITMAP* menu_exit_1 = al_load_bitmap("imagenes/fondo/background_salir_1.png");
	ALLEGRO_BITMAP* buffer = al_load_bitmap("fondo1.png");
	ALLEGRO_BITMAP* tutorial_null = al_load_bitmap("fondo/tutorial/1.png");
	ALLEGRO_BITMAP* tutorial_1 = al_load_bitmap("fondo/tutorial/2.png");
	ALLEGRO_BITMAP* tutorial_2 = al_load_bitmap("fondo/tutorial/3.png");
	blanco = al_map_rgb(255, 255, 255);
	naranja = al_map_rgb(239, 186, 36);
	negro = al_map_rgb(0, 0, 0);
	rojo = al_map_rgb(255, 43, 43);
	azul = al_map_rgb(53, 43, 255);

	bool end_program = false;
	bool tutorial = false;

	int x = -1, y = -1;
	int segundo = 0;
	while (!end_program)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		al_clear_to_color(negro);



		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && !tutorial)
		{
			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 704 && x <= 976 && y >= 398 && y <= 475)
			{
				al_draw_bitmap(menu_start_1, 0, 0, 0);
				if (evento.mouse.button & 1)
				{
					al_draw_bitmap(menu_start, 0, 0, 0);
					tutorial = true;
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
						end_program = true;
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

		if (tutorial)
		{
			al_draw_bitmap(tutorial_null, 0, 0, 0);
			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				x = evento.mouse.x;
				y = evento.mouse.y;
				if (x >= 811 && x <= 942 && y >= 522 && y <= 604)
				{
					al_draw_bitmap(tutorial_1, 0, 0, 0);
					if (evento.mouse.button & 1)
					{
						al_draw_bitmap(tutorial_2, 0, 0, 0);
						printf("Termino el tutorial\n");
						jugar(ventana);
						end_program = true;
					}
				}				
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
		queue = al_create_event_queue();
		al_wait_for_event(queue, &evento);
		al_clear_to_color(negro);
		al_flip_display();

	}
	cout << "diste click en salir";
}

void jugar(ALLEGRO_DISPLAY * ventana)
{
	cout << "Presionaste JUGAR\n";
	ALLEGRO_EVENT evento;
	al_wait_for_event(queue, &evento);
	
	bool end = false;
	int x = -1, y = -1;

	while (!end)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);
		al_clear_to_color(negro);
		al_flip_display();
		usarTeclado(ventana);
		end = true;
	}

}

bool perdiste_game(ALLEGRO_DISPLAY* ventana)
{
	ALLEGRO_BITMAP* perdiste[5] = { al_load_bitmap("fondo/perdiste/estandar.png"),
									al_load_bitmap("fondo/perdiste/si/1.png"),
									al_load_bitmap("fondo/perdiste/si/2.png"),
									al_load_bitmap("fondo/perdiste/no/1.png"),
									al_load_bitmap("fondo/perdiste/no/2.png") };

	bool salir_program = false;
	bool restart;

	int x = -1, y = -1;
	while (!salir_program)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);

		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = evento.mouse.x;
			y = evento.mouse.y;

			if (x >= 415 && x <= 688 && y >= 322 && y <= 399)
			{
				al_draw_bitmap(perdiste[1], 0, 0, 0);
				if (evento.mouse.button & 1)
				{
					al_draw_bitmap(perdiste[2], 0, 0, 0);
					restart = true;
					salir_program = true;
				}
			}
			else
			{
				if (x >= 416 && x <= 692 && y >= 469 && y <= 545)
				{
					al_draw_bitmap(perdiste[3], 0, 0, 0);
					if (evento.mouse.button & 1)
					{
						al_draw_bitmap(perdiste[4], 0, 0, 0);
						restart = false;
						salir_program = true;
					}
				}
				else
				{
					al_draw_bitmap(perdiste[0], 0, 0, 0);
				}
			}
		}
		else
		{
			al_draw_bitmap(perdiste[0], 0, 0, 0);
		}

		al_flip_display();
	}
	return restart;
}

bool ganaste_game(ALLEGRO_DISPLAY* ventana, int puntos, int vidas)
{
	
	ALLEGRO_BITMAP* ganaste[3] = { al_load_bitmap("fondo/ganaste/ok_1.png"),
									al_load_bitmap("fondo/ganaste/ok_1_5.png"),
									al_load_bitmap("fondo/ganaste/ok_2.png") };
	ALLEGRO_BITMAP* continuar[5] = { al_load_bitmap("fondo/continuar/estandar.png"),
									al_load_bitmap("fondo/continuar/si/1.png"),
									al_load_bitmap("fondo/continuar/si/2.png"),
									al_load_bitmap("fondo/continuar/no/1.png"),
									al_load_bitmap("fondo/continuar/no/2.png") };
	bool salir_program = false, ok = false;
	bool restart;

	int x = -1, y = -1;
	while (!salir_program)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(queue, &evento);

		if (!ok)
		{
			al_draw_bitmap(ganaste[0], 0, 0, 0);
			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				x = evento.mouse.x;
				y = evento.mouse.y;
				al_draw_bitmap(ganaste[0], 0, 0, 0);
				if (x >= 416 && x <= 688 && y >= 531 && y <= 607)
				{
					al_draw_bitmap(ganaste[1], 0, 0, 0);
					if (evento.mouse.button & 1)
					{
						al_draw_bitmap(ganaste[2], 0, 0, 0);
						ok = true;
					}
				}
				
			}
			al_draw_text(Golden_Age_Shad, negro, 349, 186, NULL, (to_string(puntos)).c_str());
			al_draw_text(Golden_Age_Shad, negro, 349, 257, NULL, ("x"+to_string(vidas)).c_str());
			al_draw_text(Golden_Age_Shad, azul, 346, 397, NULL, (to_string(puntos*vidas)).c_str());
		}
		else
		{
			al_draw_bitmap(continuar[0], 0, 0, 0);
			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				x = evento.mouse.x;
				y = evento.mouse.y;

				if (x >= 413 && x <= 688 && y >= 255 && y <= 331)
				{
					al_draw_bitmap(continuar[1], 0, 0, 0);
					if (evento.mouse.button & 1)
					{
						al_draw_bitmap(continuar[2], 0, 0, 0);
						restart = true;
						salir_program = true;
					}
				}
				else
				{
					if (x >= 413 && x <= 688 && y >= 426 && y <= 505)
					{
						al_draw_bitmap(continuar[3], 0, 0, 0);
						if (evento.mouse.button & 1)
						{
							al_draw_bitmap(continuar[4], 0, 0, 0);
							restart = false;
							salir_program = true;
						}
					}
				}
			}
		}
		al_flip_display();
	}
	return restart;
}


void usarTeclado(ALLEGRO_DISPLAY* ventana)
{

	//para que se ejecute a la misma velocidad en cualquier computadora 
	ALLEGRO_TIMER* tiempo = al_create_timer(1.0 / 5);
	ALLEGRO_EVENT_QUEUE* evento_queue = al_create_event_queue();
	ALLEGRO_BITMAP* caminando_right[8];
	ALLEGRO_BITMAP* caminando_left[8];
	ALLEGRO_BITMAP* vidas[8];
	ALLEGRO_BITMAP* fondo[2];
	
	ALLEGRO_KEYBOARD_STATE keyState;

	al_register_event_source(evento_queue, al_get_keyboard_event_source());
	al_register_event_source(evento_queue, al_get_timer_event_source(tiempo));
	al_get_keyboard_state(&keyState);
	//no declarar variables antes del tiempo
	al_start_timer(tiempo);

	// V A R I A B L E S
	//Booleanos
	bool terminado = false, dibujo = true, activo = false, correcto = true, game_over = false, restart, derecha = true;
	//Enteros
	int x = 60, y = 460;
	int xfondo = 60;
	int velMovimiento = 200;
	int i, j, l, indice, resultado, avanceJugador, puntos = 0;
	indice = 0, j = 0, avanceJugador = 1;
	int n1, n2;
	int rf = 5;
	n1 = 1;
	n2 = rand() % rf + 1;
	resultado = n1 + n2;

	//cargar imagenes
	for (i = 0; i < 8; i++)
	{
		std::stringstream str;
		str << "sprites/derecha/" << i + 1 << ".png";
		caminando_right[i] = al_load_bitmap(str.str().c_str());
	}
	for (i = 0; i < 8; i++)
	{
		std::stringstream str;
		str << "sprites/izquierda/" << i + 1 << ".png";
		caminando_left[i] = al_load_bitmap(str.str().c_str());
	}

	for (j = 0; j < 2; j++)
	{
		std::stringstream str;
		str << "fondo/" << j + 1 << ".png";
		fondo[j] = al_load_bitmap(str.str().c_str());
	}
	for (l = 0; l < 8; l++)
	{
		std::stringstream str;
		str << "lifes/" << l << ".png";
		vidas[l] = al_load_bitmap(str.str().c_str());
	}
	j = 0;
	l = 7;

	while (!terminado)
	{
		ALLEGRO_EVENT eventos;
		al_wait_for_event(evento_queue, &eventos);
		if (!game_over)
		{
			al_draw_bitmap(fondo[j], 0, 0, 0);
			if (eventos.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (eventos.keyboard.keycode)
				{
				case ALLEGRO_KEY_RIGHT:
					if (avanceJugador < 50)
					{
						derecha = true;
						x += velMovimiento;
						xfondo += velMovimiento;
						avanceJugador++;

						if (x >= 1060)
						{
							x = 60;
						}
						if (xfondo < 1060)
						{
							j = 0;
						}
						else
						{
							j = 1;
							if (xfondo > 1920)
							{
								j = 0;
								xfondo = 60;

							}
						}
					}
					break;
				case ALLEGRO_KEY_LEFT:
					if (avanceJugador > 1)
					{
						derecha = false;
						avanceJugador--;
						x -= velMovimiento;
						xfondo -= velMovimiento;

						if (x < 60)
						{
							x = 860;
						}
						if (xfondo >= 1060)
						{
							j = 1;
						}
						else
						{
							j = 0;
							if (xfondo < 60)
							{
								j = 1;
								xfondo = 1860;

							}
						}
					}
					break;
				case ALLEGRO_KEY_ENTER:
					puntos = puntaje(resultado, avanceJugador, puntos);
					correcto = respuesta(resultado, avanceJugador);
					if (!correcto)
					{
						x = 60;
						xfondo = 60;
						avanceJugador = 1;
						n1 = 1;
						n2 = rand() % rf + 1;
						l--;
						if (l == 0)
						{
							game_over = true;
							printf("PERDISTE");
						}
					}
					else
					{
						n1 = resultado;
						avanceJugador = resultado;
						if (n1 == M)
						{
							game_over = true;
							printf("GANASTE");
						}
						else
						{
							n2 = rand() % rf + 1;
							while (n1 + n2 > M)
							{
								n2 = rand() % rf + 1;
							}
						}
					}
					resultado = n1 + n2;
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
					if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
					{
						x -= velMovimiento;
					}
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
				//impNum(n1, n2);
				al_draw_text(Golden_Age_Shad, azul, 250, 311, NULL, (to_string(n1)).c_str());
				al_draw_text(Golden_Age_Shad, azul, 530, 311, NULL, (to_string(n2)).c_str());
				al_draw_text(Golden_Age_Shad, azul, 800, 311, NULL, (to_string(avanceJugador)).c_str());
				//mensajes(avanceJugador, puntos); 
				al_draw_text(Golden_Age_Shad_pequeño, rojo, 200, 410, NULL, "ESTAS EN EL");
				al_draw_text(Golden_Age_Shad_pequeño, rojo, 480, 410, NULL, "AVANZA");
				al_draw_text(Golden_Age_Shad_pequeño, rojo, 742, 410, NULL, "LlEGASTE A");
				al_draw_text(Golden_Age_Shad, rojo, 70, 49, NULL, (to_string(puntos)).c_str());
				if (derecha)
				{
					al_draw_bitmap(caminando_right[indice], x, y, NULL);
				}
				else
				{
					al_draw_bitmap(caminando_left[indice], x, y, NULL);
				}
				
				al_draw_bitmap(vidas[l], 500, 74, NULL);
			}
		}
		else
		{
			if (l <= 0)
			{
				//al_draw_bitmap(ganaste[0], 0, 0, 0);
				restart = perdiste_game(ventana);
				l = 7;
				puntos = 0;
			}
			else
			{
				//al_draw_bitmap(ganaste[0], 0, 0, 0);
				restart = ganaste_game(ventana, puntos,l);
				puntos = puntos * l;
			}
			
			if (restart)
			{
				game_over = false;
				dibujo = true;
				activo = false;
				correcto = true;
				j = 0;
				x = 60;
				xfondo = 60;
				avanceJugador = 1;
				n1 = 1;
				n2 = rand() % rf + 1;
				resultado = n1 + n2;
				derecha = true;

			}
			else
			{
				terminado = true;
			}
		}
		al_flip_display();
	}
	
	for (i = 0; i < 8; i++)
	{
		al_destroy_bitmap(caminando_right[i]);
	}
	for (i = 0; i < 8; i++)
	{
		al_destroy_bitmap(caminando_left[i]);
	}
	al_destroy_event_queue(evento_queue);
	al_destroy_bitmap(fondo[j]);
	al_destroy_display(ventana);
}