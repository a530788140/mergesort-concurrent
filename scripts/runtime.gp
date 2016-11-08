reset
set ylabel 'time(sec)'
set style fill solid
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][0:0.01]'output.txt' using 2:xtic(1) with histogram title 'thread-num', \
'' using ($0+0.10):($2+0.0002):2 with labels title ' ', 
