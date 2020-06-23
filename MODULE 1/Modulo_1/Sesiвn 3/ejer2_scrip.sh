inicio=0

while [ $inicio -lt $1 ]
do
	inicio=`expr $inicio + 1`
done

echo "Valor $inicio"

exit

