Se realiza un análisis empírico de los algoritmos Búsqueda Binaria y MergeSort, con el objetivo de comparar sus tiempos de ejecución experimentales con sus complejidades teóricas: O(log₂(n)) para Búsqueda Binaria y O(n·log₂(n)) para MergeSort.
Para realizar el benchmark se generan arreglos con valores aleatorios y distintos tamaños de entrada. Para cada tamaño se ejecutan ambos algoritmos múltiples veces y se mide su tiempo de ejecución en nanosegundos.
Las repeticiones permiten obtener tiempos promedio y reducir el efecto de las variaciones propias de una medición individual.
Además de los tiempos experimentales, se calculan los valores correspondientes a las funciones teóricas.
Los resultados obtenidos se almacenan en el archivo "resultados.csv" y se utilizan para generar gráficas comparativas entre el comportamiento experimental y el crecimiento esperado según el análisis teórico.
Las gráficas se incorporan en el archivo "graficas.xlsx".
La idea de este análisis es ver si conforme aumenta el tamaño de entrada n, el crecimiento medido presenta un comportamiento consistente con las complejidades esperadas de cada algoritmo.


## Búsqueda Binaria - O(log₂(n)): ![Gráfica Búsqueda Binaria](imagenes/busqueda-binaria.png)


## MergeSort - O(n·log₂(n)): ![Gráfica MergeSort](imagenes/mergesort.png)
