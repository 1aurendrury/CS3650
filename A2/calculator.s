#
# Usage: ./calculator <op> <arg1> <arg2>
#

# Make `main` accessible outside of this module
.global main

# Start of the code section
.text

# int main(int argc, char argv[][])
main:
  # Function prologue
  enter $0, $0
#movq $0, %al # needed for printf function

  # Variable mappings:
  # op -> %r12
  # arg1 -> %r13
  # arg2 -> %r14
  movq 8(%rsi), %r12  # op = argv[1]
  movq 16(%rsi), %r13 # arg1 = argv[2]
  movq 24(%rsi), %r14 # arg2 = argv[3]

# Converting the first arg into a long
movq %r13, %rdi
call atol
movq %rax, %r13
	
# Converting the second arg into a long
movq %r14, %rdi
call atol
movq %rax, %r14

#Getting the first byte of the operand, adding it to register dl
movb 0(%r12), %dl


#Comparing operands with given operand, jumping to respective functions when necessary
cmp $'+, %dl
je add


cmp $'-, %dl
je sub

cmp $'*, %dl
je mult

cmp $'/, %dl
je div

# Else, invalid operand, jump there
jmp invalidop


# End the main function here
leave
ret


# Add the two args together
add:
addq %r13, %r14
movq $format, %rdi
movq %r14, %rsi
mov $0, %al
call printf
leave
ret

#Subtract the two args together
sub:
subq %r14, %r13
movq $format, %rdi
movq %r13, %rsi
mov $0, %al
call printf
leave
ret

#Multiplt the two args together
mult:
imulq %r13, %r14
movq $format, %rdi
movq %r14, %rsi
mov $0, %al
call printf
leave 
ret

# Divide the args
div:
cmp $0, %r14
je invalid

movq %r13, %rax
movq $0, %rdx
cqto # Sign extension
idivq %r14
movq $format, %rdi
movq %rax, %rsi
call printf
leave
ret


# Function for invalid division, return statement to user
invalid:
movq $invaldiv, %rdi
call printf
mov $0, %al
leave 
ret

# Function for invalid operand, return statement to user
invalidop:
movq $invalarg, %rdi
mov $0, %al
call printf
leave
ret



# Start of the data section
.data

format: 
  .asciz "%ld\n"

# Invalid div statement
invaldiv:
.asciz "Invalid: cannot do division by 0\n"

#Invalid operand statement
invalarg:
.asciz "Unknown operation\n"

