Datos utilizados para el taller de hashing

### Datasets:

* gauss(_.txt_): distribución gaussiana de claves N(100000, 5000)
* uniforme(_.txt_): distribución uniforme de claves U(1, 6378277)
* libretas(_.txt_): listado de libretas con el número unido al año y con
    padding de 3 y 2 dígitos, respectivamente. Los números estan distribuidos
    uniformemente U(1, 7000), los años siguen una distribución de pareto 
    (15 - P(6)). 


### Graficos:

`uniforme.pdf`, `gauss.pdf` y `libretas.pdf` muestra la distribución como está.
libretas_años.pdf muestra la distribución de los años en las libretas y 
librertas_nums.pdf muestra la distribución de los números.


### Scripts:

* `generar_datos.py`: genera los datos para los tres tipos de distribuciones
* `graficar_datos.py`: genera los gráficos nombrados anteriormente a partir de
    los txt esperados
* `Makefile`: magia
