/*
 * Escriba una rutina (para ambiente gráfico Windows o Linux) que muestre la siguiente figura:
 * Un triangulo relleno en azul con las coordenadas (esquinaInferiorIZquierda, centroVentana, esquinaInferiorDerecha)
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
                ctx->scale(width, height); //Escala para trabajar con ratio y no con pixels. (1 es 100%)
                
                //FONDO
                ctx->rectangle(0.0, 0.0, 1.0, 1.0);
                ctx->set_source_rgb(1.0, 1.0, 1.0);
                ctx->fill();

                //Figura pedida
                ctx->move_to(0.0, 1.0);
                ctx->rel_line_to(0.5, -0.5);
                ctx->rel_line_to(0.5, 0.5);
                ctx->rel_line_to(-1.0, 0.0);
                ctx->set_source_rgb(0.0, 0.0, 1.0);
                ctx->fill();
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
