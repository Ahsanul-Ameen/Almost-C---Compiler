#!/usr/bin/env bash
bison -d -y 1605047.y
echo 'step 1: bison -d -y 1605047.y ..... completed'
g++ -w -c -o y.o y.tab.c -g
echo 'step 2: g++ -w -c -o y.o y.tab.c -g...... completed'
flex 1605047.l
echo 'step 3: flex 1605047.l ....... completed'
g++ -w -c -o l.o lex.yy.c -g
#g++ -fpermissive -w -c -o l.o lex.yy.c -g
# if the above command doesn't work try    g++ -fpermissive -w -c -o l.o lex.yy.c -g    instead
echo 'step 4: g++ -w -c -o l.o lex.yy.c -g....... completed'
g++ -o a.out y.o l.o -lfl -ly -g
echo 'step 5: g++ -o a.out y.o l.o -lfl -ly -g ....... completed'
gdb ./a.out	
echo 'step 6: gdb ./a.out ........ completed'

#'step 7: enter command like:  (gdb) run input.c'

#'step 8: in case of segmentation faule: do the followings sequentially'
#'(gdb) backtrace'
#'(gdb) bt full'
#'(gdb) where'
#'(gdb) list'
