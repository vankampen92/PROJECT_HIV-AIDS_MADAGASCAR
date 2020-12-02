# This is to convert each page of a ps file into a bunch of png files

gs -sDEVICE=jpeg -o out-%d.jpg $1
mogrify -format png *.jpg
