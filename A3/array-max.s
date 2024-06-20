# Write the assembly code for the array_max function

.global array_max


array_max:
	enter $0, $0
	# Num counter for the loops
	movq $0, %r15
	# number of args given in the array
	mov %rdi, %r12
	# arg addresses on the stack
	mov %rsi, %r13
	# current max value of the array (after each loop iteration)
	mov $0, %r14

loop:
	# Check to see if the loop is done (counter = num args)
	# If so, end loop and print out result
	cmp %r12, %r15
	jge loop_done
	
	#Compare current max to the current arg in array
	#If current arg is greater than current max, jump to function that will update max
	cmp %r14, (%rsi, %r15, 8)
	jg new_max
	
	# Else, increase counter and re-iterate the loop
	inc %r15
	jmp loop

#Update the max value here and recur the function again
new_max:
	# Update max, increase counter, recur again
	movq (%rsi, %r15, 8), %r14
	inc %r15
	jmp loop

# End the loop and print out the max value of the function
loop_done:
	movq %r14, %rax
	leave
	ret


