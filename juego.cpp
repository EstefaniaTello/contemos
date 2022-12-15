#include "prototipos.h"
#include "FS_libreria.h"

int main()
{

	ALLEGRO_COLOR azul = al_map_rgb(53, 43, 255);
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR naranja = al_map_rgb(239, 186, 36);
	ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR rojo = al_map_rgb(255, 43, 43);

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
	al_install_audio();
	al_init_acodec_addon();

	// V E N T A N A
	ALLEGRO_DISPLAY* ventana = al_create_display(ancho, alto);
	ALLEGRO_BITMAP* buffer = al_create_bitmap(ancho, alto);
	Golden_Age_Shad = al_load_font("fuentes/Golden_Age_Shad.otf", 70, 0);
	Golden_Age_Shad_pequenio = al_load_font("fuentes/Golden_Age_Shad.otf", 30, 0);

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

	// M U S I C A
	al_reserve_samples(5);

	ALLEGRO_SAMPLE* btnSonido = al_load_sample("Musica/boton.wav");
	ALLEGRO_SAMPLE* cancion = al_load_sample("Musica/musciakids.mp3");
	ALLEGRO_SAMPLE* correcto = al_load_sample("Musica/correcto.wav");
	ALLEGRO_SAMPLE* incorrecto = al_load_sample("Musica/incorrecto.wav");
	ALLEGRO_SAMPLE* salto = al_load_sample("Salto_sonido.wav");

	ALLEGRO_SAMPLE_INSTANCE* cancionInstance = al_create_sample_instance(cancion);

	al_set_sample_instance_playmode(cancionInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(cancionInstance, al_get_default_mixer());

	al_play_sample_instance(cancionInstance);

	/*al_destroy_sample(cancion);
	al_destroy_sample(btnSonido);
	al_destroy_sample_instance(cancionInstance);*/


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
	al_reserve_samples(1);
	ALLEGRO_SAMPLE* btnSonido = al_load_sample("Musica/boton.wav");

	blanco = al_map_rgb(255, 255, 255);
	naranja = al_map_rgb(239, 186, 36);
	negro = al_map_rgb(0, 0, 0);
	rojo = al_map_rgb(255, 43, 43);
	azul = al_map_rgb(53, 43, 255);

	bool end_program = false;
	bool tutorial = false;

	int x = -1, y = -1;
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
					al_play_sample(btnSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					al_draw_bitmap(menu_start, 0, 0, 0);
					tutorial = true;
					jugar(ventana);
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
						al_play_sample(btnSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
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
				if (evento.mouse.button & 1)
				{
					jugar(ventana);
				}
			}
		}

		al_flip_display();
	}
	al_destroy_sample(btnSonido);
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
		while (true)
		{
			ALLEGRO_EVENT evento;
			al_wait_for_event(queue, &evento);
			al_clear_to_color(negro);
			al_flip_display();
			usarTeclado(ventana);
		}
}

void usarTeclado(ALLEGRO_DISPLAY* ventana)
{

	//para que se ejecute a la misma velocidad en cualquier computadora 
	ALLEGRO_TIMER* tiempo = al_create_timer(1.0 / 5);
	ALLEGRO_EVENT_QUEUE* evento_queue = al_create_event_queue();
	ALLEGRO_BITMAP* caminando[8];
	ALLEGRO_BITMAP* fondo[2];
	ALLEGRO_BITMAP* vida[8];
	ALLEGRO_KEYBOARD_STATE keyState;

	ALLEGRO_BITMAP* perdiste[5] = { al_load_bitmap("fondo/perdiste/estandar.png"),
										al_load_bitmap("fondo/perdiste/si/1.png"),
										al_load_bitmap("fondo/perdiste/si/2.png"),
										al_load_bitmap("fondo/perdiste/no/1.png"),
										al_load_bitmap("fondo/perdiste/no/2.png") };
	ALLEGRO_BITMAP* ganaste[3] = { al_load_bitmap("fondo/ganaste/ok_1.png"),
									al_load_bitmap("fondo/ganaste/ok_1_5.png"),
									al_load_bitmap("fondo/ganaste/ok_2.png") };
	ALLEGRO_BITMAP* continuar[5] = { al_load_bitmap("fondo/continuar/estandar.png"),
									al_load_bitmap("fondo/continuar/si/1.png"),
									al_load_bitmap("fondo/continuar/si/2.png"),
									al_load_bitmap("fondo/continuar/no/1.png"),
									al_load_bitmap("fondo/continuar/no/2.png") };
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(3);
	ALLEGRO_SAMPLE* salto = al_load_sample("Musica/Salto_sonido.wav");
	ALLEGRO_SAMPLE* correctoSonido = al_load_sample("Musica/correcto.wav");
	ALLEGRO_SAMPLE* incorrectoSonido = al_load_sample("Musica/incorrecto.wav");

	
	al_register_event_source(evento_queue, al_get_keyboard_event_source());
	al_register_event_source(evento_queue, al_get_timer_event_source(tiempo));
	al_get_keyboard_state(&keyState);

	bool terminado = false, dibujo = true, activo = false;
	int x = 60, y = 460;
	int xfondo = 60;
	int velMovimiento = 200;
	int i, j, l, indice, resultado, avanceJugador, puntos = 0, numFondo = 1;
	indice = 0, j = 0, avanceJugador = 1;
	bool correcto = true;
	float camaraPos[2] = { 0,0 };
	int puntuacion,numJugador=0; 
	int n1, n2;
	int rf = 5;
	n1 = 1;
	n2 = rand() % rf + 1;
	resultado = n1 + n2;
	int puntajes[5500]; 
	impNum(n1, n2, Golden_Age_Shad);
	
	//no declarar variables despues del tiempo
	al_start_timer(tiempo); 

	//cargar imagenes
	for (i = 0; i < 8; i++)
	{
		std::stringstream str;
		str << "sprites/" << i + 1 << ".png";
		caminando[i] = al_load_bitmap(str.str().c_str());
	}
	for (j = 0; j < 2; j++)
	{
		std::stringstream str;
		str << "fondo/" << j + 1 << ".png";
		fondo[j] = al_load_bitmap(str.str().c_str());
	}
	for (l = 0; l <= 7; l++)
	{
		std::stringstream str;
		str << "lifes/" << l << ".png";
		vida[l] = al_load_bitmap(str.str().c_str());
	}
	j = 0;
	l = 7;

	while (!terminado)
	{
		ALLEGRO_EVENT eventos;
		al_wait_for_event(evento_queue, &eventos);
		if (eventos.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (eventos.keyboard.keycode)
			{
				case ALLEGRO_KEY_RIGHT:
					if (avanceJugador < 50)
					{
							al_play_sample(salto, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
							x += velMovimiento;
							avanceJugador++;
							xfondo += velMovimiento;

						if (x >= 1060)
						{
							numFondo++;
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
						al_play_sample(salto, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						avanceJugador--;
						x -= velMovimiento;
						xfondo -= velMovimiento;

						if (x < 60)
						{
							numFondo--;
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
						al_play_sample(incorrectoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						x = 60;
						numFondo = 1;
						xfondo = 60;
						avanceJugador = 1;
						n1 = 1;
						n2 = rand() % rf + 1;
						l--;
						if (l == 0)
						{

							terminado = true; 
						}
					}
					else
					{
						al_play_sample(correctoSonido, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						n1 = resultado;
						avanceJugador = resultado;
						if (n1 == 50)
						{
							//gameOver = true;
							dibujo = false;
							printf("GANASTE");

						}
						else
						{
							n2 = rand() % rf + 1;
							while (n1 + n2 > 50)
							{
								//printf("HOLA");
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
			al_draw_bitmap(fondo[j], 0, 0, 0);
			impNum(n1, n2, Golden_Age_Shad);
			mensajes(avanceJugador, puntos);
			al_draw_bitmap(caminando[indice], x, y, NULL);
			al_draw_bitmap(vida[l], 500, 74, NULL);
			numCajas(numFondo,Golden_Age_Shad_pequenio);
			al_flip_display();

		}
	}
	for (i = 0; i < 8; i++)
	{
		al_destroy_bitmap(caminando[i]);
	}
	for (l = 0; l <= 7; l++)
	{
		al_destroy_bitmap(vida[l]);
	}
	al_destroy_event_queue(evento_queue);
	al_destroy_bitmap(fondo[j]);
	al_destroy_display(ventana);
	al_destroy_sample(salto);
	al_destroy_sample(correctoSonido);
	al_destroy_sample(incorrectoSonido);
	al_destroy_timer(tiempo);

}



