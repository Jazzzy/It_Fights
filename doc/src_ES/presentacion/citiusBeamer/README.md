# Plantilla para a realización de presentacións

Baseada na plantilla realizada por Diego Rodríguez Martínez na
súa versión 2.1, a última dispoñible na wiki do CITIUS en abril
de 2015.

Se atopas algún problema ou desexas mellorar algo, podes facer
un fork do repositorio e enviar pull requests.

## Vista previa

![Screenshot 1](https://gitlab.citius.usc.es/citius/beamer-presentation/raw/master/preview1.png)

![Screenshot 2](https://gitlab.citius.usc.es/citius/beamer-presentation/raw/master/preview2.png)

![Screenshot 3](https://gitlab.citius.usc.es/citius/beamer-presentation/raw/master/preview3.png)

## Modo de emprego

O documento principal é `beamer_CiTIUS.tex`.

A plantilla contén actualmente as propias instruccións para usala.
Inclúese o arquivo `README.pdf` con exemplos dunha versión antiga.

A compilación da plantilla está verficada nos sistemas TeXLive das Ubuntu
xestionados pola Unidade de Xestión de Infraestruturas (TeXLive 2008 e
2012).

Para a correcta compilación da presentación con MikTeX (Windows) é
preciso actualizar a instalación. No caso de que aparezan problemas
relacionados coas fontes, recoméndase executar as seguintes accións
na liña de comandos (`cmd`):

```cd C:\Archivos de programa\MikTeX\miktex\bin
initexmf --mkmaps
initexmf --update-fndb```

### Activar modo 4:3

Por defecto, a plantilla utiliza a relación de aspecto 16:9. Se queres
activar a relación tradicional 4:3, debes seguir as instruccións que
están nun comentario ao principio do arquivo `beamer_CiTIUS.tex`.


