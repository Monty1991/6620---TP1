.text
.align 2
#.globl compare_char
#.globl compare_num
#.globl my_atoi
#.globl partition
.globl qsort
#.globl qsort_lexicographical
#.globl qsort_numerical
.ent qsort

#DONE
# Punto de entrada
# a0 = char **izq
# a1 = char **der
# a2 = int num
qsort:
	#a pedido de la catedra
	.set noreorder
	.cpload t9
	.set reorder
	# saltamos a la funcion correspondiente
	beq $zero, $a2, qsort_lexicographical			# saltamos si num == 0
	nop
	j qsort_numerical
	nop

#DONE
# ordena en sentido lexicografico
# a0 = char **izq
# a1 = char **der
qsort_lexicographical:
	# tenemos que guardar SRA, ABA y el pivote en LTA
	subi $sp, $sp, 40							# 4*4 + 4*2 + 4*4 = 40
	sw $ra, 32($sp)							# guardamos ra
	sw $fp, 28($sp)							# guardamos fp
	sw $gp, 24($sp)							# guardamos gp
	sw $a0, 40($sp)							# guardamos a0
	sw $a1, 44($sp)							# guardamos a1
	subu $t0, a0, a1							# izq - der
	bgez t0, qsort_lexicographical_exit	# salimos si izq >= der
	nop
	la a3, compare_char						# a3 = referencia funcion compare_char
	jal partition									# llamamos a partition
	nop
	sw $v0, 20($sp)							# guardamos pivote en LTA
	lw $a0, 40($sp)							# a0 = izq
	mov $a1, $v0								# a1 = pivote
	jal qsort_lexicographical				# primera llamada recursiva
	nop
	lw $a0, 20($sp)							# a0 = pivote + 1
	addiu $a0, 1
	lw $a1, 44($sp)							# a1 = der
	jal qsort_lexicographical				# segunda llamada recursiva
	nop
qsort_lexicographical_exit
	lw $ra, 32($sp)							# recuperamos ra
	lw $fp, 28($sp)							# recuperamos fp
	lw $gp, 24($sp)							# recuperamos gp
	addiu $sp, $sp, 40						# destruimos el stack
	jr ra
	nop

#DONE
# ordena en sentido numerico
# a0 = char **izq
# a1 = char **der
qsort_numerical:
	# tenemos que guardar SRA, ABA y el pivote en LTA
	subi $sp, $sp, 40							# 4*4 + 4*2 + 4*4 = 40
	sw $ra, 32($sp)							# guardamos ra
	sw $fp, 28($sp)							# guardamos fp
	sw $gp, 24($sp)							# guardamos gp
	sw $a0, 40($sp)							# guardamos a0
	sw $a1, 44($sp)							# guardamos a1
	subu $t0, a0, a1							# izq - der
	bgez t0, qsort_numerical_exit			# salimos si izq >= der
	nop
	la a3, compare_char						# a3 = referencia funcion compare_num
	jal partition									# llamamos a partition
	nop
	sw $v0, 16($sp)							guardamos pivote en LTA
	lw $a0, 40($sp)							# a0 = izq
	mov $a1, $v0								# a1 = pivote
	jal qsort_numerical						# primera llamada recursiva
	nop
	lw $a0, 16($sp)							# a0 = pivote + 1
	addiu $a0, 1
	lw $a1, 44($sp)							# a1 = der
	jal qsort_numerical						# segunda llamada recursiva
	nop
qsort_numerical_exit
	lw $ra, 32($sp)							# recuperamos ra
	lw $fp, 28($sp)							# recuperamos fp
	lw $gp, 24($sp)							# recuperamos gp
	addiu $sp, $sp, 40						# destruimos el stack
	jr ra
	nop

#DONE
# particiona el conjunto en 2
# devuelve el pivote
# a0 = char **izq
# a1 = char **der
# a2 = int (* comparacion)(char *, char *)
partition:
	#debemos guardar SRA, ABA y 3 temporales en el stack
	subi $sp, $sp, 48							# 4*4 + 4*4 + 4*4 = 48
	sw $ra, 40($sp)							# guardamos ra
	sw $fp, 36($sp)							# guardamos fp
	sw $gp, 32($sp)							# guardamos gp
	sw $a0, 48($sp)							# guardamos a0
	sw $a1, 52($sp)							# guardamos a1
	sw $a2, 56($sp)							# guardamos a2
	lw $t0, 0($a0)								# pivote = *izq
	sw $t0, 16($sp)							# guardamos pivote
	subi $t1, $a0, 1							# begin = izq - 1
	sw $t1, 20($sp)							# guardamos begin
	addiu $t2, $a1, 1							# end = der + 1
	sw $t2, 24($sp)							# guardamos end
partition_big_loop:
partition_loop_begin:
	lw $t1, 20($sp)							# cargamos begin
	addiu $t1, 1								# incrementamos en 1
	sw $(t1), 20($sp)						# guardamos begin
	lw $a0, 0($t1)								# a0 = *begin
	lw $a1, 16($sp)							# a1 = pivote
	lw $a2, 56($sp)							# cargamos compare
	jalr $a2										# compare(*begin, pivote)
	nop
	bltz $v0, partition_loop_begin			# seguimos loop si *begin < pivote
	nop
partition_loo_end:
	lw $t1, 24($sp)							# cargamos end
	subi $t1, 1									# decrementamos en 1
	sw $(t1), 24($sp)						# guardamos end
	lw $a0, 0($t1)								# a0 = *end
	lw $a1, 16($sp)							# a1 = pivote
	lw $a2, 56($sp)							# cargamos compare
	jalr $a2										# compare(*end, pivote)
	nop
	bgtz $v0, partition_loop_end			# seguimos loop si *end > pivote
	nop

	lw $t1, 20($sp)							# cargamos begin
	lw $v0, 24($sp)							# cargamos end
	subu $t0, $t1, $v0
	bgez $t0, partition_exit					# si begin >= end, salimos
	nop

swap:
	sw $v0, 20($sp)							# guardamos end como begin
	sw $t1, 24($sp)							# guardamos begin como end
	j partition_big_loop						# loop infinito
	nop
partition_exit:
	lw $ra, 40($sp)							# recuperamos ra
	lw $fp, 36($sp)							# recuperamos fp
	lw $gp, 32($sp)							# recuperamos gp
	addiu $sp, $sp, 48						# destruimos el stack	
	jr ra
	nop

#DONE
# compara 2 cadenas asciiz
# a0 = char *izq
# a1 = char *der
# devuelve -1 si izq < der
# 0 si izq == der
# 1 si izq > der
compare_char:
	#funcion hoja, no tenemos que guardar
compare_char_loop:
	lw $t0, $(a0)									# x = *izq
	lw $(t1), $(a1)								# y = *der
	bne $t0, $t1, compare_char_out_loop	# salimos del loop si x != y
	nop
	bez $t1, compare_char_equal				# vemos si x == '\0'
	nop
	j compare_char_loop							# repetimos ciclo
	nop
compare_char_out_loop:
	sub $t2, $t0, $t1
	bgtz $t2, compare_char_greater			# x > y
	nop
	li $v0, -1										# izq < der
	j compare_char_exit							# salimos
	nop
compare_char_greater							# izq > der
	li $v0, 1
	j compare_char_exit
	nop
compare_char_equal:							# izq = der, devolvemos 0
	xor $v0, $v0, $v0
compare_char_exit:
	jr ra
	nop

#DONE
# compara 2 cadenas asciiz, interpretandolas como numeros
# a0 = char *izq
# a1 = char *der
compare_num:
	# no es hoja, por lo que tenemos que guardar el SRA y el ABA
	# tambien tenemos que guardar 1 numero temporal
	subi $sp, $sp, 40							# 4*4 + 4*2 + 4*4 = 40
	sw $ra, 32($sp)							# guardamos ra
	sw $fp, 28($sp)							# guardamos fp
	sw $gp, 24($sp)							# guardamos gp
	sw $a0, 40($sp)							# guardamos a0
	sw $a1, 44($sp)							# guardamos a1

	jal my_atoi									# llamamos my_atoi con a0
	nop
	sw $v0, 20$(sp)							# guardamos x, en el stack
	lw $a0, (36)$sp							# cargamos der en a0
	jal my_atoi									# llamamos my_atoi con a1
	nop
	lw $t0, 20$(sp)							# reclamamos x
	beq $t0, $v0, compare_num_part3	# comprobamos si x == y
	nop
	sub $t1, $t0, $v0							# x - y
	bgtz $t1, compare_num_part2		# comprobamos si x > y
	nop
	li $v0, -1									# x < y, devolvemos -1
	j compare_num_exit						# salimos
	nop
compare_num_part2:
	li $v0, 1										# x > y, devolvemos 1
	j compare_num_exit						# salimos
	nop
compare_num_part3:
	xor $v0, $v0, $v0							# x == y, devolvemos 0
compare_num_exit:
	lw $ra, 32($sp)							# recuperamos ra
	lw $fp, 28($sp)							# recuperamos fp
	lw $gp, 24($sp)							# recuperamos gp
	addiu $sp, $sp, 40						# destruimos el stack
	jr ra
	nop

#DONE
# convierte una cadena de texto en el numero representado
# no interpreta el signo, pero se detiene en el primer caracter no digito
# a0 = char *str
my_atoi:
	# funcion hoja, no guardamos nada
	xor $v0, $v0					# inicializamos contador num en 0
	li $t0, '0'							# cargamos el digito 0 en t0
	li $t1, 10						# cargamos constante 10 para multiplicar
my_atoi_loop:
	mul $v0, $v0, $t1				# num *= 10;
	subi $t0, $t0, '0'				# digit ahora esta entre 0 y 9
	add $v0, $v0, t0				# num += digit
	lw $t0, 0($a0)					# digit = *str
	addi $a0, 1						# str++ (avanzamos 1 char)
	sub $t2, $t1, '0'				# comparamos digit con '0'
	bltz $t2, my_atoi_exit		#salimos si es menor
	nop
	sub $t2, $1, '9'				#comparamos con '9'
	bgtz $t2, my_atoi_loop		#salimos si es mayor
	nop
my_atoi_exit:
	jr ra
	nop
