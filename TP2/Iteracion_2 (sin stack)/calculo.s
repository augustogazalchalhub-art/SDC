.global calcular_gini
.type calcular_gini, @function


calcular_gini:

    pushq %rbp
    movq %rsp, %rbp

    cvttss2siq %xmm0, %rax

    addq $1, %rax

    popq %rbp
    ret