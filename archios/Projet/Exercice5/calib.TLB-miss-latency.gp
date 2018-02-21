# Calibrator v0.9e
# (by Stefan.Manegold@cwi.nl, http://www.cwi.nl/~manegold/)
 set term postscript portrait enhanced
 set output 'calib.TLB-miss-latency.ps'
#set term gif transparent interlace small size 500, 707 # xFFFFFF x333333 x333333 x0055FF x005522 x660000 xFF0000 x00FF00 x0000FF
#set output 'calib.TLB-miss-latency.gif'
set data style linespoints
set key below
set title 'calib.TLB-miss-latency'
set xlabel 'spots accessed'
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
set xrange[3.000000:1280.000000]
#set x2range[3.000000:1280.000000]
set yrange[1.000000:1000.000000]
#set y2range[1.000000:1000.000000]
set grid x2tics
set xtics mirror ('1' 1, '2' 2, '4' 4, '8' 8, '16' 16, '32' 32, '64' 64, '128' 128, '256' 256, '512' 512, '1k' 1024)
set x2tics mirror ('<L1>' 1024)
set y2tics ('(0)' 16.470000, '0.001' 1, '0.01' 10, '0.1' 100, '1' 1000)
set label 1 '(0)  ' at 3.000000,0.000000 right
set arrow 1 from 3.000000,0.000000 to 1280.000000,0.000000 nohead lt 0
 set label 2 '^{ Calibrator v0.9e (Stefan.Manegold\@cwi.nl, www.cwi.nl/~manegold) }' at graph 0.5,graph 0.02 center
#set label 2    'Calibrator v0.9e (Stefan.Manegold@cwi.nl, www.cwi.nl/~manegold)'    at graph 0.5,graph 0.03 center
plot \
0.1 title 'stride:' with points pt 0 ps 0 , \
'calib.TLB-miss-latency.data' using 1:($7-0.000000) title '32772' with linespoints lt 2 pt 4 , \
'calib.TLB-miss-latency.data' using 1:($13-0.000000) title '16388' with linespoints lt 3 pt 5 , \
'calib.TLB-miss-latency.data' using 1:($19-0.000000) title '8196' with linespoints lt 4 pt 6 , \
'calib.TLB-miss-latency.data' using 1:($25-0.000000) title '4100' with linespoints lt 5 pt 7 , \
'calib.TLB-miss-latency.data' using 1:($31-0.000000) title '2052' with linespoints lt 6 pt 8 , \
'calib.TLB-miss-latency.data' using 1:($37-0.000000) title '1028' with linespoints lt 7 pt 9
set nolabel
set noarrow
