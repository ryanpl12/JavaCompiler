#Ryan Lucero
#4/15/2024
#Lab 8 
#Compilers Spring -- Shaun Cooper
#   The purpose of this lab is to accept a user inputted number, and calculate the 
#     summation of squares, from 1 until the input number and then output the sum


.data
        .align 0
str:
        .asciiz "sum of squares from 1 to "
strr:
        .asciiz " is "
prompt: 
        .asciiz "Enter the last number to square: "


.text  # directive that we are in the code segment

main:
        subu $a0, $sp, 16 # We want 4 mem locations for main SP, RA, i , s
        sw $ra, 4($a0)    # we need to store the RA in the Activation record
        sw $sp, ($a0)     # store SP
        move $sp, $a0     # adjust SP
        
        # Display prompt and read user input
        li $v0, 4         # Set syscall to print string
        la $a0, prompt    # Load address of prompt
        syscall           # Execute syscall to print
        li $v0, 5         # Set syscall to read number
        syscall           # Execute syscall to read
        sw $v0, 16($sp)   # Save user input

        sw $0, 8($sp)     # store 0 into memory -- counting variable 
        sw $0, 12($sp)    # store 0 into memory -- accumulating variable

loop:
        lw $t6, 8($sp)      # Load counter
        mul $t7, $t6, $t6   #  i * i
        lw $t8, 12($sp)     #  s
        addu $t9, $t8, $t7  #  s + i*i
        sw $t9, 12($sp)     #   s= s + i*i Store new sum
        lw $t6, 8($sp)      # i  Reload counter
        addu $t0, $t6, 1    # i+1       
        sw $t0, 8($sp)      #  i = i + 1

        lw $t5, 16($sp)     # Load user defined number
        ble $t0, $t5, loop  # Loop if counter less than entered number
        nop                 

        la $a0, str
        li $v0, 4         #    print the string
        syscall           
        nop                

        lw $a0, 16($sp)   # Load user limit
        li $v0, 1         #   Print the number
        syscall           

        la $a0, strr      # Load second string
        li $v0, 4         #   print the string
        syscall           
        
        lw $a0, 12($sp)   # Load final sum
        li $v0, 1         #   Print the number
        syscall           

        lw $ra, 4($sp)    # restore return
        lw $sp, ($sp)     # put backl Ra and SP

        li $v0, 10        # Set syscall for exit
        syscall           #  exit for MAIN only
        
