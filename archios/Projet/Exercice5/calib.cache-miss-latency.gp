# Calibrator v0.9e
# (by Stefan.Manegold@cwi.nl, http://www.cwi.nl/~manegold/)
 set term postscript portrait enhanced
 set output 'calib.cache-miss-latency.ps'
#set term gif transparent interlace small size 500, 707 # xFFFFFF x333333 x333333 x0055FF x005522 x660000 xFF0000 x00FF00 x0000FF
#set output 'calib.cache-miss-latency.gif'
set data style linespoints
set key below
set title 'calib.cache-miss-latency'
set xlabel 'memory range [bytes]'
set x2label ''
set ylabel 'nanosecs per iteration'
set y2label 'cycles per iteration'
set logscale x 2
set logscale x2 2
set logscale y 10
set logscale y2 10
set format x '%1.0f'
set format x2 '%1.0f'
set format y '%1.0f'
set format y2 ''
set xrange[0.750000:40960.000000]
#set x2range[0.750000:40960.000000]
set yrange[1.000000:1000.000000]
#set y2range[1.000000:1000.000000]
set grid x2tics
set xtics mirror ('1k' 1, '' 2, '4k' 4, '' 8, '16k' 16, '' 32, '64k' 64, '' 128, '256k' 256, '' 512, '1M' 1024, '' 2048, '4M' 4096, '' 8192, '16M' 16384, '' 32768)
set x2tics mirror)
set y2tics ('(0)' 15.990000, '0.001' 1, '0.01' 10, '0.1' 100, '1' 1000)
set label 1 '(0)  ' at 0.750000,0.000000 right
set arrow 1 from 0.750000,0.000000 to 40960.000000,0.000000 nohead lt 0
 set label 2 '^{ Calibrator v0.9e (Stefan.Manegold\@cwi.nl, www.cwi.nl/~manegold) }' at graph 0.5,graph 0.02 center
#set label 2    'Calibrator v0.9e (Stefan.Manegold@cwi.nl, www.cwi.nl/~manegold)'    at graph 0.5,graph 0.03 center
plot \
0.1 title 'stride:' with points pt 0 ps 0 , \
'calib.cache-miss-latency.data' using 1:($7-77.140000) title '128' with linespoints lt 1 pt 3 , \
'calib.cache-miss-latency.data' using 1:($13-77.140000) title '64' with linespoints lt 2 pt 4 , \
'calib.cache-miss-latency.data' using 1:($19-77.140000) title '32' with linespoints lt 3 pt 5 , \
'calib.cache-miss-latency.data' using 1:($25-77.140000) title '16' with linespoints lt 4 pt 6 , \
'calib.cache-miss-latency.data' using 1:($31-77.140000) title '8' with linespoints lt 5 pt 7 , \
'calib.cache-miss-latency.data' using 1:($37-77.140000) title '4' with linespoints lt 6 pt 8
set nolabel
set noarrow
