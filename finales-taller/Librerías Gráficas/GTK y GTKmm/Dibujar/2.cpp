/*
 * Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje la siguiente imagen en su área de dibujo.
 * (Un circulo centrado en la ventana, con diametro igual al alto de la ventana y relleno)
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
                
                //CIRCULO PEDIDO
                ctx->arc(0.5 /*centro horizontal*/, 0.5 /*centro vertical*/, 0.5 /*radio=mediaVentana*/, 0 /*0º*/, 2*M_PI /*360º*/);
                ctx->set_source_rgb(0.0, 0.0, 1.0);  //set_source_rgb(red, green, blue)
                ctx->fill_preserve(); //Pinta relleno
                
                //Agregamos contorno para probar
                ctx->set_source_rgb(1.0, 0.0, 0.0);
                ctx->set_line_width(0.02);
                ctx->stroke_preserve(); //Pinta contorno
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
