/*
 * Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje la siguiente imagen en su área de dibujo.
 * Un triangulo relleno en negro con las coordenadas (esquinaInferiorIZquierda, esquinaSuperiorDerecha, esquinaInferiorDerecha)
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
                ctx->rectangle(0.0 /*izquierda*/, 0.0 /*arriba*/, 1.0 /*anchoVentana*/, 1.0 /*altVentana*/); //TODA LA VENTANA
                ctx->set_source_rgb(1.0 /*red*/, 1.0 /*green*/, 1.0 /*blue*/); //BLANCO (1,1,1) ; NEGRO (0,0,0)        
                ctx->fill(); //RELLENAMOS LA VENTANA
                
                //TRIANGULO PEDIDO
                ctx->move_to(0.0, 1.0);
                ctx->rel_line_to(1.0, 0.0);
                ctx->rel_line_to(0.0, -1.0);
                ctx->rel_line_to(-1.0, 1.0);
                ctx->set_source_rgb(0.0, 0.0, 0.0);  //set_source_rgb(red, green, blue)
                ctx->fill_preserve(); //Pinta relleno
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
