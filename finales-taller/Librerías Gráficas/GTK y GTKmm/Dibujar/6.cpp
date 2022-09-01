/*
 * Escriba una rutina (para ambiente gráfico Windows o Linux) que muestre la siguiente figura:
 * Un circulo arriba de un rectangulo (ambos gris). Dificil del explicar, ver resultado.
 */

#include <gtkmm.h>

class Dibujo : public Gtk::DrawingArea {
    public:
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
                ctx->rectangle(0.0 /*izquierda*/, 0.0 /*arriba*/, 1.0 /*ancho*/, 1.0 /*alto*/);
                ctx->set_source_rgb(1.0 /*red*/, 1.0 /*green*/, 1.0 /*blue*/);
                ctx->fill(); //Pinto el rectangulo de blanco que ocupa toda la ventana

                //Figura Pedida
                ctx->arc(0.5, 0.375, 0.125, 0, 2*M_PI);
                ctx->rectangle(0.1667, 0.5, 0.6667, 0.375);
                ctx->set_source_rgb(0.5, 0.5, 0.5);
                ctx->fill_preserve();
                ctx->set_line_width(0.015);
                ctx->set_source_rgb(0.0, 0.0, 0.0);
                ctx->stroke();
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
