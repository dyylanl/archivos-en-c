/* Para compilar:
 * gcc bandera_inglesa.c -o bandera_inglesa `pkg-config --cflags --libs gtk+-3.0`
*/

#include <gtk/gtk.h>
#include <math.h>

gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    int height = gtk_widget_get_allocated_height(widget);
    int width = gtk_widget_get_allocated_width(widget);

    cairo_surface_t *surface = gdk_window_create_similar_surface(
                    gtk_widget_get_window(widget),
                    CAIRO_CONTENT_COLOR, width, height);
    cairo_scale(cr, width, height);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_move_to(cr, 0.0, 0.0);
    cairo_rel_line_to(cr, 1.0, 0.0);
    cairo_rel_line_to (cr, 0.0, 1.0);
    cairo_rel_line_to (cr, -1.0, 0.0);
    cairo_rel_line_to (cr, 0.0, -1.0);
    cairo_fill(cr);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    cairo_set_line_width(cr, 0.005);
    cairo_move_to(cr, 0.0, 0.0);
    cairo_rel_line_to(cr, 1.0, 1.0);
    cairo_move_to(cr, 1.0, 0.0);
    cairo_rel_line_to (cr, -1.0, 1.0);

    cairo_stroke(cr);
    cairo_surface_destroy(surface);

    return FALSE;
}

//Callback para iniciar la aplicación
static void activate(GtkApplication* app, gpointer data)
{
  //Crea una ventana de aplicación
  GtkWidget *window = gtk_application_window_new(app);
  //Define su título y tamaño
  gtk_window_set_title(GTK_WINDOW(window), "Ejemplo");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
  //Crea un área para contener al botón
  GtkWidget *box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
  gtk_container_add(GTK_CONTAINER(window), box);

  //Crea el área de dibujo y registra la señal para llenarla al exponerse
  GtkWidget *drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, 100, 100);
  g_signal_connect(drawing_area, "draw", G_CALLBACK(draw), NULL);
  gtk_container_add(GTK_CONTAINER(box), drawing_area);

  //Crea al botón y registra la señal de clicked para cerrar la aplicación
  GtkWidget *button = gtk_button_new_with_label("Cerrar");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add(GTK_CONTAINER(box), button);

  //Muestra todos sus componentes
  gtk_widget_show_all(window);
}

int main (int argc, char **argv)
{
  //Crea la aplicación sin nombre ni opciones particulares
  GtkApplication *app = gtk_application_new (NULL, G_APPLICATION_FLAGS_NONE);
  //Define el método de ejecución de la aplicación con el callback
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  //Ejecuta la aplicación y bloquea
  int status = g_application_run (G_APPLICATION (app), argc, argv);
  //Libera el objeto app y todos sus recursos
  g_object_unref (app);

  return status;
}