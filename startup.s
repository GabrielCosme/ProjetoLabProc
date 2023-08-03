
.text
.global start

start:
   // configura modo e pilha
   mov r0, #0b10011    // modo SVR
   msr cpsr, r0
   ldr sp, =inicio_stack 

   // zera segmento bss
   mov r0, #0
   ldr r1, =inicio_bss
   ldr r2, =fim_bss
loop:
   cmp r1, r2
   bge cont
   str r0, [r1], #4
   b loop
cont:
   // executa a função main()
   bl main

stop: 
   b stop  // se main() retornar...