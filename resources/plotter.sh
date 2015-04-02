# !bin/bash

# HELP
Help() {

echo "Help: ${0##*/} [-h] [ [-g tipo] [-x coluna] -y coluna[:coluna2] -f filtro -o entrada saida ]
Onde:
-h[H]          = Mostra esta tela de ajuda.
-x[X] coluna   = Coluna do arquivo a ser utilizado para o campo X
-y[Y] coluna   = Coluna do arquivo a ser utilizado para o campo Y pode ser usado mais de um separado por ':'
-f[F] filtro   = Expressão regular de filtro a ser utilizado
-g[G] tipo     = Tipo de gráfico a ser gerado (lines, boxes)
entrada        = Arquivo de entrada   
saida          = Imagem PNG de saída 

Ex.: ${0##*/} -f \"\\[LAYER\\]\" -g lines -x 1 -y 5:6 teste.log grafico.png 
     
";}

# Checando parâmetros:
[[ $BASH_ARGC ]] || { echo "Faça: '${0##*/} -h' para obter ajuda."; exit 1; }

while getopts "hHo:O:f:F:x:X:y:Y:g:G:" OPC 2>/dev/null
do
   case "$OPC" in
      [gG]) TYPE="$OPTARG" ;;
      [fF]) FILTER="$OPTARG" ;;
      [xX]) X="$OPTARG"
            [[ $X != [0-9]* ]] && echo "Parâmetro X incorreto" && Help;;
      [yY]) Y="$OPTARG";;
      [hH]) Help ; exit ;;
      *) echo "Faça: '${0##*/} -h' para obter ajuda."; exit 1 ;;
#      [eE]) EXT="$OPTARG"
#      [[ ${EXT##.*} == $EXT ]] && EXT=".$OPTARG" ;;
    esac
done



# Removendo opções para definir arquivos de entrada e saida
shift $(($OPTIND-1))
 
if [ -z "$1" ]; then
    echo "O arquivo de entrada e de saida devem ser informados." && exit 1;
fi

if [ -z "$2" ] ; then
    echo "O arquivo de saida deve ser informado." && exit 1;
fi



INPUT=$1
OUTPUT=$2    
OUTPUT_TEMP=$INPUT".dat"
      
if [ -z "$X" ]; then
    X=1    
fi

if ! [ -z "$TYPE" ] ; then
    TYPE="with $TYPE"
fi

echo "passo 1 --- " cat $INPUT | grep "$FILTER" | cut -d ' ' -f2- | sed 's/[][]//g'  | sed 's/[a-zA-Z]*://g'| sed 's/;/\t/g'

cat $INPUT | grep "$FILTER" | cut -d ' ' -f2- | sed 's/[][]//g'  | sed 's/[a-zA-Z]*://g'| sed 's/;/\t/g' > $OUTPUT_TEMP

XLABEL=`cat $INPUT | grep "$FILTER" | cut -d ' ' -f2- | sed 's/[][]//g' | cut -d ';' -f$X | cut -d ':' -f1 | head -n 1` 

echo "passo 2 --- " $XLABEL

for YIN in `echo $Y | tr ":" "\n"`
do
    YLABEL=`cat $INPUT | grep "$FILTER" | cut -d ' ' -f2- | sed 's/[][]//g' | cut -d ';' -f$YIN | cut -d ':' -f1 | head -n 1` 

echo "passo 3 --- " $XLABEL

    if ! [ -z "$PLOTCMD" ]; then
        PLOTCMD=$PLOTCMD,    
    fi

    PLOTCMD=$PLOTCMD"\"$OUTPUT_TEMP\" using $X:$YIN $TYPE title \"$YLABEL\""
    
echo "passo 4 --- " $PLOTCMD

done

PLOTCMD="plot "$PLOTCMD

echo "passo 5 --- " $PLOTCMD


gnuplot << EOF

set grid
set xtics ("1" 1,"2"  2,"4"  4,"8"  8)
set terminal png
set output '$OUTPUT'
set xlabel "$XLABEL"
$PLOTCMD

pause -1

EOF

--rm $OUTPUT_TEMP
