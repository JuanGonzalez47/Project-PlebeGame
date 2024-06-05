#include "sprite.h"

sprite::sprite(QString name_image, int _sprite_x, int _sprite_y, int _sprite_width, int _sprite_height,qreal _x,qreal _y) {
    spriteSheet.load(name_image);

    //posicion inicial en la escena
    x=_x;
    y=_y;

    // Posición inicial en el sprite
    sprite_x = _sprite_x;
    sprite_y = _sprite_y;
    // Dimensiones de cada imagen
    sprite_width = _sprite_width;
    sprite_height = _sprite_height;

    sprit = spriteSheet.copy(sprite_x, sprite_y, sprite_width, sprite_height);
    setPixmap(sprit);
}

sprite::sprite()
{
    //carga de todas las imagenes que se van a usar para el nivel 2

    fondo_nivel_2.load(":/nivel-2/Imagenes nivel 2/Fondo.gif");
    setPixmap(fondo_nivel_2);
    pantalla_carga_nivel_2.load(":/nivel-2/Imagenes nivel 2/pantalla-carga.png");
    setPixmap(pantalla_carga_nivel_2);
    explosion_1.load(":/nivel-2/Imagenes nivel 2/explosion.png");
    setPixmap(explosion_1);
    explosion_2.load(":/nivel-2/Imagenes nivel 2/explosion_desvanecida.png");
    setPixmap(explosion_2);
    game_over.load(":/nivel-2/Imagenes nivel 2/game_over.jpg");
    setPixmap(game_over);
    time.load(":/nivel-2/Imagenes nivel 2/tiempo.png");
    setPixmap(time);
    helicoptero_amigo.load(":/nivel-2/Imagenes nivel 2/helicoptero-amigo-Photoroom.png-Photoroom.png");
    setPixmap(helicoptero_amigo);
    helicoptero_enemigo.load(":/nivel-2/Imagenes nivel 2/helicoptero-enemigo.png");
    setPixmap(helicoptero_enemigo);
    numeros.load(":/nivel-2/Imagenes nivel 2/numeros.png");
    setPixmap(numeros);
    llantas.load(":/nivel-2/Imagenes nivel 2/llanta.png");
    setPixmap(llantas);
    misiles.load(":/nivel-2/Imagenes nivel 2/misiles.png");
    setPixmap(misiles);
    personaje_principal_mov_l.load(":/nivel-2/Imagenes nivel 2/mov_prin_mirror.png");
    setPixmap(personaje_principal_mov_l);
    personaje_principal_mov_r.load(":/nivel-2/Imagenes nivel 2/mov_prin.png");
    setPixmap(personaje_principal_mov_r);
    sangre.load(":/nivel-2/Imagenes nivel 2/Sangre.png");
    setPixmap(sangre);
    telefono.load(":/nivel-2/Imagenes nivel 2/telefono.png");
    setPixmap(telefono);
    mensaje.load(":/nivel-2/Imagenes nivel 2/Texto.png");
    setPixmap(mensaje);
    salto_D.load(":/nivel-2/Imagenes nivel 2/salto-derecha.png");
    setPixmap(salto_D);
    salto_I.load(":/nivel-2/Imagenes nivel 2/salto-izquierda.png");
    setPixmap(salto_I);
    muerte.load(":/nivel-2/Imagenes nivel 2/muerte.png");
    setPixmap(muerte);
    firme.load(":/nivel-2/Imagenes nivel 2/firme.png");
    setPixmap(firme);
    punto.load(":/nivel-2/Imagenes nivel 2/puntos.png");
    setPixmap(punto);
    corazon.load(":/nivel-2/Imagenes nivel 2/corazon.png");
    setPixmap(corazon);
    muerte_mirror.load(":/nivel-2/Imagenes nivel 2/muerte-mirror.png");
    setPixmap(muerte_mirror);
    helicoptero_enemigo_1.load(":/nivel-2/Imagenes nivel 2/helicoptero-enemigo-mirror.png");
    setPixmap(helicoptero_enemigo_1);
    misil_1.load(":/nivel-2/Imagenes nivel 2/misiles-amigos.png");
    setPixmap(misil_1);
    misil_2.load(":/nivel-2/Imagenes nivel 2/misiles-amigos-mirror.png");
    setPixmap(misil_2);

}

void sprite::moveImage(int dx, int dy) {
    // Mover imagen por la escena
    x += dx;
    y += dy;
    setPos(x, y);
}

void sprite::setSprite() {

    sprite_x = sprite_width * cont; // Rotar por cada imagen
    QPixmap sprite = spriteSheet.copy(sprite_x, sprite_y, sprite_width, sprite_height);
    setPixmap(sprite);
    cont++;
    if (cont == n_image) {
        cont = 0;
    }
}

QPixmap sprite::SetSprite(unsigned int tipo_imagen)
{
    QPixmap imagen_seleccionada;

    switch(tipo_imagen){
    case 0: imagen_seleccionada = fondo_nivel_2.copy(0,0,fondo_nivel_2.width(),fondo_nivel_2.height());
        return imagen_seleccionada;
        break;

    case 1: imagen_seleccionada = pantalla_carga_nivel_2.copy(0,0,pantalla_carga_nivel_2.width(),pantalla_carga_nivel_2.height());
        return imagen_seleccionada;
        break;

    case 5: imagen_seleccionada = game_over.copy(0,0,game_over.width(),game_over.height());
        return imagen_seleccionada;
        break;

    case 6: imagen_seleccionada = time.copy(0,0,time.width(),time.height());
        return imagen_seleccionada;
        break;

    case 10: imagen_seleccionada = llantas.copy(0,0,llantas.width(),llantas.height());
        return imagen_seleccionada;
        break;

    case 15: imagen_seleccionada = telefono.copy(0,0,telefono.width(),telefono.height());
        return imagen_seleccionada;
        break;
    case 16: imagen_seleccionada = mensaje.copy(0,0,mensaje.width(), mensaje.height());
        return imagen_seleccionada;
        break;
    case 17: imagen_seleccionada = punto.copy(0,0,punto.width(), punto.height());
        return imagen_seleccionada;
        break;
    case 18: imagen_seleccionada = corazon.copy(0,0,corazon.width(), corazon.height());
        return imagen_seleccionada;
        break;
    }
}

QPixmap sprite::set_sprite_for_animation(unsigned int pos_x,unsigned int pos_y, unsigned int value, unsigned int width, unsigned int height)
{
    //se encargara de cortar cada uno de los sprites de una imagen en especifico para proceder a hacer la animacion
    switch(value){
        //animacion para el personaje
        case 0: copy = personaje_principal_mov_r.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 1: copy = personaje_principal_mov_l.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 2: copy = salto_D.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 3: copy = salto_I.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 4: copy = helicoptero_amigo.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 5: copy = misiles.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 6: copy = firme.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 7: copy = numeros.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 8: copy = explosion_1.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 9: copy = explosion_2.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 10: copy = muerte.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 11: copy = muerte_mirror.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 12: copy = helicoptero_enemigo.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 13: copy = helicoptero_enemigo_1.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 14: copy = misil_1.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
        case 15: copy = misil_2.copy(pos_x*width,pos_y*height,width,height);
            setPixmap(copy);
            return copy;
    }
}


void sprite::setAttributes(int _sprite_y, int _width, int n){

    // por si se trabaja con un solo sprite poder moverse en el libremente cambiando el numero de imagenes cambiar
    //el ancho de la imagen y la posicion en y donde rotara en x en cada imagen
    sprite_y=_sprite_y;
    sprite_width=_width;
    n_image=n;

}
