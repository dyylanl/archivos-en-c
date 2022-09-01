//Escriba una rutina (para ambiente gráfico Windows o Linux) que muestre la figura.

#include <gtkmm.h>
class Dibujo : public Gtk::DrawingArea {
    private:
        bool on_expose_event(GdkEventExpose* ev) {
            Glib::RefPtr< Gdk::Window > window = get_window();
            if (window) {
                Cairo::RefPtr< Cairo::Context > ctx = window->create_cairo_context();
                Gtk::Allocation alloc = get_allocation();
                const int height = alloc.get_height();
                const int width = alloc.get_width();
                //Escala para trabajar con ratio y no con pixels. (1 es 100%)
                ctx->scale(width, height);
                
                //FONDO BLANCO en TODA LA VENTANA
                ctx->rectangle(0.0 /*izq*/, 0.0 /*arriba*/, 1.0 /*ancho*/, 1.0 /*alto*/);
                ctx->set_source_rgb(1.0 /*red*/, 1.0 /*green*/, 1.0 /*blue*/);
                ctx->fill(); //Pinto el rectangulo de blanco que ocupa toda la ventana

                (x=0 izquierda, y=0 arriba) ; (x=1 derecha, y=1 abajo)
 				ctx->rectangle(x_origen, y_origen, width, height);
                ctx->arc(xcenter, ycenter, radio, 0, 2*M_PI);
                
                ctx->move_to(x, y); //Desplaza el cursor a la pos (x,y)
                ctx->rel_move_to(xRel, yRel); //Desplaza el cursor de forma relativa (x,y)
                ctx->line_to(x, y); //Linea desde posCursor a (x,y)
                ctx->rel_line_to(xRel, yRel); //Linea desde posCursor a posRelativa(x,y)
                ctx->close_path(); //Cierra el path para tener una figura cerrada pintable.
                
                ctx->set_line_width(grosor de linea ej 0.005);
                ctx->set_source_rgb(red[0:1], green[0:1], blue[0:1]); //Setea color paleta
                ctx->fill_preserve(); //Pinta relleno manteniendo el path del cursor
                ctx->fill(); //Pinta relleno sin mantener el path del cursor
                ctx->stroke_preserve(); //Pinta contorno manteniendo el path del cursor
                ctx->stroke(); //Pinta contorno sin mantener el path del cursor
                
                ctx->save(); //Guarda las propiedades del contexto (paleta etc.)
                ctx->restore(); //Restaura las propiedades del contexto (paleta etc.)
            }
            return true;            
        }
};
int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);  
    Dibujo unDibujo;
    Gtk::Window unaVentana;
    unaVentana.add(unDibujo);
    unaVentana.show_all();
    Gtk::Main::run(unaVentana);
    return 0;
}   
