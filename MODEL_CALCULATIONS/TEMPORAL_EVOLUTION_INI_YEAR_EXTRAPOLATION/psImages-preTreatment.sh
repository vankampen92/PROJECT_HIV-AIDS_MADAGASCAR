# This is to convert each page of a ps file into a bunch of ps files
gs -sDEVICE=ps2write -o out-%d.ps boxplot.ps

# This is to crop blank space around the plot in ps files
ps2ps [FILE].ps output.ps
ps2eps output.ps
epstopdf output.eps

# This is to convert each page of a ps file into a bunch of png files
gs -sDEVICE=jpeg -o out-%d.jpg $1
mogrify -format png *.jpg
