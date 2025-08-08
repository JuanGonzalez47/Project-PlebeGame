🎖️ World War II Platformer - C++ Project
Un juego de plataformas 2D ambientado en la Segunda Guerra Mundial, desarrollado en C++ como proyecto final para el curso "Informática II". El proyecto se centró en la aplicación de conocimientos de programación, la implementación de físicas del mundo real y el desarrollo de un flujo de trabajo colaborativo utilizando Git y GitHub.

🎬 Tráiler del Juego
Realizamos un tráiler completo del juego que muestra las mecánicas, niveles y la jugabilidad general. ¡Haz clic en la imagen para verlo en YouTube!
![alt text](https://img.youtube.com/vi/[ID_DEL_VIDEO](https://www.youtube.com/watch?v=6q0XGf-h7oo)/0.jpg)

🎯 Contexto y Objetivos del Proyecto
Este proyecto fue la culminación del curso Informática II, diseñado para integrar múltiples áreas de aprendizaje en una sola aplicación funcional. Los objetivos principales fueron:

- Aplicar conocimientos de C++: Construir una aplicación robusta utilizando Programación Orientada a Objetos.
- Implementar Físicas en el Juego: Ir más allá de los movimientos simples e integrar físicas realistas para crear una experiencia de juego más dinámica e interesante.
- Desarrollar un Flujo de Trabajo Colaborativo: Aprender a trabajar en equipo en una base de código compartida, utilizando Git para el control de versiones y GitHub para la colaboración, manejo de ramas (branches) y fusión de cambios (merges).
- 
🚀 Físicas y Mecánicas Implementadas
Una parte fundamental del desarrollo fue la integración de principios de física para controlar los movimientos clave en el juego:

- Movimiento Parabólico: Se implementó para gobernar las trayectorias de dos elementos esenciales:
    - Salto del Jugador: El salto sigue un arco parabólico natural en lugar de un simple movimiento lineal hacia arriba y abajo.
    - Lanzamiento de Granadas: Las granadas lanzadas por el jugador siguen una trayectoria balística precisa, permitiendo apuntar estratégicamente sobre   obstáculos y enemigos.
    - Movimiento Armónico Simple (MAS): En el segundo nivel del juego, se utilizó el MAS para el movimiento de los helicopteros, además de unos misiles teledirigios con una salida de proyectil con un movimiento circular y una logica de seguimiento de jugador a traves de restas vectoriales.
       
🤝 Trabajo en Equipo y División de Roles
Este fue un proyecto desarrollado en equipo por dos personas. La planificación, incluyendo el diseño del diagrama de clases, se realizó de forma conjunta para asegurar una base sólida y cohesiva. Las responsabilidades de desarrollo se dividieron de la siguiente manera:

- Juan Pablo González Blandón (Mi Rol):
Desarrollo de las pantallas de la interfaz de usuario (Pantalla de carga, menú de inicio, pantalla de final de juego).
Implementación completa de la lógica y diseño del Nivel 2.

- Juan Jose Balvin Torres:
Implementación completa del Nivel 1.
Despliegue final del proyecto, generando el archivo ejecutable .exe y sus dependencias.

🛠️ Stack Tecnológico
Lenguaje: C++
Framework: Qt (versión 4.7.0).
Se utilizó principalmente el Graphics View Framework (QGraphicsScene, QGraphicsView, QGraphicsPixmapItem) para la renderización y gestión de la escena 2D.
Se emplearon QTimer para el bucle del juego y la gestión de eventos temporizados, y QKeyEvent para las entradas del usuario.
IDE: Qt Creator 4.7.0
Control de Versiones: Git y GitHub

🎮 Descarga y Juega
¡Puedes descargar y jugar la versión final del juego! El archivo .exe para Windows está empaquetado junto con todas sus dependencias.
👉 Descarga la última versión desde la página de Releases: https://github.com/JuanGonzalez47/Project-PlebeGame/releases/tag/v1.0.0

📄 Licencia
Este proyecto está bajo la Licencia MIT. Consulta el archivo LICENSE para más detalles.
