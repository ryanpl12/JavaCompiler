#
# makefile for LAB22
#  Spring 2024 
#    CS370 
#      Ryan Lucero
#        1/26/2023
#
all:    lab22


lab22:  lab22.l lab22.y
		lex lab22.l
		yacc -d lab22.y
		gcc lex.yy.c y.tab.c -o lab22

clean: 
	 rm -f lab22
