# Write the assembly code for the main of the compare program
.global main

.text

main:
enter $0, $0

#Moving the first num arg to %r12, and the second num arg to %r13
movq 8(%rsi), %r12
movq 16(%rsi), %r13

#Ensure that only two numbers are passed in (compare counts as an arg so we it should be 3 in total)
# If we have the correct number, jump to the loop that does the comparing
cmp $3, %rdi
je loop


#If less than or greater than 2 args are passed in, jump to the invalid function
jmp invalid

leave
ret

#Here, convert both num args to longs, and send them to the compare function in C
loop:

#Converting arg1
movq %r12, %rdi
call atol
movq %rax, %r12

#Converting arg2
movq %r13, %rdi
call atol
movq %rax, %r13

#Moving long args to arg registers and calling compare
movq %r12, %rdi
movq %r13, %rsi
call compare

#Check if the result is 0 (equal)
cmp $0, %rax
je equal

#Check if the result is -1 (less than)
cmp $-1, %rax
je less

#Check if the result is 1 (greater than)
cmp $1, %rax
je greater

#End main function here, all jumps should be successful by now
leave
ret

#Arg1 is greater than arg2, so we print out greater
greater:
movq $greatertxt, %rdi
mov $0, %al
call printf
leave
ret

#Arg1 is less than arg2, so we print out less
less:
movq $lesstxt, %rdi
mov $0, %al
call printf
leave
ret 

#The two args are equal, so we print out equal
equal:
movq $equaltxt, %rdi
mov $0, %al
call printf
leave
ret

#Number of args was greater or less than 2, so we print out the error statement
invalid:
movq $statement, %rdi
mov $0, %al
call printf
leave
ret


.data

#Contains all outputs that can be printed
statement:
.asciz "Two arguments required \n"

greatertxt:
.asciz "greater \n"

lesstxt:
.asciz "less \n"

equaltxt:
.asciz "equal \n"
