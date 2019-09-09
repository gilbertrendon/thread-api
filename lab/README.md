# Thread API # 

En esta sección escribiremos algunos programas multi-hilo y usaremos una herramienta específica llamada ```helgrind``` para encontrar problemas en estos programas. 

## Questions ##

1. Primero codifique ```main-race.c```. Examine el código de manera que usted pueda ver (ojalá de manera obvia) un data race en el código. Ahora ejecute ```helgrind``` (al teclear ```valgrind --tool=helgrind main-race```) y vea como este programa reporta los *data races*. ¿Se muestran las líneas de código involucradas?, ¿Qué otra información entrega este programa?

Para poder compilar el código se debió incluir pthread con: gcc -pthread -o main-race main-race.c
Si se ejecuta el código normalmente: muestra el número de bytes que tiene almacenados la variable en dicha posición. También se muestran los locks que se adquieren en el código.
Al quitar los locks puede presentarse condiciones de carrera como similar a como se apreciará más adelante en el punto #6.

2. ¿Qué ocurre cuando usted elimina una de las líneas que generan problemas en el código? Ahora agrege un lock alrededor de las actualizaciones de la variable compartida, y entonces alrededor de ambas. ¿Qué reporta ```helgrind``` en cada uno de estos casos?

Al eliminar la línea balance++; de la función worker con valgrind no muestra nada, los hilos unicamente se inicializan y retornan NULL. Al agregar los lock, ocurre lo mismo, no se muestran errores, aunque dice que se suprimieron 7 posibles errores.

3. Ahora observe ```main-deadlock.c```. Examine el código. Este código tiene un problema conocido como deadlock. ¿Puede ver que problema podrá este tener?

Hay un interbloqueo: El primer hilo va a querer adquirir el lock m1, si ocurre un cambio de contexto en este momento, el segundo hilo se ejecuta y va a adquirir el lock m2 y va a querer adquirir m1, pero ya el hilo 1 lo ha adquirido y no lo va a soltar hasta que el segundo hilo lo suelte.

![enlace](https://raw.githubusercontent.com/gilbertrendon/thread-api/master/lab/Pantallazos/FiguraP3.png)

4. Ahora ejecute ```helgrind``` en este código. ¿Qué reporta helgrind?
Como se pudo observar en la anterior imagen: Reporta que en el hilo 3 hay una violación en el orden de adquisición de los locks. Muestra la adquisición de los locks por cada una de los hilos. Muestra que existe un error pero al parecer el compilador automáticamente corrige algunos errores en este caso 9.

5. Ahora ejecute ```helgrind``` en ```main-deadlock-global.c```. Examine el código. ¿Tiene este el mismo problema que ```main-deadlock.c```? ¿Muestra ```helgrind``` el mismo reporte de error? ¿Qué dice esto a cerca de herramientas como ```helgrind```?
 Sí, se puede verificar erróneamente el orden de adquisición de los locks y decir que se adquirió sin ser así necesariamente.
6. Ahora observe ```main-signal.c```. Este código usa una variable (```done```) para señalar que el hijo esta hecho y que el padre puede continuar. ¿Por qué este códido es ineficiente? (En que termina el padre dedicando su tiempo, si el hijo toma una gran cantidad de tiempo en completarse).
R/En realidad aquí hay un claro uso de variable(s) de condición y aparte de que hay un inconveniente con el include "mythreads.h", lo único que puede hacer el padre antes de que termine el hijo es esperar y mientras más espere habrá más uso de cpu algo que no es muy recomendable y en la siguiente imagen podemos ver que hay posibles condiciones de carrera para lo que se podrían usar locks:

![enlace](https://raw.githubusercontent.com/gilbertrendon/thread-api/master/lab/Pantallazos/FiguraP6.png)

7. Ahora ejecute ```helgrind``` para este programa. ¿Qué reporta helgrind?, ¿Es correcto el código?

Al ejecutar helgrind se puede ver mas detalladamente como se apreció en la figura del punto anterior, los fallos o posibles fallos son:
Posible data race entre los dos hilos, admás de que se debe tener en cuenta de los que se suprimen por el compilador.

8. Ahora observe una versión levemente modificada del código, la cual es encontrada en ```main-signal-cv.c```. Esta versión usa una variable de condición para señalizar (y asociar un lock). ¿Por qué este código es mejor que la versión previa? ¿Es la corrección, o el desempeño, o ambos?
9. Ejecute de nuevo ```helgrind``` en ```main-signal-cv``` ¿Reporta algunos errores?

**Nota**: Se adjuntan los códigos para facilitar en análisis.
