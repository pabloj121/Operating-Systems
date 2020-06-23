//ED clase 10/11/17

Arbol : grafo acíclico donde cada nodo tiene grado de entrada 1(excepto
el nodo y grado de salida 0 o mayor que 0)

Arbol n-ario: todos los nodos tienen 0 o mas hijos
	Arbol 2-ario -> 0 ó 2 hijos
	Arbol binario -> 0 a 2 hijos

Camino en un arbol: una sucesion de nodos n1,n2,...,nk
donde el nodo i+h es padre del nodo i+1. La longitud del
camino es igual al nº de nodos en el camino -1

Ancesto: ni es ancestro de nj si existe un camino desde ni
a nj.

"ni se coloca antes en el camino que nj"
"nj es un descendiente de ni"

EJEMPLO:
	ruta : /home/rosa/alumnos/fi
		"home es un ancestro de f1"
		"f1 es un descendiente de home"

Subarbol: Sea ni y todos los descendientes de ni

Altura de un nodo ni: se define como el camino mas largo entre el 
nodo ni y una hoja. Altura del arbol se corresponde con la altura
del nodo raiz.

Profundidad de un nodo ni: la longitud del camino que existe entre
un nodo ni y la raíz. (concepto totalmente contrario a la altura)
ahora partimos de las hojas en vez de la raiz.
"Los hijos del primer padre van a tener profundidad 1"

Niveles: Si el arbol tiene altura h. El arbol tiene h+1 nivel que va 
desde 0 hasta h. El nivel 0 se compone de la raiz, nivel 1 son los
descendientes de la raiz.

Grado de un nodo: Se refiere al nº de hijos que tiene.

Grado del arbol: al máximo de los grados de los nodos del arbol

- ARBOL BINARIO homogeneo = 2-ario = 0 ó 2 hijos ( no cabe la posibilidad de que tenga un hijo)
- ARBOL BINARIO completo = tienen todos los niveles completos excepto el último nivel en cuyo
  caso los huecos quedan a la derecha.
  	si tenemos n nodos, ¿cuantos niveles tienen? log2(n)

RECORRIDO PARA ARBOLES
	--En profundidad:
		- En preorden
			se da la etiqueta de la raiz y se llama de manera recursiva.
			raiz, Preorden(T1),Preorden(T2),...,Preorden(Tn)
		- En inorden
			Llama recursivamente para listar el hijo mas a la izquierda, luego la raiz y luego los hijos
			Inorden(T1), raíz, Inorden(T2),Inorden(T3),...,Inorden(Tn)
		- En postorden 
			Postorden(T1), Postorden(T2),..., Postorden(Tn), raíz	("empiezas de abajo a arriba")

	-- En anchura:
		- Por niveles
