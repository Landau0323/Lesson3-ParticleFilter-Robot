set term postscript color enhanced

set xrange [0:100]
set yrange [0:100]

set output "plot1.eps"

plot "particles.dat" index 0, "true_robot.dat" index 0
#plot "particles.dat" index 1, "true_robot.dat" index 0
#plot "particles.dat" index 2, "true_robot.dat" index 1
#plot "particles.dat" index 3, "true_robot.dat" index 1

reset